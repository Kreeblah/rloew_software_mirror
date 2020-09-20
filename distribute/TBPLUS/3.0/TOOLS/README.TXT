                     TERABYTE PLUS TOOLS AND IMAGES

                             Version 3.0

                              11/02/2015

                        Copyright (C) 2010-2015
                          By Rudolph R. Loew
                             
                             

This Package contains Programs and Image Files used to support the TeraByte
Plus Package.


CONTENTS

SETSECSZ.EXE    Set Logical Sector Size to be Mapped
BLKSIZE.SYS     Set DOS Internal Sector Buffer Size
FLOPBLK.SYS     Set DOS Internal Sector Buffer Size for Large Sector Floppy.
MAKEFLOP.EXE    Make an Installation Floppy from an Image File.
MAKEIMG.EXE     Make an Image File from an Installation Floppy.
FLOPPY.IMG      Image of TBPLUS Installation Floppy.
USB             Generic USB Drivers for Windows 9x.


SETSECSZ

The SETSECSZ Program sets the Logical Sector Size to be emulated by BOOTMAN.
BOOTMAN can emulate a Logical Sector Size that is a Power of 2 Multiple of
the Hard Drives actual Sector Size. SETSECSZ sets a flag in the Drives MBR
that is used by BOOTMAN to determine if Remapping is required. RFDISK also
manages this flag, setting it to the detected Sector Size and Warning if the
old value was not consistent with the new one. This makes it necessary to
activate Remapping, by rebooting under BOOTMAN2, before using RFDISK.

The Syntax is as follow:

SETSECSZ Drive SectorSize

Drive is the Interrupt 13 Drive Number starting from 0x80.
SectorSize is the desired Logical Sector Size.

Sector Sizes can be specified in Byte or in KiloBytes

Ex.  4096 or 4K
    32768 or 32K

Zero or Default disables Remapping. RFDISK will set the True Size.



BLKSIZE

The BLKSIZE Driver creates an Empty Block Driver with the Specified Block
Size. This is used to set the Internal DOS Buffer Size. The DOS Buffer Size
is set during Boot to the largest Sector Size or Block Device Block Size
detected. This buffer is used when Formatting or accessing a Drive Letter.
If all partitions are already Formatted, then the correct Buffer Size will
be large enough for all of the Partitions. When initially Formatting a
Partition with a Larger Sector Size than any already Formatted Partition, the
DOS Buffer may be too small and will be corrupted when the new Partition is
Formatted or accessed. Using the BLKSIZE Driver to insure that the Buffer is
large enough for the largest Sector Size Partition will prevent corruption.

Place the following line in your C:\CONFIG.SYS File:

DEVICE=PATH\BLKSIZE -N MaxSecSize

or

DEVICE=PATH\BLKSIZE MaxSecSize

PATH is the PATH to the BLKSIZE.SYS File
MaxSecSize is the size of the largest Logical Sector Size (Actual or Mapped).

If you use the Drive Number / Partition Number Format instead of the Drive
Letter Format of RFORMAT to Format Partitions, immediately after creating
then with RFDISK, you do not use the DOS Buffer so you do not need to use
BLKSIZE in this case.

The -N Option sets the Buffer Size without loading an Empty Block Driver.
This is recommended but requires the TBPLUS 2.0 or Higher IO.SYS File to be
used. If not using the modified IO.SYS File, do not specify the -N Option.

After Formatting, Rebooting will correctly set the DOS Buffer Size so BLKSIZE
will no longer be needed.



FLOPBLK

The FLOPBLK Driver checks the size of Sectors on the Floppy Drive. If larger
than the Current Internal DOS Buffer Size, the Buffer Size will be increased
as required. See the BLKSIZE Section above for details. The -N Option is
assumed.



MAKEFLOP.EXE

The MAKEFLOP Program copies an Installation Image File (FLOPPY.IMG) into a
Floppy Disk. This is used to create the TBPLUS Installation Floppy used in
the Installation Procedure described in the BOOTMAN2 User's Manual.

The Syntax is as follows:

MAKEFLOP ImageFile

InageFile is the Installation Image File to be written to the Floppy.

A Formatted Error Free Floppy Disk MUST be in the A: Drive before issuing
this command.



MAKEIMG.EXE

The MAKEIMG Program creates an Installation Image File from a Floppy Disk.
If you need to modify an Installation Floppy and then create a new Image
File for transfer to a CD, you can use this Program to create it.

The Syntax is as follows:

MAKEIMG ImageFile

InageFile is the Installation Image File to be created from the Floppy.

The modified TBPLUS Installation Floppy Disk MUST be in the A: Drive before
issuing this command.



FLOPPY.IMG

The FLOPPY Image File contains a Bootable DOS Setup suitable for Partitioning
and Formatting Hard Drives and to Install Windows 9x.

A BOOTMAN2 Overlay is built in so that it is loaded before DOS is loaded.
CD ROM Drivers from the Windows 98 CD are provided to provide CD Access.

A CONFIG.SYS Menu selects the Buffer Size set by BLKSIZE.SYS. The Default is
4KB. Use the Third Option if using Logical Sector Sizes above 4KB. The Second
Option disables BLKSIZE and can be used if no Large Sector Size Hard Drives
are being used.

This Image can be written to a Floppy or used to make a Bootable CD or DVD
for Computers with no Floppy Drive. A copy of the Windows Installation Files
can also be added to the CD to create a complete Installation Disk.



USB

The USB Folder contains a Generic USB Driver suitable for use with 512 Byte
Sector and Large Sector Hard Drives.



CUSTOM INSTALLER

The TBPLUS Installation Floppy/CD/DVD can be customized as follows:

Create a Floppy using MAKEFLOP.EXE and FLOPPY.IMG
Modify the Files and Scripts as needed.
Verify that they work as intended.

Do not disturb the three hidden System Files BOOT, PAD and DDO. Even
recopying them can move them making the Disk unuseable. Be especially
careful if using the XFILE File Manager Utility.

If you need to make a CD or DVD Version, do the additional following steps:

Create a new Image File from the Floppy using MAKEIMG.EXE
Burn the CD/DVD using the new Image File as the Boot Image.
