long rl(int,unsigned char *);
long find(int,int,unsigned char *,unsigned char *);

int main(int c,char **v)
{
unsigned char *b;
long x,y,z;
int e,f,i,j,k,l,ver;
char name[512],back[512];
ver=0;
if (c>1) if (v[1][0]=='-') {ver=1;c--;v++;}
printf("\nESDI_506 File Expander 1.0\n\nCopyright (C) 2006 by Rudolph R. Loew, All Rights Reserved.\n\n");
e=20;
if (c>1) if (strcmp(v[1],"/?")==0) {printf("PATCHEXP [-Verify] [PDR_File]\n");return(0);}
b=(unsigned char *)malloc(0x7ff8);
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
strcpy(back+f,".ba_");
if (stricmp(name,back)==0) {printf("Name Conflicts With Backup\n");return(20);}
f=_open((char *)name,0);
if (f<0) {printf("%s Not Found or Inaccessible\n",name);goto manual;}
i=_read(f,b,0x7ff8);
if ((i<0x300) || (i>0x6ff0)) {printf("Invalid File Size\n");goto quit;}
_close(f);
if (i<0x2000) goto fmterr;
x= *(long *)(b+0x3c);j=x;
if (x>=1024) goto fmterr;
z=i;y= *(long *)(b+j+0x80);k=y;
if ((y>=z) || (y<0x1de)) {printf("Not ESDI_506.PDR File\n");return(20);}
z= *(long *)(b+j+0xc4);z=(z+4095)& -4096;x=i;
if ((y+z)>=x) goto fmterr;
if (((*(long *)(b+j+0xe8))-(*(long *)(b+j+0xd0)))>2) {
if (ver) {printf("Patch Verified\n");goto quit;}
printf("File Already Expanded - Uninstall ? (Y/N) ");_read(0,b,4);
if ((b[0]&0xdf)-'Y') goto quit;
f=_open((char *)back,0);
if (f<0) {printf("Backup File Not Found or Inaccessible\n");return(20);}
_close(f);_dos_setfileattr(name,0);
if (unlink(name)) {printf("Cannot Unexpand File\n");return(20);}
if (rename(back,name)) {printf("Cannot Rename Backup\n");return(20);}
printf("File Unexpanded\n");return(0);
}
unlink(back);
_dos_setfileattr(name,0);
if (rename(name,back)) {printf("Cannot Rename File\n");goto quit;}
f=_creat(name,0);
if (f<0) {printf("Cannot Create Expanded File\n");goto undo;}
x= *(long *)(b+j+0x14);
(*(long *)(b+j+0x14))++;
(*(long *)(b+j+0x30))+=4;
(*(long *)(b+j+0x38))+=4;
(*(long *)(b+j+0x58))+=4;
(*(long *)(b+j+0x5C))+=4;
(*(long *)(b+j+0x68))+=4;
(*(long *)(b+j+0x6c))+=8;
(*(long *)(b+j+0x70))+=8;
(*(long *)(b+j+0x78))+=8;
(*(long *)(b+j+0x88))+=0x1008;
(*(long *)(b+j+0xb8))+=0x1008;
(*(long *)(b+j+0xd4))++;
(*(long *)(b+j+0xe8))++;
(*(long *)(b+j+0x100))++;
(*(long *)(b+j+0x118))++;
if (_write(f,b,j+0x13c)-j-0x13c) goto werr;
x<<=16;x+=65536;
if (_write(f,(char *)(&x),4)-4) goto werr;
if (_write(f,b+j+0x13c,0x22)-0x22) goto werr;
if (_write(f,b+j+0x15a,k-j-0x162)-k+j+0x162) goto werr;
j=z;
if (_write(f,b+k,j)-j) goto werr;
k+=j;
for (j=0;j<4096;j++) b[j]=0;
if (_write(f,b,4096)-4096) goto werr;
if (_write(f,b+k,i-k)-i+k) goto werr;
_close(f);_dos_setfileattr(name,7);
printf("Patch Completed\n");return(0);
werr: printf("Error Patching File\n");_close(f);unlink(name);
undo: rename(back,name);goto quit;
fmterr: printf("Not ESDI_506.PDR File\n");return(20);
manual: printf("\nRerun Command Specifying Full Path to ESDI_506.PDR File\n");
quit: return(e);
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
