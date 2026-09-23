OUTPUT_FORMAT ("elf32-littlearm")
ENTRY(irq_vector_table)
MEMORY
{
  ifdef(`CCM_SRAM_SIZE', `ccm_sram (rwx)	: ORIGIN = CCM_SRAM_ORIGIN,   LENGTH = CCM_SRAM_SIZE', `' )
  
  ifdef(`ITCM_SRAM_SIZE', `itcm_sram (rwx): ORIGIN = ITCM_SRAM_ORIGIN,   LENGTH = ITCM_SRAM_SIZE', `' )
  
  ifdef(`DTCM_SRAM_SIZE', `dtcm_sram (rw): ORIGIN = DTCM_SRAM_ORIGIN,   LENGTH = DTCM_SRAM_SIZE', `' )
  
  ifdef(`SRAM_SIZE', `sram (rwx): ORIGIN = SRAM_ORIGIN,   LENGTH = SRAM_SIZE', `' )

  
  ifdef(`D1_AXI_SRAM_SIZE', `d1_axi_sram (rwx): ORIGIN = D1_AXI_SRAM_ORIGIN,   LENGTH = D1_AXI_SRAM_SIZE', `' )
  ifdef(`D1_AHB_SRAM_SIZE', `d1_ahb_sram (rwx): ORIGIN = D1_AHB_SRAM_ORIGIN,   LENGTH = D1_AHB_SRAM_SIZE', `' )
  
  
  
    
  ifdef(`EXT_MEM_BANK0_SIZE', `ext_mem_bank0  (rwx)  : ORIGIN = EXT_MEM_BANK0_ORIGIN ,   LENGTH = EXT_MEM_BANK0_SIZE', `' )
  ifdef(`EXT_MEM_BANK1_SIZE', `ext_mem_bank1  (rwx)  : ORIGIN = EXT_MEM_BANK1_ORIGIN ,   LENGTH = EXT_MEM_BANK1_SIZE', `' )
  ifdef(`EXT_MEM_BANK2_SIZE', `ext_mem_bank2  (rwx)  : ORIGIN = EXT_MEM_BANK2_ORIGIN ,   LENGTH = EXT_MEM_BANK2_SIZE', `' )
  ifdef(`EXT_MEM_BANK3_SIZE', `ext_mem_bank3  (rwx)  : ORIGIN = EXT_MEM_BANK3_ORIGIN ,   LENGTH = EXT_MEM_BANK3_SIZE', `' )

  flash  (rx)  : ORIGIN = FLASH_ORIGIN + FLASH_TEXT_SECTION_OFFSET, LENGTH = FLASH_SIZE - FLASH_TEXT_SECTION_OFFSET
}

ifdef(`SRAM_SIZE', 
      `__sram_start__ = SRAM_ORIGIN ;
       __sram_end__ = __sram_start__ + SRAM_SIZE;
       __stack_end__ = ORIGIN(sram) + LENGTH(sram) - 4 - STACK_END_OFFSET ;
      ',
      `' )
      
ifdef(`D1_AXI_SRAM_SIZE', 
      `__sram_start__ = D1_AXI_SRAM_ORIGIN ;
       __sram_end__ = __sram_start__ + D1_AXI_SRAM_SIZE;
       __stack_end__ = ORIGIN(d1_axi_sram) + LENGTH(d1_axi_sram) - 4 - STACK_END_OFFSET ;
      ',
      `' )

__stack_end__ = __stack_end__ & 0xfffffff8 ; /* выравнивание стека на границу 8 байт */


ifdef(`CCM_SRAM_SIZE', 
      `__ccm_start__ = CCM_SRAM_ORIGIN ;
       __ccm_end__ = __ccm_start__ + CCM_SRAM_SIZE ;
      ',
      `' )
      
ifdef(`ITCM_SRAM_SIZE', 
      `__itcm_start__ = ITCM_SRAM_ORIGIN ;
       __itcm_end__ = __itcm_start__ + ITCM_SRAM_SIZE ;
      ',
      `' )

ifdef(`DTCM_SRAM_SIZE', 
      `__dtcm_start__ = DTCM_SRAM_ORIGIN ;
       __dtcm_end__ = __dtcm_start__ + DTCM_SRAM_SIZE ;
      ',
      `' )
      
__flash_start__ = FLASH_ORIGIN;
__flash_end__ = __flash_start__ + FLASH_SIZE ;      


/* now define the output sections  */
SECTIONS 
{
	. = 0;	
								/* set location counter to address zero  */
	.text :								
	{
		__image_start__  = . ;
		__vec_start__ = . ;
		KEEP(*(.flash_irq_vec_table*))
		KEEP(*(.flash_irq_vec_table))
		__vec_end__ = . ;

              ifdef(`EEPROM_FLASH_SECTOR_A',  /* STM32 FLASH_SECTOR_A*/
	      . = EEPROM_FLASH_SECTOR_A_OFFSET ;
               __eeprom_sector_a_start__ = . ;
              KEEP(*(SORT(.eeprom_sector_a*)))
	      . = EEPROM_FLASH_SECTOR_A_OFFSET + EEPROM_FLASH_SECTOR_A_SIZE ;
	      __eeprom_sector_a_end__ = . ;
              )


              ifdef(`EEPROM_FLASH_SECTOR_B',  /* STM32 FLASH_SECTOR_B*/
	      . = EEPROM_FLASH_SECTOR_B_OFFSET ;
               __eeprom_sector_b_start__ = . ;
              KEEP(*(SORT(.eeprom_sector_b*)))
	      . = EEPROM_FLASH_SECTOR_B_OFFSET + EEPROM_FLASH_SECTOR_B_SIZE ;
	      __eeprom_sector_b_end__ = . ;
              )
              
		__sunset_start__ = . ;
                KEEP(*(.sunset*))
		__sunset_end__ = . ;


		
		__code_start__ = . ;
		
		__preinit_array_start__ = . ;
		KEEP(*(SORT(.preinit_array*)))
		KEEP(*(.preinit_array))
		__preinit_array_end__ = . ;
		__init_array_start__  = . ;
		KEEP(*(SORT(.init_array*)))
		KEEP(*(.init_array))
		__init_array_end__    = . ;
		__fini_array_start__ = . ;
		KEEP(*(SORT(.fini_array*)))
		KEEP(*(.fini_array))
		__fini_array_end__   = . ;
	
		__privileged_functions_start__ = . ;
		*(.privileged_functions*)
		__privileged_functions_end__ = . ;
		
		__text_start__ = . ;
		*(.text*)						/* all .text sections (code)  */
		*(.text)
		__text_end__ = . ;
		__rodata_start__ = .;
		*(.rodata*)						/* all .rodata* sections (constants, strings, etc.)  */
		__rodata_end__ = .;
		__const_data_start__ = . ;
		*(.const_data*)					/* const data tables */
		__const_data_end__ = . ;
		*(.glue_7)						/* all .glue_7 sections  (no idea what these are) */
		*(.glue_7t)						/* all .glue_7t sections (no idea what these are) */
		*(.gnu*)
		*(.gcc*)
		. = ALIGN(16) ;
		__code_end__ = . ;

	} >flash

__data_load_start__ = __code_end__ ;

	ifdef(`CCM_SRAM_SIZE', 
	 	 `	__ccm_data_load_start__ = __data_load_start__ ;
	        .ccm_data :								/* collect all initialized .data sections that go into RAM  */ 
	        {
		       . = ALIGN(4) ;
		       __ccm_data_start__ = . ;
		       *(.ccm_data*) 						/* all .ccm_data sections  */
		       . = ALIGN(4);
		       __ccm_data_end__ = .;							/* define a global symbol marking the end of the .data section  */
	        } >ccm_sram AT >flash					     /* put all the above into RAM (but load the LMA copy into FLASH) */
	        __ccm_data_load_end__ = __ccm_data_load_start__ +  SIZEOF(.ccm_data) ;
	        __data_load_start__ = __ccm_data_load_end__ ;
	     ',
	     `'      
         )
         
 	ifdef(`ITCM_SRAM_SIZE', 
	 	 `	__itcm_data_load_start__ = __data_load_start__ ;
	        .itcm_data :								/* collect all initialized .data sections that go into RAM  */ 
	        {
		       . = ALIGN(4) ;
		       __itcm_data_start__ = . ;
		       *(.itcm_data*) 						/* all .itcm_data sections  */
		       . = ALIGN(4);
		       __itcm_data_end__ = .;							/* define a global symbol marking the end of the .data section  */
	        } >itcm_sram AT >flash					     /* put all the above into RAM (but load the LMA copy into FLASH) */
	        __itcm_data_load_end__ = __itcm_data_load_start__ +  SIZEOF(.itcm_data) ;
	        __data_load_start__ = __itcm_data_load_end__ ;
	     ',
	     `'
         )        
  
  	ifdef(`DTCM_SRAM_SIZE', 
	 	 `	__dtcm_data_load_start__ = __data_load_start__ ;
	        .dtcm_data :								/* collect all initialized .data sections that go into RAM  */ 
	        {
		       . = ALIGN(4) ;
		       __dtcm_data_start__ = . ;
		       *(.dtcm_data*) 						/* all .dtcm_data sections  */
		       . = ALIGN(4);
		       __dtcm_data_end__ = .;							/* define a global symbol marking the end of the .data section  */
	        } >dtcm_sram AT >flash					     /* put all the above into RAM (but load the LMA copy into FLASH) */
	        __dtcm_data_load_end__ = __dtcm_data_load_start__ +  SIZEOF(.dtcm_data) ;
	        __data_load_start__ = __dtcm_data_load_end__ ;
	     ',
	     `'
         )  
  
  
  
	
	.data :								/* collect all initialized .data sections that go into RAM  */ 
	{
		. = ALIGN(4) ;
		__data_start__ = . ;
		
		__ramfunc_start__ = .;
		*(.ramfunc*)
		__ramfunc_end__ = . ;
		. = ALIGN(4) ;  
		
		*(.data*) 						/* all .data sections  */
		*(.data)
		. = ALIGN(4);
		__data_end__ = .;							/* define a global symbol marking the end of the .data section  */
	}   /* put all the above into RAM (but load the LMA copy into FLASH) */
	ifdef(`SRAM_SIZE', ` > sram AT > flash',`') 
	ifdef(`D1_AXI_SRAM_SIZE', `> d1_axi_sram AT > flash',`')
			     
	__data_load_end__ = __data_load_start__ +  SIZEOF(.data) ;	
	
	. = ALIGN(__data_load_end__ ,  4) ;  
	__image_end__ = .;
	
	

	
   ifdef(`CCM_SRAM_SIZE', 
	 	 `	.ccm_bss (NOLOAD):
	          {
		        __ccm_privileged_bss_start__ = .;
		        *(ccm_privileged_bss*)
		        __ccm_privileged_bss_end__  = .;

		        __ccm_bss_start__ = . ;     
		        *(.ccm_bss*)
		        __ccm_bss_end__ = .;
	          } >ccm_sram
	     ',
	     `	
	     '
    )
    
   ifdef(`ITCM_SRAM_SIZE', 
	 	 `	.itcm_bss (NOLOAD):
	          {
		        __itcm_privileged_bss_start__ = .;
		        *(.itcm_privileged_bss*)
		        __itcm_privileged_bss_end__  = .;

		        __itcm_bss_start__ = . ;     
		        *(.itcm_bss*)
		        __itcm_bss_end__ = .;
	          } >itcm_sram
	     ',
	     `	
	     '
    )
    
       ifdef(`DTCM_SRAM_SIZE', 
	 	 `	.dtcm_bss (NOLOAD):
	          {
		        __dtcm_privileged_bss_start__ = .;
		        *(.dtcm_privileged_bss*)
		        __dtcm_privileged_bss_end__  = .;

		        __dtcm_bss_start__ = . ;     
		        *(.dtcm_bss*)
		        __dtcm_bss_end__ = .;
	          } >dtcm_sram
	     ',
	     `	
	     '
    )
	
	
	.bss (NOLOAD):								 
	{
		__ram_vec_start__ = .;
		*(.ram_vec_table*)	
		__ram_vec_end__ = .;

		__privileged_data_start__ = .;
		*(.privileged_data*)
		__privileged_data_end__  = .;

		__bss_start__ = . ;     
		*(.bss*)
		*(COMMON)
		__bss_end__ = .;
	} 
	ifdef(`SRAM_SIZE', ` > sram',`') 
	ifdef(`D1_AXI_SRAM_SIZE', `> d1_axi_sram',`')
		
	
	
	
	
	 
	  ifdef(`EXT_MEM_BANK0_SIZE', 
	 	 `/* external memory bank 0 layout  */
   .ext_mem_bank0_bss (NOLOAD):								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank0_bss_start__ = . ;     
		*(.ext_mem_bank0_bss*)
		. = ALIGN(4) ;
		__ext_mem_bank0_bss_end__ = . ;
	}  >ext_mem_bank0
	
	__ext_mem_bank0_data_load_start__ = __data_load_end__ ;
	.ext_mem_bank0_data :								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank0_data_start__ = . ;
		*(.ext_mem_bank0_data*)
		. = ALIGN(4) ;
		__ext_mem_bank0_data_end__ = .;	
	}  >ext_mem_bank0 AT >flash
	__ext_mem_bank0_data_load_end__ = __ext_mem_bank0_data_load_start__ + SIZEOF(.ext_mem_bank0_data) ;
	',
	`	__ext_mem_bank0_data_load_end__ = __data_load_end__  ;'
    ) 
    
    ifdef(`EXT_MEM_BANK1_SIZE', 
	 	 `/* external memory bank 1 layout  */
   .ext_mem_bank1_bss (NOLOAD):								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank1_bss_start__ = . ;     
		*(.ext_mem_bank1_bss*)
		. = ALIGN(4) ;
		__ext_mem_bank1_bss_end__ = . ;
	}  >ext_mem_bank1
	
	__ext_mem_bank1_data_load_start__ = __ext_mem_bank0_data_load_end__ ;
	.ext_mem_bank1_data :								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank1_data_start__ = . ;
		*(.ext_mem_bank1_data*)
		. = ALIGN(4) ;
		__ext_mem_bank1_data_end__ = .;
	}  >ext_mem_bank1 AT >flash
	__ext_mem_bank1_data_load_end__ = __ext_mem_bank1_data_load_start__ + SIZEOF(.ext_mem_bank1_data) ;
	',
	 `	__ext_mem_bank1_data_load_end__ = __ext_mem_bank0_data_load_end__  ;'
    ) 
    
    ifdef(`EXT_MEM_BANK2_SIZE', 
	 	 `/* external memory bank 2 layout  */
   .ext_mem_bank2_bss (NOLOAD):								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank2_bss_start__ = . ;     
		*(.ext_mem_bank2_bss*)
		. = ALIGN(4) ;
		__ext_mem_bank2_bss_end__ = . ;
	}  >ext_mem_bank2
	
	__ext_mem_bank2_data_load_start__ = __ext_mem_bank1_data_load_end__ ;
	.ext_mem_bank2_data :								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank2_data_start__ = . ;
		*(.ext_mem_bank2_data*)
		. = ALIGN(4) ;
		__ext_mem_bank2_data_end__ = .;
	}  >ext_mem_bank2 AT >flash
	__ext_mem_bank2_data_load_end__ = __ext_mem_bank2_data_load_start__ + SIZEOF(.ext_mem_bank2_data) ;
	',
	 `	__ext_mem_bank2_data_load_end__ = __ext_mem_bank1_data_load_end__ ;'
    ) 
	
	ifdef(`EXT_MEM_BANK3_SIZE', 
	 	 `/* external memory bank 3 layout  */
   .ext_mem_bank3_bss (NOLOAD):								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank3_bss_start__ = . ;     
		*(.ext_mem_bank3_bss*)
		. = ALIGN(4) ;
		__ext_mem_bank3_bss_end__ = . ;
	}  >ext_mem_bank3
	
	__ext_mem_bank3_data_load_start__ = __ext_mem_bank2_data_load_end__ ;
	.ext_mem_bank3_data :								 
	{
		. = ALIGN(4) ;
		__ext_mem_bank3_data_start__ = . ;
		*(.ext_mem_bank3_data*)
		. = ALIGN(4) ;
		__ext_mem_bank3_data_end__ = .;
	}  >ext_mem_bank3 AT >flash
	__ext_mem_bank3_data_load_end__ = __ext_mem_bank3_data_load_start__ + SIZEOF(.ext_mem_bank3_data) ;
	',
	 `	__ext_mem_bank3_data_load_end__ = __ext_mem_bank2_data_load_end__ ;'
    ) 

	 . = ALIGN(4) ;
	
	

	 
   /DISCARD/ :
	{
		libc.a ( * )
		libg.a ( * )
		libm.a ( * )
		libgcc.a ( * )
		*(.ARM.exidx*)
		*(.ARM.extab*)
		

	}

  
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end ) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    0 : { *(.debug_macro) }
  .debug_addr     0 : { *(.debug_addr) }
  .debug_types    0 : { *(.debug_types) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*)  *(.gnu.offload_lto_*) *(.gnu.offload_vars*) *(.gnu.offload_funcs*)}
  
  
}
