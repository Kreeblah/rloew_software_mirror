#define PRO     // SELF, PRO, DEMO

unsigned char ref[][13]={
{0xee,0x8a,0x4b,0x22,0xd3,0xe0},
{0xa9,0,0,0,0xf0,0x75,0x2b, 0xf6,0x43,0x21,1,0x75,0x2b},  // +6 0x2b -> 0x31  95 Version 1111
{0xb0,0xc8,0xee,0xb0,9},
{0x80,0x4f,0x2e,4,0xee},
{0xb0,0xca,0xee,0xb0,1},
{0x80,0x4f,0x2e,4,0xb0,0x40,0xee},
{0xee,0xe8}
};

int len[]={6,7,5,5,5,7,2};             // len[1] set to 13 for 95 Version 1111
int rel[]={0,0x1b,0x1aa,0x1b8,0x1dc,0x240,0x1fc,1};  // Rel 7 1=98 6,0=95 Flag

// blk 0
unsigned char p[]={
0x50,0xb0,0x00,0xee,0x58,0x66,0x8b,0x57,0x43,0xee,
0x8a,0x4b,0x22,0xd3,0xe0,0xc3
};

// blk 1
unsigned char p1a[]={
0x81,0xbb,0xc0,0,0,0,0,0,0x4c,0x52,0x75,4,0xc6,0x43,0x20,2,  // Force Verify if MSD = 524C0000
0x51,0x8b,0x8e,0xbb,0x00,0x00,0x00
};

unsigned char p1b[]={
0xf6,0x81,0xad,0x00,0x00,0x00,0x04,0x59,0x75,0x01   // Test 48-Bit LBA Enable Flag
                                                    // Replaced for Windows 98
};

unsigned char p1c[]={
0xc3,
0xc1,0xc0,0x08,

#ifdef DEMO
0x3c,0x10,0x76,0x02,0xb0,0x10,                      // Demo Insert
#endif

0x66,0x8b,0x57,0x45,0xee,
0xb0,0x00,0x66,0x8b,0x57,0x47,0xee,
0x66,0x8b,0x57,0x49,0xee,0xc1,0xc8,0x08,0xc3
};

// blk 2 calls blk 7
unsigned char p2[]={
0xb0,0xc8,0xe8, 0x00,0x00,0x00,0x00, 0xee,0xb0,0x09,0xc3
};
#define o2 3

// blk 4 calls blk 7
unsigned char p4[]={
0xb0,0xca,0xe8, 0x00,0x00,0x00,0x00, 0xee,0xb0,0x01,0xc3
};
#define o4 3

// blk 5 falls thru to blk 3
unsigned char p5[]={
0xb0,0x40
};

// blk 3 calls blk 7
unsigned char p3[]={
0x80,0x4f,0x2e,0x04,0xe8, 0x00,0x00,0x00,0x00, 0xee,0xc3
};
#define o3 5

// blk 6 calls blk 7 jumps back (offset = patchp)
unsigned char p6[]={
0xe8, 0x00,0x00,0x00,0x00, 0xee,0xe9,  0x00,0x00,0x00,0x00
};
#define o6a 1
#define o6b 7

// blk 7
unsigned char p7a[]={                                // Signature
0x3c,0x40,0x75,0x27,                                 // If Verify Sectors
0x81,0xbb,0xc0,0,0,0,0,0,0x4c,0x52,0x75,0x1B,        // If Offset MSD    = 524C0000
0x51,0x8b,0x4b,0x14,
0x81,0xb9,0xfc,1,0,0,0x4c,0x52,0x4c,0x52,0x75,0xa,   // If  [Sector+1FC] = 524C524C

#ifdef DEMO
0xc7,0x81,0xfc,1,0,0,1,5,0x45,0x44,                  // Set [Sector+1FC] = 44450501
#else
0xc7,0x81,0xfc,1,0,0,1,5,0x52,0x4c,                  // Set [Sector+1FC] = 4C520501
#endif

0x59,
// Version 5.1
0x51,0x8b,0x8e,0xbb,0x00,0x00,0x00
};

unsigned char p7b[]={
0xf6,0x81, 0x03,0x02,0x00,0x00, 0x04,                // CHS Test (Modified for Windows 98)
0x75,0x02,0x59,0xc3
};
#define o7b 2

unsigned char p7c[]={
0xf6,0x81,0xad,0x00,0x00,0x00,0x04,0x59,0x75,0x01    // Test 48-Bit LBA Enable
                                                     // Replaced for Windows 98
};

unsigned char p7d[]={
0xc3,
0x3c,0x20,0x75,0x03,0xb0,0x24,0xc3,
0x3c,0x30,0x75,0x03,0xb0,0x34,0xc3,
0x3c,0x40,0x75,0x03,0xb0,0x42,0xc3,
0x3c,0xc8,0x75,0x03,0xb0,0x25,0xc3,
0x3c,0xca,0x75,0x02,0xb0,0x35,0xc3
};

#ifdef SELF
char cr[]="                48-Bit LBA Patch 5.1  Copyright (C) 2003-2006 by Rudolph R. Loew. All Rights Reserved.          ";
#endif

#ifdef PRO
char cr[]="                48-Bit LBA Patch 5.1  Copyright (C) 2003-2006 by Rudolph R. Loew. All Rights Reserved.  €€€€€€€€";
#endif

#ifdef DEMO
char cr[]="                48-Bit LBA Patch 5.1  (DEMO)  Copyright (C) 2003-2006 by Rudolph R. Loew. All Rights Reserved.          ";
#endif

#define psz (cr-p)

#define patchp (p6-p+o6b)

unsigned char patch98[]={0x81,0x79,0x78,0xff,0xff,0xff,0x0f,0x59,0x74,0x01};
#define p98a (p1b-p)
#define p98b (p7c-p)
#define p98x (p7b-p+o7b)

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
int e,f,i,ver,upd,off[7];
char name[512],back[512],bx[14];

#ifdef DEMO
printf("\n48-Bit LBA Patch  Ver 5.1  (DEMO)\n\nCopyright (C) 2003-2006 by Rudolph R. Loew, All Rights Reserved.\n\n");
#else
printf("\n48-Bit LBA Patch  Ver 5.1\n\nCopyright (C) 2003-2006 by Rudolph R. Loew, All Rights Reserved.\n\n");
#endif

e=20;upd=ver=0;
if (c>1) {

#ifdef DEMO
if (strcmp(v[1],"/?")==0) {printf("PATCH137 [-Verify] [PDR_File]\n");return(0);}
#else
if (strcmp(v[1],"/?")==0) {printf("PATCHATA [-Verify] [PDR_File]\n");return(0);}
#endif

if (v[1][0]=='-') {ver=1;c--;v++;}
}
b=(unsigned char *)malloc(32256);
if (b==0) {printf("Not Enough Memory\n");goto quit;}
off[0]=0;
off[1]=p1a-p;off[2]=p2-p;off[3]=p3-p;off[4]=p4-p;off[5]=p5-p;off[6]=p6-p;
*(int *)(p2+o2)=p7a-p2-o2-4;*(int *)(p4+o4)=p7a-p4-o4-4;
*(int *)(p3+o3)=p7a-p3-o3-4;*(int *)(p6+o6a)=p7a-p6-o6a-4;
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

#ifdef DEMO
if (k==0) {printf("Full Version Found - Downgrade ? (Y/N) ");goto qupd1;}
#else
if (k) if ((k-f)<lenv) goto okupd;
#endif

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
lp0: base=0;
lp: base=find(base+1,len[0],b,ref[0]);
if (base==0) {
if (rel[7]==1) {
for (i=2;i<8;i++) (rel[i])--;
goto lp0;
}
if (rel[7]==0) {
for (i=2;i<8;i++) (rel[i])+=6;
ref[1][6]+=6;len[1]+=6;goto lp0;
}
goto bad;
}
for (i=1;i<6;i++) {
if (find(base,len[i],b,ref[i])-base-rel[i]) goto lp;
}
if (find(base+rel[6],len[6],b,ref[6])-base-rel[6]) goto lp;
j= *(long *)(b+base+rel[1]-7);
if (j==0x203) goto seme;
if (j-0x85) goto bad;
memcpy(p+p98a,patch98,10);memcpy(p+p98b,patch98,10);
*(long *)(p+p98x)=j;
seme: j= *(short *)(b+0x18);
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
bx[0]=0xe8;k=ad2-base-5;b1=b+base;
for (i=5;i<13;i++) bx[i]=0x90;
for (i=0;i<6;i++) {
*(unsigned long *)(bx+1)=k+off[i]-rel[i];memcpy(b1+rel[i],bx,len[i]);
}
*(unsigned long *)(bx+1)=k+off[6]-rel[6];memcpy(b1+rel[6],bx,6);
j=patchp;*(unsigned long *)(p+j)=ad3-ad2-j-4;
memcpy(b+ad2,p,psz+strlen(cr));
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
