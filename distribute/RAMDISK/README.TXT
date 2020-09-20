I have enclosed the 64-Bit Versions of the old style RAMDISKs (RAMDSKxx.COM).
They are in the RAMDSK64.ZIP Package.

I have developed a new set of RAMDISKs using a common Memory Allocator/Copier.
I intend to use these RAMDISKs in the future.
They are in the RAMDISK.ZIP Package.

Tou can try them both out. I plan to support only the new set unless you see
a problem with them. I have not published any Demos and no one else has
purchased a copy.

To install the new version, remove SYSENTER.SYS, BKPTHOOK.COM and any
RAMDSKxx.COM entries in CONFIG.SYS and AUTOEXEC.BAT unless you are mixing old
and new. The files can also be removed.
You can leave PROTHOOK.VXD and it's SYSTEM.INI entry.
Then install the new RAMDISKx as directed.

It is possible to mix the old and new but the following limitations apply.

1. The old SYSENTER RAMDISKs (SYSENTER.SYS, RAMDSK3S, RAMDSK6S AND RAMDSKAS)
   cannot be used with the HIMEMEX /S (SYSENTER Method) enabled.
2. Old and new 64-Bit RAMDISKs cannot be used together.
3. Old 32-Bit RAMDISKs will not use Preallocated Memory.


CHANGES FROM THE RAMDSKxx SERIES:

RAMDISKx uses an integrated Memory Manager HIMEMEX.SYS
Only 2 RAMDISK versions are needed.
Duplicated Memory Allocation and Management Code is eliminated.
SYSENTER.SYS and BKPTHOOK.COM no longer needed.
Multiple 64-Bit RAMDISKs are now supported.
Low Memory footprints have been eliminated.
Low Memory modifications are loaded and restored on each access as needed.
Optional Preallocation of RAM is available.
Interrupt 15 Memory Report can be reduced.
EMM386 Virtual I/O Method has been added.
Drive Letter Limitation have been removed.
Failed Install no longer alters system tables.
64-Bit Memory API available for Programs. API is not dependent upon whether
DOS, EMM386 or Windows is running.

Only one method can be used at a time. You cannot mix modes.
FSBASE option (RAMDSKAx) not available.
