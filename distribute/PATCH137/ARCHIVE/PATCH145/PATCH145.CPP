#include <windows.h>
#include <stdio.h>
#include <io.h>

unsigned char ref1[]={6,0xee,0x8a,0x4b,0x22,0xd3,0xe0};
unsigned char ref2[]={7,0xa9,0,0,0,0xf0,0x75,0x2b};
unsigned char ref3[]={5,0xb0,0xc8,0xee,0xb0,9};
unsigned char ref4[]={5,0x80,0x4f,0x2e,4,0xee};
unsigned char ref5[]={5,0xb0,0xca,0xee,0xb0,1};
unsigned char ref6[]={7,0x80,0x4f,0x2e,4,0xb0,0x40,0xee};
unsigned char ref7[]={2,0xee,0xe8};
unsigned char str1[]="*(ESDI)ESDITRAP: VM byte read of port %e\r\n";
unsigned char str2[]="9(ESDI)ESDITRAP: VM byte write of port %e with value %b\r\n";
unsigned char str3[]="8(ESDI)ESDITRAP: VM byte port of port %e with value %e\r\n";
unsigned char patch[]={0x58,
0x52,0x0d,0x0a,0x00,0xa9,0x00,0x00,0x00,0xf0,0x75,0x01,0xc3,0x50,0xb0,0x10,0x66,
0x8b,0x57,0x45,0xee,0xb0,0x00,0x42,0xee,0x42,0xee,0x58,0xc3,0x52,0x4c,0x50,0xb0,
0x00,0xee,0x58,0xee,0x8a,0x4b,0x22,0xd3,0xe0,0xc3,0x52,0x0d,0x0a,0x00,0xb0,0xc8,
0xe8,0x27,0x00,0x00,0x00,0xee,0xb0,0x09,0xc3,0xb0,0xca,0xe8,0x1c,0x00,0x00,0x00,
0xee,0xb0,0x01,0xc3,0xb0,0x40,0x80,0x4f,0x2e,0x04,0xe8,0x0d,0x00,0x00,0x00,0xee,
0xc3,0xe8,0x06,0x00,0x00,0x00,0xee,0xe9,0x00,0x00,0x00,0x00,0xf6,0x43,0x13,0xf0,
0x75,0x05,0xc3,0x4c,0x0d,0x0a,0x00,0x3c,0x20,0x75,0x03,0xb0,0x24,0xc3,0x3c,0x30,
0x75,0x03,0xb0,0x34,0xc3,0x3c,0x40,0x75,0x03,0xb0,0x42,0xc3,0x3c,0xc4,0x75,0x03,
0xb0,0x29,0xc3,0x3c,0xc5,0x75,0x03,0xb0,0x39,0xc3,0x3c,0xc8,0x75,0x03,0xb0,0x25,
0xc3,0x3c,0xca,0x75,0x02,0xb0,0x35,0xc3};

unsigned long rel2=0x1b;
unsigned long rel3=0x1aa;
unsigned long rel4=0x1b8;
unsigned long rel5=0x1dc;
unsigned long rel6=0x240;
unsigned long rel7=0x1fc;
unsigned long relb=0x2a;
unsigned long relc=0x63;
unsigned long sub1=0x1e;
unsigned long sub2=0x4;
unsigned long sub3=0x2e;
unsigned long sub4=0x46;
unsigned long sub5=0x39;
unsigned long sub6=0x44;
unsigned long sub7=0x51;

int cmp(unsigned char *,char *);
unsigned long rl(int,unsigned char *);
unsigned long find(int,unsigned char *,unsigned char *);

int fs;

char fn[256];
OPENFILENAME nam={sizeof(OPENFILENAME),0,0,0,0,0,0,fn,256,0,0,".",
"ESDI_506.PDR",OFN_FILEMUSTEXIST|OFN_NONETWORKBUTTON|OFN_HIDEREADONLY,
0,0,"pdr",0,0,0};

int APIENTRY WinMain(HINSTANCE h,HINSTANCE p,LPSTR l,int c)
{
unsigned char *b;
unsigned long j,k,ad1,ad2,ad3;
int i,f,ff;
char bb[512];
MessageBox(0,"Copyright (C) 2004 by Rudolph R. Loew, All Rights Reserved.","PATCH145 Copyright Notice",MB_ICONINFORMATION|MB_TOPMOST|MB_OK);
b=(unsigned char *)malloc(65536);
if (b==0) {MessageBox(0,"Not Enough Memory","PATCH145 ERROR",MB_ICONSTOP|MB_TOPMOST|MB_OK);return(20);}
f=_lopen("C:\\MSDOS.SYS",0);
if (f<0) goto manual;
while(j=rl(f,b)) if (j>9) {
if (b[6]=='=') b[6]=0;
if (cmp(b,"WINDIR")==0) goto fnd1;
}
_lclose(f);
manual: fn[0]=0;
if (GetOpenFileName(&nam)==0) return(20);
strcpy(bb,nam.lpstrFile);goto man;
fnd1: _lclose(f);strcpy(bb,(char *)b+7);
strcat(bb,"\\system\\iosubsys\\esdi_506.pdr");
man: f=_lopen((char *)bb,OF_READWRITE);
if (f<0) goto manual;
fs=_lread(f,b,65536);
if ((fs<0x300) || (fs>65535)) {MessageBox(0,"Invalid File","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);}
fs-=0x98;j=find(0,b,patch);
if (j+1) {
i=MessageBox(0,"File Already Patched - Uninstall ?","PATCH145",MB_ICONQUESTION|MB_TOPMOST|MB_YESNO);
if (i-IDYES) {
MessageBox(0,"Uninstall Aborted","PATCH145",MB_ICONSTOP|MB_TOPMOST|MB_OK);
return(10);
}
j=strlen(bb);
if (j>4) if (bb[j-4]=='.') {
bb[j-3]='b';bb[j-2]='a';bb[j-1]='k';
ff=_lopen(bb,0);
if (ff<0) {MessageBox(0,"Cannot Access Backup File","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);}
if (_lread(ff,(char *)b,fs+0x99)-(fs+0x98)) {
MessageBox(0,"Invalid Backup File","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
}
_llseek(f,0,0);
if (_lwrite(f,(char *)b,(fs+0x98))<(fs+0x98)) {
MessageBox(0,"Error Uninstalling Patch","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
}
_lclose(ff);_lclose(f);MessageBox(0,"Patch Removed","PATCH145",MB_ICONINFORMATION|MB_TOPMOST|MB_OK);DeleteFile(bb);return(0);
}
else {MessageBox(0,"No Backup File Found","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);}
}
ad1=find(0,b,ref1);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref1);
if ((j+1)==0) goto got1;
ad1=find(0,b,ref2);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref2);
if ((j+1)==0) goto got1;
ad1=find(0,b,ref3);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref3);
if ((j+1)==0) goto got1;
ad1=find(0,b,ref4);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref4);
if ((j+1)==0) goto got1;
ad1=find(0,b,ref5);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref5);
if ((j+1)==0) goto got1;
ad1=find(0,b,ref6);
if ((ad1+1)==0) goto bad;
j=find(ad1+1,b,ref6);
if ((j+1)==0) goto got1;
MessageBox(0,"Unable to Patch This Version","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
got1: if (find(ad1,b,ref1)-ad1) goto bad;
if (find(ad1+rel2,b,ref2)-ad1-rel2) goto bad;
if (find(ad1+rel3,b,ref3)-ad1-rel3) goto bad;
if (find(ad1+rel4,b,ref4)-ad1-rel4) goto bad;
if (find(ad1+rel5,b,ref5)-ad1-rel5) goto bad;
if (find(ad1+rel6,b,ref6)-ad1-rel6) goto bad;
if (find(ad1+rel7,b,ref7)-ad1-rel7) goto bad;
ad2=find(0,b,str1);
if ((ad2+1)==0) goto bad;
j=find(ad2+1,b,str1);
if (j+1) goto bad;
if (find(ad2+relb,b,str2)-ad2-relb) goto bad;
if (find(ad2+relc,b,str3)-ad2-relc) goto bad;
ad3= *(unsigned long *)(b+ad1+rel7+2)+ad1+rel7+6;
j= *(unsigned long *)(b+ad1+rel7+7)+ad1+rel7+11;
k= *(unsigned long *)(b+ad1+rel7+12)+ad1+rel7+16;
if ((ad3-j) || (ad3-k)) goto bad;
ff= -1;j=strlen(bb);
if (j>4) if (bb[j-4]=='.') {
bb[j-3]='b';bb[j-2]='a';bb[j-1]='k';
ff=_lcreat(bb,0);
}
if (ff<0) {
i=MessageBox(0,"Cannot Make Backup Of File - Continue ?","PATCH145 ERROR",MB_ICONQUESTION|MB_TOPMOST|MB_YESNO);
if (i-IDYES) {MessageBox(0,"Patch Aborted","PATCH145 ERROR",MB_ICONSTOP|MB_TOPMOST|MB_OK);return(20);}
}
if (ff>0) {
if (_lwrite(ff,(char *)b,(fs+0x98))<(fs+0x98)) {
MessageBox(0,"Error Backing Up File","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
}
_lclose(ff);
}
bb[0]=0xe8;bb[5]=bb[6]=0x90;k=ad2-ad1-5;
_llseek(f,ad1,0);*(unsigned long *)(bb+1)=k+sub1;j=ref1[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel2,0);*(unsigned long *)(bb+1)=k+sub2-rel2;j=ref2[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel3,0);*(unsigned long *)(bb+1)=k+sub3-rel3;j=ref3[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel4,0);*(unsigned long *)(bb+1)=k+sub4-rel4;j=ref4[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel5,0);*(unsigned long *)(bb+1)=k+sub5-rel5;j=ref5[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel6,0);*(unsigned long *)(bb+1)=k+sub6-rel6;j=ref6[0];
if (_lwrite(f,bb,j)<j) goto png;
_llseek(f,ad1+rel7,0);*(unsigned long *)(bb+1)=k+sub7-rel7;
if (_lwrite(f,bb,6)<6) goto png;
_llseek(f,ad2,0);j=patch[0];*(unsigned long *)(patch+j+1)=ad3-ad2-j-4;
if (_lwrite(f,(char *)patch+1,0x98)<0x98) {
png: MessageBox(0,"Error Patching File","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
}
_lclose(f);MessageBox(0,"Patch Completed","PATCH145",MB_ICONINFORMATION|MB_TOPMOST|MB_OK);return(0);
bad: MessageBox(0,"Unable to Patch This Version","PATCH145 ERROR",MB_ICONWARNING|MB_TOPMOST|MB_OK);return(20);
}

int cmp(unsigned char *a,char *b)
{
lp: if (((*a)>='a') && ((*a)<='z')) (*a)-=32;
if ((*a)-(*b)) return(1);
if (*a) {a++;b++;goto lp;}
return(0);
}

unsigned long rl(int f,unsigned char *b)
{
int i,j;
i=0;
lp: j=_lread(f,b+i,1);
if (j<1) return(0);
if (b[i]<32) {
if (i==0) goto lp;
b[i]=0;return(i);
}
if (i<255) i++;
goto lp;
}

unsigned long find(int i,unsigned char *b,unsigned char *s)
{
int j,k;
j= *(s++);
for (;i<fs;i++) {
for (k=0;k<j;k++) if (b[i+k]-s[k]) goto diff;
return(i);
diff:;
}
return(-1);
}

