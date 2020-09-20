         PRELIMINARY INSTALLATION MANUAL FOR TBPLUS PATCH PACKAGE


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
9. Generic Drivers for RAID and AHCI SATA/PATA Controllers.
10. Driver for SI 3512 SATA Controller.

The Patch files are based on the most recent Versions of the Windows 98SE
files for the English Version.



INSTALLATION

To Install this Package run the INSTALL.BAT Script using the following Syntax:

INSTALL Windir

Where "Windir" is the Path to the Windows Folder (ex. C:\WINDOWS).



UNINSTALL

To Uninstall this Package run the UNINST.BAT Script using the following Syntax:

UNINST Windir

Where "Windir" is the Path to the Windows Folder (ex. C:\WINDOWS).



You will need to reboot for the Patches to take effect.
