#-------------------------------------------------------------------
# default tools for project build
CC      = $(TOOLS_VARIIANT)-gcc
CXX     = $(TOOLS_VARIIANT)-g++
FC      = $(TOOLS_VARIIANT)-gfortran
#LD     = $(TOOLS_VARIIANT)-ld.bfd       // не спользуется явно, только через драйвер gcc/g++
#GLD    = $(TOOLS_VARIIANT)-ld.gold     // не спользуется явно, только через драйвер gcc/g++
AR      = $(TOOLS_VARIIANT)-gcc-ar      #врапер arm-kgp-eabi-ar --plugin liblto_plugin.so
AS      = $(TOOLS_VARIIANT)-as
CP      = $(TOOLS_VARIIANT)-objcopy
OD	    = $(TOOLS_VARIIANT)-objdump
SIZE    = $(TOOLS_VARIIANT)-size
SR      = $(TOOLS_VARIIANT)-strip
NM      = $(TOOLS_VARIIANT)-gcc-nm      #врапер arm-kgp-eabi-nm --plugin liblto_plugin.so
GDB     = $(TOOLS_VARIIANT)-gdb
RL	    = $(TOOLS_VARIIANT)-gcc-ranlib  #врапер arm-kgp-eabi-ranlib --plugin liblto_plugin.so
RM	= rm
TAR     = tar
TOUCH   = touch
M4 	= m4
MEMUTZ	= memutz
FIND	= find
GREP	= grep
CD	= cd
PERL	= perl
DFU_UTIL = dfu-util
