                           R. Loew TRIMCHK Program


The R. Loew TRIM Program allows the user to send TRIM Commands to SSD Drives
so that the Drives Controller can reuse data blocks that are no longer
needed.

The TRIMCHK Program allows the user to determine if a given Drive can be
Trimmed by the TRIM Program without performing an actual TRIM. It is part of
the Demo Package for the TRIM program so you can test compatability before
purchasing the Full TRIM Package.


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

The syntax for the TRIM Program is:

TRIMCHK Drive|Disk

Drive is the Drive Letter of a Partition to TRIM.
or
Disk is the INT 13 Number of the Disk to TRIM. First Hard Disk is 0x80 or 128.



WINDOWS:

The TRIMCHK Program cannot be run from Windows, even in a DOS Box. It must be
run from Real Mode DOS.



EXAMPLES:

TRIM D:         Tests Drive that holds D: Partition
TRIM 0x81       Teses Second Physical Hard Drive
