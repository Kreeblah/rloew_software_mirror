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
        JNC     OKXFER
        POP     ES
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
        MOV     EBP,DS:[MBASE+4]
        MOV     EDX,DS:[SECTOR]
        SHL     EDX,9
        ADD     EDX,DS:[MBASE]
        ADC     EBP,0
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
        MOV     BX,OFFSET EXPTR
        CALL    FAR PTR [BX]
        JNC     GDXFER
        TEST    BYTE PTR DS:[HOOKFL],1
        JNZ     VLP
        PUSH    DX
        MOV     DX,OFFSET NOHOOK
        MOV     AH,9
        INT     21H
        MOV     AH,0
        INT     16H
        POP     DX
        MOV     BYTE PTR CS:[HOOKFL],1
VLP:    STC
GDXFER: POPAD
        POP     DS
        RET

VECTOR  DW      INIT,MEDIA,BLDBPB,ERROR3,READ,NODATA,EXIT,EXIT
	DW      WRITE,WRITE,EXIT,EXIT

HDROFF  DW      0
HDRSEG  DW      0

SECTOR  DD      0
DRIVE   DB      0FFH
IOREQ   DB      0
IOSIZE  DW      0
MBASE   DD      0,0
ARGPTR  DD      0
EXVAL   DW      0
ERFLG   DB      0
EXPTR   DD      0
EXARG   DD      0,0,0,0,0,0

BPBTAB  DW      SECSIZ     ;One Instance

BOOT:   JMP     SHORT BCODE
        NOP
IDENT   DB      'RLOEW 32'
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
MESS4   DB      'MAXIMUM DRIVE SIZE IS 4193664 KB',13,10,24H

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
        MOV     AX,3D00H
        MOV     CL,0
        MOV     DX,OFFSET HIMEMEX
        INT     21H
        JC      ERR1
        MOV     BX,AX
        MOV     AH,3FH
        MOV     CX,4
        MOV     DX,OFFSET EXPTR
        INT     21H
        JC      ERR1
        MOV     AH,3EH
        INT     21H
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
ARG1E:  CMP     ECX,3FFD81H
        JNC     ERR4
        SHL     ECX,10
        PUSH    CS
        POP     DS
        AND     ECX,ECX
        JNZ     DEFLT
        MOV     AH,1
        MOV     BX,OFFSET EXPTR
        CALL    FAR PTR [BX]
        MOV     ECX,EDI
        AND     ESI,ESI
        JZ      DEFLT
        MOV     ECX,0FFF60000H
DEFLT:  MOV     AX,300H
        XOR     EBX,EBX
        MOV     SI,OFFSET EXPTR
        CALL    FAR PTR [SI]
        JC      ERR2
        MOV     CS:[MBASE+4],ESI
        MOV     CS:[MBASE],EDI
        MOV     EAX,ECX
        CMP     EAX,0FFF60000H
	JC      SIZEOK
        MOV     EAX,0FFF60000H
SIZEOK: ADD     EAX,1FFH
        SHR     EAX,9
        CMP     EAX,400001H
        JNC     NOT2GB
        CMP     EAX,3FFE21H
        JC      NOT2GB
        MOV     EAX,3FFE21H
NOT2GB: CMP     EAX,1027H
        JC      ERR3
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
        PUSH    CS
        POP     ES
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

GOOD    DB      'R. LOEW 64-Bit HIMEMEX RAMDISK  Ver 1.2',13,10,'Copyright (C) 2008-2009,  All Rights Reserved.',13,10,13,10
        DB      'MOUNTED ON DRIVE '
GOOD1   DB      0,':',13,10,13,10,24H
BADLT   DB      'INVALID DRIVE LETTER',13,10,24H
HIMEMEX DB      'HIMEMEX0',0

REQ     DB      18H DUP(0)

CODE    ENDS
	END
