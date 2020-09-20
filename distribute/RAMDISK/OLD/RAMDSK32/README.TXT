        PRELIMINARY MANUAL FOR 32-BIT NON-XMS RAMDISKS VERSION 1.0



This Package contains all three versions of my NON-XMS 32-Bit RAMDISK.

The differences between them are the way they switch to Priviledged Mode
when running in Windows.

You are free to experiment with the different versions and E-Mail me any
comments. I plan to choose one to promote and offer the others on request.
The filenames RAMDSK30.COM and RAMDSK3S.COM may change in later versions.

All three versions can be run simultaneously.
Multiple instances of any 32-Bit RAMDISK can be run simultaneously.



INSTALLATION:

Place the RAMDSKxx.COM file in a known location.
Add a line to your AUTOEXEC.BAT File to run the RAMDISK Program.
Do not use LOADHIGH or LH.

The command Syntax is:

RAMDSKxx Size
or
RAMDSKxx X: Size

Size is the size of the RAMDISK in KB.
X: is the Drive letter to be assigned to the RAMDISK.

NOTE: Letters must be in ascending order

Install the Hook Program according to the instructions for the specific
version.

Only one instance of the Hook Program is required for a given version
regardless of the number of RAMDISKs of the corresponding version.

If you want Windows to recognize the RAMDISK as a RAM DISK rather than a
Hard Drive, add the following line to your AUTOEXEC.BAT file after the
RAMDISK Command:

LABEL X: MS-RAMDRIVE

If you intend to use the RAMDISK for Swapping, do not use MS-RAMDRIVE as a
label.



VERSIONS


RAMDSK32

This version uses a Hook added to the Exception Handler in Windows.
This is currently my preferred choice.

PROS:

No modifications to DOS.
Compatible with Windows ME.
Hook can be used by both 16-Bit and 32-Bit Programs.
Hook can be integrated into RAM Limitation Patch.
Works with all CPUs.

CONS:

Modifies Windows.
Installation more complex.
Separate Hook required for each Windows SYSTEM.INI File.
Hook cannot be integrated into RAMDISK Program.
RAM Limitation Patch integrated version slightly reduces size of a system
stack.

HOOK INSTALLATION:

Place PROTHOOK.VXD in Windows\SYSTEM Directory.
Add the following line to the [386Enh] section of your SYSTEM.INI File:

device=prothook.vxd


RAMDSK3S

This version uses the SYSENTER command as a Hook to Priviledged Mode.

PROS:

No modifications to Windows.
No modifications to DOS in most cases.
Simpler Installation.
Hook can be used by both 16-Bit and 32-Bit Programs.
One Hook required per CONFIG.SYS File.

CONS:

Not Compatible with Windows ME without using DDO.
Hook cannot be integrated into RAM Limitation Patch.
Hook cannot be integrated into RAMDISK Program.
Requires Pentium Class CPU or better.

HOOK INSTALLATION:

Place SYSENTER.SYS in a known location.
Add the following line to your CONFIG.SYS File:

device=<path>SYSENTER.SYS

This line should be placed first and MUST be before EMM386 if used.

NOTE: Diagnostics will report that this driver fails to load. This is normal.


RAMDSK30

This version uses the Windows Breakpoint Coded as a Hook to Priviledged Mode.

PROS:

No modifications to Windows.
Simpler Installation.
One Hook required per AUTOEXEC.BAT File.
Hook can be integrated into RAMDISK Program.
Works with all CPUs.

CONS:

Hook cannot be used by 32-Bit Programs.
DOS RAM is modified in areas not proven to be unused.
Modifications or Updates to Windows may break the Hook.
Not Compatible with Windows ME unless integrated into RAMDISK.
Hook cannot be integrated into RAM Limitation Patch.

HOOK INSTALLATION:

Place BKPTHOOK.COM in a known location.
Add the following line to your AUTOEXEC.BAT File:

<path>BKPTHOOK

This line MUST be placed before any RAMDISK30 lines.

