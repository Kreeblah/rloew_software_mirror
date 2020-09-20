        PRELIMINARY MANUAL FOR 64-BIT NON-XMS RAMDISKS VERSION 1.0



This Package contains all six versions of my NON-XMS 64-Bit RAMDISK.

The differences between them are the way they switch to Priviledged Mode
when running in Windows and the means to access 64-Bit Memory.

You are free to experiment with the different versions and E-Mail me any
comments. I plan to choose one to promote and offer the others on request.
The filenames may change in later versions.

Only one of these 64-Bit RAMDISKs can be run at a time.
Multiple instances of any 32-Bit RAMDISK can be run simultaneously.



INSTALLATION:

Place the RAMDSKxx.COM file in a known location.
Add a line to your AUTOEXEC.BAT File to run the RAMDISK Program.
Do not use LOADHIGH or LH.

The command Syntax is:

RAMDSKxx
or
RAMDSKxx X:

X: is the Drive letter to be assigned to the RAMDISK.

The RAMDISK will use all 64-Bit RAM up to 4GB.

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


RAMDSK64 and RAMDSKA4

These versions use a Hook added to the Exception Handler in Windows.
RAMDSK64 is currently my preferred choice.

PROS:

No modifications to DOS.
Compatible with Windows ME.
Hook can be used by both 16-Bit and 32-Bit Programs.
Hook can be integrated into RAM Limitation Patch.
RAMDSK64 works with all CPUs.

CONS:

Modifies Windows.
Installation more complex.
Separate Hook required for each Windows SYSTEM.INI File.
Hook cannot be integrated into RAMDISK Program.
RAMDSKA4 requires AMD 64 CPU.
RAM Limitation Patch integrated version slightly reduces size of a system
stack.

HOOK INSTALLATION:

Place PROTHOOK.VXD in Windows\SYSTEM Directory.
Add the following line to the [386Enh] section of your SYSTEM.INI File:

device=prothook.vxd


RAMDSK6S and RAMDSKAS

These versions use the SYSENTER command as a Hook to Priviledged Mode.

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
RAMDKSAS requires AMD 64 CPU.

HOOK INSTALLATION:

Place SYSENTER.SYS in a known location.
Add the following line to your CONFIG.SYS File:

device=<path>SYSENTER.SYS

This line should be placed first and MUST be before EMM386 if used.

NOTE: Diagnostics will report that this driver fails to load. This is normal.


RAMDSK60 and RAMDSKA0

These versions use the Windows Breakpoint Coded as a Hook to Priviledged Mode.

PROS:

No modifications to Windows.
Simpler Installation.
One Hook required per AUTOEXEC.BAT File.
Hook can be integrated into RAMDISK Program.
RAMDSK60 works with all CPUs.

CONS:

Hook cannot be used by 32-Bit Programs.
DOS RAM is modified in areas not proven to be unused.
Modifications or Updates to Windows may break the Hook.
Not Compatible with Windows ME unless integrated into RAMDISK.
Hook cannot be integrated into RAM Limitation Patch.
RAMDKSA0 requires AMD 64 CPU.

HOOK INSTALLATION:

Place BKPTHOOK.COM in a known location.
Add the following line to your AUTOEXEC.BAT File:

<path>BKPTHOOK

This line MUST be placed before the RAMDISK line.



RAMDISK FAMILIES:


The RAMDSK6x family use PSE (Page Size Extensions) to access 64-Bit Memory.

PROS:

Compatible with all 64-Bit Processors.
Can Read/Write to Virtual Memory buffers without copying.

CONS:

Requires setting up Protected Mode and Paging to access Memory.


The RAMDSKAx family use the FSBASE MSR to access 64-Bit Memory.

PROS:

No setup required when running in Real Mode or unmapped Protected Mode.

CONS:

Compatible only with AMD 64 Processors.
Requires buffers when transferring to or from Virtual Memory.
