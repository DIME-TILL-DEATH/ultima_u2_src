'''
Created on 22.04.2012

@author: johnny
'''

import common
from common import *

class RegField:
  def __init__(self, io, const, type, name, count, comment):
    self.io = io
    self.const = const
    self.type = type
    self.name = name
    self.count = count
    self.bitfields = []  # [bitfields.BitField(), ... ]

    pos = comment.find('Address offset:')
    if pos != -1:
      comment = comment[:pos].strip()
      if comment[-1] == ',':
        comment = comment[:-1]
    parts = comment.split('\n')
    comment = ' '.join(p.strip() for p in parts)
    self.comment = comment

  def __repr__(self):
    res = ''
    if self.io: res += self.io + ' '
    res += '%r %r' % (self.type, self.name)
    if self.count: res += '[' + str(self.count) + ']'
    if self.comment: res += ' // ' + self.comment
    return res
  __str__ = __repr__

  def elemSize(self):
    if self.type == 'uint8_t':
      return 1
    elif self.type == 'uint16_t':
      return 2
    elif self.type == 'uint32_t':
      return 4
    else:
      return self.type.sizeof()

  def sizeof(self):
    cnt = self.count if self.count else 1
    return cnt * self.elemSize()


class RegTypedef:
  def __init__(self, name, fieldlist):
    self.name = name
    self.fields = fieldlist

  def __repr__(self):
    return self.name + "(" + str(self.fields) + ")"
  __str__ = __repr__

  def __getitem__(self, n):
    return self.fields[n]

  def __len__(self):
    return len(self.fields)

  def sizeof(self):
    res = 0
    for f in self.fields:
      res += f.sizeof()
    return res

  def addBitFields(self, regbitfields):
    if self.name.endswith('_TypeDef'):
      name = self.name[:-len('_TypeDef')]
    else:
      name = self.name
    for f in self.fields:
      f.bitfields = regbitfields.get(name + '_' + f.name, [])
      # print self.name, f, f.bitfields


class RegTypedefs:
  tokens = types + keywords + io + ('CONST', 'NUMBER', 'IGNORE_COMMENT', 'DOC_COMMENT', 'NAME')
  literals = '[]{};'
  t_ignore = ' \t'
  t_CONST = 'const'
  t_newline = common.l_newline
  t_error = common.l_error
  def t_NAME(self, t):
    r'[A-Za-z_][A-Za-z0-9_]*'
    if t.value in types or t.value in keywords or t.value in io:
      t.type = t.value
    if t.value == 'const':
      t.type = 'CONST'
    return t
  def t_DOC_COMMENT(self, t):
    r'/\*!<(.|\n)*?\*/'
    t.value = t.value[4:-2].strip()
    return t
  def t_IGNORE_COMMENT(self, t):
    r'/\*(.|\n)*?\*/'
    return None
  t_NUMBER = common.l_number


  def p_all(self, p):
    '''all : reg all 
           | '''

  def p_reg(self, p):
    '''reg : typedef struct '{' fieldlist '}' NAME ';' '''
    name = p[6]
    p[0] = RegTypedef(name, p[4])
    self.regs[name] = p[0]

  def p_fieldlist(self, p):
    '''fieldlist : field fieldlist 
                 | '''
    if len(p) > 1:
      p[0] = [p[1]] + p[2]
    else:
      p[0] = []

  def p_field(self, p):
    '''field : io const type NAME array ';' comment '''
    p[0] = RegField(p[1], p[2], p[3], p[4], p[5], p[7])

  @setDoc('io : \n| ' + '\n| '.join(io))
  def p_io(self, p):
    p[0] = p[1] if len(p) > 1 else None

  def p_const(self, p):
    '''const : CONST
             | '''
    p[0] = len(p) > 1

  @setDoc('type : ' + '\n| '.join(types))
  def p_type_builtin(self, p):
    p[0] = p[1]

  def p_type_custom(self, p):
    'type : NAME'
    p[0] = self.regs[p[1]]

  def p_array(self, p):
    '''array : '[' NUMBER ']' 
             |  '''
    p[0] = p[2] if len(p) > 1 else None

  def p_comment(self, p):
    '''comment : DOC_COMMENT 
               | '''
    p[0] = p[1] if len(p) > 1 else ''

  p_error = common.p_error

  def __init__(self, lineAndText):
    self.regs = {}
    common.parse(self, lineAndText)

  def __str__(self):
    return '\n'.join(str(r) for r in self.regs.values())

  def __getitem__(self, ind):
    return self.regs[ind]
