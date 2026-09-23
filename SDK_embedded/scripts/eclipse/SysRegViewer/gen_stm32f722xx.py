'''
Created on 22.04.2012

@author: johnny
'''

from xmlGen import *

g = XmlGen()
g.parse("headers/f7/stm32f722xx.h")

g.chipname = "stm32f722xx"
g.groups = [
            Group('ADC'),
            Group('CAN'),
            Group('CRC'),
            Group('DAC'),
            Group('DBGMCU'),
            Group('EXTI'),
            Group('FLASH'),
            Group('FMC', 'FMC'),
            Group('IWDG'),
            Group('PWR'),
            Group('QUADSPI'),
            Group('RCC'),
            Group('RNG'),
            Group('RTC'),
            Group('SAI', 'SAI'),
            Group('SDMMC', 'SDMMC'),
            Group('SYSCFG'),
            Group('USB_OTG_FS'),
            Group('USB_OTG_HS'),
            Group('DMA1'),
            Group('DMA2'),
            Group('GPIO'),
            Group('I2C'),
            Group('SPI'),
            Group('TIM' ),
            Group('LPTIM' ),
            Group(('USART', 'UART')),
            Group('WWDG' ),
           ]
g.generate()


g.toXml('xml/stm32f722xx.xml')

