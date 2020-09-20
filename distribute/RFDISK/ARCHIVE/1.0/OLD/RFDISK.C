/*( int13ex int13chs int13raw )*/

unsigned char mbr[]={0};
unsigned char mbr2[]={0};
unsigned char dos[]={0};
unsigned char win[]={0};

struct part {
struct part *next,*lpart;
unsigned long start,len,base;
unsigned char type,btype,clear,valid,heads,sectors,active[63],partsec[63];
};

struct drive {
struct drive *next;
unsigned char drive,heads,sectors,partsecs,install,hd8,sec8;
unsigned int cyl8;
unsigned long length,cyls,cylex,hdex,secex;
unsigned char id[63],id0[63],active;
struct part *list;
};

struct table {
unsigned char act,shead,ssec,scyl,type,ehead,esec,ecyl;
unsigned long off,len;
};

struct sector {  
unsigned char x0[0x13];
unsigned short slen;
unsigned char x1[3];
int secs,heads;
unsigned long off,len;
unsigned char x2[0x12];
long type;
unsigned char type1;
unsigned char x3[0x17];
long type2;
unsigned char x4[0x15a];
int def,id;
unsigned char x5[10];
struct table parts[4];
unsigned int tag;
};

struct psec {
struct psec *next;
unsigned long blk;
unsigned char s1[512],s2[512];
};

struct drive *disks=0;

void build(),buildl(),addl(),addx(),show(),freed(),valid();
long int13_8();
struct part *add(),*find();
char *fmt();

int mode=0;
long hide=0x3fffffff;
int f0=0,f1=0,ov=1,sr=1;

main(c,v)
int c;
char **v;
{
int i,j,k,m,x;
unsigned long e,l,ll,d[8];
struct drive *disk,*dd,*cdisk;
struct sector sec;
struct part *p,*ep;
unsigned char cmd[128],*s,*ss;
struct psec *ext,*ext1;
m=256;
arg: if (c>1) if (v[1][0]=='-') {
if ((v[1][1]&0xdf)=='R') {mode|=1;c--;v++;goto arg;}
if ((v[1][1]&0xdf)=='C') {mode|=2;c--;v++;goto arg;}
if ((v[1][1]&0xdf)=='O') {ov=0;c--;v++;goto arg;}
if ((v[1][1]&0xdf)=='N') {sr=0;c--;v++;goto arg;}
{sscanf(v[1]+1,"%d",&m);m+=128;c--;v++;}
}
printf("RFDISK Read Only Demo\n\nCopyright (c) 2004 by Rudolph R. Loew\n\nAll Rights Reserved\n\n");
start: cdisk=0;
for (i=0x80;i<m;i++) {
int13(0x42,i,0L,0L,&sec);
if (int13(0x42,i,0L,0L,&sec)==0) {
disk=(struct drive *)calloc(sizeof(struct drive),1);
if (disk==0) goto nomem;
e=int13_8(i);disk->cyl8=(e>>16)+1;disk->hd8=(e>>8)+1;disk->sec8=e;
disk->drive=i;disk->heads=disk->hd8;disk->sectors=disk->sec8;
if (disk->sec8==0) {disk->heads=255;disk->sectors=63;}
d[4]=0;int13(0x48,i,0L,0L,d);disk->length=d[4];
disk->cylex=d[1];disk->hdex=d[2];disk->secex=d[3];
if (disk->length==0) disk->length=0xffffffff;
disk->partsecs=1;disk->id[0]='-';disk->active=sec.def;
if (sec.tag==0xaa55) {
for (j=0;j<4;j++) if (sec.parts[j].type) goto fnd;
goto notfnd;
fnd: disk->heads=sec.parts[j].ehead+1;disk->sectors=sec.parts[j].esec&63;
notfnd: disk->cyls=disk->length/disk->heads/disk->sectors;
if (sec.id==0x4c52) {
for (l=1;l<disk->sectors;l++) {
if (int13(0x42,i,0L,l,&sec)==0) {
if (sec.tag&255) {
k=sec.tag>>8;
if (k) {j=l;disk->id[l]=sec.tag;build(disk,j,&sec);}
else {
j=sec.tag&0xff;
if ((j>='A') && (j<='Z')) j+=32;
else j='*';
disk->id0[l]=j;
}
if (k>1) l+=k-1;
}
else {disk->partsecs=l;l=64;disk->id[0]=0;}
}
else printf("Error on Disk %02x Sector %02x\n",i,l);
}
}
else build(disk,0,&sec);
}
else disk->install=1;
if (disks) {
dd=disks;
while (dd->next) dd=dd->next;
dd->next=disk;
}
else disks=disk;
}
}
if (disks==0) {printf("No Disks Detected\n");exit(20);}
if (disks->next==0) cdisk=disks;
lp: if (cdisk) show(cdisk);
else {
dd=disks;
while (dd) {show(dd);dd=dd->next;}
}
lp1: if (f0==0) printf("\n> ");
i=0;
while (read(f0,cmd+i,1)>0) { 
i++;
if (i==126) goto lp0;
if (cmd[i-1]==10) goto lp0;
}
if (f0==0) return(0);
close(f0);f0=0;goto lp1;
lp0: cmd[i]=0;
if (i==0) exit(0);
if (cmd[0]==10) goto lp;
if (cmd[0]=='?') {
if (cdisk) {
printf("Add Type Start End [+Head1]\n");
printf("Change Type Start NewType [NewEnd]\n");
printf("Remove Type Start\n");
printf("Kill All\n");
printf("Link Type Start Reference\n");
printf("UnLink Type Start Reference\n");
printf("NewTable Reference\n");
printf("SetActiveTable Reference\n");
printf("MBR\n");
printf("ToggleActive Type Start Reference\n");
printf("EraseBootToggle Type Start\n");
printf("Validate Type Start\n");
printf("Geometry Heads Sectors [Cylinders]\n");
printf("ZeroFillExt Add|Remove\n");
printf("Find [Start]\n");
printf("Build SaveFile\n");
printf("Write\n");
}
else {
printf("Install/Uninstall_Multiboot Drive#\n");
}
printf("Drive [#]\n");
printf("Hide [#] (0=Ext)\n");
printf("OldValues\n");
printf("<InputFile\n");
printf("Quit\n");
goto lp1;
}
cmd[0]&=0xdf;
if (cdisk==0) if (cmd[0]=='I') {
i= -1;sscanf(cmd,"%s %d",cmd+64,&i);
if (i<0) {printf("Drive Not Specified\n");goto lp1;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) goto iok;
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
iok: if (dd->partsecs==1) printf("Cannot Install SWBT in DIAG Mode\n");
else printf("Cannot Remove SWBT in DIAG Mode\n");
goto lp1;
}
if (cmd[0]=='<') {
if (f0) close(f0);
f0=strlen(cmd);
if (cmd[f0-1]==10) cmd[f0-1]=0;
f0=open(cmd+1,0);
if (f0<0) {printf("Cannot Open Input File\n");f0=0;}
goto lp1;
}
if (cmd[0]=='Q') return(0);
if (cmd[0]=='O') {freed();goto start;}
if (cmd[0]=='D') {
i= -1;sscanf(cmd,"%s %d",cmd+64,&i);
if (i<0) {cdisk=0;goto lp;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) {cdisk=dd;goto lp;}
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
}
if (cmd[0]=='H') {
hide= -1;sscanf(cmd,"%s %ld",cmd+64,&hide);
if (hide<0) hide=0x3fffffff;
goto lp;
}
if (cdisk==0) {printf("Invalid Command\n");goto lp1;}
switch(cmd[0]) {
case 'A': ll=0;cmd[60]=0;sscanf(cmd,"%s %x %ld %ld %s",cmd+64,&i,&l,&ll,cmd+60);
          if (ll==0) goto bad;
          if ((i==5) || (i==15)) {
          if (l==0) {printf("Invalid Start\n");goto lp1;}
          if (cmd[60]=='+') {printf("Cannot Offset Extended Partition\n");goto lp1;}
          }
          l*=cdisk->heads*cdisk->sectors;
          ll*=cdisk->heads*cdisk->sectors;
          addx(cdisk,i,l,ll,(cmd[60]=='+') ? 1 : 0);goto lp;
case 'B': f1=strlen(cmd);
          if (cmd[f1-1]==10) cmd[f1-1]=0;
          f1=0;
          while (cmd[f1] && (cmd[f1]-32)) f1++;
          while (cmd[f1] && (cmd[f1]==32)) f1++;
          if (cmd[f1]==0) {f1=0;goto bad;}
          f1=creat(cmd+f1,1);
          if (f1<0) {f1=0;printf("Cannot Create SaveFile\n");goto lp1;}
          show(cdisk);close(f1);f1=0;goto lp;
case 'C': j=256;ll=0;sscanf(cmd,"%s %x %ld %x %ld",cmd+64,&i,&l,&j,&ll);
          if (j==256) goto bad;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          ll=ll*p->heads*p->sectors;
          if (ll==0) ll=p->start+p->len;
          if (ll<=p->start) {printf("Invalid End\n");goto lp1;}
          p->len=ll-p->start;p->type=j;valid(cdisk,p);
          goto lp;
case 'R': l=0xffffffff;sscanf(cmd,"%s %x %ld",cmd+64,&i,&l);
          if (l==0xffffffff) goto bad;      
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          free1(p);goto lp;
case 'K': while(cdisk->list) free1(cdisk->list);
          goto lp;
case 'L': l=0xffffffff;cmd[60]='-';sscanf(cmd,"%s %x %ld %s",cmd+64,&i,&l,cmd+60);
          if (l==0xffffffff) goto bad;      
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if (p->base) {printf("Cannot Link Logical Partition\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto lfnd;
          printf("Unknown Partition ID\n");goto lp1;
lfnd:     for (i=0;i<63;i++) {
          if (p->partsec[i]==0) {p->partsec[i]=j;goto lp;}
          if (p->partsec[i]==j) {printf("Already Linked\n");goto lp1;}
          }
          printf("List Full\n");goto lp1;
case 'U': l=0xffffffff;cmd[60]='-';sscanf(cmd,"%s %x %ld %s",cmd+64,&i,&l,cmd+60);
          if (l==0xffffffff) goto bad;      
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if (p->base) {printf("Cannot UnLink Logical Partition\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto ufnd;
          printf("Unknown Partition ID\n");goto lp1;
ufnd:     for (i=0;i<63;i++) {
          if (p->partsec[i]==0) {printf("Link Not Found\n");goto lp1;}
          if (p->partsec[i]==j) {
          for (;i<62;i++) p->partsec[i]=p->partsec[i+1];
          p->partsec[62]=0;;goto lp;
          }
          }
          printf("Link Not Found\n");goto lp1;
case 'N': cmd[60]='0';sscanf(cmd,"%s %s",cmd+64,cmd+60);
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          if (cdisk->partsecs==1) {printf("No SWBT\n");goto lp1;}
          if ((cmd[60]=='D') || (cmd[60]=='W')) cmd[60]+=32;
          for (j=0;j<63;j++) if ((cdisk->id[j]==cmd[60]) || (cdisk->id0[j]==cmd[60])) {
          printf("Partition ID Exists\n");goto lp1;
          }
          if (cdisk->partsecs==63) {printf("List Full\n");goto lp1;}
          if ((cmd[60]=='d') || (cmd[60]=='w')) {
          cdisk->id0[cdisk->partsecs++]=cmd[60];
          }
          else cdisk->id[cdisk->partsecs++]=cmd[60];
          goto lp;
case 'S': cmd[60]='0';sscanf(cmd,"%s %s",cmd+64,cmd+60);
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          if (cdisk->partsecs==1) {printf("No SWBT\n");goto lp1;}
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto sok;
          if (cmd[60]-'?') printf("\nID Not Listed Assuming Boot Overlay\n");
sok:      cdisk->active=cmd[60];goto lp;
case 'M': cdisk->install=1;goto lp;      
case 'T': l=0xffffffff;cmd[60]='-';sscanf(cmd,"%s %x %ld %s",cmd+64,&i,&l,cmd+60);
          if (l==0xffffffff) goto bad;      
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if (p->base) {printf("Cannot Activate Logical Partition\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto tfnd;
          printf("Unknown Partition ID\n");goto lp1;
tfnd:     for (i=0;i<63;i++) {
          if (p->active[i]==0) {p->active[i]=j;goto lp;}
          if (p->active[i]==j) {
          for (;i<62;i++) p->active[i]=p->active[i+1];
          p->active[62]=0;goto lp;
          }
          }
          printf("List Full\n");goto lp1;
case 'E': l=0xffffffff;sscanf(cmd,"%s %x %ld",cmd+64,&i,&l);
          if (l==0xffffffff) goto bad;      
          if ((i==5) || (i==15)) {printf("Cannot Erase Extended Partition\n");goto lp1;}
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if (p->valid==1) p->valid=0;
          else p->valid=1;
          goto lp;
case 'V': l=0xffffffff;sscanf(cmd,"%s %x %ld",cmd+64,&i,&l);
          if (l==0xffffffff) goto bad;      
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          valid(cdisk,p);
          goto lp;
case 'G': i=j=0;e=0;sscanf(cmd,"%s %d %d %ld",cmd+64,&i,&j,&e);
          if ((i==0) || (j==0)) goto bad;      
          cdisk->heads=i;cdisk->sectors=j;
          if (e) {cdisk->cyls=e;cdisk->length=e*cdisk->heads*cdisk->sectors;}
          else cdisk->cyls=cdisk->length/cdisk->heads/cdisk->sectors;
          goto lp;
case 'Z': cmd[60]=0;sscanf(cmd,"%s %s",cmd+64,cmd+60);
          p=cdisk->list;
          while(p) {
          if ((p->type==5) || (p->type==15)) {
          switch(cmd[60]&0xdf) {
          case 'A': l=p->start;e=l+p->len;ep=p->lpart;
                    while(ep) {
                    ll=ep->start-cdisk->sectors;
                    if (ll>l) addx(cdisk,0,l,ll,0);
                    l=ep->start+ep->len;
                    ep=ep->next;
                    }
                    if (e>l) addx(cdisk,0,l,e,0);
                    break;
          case 'R':
zfnd1:              if (p->lpart==0) break;
                    if (p->lpart->type==0) {free1(p->lpart);goto zfnd1;}
                    ep=p->lpart;
zfnd2:              if (ep->next==0) break;
                    if (ep->next->type==0) {free1(ep->next);goto zfnd2;}
                    ep=ep->next;goto zfnd2;
          default:  printf("Invalid Option\n");goto lp1;
          };
          }
          p=p->next;
          }
          goto lp;
case 'F': l=0;sscanf(cmd,"%s %ld",cmd+64,&l);
          if (l==0) {
          for (l=1;l<64;l++) if (l-cdisk->sectors) if (int13(0x42,cdisk->drive,0L,l,&sec)==0) if (sec.tag==0xaa55) {
          if (sec.len==0) sec.len=sec.slen;
          switch(sec.type) {
          case 0: printf("Unexpected EXT Record at Sector %ld\n",l);break;
          case 0x33544146: printf("Unexpected FAT32 Record at Sector %ld: Off=%ld Len=%ld Heads=%d Secs=%d\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
          case 0x31544146: if (sec.type1=='6') {
                           printf("Unexpected FAT16 Record at Sector %ld: Off=%ld Len=%ld Heads=%d Secs=%d\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
                           }
                           if (sec.type1=='2') {
                           printf("Unexpected FAT12 Record at Sector %ld: Off=%ld Len=%ld Heads=%d Secs=%d\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
                           }
          default: printf("Unexpected Record at Sector %ld\n",l);
          };
          }
          l=0;
          }
          l*=cdisk->heads*cdisk->sectors;
          for (;l<cdisk->length;l+=cdisk->heads*cdisk->sectors) {
f0:       if (l>=(hide*cdisk->heads*cdisk->sectors)) {printf("*\n");goto lp;}
          if (l) {
          if (int13(0x42,cdisk->drive,0L,l,&sec)) goto lp;
          if (sec.tag==0xaa55) {
          if (sec.type==0) sec.type=sec.type2;
          if (sec.len==0) sec.len=sec.slen;
          fmt(&sec,cdisk,l);
          fmt(&(sec.x3),cdisk,l+sec.len);
          fmt(&(sec.parts),cdisk,sec.off);
          switch(sec.type) {
          case 0: printf("EXT   Record at %s\n",&sec);break;
          case 0x33544146: printf("FAT32 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
          case 0x31544146: if (sec.type1=='6') {
                           printf("FAT16 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
                           }
                           if (sec.type1=='2') {
                           printf("FAT12 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
                           }
          default: printf("Unknown Record at %s\n",&sec);
          };
          }
          }
          if (int13(0x42,cdisk->drive,0L,l+cdisk->sectors,&sec)) goto lp;
          if (sec.tag==0xaa55) {
          if (sec.type==0) sec.type=sec.type2;
          if (sec.len==0) sec.len=sec.slen;
          fmt(&sec,cdisk,l+cdisk->sectors);
          fmt(&(sec.x3),cdisk,l+sec.len+cdisk->sectors);
          fmt(&(sec.parts),cdisk,sec.off);
          switch(sec.type) {
          case 0: printf("Unexpected EXT Record at %s\n",&sec);break;
          case 0x33544146: printf("FAT32 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
          case 0x31544146: if (sec.type1=='6') {
                           printf("FAT16 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
                           }
                           if (sec.type1=='2') {
                           printf("FAT12 Record at %s: End = %s   Off = %s Heads=%d Secs=%d\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
                           }
          default: printf("Unknown Record at %s\n",fmt(&sec,cdisk,l));
          };
          }
          }
          goto lp;
f1:       l+=sec.len;
          goto f0;
f2:       i=(l ? 1 : 0);
          l+=sec.len+cdisk->sectors;
          if (i==0) if (int13(0x42,cdisk->drive,0L,cdisk->heads*cdisk->sectors,&sec)==0) if (sec.tag==0xaa55) {
          printf("Unexpected Record at Cylinder 1\n");
          }
          goto f0;
case 'W': ext=0;j=cdisk->partsecs;
          s=(char *)calloc(j+1,1024);
          if (s==0) {printf("Not Enough Memory\n");goto lp1;}
          for (i=0;i<j;i++) {
          l=i;
          if (int13(0x42,cdisk->drive,0L,l,s+(i<<9))) {printf("Error on Disk %x Sector %lx\n",cdisk->drive,l);free(s);goto lp1;}
          }
          memcpy(s+((j+1)<<9),s,j<<9);
          if (cdisk->install) {
          if (cdisk->partsecs>1) {
          memcpy(s,mbr2,0x1a2);s[0x1b2]='R';s[0x1b3]='L';
          }
          else {
          memcpy(s,mbr,0x18a);
          for (i=0x18a;i<0x1b4;i++) s[i]=0;
          }
          s[0x1fe]=0x55;s[0x1ff]=0xaa;
          }
          for (ss=s,i=0;i<=j;ss+=512,i++) {
          if (i) if (cdisk->id[i]) if (cdisk->id[i]-s[(i<<9)+0x1fe]) {
          memcpy(ss,s+512,512);
          ss[0x1fe]=cdisk->id[i];ss[0x1ff]=1;ss[0x3fe]=0;
          }
          if (i) if (cdisk->id0[i]) if (cdisk->id0[i]-s[(i<<9)+0x1fe]) {
          if (cdisk->id0[i]=='d') memcpy(ss,dos,512);
          if (cdisk->id0[i]=='w') memcpy(ss,win,512);
          ss[0x3fe]=0;
          }
          if (cdisk->id[i]) {
          for (k=0x1be;k<0x1fe;k++) ss[k]=0;
          p=cdisk->list;k=0x1be;
          while(p) {
          for (x=0;x<63;x++) if (p->partsec[x]==(i+1)) {
          if (k==0x1fe) {printf("Too Many Partitions in Sector %d\n",i);goto lp3;}
          for (x=0;x<63;x++) if (p->active[x]==(i+1)) {ss[k]=0x80;x=63;}
          l=p->start;
          *(long *)(ss+k+8)=l;
          ss[k+1]=(l/p->sectors)%p->heads;
          ss[k+2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          ss[k+3]=x;ss[k+2]+=(x>>2)&192;
          ss[k+4]=p->type;
          l+=p->len;
          *(long *)(ss+k+12)=p->len;
          l--;
          ss[k+5]=(l/p->sectors)%p->heads;
          ss[k+6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          ss[k+7]=x;ss[k+6]+=(x>>2)&192;
          if ((l^ll)&0xfffffc00) {ss[k+5]=p->heads-1;ss[k+6]=192+p->sectors;ss[k+7]=255;}
          x=63;k+=16;
          }
          p=p->next;
          }
          if (sr) if (ss[0x1be]==0) for (k=0x1ce;k<0x1fe;k+=16) if (ss[k]) {
          if (ss[k+4]-7) {
          memcpy(cmd,ss+k,16);memcpy(cmd+16,ss+0x1be,k-0x1be);
          memcpy(ss+0x1be,cmd,k-0x1ae);goto swapd;
          }
          }
swapd:
          }
          }
          if (cdisk->partsecs>1) {
          s[0x1b0]=cdisk->active;
          if (cdisk->active-'?') {
          for (i=1;i<63;i++) if (cdisk->id[i]==cdisk->active) goto saok;
          i=1;
          saok: memcpy(s+0x1be,s+0x1be+(i<<9),64);
          }
          }
          p=cdisk->list;
          while(p) {
          if (p->lpart) {
          ep=p->lpart;
          while(ep) {
          ext1=(struct psec *)calloc(sizeof(struct psec),1);
          if (ext1==0) {printf("Not Enough Memory\n");goto lp3;}
          ext1->next=ext;ext=ext1;ext->blk=ep->base;
          if (int13(0x42,cdisk->drive,0L,ep->base,ext->s1)) {printf("Error on Disk %x Sector %lx\n",cdisk->drive,ep->base);goto lp3;}
          memcpy(ext->s2,ext->s1,512);
          for (i=0x1be;i<0x1fe;i++) ext->s1[i]=0;
          ext->s1[0x1fe]=0x55;ext->s1[0x1ff]=0xaa;
          l=ep->start;ss=ext->s1+0x1be;
          *(long *)(ss+8)=ep->start-ep->base;
          ss[1]=(l/p->sectors)%p->heads;
          ss[2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          ss[3]=x;ss[2]+=(x>>2)&192;
          ss[4]=ep->type;
          l+=ep->len;
          *(long *)(ss+12)=ep->len;
          l--;
          ss[5]=(l/p->sectors)%p->heads;
          ss[6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          ss[7]=x;ss[6]+=(x>>2)&192;
          if ((l^ll)&0xfffffc00) {ss[5]=p->heads-1;ss[6]=192+p->sectors;ss[7]=255;}
          ep=ep->next;
          if (ep) {
          l=ep->base;ss=ext->s1+0x1ce;
          *(long *)(ss+8)=ep->base-p->start;
          ss[1]=(l/p->sectors)%p->heads;
          ss[2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          ss[3]=x;ss[2]+=(x>>2)&192;
          ss[4]=5;
          l=ep->start+ep->len;
          *(long *)(ss+12)=l-ep->base;
          l--;
          ss[5]=(l/p->sectors)%p->heads;
          ss[6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          ss[7]=x;ss[6]+=(x>>2)&192;
          if ((l^ll)&0xfffffc00) {ss[5]=p->heads-1;ss[6]=192+p->sectors;ss[7]=255;}
          }
          }
          }
          p=p->next;
          }
          p=cdisk->list;
          while(p) {
          if (p->valid==1) {
          k=1;
          if ((p->type==0xb) || (p->type==0xc)) k=9;
          for (i=0;i<k;i++) {
          printf("Erasing %lx\n",p->start+i);
          }
          }
          ep=p->lpart;
          while(ep) {
          if (ep->valid==1) {
          k=1;
          if ((ep->type==0xb) || (ep->type==0xc)) k=9;
          for (i=0;i<k;i++) {
          printf("Erasing %lx\n",ep->start+i);
          }
          }
          ep=ep->next;
          }
          p=p->next;
          }
          l=k=(j+1)<<9;
          if (k==1024) k=512;
          for (i=0;i<k;i++) if (s[i]-s[i+l]) printf("Diff %x: %02x %02x\n",i,s[i+l],s[i]);
          ext1=ext;
          while(ext1) {
          for (i=0;i<512;i++) if (ext1->s1[i]-ext1->s2[i]) printf("Sector %lx Mismatch %x: %02x %02x\n",ext1->blk,i,ext1->s2[i],ext1->s1[i]);
          ext1=ext1->next;
          }
          printf("END DIAG LIST\n");
lp3:      free(s);
lp2:      while(ext1=ext) {ext=ext->next;free(ext1);}
          if (cdisk==0) {freed();goto start;}
          goto lp1;
default:  printf("Invalid Command\n");goto lp1;
};
nomem: printf("Not Enough Memory\n");return(20);
bad: printf("Missing Argument\n");goto lp1;
}

void build(disk,n,s)
struct drive *disk;
struct sector *s;
int n;
{
int i;
struct part *p;
struct sector s2;
for (i=0;i<4;i++) if (s->parts[i].esec) {
p=add(disk,n,&(s->parts[i]));
if (p) if ((s->parts[i].type==5) || (s->parts[i].type==15)) {
buildl(disk,p,s->parts[i].off,s->parts[i].off,s->parts[i].type);
}                                                                                         
}
}

void buildl(disk,p,o,e,b)
struct drive *disk;
struct part *p;
unsigned long o,e;
unsigned char b;
{
int i;
struct sector s2;
if (int13(0x42,disk->drive,0L,o,&s2)) {printf("Error on Disk %x Sector %lx\n",disk->drive,o);return;}
for (i=0;i<4;i++) if (s2.parts[i].esec) {
if ((s2.parts[i].type-5) && (s2.parts[i].type-15)) {
addl(disk,p,o,&(s2.parts[i]),b);
}
}
for (i=0;i<4;i++) if (s2.parts[i].esec) {
if ((s2.parts[i].type==5) || (s2.parts[i].type==15)) {
buildl(disk,p,s2.parts[i].off+e,e,b);
}                                                                                         
}
}

struct part *add(disk,n,t)
struct drive *disk;
struct table *t;
int n;
{
int i;
struct part *p,*pp;
struct sector s;
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
p->start=t->off;p->len=t->len;p->type=t->type;p->partsec[0]=n+1;
p->heads=t->ehead+1;p->sectors=t->esec&63;
if (t->act) p->active[0]=n+1;
if (p->start<disk->sectors) goto ng;
if (disk->list==0) {disk->list=p;goto chk;}
pp=disk->list;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;disk->list=p;goto chk;
}
lp: if (pp->next) if (pp->next->start<=p->start) {pp=pp->next;goto lp;}
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);
i=0;
while(pp->partsec[i]) i++;
pp->partsec[i]=n+1;
if (t->act) {
i=0;
while(pp->active[i]) i++;
pp->active[i]=n+1;
}
return(0);
}
if (ov) if ((pp->start+pp->len)>p->start) if ((pp->type-5) && (pp->type-15)) goto overlap;
p->next=pp->next;pp->next=p;goto chk; 
overlap: printf("Overlap on drive %02x\n",disk->drive);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n",p->partsec[0],p->type,p->start,p->start+p->len);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n\n",pp->partsec[0],pp->type,pp->start,pp->start+pp->len);
free(p);return(0);
ng: printf("Bad Partition on drive %02x  Range %02x - %08lx\n",disk->drive,disk->sectors,disk->length);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n",p->partsec[0],p->type,p->start,p->start+p->len);
free(p);return(0);
chk: valid(disk,p);return(p);
}

void addl(disk,ep,o,t,b)
struct drive *disk;
struct part *ep;
struct table *t;
unsigned long o;
unsigned char b;
{
int i;
struct part *p,*pp;
struct sector s;
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
p->start=t->off+o;p->len=t->len;p->base=o;p->btype=b;p->type=t->type;
p->heads=t->ehead+1;p->sectors=t->esec&63;
if (p->start<ep->start) goto ng;
if ((p->start+p->len)>(ep->start+ep->len)) goto ng;
if (ep->lpart==0) {ep->lpart=p;goto chk;}
pp=ep->lpart;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;ep->lpart=p;goto chk;
}
lp: if (pp->next==0) goto fnd;
if (pp->next->start<p->start) {pp=pp->next;goto lp;}
if (ov) if ((pp->start+pp->len)>p->start) goto overlap;
fnd: p->next=pp->next;pp->next=p;goto chk; 
overlap: printf("Overlap on drive %02x\n",disk->drive);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n",p->type,p->start,p->start+p->len);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n\n",pp->type,pp->start,pp->start+pp->len);
free(p);return;
ng: printf("Bad Logical Partition on drive %02x\n",disk->drive);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n",p->type,p->start,p->start+p->len);
printf("Extend  Part Type=%02x Start=%08lx End=%08lx\n\n",ep->type,ep->start,ep->start+ep->len);
free(p);return;
chk: valid(disk,p);
}

void addx(disk,t,s,l,h)
int t,h;
unsigned long s,l;
struct drive *disk;
{
int i;
struct part *p,*pp,*ep;
if (h || (s==0)) s+=disk->sectors;
if (l<=s) {printf("Invalid Length\n");return;}
l-=s;
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
p->start=s;p->len=l;p->type=t;p->heads=disk->heads;p->sectors=disk->sectors;
if (disk->partsecs==1) p->partsec[0]=1;
if (p->start<disk->sectors) goto ng;
if ((p->start+p->len)>disk->length) printf("Partition Past End of Disk\n");
if (disk->list==0) {disk->list=p;goto chk;}
pp=disk->list;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;disk->list=p;goto chk;
}
lp: if (pp->next) if (pp->next->start<=p->start) {pp=pp->next;goto lp;}
if (ov) if (pp->next) if (pp->next->start<(p->start+p->len)) goto overlap;
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);printf("Partition Already Exists\n");return;
}
if ((pp->start+pp->len)>p->start) {
if ((pp->type-5) && (pp->type-15)) {
if (ov) goto overlap;
goto prim;
}
if (h) p->base=p->start-disk->sectors;
else {p->base=p->start;p->start+=disk->sectors;p->len-=disk->sectors;}
p->btype=pp->type;ep=pp;
if (p->start<ep->start) goto ng;
if ((p->start+p->len)>(ep->start+ep->len)) goto ng;
if (ep->lpart==0) {ep->lpart=p;goto chke;}
pp=ep->lpart;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;ep->lpart=p;goto chke;
}
lpe: if (pp->next) if (pp->next->start<p->start) {pp=pp->next;goto lpe;}
if (ov) if (pp->next) if (pp->next->start<(p->start+p->len)) goto overlap;
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);printf("Partition Already Exists\n");return;
}
if (ov) if ((pp->start+pp->len)>p->start) goto overlap;
p->next=pp->next;pp->next=p; 
chke: valid(disk,p);return;
}
prim: p->next=pp->next;pp->next=p;
chk: valid(disk,p);return;
ng: printf("Invalid Partition Parameters\n");free(p);return;
overlap: printf("Partition Overlaps Another\n");free(p);return;
}

void valid(disk,p)
struct drive *disk;
struct part *p;
{
struct sector s;
long i;
p->valid=0;
switch(p->type) {
case 1:
case 4:
case 6:
case 11:
case 12: if (int13(0x42,disk->drive,0L,p->start,&s)) printf("Error on Disk %x Sector %lx\n",disk->drive,p->start);
         if (s.tag-0xaa55) break;
         if (s.len==0) s.len=s.slen;
         p->valid=1;
         if (s.len==p->len) {
         if (s.off==p->start) {
         if (p->btype==0) p->valid=2;
         if (p->btype==15) p->valid=2;
         if (p->btype==5) p->valid=3;
         }
         if (s.off==(p->start-p->base)) {
         if (p->btype==15) p->valid=3;
         if (p->btype==5) p->valid=2;
         }
         }
         break;
};
if (p->valid==0) if ((p->type==11) || (p->type==12)) {
for (i=1;i<9;i++) {
if (int13(0x42,disk->drive,0L,p->start+i,&s)) printf("Error on Disk %x Sector %lx\n",disk->drive,p->start+i);
if (s.tag==0xaa55) {p->valid=1;return;}
}
}
}

char *fmt(s,d,x)
char *s;
struct drive *d;
unsigned long x;
{
unsigned long i,j;
i=x/d->heads/d->sectors;j=i*d->heads*d->sectors;
if (x==j) {sprintf(s,"%6ld  ",i);return(s);}
if (x==(j+d->sectors)) {sprintf(s,"%6ld+ ",i);return(s);}
sprintf(s,"%6ld/%03ld/%02ld ",i,(x-j)/d->sectors,((x-j)%d->sectors)+1);
return(s);
}

void show(dd)
struct drive *dd;
{
struct part *entry,*lg;
char *b,s1[16],s2[16],s3[16];
int i,h,a;
h=0;
if (dd->length-0xffffffff) {
printf("\nDrive=%2d Cyls=%ld Heads=%d Sectors=%d PartSecs=%d [",dd->drive-128,dd->length/dd->heads/dd->sectors,dd->heads,dd->sectors,dd->partsecs);
}
else printf("\nDrive=%d Cyls=???? Heads=%3d Sectors=%2d PartSecs=%d [",dd->drive-128,dd->heads,dd->sectors,dd->partsecs);
for (i=0;i<dd->partsecs;i++) {
if (dd->id[i]) printf("%c",dd->id[i]);
else {
if (dd->id0[i]) printf("%c",dd->id0[i]);
else printf(".");
}
}
post("K\n");
if (dd->partsecs>1) {printf("] Active %c\n\n",dd->active);post("S %c\n",dd->active);}
else printf("]\n\n");
i=0;
if (((dd->length/dd->heads/dd->sectors)-dd->cylex) || (dd->heads-dd->hdex) || (dd->sectors-dd->secex)) {
if (mode==0) printf("WARNING: INT13(48) Reports Cylinders=%ld Heads=%ld Sectors=%ld\n",dd->cylex,dd->hdex,dd->secex);
i=1;
}
if (dd->sec8) {
i=dd->hd8;
if (((dd->cyl8<1023) && (dd->cyl8-dd->cyls)) || (dd->heads-i) || (dd->sectors-dd->sec8)) {
if (mode==0) printf("WARNING: INT13(8)  Reports Cylinders=%d Heads=%d Sectors=%d\n",dd->cyl8,i,dd->sec8);
i=1;
}
}
if (i) printf("\n");
entry=dd->list;
while (entry) {
i=entry->start/dd->heads/dd->sectors;
a=strlen(fmt(s1,dd,entry->start));
if (s1[a-2]=='+') {s1[a-2]=0;a='+';}
else a=32;
post("A %x %s %s %c\n",entry->type,s1,fmt(s2,dd,entry->start+entry->len),a);
b=entry->partsec;
while (*b) post("L %x %s %c\n",entry->type,s1,dd->id[*(b++) -1]);
b=entry->active;
while (*b) post("T %x %s %c\n",entry->type,s1,dd->id[*(b++) -1]);
if (hide) if (i>=hide) {printf("*");h=1;goto skip;}
printf("Part  Type=%02x Start=%s End=%s              ",entry->type,fmt(s1,dd,entry->start),fmt(s2,dd,entry->start+entry->len));
switch(entry->valid) {
case 0: printf("     ");break;
case 1: printf("INV  ");break;
case 2: printf("VALID");break;
case 3: printf("DOSOF");
};
printf("  Ref= ");b=entry->partsec;
plp: printf("%c",dd->id[*(b++) -1]);
if (*b) goto plp;
printf("  Act= ");b=entry->active;
alp: printf("%c",dd->id[*(b++) -1]);
if (*b) goto alp;
printf("\n");
if ((entry->heads-dd->heads) || (entry->sectors-dd->sectors)) printf("WARNING: Partition Geometry Set To %d Heads %d Sectors\n",entry->heads,entry->sectors);
if ((entry->start+entry->len)>dd->length) printf("WARNING: Partition Past End Of Disk\n");
lg=entry->lpart;
if ((hide==0) && lg) {printf("*\n");goto skip;}
while(lg) {
i=lg->start/dd->heads/dd->sectors;
a=strlen(fmt(s1,dd,lg->start));
if (s1[a-2]=='+') {s1[a-2]=0;a='+';}
else a=32;
post("A %x %s %s %c\n",lg->type,s1,fmt(s2,dd,lg->start+lg->len),a);
if (hide) if (i>=hide) {printf("*");h=1;goto skip1;}
printf("LPart Type=%02x Start=%s End=%s Base=%s",lg->type,fmt(s1,dd,lg->start),fmt(s2,dd,lg->start+lg->len),fmt(s3,dd,lg->base));
switch(lg->valid) {
case 0: printf("\n");break;
case 1: printf("INV  \n");break;
case 2: printf("VALID\n");break;
case 3: printf("DOSOF\n");
};
if ((lg->heads-dd->heads) || (lg->sectors-dd->sectors)) printf("WARNING: Partition Geometry Set To %d Heads %d Sectors\n",lg->heads,lg->sectors);
if ((lg->start+lg->len)>dd->length) printf("WARNING: Partition Past End Of Disk\n");
skip1: lg=lg->next;
}
skip: entry=entry->next;
}
if (h) printf("\n");
}

void freed()
{
struct drive *d;
struct part *p,*p1,*e,*e1;
while(d=disks) {
disks=d->next;p=d->list;
while(p1=p) {
p=p->next;e=p1->lpart;
while(e1=e) {e=e->next;free(e1);}
free(p1);
}
free(d);
}
}

int free1(n)
struct part *n;
{
struct drive *d;
struct part *p,*p1,*e,*e1;
d=disks;
while(d) {
p=d->list;
if (n==p) {d->list=p->next;free(p);return(1);}
while(p) {
p1=p->next;
if (n==p1) {
while (e=p1->lpart) {p1->lpart=e->next;free(e);}
p->next=p1->next;free(p1);return(1);
}
e=p->lpart;
if (n==e) {p->lpart=e->next;free(e);return(1);}
while(e) {
e1=e->next;
if (n==e1) {e->next=e1->next;free(e1);return(1);}
e=e1;
}
p=p1;
}
d=d->next;
}
return(0);
}

struct part *find(d,t,s)
struct drive *d;
int t;
unsigned long s;
{
unsigned long ss;
struct part *p,*e;
ss=d->heads*d->sectors;s*=ss;ss+=s;
p=d->list;
while(p) {
if (p->type==t) if ((p->start>=s) && (p->start<ss)) return(p);
e=p->lpart;
while(e) {
if (e->type==t) if ((e->start>=s) && (e->start<ss)) return(e);
e=e->next;
}
p=p->next;
}
return(0);
}

int post(a,b,c,d,e)
char *a,*b,*c,*d,*e;
{
char x[64];
if (f1) {sprintf(x,a,b,c,d,e);write(f1,x,strlen(x));}
return(0);
}

int int13(c,d,x,y,b)
int c,d;
unsigned long x,y,*b;
{
unsigned int j,k;
if (mode==0) return(int13ex(c,d,x,y,b));
if (mode==1) return(int13raw(c,d,x,y,b));
if (mode==3) return(int13raw(c-0x40,d,x,y,b));
x=int13_8(d);
if (x==0) return(-1);
j=x&255;k=((x>>8)&255)+1;
switch(c) {
case 0x42: return(int13_2(d,y,b,k,j));
case 0x43: return(-1);
case 0x48: b[1]=((x>>16)&65535)+1;b[2]=k;b[3]=j;b[4]=b[1]*b[2]*b[3];return(0);
};
return(-1);
}

