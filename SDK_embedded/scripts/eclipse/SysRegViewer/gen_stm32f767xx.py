'''
Created on 22.04.2012

@author: johnny
'''

from xmlGen import *

g = XmlGen()
g.parse("headers/f7/stm32f767xx.h")

g.chipname = "stm32f767xx"
g.groups = [
            Group('TIM'),
            Group('SPI'),
            Group('I2C'),
            Group('USART'),
            Group('UART'),
            Group('CAN'),
            Group('ADC'),
            Group('DMA1'),
            Group('DMA2'),
            Group('FMC'),
            Group('GPIO'),
            Group('SAI'),
            Group('DFSDM'),
            Group('LTDC'),
            Group('SDMMC'),
           ]
g.generate()


g.toXml('xml/stm32f767.xml')

