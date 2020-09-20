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

INIT:   LDS     BX,DWORD PTR DS:[HDROFF]
        MOV     EAX,DS:[BX+12H]
        MOV     CS:[ARGPTR],EAX
        MOV     AX,4309H
        INT     2FH
        CMP     AL,43H
        JNZ     ERR1
        MOV     CX,ES:[BX+2]
        MOVZX   EAX,BYTE PTR ES:[BX+1]
        MOV     ESI,EAX
        LES     BX,ES:[BX+4]
        XOR     DI,DI
        XOR     EDX,EDX
SCAN:   CMP     BYTE PTR ES:[BX],1
        JNZ     SCANSK
        MOV     EAX,ES:[BX+2]
        ADD     EAX,ES:[BX+6]
        CMP     EAX,EDX
        JC      SCANSK
        MOV     DI,BX
        MOV     EDX,EAX
SCANSK: ADD     EBX,ESI
        LOOP    SCAN
        AND     DI,DI
        JZ      ERR2
        XOR     ECX,ECX
        LDS     SI,CS:[ARGPTR]
        XOR     EAX,EAX
        MOV     BP,0
        LODSB
        CMP     AL,2DH
        JNZ     ARG1A
        MOV     BP,AX
ARG1:   LODSB
ARG1A:  CMP     AL,30H
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
ARG1E:  AND     ECX,ECX
        JZ      ERR3
        AND     BP,BP
        JZ      PLUS
        SUB     EDX,ECX
        JBE     ERR5
        MOV     ECX,EDX
PLUS:   CMP     ECX,ES:[DI+6]
        JNC     ERR6
        MOV     EAX,ES:[DI+2]
        ADD     EAX,ES:[DI+6]
        SUB     EAX,ECX
        MOV     ESI,ECX
        SHL     EAX,10
        MOV     CS:[MBASE],EAX
        MOV     EAX,ECX
        SHL     EAX,10
	PUSH    CS
	POP     DS
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
        SUB     ES:[DI+6],ESI
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
        XOR     EAX,EAX
        MOV     AX,CS
        MOVZX   EBX,WORD PTR DS:[BUFFER]
        SHL     EAX,4
        ADD     EAX,EBX
        MOV     DS:[MBUFF],EAX
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

VXFER:  MOV     CX,100H
RXFER:  MOV     DWORD PTR CS:[GDT+12H],ESI
        MOV     DWORD PTR CS:[GDT+1AH],EDI
        PUSH    ES
        PUSH    CS
        POP     ES
        MOV     SI,OFFSET GDT
        MOV     AL,CS:[GDT+15H]
        MOV     CS:[GDT+17H],AL
        MOV     AL,CS:[GDT+1DH]
        MOV     CS:[GDT+1FH],AL
        MOV     AX,8793H
        MOV     CS:[GDT+15H],AL
        MOV     CS:[GDT+1DH],AL
        INT     15H
        AND     AH,AH
        JZ      ENDEX
        MOV     BYTE PTR CS:[ERFLG],0CH
ENDEX:  POP     ES
        RET

VMODE:  MOV     DX,SI
        MOV     EBP,ECX
        TEST    BYTE PTR CS:[HOOKFL],1
        JNZ     VLP
        MOV     AX,1600H
        INT     2FH
        AND     AL,AL
        JZ      VLP
        PUSH    CS
        POP     DS
        PUSH    DX
        MOV     DX,OFFSET NOHOOK
        MOV     AH,9
        INT     21H
        MOV     AH,0
        INT     16H
        POP     DX
        MOV     BYTE PTR CS:[HOOKFL],1
                                ;DH=MODE DL=LEN ES:BX=DATA EBP=SECOFF [MBUFF]
VLP:    CMP     DH,2
        JZ      VRD
        PUSH    ES
        POP     DS
        PUSH    CS
        POP     ES
        MOV     SI,BX
        MOV     DI,CS:[BUFFER]
        MOV     CX,80H
        REP     MOVSD
        PUSH    DS
        POP     ES
        MOV     ESI,CS:[MBUFF]
        MOV     EDI,EBP
        CALL    VXFER
        JMP     VRDWR
VRD:    MOV     ESI,EBP
        MOV     EDI,CS:[MBUFF]
        CALL    VXFER
        MOV     SI,CS:[BUFFER]
        MOV     DI,BX
        MOV     CX,80H
        DB      2EH
        REP     MOVSD
VRDWR:  ADD     EBP,200H
        ADD     BX,200H
        DEC     DL
        JNZ     VLP
        JMP     ENDPRO

REALM:  SMSW    AX
        AND     AL,1
        JNZ     VMODE
        MOV     DX,SI
        MOV     EBX,EBP
        MOV     EBP,ECX
                                ;DH=MODE DL=LEN EBX=DATA EBP=SECOFF 
        MOV     CH,DL
        MOV     CL,0
        MOV     ESI,EBP
        MOV     EDI,EBX
        CMP     DH,2
        JZ      RRD
        XCHG    ESI,EDI
RRD:    CALL    RXFER
ENDPRO: POPAD
        POP     DS
	RET

XFER:   PUSH    DS              ;AH=MODE AL=LEN ES:BX=DATA [SECTOR]
        PUSHAD
        MOV     ECX,DS:[SECTOR]
        SHL     ECX,9
        ADD     ECX,DS:[MBASE]
        MOV     SI,AX
        XOR     EBP,EBP     
        MOV     BP,ES
        SHL     EBP,4
	MOVZX   EAX,BX
        ADD     EBP,EAX
	MOV     EAX,52524C4CH
	MOV     EAX,CR0
	NOP
        JMP     SHORT REALM
        JMP     SHORT ENDPRO
                                ;SI=MODE:LEN ECX=SEC OFF EBP=DATA
                                ;Following Code Inverted
        JMP     SHORT HOP
        DD      17 DUP(0)
HOP:    MOV     BX,SI
        MOV     SI,CX
        PUSH    AX
        PUSH    SI
        MOV     SI,444H
        DW      0FF80H
        MOV     DI,AX
        ADD     DI,2       
        MOV     AX,CX
        MOV     CX,17
        DW      0          
        REP     MOVSW
        MOV     DI,444H
        DW      0FF80H
        AND     AX,0F000H
        DW      0FFFFH
        DB      66H
        OR      AX,267H
        MOV     CX,17
        DW      0
H1:     STOSW
        ADD     AX,1000H
        DW      0
        LOOP    H1
        MOV     EAX,CR3
        MOV     CR3,EAX
        POP     SI
        AND     SI,0FFFH
        DW      0
        OR      SI,1000H
        DW      11H
        MOV     DI,BP
        XOR     CX,CX
        MOV     CH,BL
        SHR     CX,1
	CMP     BH,2
        JZ      PRD
        XCHG    SI,DI
PRD:    REP     MOVSW
        CMP     BH,2
        JZ      PEND
        WBINVD
PEND:   POP     AX
        MOV     DI,444H
        DW      0FF80H
        MOV     SI,AX
        ADD     SI,2
        MOV     CX,17
        DW      0
        REP     MOVSW
        MOV     EAX,CR3
        MOV     CR3,EAX
        IRET

VECTOR  DW      INIT,MEDIA,BLDBPB,ERROR3,READ,NODATA,EXIT,EXIT
	DW      WRITE,WRITE,EXIT,EXIT

HDROFF  DW      0
HDRSEG  DW      0

SECTOR  DD      0
DRIVE   DB      0FFH
IOREQ   DB      0
IOSIZE  DW      0
MBASE   DD      0
MBUFF   DD      0
ARGPTR  DD      0
EXVAL   DW      0
ERFLG   DB      0

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

GDT     DB      16 DUP(0)
        DB      0FFH,0FFH,0,0,0,0,0,0
        DB      0FFH,0FFH,0,0,0,0,0,0
        DB      16 DUP(0)

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
        JMP     REPORT
ERR5:   MOV     DX,OFFSET MESS5
        JMP     REPORT
ERR6:   MOV     DX,OFFSET MESS6
REPORT: PUSH    CS
        POP     DS
        MOV     AH,9
        INT     21H
        JMP     ERROR3

MESS1   DB      'HIMEM HANDLE TABLE NOT FOUND',13,10,24H
MESS2   DB      'NO FREE MEMORY',13,10,24H
MESS3   DB      'DISK SIZE INVALID OR NOT SPECIFIED',13,10,24H
MESS4   DB      'DRIVE TOO SMALL FOR FAT16',13,10,24H
MESS5   DB      'DRIVE START ADDRESS ABOVE TOP OF MEMORY',13,10,24H
MESS6   DB      'NOT ENOUGH FREE MEMORY',13,10,24H

START:  MOV     AH,0
        MOV     SI,81H
S1:     LODSB
S4:     CMP     AL,20H
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
S3:     LODSB
        CMP     AL,21H
        JNC     S3
        JMP     S4
S5:     DEC     SI
        MOV     WORD PTR CS:[REQ+12H],SI
        MOV     WORD PTR CS:[REQ+14H],DS
        PUSH    AX
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

GOOD    DB      'R. LOEW NON-XMS RAMDISK  Ver 1.0 (PH)  Copyright (C) 2008,  All Rights Reserved.',13,10,13,10
        DB      'MOUNTED ON DRIVE '
GOOD1   DB      0,':',13,10,13,10,24H
BADLT   DB      'INVALID DRIVE LETTER',13,10,24H

REQ     DB      18H DUP(0)

CODE    ENDS
	END
