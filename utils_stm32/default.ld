/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20020000;    /* end of RAM */

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x400; /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
	FLASH_1(rx)     : ORIGIN = 0x08000000,      LENGTH = 16K    
        FLASH_2(rx)     : ORIGIN = 0x08000000+16k,  LENGTH = 16K    
        FLASH_3(rx)     : ORIGIN = 0x08000000+32k,  LENGTH = 16K    
        FLASH_4(rx)     : ORIGIN = 0x08000000+48k,  LENGTH = 16K    
	FLASH_A(rx)     : ORIGIN = 0x08000000+64k,  LENGTH = (1024K-64K)
	RAM (xrw)       : ORIGIN = 0x20000000,      LENGTH = 128K
	CCMRAM (rw)     : ORIGIN = 0x10000000,      LENGTH = 64K
}

/* Define output sections */
SECTIONS
{
  .flash1_begin (NOLOAD): 
  {
    flash1_begin = .;
  } >FLASH_1

  .flash2_begin (NOLOAD): 
  {
    flash2_begin = .;
  } >FLASH_2

  .flash3_begin (NOLOAD): 
  {
    flash3_begin = .;
  } >FLASH_3

  .flash4_begin (NOLOAD): 
  {
    flash4_begin = .;
  } >FLASH_4

  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    PROVIDE_HIDDEN(__isr_start = .);
    KEEP(*(.isr_vector)) /* Startup code */
    . = __isr_start + 0x1E0;
    KEEP(*(.FLASH_INFO))    
  } >FLASH_1

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH_A

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH_A

  .ARM.extab   : {
	*(.ARM.extab* .gnu.linkonce.armextab.*) 
   } >FLASH_A
   
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH_A

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH_A
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH_A
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH_A

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
 	*(.REBOOT_STATE)
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH_A

  /* CCM-RAM section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
  .ccmram :
  {
    . = ALIGN(4);
    *(.ccmram)
    *(.noinit)
    *(.ccmram*)
    
    . = ALIGN(4);
  } >CCMRAM AT> FLASH_A

  
  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  
  .flash_end (NOLOAD): 
  {
    flash_end = .;
  } >FLASH_A

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}