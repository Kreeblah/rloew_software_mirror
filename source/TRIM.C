/*( getnum identify trimcmd blk13ex )*/

//#define TESTMODE
//#define PRNT

long getnum();
int b[256],j,k;

add(x,y)
long x,y;
{
int l;

#ifdef PRNT
printf("%lx - %lx\n",x,y);
#endif

more: if (j==256) {

#ifndef TESTMODE
if (l=trimcmd(k,b)) {printf("TRIM Failed Code %d\n",l);return(20);}
#endif

for (l=0;l<256;l++) b[l]=0;
j=0;
}
b[j++]=x;b[j++]=x>>16;b[j++]=0;
if (y>(x+65535)) {b[j++]=65535;x+=65535L;goto more;}
b[j++]=y-x;return(0);
}

int zero(unsigned long *b)
{
_asm {
push di
mov di,[b]
xor ax,ax
mov cx,0x100
repz scasw
pop di
jnz notz
mov word ptr [b],0
};
notz: return((int)b);
}

main(c,v)
int c;
char **v;
{
unsigned long x,y,z,buff[8192],fs,base,fb,fb2,st,end;
int q,i,l,m,cs,n,fp,zt;
unsigned char *bb;
q=1;printf("DOS FAT32 and Physical Disk TRIM Program  Version 1.3 RRL\nCopyright (C) 2015-2017 by Rudolph R. Loew. All Rights Reserved.\n\n");
if (c>1) if (v[1][0]=='-') {q=0;c--;v++;}
if (c<2) {printf("TRIM [-NoQuery] Drive|Disk Free|Zero|All|[Start Stop]....\n");return(20);}
j=0;x=0;z=0xffffffff;bb=(unsigned char *)buff;
k=v[1][0]&0xdf;
if ((k>='A') && (k<='Z')) {k=drive(k-64,&x,&z);z+=x;}
else k=getnum(v[1]);
if ((k<0x80) || (k>=0xa0)) {printf("Invalid Drive\n");return(20);}
zt=1;

#ifndef TESTMODE
if (identify(k,bb)) {printf("Cannot Get Disk Info\n");return(20);}
if ((bb[0x152]&1)==0) {printf("TRIM not supported\n");return(20);}
if ((bb[0x8a]&32)==0) zt=0;
if ((bb[0x8b]&64)==0) zt=0;
if ((*(long *)(bb+0xcc))==0) {
y= *(long *)(bb+0xc8);
if (y<z) z=y;
}
#endif

for (i=0;i<256;i++) b[i]=0;
if (c==2)  printf("Drive = %x  Start = %lx  End = %lx\n",k,x,z);
if (c==3) if ((v[2][0]&0xdf)=='A') {

#ifndef TESTMODE
if (z==0xffffffff) {printf("Greater that 2TiB Drive Not Supported\n");return(20);}
#endif

printf("Trim 0x%lx Sectors?\nEntire Drive or Partition will be IRREVERSIBLY ERASED!\nType \042Erase ALL\042 to Continue, Press ENTER to Abort\n> ",z-x);
bb[0]=0;read(0,bb,12);
if (strncmp(bb,"Erase ALL",9)) return(5);
if (add(x,z)) return(20);
goto done;
}
if (c==3) if ((v[2][0]&0xdf)=='Z') {

#ifndef TESTMODE
if (*(long *)(bb+0xcc)) if (x>0xff000000) {printf("Partition Starting After 2TiB Not Supported\n");return(20);}
#endif

if (zt==0) {printf("Cannot Zero TRIM This Disk\n");return(20);}
fp=8192;i=64;m=0;
while(x<z) {
if ((x&4095)==0) printf("%lx\r",x);
if (fp>=(i<<7)) {
if (z<(x+64)) i=z-x;
if (blk13ex(0x42,k,x,buff,i)) {fb=x;goto rerr;}
fp=0;
}
l=zero(buff+fp);
switch(m) {
case 0: if (l) break;
        st=x;m=1;break;
case 1: if (l==0) break;
        if (add(st,x)) return(20);
        m=0;
};
x++;fp+=128;
}
if (m==1) if (add(st,x)) return(20);
goto done;
}
if (c==3) if ((v[2][0]&0xdf)=='F') {

#ifndef TESTMODE
if (*(long *)(bb+0xcc)) if (x>0xff000000) {printf("Partition Starting After 2TiB Not Supported\n");return(20);}
#endif

if (q) {
printf("Warning - TRIM Operation is IRREVERSIBLE\nDo Not Continue if Partition has not passed SCANDISK\nContinue (Y/N)? (N) ");
bb[0]=0;read(0,bb,4);
if ((bb[0]&0xdf)-'Y') return(5);
}
fb=x;
if (blk13ex(0x42,k,x,buff,1)) goto rerr;
if (buff[5]&0xffff0000) goto notfat;
if ((buff[20]&0xffff0000)-0x41460000) goto notfat;
if (buff[21]-0x20323354) goto notfat;
if ((bb[11]) || (bb[12]-2)) {printf("Large Sector Format Not Supported\n");return(20);}
cs=bb[13];y= *(unsigned int *)(bb+14);n=bb[16];fs=buff[9];
if (buff[8]>(z-x)) {printf("Length Longer Than Partition\n");return(20);}
if (buff[8]<(z-x)) z=x+buff[8];
fb=x+y;fb2=fb+fs;base=fb+(n*fs)-cs-cs;end=z-cs+1;m=0;fp=4096;
while(base<end) {
if (fp==4096) {
if (blk13ex(0x42,k,fb,buff,32)) goto rerr;
if (blk13ex(0x42,k,fb2,buff+4096,32)) goto rerr;
fp=0;fb+=32;fb2+=32;
}
if (buff[fp]-buff[fp+4096]) {printf("FAT Table Mismatch Found - Run SCANDISK - Then Restart TRIM\n");return(20);}
switch(m) {
case 0: if (buff[fp]) break;
        st=base;m=1;break;
case 1: if (buff[fp]==0) break;
        if (add(st,base)) return(20);
        m=0;
};
base+=cs;fp++;
}
if (m==1) if (add(st,base)) return(20);
goto done;
}
if (c==2) return(0);
if (c&1) {printf("Missing Range End\n");return(20);}
printf("Warning - Selected Regions will be IRREVERSIBLY ERASED!\nType \042Erase\042 to Continue, Press ENTER to Abort\n> ");
bb[0]=0;read(0,bb,12);
if (strncmp(bb,"Erase",5)) return(5);
for (i=2,j=0;i<c;i+=2) {
st=getnum(v[i])+x;y=getnum(v[i+1])+x;
if ((y>z) || (y<=st)) {printf("Invalid Range\n");return(20);}
if (add(st,y)) return(20);
}
done: if (j) {

#ifndef TESTMODE
l=trimcmd(k,b);
if (l) {printf("TRIM Failed Code %d\n",l);return(20);}
#endif

}
printf("DONE    \n");return(0);
rerr: printf("Read Error on Sector %ld\n",fb);return(20);
notfat: printf("Not FAT32 Formatted\n");return(20);
}
