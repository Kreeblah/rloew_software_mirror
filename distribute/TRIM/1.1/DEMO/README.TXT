                   DOS DISK/FAT32 TRIM Package (Demo)
                          TRIMCHK Test Program
                        
                             Version 1.1

                              06/03/2015

                          Copyright (C) 2015
                          By Rudolph R. Loew


The DOS DISK/FAT32 TRIM Program allows the user to send TRIM Commands to SSD
Drives so that the Drives Controller can reuse data blocks that are no longer
needed.

The TRIMCHK Program allows the user to determine if a given Drive can be
Trimmed by the TRIM Program without performing an actual TRIM. It is the Demo
Package for the TRIM program so you can test compatability before purchasing
the Full TRIM Package.


REQUIREMENTS:

Bootable DOS OS.
SSD or other Drive that supports TRIM Command.
Hard Disk Controller BIOS that reports Control Ports via INT 13 AH=48
USB or Firewire Connected Drives are NOT supported.
Only FAT32 Filesystem supported for selective TRIM.


PURPOSE:

Operating systems older than Windows 7 do not provide TRIM functionality
so SSD Drives accumulate no longer used data blocks that it doesn't know
can be reused. This can greatly slow Write operations to the Drive.


DRIVES AND PARTITIONS:

The TRIMCHK Program accepts INT 13 Disk Numbers starting at 0x80 or Drive
Letters starting with C:.

Specifying Disk Numbers tells TRIMCHK to test a specific Physical Drive.
Disk Numbers start at 0x80 or 128. TRIMCHK allows either representation.

Specifying Drive Letters tells TRIMCHK to identify the Drive holding a
particular Partition and run the compatability test on it.



SYNTAX:

The syntax for the TRIMCHK Program is:

TRIMCHK Drive|Disk

Drive is the Drive Letter of a Partition to test.
or
Disk is the INT 13 Number of the Disk to test. First Hard Disk is 0x80 or 128.



WINDOWS:

The TRIMCHK Program cannot be run from Windows, even in a DOS Box. It must be
run from Real Mode DOS.



EXAMPLES:

TRIM D:         Tests Drive that holds D: Partition
TRIM 0x81       Tests Second Physical Hard Drive



LICENSE

Read the Licensing terms and conditions in the LICENSE.TXT file before
using the Program. Installation of the Program constitutes acceptance
of all of the terms and conditions in the LICENSE.TXT file.



ORDERING

To purchase additional copies of this Software for other Computers:
Send $10 US + $1 S&H per copy to:

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

C. C. Anderson  http://slesarc.x10host.com

Delivery is by E-Mail. You MUST include the E-Mail address you want the
Software to be sent to. It will be a 69KB Zipped Attachment.
Please type or print your E-Mail address clearly. Sending me an E-Mail when
you place an order will insure that I have your correct E-Mail address.

Prices and Terms may change at any time. Download the current Version of this
Software from http://rloew1.no-ip.com or from Simtel before ordering.

For additional information or help placing your order,
I can be reached in the following ways:

E-Mail: rloew@hotmail.com
Phone:  1-516-352-9078
VOIP:   IP = conference.no-ip.org  PORT = 8192 (Conference Console)



QUESTIONS AND COMMENTS

Please direct any questions or comments about the Program or the
Documentation to me at rloew@hotmail.com or as described under ORDERING.
Please send any Bug Reports to rloew@hotmail.com.


MAILING LIST

If you would like to be notified about updates and/or fixes or other products
from Rudolph Loew, E-Mail me at rloew@hotmail.com and ask to be put on my
Mailing list. Your E-Mail address will not be given out nor will you receive
any unsolicited mail. You can unsubscribe at any time.

