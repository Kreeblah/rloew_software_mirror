        .model tiny
	.586p

INTOFF  EQU     20BH           ;Segment  Offset  of INT 30 Call
PROTCD  EQU     208H           ;Absolute Address of Protected Mode Transfer
INTCOD  EQU     (INTOFF+3B0H)  ;Absolute Address of INT 30 Call

CODE	SEGMENT
	ASSUME	CS:CODE
	ORG	0
 
BASE    DW      0FFFFH,0FFFFH,8800H,STRAT,ENTRY
        DB      'HIMEMEX0'
 
STRAT:  MOV     CS:[HDOFF],BX
	MOV	CS:[HDSEG],ES
        RETF

ENTRY:  PUSHAD
	MOV	SI,OFFSET VECT
	PUSH	DS
	PUSH	ES
	LDS	BX,DWORD PTR CS:[HDOFF]
	MOV	AL,DS:[BX+2]
	SUB	AH,AH
	ADD	SI,AX
	ADD	SI,AX
	CMP	AL,10H
	JNC	ERROR3
	JMP	WORD PTR CS:[SI]

ERROR3:	MOV	AL,3
ERRORX:	MOV	AH,81H
	STC
	JMP	SHORT EXIT1
EXIT:	MOV	AX,100H
EXIT1: 	LDS	BX,DWORD PTR CS:[HDOFF]
	MOV	DS:[BX+3],AX
        POP     ES
	POP	DS
        POPAD
        RETF

OPEN:   MOV     BYTE PTR CS:[RDPTR],0
        MOV     BYTE PTR CS:[WRPTR],0
        MOV     BYTE PTR CS:[VIRT+1],0FFH
        JMP     EXIT

;READ RETURNS:  CMD ENTRY POINT CS:IP, RSVD, RSVDLEN, TOP64.8, RESULT (-1=ERR)
;               RESETS WRITE

READ:   MOV     SI,OFFSET RDDATA
        MOV     CX,DS:[BX+12H]
        LDS     BX,DWORD PTR DS:[BX+0EH]
        MOV     DH,0
        AND     CX,CX
        JZ      EXIT
        MOV     DL,CS:[RDPTR]
        MOV     BYTE PTR CS:[WRPTR],0
        ADD     SI,DX
READ1:  CMP     DL,24
        JNC     EXIT
        MOV     AL,CS:[SI]
        MOV     DS:[BX],AL
        INC     SI
        INC     BX
        INC     DL
        MOV     CS:[RDPTR],DL
        LOOP    READ1
	JMP	EXIT

;WRITE: CMD 0:  MEMCOPY_ARGS.24, AL, 0
;WRITE: CMD 1:  UNUSED.25, 1     SETS RESULT = HIMEM LENGTH
;WRITE: CMD 2:  LEN,UNUSED.20, AL, 2 SETS RESULT = ADDR  (ABS LEN)
;WRITE: CMD 3:  LEN.8,UNUSED.17, 3  ADDR=TOP64.8+100000000
;WRITE: CMD FF: NOP
;               RESETS READ

WRITE:  MOV     SI,OFFSET SRCADDR
        MOV     CX,DS:[BX+12H]
        LDS     BX,DWORD PTR DS:[BX+0EH]
        MOV     DH,0
        AND     CX,CX
        JZ      EXIT
        MOV     DL,CS:[WRPTR]
        MOV     BYTE PTR CS:[RDPTR],0
        ADD     SI,DX
WRITE1: CMP     DL,26
        JNC     EXIT
        MOV     AL,DS:[BX]
        MOV     CS:[SI],AL
        INC     SI
        INC     BX
        INC     DL
        MOV     CS:[WRPTR],DL
        LOOP    WRITE1
        TEST    BYTE PTR CS:[VIRT+1],80H
        JNZ     EXIT
        PUSH    CS
        POP     DS
        MOV     SI,OFFSET SRCADDR
        MOV     AX,WORD PTR DS:[VIRT]
        MOV     BYTE PTR DS:[VIRT+1],0FFH
        PUSH    AX
        MOV     ECX,DS:[SRCADDR]
        MOV     EBX,DS:[SRCADDR+4]
        MOV     DWORD PTR DS:[RES1],-1
        PUSH    CS
        CALL    CMD
        POP     AX
        JC      EXIT
        MOV     CS:[RES1],ECX
        CMP     AH,2
        JNZ     EXIT
        CMP     AL,3
        JZ      EXIT
        MOV     CS:[RES1],ESI
        JMP     EXIT

;AH  0=COPY     DS:SI -> SRC64, DEST64, LEN64  CF=ERROR
;               AL=0 PHYS/PHYS  AL=1 PHYS/VIR  AL=2 VIR/PHYS  AL=3 VIR/VIR
;AH  1=AVAIL    ECX = RES  EDX = RSVD  ESI:EDI = 64-BIT  CF=ERROR
;AH  2=ALLOC32  ECX = LEN  ESI = ADDR          CF=ERROR
;               AL=0 RSVD/DOWN AL=1 DOWN  AL=2 UP  AL=3 ABS  Top Himem Block
;AH  3=ALLOC64  EBX:ECX = LEN  ESI:EDI = ADDR  CF=ERROR      Allocated Down

INT2B:  PUSH    CS
        CALL    CMD
        RETF    2

CMD:    CMP     AH,0
        JZ      XFER
        CMP     AH,1
        JZ      AVAIL
        CMP     AH,2
        JZ      ALL32
        CMP     AH,3
        JZ      ALL64
        STC
        RETF
AVAIL:  MOV     EDX,CS:[RSVDLEN]
        MOV     ESI,CS:[TOP64+4]
        MOV     EDI,CS:[TOP64]
        PUSH    BX
        PUSH    ES
        CALL    HIMEM
        AND     BX,BX
        STC
        JZ      FAILED
        MOV     ECX,ES:[BX+6]
        SHL     ECX,10
        MOV     AX,524CH
        CLC
FAILED: POP     ES
        POP     BX
        RETF
ALL32:  AND     AL,AL
        JNZ     NOTRSV
        MOV     ESI,CS:[RSVDLEN]
        SUB     ESI,ECX
        JC      NOTRSV
        MOV     CS:[RSVDLEN],ESI
        ADD     ESI,CS:[RSVD]
        RETF
NOTRSV: PUSH    BX
        PUSH    ES
        PUSH    AX
        CALL    HIMEM
        POP     AX
        AND     BX,BX
        STC
        JZ      FAILED
        ADD     ECX,3FFH
        SHR     ECX,10
        SHR     ESI,10
        CMP     AL,3
        JZ      DOABS
        CMP     ES:[BX+6],ECX
        JBE     NOROOM
        CMP     AL,2
        JZ      UP
DOWN:   SUB     ES:[BX+6],ECX
        MOV     ESI,ES:[BX+2]
        ADD     ESI,ES:[BX+6]
        JMP     ROOM
UP:     SUB     ES:[BX+6],ECX
        MOV     ESI,ES:[BX+2]
        ADD     ES:[BX+2],ECX
        JMP     ROOM
DOABS:  CMP     ES:[BX+2],ESI
        JNC     NOROOM
        MOV     ECX,ES:[BX+2]
        ADD     ECX,ES:[BX+6]
        SUB     ECX,ESI
        JC      NOROOM      
        JMP     DOWN
NOROOM: MOV     AL,80H
ROOM:   SHL     ECX,10
        SHL     ESI,10
        SHL     AL,1
        POP     ES
        POP     BX
        RETF
ALL64:  MOV     ESI,CS:[TOP64+4]
        MOV     EDI,CS:[TOP64]
        SUB     EDI,ECX
        SBB     ESI,EBX
        JC      ENDCMD
        MOV     CS:[TOP64+4],ESI
        MOV     CS:[TOP64],EDI
        INC     ESI
        RETF
XFER:   PUSHAD
        PUSH    DS
        PUSH    ES
        PUSH    FS
        CALL    DOXFER
        POP     FS
        POP     ES
        POP     DS
        POPAD
ENDCMD: RETF

DOXFER: PUSH    CS
        POP     ES
        MOV     CX,12
        MOV     DI,OFFSET SRCADDR
        REP     MOVSW
        STOSB
        PUSH    CS
        POP     DS
        SMSW    AX
        TEST    AL,1
        JZ      DOREAL
        MOV     AX,1600H
        INT     2FH
        AND     AL,AL
        JNZ     WIN
        CMP     WORD PTR DS:[PORTTAB],1
        JZ      PROTE
        CMP     WORD PTR DS:[PORTTAB],100H
        JNC     EMMIO
        CALL    EMMOFF
        JC      BADEMM
        CALL    DOREAL
        JMP     EMMON
EMMIO:  CALL    SETEMM
        JC      BADEMM
        MOV     DX,DS:[PORTTAB]
        IN      AL,DX
        CLC
BADEMM: RET
WIN:    MOV     AL,DS:[MODE]
        AND     AL,AL
        JZ      PROT32
        DEC     AL
        JZ      PROT30
        JMP     PROTS

DOREAL: CLI
        PUSH    DS
        PUSH    ES
        PUSH    CS
        POP     ES
        XOR     AX,AX
        MOV     DS,AX
        MOV     CX,16H
        XOR     SI,SI
        MOV     DI,OFFSET ZSAVE
        REP     MOVSW
        PUSH    DS
        PUSH    ES
        POP     DS
        POP     ES
        MOV     CX,13H
        XOR     DI,DI
        MOV     SI,OFFSET ZSETUP
        REP     MOVSW
        PUSH    ES
        POP     DS
        PUSH    CS
        POP     FS
        MOV     EAX,CR4
        OR      AL,10H
        MOV     CR4,EAX
        DB      0FH,1,6,26H,0      ;SGDT [26H]
        DB      0FH,1,16H,20H,0    ;LGDT [20H]
        MOV     EAX,CR3
        PUSH    EAX
        XOR     EAX,EAX
        MOV     CR3,EAX
        MOV     EAX,CR0
        OR      EAX,80000001H
        MOV     CR0,EAX
        MOV     AX,8
        MOV     DS,AX
        MOV     ES,AX
        CALL    REAL
        MOV     EAX,CR0
        AND     EAX,7FFFFFFEH
        MOV     CR0,EAX
        POP     EAX
        MOV     CR3,EAX
        DB      0FH,1,16H,26H,0    ;LGDT [26H]
        PUSH    CS
        POP     DS
        XOR     AX,AX
        MOV     ES,AX
        MOV     CX,16H
        MOV     SI,OFFSET ZSAVE
        XOR     DI,DI
        REP     MOVSW
        POP     ES
        POP     DS
        STI
        CLC
        RET

DOEMM:  PUSH    DS
        PUSH    ES
        PUSH    FS
        PUSH    DS
        POP     FS
        MOV     AX,80H
        MOV     DS,AX
        MOV     ES,AX
        MOV     EAX,CR4
        OR      AL,10H
        MOV     CR4,EAX
        CALL    REAL
        POP     FS
        POP     ES
        POP     DS
        CLC
        RETF

;CS = 16

REAL:   MOV     EBX,CR3
        XOR     EBP,EBP
        MOV     AL,CS:[VIRT]
        CMP     AL,2
        JNZ     SOK
        MOV     ESI,CS:[SRCADDR+2]
        AND     ESI,0FFFFFFC0H
        CMP     ESI,0C0H
        JZ      SNG
SOK:    CMP     AL,1
        JNZ     DOK
        MOV     EDI,CS:[DESTADDR+2]
        AND     EDI,0FFFFFFC0H
        CMP     EDI,80H
        JNZ     DOK
SNG:    MOV     EBP,400000H
        SUB     EBX,4
DOK:    PUSH    DWORD PTR [EBX+8]
        PUSH    DWORD PTR [EBX+12]
        MOV     ESI,CS:[SRCADDR]
        MOV     ECX,ESI
        NOT     ECX
        AND     ECX,3FFFFFH
        INC     ECX
        MOV     EDI,CS:[DESTADDR]
        MOV     EDX,EDI
        NOT     EDX
        AND     EDX,3FFFFFH
        INC     EDX
        CMP     EDX,ECX
        JNC     MIN1
        MOV     ECX,EDX
MIN1:   CMP     DWORD PTR CS:[XFERLEN+4],0
        JNZ     MIN2
        MOV     EDX,CS:[XFERLEN]
        CMP     EDX,ECX
        JNC     MIN2
        MOV     ECX,EDX
MIN2:   AND     ECX,ECX
        JZ      DONE
        TEST    BYTE PTR CS:[VIRT],2
        JNZ     VIRTS
        MOV     EAX,ESI
        AND     EAX,0FFC00000H
        MOV     EDX,CS:[SRCADDR+4]
        SHL     EDX,13
        ADD     DX,2E7H
        ADD     EAX,EDX
        MOV     [EBX+8],EAX
        AND     ESI,3FFFFFH
        OR      ESI,800000H
        SUB     ESI,EBP
VIRTS:  TEST    BYTE PTR CS:[VIRT],1
        JNZ     VIRTD
        MOV     EAX,EDI
        AND     EAX,0FFC00000H
        MOV     EDX,CS:[DESTADDR+4]
        SHL     EDX,13
        ADD     DX,2E7H
        ADD     EAX,EDX
        MOV     [EBX+12],EAX
        AND     EDI,3FFFFFH
        OR      EDI,0C00000H
        SUB     EDI,EBP
VIRTD:  CLD
        MOV     EAX,CR3
        MOV     CR3,EAX
        WBINVD
        PUSH    ECX
        PUSH    ECX
        SHR     ECX,2
        DB      67H
        REP     MOVSD
        POP     ECX
        AND     ECX,3
        DB      67H
        REP     MOVSB
        POP     ECX
        WBINVD
        ADD     FS:[SRCADDR],ECX
        ADC     DWORD PTR FS:[SRCADDR+4],0
        ADD     FS:[DESTADDR],ECX
        ADC     DWORD PTR FS:[DESTADDR+4],0
        SUB     FS:[XFERLEN],ECX
        SBB     DWORD PTR FS:[XFERLEN+4],0
        POP     DWORD PTR [EBX+12]
        POP     DWORD PTR [EBX+8]
        JMP     REAL
DONE:   POP     DWORD PTR [EBX+12]
        POP     DWORD PTR [EBX+8]
        MOV     EAX,CR3
        MOV     CR3,EAX
        RET

;CS = 32

PROT30: PUSH    CS
        POP     ES
        XOR     AX,AX
        MOV     DS,AX
        CLI
        MOV     SI,PROTCD
        MOV     DI,OFFSET ZSAVE
        MOV     CX,PROT2-PROT1
        REP     MOVSB
        MOV     SI,INTCOD
        MOVSD
        PUSH    DS
        PUSH    ES
        POP     DS
        POP     ES
        MOV     SI,PROT1       ;Copy PM Code to Memory
        MOV     DI,PROTCD
        MOV     CX,PROT2-PROT1
        REP     MOVSB
        MOV     DS,AX          
        MOV     DWORD PTR DS:[INTCOD],0CB30CDH ;Put INT 30, RETF into INT 30 Call Stub
        PUSH    CS
        POP     DS
        MOV     EBX,CS:[TABLE]
        MOV     EAX,CS:[PROTA]
        MOV     DI,OFFSET INTPTR
        CALL    FAR PTR [DI]
        PUSH    CS
        POP     DS
        XOR     AX,AX
        MOV     ES,AX
        MOV     SI,OFFSET ZSAVE
        MOV     DI,PROTCD
        MOV     CX,PROT2-PROT1
        REP     MOVSB
        MOV     DI,INTCOD
        MOVSD
        STI 
        RET

PROTE:  MOV     ECX,CS:[PROTESA]
        JMP     PROTS0
PROTS:  MOV     ECX,CS:[PROTSCA]
PROTS0: PUSH    CS
        POP     DS
        XOR     AX,AX
        MOV     BX,OFFSET SYSSTK
        MOV     [BX],OFFSET ENDPRO
        MOV     [BX+2],AX
        MOV     [BX+4],CS
        MOV     [BX+6],AX
        PUSHF
        POP     WORD PTR [BX+8]
        MOV     WORD PTR [BX+10],2
        MOV     [BX+12],SP
        MOV     [BX+14],AX
        MOV     [BX+16],SS
        MOV     [BX+18],AX
        MOV     [BX+20],ES
        MOV     [BX+22],AX
        MOV     [BX+24],CS
        MOV     [BX+26],AX
        MOV     [BX+28],FS
        MOV     [BX+30],AX
        MOV     [BX+32],GS
        MOV     [BX+34],AX
        MOV     EBX,CS:[TABLE]
        MOV     EAX,ECX
        DB      0FH,34H         ;SYSENTER
PROTSC:
        DB      66H
        MOV     AX,30H
        MOV     DS,AX
        MOV     ES,AX
        JMP     SHORT PROT

PROTES:
        DB      66H
        MOV     AX,80H
        MOV     DS,AX
        MOV     ES,AX
        MOV     SS,AX
        MOV     EAX,CR3
        ADD     AL,8
        MOV     [BP+DI+26],AX
        JMP     SHORT PROT0

ENDPRO: CLC
        RET
BADPRO: STC
        RET

PROT32: MOV     EBX,CS:[TABLE]
	MOV     EAX,52524C4CH
	MOV     EAX,CR0
	NOP
        JMP     SHORT BADPRO
        JMP     SHORT ENDPRO
PROT:   MOV     WORD PTR [BP+DI+26],0E008H
        DW      0FFBFH
PROT0:  PUSHA
        PUSHF
        POP     AX
        AND     AX,0BFFFH
        DW      0FFFFH
        PUSH    AX
        POPF
        MOV     ECX,CR4
        OR      CL,10H
        MOV     CR4,ECX
LP32:   MOV     AX,[BP+DI+26]
        MOV     CL,[BP+DI+24]
        CMP     CL,2
        JNZ     SSOK
        MOV     SI,[BP+DI+2]
        DB      81H,0E6H        ;AND SI
        DD      0FFFFFFC0H
        CMP     SI,0C0H
        DW      0
        JZ      SSNG
SSOK:   CMP     CL,1
        JNZ     DDOK
        MOV     DI,[BP+DI+10]
        DB      81H,0E7H        ;AND DI
        DD      0FFFFFFC0H
        CMP     DI,0C0H
        DW      0
        JNZ     DDOK
SSNG:   SUB     AL,4
DDOK:   PUSH    WORD PTR [BX+SI]
        PUSH    WORD PTR [BX+SI+4]
        MOV     BP,AX
        MOV     SI,[BP+DI]
        MOV     CX,SI
        NOT     CX
        DB      81H,0E1H        ;AND CX
        DD      3FFFFFH
        INC     CX
        MOV     DI,[BP+DI+8]
        MOV     DX,DI
        NOT     DX
        DB      81H,0E2H        ;AND DX
        DD      3FFFFFH
        INC     DX
        CMP     DX,CX
        JNC     SHORT MIN3
        MOV     CX,DX
MIN3:   CMP     WORD PTR [BP+DI+20],0
        JNZ     SHORT MIN4
        MOV     DX,[BP+DI+16]
        CMP     DX,CX
        JNC     SHORT MIN4
        MOV     CX,DX
MIN4:   AND     CX,CX
        JNZ     SHORT MORE
        MOV     AX,BP
        POP     WORD PTR [BX+SI+4]
        POP     WORD PTR [BX+SI]
        MOV     EAX,CR3
        MOV     CR3,EAX
        POPA
        IRET
MORE:   TEST    BYTE PTR [BP+DI+24],2
        JNZ     VIRTPS
        MOV     AX,SI
        DB      25H             ;AND AX
        DD      0FFC00000H
        MOV     DX,[BP+DI+4]
        SHL     DX,13
        DB      66H
        ADD     DX,2E7H
        ADD     AX,DX
        XCHG    BX,BP
        MOV     [BP+DI],AX
        DB      81H,0E6H        ;AND SI
        DD      3FFFFFH
        DB      81H,0CEH        ;OR SI
        DD      800000H
        CMP     BL,8
        XCHG    BX,BP
        JZ      VIRTPS
        DB      81H,0EEH        ;SUB SI
        DD      400000H
VIRTPS: TEST    BYTE PTR [BP+DI+24],1
        JNZ     VIRTPD
        MOV     AX,DI
        DB      25H             ;AND AX
        DD      0FFC00000H
        MOV     DX,[BP+DI+12]
        SHL     DX,13
        DB      66H
        ADD     DX,2E7H
        ADD     AX,DX
        XCHG    BX,BP
        MOV     [BP+DI+4],AX
        DB      81H,0E7H        ;AND DI
        DD      3FFFFFH
        DB      81H,0CFH        ;OR DI
        DD      0C00000H
        CMP     BL,8
        XCHG    BX,BP
        JZ      VIRTPD
        DB      81H,0EFH        ;SUB DI
        DD      400000H
VIRTPD: CLD
        MOV     EAX,CR3
        MOV     CR3,EAX
        WBINVD
        PUSH    CX
        PUSH    CX
        SHR     CX,2
        REP     MOVSW
        POP     CX
        DB      83H,0E1H        ;AND CX
        DB      3
        REP     MOVSB
        POP     CX
        WBINVD
        ADD     [BP+DI],CX
        ADC     WORD PTR [BP+DI+4],0
        ADD     [BP+DI+8],CX
        ADC     WORD PTR [BP+DI+12],0
        SUB     [BP+DI+16],CX
        SBB     WORD PTR [BP+DI+20],0
        MOV     AX,BP
        POP     WORD PTR [BX+SI+4]
        POP     WORD PTR [BX+SI]
        DB      0E9H            ;JMP
        DD      LP32-LP32X
LP32X:

EMMOFF: CMP     BYTE PTR CS:[EMMACT],0
        JNZ     YESEMM
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
YESEMM: MOV     AX,0
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
        JMP     EMMOK

SETEMM: CMP     BYTE PTR CS:[EMMACT],0
        JNZ     EMMS
        MOV     AX,CS:[PORTTAB]
        MOV     DX,AX
        SHL     EDX,16
        MOV     DX,AX
        MOV     AX,4A15H
        XOR     BX,BX
        MOV     CX,1
        MOV     SI,OFFSET PORTTAB
        MOV     DI,OFFSET ENDPTR
        INT     2FH
        JC      EMMF
        CMP     AX,4A15H
        JNZ     EMMOK
NOEMM:  STC
EMMF:   RET
EMMOK:  INC     BYTE PTR CS:[EMMACT]
EMMS:   CLC
        RET

HIMEM:  PUSH    CX
        PUSH    EDX
        PUSH    DI
        XOR     BX,BX
        MOV     AX,4309H
        INT     2FH
        CMP     AL,43H
        JNZ     NONE
        CMP     BYTE PTR ES:[BX+1],10
        JNZ     NONE
        MOV     CX,ES:[BX+2]
        LES     BX,ES:[BX+4]
        XOR     EDX,EDX
HIMEM1: CMP     BYTE PTR ES:[BX],1
        JNZ     HIMEM2
        CMP     DWORD PTR ES:[BX+2],EDX
        JC      HIMEM2
        MOV     DI,BX
        MOV     EDX,DWORD PTR ES:[BX+2]
HIMEM2: ADD     BX,10
        LOOP    HIMEM1
        MOV     BX,DI
NONE:   POP     DI
        POP     EDX
        POP     CX        
        RET

PROT1:  ADD     WORD PTR [DI+24H],2     ;Protected Mode Setup (Code Inverted)
        POP     AX
        CLI
        XCHG    SP,[BX+4CH]
        POPA
        ADD     SP,4
        JMP     AX
PROT2:

INT15:  CMP     AX,0E801H
        JNZ     INT15A
        PUSHF
        PUSH    CS
        CALL    INT15J
        MOV     BX,CS:[BIOSSZ]
        MOV     DX,CS:[BIOSSZ]
        RETF    2
INT15A: CMP     AX,0E820H
        JNZ     INT15J
        CMP     EDX,534D4150H
        JNZ     INT15J
        CMP     CS:[BIOSIND],EBX
        JNZ     INT15J
        PUSHF
        PUSH    CS
        CALL    INT15J
        JC      INT15R
        PUSH    EAX
        MOV     EAX,CS:[BIOSLEN]
        MOV     ES:[DI+8],EAX
        POP     EAX
INT15R: RETF    2

VECT	DW	INIT,EXIT,EXIT,EXIT,READ,EXIT,EXIT,EXIT
        DW      WRITE,WRITE,EXIT,EXIT,EXIT,OPEN,EXIT,EXIT
HDOFF	DW	0
HDSEG	DW	0

SYSJMP: JMP     AX
        DB      40H DUP(0)
SYSSTK:                                      ;USES ZSAVE SPACE
ZSAVE   DB      2CH DUP(0)                   ;MULTIPLE USES
ZSETUP  DD      2E7H,400002E7H,800002E7H,0C00002E7H  ;PAGE TABLE
        DD      0,0,0FFFFH,0CF9200H          ;GDT
        DW      10H,10H,0                    ;LGDT DATA

INTPTR  DW      INTOFF,3BH                   ;INT30 PTR
PORTTAB DW      1,DOEMM                      ;EMM I/O PORT, VECTOR
EMMACT  DB      0
MODE    DB      0

RDDATA  DW      CMD,0                        ;Keep In Order
RSVD    DD      0
RSVDLEN DD      0
TOP64   DD      0,0
RES1    DD      0

RDPTR   DB      0
WRPTR   DB      0

BIOSIND DD      0
BIOSST  DD      0
BIOSLEN DD      0
BIOSSZL DW      0
BIOSSZ  DW      0

INT15J:
        DB      0EAH    ;JMP FAR
INT15P  DD      0

EMMA1   DW      0
EMMA2   DW      0
EMMSAV  DB      0

TABLE   DD      0

SRCADDR         DD      0,0                  ;Keep In Order
DESTADDR        DD      0,0
XFERLEN         DD      0,0
VIRT            DB      0,0
PMAP            DD      0

PROTA           DD      0
PROTSCA         DD      0
PROTESA         DD      0
SYSJMPP         DD      0
SYSSTKP         DD      0

ENDPTR:

INIT:   IN      AL,92H
        OR      AL,2
        OUT     92H,AL
        OUT     0EBH,AL
        SMSW    AX
        AND     AL,1
        JNZ     INPROT
        MOV     EAX,CR4
        OR      AL,10H
        MOV     CR4,EAX
INPROT: PUSH    DS
        PUSH    BX
        PUSH    CS
        POP     DS
        PUSH    CS
        POP     ES
        MOV     EAX,0E801H
	INT     15H
        JC      SCANX
        MOV     DS:[BIOSSZ],DX
SCANX:  XOR     EBX,EBX
        XOR     EBP,EBP
SCAN64: MOV     EAX,0E820H
	MOV     ECX,20H
	MOV     EDX,534D4150H
        MOV     ESI,EBX
        MOV     DI,OFFSET ZSAVE
	INT     15H
        JC      NO64
	CMP     BYTE PTR [DI+16],1
	JNZ     SCAN1
	CMP     DWORD PTR [DI+4],1
        JNC     SCAN2
        CMP     [DI],EBP
        JC      SCAN1
        MOV     EBP,[DI]
        MOV     DS:[BIOSIND],ESI
        MOV     EAX,[DI]
        MOV     DS:[BIOSST],EAX
        MOV     EAX,[DI+8]
        MOV     DS:[BIOSLEN],EAX
        JMP     SCAN1
SCAN2:  JNZ     SCAN1
	CMP     DWORD PTR [DI],0
	JNZ     SCAN1
        MOV     EAX,[DI+8]
        MOV     DS:[TOP64],EAX
        MOV     EAX,[DI+12]
        MOV     DS:[TOP64+4],EAX
SCAN1:  AND     BX,BX
        JNZ     SCAN64
NO64:   POP     BX
        POP     DS
        MOV     WORD PTR DS:[BX+0EH],OFFSET ENDPTR
	MOV	DS:[BX+10H],CS
        LDS     SI,DS:[BX+12H]
DROP:   LODSB
        CMP     AL,20H
        JC      ENDSC
        JZ      DROP
DROP1:  LODSB
        CMP     AL,20H
        JC      ENDSC
        JNZ     DROP1
SCAN:   LODSB
        CMP     AL,20H
        JZ      SCAN
        JC      ENDSC
        CMP     AL,2FH
        JNZ     ARGLST
        LODSB
        CMP     AL,32H
        JNZ     SCANL
        MOV     BYTE PTR CS:[INT2BF],1
        JMP     SCAN
SCANL:  AND     AL,0DFH
        CMP     AL,56H
        JNZ     SCANV
        MOV     CS:[VERB],1
        JMP     SCAN
SCANV:  CMP     AL,49H
        JNZ     SCANI
        CMP     BYTE PTR CS:[MODE],0
        JNZ     DUPARG
        MOV     CS:[MODE],1
        JMP     SCAN
SCANI:  CMP     AL,53H
        JNZ     SCANS
        CMP     BYTE PTR CS:[MODE],0
        JNZ     DUPARG
        SMSW    AX
        AND     AL,1
        JNZ     ORDER
        MOV     CS:[MODE],2
        JMP     SCAN
SCANS:  CMP     AL,45H
        JNZ     SCANE
        CMP     WORD PTR CS:[PORTTAB],1
        JNZ     DUPARG
        MOV     CS:[PORTTAB],0
        LODSB
        CMP     AL,3AH
        JNZ     SCAN
        CALL    HEX
        CMP     ECX,10000H
        JNC     BADARG
        CMP     CX,100H
        JC      BADARG
        MOV     CS:[PORTTAB],CX
        JMP     SCAN
SCANE:  CMP     AL,41H
        JNZ     SCANA
        CMP     DWORD PTR CS:[RSVDLEN],0
        JNZ     DUPARG
        LODSB
        CMP     AL,3AH
        JNZ     BADARG
        CALL    HEX
        SHL     ECX,10
        JMP     PRE1
SCANA:  CMP     AL,4CH
        JNZ     ARGLST
        CMP     DWORD PTR CS:[RSVDLEN],0
        JNZ     DUPARG
        LODSB
        CMP     AL,3AH
        JNZ     BADARG
        CALL    HEX
        SHL     ECX,10
        MOV     CL,1
PRE1:   MOV     CS:[RSVDLEN],ECX
        JMP     SCAN
DUPARG: MOV     SI,OFFSET DUPARGS
        JMP     ARGERR
ORDER:  MOV     SI,OFFSET ORDERM
        JMP     ARGERR
BADARG: MOV     SI,OFFSET BADARGS
ARGERR: PUSH    CS
        POP     DS
        CALL    PRINT
        JMP     ERROR3
ARGLST: PUSH    CS
        POP     DS
        MOV     SI,OFFSET ARGS
        CALL    PRINT
        JMP     ERROR3
BADPRT: MOV     SI,OFFSET PORTER
        CALL    PRINT
        JMP     ERROR3
ENDSC:  MOV     ECX,CS:[RSVDLEN]
        AND     ECX,ECX
        JZ      NOPRE
        CALL    HIMEM
ENDSC1: MOV     DL,CL
        MOV     CL,0
        AND     BX,BX
        JNZ     HIMEMP
        MOV     EAX,CS:[BIOSLEN]
        AND     EAX,EAX
        JNZ     DO20
        AND     DL,DL
        JZ      NOTL1
        MOV     EAX,DWORD PTR CS:[BIOSSZL]
        ADD     EAX,1000000H
        SUB     EAX,ECX
        JZ      NOPRE
        MOV     ECX,EAX
        MOV     CS:[RSVDLEN],ECX
        JMP     ENDSC1
NOTL1:  MOV     EAX,DWORD PTR CS:[BIOSSZL]
        CMP     EAX,ECX
        JC      BADARG
        SUB     EAX,ECX
        MOV     DWORD PTR CS:[BIOSSZL],EAX
        ADD     EAX,1000000H
        JMP     SETSIZ
DO20:   AND     DL,DL
        JZ      NOTL2
        MOV     EAX,CS:[BIOSLEN]
        ADD     EAX,CS:[BIOSST]
        SUB     EAX,ECX
        JZ      NOPRE
        MOV     ECX,EAX
        MOV     CS:[RSVDLEN],ECX
        JMP     ENDSC1
NOTL2:  MOV     EAX,CS:[BIOSLEN]
        CMP     EAX,ECX
        JC      BADARG
        SUB     EAX,ECX
        MOV     CS:[BIOSLEN],EAX
        SUB     DWORD PTR CS:[BIOSSZL],ECX
        ADD     EAX,CS:[BIOSST]
SETSIZ: MOV     CS:[RSVD],EAX
        PUSH    DS
        XOR     AX,AX
        MOV     DS,AX
        MOV     EAX,DS:[54H]
        MOV     CS:[INT15P],EAX
        MOV     DS:[54H],OFFSET INT15
        MOV     DS:[56H],CS
        POP     DS
        JMP     NOPRE
HIMEMP: AND     DL,DL
        JZ      NOTL3
        MOV     EAX,ES:[BX+2]
        ADD     EAX,ES:[BX+6]
        SHL     EAX,10
        SUB     EAX,ECX
        JZ      NOPRE
        MOV     ECX,EAX
        MOV     CS:[RSVDLEN],ECX
        JMP     ENDSC1
NOTL3:  SHR     ECX,10
        CMP     ES:[BX+6],ECX
        JBE     BADARG
        SUB     ES:[BX+6],ECX
        MOV     ECX,ES:[BX+2]
        ADD     ECX,ES:[BX+6]
        SHL     ECX,10
        MOV     CS:[RSVD],ECX
NOPRE:  PUSH    CS
        POP     DS
        PUSH    CS
        POP     ES
        MOV     DX,DS:[PORTTAB]
        CMP     DS:[MODE],2
        JZ      MODE2
        CMP     DX,1
        JNZ     MODE2
        MOV     DX,7C80H
        MOV     DS:[PORTTAB],DX
MODE2:  CMP     DX,2
        JC      PORT0
        IN      AL,DX
        CMP     AL,0FFH
        JNZ     BADPRT
        MOV     AL,0
        OUT     DX,AL
        IN      AL,DX
        CMP     AL,0FFH
        JNZ     BADPRT
PORT0:  XOR     EBX,EBX
        MOV     BX,CS
        SHL     EBX,4
        XOR     EAX,EAX
        MOV     AX,OFFSET SRCADDR
        ADD     EAX,EBX
        MOV     DS:[TABLE],EAX
        XOR     EAX,EAX
        MOV     AX,OFFSET PROT
        ADD     EAX,EBX
        MOV     DS:[PROTA],EAX
        XOR     EAX,EAX
        MOV     AX,OFFSET PROTSC
        ADD     EAX,EBX
        MOV     DS:[PROTSCA],EAX
        XOR     EAX,EAX
        MOV     AX,OFFSET PROTES
        ADD     EAX,EBX
        MOV     DS:[PROTESA],EAX
        XOR     EAX,EAX
        MOV     AX,OFFSET SYSJMP
        ADD     EAX,EBX
        MOV     DS:[SYSJMPP],EAX
        XOR     EAX,EAX
        MOV     AX,OFFSET SYSSTK
        ADD     EAX,EBX
        MOV     DS:[SYSSTKP],EAX
        MOV     CS:[RDDATA+2],CS
        MOV     AL,DS:[MODE]
        CMP     AL,2
        JNZ     MODE0
        MOV     EAX,CS:[SYSJMPP]
        XOR     EDX,EDX
        MOV     ECX,176H
        WRMSR
        MOV     EAX,CS:[SYSSTKP]
        DEC     CX
        WRMSR
        XOR     EAX,EAX
        MOV     AL,28H
        DEC     CX
        WRMSR
MODE0:  CMP     BYTE PTR CS:[INT2BF],0
        JZ      INIT0
        XOR     AX,AX
        MOV     DS,AX
        MOV     DS:[0ACH],OFFSET INT2B
        MOV     DS:[0AEH],CS
INIT0:  PUSH    CS
        POP     DS
        MOV     SI,OFFSET CPYRT
        CALL    PRINT
        CMP     BYTE PTR DS:[VERB],0
        JZ      EXIT
        MOV     AL,DS:[MODE]
        AND     AL,AL
        JZ      VM0
        DEC     AL
        JZ      VM1
        MOV     SI,OFFSET VERBM2
        JMP     VM2
VM0:    MOV     SI,OFFSET VERBM0
        JMP     VM2
VM1:    MOV     SI,OFFSET VERBM1
VM2:    CALL    PRINT
        MOV     AX,DS:[PORTTAB]
        CMP     AX,1
        JZ      VE0
        AND     AX,AX
        JNZ     VE1
        MOV     SI,OFFSET VERBE0
        CALL    PRINT
        JMP     VE2
VE0:    MOV     SI,OFFSET VERBE2
        CALL    PRINT
        JMP     VE2
VE1:    MOV     SI,OFFSET VERBE1
        PUSH    AX
        CALL    PRINT
        POP     AX
        CALL    PHEX
VE2:    MOV     EAX,DS:[RSVDLEN]
        AND     EAX,EAX
        JNZ     VA1
        MOV     SI,OFFSET VERBA0
        CALL    PRINT
        JMP     VA2
VA1:    MOV     SI,OFFSET VERBA1
        PUSH    AX
        CALL    PRINT
        POP     AX
        SHR     EAX,10
        CALL    PDEC
VA2:    CMP     BYTE PTR CS:[INT2BF],0
        JZ      V2
        MOV     SI,OFFSET INT2BT
        CALL    PRINT
V2:     CMP     DWORD PTR CS:[INT15P],0
        JZ      V15
        MOV     SI,OFFSET INTCPT
        CALL    PRINT
V15:    MOV     EAX,DS:[TOP64+1]
        AND     EAX,EAX
        JNZ     VT1
        MOV     SI,OFFSET VERBT0
        CALL    PRINT
        JMP     VT2
VT1:    MOV     SI,OFFSET VERBT1
        PUSH    AX
        CALL    PRINT
        POP     AX
        SHR     EAX,2
        CALL    PDEC
VT2:    MOV     SI,OFFSET NL
        CALL    PRINT
        JMP     EXIT

HEX:    XOR     ECX,ECX
HEX0:   LODSB   
        CMP     AL,30H
        JC      HEXEND
        CMP     AL,40H
        JC      HEX1
        AND     AL,0DFH
        CMP     AL,41H
        JC      HEXEND
        CMP     AL,57H
        JNC     HEXEND
        SUB     AL,7
        JMP     HEX2
HEX1:   CMP     AL,3AH
        JNC     HEXEND
HEX2:   AND     AL,0FH
        SHL     ECX,4
        ADD     CL,AL
        JMP     HEX0
HEXEND: RET

PRINT:  MOV     AH,0EH
        LODSB
        AND     AL,AL
        JZ      SHORT HEXEND
        INT     10H
        JMP     PRINT

PHEX:   MOV     BX,AX
        MOV     CX,4
        MOV     AH,0EH
PHEX1:  ROL     BX,4
        MOV     AL,BL
        AND     AL,0FH
        CMP     AL,10
        JC      PHEX2
        ADD     AL,7
PHEX2:  ADD     AL,30H
        INT     10H
        LOOP    PHEX1
        MOV     SI,OFFSET NL
        JMP     PRINT

PDEC:   MOV     SI,OFFSET ZSAVE+10
        MOV     BYTE PTR [SI],0
PDEC1:  AND     EAX,EAX
        JZ      PDEC2
        MOV     EBX,10
        XOR     EDX,EDX
        DIV     EBX
        ADD     DL,30H
        DEC     SI
        MOV     BYTE PTR [SI],DL
        JMP     PDEC1
PDEC2:  CALL    PRINT
        MOV     SI,OFFSET KB
        JMP     PRINT

VERB    DB      0
INT2BF  DB      0

CPYRT   DB      'HIMEMEX  Ver 1.2  Copyright (C) 2008-2009  by Rudolph R. Loew',13,10
        DB      '         All Rights Reserved',13,10,13,10,0
ARGS    DB      'HIMEMEX [/I | /S] [/E:# | /E] [/A:# | /L:#] [/2] [/V]',13,10
        DB      '        /I=INT30 Method  /S=SYSENTER Method  Default=PROTHOOK Method',13,10
        DB      '        /E:#=EMM386 Virtualization Port  /E=EMM386 ON/OFF',13,10
        DB      '        /A:#=Preallocate 32-Bit Memory (KB)',13,10
        DB      '        /L:#=Preallocate 32-Bit Memory Above Address (KB)',13,10
        DB      '        /2=Use Interrupt 2BH for HIMEMEX Calls  /V=Verbose',13,10
        DB      '        # = Port or Memory (KB) in Hexadecimal',13,10,13,10,0
ORDERM  DB      'SYSENTER Method Requires HIMEMEX Loaded Before EMM386',13,10,13,10,0
DUPARGS DB      'Multiple or Conflicting Arguments',13,10,13,10,0
BADARGS DB      'Invalid Preallocation or EMM386 Virtual I/O Port',13,10,13,10,0
PORTER  DB      'Selected EMM386 Virtual I/O Port is in use',13,10,13,10,0
KB      DB      ' KB'
NL      DB      13,10,0
VERBM0  DB      'PROTHOOK Method',13,10,0
VERBM1  DB      'INT30 Method',13,10,0
VERBM2  DB      'SYSENTER Method',13,10,0
VERBE0  DB      'EMM386 ON/OFF Method',13,10,0
VERBE1  DB      'EMM386 Virtual I/O Port ',0
VERBE2  DB      'EMM386 SYSENTER Method',13,10,0
VERBA0  DB      'No Preallocated 32-Bit Memory',13,10,0
VERBA1  DB      'Preallocated 32-Bit Memory:  ',0
VERBT0  DB      'No 64-Bit Memory',13,10,0
VERBT1  DB      '64-Bit Memory:  ',0
INT2BT  DB      'Interrupt 2BH Setup for HIMEMEX Calls',13,10,0
INTCPT  DB      'Interrupt 15H Hooked',13,10,0

CODE    ENDS
	END
