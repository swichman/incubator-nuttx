boards/mips/pic32mx/p32mx270f256b_bare README
=====================

This README file discusses the port of NuttX to the "p32mx270f256b_bare" module.


Contents
========

  PIC32MX270F256BD Pin Out
  Toolchains
  Loading NuttX with ICD3
  LED Usage
  UART Usage
  Analog Input
  PIC32MX Configuration Options
  Configurations

PIC32MX250F128D Pin Out
=======================

PIC32MX250F128D 44 pin package.

PIN PIC32 SIGNAL(s)                                  NuttX Function
--- ------------------------------------------------ ----------------------------------
 1  ~MCLR                                            Keep high for operation
--- ------------------------------------------------ ----------------------------------
 2  PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0 N/A
--- ------------------------------------------------ ----------------------------------
 3  PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1       N/A
--- ------------------------------------------------ ----------------------------------
 4  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0        PGED1
--- ------------------------------------------------ ----------------------------------
 5  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1       PGEC1
--- ------------------------------------------------ ----------------------------------
 6  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2        U1RX
--- ------------------------------------------------ ----------------------------------
 7  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3          U1TX
--- ------------------------------------------------ ----------------------------------
 8  VSS                                              VSS
--- ------------------------------------------------ ----------------------------------
 9  OSC1/CLKI/RPA2/RA2                               N/A
--- ------------------------------------------------ ----------------------------------
10  OSC2/CLKO/RPA3/PMA0/RA3                          N/A
--- ------------------------------------------------ ----------------------------------
11  SOSCI/RPB4/RB4                                   N/A
--- ------------------------------------------------ ----------------------------------
12  SOSCO/RPA4/T1CK/CTED9/PMA1/RA4                   N/A
--- ------------------------------------------------ ----------------------------------
13  VDD                                              VDD
--- ------------------------------------------------ ----------------------------------
14  TMS/RPB5/USBID/RB5                               N/A
--- ------------------------------------------------ ----------------------------------
15  VBUS                                             VBUS
--- ------------------------------------------------ ----------------------------------
16  TDI/RPB7/CTED3/PMD5/INT0/RB7                     LED0
--- ------------------------------------------------ ----------------------------------
17  TCK/RPB8/SCL1/CTED10/PMD4/RB8                    LED1
--- ------------------------------------------------ ----------------------------------
18  TDO/RPB9/SDA1/CTED4/PMD3/RB9                     N/A
--- ------------------------------------------------ ----------------------------------
19  VSS                                              VSS
--- ------------------------------------------------ ----------------------------------
20  VCAP                                             VCAP
--- ------------------------------------------------ ----------------------------------
21  PGED2/RPB10/D+/CTED11/RB10                       U2RX
--- ------------------------------------------------ ----------------------------------
22  PGEC2/RPB11/D-/RB11                              U2TX
--- ------------------------------------------------ ----------------------------------
23  VUSB3V3                                          VUSB3V3
--- ------------------------------------------------ ----------------------------------
24  AN11/RPB13/CTPLS/PMRD/RB13                       N/A
--- ------------------------------------------------ ----------------------------------
25  CVREFOUT/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 N/A
--- ------------------------------------------------ ----------------------------------
26  AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15            N/A
--- ------------------------------------------------ ----------------------------------
27  AVSS                                             AVSS
--- ------------------------------------------------ ----------------------------------
28  AVDD                                             AVDD
--- ------------------------------------------------ ----------------------------------

Additional signals available via Peripheral Pin Selections (PPS)
----------------------------------------------------------------

  REFCLKI  Reference Input Clock
  REFCLKO  Reference Output Clock
  IC1      Capture Inputs 1
  IC2      Capture Inputs 2
  IC3      Capture Inputs 3
  IC4      Capture Inputs 4
  IC5      Capture Inputs 5
  OC1      Output Compare Output 1
  OC2      Output Compare Output 2
  OC3      Output Compare Output 3
  OC4      Output Compare Output 4
  OC5      Output Compare Output 5
  OCFA     Output Compare Fault A Input
  OCFB     Output Compare Fault B Input
  INT1     External Interrupt 1
  INT2     External Interrupt 2
  INT3     External Interrupt 3
  INT4     External Interrupt 4
  T2CK     Timer2 external clock input
  T3CK     Timer3 external clock input
  T4CK     Timer4 external clock input
  T5CK     Timer5 external clock input
  U1CTS    UART1 clear to send
  U1RTS    UART1 ready to send
  U1RX     UART1 receive
  U1TX     UART1 transmit
  U2CTS    UART2 clear to send
  U2RTS    UART2 ready to send
  U2RX     UART2 receive
  U2TX     UART2 transmit
  SDI1     SPI1 data in
  SDO1     SPI1 data out
  SS1      SPI1 slave synchronization or frame pulse I/O
  SDI2     SPI2 data in
  SDO2     SPI2 data out
  SS2      SPI2 slave synchronization or frame pulse I/O
  C1OUT    Comparator 1 Output
  C2OUT    Comparator 2 Output
  C3OUT    Comparator 3 Output

Toolchains
==========

  Note that in addition to the configuration options listed below, the
  toolchain can be configured using the kconfig-mconf utility ('make menuconfig')
  or by passing CONFIG_MIPS32_TOOLCHAIN=<toolchain> to make, where
  <toolchain> is one of GNU_ELF, MICROCHIPL, MICROCHIPW, MICROCHIPL_LITE,
  MICROCHIPW_LITE, MICROCHIPOPENL or PINGUINOW as described below.

  MPLAB/C32
  ---------

  I am using the free, "Lite" version of the PIC32MX toolchain available
  for download from the microchip.com web site.  I am using the Windows
  version.  The MicroChip toolchain is the only toolchain currently
  supported in these configurations, but it should be a simple matter to
  adapt to other toolchains by modifying the Make.defs file include in
  each configuration.

  Toolchain Options:

    CONFIG_MIPS32_TOOLCHAIN_MICROCHIPW      - MicroChip full toolchain for Windows (C32)
    CONFIG_MIPS32_TOOLCHAIN_MICROCHIPL      - MicroChip full toolchain for Linux (C32)
    CONFIG_MIPS32_TOOLCHAIN_MICROCHIPW_LITE - MicroChip LITE toolchain for Windows (C32)
    CONFIG_MIPS32_TOOLCHAIN_MICROCHIPL_LITE - MicroChip LITE toolchain for Linux (C32)

  NOTE:  The "Lite" versions of the toolchain does not support C++.  Also
  certain optimization levels are not supported by the Lite toolchain.

  MicrochipOpen
  -------------

  An alternative, build-it-yourself toolchain is available here:
  http://sourceforge.net/projects/microchipopen/ .  These tools were
  last updated circa 2010.  NOTE:  C++ support still not available
  in this toolchain.  Use this configuration option to select the microchipopen
  toolchain:

    CONFIG_MIPS32_TOOLCHAIN_MICROCHIPOPENL - microchipOpen toolchain for Linux

  And set the path appropriately in the PATH environment variable.

  Building MicrochipOpen (on Linux)
  ---------------------------------

  1) Get the build script from this location:

      http://microchipopen.svn.sourceforge.net/viewvc/microchipopen/ccompiler4pic32/buildscripts/trunk/

  2) Build the code using the build script, for example:

      ./build.sh -b v105_freeze

     This will check out the selected branch and build the tools.

  3) Binaries will then be available in a subdirectory with a name something like
     pic32-v105-freeze-20120622/install-image/bin (depending on the current data
     and the branch that you selected.

     Note that the tools will have the prefix, mypic32- so, for example, the
     compiler will be called mypic32-gcc.

  Pinguino mips-elf / Generic mips-elf Toolchain
  ---------------------------

  Another option is the mips-elf toolchain used with the Pinguino project.  This
  is a relatively current mips-elf GCC and should provide free C++ support as
  well. This toolchain can be downloaded from the Pinguino website:
  http://wiki.pinguino.cc/index.php/Main_Page#Download .

  Support for the Pinguino mips-elf toolchain has been included in the p32mx270f256b_bare
  configurations.  Use one of these configuration options to select the Pinguino
  mips-elf toolchain:

    CONFIG_MIPS32_TOOLCHAIN_PINGUINOW - Pinguino mips-elf toolchain for Windows
    CONFIG_MIPS32_TOOLCHAIN_GNU_ELF   - mips-elf toolchain for Linux or macOS

  And set the path appropriately in the PATH environment variable.  These tool
  configurations are untested -- expect some additional integration issues.
  Good luck!

  This configuration will also work with any generic mips-elf GCC past version
  4.6 or so.

  MPLAB/C32 vs MPLABX/X32
  -----------------------

  It appears that Microchip is phasing out the MPLAB/C32 toolchain and replacing
  it with MPLABX and XC32.  At present, the XC32 toolchain is *not* compatible
  with the NuttX build scripts.  Here are some of the issues that I see when trying
  to build with XC32:

  1) Make.def changes:  You have to change the tool prefix:

     CROSSDEV=xc32-

  2) debug.ld/release.ld:  The linker expects some things that are not present in
     the current linker scripts (or are expected with different names).  Here
     are some partial fixes:

     Rename:  kseg0_progmem to kseg0_program_mem
     Rename:  kseg1_datamem to kseg1_data_mem

  Even then, there are more warnings from the linker and some undefined symbols
  for non-NuttX code that resides in the unused Microchip libraries.  You will
  have to solve at least this undefined symbol problem if you want to used thei
  XC32 toolchain.

  Windows Native Toolchains
  -------------------------

  NOTE:  There are several limitations to using a Windows based toolchain in a
  Cygwin environment.  The three biggest are:

  1. The Windows toolchain cannot follow Cygwin paths.  Path conversions are
     performed automatically in the Cygwin makefiles using the 'cygpath' utility
     but you might easily find some new path problems.  If so, check out 'cygpath -w'

  2. Windows toolchains cannot follow Cygwin symbolic links.  Many symbolic links
     are used in NuttX (e.g., include/arch).  The make system works around these
     problems for the Windows tools by copying directories instead of linking them.
     But this can also cause some confusion for you:  For example, you may edit
     a file in a "linked" directory and find that your changes had no effect.
     That is because you are building the copy of the file in the "fake" symbolic
     directory.  If you use a Windows toolchain, you should get in the habit of
     making like this:

       make clean_context all

     An alias in your .bashrc file might make that less painful.

Loading NuttX with ICD3
========================

  Intel Hex Format Files:
  -----------------------

    When NuttX is built it will produce two files in the top-level NuttX
    directory:

    1) nuttx - This is an ELF file, and
    2) nuttx.hex - This is an Intel Hex format file.  This is controlled by
       the setting CONFIG_INTELHEX_BINARY in the .config file.

    The PICkit tool wants an Intel Hex format file to burn into FLASH. However,
    there is a problem with the generated nutt.hex: The tool expects the nuttx.hex
    file to contain physical addresses.  But the nuttx.hex file generated from the
    top-level make will have address in the KSEG0 and KSEG1 regions.

  tools/pic32/mkpichex:
  ----------------------

    There is a simple tool in the NuttX tools/pic32 directory that can be
    used to solve both issues with the nuttx.hex file.  But, first, you must
    build the tool:

      cd tools/pic32
      make -f Makefile.host

    Now you will have an executable file call mkpichex (or mkpichex.exe on
    Cygwin).  This program will take the nutt.hex file as an input, it will
    convert all of the KSEG0 and KSEG1 addresses to physical address, and
    it will write the modified file, replacing the original nuttx.hex.

    To use this file, you need to do the following things:

      export PATH=???  # Add the NuttX tools/pic32 directory to your
                       # PATH variable
      make             # Build nuttx and nuttx.hex
      mkpichex $PWD    # Convert addresses in nuttx.hex.  $PWD is the path
                       # to the top-level build directory.  It is the only
                       # required input to mkpichex.

      This procedure is automatically performed at the end of a build.

LED Usage
=========

  The p32mx270f256b_bare module has 2 user LEDs labeled LED0 and LED1 in the schematics:

    ---  ----- --------------------------------------------------------------
    PIN  Board Notes
    ---  ----- --------------------------------------------------------------
    RC8  LED0  Grounded, high value illuminates
    RC9  LED1  Grounded, high value illuminates

  The Dimitech DTX1-4000L EV-kit1 supports 3 more LEDs, but there are not
  controllable from software.

  If CONFIG_ARCH_LEDS is defined, then NuttX will control these LEDs as
  follows:
                                 ON        OFF
    ------------------------- ---- ---- ---- ----
                              LED0 LED1 LED0 LED1
    ------------------------- ---- ---- ---- ----
    LED_STARTED            0  OFF  OFF  ---  ---
    LED_HEAPALLOCATE       1  ON   OFF  ---  ---
    LED_IRQSENABLED        2  OFF  ON   ---  ---
    LED_STACKCREATED       3  ON   ON   ---  ---
    LED_INIRQ              4  ON   N/C  OFF  N/C
    LED_SIGNAL             4  ON   N/C  OFF  N/C
    LED_ASSERTION          4  ON   N/C  OFF  N/C
    LED_PANIC              4  ON   N/C  OFF  N/C

UART Usage
==========

  When mounted on the DTX1-4000L EV-kit1 board, serial output is available through
  an FT230X device via the FUNC0 and FUNC1 module outputs.  If CONFIG_PIC32MX_UART2
  is enabled, the src/pic32_boot will configure the UART2 pins as follows:

    ---------- ------ ----- ------ -------------------------
       BOARD   MODULE  PIN  SIGNAL NOTES
    ---------- ------ ----- ------ -------------------------
    FT230X RXD  FUNC0 RPB11  U2RX  UART2 RX (Also PGEC2)
    FT230X TXD  FUNC1 RPB10  U2TX  UART2 TX (Also PGED2)

  However, since the FUNC0/1 pins are shared with the PGEC/D2, they cannot be used
  for UART2 if you are also debugging with the ICD3.  In that case, you may need
  to switch to UART1.

  If CONFIG_PIC32MX_UART1 is enabled, the src/pic32_boot will configure the UART
  pins as follows.  This will support communictions (via an external RS-232
  driver) through X3 pins 4 and 5:

    ---------- ------ ----- ------ -------------------------
       BOARD   MODULE  PIN  SIGNAL NOTES
    ---------- ------ ----- ------ -------------------------
    X3, pin 4   FUNC4 RPBC5  U1TX  UART1 TX
    X3, pin 5   FUNC5 RPBC6  U1RX  UART1 RX

  If you are not using MPLAB to debug, you may also want to change Make.defs
  to use the release.ld linker script instead of the debug.ld link script.  This
  change will give you a little more memory by re-using the boot FLASH and SRAM
  that would otherwise be reserved for MPLAB.

Analog Input
============

  The p32mx270f256b_bare features a PGA117 amplifier/multipexer that can be configured to
  bring any analog signal from PORT0,.. PORT7 to pin 19 of the PIC32MX:

  --- ------------------------------------------------ ----------------------------
  PIN PIC32 SIGNAL(s)                                  BOARD SIGNAL/USAGE
  --- ------------------------------------------------ ----------------------------
  19  PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0 AIN PGA117 Vout
  --- ------------------------------------------------ ----------------------------

  The PGA117 driver can be enabled by setting the following the nsh
  configuration:

    CONFIG_ADC=y         : Enable support for analog input devices
    CONFIG_PIC32MX_ADC=y : Enable support the PIC32 ADC driver
    CONFIG_ADC_PGA11X=y  : Enable support for the PGA117

  When CONFIG_PIC32MX_ADC=y is defined, the p32mx270f256b_bare boot up logic will
  automatically configure pin 18 (AN0) as an analog input (see boards/p32mx270f256b_bare/src/up_adc.c).
  To initializee and use the PGA117, you to add logic something like the
  following in your application code:

  #include <nuttx/spi/spi.h>
  #include <nuttx/analog/pga11x.h>

  FAR struct spi_dev_s *spi;
  PGA11X_HANDLE handle;

  /* Get the SPI port */

  spi = pic32mx_spibus_initialize(2);
  if (!spi)
    {
      _err("ERROR: Failed to initialize SPI port 2\n");
      return -ENODEV;
    }

  /* Now bind the SPI interface to the PGA117 driver */

  handle = pga11x_initialize(spi);
  if (!handle)
    {
      _err("ERROR: Failed to bind SPI port 2 to the PGA117 driver\n");
      return -ENODEV;
    }

  After that initialization is set, then one of PORT0-7 can be select as
  an analog input to AN0 like:

  struct pga11x_settings_s settings;
  int ret;

  settings.channel = PGA11X_CHAN_CH2;
  settings.gain    = PGA11X_GAIN_2;

  ret = pga11x_select(handle, &settings);
  if (ret < 0)
    {
      _err("ERROR: Failed to select channel 2, gain 2\n");
      return -EIO;
    }

  The above logic may belong in boards/p32mx270f256b_bare/src/up_adc.c?

  There is still one missing piece to complete the analog support on the
  p32mx270f256b_bare.  This is the ADC driver that collects analog data and provides
  and ADC driver that can be used with standard open, close, read, and write
  interfaces.  To complete this driver, the following is needed:

  (1) arch/mips/src/pic32mx/pic32mx_adc.c.  The ADC driver that implements
      the ADC interfaces defined in include/nuttx/analog/adc.h and must
      be built when CONFIG_PIC32MX_ADC is defined.

  (2) boards/p32mx270f256b_bare/up_adc.c.  Add p32mx270f256b_bare logic that initializes and
      registers the ADC driver.

  A complete ADC driver will be a considerable amount of work to support
  all of the ADC features (such as timer driven sampling).  If all you want
  to do is a simple analog conversion, then in lieu of a real ADC driver,
  you can use simple in-line logic such as you can see in the PIC32MX7 MMB
  touchscreen driver at boards/pic32mx7mmb/src/up_touchscreen.c

PIC32MX Configuration Options
=============================

  General Architecture Settings:

    CONFIG_ARCH - Identifies the arch/ subdirectory.  This should
     be set to:

       CONFIG_ARCH=mips

    CONFIG_ARCH_family - For use in C code:

       CONFIG_ARCH_MIPS=y

    CONFIG_ARCH_architecture - For use in C code:

       CONFIG_ARCH_MIPS32=y

    CONFIG_ARCH_CHIP - Identifies the arch/*/chip subdirectory

       CONFIG_ARCH_CHIP=pic32mx

    CONFIG_ARCH_CHIP_name - For use in C code to identify the exact
       chip:

       CONFIG_ARCH_CHIP_PIC32MX250F128D=y

    CONFIG_ARCH_BOARD - Identifies the boards/ subdirectory and
       hence, the board that supports the particular chip or SoC.

       CONFIG_ARCH_BOARD=p32mx270f256b_bare

    CONFIG_ARCH_BOARD_name - For use in C code

       CONFIG_ARCH_BOARD_P32MX270F256B_BARE=y

    CONFIG_ARCH_LOOPSPERMSEC - Must be calibrated for correct operation
       of delay loops

    CONFIG_ENDIAN_BIG - define if big endian (default is little
       endian)

    CONFIG_RAM_SIZE - Describes the installed DRAM (CPU SRAM in this case):

       CONFIG_RAM_SIZE=(32*1024) (32Kb)

       There is an additional 32Kb of SRAM in AHB SRAM banks 0 and 1.

    CONFIG_RAM_START - The start address of installed DRAM

       CONFIG_RAM_START=0xa0000000

    CONFIG_ARCH_LEDS - Use LEDs to show state. Unique to boards that
       have LEDs

    CONFIG_ARCH_INTERRUPTSTACK - This architecture supports an interrupt
       stack. If defined, this symbol is the size of the interrupt
       stack in bytes.  If not defined, the user task stacks will be
       used during interrupt handling.

    CONFIG_ARCH_STACKDUMP - Do stack dumps after assertions

    CONFIG_ARCH_LEDS -  Use LEDs to show state. Unique to board architecture.

    PIC32MX Configuration

      CONFIG_PIC32MX_MVEC - Select muli- vs. single-vectored interrupts

    Individual subsystems can be enabled:

       CONFIG_PIC32MX_WDT            - Watchdog timer
       CONFIG_PIC32MX_T2             - Timer 2 (Timer 1 is the system time and always enabled)
       CONFIG_PIC32MX_T3             - Timer 3
       CONFIG_PIC32MX_T4             - Timer 4
       CONFIG_PIC32MX_T5             - Timer 5
       CONFIG_PIC32MX_IC1            - Input Capture 1
       CONFIG_PIC32MX_IC2            - Input Capture 2
       CONFIG_PIC32MX_IC3            - Input Capture 3
       CONFIG_PIC32MX_IC4            - Input Capture 4
       CONFIG_PIC32MX_IC5            - Input Capture 5
       CONFIG_PIC32MX_OC1            - Output Compare 1
       CONFIG_PIC32MX_OC2            - Output Compare 2
       CONFIG_PIC32MX_OC3            - Output Compare 3
       CONFIG_PIC32MX_OC4            - Output Compare 4
       CONFIG_PIC32MX_OC5            - Output Compare 5
       CONFIG_PIC32MX_I2C1           - I2C 1
       CONFIG_PIC32MX_I2C2           - I2C 2
       CONFIG_PIC32MX_SPI1           - SPI 1
       CONFIG_PIC32MX_SPI2           - SPI 2
       CONFIG_PIC32MX_UART1          - UART 1
       CONFIG_PIC32MX_UART2          - UART 2
       CONFIG_PIC32MX_ADC            - ADC 1
       CONFIG_PIC32MX_PMP            - Parallel Master Port
       CONFIG_PIC32MX_CM1            - Comparator 1
       CONFIG_PIC32MX_CM2            - Comparator 2
       CONFIG_PIC32MX_CM3            - Comparator 3
       CONFIG_PIC32MX_RTCC           - Real-Time Clock and Calendar
       CONFIG_PIC32MX_DMA            - DMA
       CONFIG_PIC32MX_FLASH          - FLASH
       CONFIG_PIC32MX_USBDEV         - USB device
       CONFIG_PIC32MX_USBHOST        - USB host
       CONFIG_PIC32MX_CTMU           - CTMU

    PIC32MX Configuration Settings
    DEVCFG0:
      CONFIG_PIC32MX_DEBUGGER - Background Debugger Enable. Default 3 (disabled). The
        value 2 enables.
      CONFIG_PIC32MX_ICESEL - In-Circuit Emulator/Debugger Communication Channel Select
        Default 1 (PG2)
      CONFIG_PIC32MX_PROGFLASHWP  - Program FLASH write protect.  Default 0xff (disabled)
      CONFIG_PIC32MX_BOOTFLASHWP - Default 1 (disabled)
      CONFIG_PIC32MX_CODEWP - Default 1 (disabled)
    DEVCFG1: (All settings determined by selections in board.h)
    DEVCFG2: (All settings determined by selections in board.h)
    DEVCFG3:
      CONFIG_PIC32MX_USBIDO - USB USBID Selection.  Default 1 if USB enabled
        (USBID pin is controlled by the USB module), but 0 (GPIO) otherwise.
      CONFIG_PIC32MX_VBUSIO - USB VBUSON Selection (Default 1 if USB enabled
        (VBUSON pin is controlled by the USB module, but 0 (GPIO) otherwise.
      CONFIG_PIC32MX_WDENABLE - Enabled watchdog on power up.  Default 0 (watchdog
        can be enabled later by software).

    The priority of interrupts may be specified.  The value ranage of
    priority is 4-31. The default (16) will be used if these any of these
    are undefined.

       CONFIG_PIC32MX_CTPRIO         - Core Timer Interrupt
       CONFIG_PIC32MX_CS0PRIO        - Core Software Interrupt 0
       CONFIG_PIC32MX_CS1PRIO        - Core Software Interrupt 1
       CONFIG_PIC32MX_INT0PRIO       - External Interrupt 0
       CONFIG_PIC32MX_INT1PRIO       - External Interrupt 1
       CONFIG_PIC32MX_INT2PRIO       - External Interrupt 2
       CONFIG_PIC32MX_INT3PRIO       - External Interrupt 3
       CONFIG_PIC32MX_INT4PRIO       - External Interrupt 4
       CONFIG_PIC32MX_FSCMPRIO       - Fail-Safe Clock Monitor
       CONFIG_PIC32MX_T1PRIO         - Timer 1 (System timer) priority
       CONFIG_PIC32MX_T2PRIO         - Timer 2 priority
       CONFIG_PIC32MX_T3PRIO         - Timer 3 priority
       CONFIG_PIC32MX_T4PRIO         - Timer 4 priority
       CONFIG_PIC32MX_T5PRIO         - Timer 5 priority
       CONFIG_PIC32MX_IC1PRIO        - Input Capture 1
       CONFIG_PIC32MX_IC2PRIO        - Input Capture 2
       CONFIG_PIC32MX_IC3PRIO        - Input Capture 3
       CONFIG_PIC32MX_IC4PRIO        - Input Capture 4
       CONFIG_PIC32MX_IC5PRIO        - Input Capture 5
       CONFIG_PIC32MX_OC1PRIO        - Output Compare 1
       CONFIG_PIC32MX_OC2PRIO        - Output Compare 2
       CONFIG_PIC32MX_OC3PRIO        - Output Compare 3
       CONFIG_PIC32MX_OC4PRIO        - Output Compare 4
       CONFIG_PIC32MX_OC5PRIO        - Output Compare 5
       CONFIG_PIC32MX_I2C1PRIO       - I2C 1
       CONFIG_PIC32MX_I2C2PRIO       - I2C 2
       CONFIG_PIC32MX_SPI1PRIO       - SPI 1
       CONFIG_PIC32MX_SPI2PRIO       - SPI 2
       CONFIG_PIC32MX_UART1PRIO      - UART 1
       CONFIG_PIC32MX_UART2PRIO      - UART 2
       CONFIG_PIC32MX_CN             - Input Change Interrupt
       CONFIG_PIC32MX_ADCPRIO        - ADC1 Convert Done
       CONFIG_PIC32MX_PMPPRIO        - Parallel Master Port
       CONFIG_PIC32MX_CM1PRIO        - Comparator 1
       CONFIG_PIC32MX_CM2PRIO        - Comparator 2
       CONFIG_PIC32MX_FSCMPRIO       - Fail-Safe Clock Monitor
       CONFIG_PIC32MX_RTCCPRIO       - Real-Time Clock and Calendar
       CONFIG_PIC32MX_DMA0PRIO       - DMA Channel 0
       CONFIG_PIC32MX_DMA1PRIO       - DMA Channel 1
       CONFIG_PIC32MX_DMA2PRIO       - DMA Channel 2
       CONFIG_PIC32MX_DMA3PRIO       - DMA Channel 3
       CONFIG_PIC32MX_FCEPRIO        - Flash Control Event
       CONFIG_PIC32MX_USBPRIO        - USB

  PIC32MXx specific device driver settings

    CONFIG_UARTn_SERIAL_CONSOLE - selects the UARTn for the
       console and ttys0 (default is the UART0).
    CONFIG_UARTn_RXBUFSIZE - Characters are buffered as received.
       This specific the size of the receive buffer
    CONFIG_UARTn_TXBUFSIZE - Characters are buffered before
       being sent.  This specific the size of the transmit buffer
    CONFIG_UARTn_BAUD - The configure BAUD of the UART.  Must be
    CONFIG_UARTn_BITS - The number of bits.  Must be either 7 or 8.
    CONFIG_UARTn_PARTIY - 0=no parity, 1=odd parity, 2=even parity
    CONFIG_UARTn_2STOP - Two stop bits

  PIC32MXx USB Device Configuration

  PIC32MXx USB Host Configuration (the PIC32MX does not support USB Host)

Configurations
==============

Each PIC32MX configuration is maintained in a sub-directory and can be
selected as follow:

    tools/configure.sh p32mx270f256b_bare:<subdir>

Where <subdir> is one of the following:

  nsh

    This configuration directory holds configuration files that can
    be used to support the NuttShell (NSH).  This configuration use
    UART1 which is available on FUNC 4 and 5 on connector X3:

      CONFIG_PIC32MX_UART1=y           : UART1 for serial console
      CONFIG_UART1_SERIAL_CONSOLE=n

    NOTES:

    1. This configuration uses the mconf-based configuration tool.  To
       change this configurations using that tool, you should:

       a. Build and install the kconfig-mconf tool.  See nuttx/README.txt
          see additional README.txt files in the NuttX tools repository.

       b. Execute 'make menuconfig' in nuttx/ in order to start the
          reconfiguration process.

    2. UART2

       If you are not using MPLAB to debug, you may switch to UART2
       by modifying the NuttX configuration to disable UART1 and to
       select UART2.  You should also change Make.defs to use the
       release.ld linker script instead of the debug.ld link script.

    3. This configuration also uses the Microchip C32 toolchain under
       windows by default:

         CONFIG_MIPS32_TOOLCHAIN_MICROCHIPW_LITE=y : Lite version of windows toolchain

       To switch to the Linux C32 toolchain you will have to change (1) the
       toolchain selection in .config (after configuration) and (2) the
       path to the toolchain in the PATH environment variable.  See notes above
       with regard to the XC32 toolchain.

    4. PGA117 Support

       The p32mx270f256b_bare's PGA117 amplifier/multiplexer is not used by this configuration
       but can be enabled by setting:

         CONFIG_ADC=y         : Enable support for analog input devices
         CONFIG_ADC_PGA11X=y  : Enable support for the PGA117

  nxffs

    This is a configuration very similar to the nsh configuration.  This
    configure also provides the NuttShell (NSH).  And this configuration use
    UART1 which is available on FUNC 4 and 5 on connector X3 (as described
    for the nsh configuration).  This configuration differs from the nsh
    configuration in the following ways:

    1. This configuration uses the mconf-based configuration tool.  To
       change this configurations using that tool, you should:

       a. Build and install the kconfig-mconf tool.  See nuttx/README.txt
          see additional README.txt files in the NuttX tools repository.

       b. Execute 'make menuconfig' in nuttx/ in order to start the
          reconfiguration process.

    2. It uses the Pinguino toolchain be default (this is easily changed,
       see above).

         CONFIG_MIPS32_TOOLCHAIN_PINGUINOW=y

    3. SPI2 is enabled and support is included for the NXFFS file system
       on the 32Mbit SST25 device on the p32mx270f256b_bare board.  NXFFS is the NuttX
       wear-leveling file system.

         CONFIG_PIC32MX_SPI2=y
         CONFIG_MTD_SST25=y
         CONFIG_SST25_SECTOR512=y
         CONFIG_DISABLE_MOUNTPOINT=n
         CONFIG_FS_NXFFS=y
         CONFIG_NSH_ARCHINIT=y

    4. Many operating system features are suppressed to produce a smaller
       footprint.

         CONFIG_SCHED_WAITPID=n
         CONFIG_DISABLE_POSIX_TIMERS=y
         CONFIG_DISABLE_PTHREAD=y
         CONFIG_DISABLE_MQUEUE=y
         CONFIG_DISABLE_MQUEUE=y

    5. Many NSH commands are suppressed, also for a smaller FLASH footprint

       CONFIG_NSH_DISABLESCRIPT=y
       CONFIG_NSH_DISABLEBG=y

       CONFIG_NSH_DISABLE_DD=y
       CONFIG_NSH_DISABLE_EXEC=y
       CONFIG_NSH_DISABLE_EXIT=y
       CONFIG_NSH_DISABLE_GET=y
       CONFIG_NSH_DISABLE_IFCONFIG=y
       CONFIG_NSH_DISABLE_KILL=y
       CONFIG_NSH_DISABLE_MKFIFO=y
       CONFIG_NSH_DISABLE_MKRD=y
       CONFIG_NSH_DISABLE_PUT=y
       CONFIG_NSH_DISABLE_SOURCE=y
       CONFIG_NSH_DISABLE_TEST=y
       CONFIG_NSH_DISABLE_WGET=y

      When the system boots, you should have the NXFFS file system mounted
      at /mnt/sst25.

      NOTES:

      a) It takes many seconds to boot the system using the NXFFS
         file system because the entire FLASH must be verified on power up
         (and longer the first time that NXFFS comes up and has to format the
         entire FLASH).
      b) FAT does not have these delays and this configuration can be modified
         to use the (larger) FAT file system as described below.  But you will,
         or course, lose the wear-leveling feature if FAT is used.

    6. FAT

       There is no FAT configuration, but the nxffx configuration can be used
       to support the FAT FS if the following changes are made to the NuttX
       configuration file:

         CONFIG_FS_NXFFS=n
         CONFIG_FS_FAT=y
         CONFIG_NSH_DISABLE_MKFATFS=n

       In this configuration, the FAT file system will not be automatically
       mounted.  When NuttX boots to the NSH prompt, you will find the
       SST5 block driver at /dev/mtdblock0.  This can be formatted with a
       FAT file system and mounted with these commands:

         nsh> mkfatfs /dev/mtdblock0
         nsh> mount -t vfat /dev/mtdblock0 /mnt/sst25

    7. PGA117 Support

       The p32mx270f256b_bare's PGA117 amplifier/multipexer is not used by this
       configuration but can be enabled by setting:

         CONFIG_ADC=y         : Enable support for anlog input devices
         CONFIG_ADC_PGA11X=y  : Enable support for the PGA117
