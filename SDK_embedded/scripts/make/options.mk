# ��������� �������� ��������� ��������
ROOT_DIR=$(SRC_DIR)/..
OUT_DIR=$(ROOT_DIR)/out
LIB_DIR=$(ROOT_DIR)/lib
DOC_DIR=$(ROOT_DIR)/doc
PC_DIR=$(ROOT_DIR)/pc
SCRIPT_DIR=$(ROOT_DIR)/scripts

#функция вычисления GNUmakefile_XXX
make_file_from_sdk=$(SDK_DIR)/scripts/make/libs/stm32/GNUmakefile_$(1)

ifndef TOOLS_VARIIANT 
		TOOLS_VARIIANT = arm-kgp-eabi
endif
#-------------------------------------------------------------------
#	���������� ������� ������ �� ���������
ifeq ($(origin MAKE_JOBS), undefined)
	MAKE_JOBS=12
endif
#-------------------------------------------------------------------
#      ���������� ���������� � ���� ������ make
ifeq ($(origin MAKE_DIR_TARGET_SEPARATOR), undefined)
	MAKE_DIR_TARGET_SEPARATOR=/
endif


MAKE_DIR=   $(word 1,$(subst $(MAKE_DIR_TARGET_SEPARATOR), ,$@))
MAKE_TARGET=$(word 2,$(subst $(MAKE_DIR_TARGET_SEPARATOR), ,$@))


ifeq ($(origin MAKE_DIR_TARGET_SEPARATOR), undefined)
	MAKE_DIR_TARGET_SEPARATOR=/
endif
#-------------------------------------------------------------------
# ��������� ������� ������� �������
ifeq ($(origin LIB_SRC_DIR), undefined)
  LIB_SRC_DIR=.
endif

# find a memutz utilite
#MEM_USAGE = $(word 1, $(notdir $(filter-out $(MEMUTZ): $(SIZE):, $(shell whereis $(MEMUTZ) $(SIZE)))))
MEM_USAGE = memutz
ifeq ($(MEM_USAGE),$(MEMUTZ))
	MEM_USAGE_OPT = $(FLASH_SIZE) $(SRAM_SIZE) $(D1_AXI_SRAM_SIZE)
endif

#-------------------------------------------------------------------
#вычисление поддиректорий 
# если не SUBDIR_WALKER, то поддиректории вычисляются автоматически
ifeq ($(origin get_subdir_walker), undefined)
    SUBDIR_WALKER_MASK=	/*.
    ifeq ($(origin NO_SUBDIR_WALKER), undefined)
	    SUBDIR_WALKER_MASK+=	/*/*.	\
			            /*/*/*.	\
			            /*/*/*/*.
    endif
else
   SUBDIR_WALKER_MASK = $(addprefix /,$(addsuffix /*.,$(call get_subdir_walker,$(STM32_CHIP_FAMILY_CODE)))) 
endif

#-------------------------------------------------------------------
ifndef LIBNAME
	ifndef APPNAME 
		APPNAME = image
	endif
endif

# ���������� ����� ������
ifdef LIBNAME
	FULLNAME = $(LIB_DIR)/$(LIBNAME).a
endif

ifdef APPNAME
	FULLNAME = $(OUT_DIR)/$(APPNAME).elf
	IHEXNAME = $(OUT_DIR)/$(APPNAME).ihex
endif
#-------------------------------------------------------------------
# memory pools defenition

# ccm sram memory  
ifdef CCM_SRAM_POOL_SIZE
    MEM_POOLS_DEFS += -DCCM_SRAM_POOL_SIZE=$(CCM_SRAM_POOL_SIZE)
endif
    
# internal sram memory  
ifdef INTERNAL_SRAM_POOL_SIZE
    MEM_POOLS_DEFS += -DINTERNAL_SRAM_POOL_SIZE=$(INTERNAL_SRAM_POOL_SIZE)
endif

# external memory bank 
	ifdef EXT_MEM_BANK0_SIZE
		ifdef EXT_MEM_BANK0_POOL_SIZE
			MEM_POOLS_DEFS +=-DEXT_MEM_BANK0_POOL_SIZE=$(EXT_MEM_BANK0_POOL_SIZE)
		endif
	endif
	
	ifdef EXT_MEM_BANK1_SIZE
		ifdef EXT_MEM_BANK1_POOL_SIZE
			MEM_POOLS_DEFS +=-DEXT_MEM_BANK1_POOL_SIZE=$(EXT_MEM_BANK1_POOL_SIZE)
		endif
	endif	

	ifdef EXT_MEM_BANK2_SIZE
		ifdef EXT_MEM_BANK2_POOL_SIZE
			MEM_POOLS_DEFS +=-DEXT_MEM_BANK2_POOL_SIZE=$(EXT_MEM_BANK2_POOL_SIZE)
		endif
	endif

	ifdef EXT_MEM_BANK3_SIZE
		ifdef EXT_MEM_BANK3_POOL_SIZE
			MEM_POOLS_DEFS +=-DEXT_MEM_BANK3_POOL_SIZE=$(EXT_MEM_BANK3_POOL_SIZE)
		endif
	endif
#-------------------------------------------------------------------
ifndef LD_SCRIPT
	# ��������� m4 ������� ��������� ld ������� �� ���������

	# ��������� ����� �����. 
	ifndef ENTRY_SYMBOL
		ENTRY_SYMBOL = irq_vector_table
	endif	

	ifndef LD_SCRIPT_M4
		ifeq ($(origin LINK_IN_RAM), undefined)
			LD_SCRIPT_M4 = $(SDK_DIR)/scripts/ld/ld_flash.m4
		else
			LD_SCRIPT_M4 = $(SDK_DIR)/scripts/ld/ld_ram.m4
		endif
	endif
	
	# смещение секции кода относительно начала начала адресного пространсва флеша
	# используется для связки загрузчика и приложения (размещение приложения)
	# в свободной от кода згрузчика части флеша.
	ifndef FLASH_TEXT_SECTION_OFFSET    
	    FLASH_TEXT_SECTION_OFFSET = 0x00000000
	endif

	ifndef STACK_END_OFFSET
		STACK_END_OFFSET = 0x00000000
	endif

	#���������� ��������� ������ m4 ��� ��������� ld �������
	LDGENFLAGS+= -DENTRY_SYMBOL=$(ENTRY_SYMBOL)		\
			-DFLASH_ORIGIN=$(FLASH_ORIGIN)		\
			-DFLASH_TEXT_SECTION_OFFSET=$(FLASH_TEXT_SECTION_OFFSET) \
			-DFLASH_SIZE=$(FLASH_SIZE)		\
			-DSTACK_END_OFFSET=$(STACK_END_OFFSET)
			
	# SRAM on stm32f4
	ifdef SRAM_SIZE
		LDGENFLAGS+= -DSRAM_ORIGIN=$(SRAM_ORIGIN)	-DSRAM_SIZE=$(SRAM_SIZE)
	endif		
			
	# CCM SRAM on stm32f4
	ifdef CCM_SRAM_SIZE
		LDGENFLAGS+= -DCCM_SRAM_ORIGIN=$(CCM_SRAM_ORIGIN)	-DCCM_SRAM_SIZE=$(CCM_SRAM_SIZE)
	endif
	
	# ITCM SRAM on stm32f7
	ifdef ITCM_SRAM_SIZE
		LDGENFLAGS+= -DITCM_SRAM_ORIGIN=$(ITCM_SRAM_ORIGIN)	-DITCM_SRAM_SIZE=$(ITCM_SRAM_SIZE)
	endif
	
	# DTCM RAM on stm32f7
	ifdef DTCM_SRAM_SIZE
		LDGENFLAGS+= -DDTCM_SRAM_ORIGIN=$(DTCM_SRAM_ORIGIN)	-DDTCM_SRAM_SIZE=$(DTCM_SRAM_SIZE)
	endif

	# D1_ITCM RAM on stm32h7
	ifdef D1_ITCM_SRAM_SIZE
		LDGENFLAGS+= -DD1_ITCM_SRAM_ORIGIN=$(D1_ITCM_SRAM_ORIGIN) -DD1_ITCM_SRAM_SIZE=$(D1_ITCM_SRAM_SIZE)
	endif
	
	# D1_DTCM RAM on stm32h7
	ifdef D1_DTCM_SRAM_SIZE
		LDGENFLAGS+= -DD1_DTCM_SRAM_ORIGIN=$(D1_DTCM_SRAM_ORIGIN) -DD1_DTCM_SRAM_SIZE=$(D1_DTCM_SRAM_SIZE)
	endif

	# D1_AXI_SRAM on stm32h7
	ifdef D1_AXI_SRAM_SIZE
		LDGENFLAGS+= -DD1_AXI_SRAM_ORIGIN=$(D1_AXI_SRAM_ORIGIN) -DD1_AXI_SRAM_SIZE=$(D1_AXI_SRAM_SIZE)
	endif
	
	# D2_SRAM on stm32h7
	ifdef D2_SRAM_SIZE
		LDGENFLAGS+= -DD2_SRAM_ORIGIN=$(D2_SRAM_ORIGIN) -DD2_SRAM_SIZE=$(D2_SRAM_SIZE)
	endif
	
	#  DD3_SRAM on stm32h7
	ifdef D3_SRAM_SIZE
		LDGENFLAGS+= -DD3_SRAM_ORIGIN=$(D3_SRAM_ORIGIN) -DD3_SRAM_SIZE=$(D3_SRAM_SIZE)
	endif
	
	# D3_BACKUP_SRAM on stm32h7
	ifdef D3_BACKUP_SRAM_SIZE
		LDGENFLAGS+= -DD3_BACKUP_SRAM_ORIGIN=$(D3_BACKUP_SRAM_ORIGIN) -DD3_BACKUP_SRAM_SIZE=$(D3_BACKUP_SRAM_SIZE)
	endif
		
	# eeprom emulated sector 'a'  is a embedded FLASH sector #1, embedded FLASH sector #0 is a 'reset_vector' storage
	ifdef EEPROM_FLASH_SECTOR_A
		LDGENFLAGS+= -DEEPROM_FLASH_SECTOR_A -DEEPROM_FLASH_SECTOR_A_OFFSET=$(EEPROM_FLASH_SECTOR_A_OFFSET) -DEEPROM_FLASH_SECTOR_A_SIZE=$(EEPROM_FLASH_SECTOR_A_SIZE) 
		# inform application for EEPROM_16K_FLASH_SECTOR_A usage
		APP_DEFS+= -D__EEPROM_FLASH_SECTOR_A__
	endif 

	# eeprom emulated sector 'b'  is a embedded FLASH sector #2
	ifdef EEPROM_FLASH_SECTOR_B
		LDGENFLAGS+= -DEEPROM_FLASH_SECTOR_B -DEEPROM_FLASH_SECTOR_B_OFFSET=$(EEPROM_FLASH_SECTOR_B_OFFSET) -DEEPROM_FLASH_SECTOR_B_SIZE=$(EEPROM_FLASH_SECTOR_B_SIZE)
		# inform application for EEPROM_FLASH_SECTOR_B usage
		APP_DEFS+= -D__EEPROM_FLASH_SECTOR_B__
	endif

	# external memory bank 
	ifdef EXT_MEM_BANK0_SIZE
		ifndef EXT_MEM_BANK0_ORIGIN
			EXT_MEM_BANK0_ORIGIN = 0xFFFFFFFF
		endif
		LDGENFLAGS+= -DEXT_MEM_BANK0_ORIGIN=$(EXT_MEM_BANK0_ORIGIN) -DEXT_MEM_BANK0_SIZE=$(EXT_MEM_BANK0_SIZE)
	endif
	
	ifdef EXT_MEM_BANK1_SIZE
		ifndef EXT_MEM_BANK1_ORIGIN
			EXT_MEM_BANK1_ORIGIN = 0xFFFFFFFF
		endif
		LDGENFLAGS+= -DEXT_MEM_BANK1_ORIGIN=$(EXT_MEM_BANK1_ORIGIN) -DEXT_MEM_BANK1_SIZE=$(EXT_MEM_BANK1_SIZE)
	endif
	
	ifdef EXT_MEM_BANK2_SIZE
		ifndef EXT_MEM_BANK2_ORIGIN
			EXT_MEM_BANK2_ORIGIN = 0xFFFFFFFF
		endif
		LDGENFLAGS+= -DEXT_MEM_BANK2_ORIGIN=$(EXT_MEM_BANK2_ORIGIN) -DEXT_MEM_BANK2_SIZE=$(EXT_MEM_BANK2_SIZE)
	endif
	
	ifdef EXT_MEM_BANK3_SIZE
		ifndef EXT_MEM_BANK3_ORIGIN
			EXT_MEM_BANK3_ORIGIN = 0xFFFFFFFF
		endif
		LDGENFLAGS+= -DEXT_MEM_BANK3_ORIGIN=$(EXT_MEM_BANK3_ORIGIN) -DEXT_MEM_BANK3_SIZE=$(EXT_MEM_BANK3_SIZE)
	endif	

	#��� ����� ������� ld � ����� � ��� ��������� 
	LD_SCRIPT=$(SCRIPT_DIR)/$(PRJ_NAME).ld
endif
	
LD_SCRIPT_OPT=-T $(LD_SCRIPT)

#----- hardware auto defs ----------------------------------------
HARDWARE_DEFS+= -DF_OSC=$(F_OCS) -DOSC_TYPE=$(OSC_TYPE) -DOSC_STATE=$(OSC_STATE)
ifneq ($(origin PLL_N), undefined)
   PLL_CONFIG=4
   HARDWARE_DEFS+=-DPLL_M=$(PLL_M) -DPLL_N=$(PLL_N) -DPLL_Q=$(PLL_Q) -DFLASH_LATENCY=$(FLASH_LATENCY)
else
   ifndef PLL_CONFIG
       PLL_CONFIG=0
   endif
endif

HARDWARE_DEFS+=-DPLL_CONFIG=$(PLL_CONFIG)

#----- CRT auto defines -------------------------------------------------
ifeq ($(origin VEC_TABLE_OFFSET),undefined)
	CRT_DEFS+= -DVEC_TABLE_OFFSET=0x08000000
else
    CRT_DEFS+= -DVEC_TABLE_OFFSET=$(VEC_TABLE_OFFSET)	
endif

ifneq ($(origin DELAY_FOR_GDB), undefined)
	CRT_DEFS+= -DDELAY_FOR_GDB=$(DELAY_FOR_GDB)
endif

ifneq ($(origin USE_FREERTOS), undefined)
	CRT_DEFS+= -D__USE_FREERTOS__
endif

ifneq ($(origin CCM_RAM_SIZE), undefined)
	CRT_DEFS+= -D__CCM_RAM__
endif

ifneq ($(origin ITCM_RAM_SIZE), undefined)
	CRT_DEFS+= -D__ITCM_RAM__
endif

ifneq ($(origin DTCM_RAM_SIZE), undefined)
	CRT_DEFS+= -D__DTCM_RAM__
endif

ifneq ($(origin EXT_MEM_BANK0_SIZE), undefined)
	CRT_DEFS+= -D__EXT_MEM_BANK0__
endif

ifneq ($(origin EXT_MEM_BANK1_SIZE), undefined)
	CRT_DEFS+= -D__EXT_MEM_BANK1__
endif

ifneq ($(origin EXT_MEM_BANK2_SIZE), undefined)
	CRT_DEFS+= -D__EXT_MEM_BANK2__
endif

ifneq ($(origin EXT_MEM_BANK3_SIZE), undefined)
	CRT_DEFS+= -D__EXT_MEM_BANK3__
endif

#------application auto defs -------------------------------------

ifneq ($(origin USE_FREERTOS), undefined)
	APP_DEFS+= -D__USE_FREERTOS__
endif

ifneq ($(origin USE_REENTRANT), undefined)
    APP_DEFS+= -D__USE_REENTRANT__
endif

ifndef DEV_DESCRIPTION
	DEV_DESCRIPTION="\"unknown device"\"
endif
APP_DEFS+= -DDEV_DESCRIPTION=$(DEV_DESCRIPTION)

ifndef PROJECT_DESCRIPTION
	PROJECT_DESCRIPTION="\"unknown project"\" 
endif
APP_DEFS+= -DPROJECT_DESCRIPTION=$(PROJECT_DESCRIPTION)




#-----------------------------------------------------------------
# �������� ������
FW_BUILD_DATE_STR="\"$(shell date +%Y%m%d:%H:%M:%S)"\"

FW_BUILD_DATE=$(shell date +%Y%m%d)
FW_BUILD_TIME=$(shell date +%H%M%S)

PKG_NAME	= $(LIBNAME)$(PRJNAME)

# вычислене пути к LTO плагину
#LTO_PLUGIN=/opt/arm-kgp-eabi/libexec/gcc/arm-kgp-eabi/$(shell $(CC) -dumpversion )/liblto_plugin.so
#BU_PLUGIN=--plugin $(LTO_PLUGIN)
#
# в текужей реализаци неиспользуется, т.к.  вызываются враперы gcc-ar/gcc-nm/gcc-ranlib


# ����� ������������
#ifndef ARFLAGS
	ARFLAGS = -rcs 
#endif

ifndef RLFLAGS
	RLFLAGS = -t 
endif

# ��������� �������� � ������� Intel HEX
ifndef CPFLAGS_HEX
	CPFLAGS_HEX = --strip-all  -O ihex
endif

# ��������� �������� � ������� raw binary
ifndef CPFLAGS_RAW_BIN
	CPFLAGS_RAW_BIN = --strip-all  -O binary
endif

ifndef CPFLAGSBINDATA
	CPFLAGSBINDATA = -I binary -O elf32-littlearm  -B arm --rename-section .data=.rodata
endif

# ��������� �����
ifndef ODFLAGS_DUMP
	ODFLAGS_DUMP	= -x --syms
endif

# ��������� ��������
ifndef ODFLAGS_LSS
	ODFLAGS_LSS	= --disassemble --source --demangle
endif

ifndef NMFLAGS_SYMS
	NMFLAGS_LSS	= --demangle --print-size --reverse-sort --size-sort
endif

# general compilation options -----------------------------------------------
ifndef ASM_LST_FLAGS
	ASM_LST_FLAGS=-adhlns=$@.lst $(ASM_LST_EXT_FLAGS)
endif

# DEPENDENSIS ----------------------------------------------------------------
ifndef DEP_FLAGS
	DEP_FLAGS=-Wp,-M,-MP,-MT,$@,-MF,.dep/$(@F).dep $(DEP_EXT_FLAGS)
endif

# WARNINGS -------------------------------------------------------------------
ifndef WARN_FLAGS
	WARN_FLAGS=-W -Wall -Wno-unused-parameter $(WARN_EXT_FLAGS)
endif

# DFU operation --------------------------------------------------------------
ifndef DFUFLAGS_WRITE_FLASH
	DFUFLAGS_WRITE_FLASH=--device $(DFU_USB_VIDPID) --alt 0 --dfuse-address $(FLASH_ORIGIN) -D 
endif

ifndef DFUFLAGS_READ_FLASH
	DFUFLAGS_READ_FLASH=--device $(DFU_USB_VIDPID) --alt 0 --dfuse-address $(FLASH_ORIGIN):$(FLASH_SIZE)  -U
endif

# OPTIMIZATION ---------------------------------------------------------------
ifndef OPT_LEVEL
	OPT_LEVEL=-Ofast
endif

ifndef OPT_FLAGS
	OPT_FLAGS=$(OPT_LEVEL) -ffunction-sections -fdata-sections -fgraphite -funroll-loops
endif

#LTO optimization
ifdef OPT_LTO
	OPT_FLAGS+=-flto=$(OPT_LTO) -ffat-lto-objects
        # 
        #-ffat-lto-objects  -flto-odr-type-merging
endif

#add user defined optimization flags
OPT_FLAGS+=$(OPT_EXT_FLAGS)

# DEBUG ----------------------------------------------------------------------
ifndef DBG_FLAGS
	DBG_FLAGS=  -gdwarf-4 -g3 -gno-strict-dwarf -fvar-tracking-assignments -fverbose-asm $(DBG_EXT_FLAGS)
#
#
endif

# ASM OPT OUTPUT -------------------------------------------------------------
ifndef HL_TO_ASM_FLAGS
	HL_TO_ASM_FLAGS=-Wa,$(ASM_LST_FLAGS) $(HL_TO_ASM_EXT_FLAGS)
endif


#	LANGUAGES_FLAGS+= -fsingle-precision-constant !!! unused key becous not compiling c++ headers what use double constant default
ifeq ($(CPU),CORTEX_M7)
    ifeq ($(FPU_TYPE),double)
       CPU_FLAGS= -mthumb -march=armv7e-m+fp.dp -mfloat-abi=hard -mcpu=cortex-m7 -mfpu=fpv5-d16
    else ifeq ($(FPU_TYPE),single)
       CPU_FLAGS= -mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mfpu=fpv5-sp-d16
    else
       $(error CORTEX_M7 requare defined FPU_TYPE as double or single for $(CHIP_TARGET))
    endif
else ifeq ($(CPU),CORTEX_M4F)
    CPU_FLAGS=   -mthumb -march=armv7e-m+fp -mfloat-abi=hard -mcpu=cortex-m4
else ifeq ($(CPU),CORTEX_M3)
	CPU_FLAGS=   -mthumb -march=armv7-m -mfloat-abi=soft -mcpu=cortex-m3
else ifeq ($(CPU),CORTEX_M0PLUS)	
	CPU_FLAGS=   -mthumb -march=armv6s-m -mfloat-abi=soft -mcpu=cortex-m0plus
else ifeq ($(CPU),CORTEX_M0)	
	CPU_FLAGS=   -mthumb -march=armv6s-m -mfloat-abi=soft -mcpu=cortex-m0
endif
CPU_FLAGS+=$(CPU_EXT_FLAGS)

COMMON_PROJECT_INCLIDE_PATH=   \
                   -I./ \
                   -I$(SRC_DIR)/include \
                   -I$(SDK_DIR)/libs/common \
                   -I$(SDK_STM32_COMMON_DIR) \
			       -I$(SDK_STM32_DIR)  \
			       

COMPILE_FLAGS+=		$(DEFS) \
                    $(DBG_FLAGS)  \
					$(CPU_FLAGS) \
					$(OPT_FLAGS) \
					$(DEP_FLAGS) \
				 	$(WARN_FLAGS) \
				 	$(COMMON_PROJECT_INCLIDE_PATH) \
				 	$(HL_TO_ASM_EXT_FLAGS) \
				 	$(COMPILE_EXT_FLAGS) \
				 	$(LANGUAGES_FLAGS)

# C STANDARD ---------------------------------------------------------------
ifndef CSTD_FLAGS
	CSTD_FLAGS=-std=c18 -Wno-error=implicit-function-declaration -Wno-error=int-conversion -Wno-error=incompatible-pointer-types
	#gnu99,c11
endif

# C++ STANDARD ---------------------------------------------------------------
ifndef CPPSTD_FLAGS
	CPPSTD_FLAGS=-std=c++2a
endif

# FORTRAN STANDARD ---------------------------------------------------------------
ifndef FSTD_FLAGS
	FSTD_FLAGS=-ffree-form
endif

#--------------------------------------------------------------------------------
CFLAGS+=	$(CSTD_FLAGS) 	 $(COMPILE_FLAGS)	$(C_EXT_FLAGS)
FFLAGS+=	$(FSTD_FLAGS) 	 $(COMPILE_FLAGS)	$(F_EXT_FLAGS)
CXXFLAGS+=	$(CPPSTD_FLAGS)  $(COMPILE_FLAGS)	-fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-rtti $(CPP_EXT_FLAGS)
ASFLAGS+=	$(CPU_FLAGS)	 $(COMPILE_DEBUG_FLAGS) -mapcs-32 $(ASM_LST_FLAGS) $(CRT_CONFIG) $(AS_EXT_FLAGS)

#LINK FLAGS ----------------------------------------------------------------------
LINK_FLAGS+= \
             -fuse-linker-plugin \
             -nostartfiles \
             -Wl,-gc-sections \
             -Wl,--defsym,__firmware_build_date__=$(FW_BUILD_DATE),--defsym,__firmware_build_time__=$(FW_BUILD_TIME) \
             $(CPU_FLAGS) \
             $(OPT_FLAGS) \
             -L$(LIB_DIR) \
             $(LINK_EXT_FLAGS)
# GOLD сообщает ошибку переполения секций             
# -Wl,$(LD_PLUGIN) - не требуется, драйвер линкеру автоматом подгружает liblto_plugin.so, если воткнуть ключ то ссобщает о повторной загрузке плагина
# -fuse-ld=gold -nodefaultlibs -nostdlib
#-Wl,-debug,-plugin-opt=-debug -save-temps
#-fwhole-program 
