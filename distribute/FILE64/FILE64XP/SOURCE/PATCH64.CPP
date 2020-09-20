/*( getnum parsearg )*/

#include <windows.h>
#include <stdio.h>
#include <rloew.h>

char *patch[]={
"A K32CloseHandle .CloseHandle",
"A K32CopyFileA .CopyFileA",
"A K32CreateFileA .CreateFileA",
"A K32DeleteFileA .DeleteFileA",
"A K32FindClose .FindClose",
"A K32FindFirstFileA .FindFirstFileA",
"A K32FindNextFileA .FindNextFileA",
"A K32FlushFileBuffers .FlushFileBuffers",
"A K32GetFileAttributesA .GetFileAttributesA",
"A K32GetFileAttributesExA .GetFileAttributesExA",
"A K32GetFileInformationByHandle .GetFileInformationByHandle",
"A K32GetFileSize .GetFileSize",
"A K32MoveFileA .MoveFileA",
"A K32ReadFile .ReadFile",
"A K32SetEndOfFile .SetEndOfFile",
"A K32SetFileAttributesA .SetFileAttributesA",
"A K32SetFilePointer .SetFilePointer",
"A K32WriteFile .WriteFile",
"A K32FindFirstFileExA .FindFirstFileExA",
"A K32CopyFileExA .CopyFileExA",
"A File64Handle FILE64.File64Handle",
"E CloseHandle FILE64.CloseHandle",
"E CopyFileA FILE64.CopyFileA",
"E CreateFileA FILE64.CreateFileA",
"E DeleteFileA FILE64.DeleteFileA",
"E FindClose FILE64.FindClose",
"E FindFirstFileA FILE64.FindFirstFileA",
"E FindNextFileA FILE64.FindNextFileA",
"E FlushFileBuffers FILE64.FlushFileBuffers",
"E GetFileAttributesA FILE64.GetFileAttributesA",
"E GetFileAttributesExA FILE64.GetFileAttributesExA",
"E GetFileInformationByHandle FILE64.GetFileInformationByHandle",
"E GetFileSize FILE64.GetFileSize",
"E MoveFileA FILE64.MoveFileA",
"E ReadFile FILE64.ReadFile",
"E SetEndOfFile FILE64.SetEndOfFile",
"E SetFileAttributesA FILE64.SetFileAttributesA",
"E SetFilePointer FILE64.SetFilePointer",
"E SetFilePointerEx FILE64.SetFilePointerEx",
"E WriteFile FILE64.WriteFile",
"E GetFileSizeEx FILE64.GetFileSizeEx",
"E FindFirstFileExA FILE64.FindFirstFileExA",
"E CopyFileExA FILE64.CopyFileExA",
"E CopyFileW FILE64.CopyFileW",
"E CreateFileW FILE64.CreateFileW",
"E DeleteFileW FILE64.DeleteFileW",
"E FindFirstFileW FILE64.FindFirstFileW",
"E FindNextFileW FILE64.FindNextFileW",
"E GetFileAttributesExW FILE64.GetFileAttributesExW",
"E MoveFileW FILE64.MoveFileW",
"E SetFileAttributesW FILE64.SetFileAttributesW",
"E _lclose FILE64._lclose",
"E _lcreat FILE64._lcreat",
"E _llseek FILE64._llseek",
"E _lopen FILE64._lopen",
"E _lread FILE64._lread",
"E _lwrite FILE64._lwrite",
"E FindFirstFileExW FILE64.FindFirstFileExW",
"E CopyFileExW FILE64.CopyFileExW",
0
};

unsigned long base,ots,ote,tb[64][4],*entry;
int t=0;
int pp=0;

int getline(char *x)
{
if (patch[pp]==0) return(-1);
strcpy(x,patch[pp++]);return(strlen(x));
}

unsigned long rtf(unsigned long x) {
int i;
if (x==0) return(0);
for (i=0;i<t;i++) {
if ((x>=tb[i][2]) && (x<tb[i][3])) return(x-tb[i][2]+tb[i][0]);
}
return(-1);
}

unsigned long ftr(unsigned long x) {
int i;
if (x==0) return(0);
for (i=0;i<t;i++) {
if ((x>=tb[i][0]) && (x<tb[i][1])) return(x-tb[i][0]+tb[i][2]);
}
return(-1);
}

int find(char *n)
{
int i,j;
for (i=ots;i<ote;i++) if (entry[(i<<2)+1]) if (strcmp((char *)entry[(i<<2)+1],n)==0) return(i);
return(-1);
}

int addstr(char *s)
{
int i;
i=strlen(s)+1;i=(int)malloc(i);
if (i==0) {printf("Not Enough Memory\n");exit(20);}
strcpy((char *)i,s);return(i);
}

void setnam(int j,char *c)
{
int k;
if (c[0]-'@') {
if (c[0]=='\\') k=addstr(c+1);
else k=addstr(c);
entry[j+1]=k;
}
else entry[j+1]=0;
}

int setval(int j,char *c)
{
int k;
if (c[0]=='.') {
if (c[1]-'@') {
if (c[1]=='\\') k=find(c+2);
else k=find(c+1);
if (k<0) return(-1);
}
else k=getnum(c+2);
k<<=2;
entry[j+2]=entry[k+2];entry[j+3]=entry[k+3];return(0);
}
if ((c[0]>47) && (c[0]<58)) {
k=strlen(c)-1;
if ((c[k]&0xdf)=='R') {c[k]=0;entry[j+2]=getnum(c);goto done;}
if ((c[k]&0xdf)=='O') {c[k]=0;entry[j+2]=ftr(getnum(c));goto done;}
entry[j+2]=getnum(c)-base;
done: entry[j+3]=0;
}
else {
if (c[0]=='\\') k=addstr(c+1);
else k=addstr(c);
entry[j+3]=k;entry[j+2]=0;
}
return(0);
}

void movedown(int i) {
int j;
j=ote<<2;
for (i<<=2;i<j;i++) entry[i-4]=entry[i];
}

void moveup(int i) {
int j;
i<<=2;
for (j=(ote<<2)-1;j>=i;j--) entry[j+4]=entry[j];
}

main(int c,char **v)
{
unsigned long *bd,*bd2,l,x,exp,expl,rva,*at,*np,pe,otx,otl,fsz,*imp,rsv,attr;
unsigned short *bs,*bs2,*ot,*ot2;
int f,f2,i,j,k,ii,jj,kk,impl,impp,noexp;
char *b,*bb,*b2,line[512],**cmd,*sptr;
rsv=0;noexp=1;attr=0x60000020;
b=(char *)malloc(3004096+1048576+0x30000);
if (b==0) {printf("Not Enough Memory\n");return(20);}
bd=(unsigned long *)b;bs=(unsigned short *)b;
b2=b+1004096;
bd2=(unsigned long *)b2;bs2=(unsigned short *)b2;
entry=(unsigned long *)(b+3004096);
imp=(unsigned long *)(b+3004096+1048576);impl=0;
if (c<3) {
bad: printf("PATCH64 Source Dest\n");return(20);
}
f=_lopen(v[1],0);
if (f<0) {printf("Cannot Open Source File\n");return(20);}
l=_llseek(f,0,2);_llseek(f,0,0);
if (l<64) goto notpe;
if (_lread(f,b,64)<64) goto rerr;
pe=bd[15];
if (pe>(l-248)) goto notpe;
_llseek(f,pe,0);
i=_lread(f,b,4096);
if (i<0) goto rerr;
x=i;
if (i<4096) if ((pe+x)<l) goto rerr;
if (bd[0]-0x4550) goto notpe;
base=bd[13];rva=bd[20];
i=30+(bd[29]<<1);j=i+(bs[3]*10);
for (k=i;k<j;k+=10) {
tb[t][0]=bd[k+5];tb[t][1]=bd[k+5]+bd[k+4];
tb[t][2]=bd[k+3];tb[t++][3]=bd[k+3]+bd[k+2];
ii=bd[k+5];jj=bd[k+4];
}
fsz=ii+jj;
impp=0;
if (bd[32]) impp=rtf(bd[32]);
exp=rtf(bd[30]);expl=bd[31];ots=ote=0;
memcpy(b+1000000,b,4096);
for (i=0;i<0x40000;i++) entry[i]=0;
bd[0]=bd[1]=bd[2]=bd[3]=0;
if (bd[30]==0) goto skipex;
if (expl>1000000) {printf("EXPORT TABLE TOO BIG\n");return(20);}
i=expl;_llseek(f,exp,0);
if (_lread(f,b,i)<i) goto rerr;
at=(unsigned long *)(b+(rtf(bd[7])-exp));
np=(unsigned long *)(b+(rtf(bd[8])-exp));
ot=(unsigned short *)(b+(rtf(bd[9])-exp));
j=bd[5];k=bd[4];jj=bd[6];
ots=k;ote=j+k;
skipex: i=4;
arg: if (c>(i+1)) {
if (v[i][0]-'-') goto bad;
switch(v[i][1]&0xdf) {
case 'S': ots=getnum(v[i+1]);break;
case 'E': ote=getnum(v[i+1]);break;
case 'R': rsv=getnum(v[i+1]);break;
default: goto bad;
};
i+=2;goto arg;
}
rva+=rsv;
if (ote<ots) ote=ots;
for (i=0;i<j;i++) if ((i+k)>=ots) if ((i+k)<ote) {
for (ii=0;ii<jj;ii++) if (ot[ii]==i) {
if ((rtf(at[i])>=exp) && (rtf(at[i])<(exp+expl))) {
entry[((i+k)<<2)+1]=(int)(b+rtf(np[ii])-exp);
entry[((i+k)<<2)+3]=(int)(b+rtf(at[i])-exp);
}
else {
entry[((i+k)<<2)+1]=(int)(b+rtf(np[ii])-exp);
entry[((i+k)<<2)+2]=at[i];
}
goto nextex;
}
if ((rtf(at[i])>=exp) && (rtf(at[i])<(exp+expl))) {
entry[((i+k)<<2)+3]=(int)(b+rtf(at[i])-exp);
}
else 
entry[((i+k)<<2)+2]=at[i];
nextex:;
}
cmd=(char **)b2;otx=65535;otl=ote-ots;
lp: i=getline(line);memcpy(line+256,line,256);
if (i<0) goto endlp;
if (i<1) goto lp;
if (line[0]==';') goto lp;
i=parsearg(cmd,line,6,32);
if (i<2) goto merr;
cmd[0][0]&=0xdf;j=0;
if (cmd[1][0]-'@') {
if (cmd[0][0]-'X') j=find(cmd[1]);
if (cmd[0][0]=='A') {
if (j>=0) goto merr;
}
else if (j<0) goto merr;
}
else j=getnum(cmd[1]+1);
if (cmd[0][0]-'X') noexp=0;
switch(cmd[0][0]) {
case 'A': if (i<3) goto merr;
          j=ote++;j<<=2;
          setnam(j,cmd[1]);
          if (setval(j,cmd[2])) {ote--;entry[j+1]=0;goto merr;}
          otl++;break;
case 'C': if (i<3) goto merr;
          setnam(j<<2,cmd[2]);
          break;
case 'D': j<<=2;entry[j]=0x80000000;entry[j+1]=0;otl--;break;
case 'E': if (i<3) goto merr;
          if (setval(j<<2,cmd[2])) goto merr;
          break;
case 'I': if (i<4) goto merr;
          j<<=2;
          while (entry[j]&0xffff) {j=entry[j];j<<=2;}
          entry[otx<<2]=0;entry[j]=otx;k=j;
          j=otx--;j<<=2;
          setnam(j,cmd[2]);
          if (setval(j,cmd[3])) {entry[j+1]=entry[k]=0;otx++;goto merr;}
          otl++;break;
case 'R': if (i<4) goto merr;
          j<<=2;
          setnam(j,cmd[2]);
          if (setval(j,cmd[3])) {entry[j+1]=0;goto merr;}
          break;
case 'X': if (i<4) goto merr;
          if (impp==0) {printf("No Import Table\n");goto merr;}
          if (strcmp(cmd[1],"*")==0) {imp[impl]=imp[impl-3];impl++;}
          else imp[impl++]=addstr(cmd[1]);
          if (cmd[2][0]=='\\') imp[impl++]=addstr(cmd[2]+1);
          else {
          if (cmd[2][0]=='@') imp[impl++]=0x80000000+getnum(cmd[2]+1);
          else imp[impl++]=addstr(cmd[2]);
          }
          if (cmd[3][0]=='\\') imp[impl++]=addstr(cmd[3]+1);
          else {
          if (cmd[3][0]=='@') imp[impl++]=0x80000000+getnum(cmd[3]+1);
          else imp[impl++]=addstr(cmd[3]);
          }
          break;
default:  goto merr;
};
goto lp;
endlp: if (noexp) {ots=ote=0;}
for (i=ots;i<ote;i++) {
j=i<<2;
if (entry[j]==0x80000000) {movedown(i+1);ote--;i--;goto retry;}
if (entry[j]&0xffff) {
ii=entry[j];jj=ii<<2;entry[j]=0;k=i;
ilp: moveup(k);ote++;memcpy(entry+(k<<2),entry+jj,16);entry[k<<2]=0;k++;
if (entry[jj]&0xffff) {ii=entry[jj];jj=ii<<2;goto ilp;}
}
retry:;
}
j=0;
for (i=ots;i<ote;i++) if (entry[(i<<2)+1]) j++;
bd2[0]=bd[0];
bd2[1]=bd[1];
bd2[2]=bd[2];
bd2[4]=ots;              //   ordinal base
bd2[5]=otl;              //   address table length
bd2[6]=j;                //   number of names
bd2[7]=rva+40;           //   address table rva
bd2[8]=bd2[7]+(otl<<2);  //   name table pointer  rva
bd2[9]=bd2[8]+(j<<2);    //   ordinal table  rva
bd2[3]=bd2[9]+(j<<1);    //   export name
sptr=b2+bd2[3]-rva;
if (bd[3]) {i=strlen(b+rtf(bd[3])-exp);strcpy(sptr,b+rtf(bd[3])-exp);sptr+=i+1;}
else {i=strlen(v[1]);strcpy(sptr,v[1]);sptr+=i+1;}
if (noexp) sptr=b2;
at=(unsigned long *)(b2+bd2[7]-rva);
np=(unsigned long *)(b2+bd2[8]-rva);
ot=(unsigned short *)(b2+bd2[9]-rva);
k=ii=jj=0;otl=otx=ots;
while (otx<ote) {
i=otx<<2;
if (entry[i+1]) {
ot[ii]=otl-ots;np[ii++]=sptr-b2+rva;
j=strlen((char *)entry[i+1]);strcpy(sptr,(char *)entry[i+1]);sptr+=j+1;
}
at[jj]=0;
if (entry[i+2]) at[jj]=entry[i+2];
if (entry[i+3]) {
at[jj]=sptr-b2+rva;
j=strlen((char *)entry[i+3]);strcpy(sptr,(char *)entry[i+3]);sptr+=j+1;
}
jj++;otl++;
skip: otx++;
}
for(i=0;i<bd2[6];i++) for(j=i+1;j<bd2[6];j++) {
if (strcmp((char *)(np[i]+b2-rva),(char *)(np[j]+b2-rva))>0) {
k=ot[i];ot[i]=ot[j];ot[j]=k;k=np[i];np[i]=np[j];np[j]=k;
}
}
_llseek(f,0,0);f2=_lcreat(v[2],0);
if (f2<0) {printf("Cannot Create Dest File\n");return(20);}
k=fsz;
cp: j=(k>1000000) ? 1000000 : k;
if (_lread(f,b,j)-j) goto rerr;
if (_lwrite(f2,b,j)-j) goto werr;
k-=j;
if (k) goto cp;
memcpy(b,b+1000000,4096);
for (i=2;i<impl;i+=3) if ((imp[i]&0x80000000)==0) {
*(sptr++)=0;*(sptr++)=0;j=strlen((char *)imp[i]);strcpy(sptr,(char *)imp[i]);
imp[i]=sptr-b2+rva-2;sptr+=j+1;
}
ii=jj=sptr-b2+rsv;
if (ii) {
jj=(ii+bd[14]-1)&(-bd[14]);
ii=(ii+bd[15]-1)&(-bd[15]);
if (rsv) printf("Reserved Area: 0x%x  Length 0x%x  RVA 0x%x  VA 0x%x\n",fsz,rsv,bd[20],bd[13]+bd[20]);
i=30+(bd[29]<<1);j=i+(bs[3]*10);
bd[j]=0x706d692e;bd[j+1]=0x707865;
bd[j+5]=fsz;bd[j+4]=ii;bd[j+3]=bd[20];bd[j+2]=sptr-b2+rsv;
bd[j+6]=bd[j+7]=bd[j+8]=0;bd[j+9]=attr;
bs[3]++;bd[7]+=ii;bd[20]+=jj;bd[22]=0;
}
if (noexp==0) {bd[30]=rva;bd[31]=sptr-b2;}
for (i=sptr-b2;i<ii;i++) b2[i]=0;
if (ii) {
if (rsv) _lwrite(f2,b2+ii-rsv,rsv);
if (ii-rsv) _lwrite(f2,b2,ii-rsv);
}
while((i=_lread(f,b2,1000000))>0) {_lwrite(f2,b2,i);}
_llseek(f2,pe,0);_lwrite(f2,b,bd[21]);
if (impl) {
_llseek(f2,impp,0);k=_lread(f2,b,1000000);memcpy(b2,b,k);
for (i=0;i<impl;i+=3) {
j=0;
while(bd[j+3]) {
ii=rtf(bd[j+3])-impp;
if (ii>k) {printf("Module Name Not in Buffer\n");return(20);}
ii+=(int)b;
if (stricmp((char *)imp[i],(char *)ii)==0) {
if ((imp[i+1]&0x80000000)==0) if (strcmp((char *)imp[i+1],".")==0) {bd2[j+3]=imp[i+2]+2;goto found;}
ii=rtf(bd[j])-impp+(int)b;
while(jj= *(int *)ii) {
if (jj&imp[i+1]&0x80000000) if (jj==imp[i+1]) {*(int *)(ii+b2-b)=imp[i+2];goto found;}
if ((jj|imp[i+1])&0x80000000) goto next;
jj=rtf(jj)-impp;
if (jj>k) {printf("Import Name Not in Buffer\n");return(20);}
if (strcmp((char *)imp[i+1],b+jj+2)==0) {*(int *)(ii+b2-b)=imp[i+2];goto found;}
next: ii+=4;
}
}
j+=5;
}
if (imp[i+1]&0x80000000) printf("Import Not Found %s @0x%x\n",imp[i],imp[i+1]&0x7fffffff);
else printf("Import Not Found %s %s\n",imp[i],imp[i+1]);
return(20);
found:;
}
_llseek(f2,impp,0);
if (_lwrite(f2,b2,k)<k) goto werr;
}
return(0);
rerr: printf("Read Error\n");return(20);
werr: printf("Write Error\n");return(20);
merr: printf("Bad ModList Entry: %s\n",line+256);
return(20);
notpe: printf("Not PE File\n");return(20);
}
