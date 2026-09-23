'''
Created on 22.04.2012

@author: johnny
'''

import common
from common import *
import re

class BitField:
  def __init__(self, name, bitname, value, comment):
    self.name = name
    self.bitname = bitname
    self.value = value
    self.comment = comment

    startNonZero = -1
    endNonZero = 0
    for i in xrange(0, 32):
      if ((value >> i) & 1) == 1:
        if startNonZero == -1:
          startNonZero = i
        endNonZero = i
    self.offset = startNonZero
    self.length = endNonZero - startNonZero + 1
  def __repr__(self):
    return "Bitfield[%s: %s %s %s]" % (self.name, self.bitname, self.value, self.comment)
  __str__ = __repr__

reIgnoreName = re.compile('(_\d+)|(_Pos)|(_Msk)$')

class BitFields:
  tokens = (
          'DEFINE',
          'NAME',
          'NUMBER',
          'DOC_COMMENT',
          'IGNORED_COMMENT',
          'LSHIFT',
          ) + types
  literals = '()'

  t_LSHIFT = "<<"
  t_DEFINE = "\#define"
  def t_NAME(self, t):
    r'[A-Za-z_][A-Za-z0-9_]*'
    if t.value in types:
      t.type = t.value
    return t

  t_NUMBER = common.l_number
  def t_DOC_COMMENT(self, t):
    r'/\*!<(.|\n)*?\*/'
    t.value = t.value[4:-2].strip()
    return t

  def t_IGNORED_COMMENT(self, t):
    r'/\*(.|\n)*?\*/'
    return None

  t_ignore = " \t"
  t_newline = common.l_newline
  t_error = common.l_error

  def p_all(self, p):
    '''all : define all
           | comment all 
           | '''

  def p_define(self, p):
    'define : DEFINE NAME expr comment'
    name = p[2]

    pos = name.find('_')
    if pos == -1:
      print 'ignore 2 ' + name
    else:
      pos = name.find('_', pos + 1)
      if pos == -1:
        print 'ignore 3 ' + name

    bitname = name[pos + 1:] if pos >= 0 else ''
    bf = BitField(name, bitname, p[3], p[4])
    # print bf
    self.bitfields[name] = bf

    if reIgnoreName.search(name) or pos == -1:
      return

    regn = name[:pos]
    if regn in self.regbitfields:
      lst = self.regbitfields[regn]
    else:
      lst = []
      self.regbitfields[regn] = lst
    lst.append(bf)

  def p_expression(self, p):
    '''expr : '(' '(' type ')' NUMBER ')' '''
    p[0] = p[5]

  def p_expression_pos(self, p):
    '''expr : '(' NUMBER ')' '''
    p[0] = p[2]

  def p_expression_msk(self, p):
    '''expr : '(' NUMBER  LSHIFT NAME ')' '''
    p[0] = p[2] << self.bitfields[p[4]].value

  def p_expression_number(self, p):
    '''expr : NUMBER '''
    p[0] = p[1]

  def p_expression_name(self, p):
    '''expr : NAME '''
    p[0] = self.bitfields[p[1]].value

  @setDoc('type : ' + '\n| '.join(types))
  def p_type(self, p):
    pass

  def p_comment(self, p):
    ''' comment : DOC_COMMENT
                | '''
    if len(p) > 1:
      p[0] = p[1]
    else:
      p[0] = ''

  def p_define_ignored(self, p):
    'define : DEFINE NAME comment'

  p_error = common.p_error

  def __init__(self, lineAndText):
    self.bitfields = {}
    self.regbitfields = {}

    common.parse(self, lineAndText)

  def __str__(self):
    return str(self.bitfields)

  def __getitem__(self, ind):
    return self.bitfields[ind]
