main(c,v)
int c;
char **v;
{
int f,i;
long x,lseek();
int b[0x1200];
if (c<2) {printf("MAKEIMG File\n");return(20);}
f=_creat(v[1],0);
if (f<0) {printf("Cannot Create File\n");return(20);}
for (i=0;i<160;i++) {
if (get(b,i)) if (get(b,i)) {printf("\nError Reading Floppy\n");return(20);}
if (i==0) if (b[0xd9]-0x4c52) {printf("\nTBPLUS Boot Sector damaged or missing\n");return(20);}
if (_write(f,b,0x2400)-0x2400) {printf("\nError Writing File\n");return(20);}
}
printf("\nDone\n");return(0);
}

get(b,i)
int b,i;
{
int j,k;
j=((i>>1)<<8)+1;k=(i&1) ? 0x100 : 0;
printf("Reading Cylinder %d\r",i>>1);
_asm {
db 0x60
mov ax,0x212
mov bx,[b]
mov cx,[j]
mov dx,[k]
int 0x13
db 0x61
jc fail
mov word ptr [b],0
};
fail: return(b);
}
