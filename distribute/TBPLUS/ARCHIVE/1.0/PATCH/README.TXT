             INSTALLATION INSTRUCTIONS FOR TBPLUS PATCH PACKAGE

                             Version 1.0

                              11/04/2010

                          Copyright (C) 2010
                          By Rudolph R. Loew


This Package contains the Patched System Files and SATA INF Files to support
the following features.

1. Large Sector Size support up to 32KB per Sector in DOS.
2. Large Sector Size support up to 4KB per Sector in Windows 98SE.
3. 256 Sector (128KB to 1MB/8MB) Cluster Size support for DOS and Windows.
4. Full 48-Bit LBA Addressing Support for Windows 98SE.
5. Support for 40-Bit Partition Addresses (RFDISK ExtMBR Feature).
6. Boot DOS using any or all above Features.
7. Patched Partitioning bug when using Multiple Primary Partitions.
8. Native Mode support for SATA Controllers for Windows 98SE.
9. Generic Drivers for RAID and RAID/AHCI SATA/PATA Controllers.
10. Driver for SI 3512 SATA Controller.

The Patch files are based on the most recent Versions of the Windows 98SE
files for the English Version.



INSTALLATION

To Install the full Package run the INSTALL.BAT Script using the following
Syntax:

INSTALL WinDir

Where "WinDir" is the Path to the Windows Folder (ex. C:\WINDOWS).



UNINSTALL

To Uninstall the full Package run the UNINST.BAT Script using the following
Syntax:

UNINST WinDir

Where "WinDir" is the Path to the Windows Folder (ex. C:\WINDOWS).



PARTIAL INSTALLATIONS

To Install or Uninstall only the Windows Patches use:

INSTALLW WinDir
or
UNINSTW WinDir

To Install or Uninstall only the DOS Patches use:

INSTALLD DOSDir
or
UNINSTD DOSDir

where DOSDir is the Path to the DOS Folder that contains the DBLBUFF.SYS and
SMARTDRV.EXE Programs.



You will need to reboot for the Patches to take effect.


IMPORTANT: The DOS ATTRIB.EXE Command must be in the current PATH to update
           IO.SYS for the Full or DOS Patch Installation. Copy the ATTRIB.EXE
           to the current Directory otherwise.

           If you have an AHCI Only SATA Controller in your Computer, you
           must remove the ATA0106.INF File from your WINDOWS\INF Folder after
           you Install the Patch and before you Reboot.
