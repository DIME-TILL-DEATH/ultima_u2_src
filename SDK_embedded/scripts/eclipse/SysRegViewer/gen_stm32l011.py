'''
Created on 22.04.2012

@author: johnny
'''

from xmlGen import *

g = XmlGen()
g.parse("headers/l0/stm32l011.h")

g.chipname = "stm32l011"
g.groups = [
           ]
g.generate()


g.toXml('xml/stm32l011.xml')

