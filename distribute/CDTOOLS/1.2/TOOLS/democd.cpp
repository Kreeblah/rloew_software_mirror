/*( wtree getline parsearg catname dateconv aspi getnum )*/

#define DEMO

#define max 32

#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <time.h>
#include <sys\timeb.h>
#include <sys\utime.h>
#include <rloew.h>

struct list {
struct list *next;
struct entr *ptr;
} dir;

struct entr {
struct entr *next;
struct entr *parent;
char *name;
char *sname;
char *com;
short type;
short attr;
unsigned int size;
int date;
int sector;
BYTE *pent,*upent;
struct entr *dirs;           /* file = source */

struct list *dirsecs;        /* directory only section */
struct list *udirsecs;
int usize,usector,dirnum;
} ent;

struct _timeb tb;

#ifndef DEMO

int mon[]={-1,30,58,89,119,150,180,211,242,272,303,333,364};

char *boothead="\000CD001\001EL TORITO SPECIFICATION";
BYTE bootsec[]={
0xFA,0x33,0xC0,0x8E,0xD0,0xBC,0x00,0x7C,
0x8B,0xF4,0x8E,0xC0,0x8E,0xD8,0xFB,0xEB,
0x51,0x43,0x44,0x2D,0x52,0x4F,0x4D,0x20,
0x6E,0x6F,0x74,0x20,0x62,0x6F,0x6F,0x74,
0x61,0x62,0x6C,0x65,0x20,0x6F,0x6E,0x20,
0x74,0x68,0x69,0x73,0x20,0x73,0x79,0x73,
0x74,0x65,0x6D,0x2E,0x52,0x65,0x6D,0x6F,
0x76,0x65,0x20,0x43,0x44,0x2D,0x52,0x4F,
0x4D,0x20,0x61,0x6E,0x64,0x20,0x70,0x72,
0x65,0x73,0x73,0x20,0x45,0x4E,0x54,0x45,
0x52,0x20,0x6B,0x65,0x79,0x20,0x74,0x6F,
0x20,0x63,0x6F,0x6E,0x74,0x69,0x6E,0x75,
0x65,0x2E,0xBD,0x11,0x7C,0xB4,0x13,0xB0,
0x00,0xB9,0x23,0x00,0xB6,0x00,0xB2,0x00,
0xB7,0x00,0xB3,0x07,0xCD,0x10,0xBD,0x34,
0x7C,0xB4,0x13,0xB0,0x00,0xB9,0x2E,0x00,
0xB6,0x01,0xB2,0x00,0xB7,0x00,0xB3,0x07,
0xCD,0x10,0xB4,0x00,0xCD,0x16,0x3C,0x00,
0x74,0xF8,0x80,0xFC,0x1C,0x75,0xF3,0xEA,
0xF0,0xFF,0x00,0xF0};
char *bootdesc="\001\000\000\000Microsoft Corporation\000\000\000LIU\252";

#endif

int cdirsize=10;
int ucdirsize=10;
int filesecs=0;
int shrt=1;
int boot=0;
int sc=0;
int pad=0;
int diag=0;
int wm=0x42;
int ctl=256;
int dm=8;
int ls=0;
int sp=0;
int pos=0;
int q=0;
int neb=1;
int buffs=512;
int pkt=32;
BYTE cue[]={1,0,0,1,0,0,0,0,0x41,1,0,0x10,0,0,0,0,
0x41,1,1,0x10,0,0,2,0,1,0xaa,1,1,0,0,0,0};
BYTE mid[]={0,8,0,0,0,0,0,0,0,0,0,0};

int bt,files,dirs,secp,len,sz,ty,*hdr1,*hdr2;
BYTE *cdir,*ucdir,*rcdir,*rucdir,*bfr;
char *(vv[3]),snb[14];
int n0,n1,n2,u;
BYTE **buff,*b;
HANDLE hh;
BYTE sen[16];

int pr(char *,char *,struct _finddata_t *,int,int,int);
void sname(struct entr *);
void scandir(struct entr *,int);
void fixroot(struct entr *);
void makedate(int,BYTE *);
BYTE *alloc(struct list *);
char *makeshort(char *,int);
char *str(char *);
char *parse(char *,int,int *);
int bsize(struct entr *,char *,int);
int build(BYTE *,struct entr *,char *,int);
void scanfile(struct entr *);
void bcdir(),nomem();
int uniq(struct entr *,char *,struct entr *);
void fixdir(struct entr *e);
void zero(BYTE *,int);
int rev(int);
void kill();

#ifndef DEMO

void writedir(struct entr *);
void writefile(struct entr *);
void xwrite(BYTE *,int);
void cdwr();

#endif

int aspicmdx(int d,int c,int o,int l,int m,BYTE *da,int l2)
{
int i;
if (diag) printf("%x: %4x %8x %4x %4x %6x -> ",d,c,o,l,m,l2);
i=aspicmd(d,c,o,l,m,da,l2,sen);
if (diag) {
if (i+2) printf("%d    \n",i);
else printf("%d    \r",i);
}
return(i);
}

main(int c,char **v)
{
int i,j,k,l,bf,btt;
char *hdr,*d,*bn,bsec[68];
printf("R. Loew CD/DVD/BD Disk Burner  Version 1.1\nCopyright (c) 2011 by Rudolph R. Loew\nAll Rights Reserved\n\n");
arg: if (c>1) if (v[1][0]=='-') {
switch(v[1][1]&0xdf) {
case   3: buffs=getnum(v[2]);c-=2;v+=2;goto arg;
case 'C': sc=1;break;
case 'D': diag=1;break;
case 'E': wm|=0x10;break;
case 'N': shrt=0;break;
case 'P': pad=1;break;
case 'T': wm=(wm& -3)|1;break;
case 'B': boot=2;bn=v[2];c-=2;v+=2;goto arg;
case 'F': if (boot) boot=(v[2][0]&7)+8;c-=2;v+=2;goto arg;
case 'S': sp=getnum(v[2]);c-=2;v+=2;goto arg;
case 'X': ctl=getnum(v[2]);dm=getnum(v[3]);ls=getnum(v[4]);c-=4;v+=4;goto arg;
case 'Q': q=1;break;
default: printf("Invalid Option\n");return(20);
};
arg1: c--;v++;goto arg;
}
if (c-4) if ((c<3) || ((c&1)==0)) {

#ifndef DEMO

printf("MAKECD [-B BootImg [-Force Mode]] [-CommentShort] [-NoShortNames] [-Pad]\n       [-Diag] [-Emulate] [-X CT DM LS] [-TAO] [-S Speed] [-# Buffers)]\n       [-Query] R.A.I.L. VolumeName PathFile | [SrcPath DestPath] ....\n");

#endif

#ifdef DEMO

printf("DEMOCD [-B BootImg [-Force Mode]] [-CommentShort] [-NoShortNames] [-Pad]\n       [-Diag] [-Emulate] [-X CT DM LS] [-TAO] [-S Speed] [-# Buffers)]\n       [-Query] R.A.I.L. VolumeName PathFile | [SrcPath DestPath] ....\n");

#endif

return(20);
}
n1= -10000;
u=getnum(v[1]);
if (u<4096) if (openaspi()==0) {printf("ASPI Not Available\n");return(20);}
if (typeaspi(u)-5) {printf("Not CD/DVD Drive\n");return(20);}
buff=(BYTE **)malloc(buffs<<2);
if (buff==0) nomem();
b=(BYTE *)malloc(max<<11);
if (b==0) nomem();
ty=1;
if (aspicmdx(u,0x246,0,32,1,b,32)>=8) {
switch(b[7]) {
case 0:  printf("NO DISK\n");return(20);
case 8:  printf("CD-ROM Disk or Drive\n");return(20);
case 9:  ty=0x80;break;
case 10: ty=0xc0;break;
case 16: printf("DVD-ROM Mode Only\n");return(20);
case 17: ty=0;break;
case 19: ty=0x50;printf("Warning - Restricted Write Support Untested\n");break;
case 20: ty=0x40;break;
case 21: ty=8;break;
case 26: ty=0x60;break;
case 27: ty=0x20;break;
case 43: ty=0x28;break;
case 67: ty=0x70;break;
default: printf("Unknown Profile\n");return(20);
};
}
if ((k=aspicmdx(u,0x25,0,8,1,b,8))==8) {
sz=b[0];sz<<=8;sz+=b[1];sz<<=8;sz+=b[2];sz<<=8;sz+=b[3];sz++;
}
else sz=1;
if (sz>1) {
if (ty==0xc0) {
printf("Disk Is Not Blank - Setting Packet Mode\n");
if (wm&16) printf("Warning - Test Mode Disabled\n");
wm&=0xec;
}
else if ((ty&0xef)-0x60) {printf("Disk Is Not Blank\n");return(20);}
}
else {
if ((ty&0xef)==0x60) {printf("Disk Is Not Formatted\n");return(20);}
}
if (ty&0x81) {
k=aspicmdx(u,0x243,0x4000000,16,1,b,16);
if (k>=16) {
if (ty==1) ty=b[6]&0xc0;
if (ty-(b[6]&0xc0)) {printf("CD Identification Error\n");return(20);}
if (wm&3) {sz=b[12];sz*=60;sz+=b[13];sz*=75;sz+=b[14];sz-=150;}
}
else {
if (ty&0x80) {printf("Cannot Read ATIP\n");return(20);}
}
}
if ((ty&0x80)==0) {
if ((k=aspicmdx(u,0x51,0,32,1,b,32))<16) {
printf("Cannot Get Track Info\n");return(20);
}
if ((ty&0xf7)==0x20) {
sz=b[20];sz<<=8;sz+=b[21];sz<<=8;sz+=b[22];sz<<=8;sz+=b[23];
}
if (b[2]&16) if (ty==1) ty=0x41;
if ((k=aspicmdx(u,0x23,0,52,1,b,52))<16) {
printf("Cannot Get Formattable Size\n");return(20);
}
if (ty&1) {
if (sz>1) ty+=0x1f;
else ty--;
}
// if (ty==0x20) {
// sz=b[4];sz<<=8;sz+=b[5];sz<<=8;sz+=b[6];sz<<=8;sz+=b[7];
// }
if (ty==0x40) {
sz=b[12];sz<<=8;sz+=b[13];sz<<=8;sz+=b[14];sz<<=8;sz+=b[15];
}
if ((ty&0xf7)==0) {
if ((k=aspicmdx(u,0x52,0,36,1,b,36))<20) {
printf("Cannot Get Size\n");return(20);
}
sz=b[16];sz<<=8;sz+=b[17];sz<<=8;sz+=b[18];sz<<=8;sz+=b[19];
}
}
if (ctl>255) {
if (wm&3) ctl=((ty&0x80) ? 4 : 5);
else {ctl=0x27;dm=0xa;}
}
if ((ty&0xe0)==0x60) wm&=0xfc;
if (ty&0x20) if (wm&2) wm--;
if ((ty&0xa0)==0) if (wm&1) wm++;
if (ty&0x20) if (wm&16) {wm&=0xef;printf("Warning - Test Mode Disabled\n");}
cue[8]=cue[16]=(ctl<<4)+1;
for (i=0;i<buffs;i++) if ((buff[i]=(BYTE *)malloc(max<<11))==0) nomem();
if (boot) {
i=boot;bf=_lopen(bn,0);
if (bf<0) {printf("Cannot Open Boot Image File\n");return(20);}
if (_lread(bf,bsec,68)<68) {printf("Bad Boot Image\n");return(20);}
l=boot=_llseek(bf,0,2);_llseek(bf,0,0);
if (boot&511) {printf("Invalid Boot Image Size\n");return(20);}
if (i==8) neb=boot>>9;
boot=(boot+2047)>>11;printf("Boot Image = %d Sectors\n",boot);
bt=4;btt=64;
if (*(short *)(bsec+22)) btt=36;
if (i<8) {
if (boot==600) bt=1;
if (boot==720) bt=2;
if (boot==1440) bt=3;
if (bt==4) if (bsec[21]== -16) {
if (bsec[26]==2) if ((*(int *)(bsec+28))==0) if (bsec[btt]==0) {
if (bsec[24]==15) bt=1;
if (bsec[24]==18) bt=2;
if (bsec[24]==36) bt=3;
}
if (bt==4) {printf("Invalid Extended Boot\n");return(20);}
}
}
if (i==8) bt=8;
if (i>8) if (bt==4) {
bt=i;
switch(bt) {
case 9:  if (boot>0x1e00) {printf("Boot Image Too Large\n");return(20);}
         break;
case 10: if (boot>0x2400) {printf("Boot Image Too Large\n");return(20);}
         break;
case 11: if (boot>0x4800) {printf("Boot Image Too Large\n");return(20);}
         break;
default: printf("Invalid Boot Mode\n");return(20);
};
}
if (bt-8) {
i= *(unsigned short *)(bsec+19);
if (i==0) i= *(int *)(bsec+32);
if (l<(i<<9)) printf("Warning - Boot Image Smaller Than File System\n");
}
printf("Boot Type = %d%s\n",bt&7,(bt&8) ? " (Forced)" : "");
}
if (v[2][0]==0) v[2]="NONAME";
bfr=(BYTE *)malloc(32768);if (bfr==0) nomem();
hdr1=(int *)malloc(4096);if (hdr1==0) nomem();
zero((BYTE *)hdr1,2048);hdr2=hdr1+512;hdr=(char *)hdr1;
hdr1[1]=0x00013130;hdr1[30]=hdr1[31]=0x1000001;hdr1[32]=0x80800;
for (i=0xbe;i<0x32d;i++) hdr[i]=32;
_ftime(&tb);d=fmtdate(tb.time);
i=(d[0]<<4)&255;i+=d[1]&15;
if (i<0x78) {hdr[0x360]='2';hdr[0x361]='0';}
else {hdr[0x360]='1';hdr[0x361]='9';}
memcpy(hdr+0x362,d,6);memcpy(hdr+0x368,d+7,6);hdr[0x36e]=hdr[0x36f]=48;
memcpy(hdr+0x32d,hdr+0x360,17);memcpy(hdr+0x33e,hdr+0x360,17);
memcpy(hdr+0x34f,hdr+0x360,17);hdr[0x371]=1;memcpy(hdr2,hdr1,2048);
for (i=4;i<0x12;i++) hdr1[i]=0x20202020;
for (i=6;i<0x12;i++) hdr2[i]=0x20002000;
hdr1[0]=0x30444301;hdr1[2]=0x4c202e52;hdr1[3]=0x2057454f;
hdr2[0]=0x30444302;hdr2[2]=0x2e005200;hdr2[3]=0x4c002000;hdr2[4]=0x45004f00;
hdr2[5]=0x20005700;
i=strlen(v[2]);
for (j=0;j<i;j++) {hdr[2088+j+j]=0;hdr[2089+j+j]=v[2][j];}
if (makeshort(v[2],0)) v[2]=snb;
memcpy(hdr1+10,v[2],strlen(v[2]));hdr2[0x16]=0x402f25;
zero((BYTE *)(&ent),sizeof(struct entr));dir.next=0;dir.ptr=0;
ent.parent= &ent;ent.date=tb.time;
printf("Building File List\n");files=0;dirs=1;
if (c-4) {
while(c>3) {
c-=2;v+=2;
if (wtree(&pr,v[1],0,0,(int)(v[2]))) return(20);
}
}
else {
i=_lopen(v[3],0);
if (i<0) {printf("Cannot Open List File\n");return(20);}
while(getline(i,(char *)bfr,512)>=0) {
if (parsearg(vv,(char *)bfr,3,32)==2) if (wtree(&pr,vv[0],0,0,(int)(vv[1]))) return(20);
}
_lclose(i);
}
printf(" %d Dirs %d Files\nProcessing Names\n",dirs,files);files=dirs=0;sname(&ent);
i=(cdirsize+2047)>>11;j=(ucdirsize+2047)>>11;
hdr1[0x22]=rev(cdirsize);hdr1[0x21]=cdirsize;
hdr2[0x22]=rev(ucdirsize);hdr2[0x21]=ucdirsize;
secp=18+shrt;
if (boot) secp+=boot+2;
hdr1[0x23]=secp;secp+=i;hdr1[0x25]=rev(secp);secp+=i;
if (shrt) {hdr2[0x23]=secp;secp+=j;hdr2[0x25]=rev(secp);secp+=j;}
cdir=(BYTE *)malloc(i<<12);
if (cdir==0) nomem();
ucdir=(BYTE *)malloc(j<<12);
if (ucdir==0) nomem();
zero(cdir,i<<12);zero(ucdir,j<<12);rcdir=cdir+(i<<11);rucdir=ucdir+(j<<11);
printf("Mapping Directories       \n");dirs=0;scandir(&ent,0);
printf("Linking Directories\n");dirs=0;fixroot(&ent);fixdir(&ent);
k=secp+filesecs;hdr1[0x14]=hdr2[0x14]=k;hdr1[0x15]=hdr2[0x15]=rev(k);
len=k+(pad ? 150 : 0);
printf("CD Size = %d Sectors\n",len);
printf("Building Directory Tables\n");dirs=0;bcdir();
printf("Mapping Files  \n");files=0;scanfile(&ent);
cue[29]=(len+150)/4500;cue[30]=((len+150)/75)%60;cue[31]=len%75;
if (sz<len) printf("Warning - CD Capacity is %d Sectors\n",sz);
else printf("Disk Capacity is %d Sectors\n",sz);
switch(ty) {
case 0:    printf("DVD-R  ");break;
case 8:    printf("DVD-R DL  ");break;
case 0x20: printf("DVD+R  ");break;
case 0x28: printf("DVD+R DL  ");break;
case 0x40: printf("DVD-RW  ");break;
case 0x60: printf("DVD+RW  ");break;
case 0x70: printf("BD-RE  ");break;
case 0x80: printf("CD-R  ");break;
case 0xc0: printf("CD-RW  ");break;
};
switch(wm&3) {
case 0: printf("PKT  ");break;
case 1: printf("TAO  ");break;
case 2: printf("DAO  ");break;
case 3: printf("RAW  ");
};
if (ty==0xc0) if ((wm&3)==0) {
if ((aspicmdx(u,0x52,0,32,1,b,48))==48) {
k=b[20];k<<=8;k+=b[21];k<<=8;k+=b[22];k<<=8;k+=b[23];pkt=k;
}
printf("Packet Size = %d Sectors\n",pkt);
}
printf("  %d Sectors = %02d:%02d:%02d\n",len,cue[29],cue[30],cue[31]);

#ifdef DEMO
return(0);
#endif

#ifndef DEMO

if (wm&16) printf("\nBegin Test Write (Y/N) ? ");
else printf("\nBegin Actual Writing (Y/N) ? ");
_read(0,&k,4);
if ((k&0xdf)-0x59) return(20);

hh=GetCurrentProcess();SetPriorityClass(hh,HIGH_PRIORITY_CLASS);



if (ty==0x28) {
i=((len+31)>>1)&(-16);
if ((i+i)<sz) {
mid[8]=i>>24;mid[9]=i>>16;mid[10]=i>>8;mid[11]=i;
if ((k=aspicmdx(u,0xbf,0,0x20000c,2,mid,12))<0) aspierr("Cannot Set Layer Switch Point",sen);
}
}






if ((k=aspicmdx(u,0x5a,0x5000000,0x44,1,b,0x44))<0) {
aspierr("Cannot Get Write Parameters",sen);return(20);
}
b[11]=ctl;b[12]=dm;b[13]=ls;b[16]=0;
if ((wm&3)==0) {b[16]=0x20;b[21]=pkt;}
wm1: b[10]=wm&0xef;
if (wm&16) {
if ((k=aspicmdx(u,0x1055,0,b[9]+10,2,b,b[9]+10))<0) {
if (wm&0x40) {printf("DISABLING BURN PROOFING\n");wm&=0xbf;goto wm1;}
aspierr("Cannot Set Normal Write Parameters",sen);return(20);
}
}
wm2: b[10]=wm;                                            
if ((k=aspicmdx(u,0x1055,0,b[9]+10,2,b,b[9]+10))<0) {
if (wm&0x40) {printf("DISABLING BURN PROOFING\n");wm&=0xbf;goto wm2;}
aspierr("Cannot Set Write Parameters",sen);return(20);
}
k= -1;
if (sp) k=(sp*180)-65536;
if (aspicmdx(u,0xbb,k,0,0,0,0)) {aspierr("Cannot Set Speed",sen);return(20);}
if (wm&2) {
if (ty&0x80) {
printf("Sending Cue Sheet\n");
if (aspicmdx(u,0x5d,0,32,2,cue,32)<32) {
aspierr("Cannot Send Cue Sheet",sen);return(20);
}
}
if ((ty&0xa0)==0) if ((wm&0x10)==0) {
printf("Reserving Track\n");
if (aspicmdx(u,0x53,0,len,0,0,0)<0) {
aspierr("Error Reserving Track",sen);return(20);
}
}
}
n0=n1=n2=0;
hh=CreateThread(0,0,(LPTHREAD_START_ROUTINE)cdwr,0,0,(unsigned long *)(&k));
if (hh==0) {printf("Cannot Start Writer\n");return(20);}
SetThreadPriority(hh,THREAD_PRIORITY_BELOW_NORMAL);
CloseHandle(hh);printf("Writing Header \n");
zero(bfr,32768);xwrite(bfr,32768);xwrite((BYTE *)hdr1,2048);
if (boot) {
memcpy(bfr+2048,boothead,30);bfr[2119]=shrt+19;
memcpy(bfr+2560,bootsec,156);xwrite(bfr+2048,2048);
}
if (shrt) xwrite((BYTE *)hdr2,2048);
memcpy(bfr,hdr1,8);bfr[0]=255;xwrite(bfr,2048);
if (boot) {
memcpy(bfr+4096,bootdesc,32);bfr[4128]=0x88;bfr[4129]=bt&7;
*(WORD *)(bfr+4134)=neb;bfr[4136]=shrt+20;xwrite(bfr+4096,2048);
printf("Writing Boot Image\n");
while(l>0) {
boot=l;
if (boot>32768) boot=32768;
if (_lread(bf,bfr,boot)-boot) {printf("Boot Image Read Error\n");return(20);}
while(boot&2047) bfr[boot++]=0;
if ((bt>8) && (bt<12)) {
bfr[21]=0xf0;bfr[26]=2;bfr[btt]=0;*(int *)(bfr+28)=0;
switch(bt) {
case 9:  bfr[24]=15;break;
case 10: bfr[24]=18;break;
case 11: bfr[24]=36;break;
};
}
xwrite(bfr,boot);l-=boot;bt&=7;
}
}
printf("Writing Indexes\n");
xwrite(rcdir,i<<11);xwrite(cdir,i<<11);
if (shrt) {xwrite(rucdir,j<<11);xwrite(ucdir,j<<11);}
i=(int)(&ent);j=(int)(&ent.dirs);
printf("Writing Directories\n");dirs=0;
writedir((struct entr *)(((int)&i)+i-j));
printf("Writing Files      \n");files=0;bt=0;writefile(&ent);
if (pad) {
printf("Writing Pad        \n");zero(bfr,0x7800);
for (i=0;i<10;i++) xwrite(bfr,0x7800);
}
xwrite(0,-1);
while(n1>=0) Sleep(1000);
printf("Done\n");return(0);

#endif

}

int pr(char *bstr,char *s,struct _finddata_t *exam,int ds,int dire,int pass)
{
int i,j,l;
char *src,*dest,*x,*dstr,sn[512];
struct entr *e,*ee,*eee,*e1;
dstr=(char *)ds;
if ((dstr[0]|s[0])==0) {
if ((exam->attrib&16)==0) {printf("Root Cannot Be File\n");return(-1);}
ent.type=2;ent.date=tb.time;ent.attr=exam->attrib&0x27;return(0);
}
dest=str(catpath(dstr,s));src=str(catpath(bstr,s));
if (q) {
ask: if (exam->attrib&16) printf("Include Dir  %s ? (Yes/No/SkipDir/Quit/All) (N) ",src);
else printf("Include File %s ? (Yes/No/Quit/All) (N) ",src);
_read(0,sn,4);
if (sn[0]<14) return(0);
switch(sn[0]&0xdf) {
case 'N': return(0);
case 'Q': return(-1);
case 'S': return(1);
case 'A': q=0;
case 'Y': break;
default: goto ask;
};
}
e= &ent;i=0;
next: x=parse(dest,i++,&l);eee=e;ee=e->dirs;
while(ee) {
j=strcmp(x,ee->name);
if (j<0) goto new1;
if (j==0) {
if (ee->type==1) {
exists: printf("File %s Already Exists\n",dest);return(0);
}
e1=ee;
if (l==0) goto done;
if ((exam->attrib&16)==0) {printf("Dir %s Already Exists\n",dest);return(0);}
if (e1->type==2) goto done;
e1->type=2;goto fill;
}
eee=ee;ee=ee->next;
}
new1: e1=(struct entr *)malloc(sizeof(struct entr));
if (e1==0) nomem();
zero((BYTE *)e1,sizeof(struct entr));e1->next=ee;e1->parent=e;
if (e-eee) eee->next=e1;else eee->dirs=e1;
if (l==0) {e1->date=tb.time;goto done1;}
e1->type=((exam->attrib&16) ? 2 : 1);
fill: e1->attr=exam->attrib&0x27;e1->date=exam->time_write;
if (sc) if (s[0]) if (GetShortPathName(src,sn,512)) {
j=0;
while(sn[i++]) if (sn[i-1]=='\\') j=i;
e1->com=str(sn+j);
}
if ((exam->attrib&16)==0) {
e1->dirs=(struct entr *)str(src);e1->size=exam->size;
filesecs+=(exam->size+2047)>>11;
}
done1: e1->name=x;
if (e1->type==1) printf(" %d Dirs %d Files\r",dirs,++files);
else printf(" %d Dirs %d Files\r",++dirs,files);
goto done2;
done: free(x);
done2: e=e1;
if (l==0) goto next;
free(src);free(dest);return(0);
}

void sname(struct entr *e)
{
int i,j;
char *n;
struct entr *ee;
ee=e->dirs;j=2;
while(ee) {
if (ee->type-1) sname(ee);
if (shrt==0) {ee->sname=ee->name;goto done;}
n=makeshort(ee->name,0);
if (n==0) {ee->sname=ee->name;goto done;}
if (stricmp(n,ee->name)==0) goto done1;
i=1;
lp: n=makeshort(ee->name,i++);
if (uniq(e->dirs,n,ee)==0) {
if (i==2) i=j;
else j=i;
goto lp;
}
if (i==2) j=2;
done1: ee->sname=str(n);
done: if (ee->type-1) {
cdirsize+=(strlen(ee->sname)+9)& -2;ucdirsize+=(strlen(ee->name)<<1)+8;
printf(" %d Dirs %d Files\r",++dirs,files);
}
else printf(" %d Dirs %d Files\r",dirs,++files);
ee=ee->next;
}
}

void scandir(struct entr *e,int l)
{
int i,j,p,up;
struct entr *ee;
struct list *d,*dd;
BYTE *s,*us;
d= &dir;
for (i=0;i<l;i++) {
if (d->next==0) {
dd=(struct list *)malloc(8);
if (dd==0) nomem();
dd->next=0;dd->ptr=0;d->next=dd;
}
d=d->next;
}
d=(struct list *)(&(d->ptr));
while(d->next) d=d->next;
dd=(struct list *)malloc(8);
if (dd==0) nomem();
dd->next=0;dd->ptr=e;d->next=dd;e->size=2048;e->usize=2048;
s=alloc((struct list *)(&(e->dirsecs)));
us=alloc((struct list *)(&(e->udirsecs)));
i=build(s,e,0,0);build(us,e,0,1);
j=build(s+i,e->parent,(char *)1,0);build(us+i,e->parent,(char *)1,1);
p=up=i+j;memcpy(us,s,p);ee=e->dirs;
while(ee) {
i=bsize(ee,ee->sname,0);
if (shrt) j=bsize(ee,ee->name,1);
if ((p+i)>2046) {s=alloc((struct list *)(&(e->dirsecs)));p=0;e->size+=2048;}
build(s+p,ee,ee->sname,0);ee->pent=s+p;p+=i;
if (shrt) {
if ((up+j)>2046) {us=alloc((struct list *)(&(e->udirsecs)));up=0;e->usize+=2048;}
build(us+up,ee,ee->name,1);ee->upent=us+up;up+=j;
}
ee=ee->next;
}
i=e->size>>11;j=e->usize>>11;s=((BYTE *)e->dirsecs)+4;
*(int *)(s+14)=rev(e->size);*(int *)(s+10)=e->size;
if (l==0) {
i=s[0];s+=i&255;*(int *)(s+14)=rev(e->size);*(int *)(s+10)=e->size;
}
s=((BYTE *)e->udirsecs)+4;
*(int *)(s+14)=rev(e->usize);*(int *)(s+10)=e->usize;
if (l==0) {
i=s[0];s+=i&255;*(int *)(s+14)=rev(e->usize);*(int *)(s+10)=e->usize;
}
if (e->pent) {s=e->pent;*(int *)(s+14)=rev(e->size);*(int *)(s+10)=e->size;}
if (e->upent) {s=e->upent;*(int *)(s+14)=rev(e->usize);*(int *)(s+10)=e->usize;}
ee=e->dirs;
while(ee) {
if (ee->type-1) scandir(ee,l+1);
ee=ee->next;
}
printf(" %d Dirs\r",++dirs);
}

void fixroot(struct entr *e)
{
int i;
BYTE *s;
e->sector=secp;secp+=e->size>>11;
if (shrt) {e->usector=secp;secp+=e->usize>>11;}
s=((BYTE *)e->dirsecs)+4;
*(int *)(s+6)=rev(e->sector);*(int *)(s+2)=e->sector;
i=s[0];i&=255;memcpy(hdr1+0x27,s,i);s+=i;
*(int *)(s+6)=rev(e->sector);*(int *)(s+2)=e->sector;
s=((BYTE *)e->udirsecs)+4;
*(int *)(s+6)=rev(e->usector);*(int *)(s+2)=e->usector;
i=s[0];i&=255;memcpy(hdr2+0x27,s,i);s+=i;
*(int *)(s+6)=rev(e->usector);*(int *)(s+2)=e->usector;
}

void fixdir(struct entr *e)
{
int i;
struct entr *ee;
BYTE *s;
ee=e->dirs;
while(ee) {
if (ee->type-1) {
ee->sector=secp;secp+=ee->size>>11;
if (shrt) {ee->usector=secp;secp+=ee->usize>>11;}
s=((BYTE *)ee->dirsecs)+4;
*(int *)(s+6)=rev(ee->sector);*(int *)(s+2)=ee->sector;
i=s[0];i&=255;s+=i;
*(int *)(s+6)=rev(ee->parent->sector);*(int *)(s+2)=ee->parent->sector;
s=((BYTE *)ee->udirsecs)+4;
*(int *)(s+6)=rev(ee->usector);*(int *)(s+2)=ee->usector;
i=s[0];i&=255;s+=i;
*(int *)(s+6)=rev(ee->parent->usector);*(int *)(s+2)=ee->parent->usector;
if (ee->pent) {s=ee->pent;*(int *)(s+6)=rev(ee->sector);*(int *)(s+2)=ee->sector;}
if (ee->upent) {s=ee->upent;*(int *)(s+6)=rev(ee->usector);*(int *)(s+2)=ee->usector;}

}
ee=ee->next;
}
ee=e->dirs;
while(ee) {
if (ee->type-1) fixdir(ee);
ee=ee->next;
}
printf(" %d Dirs\r",++dirs);
}

void bcdir()
{
struct list *d,*dd;
struct entr *e;
int i,j,k,kk,l,ll,p,up;
d= &dir;i=1;p=up=0;
while(d) {
dd=(struct list *)d->ptr;
while(dd) {
e=dd->ptr;e->dirnum=i;
if (i==1) j=1;
else j=e->parent->dirnum;
k=l=kk=ll=0;
if (e->name) k=l=strlen(e->name);
if (e->sname) kk=ll=strlen(e->sname);
if (i==1) ll=l=1;
cdir[p]=rcdir[p]=ll;ucdir[up]=rucdir[up]=((i==1) ? 1 : k<<1);
*(int *)(cdir+p+2)=rev(e->sector);*(int *)(rcdir+p+2)=e->sector;
*(int *)(ucdir+up+2)=rev(e->usector);*(int *)(rucdir+up+2)=e->usector;
*(short *)(cdir+p+6)= *(short *)(ucdir+up+6)=rev(j<<16);
*(short *)(rcdir+p+6)= *(short *)(rucdir+up+6)=j;
memcpy(rcdir+p+8,e->sname,kk);memcpy(cdir+p+8,e->sname,kk);
for (j=0;j<k;j++) rucdir[up+9+j+j]=ucdir[up+9+j+j]=e->name[j];
up+=8+l+l;ll=(ll+9)& -2;p+=ll;i++;dd=dd->next;printf(" %d Dirs\r",++dirs);
}
d=d->next;
}
if (p-cdirsize) {printf("CDIR Bad\n");kill();}
if (up-ucdirsize) {printf("UCDIR Bad\n");kill();}
}

void scanfile(struct entr *e)
{
struct entr *ee;
BYTE *s,*us;
ee=e->dirs;
while(ee) {
if (ee->type==1) {
s=ee->pent;us=ee->upent;
if (shrt==0) us=s;
*(int *)(s+6)= *(int *)(us+6)=rev(secp);*(int *)(s+2)= *(int *)(us+2)=secp;
ee->sector=secp;secp+=(ee->size+2047)>>11;printf(" %d Files\r",++files);
}
ee=ee->next;
}
ee=e->dirs;
while(ee) {
if (ee->type-1) scanfile(ee);
ee=ee->next;
}
}

char *str(char *s)
{
char *i;
i=(char *)malloc(strlen(s)+1);
if (i==0) nomem();
strcpy(i,s);return(i);
}

char *parse(char *s,int n,int *l)
{
int i;
char *ss;
i=0;*l=0;
while(i-n) {
switch(*(s++)) {
case 0: printf("Name Overrun\n");kill();
case ':':
inv: printf("Invalid Name\n");kill();
case '\\': i++;
          if (s[0]=='\\') goto inv;
};
}
if (s[0]==0) {printf("Empty Name\n");kill();}
ss=s;
while(*ss) {
if (ss[0]=='\\') {ss[0]=0;s=str(s);ss[0]='\\';return(s);}
ss++;
}
*l=1;return(str(s));
}

int bsize(struct entr *e,char *n,int m)
{
int i,j,k,p;
k=1;
lp: i=(int)n;
if (i<2) p=34;
else {
j=strlen(n);
if (m) p=34+(j<<1);
else p=(j+34)& -2;
}
i=0;
if (e->com) i=strlen(e->com)+6;
// if (e->attr) i=(i ? i+4 : 9);
i=i+p+1;
if (i>255) {
if (k) {
printf("Truncating Long Filename:\n[%s]\n",n);k=0;
}
n[j-1]=0;goto lp;
}
if (k==0) printf("To:\n[%s]\n",n);
return(i & -2);
}

int build(BYTE *s,struct entr *e,char *n,int m)
{
int i,j,k,p;
i=(int)n;
if ((i==1) && m && (e->type-1)) {
*(int *)(s+14)=rev(e->usize);*(int *)(s+10)=e->usize;
}
else {*(int *)(s+14)=rev(e->size);*(int *)(s+10)=e->size;}
makedate(e->date,s+18);s[25]=2;
if (e->type) s[25]=((e->attr&2) ? -1 : -2)+(e->type<<1);
s[28]=s[31]=1;
if ((i& -2)==0) {s[32]=1;s[33]=i;p=34;}
else {
j=strlen(n);
if (m) {
p=34+(j<<1);s[32]=j<<1;
for (i=0;i<j;i++) s[34+i+i]=n[i];
}
else {s[32]=j;memcpy(s+33,n,j);p=(j+34)& -2;}
}
i=j=0;
if (e->com) {i=strlen(e->com)+6;j=2;}
// if (e->attr) {i=(i ? i+4 : 9);j++;}
s[0]=m=(i+p+1)& -2;
if (j) {
s[p]='A';s[p+1]='S';s[p+2]=i;s[p+3]=1;s[p+4]=j;
// if (j&1) {s[p+5]=s[p+6]=0;k=e->attr&15;s[p+7]=255-(k<<4)-k;s[p+8]=e->attr;}
if (j&2) {
k=((j&1) ? p+9 : p+5);s[k]=strlen(e->com)+1;memcpy(s+k+1,e->com,s[k]-1);
}
}
return(m);
}

void makedate(int date,BYTE *dstr)
{
struct tm *d;
d=localtime((long *)(&date));
dstr[0]=d->tm_year;dstr[1]=d->tm_mon+1;dstr[2]=d->tm_mday;
dstr[3]=d->tm_hour;dstr[4]=d->tm_min;dstr[5]=d->tm_sec;
}

BYTE *alloc(struct list *l)
{
struct list *ll;
while(l->next) l=l->next;
ll=(struct list *)malloc(2052);
if (ll==0) nomem();
zero((BYTE *)ll,2052);l->next=ll;return((BYTE *)(&(ll->ptr)));
}

char *makeshort(char *s,int n)
{
int i,j,l,p,pp,ppp;
char x;
if (n>9999999) {printf("Short Name Overflow\n");kill();}
l=strlen(s);p=l;
for (i=0;i<l;i++) if (s[i]=='.') p=i;
for (i=j=0;i<p;i++) if (j<8) {
x=s[i];
if ((x>='a') && (x<='z')) x-=32;
if (x-'.') if (x-32) snb[j++]=x;
}
ppp=pp=j;
if (p-l) for (;i<l;i++) if (j<(pp+4)) {
x=s[i];
if ((x>='a') && (x<='z')) x-=32;
if (x-32) snb[j++]=x;
}
snb[j]=0;
if (n==0) {
if (strcmp(snb,s)==0) return(0);
if (stricmp(snb,s)==0) return(snb);
n=1;
}
while(pp<8) {
for (i=12;i>pp;i--) snb[i]=snb[i-1];
snb[pp++]=32;
}
snb[13]=0;i=7;
while(n) {snb[i--]=(n%10)+48;n/=10;}
snb[i]='~';
while(snb[ppp]==32) for (i=ppp;i<13;i++) snb[i]=snb[i+1];
return(snb);
}

void nomem()
{
printf("Not Enough Memory\n");kill();
}

int uniq(struct entr *f,char *n,struct entr *x)
{
lp: if (f==0) return(1);
if (f-x) {
if (stricmp(f->name,n)==0) return(0);
if (f->sname) if (stricmp(f->sname,n)==0) return(0);
}
f=f->next;goto lp;
}

int rev(int s)
{
int i;
i=s&255;i<<=8;s>>=8;i+=s&255;i<<=8;s>>=8;i+=s&255;i<<=8;s>>=8;
return(i+(s&255));
}

void zero(BYTE *s,int l)
{
while(l>3) {*(int *)s=0;s+=4;l-=4;}
while(l--) *(s++)=0;
}

void kill()
{
while(n1>=0) Sleep(1000);
exit(20);
}

#ifndef DEMO

void writedir(struct entr *e)
{
int i;
struct entr *ee;
struct list *d;
ee=e->dirs;
while(ee) {
if (ee->type-1) {
i=ee->size;d=ee->dirsecs;
while(i) {
if (d==0) {printf("Dir Too Short\n");kill();}
xwrite((BYTE *)(((int)d)+4),2048);i-=2048;d=d->next;
}
if (d) {printf("Dir Too Long\n");kill();}
if (shrt) {
i=ee->usize;d=ee->udirsecs;
while(i) {
if (d==0) {printf("UDir Too Short\n");kill();}
xwrite((BYTE *)(((int)d)+4),2048);i-=2048;d=d->next;
}
if (d) {printf("UDir Too Long\n");kill();}
}
}
ee=ee->next;
}
ee=e->dirs;
while(ee) {
if (ee->type-1) writedir(ee);
ee=ee->next;
}
++dirs;
if (pos<=0) printf(" %d Dirs\r",dirs);
}

void writefile(struct entr *e)
{
int r,j;
unsigned int i;
struct entr *ee;
char x[4];
ee=e->dirs;x[0]=0;
while(ee) {
if (ee->type==1) {
i=ee->size;
if (i) {
r=_lopen((char *)ee->dirs,0);
if (r<0) {printf("Cannot Open %s\n",ee->dirs);kill();}
while(i) {
j=i;
if (i>32768) j=32768;
if (_lread(r,bfr,j)<j) if ((x[0]&0xdf)-'Y') {
printf("Read Error On %s  Ignore (Y/N) ? ",ee->dirs);read(0,x,4);
if ((x[0]&0xdf)-'Y') kill();
}
i-=j;
while(j&2047) bfr[j++]=0;
xwrite(bfr,j);
}
_lclose(r);
}
++files;
if (pos<=0) printf(" %d Files\r",files);
}
ee=ee->next;
}
ee=e->dirs;
while(ee) {
if (ee->type-1) writefile(ee);
ee=ee->next;
}
}

void cdwr()
{
int e,r1,r2,f,i,j,k,l;
i=buffs-4;j=len/max;
if (j<i) i=j;
while(n2<i) Sleep(1000);
if (ty&0x80) if (wm&2) {
pos= -150;printf("Burning PreGap   \n");
for (k=0;k<(max<<11);k++) b[k]=0;
for (i=0;i<150;i+=max) {
j=max;
if ((i+j)>150) j=150-i;
lw1: if ((k=aspicmdx(u,0xaa,pos,j,2,b,j<<11))<0) {
if (k== -2) {Sleep(100);goto lw1;}
aspierr("\nError Burning PreGap",sen);pos=0;goto nogap;
}
pos+=j;
}
}
nogap: printf("Burning %05x     \n",len);
for (i=0;i<len;i+=max) {
j=max;e=1;
if ((i+j)>len) j=len-i;
while (n1==n2) Sleep(2);
b=buff[(n1++)%buffs];
if (n1<0) {printf("\nError Reading File\n");goto abrt0;}
if (bt==0) printf("%d Files  ",files);
if (wm&16) {
k=n2-n1;
if (k<0) k+=buffs;
printf("%4d ",k);
}
printf("%06x%s\r",pos,bt ? "    " : "");l=j<<11;
lw2: k=aspicmdx(u,0xaa,pos,j,2,b,l);
if (k== -2) {Sleep(100);goto lw2;}
if (k<l) {aspierr("\nError Burning Data",sen);goto abrt0;}
pos+=j;
}
abrt0: printf("\rFlushing Cache                \n");
lw3: if ((k=aspicmdx(u,0x35,0,0,0,b,0))<0) {
if (k== -2) {Sleep(10);goto lw3;}
aspierr("Error Flushing Cache",sen);goto abrt;
}
if ((wm&0x13)==1) {
printf("\rClosing Disk                  \n");
if ((ty&0xf7)==0x20) {
lw4: if ((k=aspicmdx(u,0x5b,0x1000001,0,0,b,0))<0) {
if (k== -2) {Sleep(10);goto lw4;}
aspierr("Error Closing Track",sen);goto abrt;
}
lw5: if ((k=aspicmdx(u,0x5b,(ty==0x28) ? 0x5000000 : 0x6000000,0,0,b,0))<0) {
if (k== -2) {Sleep(10);goto lw5;}
aspierr("Error Closing Disk",sen);goto abrt;
}
}
else {
lw6: if ((k=aspicmdx(u,0x5b,0x2000000,0,0,b,0))<0) {
if (k== -2) {Sleep(10);goto lw6;}
aspierr("Error Closing Disk",sen);goto abrt;
}
}
}                        
abrt: closeaspi();printf("\007");Sleep(1000);printf("\007");n1= -10000;return;
}

void xwrite(BYTE *b,int l)
{
int i;
lp: while (n2==(n1+buffs-2)) Sleep(2);
if (n1<0) return;
if (l<0) {
if (n0) n2++;
return;
}
i=(max<<11)-n0;
if (l<i) i=l;
memcpy(buff[n2%buffs]+n0,b,i);b+=i;l-=i;n0+=i;
if (n0<(max<<11)) return;
n2++;n0=0;
if (l) goto lp;
return;
}

#endif
