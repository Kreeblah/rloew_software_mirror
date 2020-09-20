unsigned char ref[][7]={
{0xee,0x8a,0x4b,0x22,0xd3,0xe0},
{0xa9,0,0,0,0xf0,0x75,0x2b},
{0xb0,0xc8,0xee,0xb0,9},
{0x80,0x4f,0x2e,4,0xee},
{0xb0,0xca,0xee,0xb0,1},
{0x80,0x4f,0x2e,4,0xb0,0x40,0xee},
{0xee,0xe8}
};

int len[]={6,7,5,5,5,7,2};
int rel[]={0,0x1b,0x1aa,0x1b8,0x1dc,0x240,0x1fc};

unsigned char patch[]={
// blk 0
0x50,0xb0,0x00,0xee,0x58,0xee,0x8a,0x4b,0x22,0xd3,0xe0,0xc3,
// blk 1
0x3d,0x00,0xff,0xff,0x0f,0x73,0x01,0xc3,
0xc1,0xc0,0x08,
0x3c,0x10,0x76,0x02,0xb0,0x10, // Demo Insert
0x66,0x8b,0x57,0x45,0xee,0xb0,0x00,0x42,0xee,0x42,0xee,0xc1,0xc8,0x08,0xc3,
// blk 2 calls blk 7
0xb0,0xc8,0xe8,0x27,0x00,0x00,0x00,0xee,0xb0,0x09,0xc3,
// blk 4 calls blk 7
0xb0,0xca,0xe8,0x1c,0x00,0x00,0x00,0xee,0xb0,0x01,0xc3,
// blk 5 falls thru to blk 3
0xb0,0x40,
// blk 3 calls blk 7
0x80,0x4f,0x2e,0x04,0xe8,0x0d,0x00,0x00,0x00,0xee,0xc3,
// blk 6 calls blk 7 jumps back (offset = patchp)
0xe8,0x06,0x00,0x00,0x00,0xee,0xe9,  0x00,0x00,0x00,0x00,
// blk 7
                                                     // Signature
0x3c,0x40,0x75,0x22,                                 // If Verify Sectors
0x81,0xbb,0xc0,0,0,0,0x52,0x4c,0x52,0x4c,0x75,0x16,  // If Offset MSD 4C524C52
0x81,0x3d,0xec,1,0,0,0x4c,0x52,0x4c,0x52,0x75,0xa,   // If  [1EC] =   524C524C
0xc7,5,0xec,1,0,0,6,4,0x45,0x44,                     // Set [1EC] =   44450406
// Version 4.6

0x81,0x7b,0x10,0x00,0xff,0xff,0x0f,0x73,0x01,0xc3,
0x3c,0x20,0x75,0x03,0xb0,0x24,0xc3,
0x3c,0x30,0x75,0x03,0xb0,0x34,0xc3,
0x3c,0x40,0x75,0x03,0xb0,0x42,0xc3,
0x3c,0xc4,0x75,0x03,0xb0,0x29,0xc3,
0x3c,0xc5,0x75,0x03,0xb0,0x39,0xc3,
0x3c,0xc8,0x75,0x03,0xb0,0x25,0xc3,
0x3c,0xca,0x75,0x02,0xb0,0x35,0xc3
};

int off[]={0,0xc,0x2c,0x44,0x37,0x42,0x4f};
#define patchp 0x56

#define psz (sizeof(patch))

char cr[]="                48 Bit LBA Patch 4.6  (DEMO)  Copyright (C) 2003-2006 by Rudolph R. Loew. All Rights Reserved.          ";
#define lenv (sizeof(cr)-8)
#define lenvo 12
#define lenvl 20
#define lenvv (lenvl+1)
#define lenvs (lenvl+3)
long rl(int,unsigned char *);
long find(int,int,unsigned char *,unsigned char *);

int fs;
long base;

int main(int c,char **v)
{
unsigned char *b,*b1;
long j,k,ad2,ad3;
int e,f,i,ver,upd;
char name[512],back[512],bx[8];
printf("\n48 Bit LBA Patch  Ver 4.6  (DEMO)\n\nCopyright (C) 2003-2006 by Rudolph R. Loew, All Rights Reserved.\n\n");
e=20;upd=ver=0;
if (c>1) {
if (strcmp(v[1],"/?")==0) {printf("PATCH137 [-Verify] [PDR_File]\n");return(0);}
if (v[1][0]=='-') {ver=1;c--;v++;}
}
b=(unsigned char *)malloc(32256);
if (b==0) {printf("Not Enough Memory\n");goto quit;}
if (c>1) {strcpy(name,v[1]);goto man;}
f=_open("C:\\MSDOS.SYS",0);
if (f<0) {printf("Cannot Open C:\\MSDOS.SYS\n");goto manual;}
while(j=rl(f,b)) if (j>9) {
if (b[6]=='=') b[6]=0;
if (stricmp(b,"WINDIR")==0) goto fnd1;
}
_close(f);printf("Cannot Locate Windows Directory\n");goto manual;
fnd1: _close(f);strcpy(name,(char *)b+7);
strcat(name,"\\system\\iosubsys\\Esdi_506.pdr");
man: strcpy(back,name);k=f=strlen(name);
f=k;
for (i=0;i<k;i++) if (back[i]=='.') f=i;
strcpy(back+f,".bak");
if (stricmp(name,back)==0) {printf("Name Conflicts With Backup\n");return(20);}
f=_open((char *)name,0);
if (f<0) {printf("%s Not Found or Inaccessible\n",name);goto manual;}
fs=_read(f,b,32000);
if ((fs<0x300) || (fs>31999)) {printf("Invalid File Size\n");goto quit;}
_close(f);
for (i=fs;i<32256;i++) b[i]=0;
if (find(0,lenv,b,cr)) {
if (ver) {printf("Patch Verified\n");e=0;goto quit;}
printf("File Already Patched - Uninstall ? (Y/N) ");_read(0,b,4);
if ((b[0]&0xdf)-'Y') goto quit;
_dos_setfileattr(name,0);
if (unlink(name)) {printf("Cannot Remove Patch\n");return(20);}
if (rename(back,name)) {printf("Cannot Rename Backup\n");return(20);}
printf("Patch Removed\n");return(0);
}
if (f=find(0,lenvl,b,cr+lenvo)) {
k=find(f,6,b,"(DEMO)");
if (k==0) {printf("Full Version Found - Downgrade ? (Y/N) ");goto qupd1;}
if (b[f+lenvv]<cr[lenvo+lenvv]) goto okupd;
if (b[f+lenvv]>cr[lenvo+lenvv]) goto qupd;
if (b[f+lenvs]<=cr[lenvo+lenvs]) goto okupd;
qupd: printf("Newer Version Found - Downgrade ? (Y/N) ");
qupd1: _read(0,b+32252,4);
if ((b[32252]&0xdf)-'Y') goto quit;
upd=1;
okupd: f=_open((char *)back,0);
if (f<0) {printf("Backup File Not Found or Inaccessible\n");goto quit;}
fs=_read(f,b,32000);
if ((fs<0x300) || (fs>31999)) {printf("Invalid Backup File\n");goto quit;}
_close(f);upd++;
}
base=0;
lp: base=find(base+1,len[0],b,ref[0]);
if (base==0) goto bad;
for (i=1;i<6;i++) {
if (find(base,len[i],b,ref[i])-base-rel[i]) goto lp;
}
if (find(base+rel[6],len[6],b,ref[6])-base-rel[6]) goto lp;
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
ad2+=ad3;ad3= *(unsigned long *)(b+base+rel[6]+2)+base+rel[6]+6;
j= *(unsigned long *)(b+base+rel[6]+7)+base+rel[6]+11;
k= *(unsigned long *)(b+base+rel[6]+12)+base+rel[6]+16;
if ((ad3-j) || (ad3-k)) goto bad;
bx[0]=0xe8;bx[5]=bx[6]=0x90;k=ad2-base-5;b1=b+base;
for (i=0;i<6;i++) {
*(unsigned long *)(bx+1)=k+off[i]-rel[i];memcpy(b1+rel[i],bx,len[i]);
}
*(unsigned long *)(bx+1)=k+off[6]-rel[6];memcpy(b1+rel[6],bx,6);
j=patchp;*(unsigned long *)(patch+j)=ad3-ad2-j-4;
memcpy(b+ad2,(char *)patch,psz);memcpy(b+ad2+psz,cr,strlen(cr));
if (upd) {
_dos_setfileattr(name,0);
}
else {
unlink(back);
if (rename(name,back)) {printf("Cannot Rename File\n");goto quit;}
}
f=_creat(name,0);
if (f<0) {printf("Cannot Create Patch File\n");goto undo;}
if (_write(f,b,fs)<fs) {
printf("Error Patching File\n");_close(f);unlink(name);
undo: rename(back,name);goto quit;
}
_close(f);_dos_setfileattr(name,7);
switch (upd) {
case 0: printf("Patch Completed\n");break;
case 1: printf("Patch Upgraded\n");break;
case 2: printf("Patch Downgraded\n");
};
return(0);
manual: printf("\nRerun Command Specifying Full Path to ESDI_506.PDR File\n");
goto quit;
bad: printf("Cannot Patch This Version\n");
quit: if (ver) if (e) {printf("Press Enter to Continue or RESET to Reboot \n");_read(0,back,4);}
return(e);
}

long rl(int f,unsigned char *b)
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

long find(int i,int j,unsigned char *b,unsigned char *s)
{
int k;
for (;i<fs;i++) {
for (k=0;k<j;k++) if (b[i+k]-s[k]) goto diff;
return(i);
diff:;
}
return(0);
}
