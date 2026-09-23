'''
Created on 22.04.2012

@author: johnny
'''

from ply import lex, yacc
from ply.lex import TOKEN

types = ('uint32_t', 'uint16_t', 'uint8_t')
keywords = ('typedef', 'struct')
io = ('__IO', '__I', '__O')

def l_number(self, t):
    r'(([1-9][0-9]*)|(0x[0-9A-Fa-f]+)|0)U?'
    if t.value[-1] == 'U':
      t.value = t.value[:-1]
    if len(t.value) > 2 and t.value[1] == "x":
      t.value = int(t.value, 16)
    else:
      t.value = int(t.value)
    return t

def l_newline(self, t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")

def l_error(self, t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

def p_error(self, p):
  if p:
    print("Syntax error at token", p.type, " line:", p.lineno + self.startLine, " value:", p.value)
    # Just discard the token and tell the parser it's okay.
    self.parser.errok()
  else:
    print("Syntax error at EOF")

def parse(self, lineAndText):
  self.lexer = lex.lex(object=self)
  self.parser = yacc.yacc(module=self)
  self.startLine = lineAndText[0]
  self.parser.parse(lineAndText[1], lexer=self.lexer)

def setDoc(doc):
  def setDoc_proxy(f):
    f.__doc__ = doc
    return f
  return setDoc_proxy
