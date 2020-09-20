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
0x52,0x0d,0x0a,0x00,0xa9,0x00,0x00,0x00,0xf0,0x75,0x01,0xc3,0xc1,0xc0,0x08,0x66,
0x8b,0x57,0x45,0xee,0xb0,0x00,0x42,0xee,0x42,0xee,0xc1,0xc8,0x08,0xc3,0x50,0xb0,
0x00,0xee,0x58,0xee,0x8a,0x4b,0x22,0xd3,0xe0,0xc3,0x57,0x0d,0x0a,0x00,0xb0,0xc8,
0xe8,0x27,0x00,0x00,0x00,0xee,0xb0,0x09,0xc3,0xb0,0xca,0xe8,0x1c,0x00,0x00,0x00,
0xee,0xb0,0x01,0xc3,0xb0,0x40,0x80,0x4f,0x2e,0x04,0xe8,0x0d,0x00,0x00,0x00,0xee,
0xc3,0xe8,0x06,0x00,0x00,0x00,0xee,0xe9,0x00,0x00,0x00,0x00,0xf6,0x43,0x13,0xf0,
0x75,0x05,0xc3,0x50,0x0d,0x0a,0x00,0x3c,0x20,0x75,0x03,0xb0,0x24,0xc3,0x3c,0x30,
0x75,0x03,0xb0,0x34,0xc3,0x3c,0x40,0x75,0x03,0xb0,0x42,0xc3,0x3c,0xc4,0x75,0x03,
0xb0,0x29,0xc3,0x3c,0xc5,0x75,0x03,0xb0,0x39,0xc3,0x3c,0xc8,0x75,0x03,0xb0,0x25,
0xc3,0x3c,0xca,0x75,0x02,0xb0,0x35,0xc3};

char cr[]="‚€€€€€€‚    48 Bit LBA Patch 1.1    Copyright (C) 2003-2004 by Rudolph R. Loew. All Rights Reserved.    ";

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

int main(int c,char **v)
{
unsigned char *b;
unsigned long j,k,ad1,ad2,ad3;
int e,f,ff,ver;
char bb[512],bbb[512];
printf("\n48 Bit LBA Patch  Ver 1.1\n\nCopyright (C) 2003-2004 by Rudolph R. Loew, All Rights Reserved.\n\n");
e=20;ver=0;
if (c>1) {
if (strcmp(v[1],"/?")==0) {printf("PATCHATA [-Verify] [PDR_File]\n");return(0);}
if (v[1][0]=='-') {ver=1;c--;v++;}
}
b=(unsigned char *)malloc(32000);
if (b==0) {printf("Not Enough Memory\n");goto chk;}
if (c>1) {strcpy(bb,v[1]);goto man;}
f=_open("C:\\MSDOS.SYS",0);
if (f<0) {printf("Cannot Open C:\\MSDOS.SYS\n");goto manual;}
while(j=rl(f,b)) if (j>9) {
if (b[6]=='=') b[6]=0;
if (cmp(b,"WINDIR")==0) goto fnd1;
}
_close(f);printf("Cannot Locate Windows Directory\n");goto manual;
fnd1: _close(f);strcpy(bb,(char *)b+7);
strcat(bb,"\\system\\iosubsys\\esdi_506.pdr");
man: _dos_setfileattr(bb,0);strcpy(bbb,bb);
f=_open((char *)bb,4);
if (f<0) {printf("%s not found or inaccessible\n",bb);goto manual;}
fs=_read(f,b,32000);
if ((fs<0x300) || (fs>31999)) {printf("Invalid File Size\n");goto quit;}
fs-=0x98;j=find(0,b,patch);
if (j+1) {
if (ver) {printf("Patch Verified\n");e=0;goto quit;}
printf("File Already Patched - Uninstall ? (Y/N) ");_read(0,b,4);
if ((b[0]&0xdf)-'Y') goto quit;
fs+=0x98-strlen(cr);j=strlen(bb);
if (j>4) if (bb[j-4]=='.') {
bb[j-3]='b';bb[j-2]='a';bb[j-1]='k';
ff=_open(bb,0);
if (ff<0) {printf("Cannot Open Backup File %s\n",bb);goto quit;}
if (_read(ff,(char *)b,fs+1)-fs) {
printf("Invalid Backup File\n");goto quit;
}
j=fs;chsize(f,j);lseek(f,0L,0);
if (_write(f,(char *)b,fs)<fs) {
printf("Error Uninstalling Patch\n");goto quit;
}
_close(ff);_close(f);printf("Patch Removed\n");unlink(bb);return(0);
}
else {printf("No Backup Created for This FileName\n");goto quit;}
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
printf("Cannot Determine Patch Area\n");goto chk;
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
ff=_creat(bb,0);
}
if (ff<0) {
printf("Cannot Make Backup of File - Continue ? (Y/N) ");
_read(0,bb,4);
if ((bb[0]&0xdf)-'Y') {printf("Patch Aborted\n");return(20);}
}
if (ff>0) {
if (_write(ff,(char *)b,(fs+0x98))<(fs+0x98)) {
printf("Error Backing up File\n");goto chk;
}
_close(ff);
}
bb[0]=0xe8;bb[5]=bb[6]=0x90;k=ad2-ad1-5;
lseek(f,ad1,0);*(unsigned long *)(bb+1)=k+sub1;j=ref1[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel2,0);*(unsigned long *)(bb+1)=k+sub2-rel2;j=ref2[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel3,0);*(unsigned long *)(bb+1)=k+sub3-rel3;j=ref3[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel4,0);*(unsigned long *)(bb+1)=k+sub4-rel4;j=ref4[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel5,0);*(unsigned long *)(bb+1)=k+sub5-rel5;j=ref5[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel6,0);*(unsigned long *)(bb+1)=k+sub6-rel6;j=ref6[0];
if (_write(f,bb,j)<j) goto perr;
lseek(f,ad1+rel7,0);*(unsigned long *)(bb+1)=k+sub7-rel7;
if (_write(f,bb,6)<6) goto perr;
lseek(f,ad2,0);j=patch[0];*(unsigned long *)(patch+j+1)=ad3-ad2-j-4;
if (_write(f,(char *)patch+1,0x98)<0x98) goto perr;
lseek(f,0L,2);j=strlen(cr);
if (_write(f,cr,j)<j) {
perr: printf("Error Patching File\n");goto chk;
}
_close(f);_dos_setfileattr(bbb,7);printf("Patch Completed\n");return(0);
manual: printf("\nRerun command specifying full path to ESDI_506.PDR file\n");
goto chk;
bad: printf("Cannot Patch This Version\n");goto chk;
quit: _close(f);_dos_setfileattr(bbb,7);
chk: if (ver) if (e) {printf("Press Enter To Continue or RESET to Reboot \n");_read(0,bb,4);}
return(e);
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
lp: j=_read(f,b+i,1);
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

