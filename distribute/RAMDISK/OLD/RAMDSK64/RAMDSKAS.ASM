	.model tiny
	.586p

CODE    SEGMENT
	ASSUME  CS:CODE
        ORG     100H

BASE    DB      90H              ; Replaced     DW      0FFFFH,0FFFFH
        JMP     START
        DW      2,STRAT,ENTRY
	DB      1,0,0,0,0,0,0,0

STRAT:  MOV     CS:[HDROFF],BX
	MOV     CS:[HDRSEG],ES
RETF_1  PROC    FAR
	RET
RETF_1  ENDP

ENTRY:  CLD
        PUSHAD
	PUSH    DS
	PUSH    ES
	MOV     SI,OFFSET VECTOR
	LDS     BX,DWORD PTR CS:[HDROFF]
	MOV     AL,DS:[BX+1]
	MOV     AH,DS:[BX+0DH]
	MOV     CX,DS:[BX+12H]
	MOV     EDX,DS:[BX+1AH]
	XCHG    DI,AX
	MOV     AL,DS:[BX+2]
	SUB     AH,AH
	ADD     SI,AX
	ADD     SI,AX
	CMP     AL,0BH
	JA      ERROR3
	XCHG    DI,AX
	LES     DI,DWORD PTR DS:[BX+0EH]
	PUSH    CS
	POP     DS
	JMP     WORD PTR DS:[SI]

NODATA: MOV     AH,3
	JMP     SHORT EXIT1
ERROR3: MOV     AL,3
        MOV     AH,81H
	STC
	JMP     SHORT EXIT1
EXIT:   MOV     AH,1
        CLC
EXIT1:  LDS     BX,DWORD PTR CS:[HDROFF]
        MOV     DS:[BX+3],AX
        MOV     CS:[EXVAL],AX
	POP     ES
	POP     DS
        POPAD
        MOV     AX,CS:[EXVAL]
RETF_2  PROC    FAR
	RET
RETF_2  ENDP

INIT:	PUSH    CS
	POP     ES
        IN      AL,92H
        OR      AL,2
        OUT     92H,AL
        OUT     0EBH,AL
	XOR     EBX,EBX
SCAN:   MOV     EAX,0E820H
	MOV     ECX,20H
	MOV     EDX,534D4150H
	MOV     DI,OFFSET MAPBUF
	INT     15H
        JC      ERR1
	CMP     BYTE PTR [DI+16],1
	JNZ     SCAN1
	CMP     DWORD PTR [DI+4],1
	JNZ     SCAN1
	CMP     DWORD PTR [DI],0
	JNZ     SCAN1
        CMP     DWORD PTR [DI+12],0   ;FAT16 Limit <4GB
	JNZ     TOOBIG
	MOV     EAX,[DI+8]
        CMP     EAX,0FFF60000H
	JC      SIZEOK
TOOBIG: MOV     EAX,0FFF60000H
SIZEOK: ADD     EAX,1FFH
        SHR     EAX,9
        CMP     EAX,400001H
        JNC     NOT2GB
        CMP     EAX,3FFE21H
        JC      NOT2GB
        MOV     EAX,3FFE21H
NOT2GB: CMP     EAX,1027H
        JC      ERR4
        MOV     DS:[NUMSEC],EAX
        MOV     BL,128
        MOV     ECX,EAX
        SUB     EAX,289
        SUB     ECX,49
CADJ:   CMP     EAX,3FFD01H
        JNC     CADJ1
        CMP     BL,1
        JZ      CADJ1
        SHR     BL,1
        ADD     EAX,EAX
        ADD     ECX,ECX
        JMP     CADJ
CADJ1:  MOV     DS:[CLUSIZ],BL
        ADD     ECX,7FFFH
        SHR     ECX,15
        MOV     DS:[FATSIZ],CX
        MOV     AH,2AH
        INT     21H
        SUB     CX,1980
        SHL     CX,4
        ADD     CL,DH
        SHL     CX,5
        ADD     CL,DL
        MOV     DS:[SIG1],CX
        MOV     AH,2CH
        INT     21H
        MOVZX   BX,CH
        SHL     BX,6
        ADD     BL,CL
        SHL     BX,5
        SHR     DH,1
        ADD     BL,DL
        MOV     DS:[SIG2],BX
        XOR     EAX,EAX
        MOV     AX,CS
        SHL     EAX,4
        MOVZX   EBX,WORD PTR DS:[BUFFER]
        ADD     EBX,EAX
        MOV     DS:[BUFFP],EBX
        XOR     EBX,EBX
        MOV     DS:[SECTOR],EBX
        MOV     BX,OFFSET PMCODE
        ADD     EBX,EAX
        MOV     DS:[PMC],EBX
        XOR     AX,AX
        MOV     DS,AX
        TEST    WORD PTR DS:[19CH],0FFFFH
        PUSH    CS
        POP     DS
        JZ      NOEMM
        MOV     AX,0FFA5H
        INT     67H
        CMP     AH,84H
        JNZ     NOEMM
        MOV     DS:[EMMA1],CX
        MOV     DS:[EMMA2],BX
        JMP     YESEMM
NOEMM:  MOV     BX,OFFSET EMMOFF
        MOV     BYTE PTR [BX],0C3H
        MOV     BX,OFFSET EMMON
        MOV     BYTE PTR [BX],0C3H
YESEMM: LEA     SI,BOOT
        MOV     DI,DS:[BUFFER]
        MOV     BX,DI
        MOV     CX,20H
        REP     MOVSW
        XOR     AX,AX
        MOV     CX,0DFH
        REP     STOSW
        MOV     AX,0AA55H
        STOSW
        MOV     AX,301H
        CALL    XFER
        MOV     DI,DS:[BUFFER]
        XOR     AX,AX
        MOV     CX,100H
        REP     STOSW
        MOV     CX,DS:[FATSIZ]
        CALL    FILL1
        MOV     CX,20H
        CALL    FILL
        LDS     BX,DWORD PTR DS:[HDROFF]
	MOV     BYTE PTR DS:[BX+0DH],1
	MOV     WORD PTR DS:[BX+12H],OFFSET BPBTAB
	MOV     DS:[BX+14H],CS
        MOV     DX,CS:[BUFFER]
	ADD     DX,200H
	MOV     DS:[BX+0EH],DX
	MOV     DS:[BX+10H],CS
        JMP     EXIT
SCAN1:  AND     BX,BX
        JZ      ERR2
	JMP     SCAN

FILL1:  MOV     EAX,0FFFFFFF8H
        MOV     BX,DS:[BUFFER]
        MOV     [BX],EAX
FILL:   INC     DWORD PTR DS:[SECTOR]
        MOV     AX,301H
        MOV     BX,DS:[BUFFER]
        CALL    XFER
        XOR     EAX,EAX
        MOV     [BX],EAX
        LOOP    FILL
        RET

MEDIA:  CMP     AL,DS:[DRIVE]
	JNZ     NEWDRV
	CMP     AH,DS:[DTYPE]
	JNZ     NEWCOD
	MOV     CL,AL
	PUSH    DS
	SUB     AX,AX
	MOV     DS,AX
	MOV     AL,DS:[43FH]
	POP     DS
	MOV     AH,1
	SHL     AH,CL
	TEST    AH,AL
	JZ      NEWDRV
	MOV     AL,1
	JMP     SHORT STATUS
NEWDRV: XOR     AL,AL
	JMP     SHORT STATUS
NEWCOD: MOV     AL,0FFH
STATUS: LDS     BX,DWORD PTR DS:[HDROFF]
	MOV     DS:[BX+0EH],AL
	JMP     EXIT

BLDBPB: MOV     DWORD PTR DS:[SECTOR],0
	PUSH    DS
	POP     ES
        MOV     BX,DS:[BUFFER]
        MOV     AX,201H
        CALL    XFER
        MOV     AL,0F8H
        CMP     WORD PTR [BX+1FEH],0AA55H
        JNZ     NOSIG
        LEA     SI,[BX+0BH]
        MOV     DI,OFFSET SECSIZ
        MOV     CX,19H
        REP     MOVSB
        MOV     AL,DS:[BX+15H]
NOSIG:	LDS     BX,DWORD PTR DS:[HDROFF]
	MOV     DS:[BX+0DH],AL
        MOV     WORD PTR DS:[BX+12H],OFFSET SECSIZ
	MOV     DS:[BX+14H],CS
	JMP     EXIT

READ:   PUSH    AX
	MOV     AL,2
	JMP     SHORT RD_WR

WRITE:  AND     EDX,EDX
        JNZ     WR1
        MOV     AL,0FFH
WR1:    PUSH    AX
	MOV     AL,3
RD_WR:  MOV     DS:[IOREQ],AL
	POP     AX
        AND     CX,CX
        JZ      EXIT
	MOV     DS:[DRIVE],AL
	MOV     BX,DI
        PUSH    ES
IOLOOP: MOV     DS:[SECTOR],EDX
	PUSH    BX
	MOV     AX,ES
	SHR     BX,4
	ADD     AX,BX
	MOV     ES,AX
	POP     BX
	AND     BX,15
	MOV     AX,CX
        CMP     AX,127
        JC      SZOK
        MOV     AX,127
SZOK:   MOV     DS:[IOSIZE],AX
	MOV     AH,DS:[IOREQ]
	CALL    XFER
        MOVZX   EAX,WORD PTR DS:[IOSIZE]
        SUB     CX,AX
	JBE     DONE
        ADD     EDX,EAX
        SHL     AX,9
	ADD     BX,AX
	JNB     IOLOOP
	LDS     BX,DWORD PTR DS:[HDROFF]
	SUB     DS:[BX+12H],CX
DONE:   POP     ES
        JMP     EXIT

REALM:  CALL    EMMOFF
        SMSW    AX
        AND     AL,1
        JZ      NOPROT
        PUSH    CS
        POP     DS
        MOV     DX,OFFSET BADEMM
        MOV     AH,9
        INT     21H
        MOV     AH,0
        INT     16H
        DB      0EBH,0FEH
NOPROT: CLI
	MOV     EAX,ECX
	SHL     EAX,9
	MOV     EDX,1
	MOV     ECX,0C0000100H
	WRMSR
	MOV     ECX,0C0010015H
	RDMSR
	OR      EAX,20000H
	WRMSR
        MOV     AX,SI
        XOR     ECX,ECX
	MOV     CH,AL
	XOR     ESI,ESI
	CMP     AH,2
	JNZ     WR
        MOVZX   EDI,BX
        DB      67H,64H
        REP     MOVSW
	JMP     RDWR
WR:     MOV     AX,ES:[BX]
	MOV     FS:[ESI],AX
	ADD     ESI,2
	ADD     BX,2
	LOOP    WR
	WBINVD
RDWR:	MOV     ECX,0C0010015H
	RDMSR
        AND     EAX,0FFFDFFFFH
	WRMSR
        STI
        CALL    EMMON
ENDPRO: POPAD
	POP     FS
	RET

XFER:   PUSH    FS              ;AH=MODE AL=LEN ES:BS=DATA [SECTOR]
        PUSHAD
        MOV     ECX,DS:[SECTOR]
	MOV     SI,AX
        XOR     EBP,EBP     
        MOV     BP,ES
        SHL     EBP,4
	MOVZX   EAX,BX
        ADD     EBP,EAX
        MOV     EDI,DS:[BUFFP]
        MOV     AX,1600H
        INT     2FH
        AND     AL,AL
        JZ      REALM
        XOR     AX,AX
        MOV     DS,AX
        MOV     DS:[3DCH],OFFSET ENDPRO
        MOV     DS:[3DEH],AX
        MOV     DS:[3E0H],CS
        MOV     DS:[3E2H],AX
        MOV     DWORD PTR DS:[3E4H],23202H
        MOV     DS:[3E8H],SP
        MOV     DS:[3EAH],AX
        MOV     DS:[3ECH],SS
        MOV     DS:[3EEH],AX
        MOV     DS:[3F0H],ES
        MOV     DS:[3F2H],AX
        MOV     DS:[3F4H],CS
        MOV     DS:[3F6H],AX
        MOV     DS:[3F8H],FS
        MOV     DS:[3FAH],AX
        MOV     DS:[3FCH],GS
        MOV     DS:[3FEH],AX
        MOV     EAX,CS:[PMC]
        DB      0FH,34H         ;SYSENTER

                                ;SI=MODE:LEN ECX=SECTOR EDI=BUFFER EBP=DATA
                                ;Following Code Inverted

PMCODE: ADD     SP,3CH          ;Move ESP from 3A0 to 3DC
        DB      66H
        MOV     AX,30H
        MOV     DS,AX
        MOV     ES,AX
        MOV     FS,AX
        MOV     BX,SI
        SHL     CX,9
        MOV     SI,CX
	MOV     CX,15H
	DW      0C001H
	RDMSR
        DB      0DH         ;OR EAX
        DD      20000H
	WRMSR
NEXT:   PUSH    SI
        PUSH    DI
        MOV     AX,SI
	MOV     DX,1
        DW      0
	MOV     CX,100H
	DW      0C000H
	WRMSR
	CMP     BH,2
        JNZ     SHORT PWR
        MOV     EAX,CR0
        DB      25H         ;AND EAX
        DD      7FFFFFFFH
        MOV     CR0,EAX
PRD:	XOR     SI,SI
        MOV     CX,80H
        DW      0
        DB      64H
        REP     MOVSW
        MOV     EAX,CR0
        DB      0DH         ;OR EAX
        DD      80000000H
        MOV     CR0,EAX
        LEA     SI,[BX-200H]
        DW      -1
        MOV     DI,BP
        MOV     CX,80H
        DW      0
        REP     MOVSW
        JMP     SHORT PRDWR
NEXT1:  JMP     SHORT NEXT
PWR:    MOV     SI,BP
        MOV     CX,80H
        DW      0
        REP     MOVSW
        SUB     DI,200H
        DW      0
	XOR     SI,SI
        MOV     EAX,CR0
        DB      25H         ;AND EAX
        DD      7FFFFFFFH
        MOV     CR0,EAX
        MOV     CX,80H
        DW      0
PWR1:   MOV     AX,[BX]
        MOV     FS:[BP+0],AX
        ADD     SI,4
        ADD     DI,4
        LOOP    PWR1
        MOV     EAX,CR0
        DB      0DH         ;OR EAX
        DD      80000000H
        MOV     CR0,EAX
PRDWR:  POP     DI
        POP     SI
        ADD     SI,200H
        DW      0
        ADD     BP,200H
        DW      0
        DEC     BL
        JNZ     SHORT NEXT1
        CMP     BH,2
        JZ      SHORT PEND
        WBINVD
PEND:   MOV     CX,15H
        DW      0C001H
        RDMSR
        DB      25H         ;AND EAX
        DD      0FFFDFFFFH
        WRMSR
        IRET

EMMOFF: MOV     AX,0
        CALL    EMM
        MOV     DS:[EMMSAV],AL
        MOV     AL,1
        JMP     EMM1
EMMON:  MOV     AL,DS:[EMMSAV]
EMM1:   MOV     AH,1
EMM:    PUSHAD
        DB      0FFH,1EH        ;CALL FAR [EMM]
        DW      OFFSET EMMA1
        POPAD
        RET

VECTOR  DW      INIT,MEDIA,BLDBPB,ERROR3,READ,NODATA,EXIT,EXIT
	DW      WRITE,WRITE,EXIT,EXIT

HDROFF  DW      0
HDRSEG  DW      0

SECTOR  DD      0
DRIVE   DB      0FFH
IOREQ   DB      0
IOSIZE  DW      0
EXVAL   DW      0
EMMA1   DW      0
EMMA2   DW      0
EMMSAV  DB      0

BPBTAB  DW      SECSIZ       ;One Instance

BOOT:   JMP     SHORT BCODE
        NOP
IDENT   DB      'RLOEW 64'
SECSIZ  DW      200H
CLUSIZ  DB      0       ;Set
FATOFF  DW      1
FATCNT  DB      1
DIRSIZ  DW      200H
	DW      0      
DTYPE   DB      0F8H
FATSIZ  DW      0       ;Set
TRKSIZ  DW      32
SIDES   DW      128
PRTOFF  DD      0
NUMSEC  DD      0       ;Set
DRV     DB      80H,0,29H
SIG1    DW      0
SIG2    DW      0
LAB     DB      '           '
FTYPE   DB      'FAT16   '
BCODE:  RET
        DB      0

MAPBUF  DD      0,0   ;Buffer is 20 Bytes
LENL    DD      0
LENH    DD      0
        DD      0

DPB     DB      0,0,0,2,0,0,1,0,1,0,2,0,0,0,0,0
        DB      0,0,0,0,1,0,0,0F8H,0FFH,0FFH,0FFH,0FFH,0FFH,0,0,0FFH
        DB      0FFH
        DB      1CH DUP(0)

BADEMM  DB      13,10,'UNABLE TO TURN OFF VIRTUAL MODE MEMORY MANAGER',13,10,13,10,24H

BUFFP   DD      0
PMC     DD      0
BUFFER  DW      BUFFER+2
        DB      512 DUP(0)

ERR1:   MOV     DX,OFFSET MESS1
        JMP     REPORT
ERR2:   MOV     DX,OFFSET MESS2
        JMP     REPORT
ERR4:   MOV     DX,OFFSET MESS4
REPORT: PUSH    CS
        POP     DS
        MOV     AH,9
        INT     21H
        JMP     ERROR3

MESS1   DB      'BIOS MEMORY MAP NOT FOUND',13,10,24H
MESS2   DB      'NO 64-BIT MEMORY',13,10,24H
MESS4   DB      'DRIVE TOO SMALL FOR FAT16',13,10,24H

START:  MOV     AH,0
        MOV     SI,81H
S1:     LODSB
        CMP     AL,20H
        JZ      S1
        CMP     AL,61H
        JC      S2
        SUB     AL,20H
S2:     CMP     AL,43H
        JC      S5
        CMP     AL,5BH
        JNC     S5
        SUB     AL,41H
        MOV     AH,AL
S5:     PUSH    AX
        MOV     AH,52H
        INT     21H
        POP     AX
        AND     AH,AH
        JNZ     YESLTR
        MOV     AH,ES:[BX+20H]
        JMP     GOTLTR
YESLTR: CMP     AH,ES:[BX+20H]
        JC      BADLTR
        CMP     AH,ES:[BX+21H]
        JNC     BADLTR
GOTLTR: MOV     DS:[DPB],AH
        MOV     WORD PTR DS:[DPB+15H],CS
        INC     AH
        MOV     ES:[BX+20H],AH
        PUSH    CS
        POP     ES
        MOV     BX,OFFSET REQ
        PUSH    CS
        CALL    STRAT
        PUSH    CS
        CALL    ENTRY
        TEST    BYTE PTR [BX+4],80H
        JNZ     FAILED
        MOV     AH,52H
        INT     21H
        MOV     AX,ES:[BX+22H]
        MOV     WORD PTR DS:[BASE],AX
        MOV     AX,ES:[BX+24H]
        MOV     WORD PTR DS:[BASE+2],AX
        MOV     ES:[BX+22H],OFFSET BASE
        MOV     ES:[BX+24H],CS
        LDS     SI,ES:[BX+16H]
        MOVZX   AX,BYTE PTR CS:[DPB]
        MOV     CX,58H
        MUL     CX
        ADD     SI,AX
        MOV     BYTE PTR [SI+44H],40H
        MOV     [SI+45H],OFFSET DPB
        MOV     [SI+47H],CS
        MOV     BYTE PTR [SI+4FH],2
        PUSH    CS
        POP     DS
        LES     BX,ES:[BX]
FDEV:   CMP     WORD PTR ES:[BX+19H],0FFFFH
        JZ      FNDDEV
        LES     BX,ES:[BX+19H]
        JMP     FDEV
FNDDEV: MOV     ES:[BX+19H],OFFSET DPB
        MOV     ES:[BX+1BH],CS
        MOV     AL,DS:[DPB]
        ADD     AL,41H
        MOV     DS:[GOOD1],AL
        MOV     DX,OFFSET GOOD
        MOV     AH,9
        INT     21H
        MOV     DX,WORD PTR DS:[REQ+0EH]
        INT     27H

BADLTR: MOV     DX,OFFSET BADLT
        MOV     AH,9
        INT     21H
FAILED: MOV     AX,10
        RET

GOOD    DB      'R. LOEW 64-BIT RAMDISK  Ver 1.0 (A-SE)  Copyright (C) 2008,  All Rights Reserved.',13,10,13,10
        DB      'MOUNTED ON DRIVE '
GOOD1   DB      0,':',13,10,13,10,24H
BADLT   DB      'INVALID DRIVE LETTER',13,10,24H

REQ     DB      18H DUP(0)

CODE    ENDS
	END
