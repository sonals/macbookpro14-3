Setting up VFIO Trace of BRCM Drivers
*************************************

Test System
===========

Product Name
   MacBookPro14,3.


BIOS/UEFI Version
   204.0.0.0.0.


Linux
   Ubuntu 18.04.4 LTS.


Pre-requisite Installs
======================

::

	apt get install p7zip-full
	apt get install ovmf
	apt get install virt-manager
	apt get install qemu-kvm


Downloads
=========

Windows10
---------

Download Windows10 ISO from the following site after specifying the edition "Windows 10" and Language (in the next page)
https://www.microsoft.com/en-us/software-download/windows10ISO

Brigadier
---------

Brigadier is a tool that will be used to download BootCamp in the next step::

  git clone https://github.com/timsutton/brigadier

Download and Extract BootCamp
-----------------------------

Obtain the version of Macbook by running the following command::

  sudo dmidecode | grep Version | grep MacBook

Download BootCamp::

  cd brigadier
  ./brigadier --model MacBookPro14,3 -o /tmp/

Now look for BootCampESD.pkg in the /tmp directory::

  find /tmp -name BootCampESD.pkg

Extract the payload from pkg whcih should produce a file named Payload~::

  7z x BootCampESD.pkg

Now extract the dmg file from Payload~ which should produce a file called Library/Application Support/BootCamp/WindowsSupport.dmg::

  cpio -i -d < Payload~

Next extract Broadcom Windows wireless drivers from WindowsSupport.dmg and verify its contents::

  cd "Library/Application Support/BootCamp"
  7z x WindowsSupport.dmg
  ls -lah BootCamp/Drivers/Broadcom/Broadcom*
  7z l BroadcomWirelessWin8x64.exe

You should see something like the following::

  xsjsonalsmbp:/<2>Library/Application Support/BootCamp>ls -lah
  total 771M
  drwxr-xr-x  4 sonals sonals 4.0K May 24 18:16  ./
  drwxr-xr-x  3 sonals sonals 4.0K May 24 18:15  ../
  -rw-r--r--  1 sonals sonals 3.6K Apr 19  2017  AutoUnattend.xml
  drwx------  3 sonals sonals 4.0K Apr 19  2017  BootCamp/
  -rw-r--r--  1 sonals sonals 771M May 24 18:15  WindowsSupport.dmg
  drwx------ 10 sonals sonals 4.0K Apr 19  2017 '$WinPEDriver$'/
  xsjsonalsmbp:/<2>Library/Application Support/BootCamp>ls -lah BootCamp/Drivers/Broadcom/Broadcom*
  -rw-r--r-- 1 sonals sonals 917K Apr 19  2017 BootCamp/Drivers/Broadcom/BroadcomBluetooth64.exe
  -rw-r--r-- 1 sonals sonals 541K Apr 19  2017 BootCamp/Drivers/Broadcom/BroadcomCardReader64.exe
  -rw-r--r-- 1 sonals sonals 517K Apr 19  2017 BootCamp/Drivers/Broadcom/BroadcomComController64.exe
  -rw-r--r-- 1 sonals sonals 761K Apr 19  2017 BootCamp/Drivers/Broadcom/BroadcomEthernet64.exe
  -rw-r--r-- 1 sonals sonals 6.6M Apr 19  2017 BootCamp/Drivers/Broadcom/BroadcomWirelessWin8x64.exe
  xsjsonalsmbp:/<2>Library/Application Support/BootCamp>7z l BootCamp/Drivers/Broadcom/BroadcomWirelessWin8x64.exe

  7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
  p7zip Version 16.02 (locale=en_US.UTF-8,Utf16=on,HugeFiles=on,64 bits,8 CPUs Intel(R) Core(TM) i7-7920HQ CPU @ 3.10GHz (906E9),ASM,AES-NI)

  Scanning the drive for archives:
  1 file, 6841960 bytes (6682 KiB)

  Listing archive: BootCamp/Drivers/Broadcom/BroadcomWirelessWin8x64.exe

  --
  Path = BootCamp/Drivers/Broadcom/BroadcomWirelessWin8x64.exe
  Type = PE
  Physical Size = 6841960
  CPU = x86
  Characteristics = Executable 32-bit NoRelocs NoLineNums NoLocalSyms
  Created = 2006-12-03 02:53:00
  Headers Size = 1024
  Checksum = 6898153
  Image Size = 131072
  Section Alignment = 4096
  File Alignment = 512
  Code Size = 77824
  Initialized Data Size = 28672
  Uninitialized Data Size = 0
  Linker Version = 5.0
  OS Version = 4.0
  Image Version = 0.0
  Subsystem Version = 4.0
  Subsystem = Windows GUI
  Stack Reserve = 1048576
  Stack Commit = 8192
  Heap Reserve = 1048576
  Heap Commit = 4096
  Image Base = 4194304
  ----
  Path = [0]
  Size = 6727936
  Packed Size = 6727936
  Virtual Size = 6727936
  Offset = 100864
  --
  Path = [0]
  Type = Rar
  Physical Size = 6727931
  Tail Size = 5
  Characteristics = Lock Solid
  Solid = +
  Blocks = 1
  Multivolume = -
  Volumes = 1

     Date      Time    Attr         Size   Compressed  Name
  ------------------- ----- ------------ ------------  ------------------------
  2016-08-02 12:26:54 ....A        22894         5314  ArabicLicense.txt
  2016-08-02 12:26:54 ....A        29920         6496  BrazilianPortugueseLicense.txt
  2016-08-02 12:26:54 ....A        28060         6770  CzechLicense.txt
  2016-08-02 12:26:54 ....A        27300         5486  DanishLicense.txt
  2016-08-02 12:26:54 ....A        34054         6276  DutchLicense.txt
  2016-08-02 12:26:54 ....A        27142         5085  EnglishLicense.txt
  2016-08-02 12:26:54 ....A        24916         5353  FinnishLicense.txt
  2016-08-02 12:26:54 ....A        32112         6374  FrenchLicense.txt
  2016-08-02 12:26:54 ....A        33430         6376  GermanLicense.txt
  2016-08-02 12:26:54 ....A        31146         6895  HungarianLicense.txt
  2016-08-02 12:26:54 ....A        32122         6429  ItalianLicense.txt
  2016-08-02 12:26:54 ....A        13762         4978  JapaneseLicense.txt
  2016-08-02 12:26:54 ....A        14590         5089  KoreanLicense.txt
  2016-08-02 12:26:54 ....A        28762         5063  NorwegianLicense.txt
  2016-08-02 12:26:54 ....A        31026         6562  PolishLicense.txt
  2016-08-02 12:26:54 ....A        31498         3127  PortugueseLicense.txt
  2016-08-02 12:26:54 ....A        34646         9226  RussianLicense.txt
  2016-08-02 12:26:54 ....A         8944         4326  SimplifiedChineseLicense.txt
  2016-08-02 12:26:54 ....A        32044         5880  SpanishLicense.txt
  2016-08-02 12:26:54 ....A        28372         5273  SwedishLicense.txt
  2016-08-02 12:26:54 ....A         8392         2834  TraditionalChineseLicense.txt
  2016-08-02 12:26:54 ....A        28716         6150  TurkishLicense.txt
  2017-04-05 10:33:14 ....A       955906        46340  bcmwl63.inf
  2016-08-02 11:59:44 ....A      1047632       260445  DPInst.exe
  2017-04-05 10:33:12 ....A      4013560       751226  bcmihvsrv.dll
  2017-04-05 10:33:13 ....A      4134392       224540  bcmihvsrv64.dll
  2017-04-05 10:33:13 ....A      3745272       100478  bcmihvui.dll
  2017-04-05 10:33:14 ....A      3778552       100839  bcmihvui64.dll
  2017-04-05 10:33:14 ....A     10346984      2407253  bcmwl63.sys
  2017-04-05 10:33:13 ....A     11251688      2704274  bcmwl63a.sys
  2017-04-05 10:33:12 ....A        19479         2314  bcm43xx.cat
  2017-04-05 10:33:14 ....A        17458         1258  bcm43xx64.cat
  2016-08-02 11:59:43 ....A        18192         1706  DPInst.xml
  ------------------- ----- ------------ ------------  ------------------------
  2017-04-05 10:33:14           39912963      6726035  33 files
  xsjsonalsmbp:/<2>Library/Application Support/BootCamp>


Install Windows10 VM
====================

Virt-manager Configuration
--------------------------

Start virt-manager click on **Create a new virtual machine** Wizard. In Step 1 select *Local install media* and
select Windows10 ISO downloaded before. In Step 5 of "Create a new virtual machine" check the box for
*Customize configuration before install*. Please select **Q35** for Chipset and **UEFI** for Firmware. If you
cannot see UEFI option please install the ovmf package for your distribution.

Install Windows10
-----------------

Go through the prompts and install Windows10

Copy Broadcom Wireless Drivers, BootCamp/Drivers/Broadcom/BroadcomWirelessWin8x64.exe into Windows10 VM.
You can use **pscp** from within Windows10 VM to copy the file from host to Windows file system.

Attach Broadcom PCIe Wireless Device to Windows10 VM
----------------------------------------------------

Open virt-manager and click on **Show virtual hardware details** Wizard.

Click on *Add Hardware* button

Click on *PCIe Host Device*

Select *BCM43602 802.11ac Wireless LAN SoC*

Shutdown the VM for the PCIe pass through to finish.

Restart the VM from virt-manager and login into Windows. Locate the BroadcomWirelessWin8x64.exe that was copied in
the earlier step and execute the file. Go through the driver installation process. Verify that driver has attached
by opening *Device Manager*. At this stage the wireless should be functional in Windows10 VM.

Now capture the command line used by QEMU to run your Windows10 VM which we will use in the next step::

  ps -aef | grep qemu

Shutdown the VM.

Setting up MMIO Tracing
=======================

Create event tracing config::

  echo "vfio_region_write" > events.txt

Open the vfiotrace.log file and look for ``0x26c960, 0xa5a5a5a5, 4)``. It would look something like the following::

  493@1581830832.154442:vfio_region_write  (0000:03:00.0:region2+0x26c960, 0xa5a5a5a5, 4)
  493@1581830832.154450:vfio_region_write  (0000:03:00.0:region2+0x26ffda, 0x5a5a, 2)
  493@1581830832.154454:vfio_region_write  (0000:03:00.0:region2+0x26ffdc, 0x5a5a, 2)
  493@1581830832.154461:vfio_region_write  (0000:03:00.0:region2+0x26c964, 0x7fdd0000, 4)
  493@1581830832.154469:vfio_region_write  (0000:03:00.0:region2+0x26c968, 0x0, 4)
  493@1581830832.154477:vfio_region_write  (0000:03:00.0:region2+0x26c96c, 0x10000, 4)
  493@1581830832.154484:vfio_region_write  (0000:03:00.0:region2+0x26c980, 0x17ae, 4)
  493@1581830832.154493:vfio_region_write  (0000:03:00.0:region2+0x26e122, 0x3739, 2)
  493@1581830832.154496:vfio_region_write  (0000:03:00.0:region2+0x26e124, 0x2c36382c, 4)
  493@1581830832.154499:vfio_region_write  (0000:03:00.0:region2+0x26e128, 0x3437, 2)
  493@1581830832.154503:vfio_region_write  (0000:03:00.0:region2+0x26e12a, 0x362c, 2)
  493@1581830832.154506:vfio_region_write  (0000:03:00.0:region2+0x26e12c, 0x32352c34, 4)
  493@1581830832.154509:vfio_region_write  (0000:03:00.0:region2+0x26e130, 0x0, 2)
  493@1581830832.154521:vfio_region_write  (0000:03:00.0:region2+0x26e120, 0x2c36382c37392c39, 8)
  ...
  493@1581830832.159343:vfio_region_write  (0000:03:00.0:region2+0x26c988, 0x730032313d766572, 8)
  493@1581830832.159368:vfio_region_write  (0000:03:00.0:region2+0x26c987, 0x6d, 1)
  493@1581830832.159376:vfio_region_write  (0000:03:00.0:region2+0x26c986, 0x6f, 1)
  493@1581830832.159383:vfio_region_write  (0000:03:00.0:region2+0x26c985, 0x72, 1)
  493@1581830832.159390:vfio_region_write  (0000:03:00.0:region2+0x26c984, 0x73, 1)
  493@1581830832.159398:vfio_region_write  (0000:03:00.0:region2+0x26c974, 0x0, 4)
  493@1581830832.159405:vfio_region_write  (0000:03:00.0:region2+0x26c978, 0x0, 4)


Copy the lines starting with ``region2+0x26c960, 0xa5a5a5a5, 4)`` to ``region2+0x26c978, 0x0, 4)`` to a separate file called vfiotrace.nvram.txt.
It should add up to about 775 lines. Copy the lines completely, do not strip out the prefix.


Generate Firmware Files
=======================

Download and Compile QEMU event trace to image generator::

  git clone https://github.com/sonals/macbookpro14-3.git
  mkdir bin
  cd bin
  cmake ../src
  make

Create memory map dump of the tracelog::

  qmap vfiotrace.nvram.txt nvram.bin
  cat nvram.bin
