'''
Created on 22.04.2012

@author: johnny
'''

import common
from common import *

class Periph:
  def __init__(self, name, type, base):
    self.name = name
    self.type = type
    self.base = base
    self.addr = -1

  def __repr__(self):
    return self.name + ' ' + self.type + ' at ' + self.base
  __str__ = __repr__

class Periphs:
  tokens = (
          'DEFINE',
          'NAME',
          'COMMENT'
          )
  literals = '*()'

  t_DEFINE = r"\#define"
  def t_NAME(self, t):
    r'[A-Za-z_][A-Za-z0-9_]*'
    return t

  def t_COMMENT(self, t):
    r'/\*(.|\n)*?\*/'
    return None

  t_ignore = " \t"
  t_newline = common.l_newline
  t_error = common.l_error


  def p_all(self, p):
    '''all : define all
           | '''

  def p_define(self, p):
    '''define : DEFINE NAME '(' '(' NAME '*' ')' NAME ')' '''
    name = p[2]
    self.periphs[name] = Periph(name, p[5], p[8])

  def p_define_ignored(self, p):
    '''define : DEFINE NAME'''


  p_error = common.p_error

  def __init__(self, lineAndText):
    self.periphs = {}
    common.parse(self, lineAndText)

  def __str__(self):
    return '\n'.join(str(v) for v in self.periphs.values())

  def __getitem__(self, ind): return self.periphs[ind]
  def __len__(self): return len(self.periphs)
  def __nonzero__(self):
    return True

