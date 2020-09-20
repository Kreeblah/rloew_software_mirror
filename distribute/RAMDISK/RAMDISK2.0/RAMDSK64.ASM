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
        MOV     BYTE PTR CS:[ERFLG],0
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
ERRORX: MOV     AH,81H
	STC
	JMP     SHORT EXIT1
EXIT:   MOV     AL,CS:[ERFLG]
        AND     AL,AL
        JNZ     ERRORX
        MOV     AH,1
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
        MOV     CX,35H
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
        AND     ECX,0FFFFH
        MOV     EAX,DS:[SECS]
        SUB     EAX,EDX
        JC      RANGE
        SUB     EAX,ECX
        JC      RANGE
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
        JNC     OKXFER
RANGE:  POP     ES
        JMP     ERROR3
OKXFER: MOVZX   EAX,WORD PTR DS:[IOSIZE]
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

XFER:   PUSH    DS              ;AH=MODE AL=LEN ES:BX=DATA [SECTOR]
        PUSHAD
        PUSH    CS
        POP     DS
        XOR     ECX,ECX
        MOV     CX,ES
        SHL     ECX,4
        MOVZX   EBX,BX
        ADD     ECX,EBX
        XOR     EDI,EDI
        XOR     EBP,EBP
        MOV     EDX,DS:[SECTOR]
        SHLD    EBP,EDX,9
        SHL     EDX,9
        ADD     EDX,DS:[MBASE]
        ADC     EBP,DS:[MBASE+4]
        CMP     AH,3
        JNZ     WRITE1
        XCHG    ECX,EDX
        XCHG    EDI,EBP
WRITE1: MOV     SI,OFFSET EXARG
        MOV     DS:[SI],EDX
        MOV     DS:[SI+4],EBP
        MOV     DS:[SI+8],ECX
        MOV     DS:[SI+12],EDI
        MOVZX   EDX,AL
        SHL     EDX,9
        MOV     DS:[SI+16],EDX
        MOV     AL,AH
        DEC     AL
        MOV     AH,0
        SHL     EAX,16
        MOV     AX,4C52H
        INT     15H
        JNC     GDXFER
        TEST    BYTE PTR DS:[HOOKFL],1
        JNZ     VLP
        MOV     DX,OFFSET NOHOOK
        MOV     AH,9
        INT     21H
        MOV     AH,0
        INT     16H
        MOV     BYTE PTR CS:[HOOKFL],1
VLP:    STC
GDXFER: POPAD
        POP     DS
        RET

VECTOR  DW      INIT,MEDIA,BLDBPB,ERROR3,READ,NODATA,EXIT,EXIT
	DW      WRITE,WRITE,EXIT,EXIT

HDROFF  DW      0
HDRSEG  DW      0

SECS    DD      0
SECTOR  DD      0
DRIVE   DB      0FFH
IOREQ   DB      0
IOSIZE  DW      0
MBASE   DD      0,0
ARGPTR  DD      0
EXVAL   DW      0
ERFLG   DB      0
EXARG   DD      0,0,0,0,0,0

BPBTAB  DW      SECSIZ     ;One Instance

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

DRV32   DB      80H,0,29H
SIG132  DW      0
SIG232  DW      0
LAB32   DB      '           '
FTYPE3  DB      'FAT32   '
BCODE3: RET
        DB      0

FATSZ3  DD      0       ;Set
        DD      0,2,1,0,0,0

DPB     DB      0,0,0,2,0,0,1,0,1,0,2,0,0,0,0,0
        DB      0,0,0,0,1,0,0,0F8H,0FFH,0FFH,0FFH,0FFH,0FFH,0,0,0FFH
        DB      0FFH
        DB      1CH DUP(0)

NOHOOK  DB      13,10,'PROTECTED MODE HOOK REQUIRED TO RUN PROPERLY IN WINDOWS',13,10,13,10,'PRESS ANY KEY TO CONTINUE',13,10,13,10,24H
HOOKFL  DB      0

BUFFER  DW      BUFFER+2

        DB      200H DUP(0)

ERR1:   MOV     DX,OFFSET MESS1
        JMP     REPORT
ERR2:   MOV     DX,OFFSET MESS2
        JMP     REPORT
ERR3:   MOV     DX,OFFSET MESS3
        JMP     REPORT
ERR4:   MOV     DX,OFFSET MESS4
REPORT: PUSH    CS
        POP     DS
        MOV     AH,9
        INT     21H
        JMP     ERROR3

MESS1   DB      'HIMEMEX DRIVER NOT FOUND',13,10,24H
MESS2   DB      'NOT ENOUGH FREE MEMORY',13,10,24H
MESS3   DB      'DRIVE TOO SMALL FOR FAT16',13,10,24H
MESS4   DB      'MAXIMUM DRIVE SIZE IS 2020GiB',13,10,24H

START:  MOV     AH,0
        MOV     SI,81H
S1:     LODSB
S4:     CMP     AL,20H
        JZ      S1
        CMP     AL,61H
        JC      S2
        SUB     AL,20H
S2:     CMP     AL,42H
        JC      S5
        CMP     AL,5BH
        JNC     S5
        SUB     AL,41H
        MOV     AH,AL
S3:     LODSB
        CMP     AL,21H
        JNC     S3
        JMP     S4
S5:     CMP     AL,41H
        JZ      BADLTR
        DEC     SI
        MOV     WORD PTR CS:[REQ+12H],SI
        MOV     WORD PTR CS:[REQ+14H],DS
        PUSH    AX
        MOV     AH,52H
        INT     21H
        POP     AX
        AND     AH,AH
        JNZ     YESLTR
        CALL    FNDLTR
        JC      BADLTR
YESLTR: CMP     AH,ES:[BX+21H]
        JNC     BADLTR
        MOV     CS:[DPB],AH
        MOV     WORD PTR CS:[DPB+15H],CS
        CALL    GETLTR
        JNZ     BADLTR
        PUSH    DS
        PUSH    ES
        PUSH    BX
        PUSH    SI
        PUSH    CS
        POP     ES
        MOV     BX,OFFSET REQ
        PUSH    CS
        CALL    STRAT
        PUSH    CS
        CALL    ENTRY
        TEST    BYTE PTR ES:[BX+4],80H
        POP     SI
        POP     BX
        POP     ES
        POP     DS
        JNZ     FAILED
        MOV     AL,CS:[DPB]
        INC     AL
        CMP     ES:[BX+20H],AL
        JNC     INRNG
        MOV     ES:[BX+20H],AL
INRNG:  MOV     AX,ES:[BX+22H]
        MOV     WORD PTR CS:[BASE],AX
        MOV     AX,ES:[BX+24H]
        MOV     WORD PTR CS:[BASE+2],AX
        MOV     ES:[BX+22H],OFFSET BASE
        MOV     ES:[BX+24H],CS
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

FNDLTR: LDS     SI,ES:[BX+16H]
        MOVZX   CX,BYTE PTR ES:[BX+21H]
        MOV     AH,0
FNDLP:  CMP     WORD PTR DS:[SI+43H],0
        JNZ     FNDIT
        RET
FNDIT:  ADD     SI,58H
        INC     AH
        LOOP    FNDLP
        STC
        RET

GETLTR: LDS     SI,ES:[BX+16H]
        MOVZX   AX,AH
        MOV     CX,58H
        MUL     CX
        ADD     SI,AX
        CMP     WORD PTR DS:[SI+43H],0
        RET

BADLTR: PUSH    CS
        POP     DS
        MOV     DX,OFFSET BADLT
        MOV     AH,9
        INT     21H
FAILED: MOV     AX,10
        RET

INIT:   LDS     BX,DWORD PTR DS:[HDROFF]
        MOV     EAX,DS:[BX+12H]
        MOV     CS:[ARGPTR],EAX
        PUSH    CS
        POP     DS
        MOV     AH,2AH
        INT     21H
        SUB     CX,1980
        SHL     CX,4
        ADD     CL,DH
        SHL     CX,5
        ADD     CL,DL
        MOV     DS:[SIG1],CX
        MOV     DS:[SIG132],CX
        MOV     AH,2CH
        INT     21H
        MOVZX   BX,CH
        SHL     BX,6
        ADD     BL,CL
        SHL     BX,5
        SHR     DH,1
        ADD     BL,DH
        MOV     DS:[SIG2],BX
        MOV     DS:[SIG232],BX
        MOV     EBX,-1
        MOV     EAX,1004C52H
        INT     15H
        CMP     EBX,-1
        JZ      ERR1
        XOR     ECX,ECX
        LDS     SI,CS:[ARGPTR]
        XOR     EAX,EAX
ARG1:   LODSB
        CMP     AL,30H
        JC      ARG1E
        CMP     AL,3AH
        JNC     ARG1E
        SUB     AL,30H
        SHL     ECX,1
        MOV     EBX,ECX
        SHL     EBX,2
        ADD     ECX,EBX
        ADD     ECX,EAX
        JMP     ARG1
ARG1E:  CMP     ECX,7FC00000H
        JNC     ERR4
        PUSH    CS
        POP     DS
        PUSH    CS
        POP     ES
        AND     ECX,ECX
        JZ      GETMAX
        XOR     EBX,EBX
        SHLD    EBX,ECX,10
        SHL     ECX,10
        JMP     DEFLT
GETMAX: MOV     AH,1
        SHL     EAX,16
        MOV     AX,4C52H
        INT     15H
        MOV     EBX,ESI
        MOV     ECX,EDI
DEFLT:  MOV     EAX,3004C52H
        INT     15H
        JC      ERR2
        MOV     DS:[MBASE+4],ESI
        MOV     DS:[MBASE],EDI
        SHRD    ECX,EBX,9
        MOV     DS:[NUMSEC],ECX
        MOV     DS:[SECS],ECX
        CMP     ECX,3FFE21H
        JC      FAT16
        MOV     EAX,ECX
        MOV     CX,80AH
        CMP     EAX,1000000H
        JC      SET32
        MOV     CX,100BH
        CMP     EAX,2000000H
        JC      SET32
        MOV     CX,200CH
        CMP     EAX,4000000H
        JC      SET32
        MOV     CX,400DH
SET32:  MOV     DS:[CLUSIZ],CH
        SUB     EAX,101AH
        SHR     EAX,CL
        MOV     DS:[FATSZ3],EAX
        MOV     WORD PTR DS:[FATOFF],32
        MOV     WORD PTR DS:[DIRSIZ],0
        MOV     BYTE PTR DS:[BOOT+1],58H
        LEA     SI,FATSZ3
        LEA     DI,DRV
        MOV     CX,0EH
        REP     MOVSW
        XOR     EBX,EBX
        MOV     DS:[SECTOR],EBX
        LEA     SI,BOOT
        MOV     DI,DS:[BUFFER]
        PUSH    DI
        MOV     BX,DI
        MOV     CX,2EH
        REP     MOVSW
        XOR     AX,AX
        MOV     CX,0D1H
        REP     STOSW
        MOV     AX,0AA55H
        STOSW
        POP     DI
        MOV     AX,301H
        CALL    XFER
        CALL    CLEAR
        XOR     EDX,EDX
        MOV     EAX,DS:[NUMSEC]
        MOV     ECX,DS:[FATSZ3]
        SUB     EAX,ECX
        SUB     EAX,32
        MOVZX   ECX,DS:[CLUSIZ]
        DIV     ECX
        DEC     EAX
        MOV     DWORD PTR [DI],41615252H
        MOV     DWORD PTR [DI+1E4H],61417272H
        MOV     DWORD PTR [DI+1E8H],EAX
        MOV     DWORD PTR [DI+1ECH],2
        MOV     WORD PTR [DI+1FEH],0AA55h
        INC     DWORD PTR DS:[SECTOR]
        MOV     AX,301H
        CALL    XFER
        CALL    CLEAR
        MOV     ECX,1EH
        CALL    FILL
        MOV     ECX,DS:[FATSZ3]
        MOVZX   EAX,DS:[CLUSIZ]
        ADD     ECX,EAX
        MOV     BX,DS:[BUFFER]
        MOV     EAX,0FFFFFFFH
        MOV     [BX+4],EAX
        MOV     [BX+8],EAX
        MOV     AL,0F8H
        MOV     [BX],EAX
        CALL    FILL
        JMP     FATX
FAT16:  CMP     ECX,1027H
        JC      ERR3
        MOV     BL,64
        MOV     EAX,ECX
        SUB     EAX,289
        SUB     ECX,49
CADJ:   CMP     EAX,1FFE80H
        JNC     CADJ1
        CMP     BL,1
        JZ      CADJ1
        SHR     BL,1
        ADD     EAX,EAX
        ADD     ECX,ECX
        JMP     CADJ
CADJ1:  MOV     DS:[CLUSIZ],BL
        ADD     ECX,3FFFH
        SHR     ECX,14
        MOV     DS:[FATSIZ],CX
        XOR     EBX,EBX
        MOV     DS:[SECTOR],EBX
        LEA     SI,BOOT
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
        CALL    CLEAR
        MOVZX   ECX,DS:[FATSIZ]
        ADD     ECX,20H
        MOV     BX,DS:[BUFFER]
        MOV     DWORD PTR [BX],0FFFFFFF8H
        CALL    FILL
FATX:   LDS     BX,DWORD PTR DS:[HDROFF]
	MOV     BYTE PTR DS:[BX+0DH],1
	MOV     WORD PTR DS:[BX+12H],OFFSET BPBTAB
	MOV     DS:[BX+14H],CS
        MOV     DX,CS:[BUFFER]
	ADD     DX,200H
	MOV     DS:[BX+0EH],DX
	MOV     DS:[BX+10H],CS
        JMP     EXIT

FILL:   INC     DWORD PTR DS:[SECTOR]
        MOV     AX,301H
        MOV     BX,DS:[BUFFER]
        CALL    XFER
        XOR     EAX,EAX
        MOV     [BX],EAX
        MOV     [BX+4],EAX
        MOV     [BX+8],EAX
        DEC     ECX
        JNZ     FILL
        RET

CLEAR:  PUSH    DI
        MOV     DI,DS:[BUFFER]
        XOR     AX,AX
        MOV     CX,100H
        REP     STOSW
        POP     DI
        RET

GOOD    DB      'R. LOEW 64-Bit HIMEMEX RAMDISK  Ver 2.0',13,10,'Copyright (C) 2008-2013,  All Rights Reserved.',13,10,13,10
        DB      'MOUNTED ON DRIVE '
GOOD1   DB      0,':',13,10,13,10,24H
BADLT   DB      'INVALID DRIVE LETTER',13,10,24H

REQ     DB      18H DUP(0)

CODE    ENDS
	END
