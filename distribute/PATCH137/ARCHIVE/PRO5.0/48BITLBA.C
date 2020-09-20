/*( getnum )*/

void lock();

main(c,v)
int c;
char **v;
{
int d,en,i,j,k,l,ll,ver,sig;
unsigned long y,z,zz,b[640],getnum();
char gb[8];
ll=en=ver=0;
arg: if (c>1) if (v[1][0]=='+') {ver=1;c--;v++;goto arg;}
if (c>1) if (v[1][0]=='-') {ll=1;c--;v++;goto arg;}
if (c>1) if (v[1][0]=='/') if (v[1][1]=='?') {printf("48BITLBA [+Verify] [-Lock] MaxDrives\n");return(20);}
if (c>1) {
en=getnum(v[1]);
if ((en<1) || (en>127)) {printf("Invalid Number of Drives\n");return(20);}
}
printf("48-Bit LBA Support Test  Version 5.0\n\nCopyright (C) 2004-2006 by\nRudolph R. Loew\nAll Rights Reserved\n\n");
z=0x10000000;zz=0x11000000;
if (int13ex(0x41,0x80,0L,0,b)) {
printf("Interrupt 13 Extensions Not Supported\nCannot Support Drives Greater Than 8.4GB\n");
if (ver) {
quit: printf("Press Any Key to Continue at Risk of DATA LOSS - Otherwise Press RESET\n");read(0,&i,4);
}
return(20);
}
if (en) en+=0x80;
else {
en=0x88;
asm {
push bx
push cx
push dx
mov ax,0x800
mov dx,0x80
int 0x13
jb  nocnt
mov dh,0
or  dl,0x80
mov [en],dx
}
nocnt: asm {
pop dx
pop cx
pop bx
}
}
for (d=0x80;d<en;d++) if (int13ex(0x48,d,0L,0,b)==0) {
y=b[4];j=l=sig=0;
if (y<0x400000) printf("Drive %d: %4ldMB = %10ld Sectors  ",d-0x7f,(y<<9)/1000000,y);
else {
if (y>=195312500) printf("Drive %d: %4ldGB = %10ld Sectors  ",d-0x7f,y/1953125,y);
else {
sprintf(gb,"%3ld",(y<<1)/390625);gb[4]=0;gb[3]=gb[2];gb[2]='.';
printf("Drive %d: %sGB = %10ld Sectors  ",d-0x7f,gb,y);
}
}
for (i=0;i<2;i++) {
b[126]=i;b[127]=0x524c524c;
int13ex(0x42,d,31L,1,b);
if (b[126]-i) goto nosig;
}
i=b[127]&65535;k=b[127]>>16;
if ((k&0xff00)==0x5400) {
printf("TeraByte Driver Patch Version %d.%d  LUN %d\n",i>>8,i&255,k&255);
sig=1;goto nosig;
}
if (k==0x4c52) {
printf("Driver Patch Version %d.%d Active\n",i>>8,i&255);
sig=1;goto nosig;
}
if (k==0x4445) {
printf("Demo Patch Version %d.%d Active\n",i>>8,i&255);
sig=1;goto nosig;
}
nosig: if (y<0xFA00000) {
if (sig==0) printf("Not 48-Bit Disk\n");
goto next;
}
if (ll) {
lock(0x84b,d+0x100,1);lock(0x84b,d+0x200,0);lock(0x84b,d+0x300,0);l=2;
}
if (int13ex(0x42,d,0L,1,b+512)) goto derr;
i=int13ex(0x42,d,z,1,b+384);
if (int13ex(0x42,d,0L,1,b)) goto derr;
if (int13ex(0x42,d,z-2,3,b)) {
if (y>z) goto derr;
if (sig==0) printf("Not 48-Bit Disk\n");
goto next;
}
if (sig==0) printf("48-Bit LBA Disk - ");
if (int13ex(0x42,d,z-1,2,b)) j|=1;
if (i) goto fail;
for (i=0;i<128;i++) if (b[i+384]-b[i+256]) goto fail;
if (int13ex(0x42,d,zz,1,b)) j|=2;
else for (i=0;i<128;i++) if (b[i+384]-b[i]) j|=2;
b[384]++;
if (int13ex(0x43,d,z,1,b+384)) {
if (ll) goto derr2;
lock(0x84b,d+0x100,2);l=1;
if (int13ex(0x43,d,z,1,b+384)) goto derr2;
}
b[384]--;
if (int13ex(0x42,d,z-2,3,b)) goto ng;
if (int13ex(0x42,d,z,1,b)) goto ng;
if (int13ex(0x42,d,zz,1,b+128)) j|=2;
if (int13ex(0x43,d,z,1,b+384)) goto derr3;
if (int13ex(0x43,d,0L,1,b+512)) goto derr2;
for (i=0;i<128;i++) if (b[i]-b[i+256]) goto fail;
if (b[0]==b[384]) {printf("Write Support Failed\n");goto err;} 
if ((j&4)==0) if (b[0]-b[128]) j|=2;
skip: if (j&1) if (ver) ver=2;
if (y<z) {
switch(j) {
case 0: printf("Not Correctly Sized\nDemo Limited to 145GB\n");break;
case 1: printf("Not Correctly Sized\nLast 28-Bit Sector Unsupported - Demo Limited to 145GB\n");break;
case 2: printf("Not Correctly Sized\n48-Bit Support Verified\n");break;
case 3: printf("Not Correctly Sized\nLast 28-Bit Sector Unsupported\n");break;
};
goto next;
}
switch(j) {
case 0: if (sig==0) printf("Demo Limited to 145GB\n");
        break;
case 1: printf("Last 28-Bit Sector Unsupported\nDemo Limited to 145GB\n");break;
case 2: if (sig==0) printf("48-Bit Support Verified\n");
        break;
case 3: printf("Last 28-Bit Sector Unsupported\n");break;
}
goto next;
fail: if (ver) ver=3;
if (sig) printf("**** INCOMPATABLE DISK ****\n");
else printf("48-Bit LBA Not Supported\n");
err: if (ver) ver=3;
goto next;
ng: int13ex(0x43,d,z,1,b+384);
if (int13ex(0x43,d,0L,1,b+512)) goto derr2;
derr: printf("Error Reading Disk\n");goto err;
derr3: int13ex(0x43,d,0L,1,b+512);
derr2: printf("Error Writing Disk\n");goto err;
next: if (l==1) lock(0x86b,d+0x100,0);
if (l==2) {
lock(0x86b,d+0x300,0);lock(0x86b,d+0x200,0);lock(0x86b,d+0x100,0);
}
}
if (ver>1) goto quit;
return(0);
}

int13ex(c,d,y,l,buff)
int c,d,l;
long y,*buff;
{
long arg[8];
int a,b,s;
s=(int)arg;a=c<<8;b=0x55aa;
switch(c) {
case 0x41:
case 0x48: arg[0]=0x20;break;
case 0x42:
case 0x43:
case 0x44: arg[0]=l;arg[0]=(arg[0]<<16)+0x10;
           arg[1]=(int)buff;arg[2]=y;arg[3]=(y-31) ? 0 : 0x524c524c;
           break;
default: return(1);
};
asm {
push bx
push cx
push dx
push si
push es
mov bx,[b]
mov dx,[d]
mov si,[s]
mov ax,ss
mov es,ax
mov [si+6],ax
mov ax,[a]
push bp
int 0x13
pop bp
mov [b],bx
pop es
pop si
pop dx
pop cx
pop bx
jc err
mov [a],0
}
err: if (c==0x48) for (d=0;d<8;d++) buff[d]=arg[d];
if (c==0x41) if (b+0x55ab) a=1;
return(a);
}

void lock(m,d,p)
int m,d,p;
{
asm {
push bx
push cx
push dx
mov ax,0x440d
mov bx,[d]
mov cx,[m]
mov dx,[p]
int 0x21
pop dx
pop cx
pop bx
}
}
