                       AHCI CD/DVD DOS DRIVER

                             Version 1.0

                              06/10/2018

                          Copyright (C) 2018
                          By Rudolph R. Loew
                             
                             

The AHCI CD/DVD DOS Driver provides support for Optical Drives (CD, DVD or
Blu-Ray) in DOS when using active AHCI Disk Drive Controllers.

This Driver can be added to a Windows or other DOS based Installation CD to
support Installation on Computers in AHCI Mode.



REQUIREMENTS

DOS
MSCDEX.EXE (part of DOS) or alternative
AHCI capable Motherboard and/or Card(s).



CONTENTS

AHCICD.SYS      AHCI CD/DVD Driver
README.TXT      This File
LICENSE.TXT     License File
HISTORY.TXT     Revision History



LICENSE

Read the Licensing terms and conditions in the LICENSE.TXT file before
using this Software Program. Usage of any of the Programs constitutes
acceptance of all of the terms and conditions in the LICENSE.TXT file.



USAGE

This Driver a standard DOS Driver and performs similarly to standard CD
Drivers such as OAKCDROM (Legacy Mode) or GCDROM (Native Mode).

The Driver is loaded by a DEVICEHIGH= or DEVICE= Entry in an A:\CONFIG.SYS or
C:\CONFIG.SYS File. MSCDEX is linked to it through a common Device Name
usually through an A:\AUTOEXEC.BAT or C:\AUTOEXEC.BAT File.

The C: Drive is used for most Installations using a Hard Drive.
The A: Drive would be used for a Floppy Disk or some USB Boot Devices.
If the Driver is being added to a Windows Installation Disk, it would be
placed in the Emulated Floppy Boot Section and would be accessed via A:.


A Drive Letter is then assigned by MSCDEX which can be used to access the CD,
DVD or Blu-Ray.

AHCICD has not been tested with alternative Drivers such as SHSUCDX.



INSTALLATION

Place the AHCICD.SYS File in a known accessible place such as the root
folder of the A: or C: Drive.

Edit the appropriate CONFIG.SYS File and add the following line after the
other DEVICEHIGH= or DEVICE= Lines:

DEVICEHIGH=<path>AHCICD.SYS /D:name [/C:#]

or

DEVICE=<path>AHCICD.SYS /D:Devname [/C:#]

<path> is the Path to the File. Only required if the File is not in the Root
of the same Drive.

Devname is the Driver Name that will be used later by MSCDEX. Standard
practice is to use OEMCD001. If you have other DOS CD Drivers that might also
get loaded, use a different Devname such as OEMCD002. Devname is not case
sensitive.

[/C:#] is an optional argument to specify a particular AHCI Controller if
there are more than one. If omitted, the first one will be used (same as
using /C:0). # is the Controller number and is a single digit from 0 thru 9. 
The first Controller is Number 0, the next is Number 1 etc.

Edit the appropriate AUTOEXEC.BAT File.

If there is an existing MSCDEX (or alternative) entry, edit or add the
Devname specified with AHCICD.SYS.

ex. MSCDEX /D:OEMCD001 /D:OEMCD002 <other options>

If not, enter the following line before any commands that need access to the
CD, otherwise the end, as follows:

<path>MSCDEX /D:Devname <other options>

<path> is the Path to the File. Only required if the File is not in the Root
of the same Drive.

Devname is the Driver Name that was specified by AHCICD.SYS.
Devname is not case sensitive.

Other Options may be specified such as starting Drive Letter. See MSCDEX
Documentation for further information.



WINDOWS INSTALLATION CD

If you are adding the AHCICD.SYS Driver to a Windows 95, 98, 98SE, or ME
Installation CD, do the following:

1. Extract the 1.44MB Boot Image from the CD.
2. Extract the Files from the Boot Image, or raw copy the Boot Image to a
   Floppy Disk.
3. Copy the AHCICD.SYS File to the Folder or Floppy holding the Files.
4. Edit the CONFIG.SYS and AUTOEXEC.BAT as described above where there are
   other DOS CD Drivers present.
5. Rebuild the Boot Image.
6. Burn a new CD using the Boot Image and the rest of the Windows
   Installation CD, plus my Windows 95/98/98SE/ME Drivers if purchased.

You will need CD burning and manipulation tools to do this.



WINDOWS 95, 98, 98SE and ME

You can use the AHCI CD/DVD DOS Driver to support Optical Drives in Windows
using the methods described above but performance will be limited as you
will be running the Optical Drive in "Compatibility Mode".

If you want full performance for the Optical Drive(s) and any Hard Drives
also connected to the AHCI Controller, you will need to purchase my Windows
95/98/98SE/ME AHCI Driver Package (see below).



LIMITATIONS

AHCICD.SYS will not work with BIOSes that do not activate the AHCI Protocol
when set to AHCI Mode.

Not tested with MSCDEX alternatives or with FREEDOS.

Do not use with the AHCI.SYS Driver from HP or Intel.



RELATED PRODUCTS

Windows 95/98/98SE/ME AHCI Driver.

This Driver provides support for AHCI Controllers to Windows 95, 98, 98SE,
and ME. This eliminates "Compatibility Mode" operation for Hard Drives and
Optical Drives connected to AHCI Controllers. Performance is significantly
increased and stability in improved.



ORDERING

To purchase additional copies of this Software for other Computers:
Send $10 US + $1 S&H per copy to:

To purchase the Windows 95/98/98SE/ME AHCI Driver:
Send $20 US + $1 S&H per copy to:

Rudolph Loew
506 Bieling Rd.
Elmont, NY 11003
USA

Payment can be made as follows:

1. Cash
2. Money Order drawn on a US Bank or Post Office
3. Personal Check drawn on a US Bank (Delivery made after Check clears)
4. International Postal Money Order accepted by the US Postal Service
5. Paypal to rloew@hotmail.com
6. Western Union

Warning: International Checks or Money Orders, not described above, will not
be accepted and will not be returned without an additional $2 US handling
charge.

Other Payment terms and methods may be available through authorized
Distributors of this Product. The following is a list of authorized
Distributors at this time:

C. C. Anderson  http://slesarc.x10hosting.com

Delivery is by E-Mail. You MUST include the E-Mail address you want the
Software to be sent to.
Please type or print your E-Mail address clearly. Sending me an E-Mail when
you place an order will insure that I have your correct E-Mail address.

Prices and Terms may change at any time.

For additional information or help placing your order,
I can be reached in the following ways:

E-Mail: rloew@hotmail.com
Phone:  1-516-352-9078


QUESTIONS AND COMMENTS

Please direct any questions or comments about the Program or the
Documentation to me at rloew@hotmail.com or as described under ORDERING.
Please send any Bug Reports to rloew@hotmail.com.


MAILING LIST

If you would like to be notified about updates and/or fixes or other products
from Rudolph Loew, E-Mail me at rloew@hotmail.com and ask to be put on my
Mailing list. Your E-Mail address will not be given out nor will you receive
any unsolicited mail. You can unsubscribe at any time.
