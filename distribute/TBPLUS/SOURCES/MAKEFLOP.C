main(c,v)
int c;
char **v;
{
int f,i,j;
long x,lseek();
int b[0x2400];
if (c<2) {printf("MAKEFLOP File\n");return(20);}
f=_open(v[1],0);
if (f<0) {printf("Cannot Open File\n");return(20);}
x=lseek(f,0L,2);lseek(f,0L,0);
if (x-1474560) {printf("Incorrect File or File Damaged\n");return(20);}
for (i=0;i<160;i++) {
if (_read(f,b,0x2400)-0x2400) {printf("\nError Reading File\n");return(20);}
if (i==0) {
if (b[0xd9]-0x4c52) {printf("TBPLUS Boot Sector damaged or missing\n");return(20);}
printf("Insert Formatted Floppy Disk with no Bad Sectors into Drive A:\n\nWARNING - ALL PREVIOUS DATA WILL BE ERASED\n\nPress ENTER to Continue - Anything else then ENTER to Quit ");
read(0,&j,2);
if ((j&255)-10) {printf("ABORTED\n");return(5);}
if (put(b,i)==0) goto skip;
}
if (put(b,i)) {printf("\nError Writing Floppy\n");return(20);}
skip:;
}
printf("\nFloppy Disk Written - Verifying\n");
lseek(f,0L,0);
for (i=0;i<160;i++) {
if (_read(f,b,0x2400)-0x2400) {printf("\nError Reading File\n");return(20);}
if (get(b+0x1200,i)) {printf("\nError Reading Floppy\n");return(20);}
for (j=0;j<0x1200;j++) if (b[j]-b[j+0x1200]) {printf("\nVerification Failed - Try Another Disk\n");return(20);}
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

put(b,i)
int b,i;
{
int j,k;
j=((i>>1)<<8)+1;k=(i&1) ? 0x100 : 0;
printf("Writing Cylinder %d\r",i>>1);
_asm {
db 0x60
mov ax,0x312
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
