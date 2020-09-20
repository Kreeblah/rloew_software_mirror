unsigned char ref1[]={6,0xee,0x8a,0x4b,0x22,0xd3,0xe0};
unsigned char ref2[]={7,0xa9,0,0,0,0xf0,0x75,0x2b};
unsigned char ref3[]={5,0xb0,0xc8,0xee,0xb0,9};
unsigned char ref4[]={5,0x80,0x4f,0x2e,4,0xee};
unsigned char ref5[]={5,0xb0,0xca,0xee,0xb0,1};
unsigned char ref6[]={7,0x80,0x4f,0x2e,4,0xb0,0x40,0xee};
unsigned char ref7[]={2,0xee,0xe8};
unsigned char patch[]={0x50,
0xa9,0x00,0x00,0x00,0xf0,0x75,0x01,0xc3,0xc1,0xc0,0x08,0xb0,0x10,0x66,0x8b,0x57,0x45,0xee,
0xb0,0x00,0x42,0xee,0x42,0xee,0xeb,0x72,0x50,0xb0,0x00,0xee,0x58,0xee,
0x8a,0x4b,0x22,0xd3,0xe0,0xc3,0xb0,0xc8,0xe8,0x27,0x00,0x00,0x00,0xee,0xb0,0x09,
0xc3,0xb0,0xca,0xe8,0x1c,0x00,0x00,0x00,0xee,0xb0,0x01,0xc3,0xb0,0x40,0x80,0x4f,
0x2e,0x04,0xe8,0x0d,0x00,0x00,0x00,0xee,0xc3,0xe8,0x06,0x00,0x00,0x00,0xee,0xe9,
0x00,0x00,0x00,0x00,0xf6,0x43,0x13,0xf0,0x75,0x01,0xc3,0x3c,0x20,0x75,0x03,0xb0,
0x24,0xc3,0x3c,0x30,0x75,0x03,0xb0,0x34,0xc3,0x3c,0x40,0x75,0x03,0xb0,0x42,0xc3,
0x3c,0xc4,0x75,0x03,0xb0,0x29,0xc3,0x3c,0xc5,0x75,0x03,0xb0,0x39,0xc3,0x3c,0xc8,
0x75,0x03,0xb0,0x25,0xc3,0x3c,0xca,0x75,0x02,0xb0,0x35,0xc3,0xc1,0xc8,0x08,0xc3};

char cr[]="                48 Bit LBA Patch 2.0a (DEMO) Copyright (C) 2003-2004 by Rudolph R. Loew. All Rights Reserved.          ";

#define psz (sizeof(patch)-1)

unsigned long rel2=0x1b;
unsigned long rel3=0x1aa;
unsigned long rel4=0x1b8;
unsigned long rel5=0x1dc;
unsigned long rel6=0x240;
unsigned long rel7=0x1fc;
unsigned long sub1=0x1a;
unsigned long sub2=0x0;
unsigned long sub3=0x26;
unsigned long sub4=0x3e;
unsigned long sub5=0x31;
unsigned long sub6=0x3c;
unsigned long sub7=0x49;

unsigned long rl(int,unsigned char *);
unsigned long find(int,unsigned char *,unsigned char *);

int fs;

int main(int c,char **v)
{
unsigned char *b,*b1;
unsigned long j,k,ad1,ad2,ad3;
int e,f,ver;
char bb[512],bbb[512],bx[8];
printf("\n48 Bit LBA Patch  Ver 2.0a (DEMO)\n\nCopyright (C) 2003-2004 by Rudolph R. Loew, All Rights Reserved.\n\n");
e=20;ver=0;
if (c>1) {
if (strcmp(v[1],"/?")==0) {printf("PATCHATA [-Verify] [PDR_File]\n");return(0);}
if (v[1][0]=='-') {ver=1;c--;v++;}
}
b=(unsigned char *)malloc(32256);
if (b==0) {printf("Not Enough Memory\n");goto quit;}
if (c>1) {strcpy(bb,v[1]);goto man;}
f=_open("C:\\MSDOS.SYS",0);
if (f<0) {printf("Cannot Open C:\\MSDOS.SYS\n");goto manual;}
while(j=rl(f,b)) if (j>9) {
if (b[6]=='=') b[6]=0;
if (stricmp(b,"WINDIR")==0) goto fnd1;
}
_close(f);printf("Cannot Locate Windows Directory\n");goto manual;
fnd1: _close(f);strcpy(bb,(char *)b+7);
strcat(bb,"\\system\\iosubsys\\esdi_506.pdr");
man: strcpy(bbb,bb);k=f=strlen(bb);
for (j=0;j<k;j++) if (bb[j]=='.') f=j;
if (f<k) strcpy(bb+f+1,"bak");
f=_open((char *)bbb,0);
if (f<0) {printf("%s not found or inaccessible\n",bb);goto manual;}
fs=_read(f,b,32000);
if ((fs<0x300) || (fs>31999)) {printf("Invalid File Size\n");goto quit;}
_close(f);
for (j=fs;j<32256;j++) b[j]=0;
j=find(0,b,patch);
if (j+1) {
if (ver) {printf("Patch Verified\n");e=0;goto quit;}
printf("File Already Patched - Uninstall ? (Y/N) ");_read(0,b,4);
if ((b[0]&0xdf)-'Y') goto quit;
if (strcmp(bb,bbb)==0) {printf("No Backup Created for This FileName\n");return(20);}
_dos_setfileattr(bbb,0);
if (unlink(bbb)) {printf("Cannot Remove Patch\n");return(20);}
if (rename(bb,bbb)) {printf("Cannot Rename Backup\n");return(20);}
printf("Patch Removed\n");return(0);
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
printf("Cannot Determine Patch Area\n");goto quit;
got1: if (find(ad1,b,ref1)-ad1) goto bad;
if (find(ad1+rel2,b,ref2)-ad1-rel2) goto bad;
if (find(ad1+rel3,b,ref3)-ad1-rel3) goto bad;
if (find(ad1+rel4,b,ref4)-ad1-rel4) goto bad;
if (find(ad1+rel5,b,ref5)-ad1-rel5) goto bad;
if (find(ad1+rel6,b,ref6)-ad1-rel6) goto bad;
if (find(ad1+rel7,b,ref7)-ad1-rel7) goto bad;
j= *(short *)(b+0x18);
if (j<0x40) goto bad;
j= *(long *)(b+0x3c);
if ((j<0x40) || (j>fs)) goto bad;
k= *(long *)(b+j+0x40);
if ((k<0xc4) || (k>fs)) goto bad;
ad2=f= *(long *)(b+j+k);
if (ad2>fs) goto bad;
ad3= *(long *)(b+j+0x80);
if ((ad3<0x15c) || (ad3>fs)) goto bad;
ad2+=(-ad2-ad3-psz)&15;k= *(long *)(b+j+k)=ad2+psz+strlen(cr);
if (((k-1)&0x1000)-((f-1)&0x1000)) goto bad;
ad2+=ad3;ad3= *(unsigned long *)(b+ad1+rel7+2)+ad1+rel7+6;
j= *(unsigned long *)(b+ad1+rel7+7)+ad1+rel7+11;
k= *(unsigned long *)(b+ad1+rel7+12)+ad1+rel7+16;
if ((ad3-j) || (ad3-k)) goto bad;
unlink(bb);
if (rename(bbb,bb)) {printf("Cannot Rename File\n");goto quit;}
bx[0]=0xe8;bx[5]=bx[6]=0x90;k=ad2-ad1-5;b1=b+ad1;
*(unsigned long *)(bx+1)=k+sub1;memcpy(b1,bx,ref1[0]);
*(unsigned long *)(bx+1)=k+sub2-rel2;memcpy(b1+rel2,bx,ref2[0]);
*(unsigned long *)(bx+1)=k+sub3-rel3;memcpy(b1+rel3,bx,ref3[0]);
*(unsigned long *)(bx+1)=k+sub4-rel4;memcpy(b1+rel4,bx,ref4[0]);
*(unsigned long *)(bx+1)=k+sub5-rel5;memcpy(b1+rel5,bx,ref5[0]);
*(unsigned long *)(bx+1)=k+sub6-rel6;memcpy(b1+rel6,bx,ref6[0]);
*(unsigned long *)(bx+1)=k+sub7-rel7;memcpy(b1+rel7,bx,6);
j=patch[0];*(unsigned long *)(patch+j+1)=ad3-ad2-j-4;
memcpy(b+ad2,(char *)patch+1,psz);memcpy(b+ad2+psz,cr,strlen(cr));
f=_creat(bbb,0);
if (f<0) {printf("Cannot Create Patch File\n");goto undo;}
if (_write(f,b,fs)<fs) {
printf("Error Patching File\n");_close(f);unlink(bbb);
undo: rename(bb,bbb);goto quit;
}
_close(f);_dos_setfileattr(bbb,7);printf("Patch Completed\n");return(0);
manual: printf("\nRerun command specifying full path to ESDI_506.PDR file\n");
goto quit;
bad: printf("Cannot Patch This Version\n");
quit: if (ver) if (e) {printf("Press Enter To Continue or RESET to Reboot \n");_read(0,bb,4);}
return(e);
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

