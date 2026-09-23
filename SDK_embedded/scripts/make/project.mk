# application defined config

ifndef PRJ_NAME
	PROJECT=PRJ_NAME_UNKNOWN
endif

#identical config for all projects
USBD_VID=0xff00 #"\"BG-Optics"\"
MANUFACTURER_STRING="\"BG-Optics"\"

ifeq ($(PRJ_NAME),code_polygon)
    PROJECT_DESCRIPTION="\"Code polygon for dev & testing experimental code"\"
    ifndef PLATFORM
    	PLATFORM=MAGNITOMETR_V1
    endif	
    USBD_PID=0x0000
else ifeq ($(PRJ_NAME),bldc)
    PROJECT_DESCRIPTION="\"Brush less DC motor controller"\"
    PLATFORM=SOROKIN_BLDC_V1
    USBD_PID=0x0001
else ifeq ($(PRJ_NAME),ofmm)
    PLATFORM=MOD01_04R1
    PROJECT_DESCRIPTION="\"BG-Optics optofiber modulator module (OFMM)"\"
    DEV_DESCRIPTION="\"$(PLATFORM)"\"
    USBD_PID=0x0002
else ifeq ($(PRJ_NAME),pump_laser_module)
    PLATFORM=PUMP_LASER_MODULE_M0
    PROJECT_DESCRIPTION="\"IR pump laser module"\"
    DEV_DESCRIPTION="\"One chanal PCB, FOL1402PNO-417"\"
    USBD_PID=0x0003
else ifeq ($(PRJ_NAME),dsp_pipe)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"dsp pipe experement"\"
    DEV_DESCRIPTION="\"Volkov V2 board with STM32F405RGT6 chip"\"
    USBD_PID=0x0004
else ifeq ($(PRJ_NAME),usb_gen)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"usb function signal generator"\"
    DEV_DESCRIPTION="\"Volkov V2 board with STM32F405RGT6 chip"\"
    USBD_PID=0x0005
else ifeq ($(PRJ_NAME),sync_module)
    PLATFORM=SYNCHRO_MODULE_M1
    PROJECT_DESCRIPTION="\"Synchronizer/modulator firmware"\"
    DEV_DESCRIPTION="\"Synchronizer/modulator module"\"
    USBD_PID=0x0006
else ifeq ($(PRJ_NAME),usb_standalone)
    PLATFORM=TE_STM32F405
    PROJECT_DESCRIPTION="\"USB<-->USART bridge"\"
    DEV_DESCRIPTION="\"TE-STM32F405 board"\"
    USBD_PID=0x0007
else ifeq ($(PRJ_NAME),black_box)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"black box registartor for UAV development"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2"\"
    USBD_PID=0x0008
else ifeq ($(PRJ_NAME),uhf_module)
    PLATFORM=MAGNITOMETR_V1
    PROJECT_DESCRIPTION="\"UHF generator 25..44000 MHz, ADF4351 used"\"
    DEV_DESCRIPTION="\"UHF generator"\"
    USBD_PID=0x0009
else ifeq ($(PRJ_NAME),opto_link)
    PLATFORM=OPTO_LINK
    PROJECT_DESCRIPTION="\"Opto link, debug version 12 MBit/s"\"
    DEV_DESCRIPTION="\"Opto link, 12Mbit/s"\"
    USBD_PID=0x000A
else ifeq ($(PRJ_NAME),opto_phase_modulator)
    PLATFORM=OPTO_PHASE_MODULATOR
    PROJECT_DESCRIPTION="\"Opto phase modulator"\"
    DEV_DESCRIPTION="\"Opto phase modulator"\"
    USBD_PID=0x000B
else ifeq ($(PRJ_NAME),ahrs)
    ifndef PLATFORM
    	PLATFORM=VOLKOV_STM32F405_V2
    endif
    PROJECT_DESCRIPTION="\"AHRS module"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 board"\"
    USBD_PID=0x000C
else ifeq ($(PRJ_NAME),vodolazen_m3)
    PLATFORM=VODOLAZEN_M3
    PROJECT_DESCRIPTION="\"vodolazen trener system"\"
    DEV_DESCRIPTION="\"VODOLAZEN_M3 board"\"
    USBD_PID=0x000D
else ifeq ($(PRJ_NAME),sound_mixer_m0)
    PLATFORM=SOUND_MIXER_M0
    PROJECT_DESCRIPTION="\"sound mixer"\"
    DEV_DESCRIPTION="\"sound mixer m0 board"\"
else ifeq ($(PRJ_NAME),usb2can)
    PLATFORM=TE_STM32F405
    PROJECT_DESCRIPTION="\"usb2can"\"
    DEV_DESCRIPTION="\"usb2can board"\"
    USBD_PID=0x000E
else ifeq ($(PRJ_NAME),usb_midi_device)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"USB MIDI device"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 test board"\"
    USBD_PID=0x0010
else ifeq ($(PRJ_NAME),bldc_ctrl_mc)
    PLATFORM=VOLKOV_STM32F030_V1
    PROJECT_DESCRIPTION="\"Microcip BLDC controler"\"
    DEV_DESCRIPTION="\"BLDC controller board"\"
else ifeq ($(PRJ_NAME),multi_drive_storage_demo)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"multi drive storage demo"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 demo board"\"
    USBD_PID=0x0011
else ifeq ($(PRJ_NAME),amt_dev)
    PLATFORM=AMT_DEV_BOARD_V1
    PROJECT_DESCRIPTION="\"demo code for AMT_DEV_BOARD_V1 (aka SD,SHARK,OLED,7-SEGMENTS,CODEC,etc...)"\"
    DEV_DESCRIPTION="\"AMT development board with ADSP-21489"\"
    USBD_PID=0x0012
else ifeq ($(PRJ_NAME),pump_vector)
    PLATFORM=PUMP_VECTOR_M0
    PROJECT_DESCRIPTION="\"Multichannel's (VECTOR) pump laser module"\"
    DEV_DESCRIPTION="\"5-channal board"\"
    USBD_PID=0x0013
else ifeq ($(PRJ_NAME),bldc_m0)
    PLATFORM=BLDC_M0_DEV_BOARD
    PROJECT_DESCRIPTION="\"BLDC motor FOC controller"\"
    DEV_DESCRIPTION="\"2-stage(control & power) devboard for test and development"\"
    USBD_PID=0x0014
else ifeq ($(PRJ_NAME),spectrum_analyzer)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"Spectrum analyzer/FFT demo"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 test board"\"
    USBD_PID=0x0015
else ifeq ($(PRJ_NAME),soa_module)
    PLATFORM=SOA_MODULE_V01_01_01
    PROJECT_DESCRIPTION="\"SOA module"\"
    DEV_DESCRIPTION="\"SOA module PCB Rev.01"\"
    USBD_PID=0x0016
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_kgl)
    PLATFORM=STM32F429_DISCOVERY
    PROJECT_DESCRIPTION="\"Klen's GL demo firmware"\"
    DEV_DESCRIPTION="\"ST stm32d429-discovery board"\"
    USBD_PID=0x0017
else ifeq ($(PRJ_NAME),sunset_loader_fx)
    PLATFORM=AMT_PANGAEA_FX
    PROJECT_DESCRIPTION="\"AMD devboard"\"
    DEV_DESCRIPTION="\"SunSet FX boot loader/updater over uSD/NAND/USB"\"
    USBD_PID=0x0018
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_lua)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"Lua demo"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x0019
else ifeq ($(PRJ_NAME),standalone_template)
    PLATFORM=COMMON_STM32F103_BOARD
    PROJECT_DESCRIPTION="\"standalone template"\"
    DEV_DESCRIPTION="\"COMMON_STM32F103_BOARD"\"
    USBD_PID=0x001A
else ifeq ($(PRJ_NAME),standalone_msc)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"standalone_msc"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x001B
else ifeq ($(PRJ_NAME),fs_ctrl_dev)
    PLATFORM=SOROKIN_DEVBOARD_STM32f4_M1
    PROJECT_DESCRIPTION="\"File sytem contol device demo"\"
    DEV_DESCRIPTION="\"SOROKIN_DEVBOARD_STM32f4_M1 dev board"\"
    USBD_PID=0x001C
else ifeq ($(PRJ_NAME),NEW_PRJ)
#    использовать для вновь заводимого проекта
#    PLATFORM=VOLKOV_STM32F405_V2
#    PROJECT_DESCRIPTION="\" NEW_PRJ "\"
#    DEV_DESCRIPTION="\" XXX BOARD "\"
#    USBD_PID=0x001D
    
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_libopencm3_cdc)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"CDC(libopencm3)/FreeRTOS demo"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x001E
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_libopencm3_msc)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"MSC(libopencm3)/FreeRTOS demo"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x001E
else ifeq ($(PRJ_NAME),digital_tube_amplifier)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"digital tube amplifier"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x001F
else ifeq ($(PRJ_NAME),engine_control_unit)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"engine control unit (ignition,injection)"\"
    DEV_DESCRIPTION="\"temporary VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x0020
else ifeq ($(PRJ_NAME),sync14c)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"sync + 14 analog output chanal + phase modulator"\"
    DEV_DESCRIPTION="\"temporary VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x0021
else ifeq ($(PRJ_NAME),bgesc)
    PLATFORM=BGESC_MINI
    PROJECT_DESCRIPTION="\"bg esc with foc"\"
    DEV_DESCRIPTION="\"dual PCB 'mini' module"\"
    USBD_PID=0x0023
else ifeq ($(PRJ_NAME),gsl_demo)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"GSL demo code"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x0024
else ifeq ($(PRJ_NAME),data_acquisition)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"Data acquisition stm32 base device"\"
    DEV_DESCRIPTION="\"VOLKOV_STM32F405_V2 dev board"\"
    USBD_PID=0x0025
else ifeq ($(PRJ_NAME),pump_rx_c2)
    PLATFORM=PUMP_RX_2C
    PROJECT_DESCRIPTION="\"Data acquisition stm32 base device"\"
    DEV_DESCRIPTION="\"pump rx 2 chanel with variable gain"\"
    USBD_PID=0x0026
else ifeq ($(PRJ_NAME),demo_stm32f7)
    PLATFORM=NUCLEO_F767ZI
    PROJECT_DESCRIPTION="\"..demo stm32f7.."\"
    DEV_DESCRIPTION="\"NUCLEO F767ZI board"\"
    USBD_PID=0x0027
else ifeq ($(PRJ_NAME),demo_stm32f7_freertos)
    PLATFORM=NUCLEO_F767ZI
    PROJECT_DESCRIPTION="\"..demo stm32f7 FreeRTOS.."\"
    DEV_DESCRIPTION="\"NUCLEO F767ZI board"\"
    USBD_PID=0x0028
else ifeq ($(PRJ_NAME),sync_interferometr)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"sync module for interferoment"\"
    DEV_DESCRIPTION="\"dev sync device"\"
    USBD_PID=0x0029
else ifeq ($(PRJ_NAME),sd_multi_player)
    PLATFORM=AMT_DEV_BOARD_V1
    #VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"SD multiplayer"\"
    DEV_DESCRIPTION="\"AMT devboard v1"\"
    USBD_PID=0x002A  
else ifeq ($(PRJ_NAME),nll_test_set)
    PLATFORM=NLL_TEST_BOARD_SET
    PROJECT_DESCRIPTION="\"Макет модуля ускополосгого лазера"\"
    DEV_DESCRIPTION="\"Макетный набор плат на медном диске"\"
    USBD_PID=0x002B
else ifeq ($(PRJ_NAME),stm32f1xx_demo)
    PLATFORM=MINIMUM_SYSTEM_DEV_BOARD
    PROJECT_DESCRIPTION="\"демонстратор stm32f1xx"\"
    DEV_DESCRIPTION="\"Макетная плата MinimunSystemDesigneBoard"\"
    USBD_PID=0x002C
else ifeq ($(PRJ_NAME),multicell_balanser)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"балансировщик батареи"\"
    DEV_DESCRIPTION="\"Макетная плата Volkov v2"\"
    USBD_PID=0x002D
else ifeq ($(PRJ_NAME),fs_browser)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"файловый проводник"\"
    DEV_DESCRIPTION="\"Макетная плата Volkov v2"\"
    USBD_PID=0x002E
else ifeq ($(PRJ_NAME),nll)
    PLATFORM=NLL_M7_BOARD
    PROJECT_DESCRIPTION="\"модуль ускополосгого лазера()"\"
    DEV_DESCRIPTION="\"плата под герметичный корпус"\"
    USBD_PID=0x002F
else ifeq ($(PRJ_NAME),demo_fixmath)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"фиксированная запятая"\"
    DEV_DESCRIPTION="\"Макетная плата Volkov v2"\"
    USBD_PID=0x0030
else ifeq ($(PRJ_NAME),sunset_loader_proto)
    PLATFORM=PLATFORM_?
    PROJECT_DESCRIPTION="\"шаблон унверсального загрузчика"\"
    DEV_DESCRIPTION="\"<?>"\"
    USBD_PID=0x0031
else ifeq ($(PRJ_NAME),sync_nano)
    PLATFORM=NUCLEO_F767ZI
    PROJECT_DESCRIPTION="\"синхронизатор stm32f7xx"\"
    DEV_DESCRIPTION="\"<?>"\"
    USBD_PID=0x0032
else ifeq ($(PRJ_NAME),pitch_shifter)
    PLATFORM=NUCLEO_F767ZI
    PROJECT_DESCRIPTION="\"pitch shifter demo on NUCLEO_F767ZI"\"
    DEV_DESCRIPTION="\"<?>"\"
    USBD_PID=0x0033
else ifeq ($(PRJ_NAME),lora)
    PLATFORM=LORA_MODEM_M1_BOARD
    PROJECT_DESCRIPTION="\"модем с модулем RFM98W+PA"\"
    DEV_DESCRIPTION="\"корпусированное изделие"\"
    USBD_PID=0x0034
else ifeq ($(PRJ_NAME),multicell_balancer_passive)
    PLATFORM=BALANCER_PASSSIVE_BOARD_V1
    PROJECT_DESCRIPTION="\"модем с модулем Lora и усилителем мощности"\"
    DEV_DESCRIPTION="\"корпусированное изделие"\"
    USBD_PID=0x0035
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_syscalls)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"demo stm32f4 freertos syscalls"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x0036
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_adc_dma)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"demo stm32f4 freertos adc dma"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x0037
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_ocm3_emfat)
    PLATFORM=DTEC_V0
    PROJECT_DESCRIPTION="\"emfat control device"\"
    DEV_DESCRIPTION="\"временно DTEC_V0"\"
    USBD_PID=0x0037
else ifeq ($(PRJ_NAME),pump)
    PLATFORM=PUMP
    PROJECT_DESCRIPTION="\"Data acquisition stm32 base device"\"
    DEV_DESCRIPTION="\"Er+ optofiber pump 1,2,5 chanel's "\"
    USBD_PID=0x0038
else ifeq ($(PRJ_NAME),demo_stm32f4)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"demo stm32f4"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
else ifeq ($(PRJ_NAME),demo_stm32f4_adv_tim_six_step)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"demo stm32f4 6-step PWM"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x0039
else ifeq ($(PRJ_NAME),demo_stm32f722_freertos_usb)
    PLATFORM=SOROKIN_BLDC_V1
    PROJECT_DESCRIPTION="\"..demo stm32f7 FreeRTOS+usb.."\"
    DEV_DESCRIPTION="\"SOROKIN_BLDC_V1 board"\"
    USBD_PID=0x003a
else ifeq ($(PRJ_NAME),tv)
    PLATFORM=TV_GENERATOR_BOARD_V1
    PROJECT_DESCRIPTION="\"ТВ генератор"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x003b
else ifeq ($(PRJ_NAME),demo_stm32f4_sdcard)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"SD card demo"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x003c
else ifeq ($(PRJ_NAME),demo_stm32f4_freertos_fatfs)
    PLATFORM=VOLKOV_STM32F405_V2
    PROJECT_DESCRIPTION="\"SD card+fatfs demo"\"
    DEV_DESCRIPTION="\"непотопляемая Волковская плата"\"
    USBD_PID=0x003d
else ifeq ($(PRJ_NAME),demo_stm32f7_freertos_bootloader)
    PLATFORM=NUCLEO_F767ZI
    PROJECT_DESCRIPTION="\"..demo stm32f7 freertos bootloader.."\"
    DEV_DESCRIPTION="\"NUCLEO F767ZI board"\"
    USBD_PID=0x0027
else ifeq ($(PRJ_NAME),amt_ultima_f7_bootloader)
    PLATFORM=AMT_F7_V1A
    PROJECT_DESCRIPTION="\"базовая код загрузчика"\"
    DEV_DESCRIPTION="\"AMT_F7_V1A board"\"
    USBD_PID=0x0028
else ifeq ($(PRJ_NAME),amt_ultima_f7_bootloader_app)
    PLATFORM=AMT_F7_V1A
    PROJECT_DESCRIPTION="\"базовый код приложения"\"
    DEV_DESCRIPTION="\"AMT_F7_V1A board"\"
    USBD_PID=0x0029
else ifeq ($(PRJ_NAME),amt_ultima_f7_cabsim)
    PLATFORM=AMT_F7_V1A
    PROJECT_DESCRIPTION="\"cabinet simulator"\"
    DEV_DESCRIPTION="\"AMT_F7_V1A board"\"
    USBD_PID=0x002a     
else ifeq ($(PRJ_NAME),no2)
    PLATFORM=NO2
    PROJECT_DESCRIPTION="\"изделиe ДА"\"
    DEV_DESCRIPTION="\"NO2 board"\"
    USBD_PID=0x002b
else ifeq ($(PRJ_NAME),dtec)
    PLATFORM=DTEC_V0
    PROJECT_DESCRIPTION="\"цифровой TEC"\"
    DEV_DESCRIPTION="\"dtec v0 board"\"
    USBD_PID=0x002c
else ifeq ($(PRJ_NAME),marcus_bldc)
    PLATFORM=MARCUS_ESC
    PROJECT_DESCRIPTION="\"порт кода Маркуса"\"
    DEV_DESCRIPTION="\"BG-OPTICS version MARCUS ESC"\"
    USBD_PID=0x002c
else ifeq ($(PRJ_NAME),leds_demo)
    PLATFORM=EASY_MX_PRO_V7_STM32F407
    PROJECT_DESCRIPTION="\"EasyMX Pro V7"\"
    DEV_DESCRIPTION="\"EasyMX Pro V7"\"
    USBD_PID=0x002e
else ifeq ($(PRJ_NAME),demo_stm32h7)
    PLATFORM=NUCLEO_H743ZI
    PROJECT_DESCRIPTION="\"demo for h7"\"
    DEV_DESCRIPTION="\"NUCLEO F767ZI board"\"
    USBD_PID=0x002f
else ifeq ($(PRJ_NAME),no2_master)
    PLATFORM=DTEC_V0
    PROJECT_DESCRIPTION="\"no2 master"\"
    DEV_DESCRIPTION="\"dtec v0 board"\"
    USBD_PID=0x0030
else ifeq ($(PRJ_NAME),nll2)
    PLATFORM=NLL_V2
    PROJECT_DESCRIPTION="\"narow line laser v2(with Duraev)"\"
    DEV_DESCRIPTION="\"narow line laser v2 board"\"
    USBD_PID=0x0031
else ifeq ($(PRJ_NAME),synthesizer_hmc832_500_1400MHz)
    PLATFORM=SYNTHESIZER_HMC832_REFBOARD
    PROJECT_DESCRIPTION="\"synthesizer by hmc832 (500..1400 MHz)"\"
    DEV_DESCRIPTION="\"bg-optics hmc832 ref board"\"
    USBD_PID=0x0032
else ifeq ($(PRJ_NAME),amt_nibiru)
    PLATFORM=AMT_NIBIRU1
    PROJECT_DESCRIPTION="\"cabinet simulator"\"
    DEV_DESCRIPTION="\"AMT_NIBIRU1 board"\"
    USBD_PID=0x002a  
else
    $(error KGP BUILD SYSTEM ERROR: Project $(PRJ_NAME) unknown, add project description info to /scripts/make/project.mk)	
endif
