/*( ring0 getnum getline parsearg user32.lib /largeaddressaware /fixed:no /base:0x80000000 /section:.text,ers /section:.rdata,rs /section:.edata,rs /section:.bss,rws /section:.data,rws /SUBSYSTEM:WINDOWS )*/

#include <windows.h>
#include <stdio.h>
#include <signal.h>
#include <rloew.h>


//#define DEMO


#ifdef DEMO
#define dsize 1024
#else
#define dsize 65536
#endif


char gpa[]={
0x60,0xe8,0,0,0,0,0x61,0xe9,0,0,0,0,
0,0,0,0,
'D','L','L','H','O','O','K',

#ifdef DEMO
' ','D','E','M','O',
#endif

0};
char undec[256];
int p1=0;
int p2=0;
int p3=0;
int d=0;
int d1=0;
int map[dsize/4]={0};
int n=0;
int p=dsize-1;
int flags=0;
int retres=0;
int *cksm;

typedef int (__stdcall *hprc)(HINSTANCE);
hprc proc;
int **table;

void strcpyx(char *a,char *b)
{
lp: (*a)=(*b);
if ((*a)=='@') *a=0;
if (*a) {a++;b++;goto lp;}
}

int strcmpx(char *a,char *b)
{
lp: if ((*a)-(*b)) return(1);
if (*a) {a++;b++;goto lp;}
return(0);
}

int setup(char *s,int f)
{
HINSTANCE h;
int i;
if (f) h=GetModuleHandle(s);
else h=LoadLibrary(s);
if (h) {
i=(*proc)(h);
if (i==0) goto bad;
i= *(short *)(i+16);i=(*table)[i];i= *(int *)(i+4);
if (i==0) goto bad;
return(i);
}
return(0);
bad: if (f==0) FreeLibrary(h);
return(0);
}

void prochook(int a) {
int i,j,k,l,*p;
char s[128];
p=&a;
if ((d1>0xbff70000) && (d1<0xc0000000)) {
if ((*(int *)p[11])==0x484c4c44) if ((*(int *)(p[11]+4))==0x5f4b4f4f) {
p[11]+=8;return;
}
if ((*(int *)p[11])==0x686c6c64) if ((*(int *)(p[11]+4))==0x5f6b6f6f) {
p[11]+=8;strcpyx(undec,(char *)(p[11]));p[11]=(int)undec;
return;
}
}
flags&= -3;
for (i=0;i<n;i+=4) {
if (map[i+1]== -1) goto nm;
if (map[i+1]) if (strcmpx((char *)p[11],(char *)(map[i+1]))) goto nm;

#ifdef DEMO
if (map[i]) if (setup("KERNEL32",1)-p[9]) goto nm;
#else
if (map[i]) if (setup((char *)(map[i]),1)-p[9]) goto nm;
#endif

if (map[i+3]) p[11]=map[i+3];
if (map[i+2]) if (i=setup((char *)(map[i+2]),0)) p[9]=i;
goto done;
nm:;
}
done:

#ifndef DEMO
if (flags&15) {
retry: i=p[9];j=p[10];k=p[11];
_asm {
push [k]
push [j]
push [i]
mov eax,[d1]
call eax
mov [retres],eax
};

if (retres==0) {
if ((flags&2)==0) {
flags|=2;
for (i=0;i<n;i+=4) {
if (map[i+1]+1) goto nm2;
if (map[i]) if (setup((char *)(map[i]),1)-p[9]) goto nm2;
if (map[i+3]) p[11]=map[i+3];
if (map[i+2]) if (i=setup((char *)(map[i+2]),0)) p[9]=i;
goto retry;
nm2:;
}
i=p[9];
}
if (flags&12) {
GetModuleFileName((HMODULE)(*(int *)(i+0x34)),s,128);
j=0;l=strlen(s);
for (i=0;i<l;i++) if (s[i]=='\\') j=i+1;
if (j) strcpy(s,s+j);
strcat(s,":");strcat(s,(char *)k);strcat(s,"  Not Found");
if (flags&4) MessageBox(0,s,gpa+16,MB_ICONERROR);
if (flags&8) {
i=_lopen("C:\\DLLHOOK.LOG",2);
if (i<0) i=_lcreat("C:\\DLLHOOK.LOG",0);
if (i>=0) {_llseek(i,0,2);strcat(s,"\r\n");_lwrite(i,s,strlen(s));_lclose(i);}
}
return;
}
}
_asm {
mov eax,[retres]
mov esp,ebp
pop ebp
pop ebx
mov [esp+28],eax
popad
ret 12
};
}
#endif

return;
}

// To test entry point __stdcall (*d1)(p[9],p[10],p[11]);

// To return value:  Put in EAXSAVE, backout, RET 12


void checksum(int *b,int l)
{
l>>=2;
while(l--) *cksm+=b[l];
}

int config(char *file)
{
char buff[512],*fp,*(vv[8]);
int f,i,j,x[4];
i=SearchPath(0,file,0,264,buff,&fp);
if (i==0) {
strcpy(buff,file);strcat(buff," Not Found\n");
MessageBox(0,buff,gpa+16,MB_ICONERROR);return(20);
}
f=_lopen(buff,0);
if (f<0) {
strcpy(buff,"Cannot Open ");strcat(buff,file);strcat(buff,"\n");
MessageBox(0,buff,gpa+16,MB_ICONERROR);return(20);
}
x[0]=x[1]=x[2]=x[3]=0;fp=(char *)map;fp[dsize-1]=0;
lp: i=getline(f,buff,510);
if (i==0) goto lp;
if (i>0) {
while (i&3) buff[i++]=0;
checksum((int *)buff,i);
if (buff[0]==';') goto lp;

#ifndef DEMO
if (buff[0]=='/') {
i=0;
while(buff[++i]) {
switch(buff[i]&0xdf) {
case 'S': flags|=4;break;
case 'L': flags|=8;break;






default: MessageBox(0,"Unknown Option in INI File\n",gpa+16,MB_ICONERROR);return(20);
};
}
goto lp;
}

if (buff[0]=='@') {
if (config(buff+1)) return(20);
goto lp;
}
#endif

i=parsearg((char **)vv,buff,8,32);
if ((i<3) || (i>4)) {MessageBox(0,"Incorrect Number of Arguments in INI File\n",gpa+16,MB_ICONERROR);return(20);}
if (i==3) vv[3]="-";
for (i=0;i<4;i++) {
if (strcmp(vv[i],"-")==0) {map[n+i]=0;goto done;}
if (i==1) if (strcmp(vv[i],"+")==0) {map[n+i]= -1;flags|=1;goto done;}
if (strcmp(vv[i],"*")==0) {map[n+i]=x[i];goto done;}
// if (vv[i][0]=='@') {map[n+i]=getnum(vv[i]+1);goto done;}
j=strlen(vv[i]);p-=j+1;
if (p<0) goto full;
strcpy(fp+p,vv[i]);map[n+i]=(int)(fp+p);
done:;
}
if ((map[n+1]==0) || (map[n+1]== -1))   {
if (map[n]==0) goto bad;
if (map[n+2]==0) goto bad;
if (map[n+3]) goto bad;
}
if (n>((dsize/4)-4)) goto full;
for (i=0;i<4;i++) x[i]=map[n+i];
n+=4;goto lp;
}
if ((n<<2)>p) {
full: MessageBox(0,"Too Many Redirects\n",gpa+16,MB_ICONERROR);return(20);
bad: MessageBox(0,"Bad Global Redirect\n",gpa+16,MB_ICONERROR);return(20);
}
_lclose(f);return(0);
}

int WinMain(HINSTANCE hi,HINSTANCE hp,char *v,int s)
{
int i,j,k,l,d2,d3;
HINSTANCE x;
k=0;
if (v[0]=='/') {
switch(v[1]) {
case 'e':
case 'E': k|=1;break;
case 'r':
case 'R': k|=2;break;
#ifdef DEMO
default: MessageBox(0,"DLLHOOK DEMO [/ExitPrompt | /Remove]",gpa+16,MB_ICONINFORMATION);return(20);
#else
default: MessageBox(0,"DLLHOOK [/ExitPrompt | /Remove]",gpa+16,MB_ICONINFORMATION);return(20);
#endif
};
}
i=(int)WinMain;
if (i>=0) {MessageBox(0,"Not Loaded in Shared Memory",gpa+16,MB_ICONERROR);return(20);}
x=LoadLibrary("KERNEL32");
if (x==0) {MessageBox(0,"Cannot Open KERNEL32",gpa+16,MB_ICONERROR);return(20);}
if (d) {
if (k&2) goto rest;
MessageBox(0,"DLLHOOK Already Loaded",gpa+16,MB_ICONERROR);return(20);
}
if (k&2) {MessageBox(0,"DLLHOOK Not Running",gpa+16,MB_ICONERROR);return(20);}
i=(int)x;j=i+0x70000;l=0;
for (;i<j;i++) {
if (((*(DWORD *)i)==0x142474ff) && ((*(DWORD *)(i+4))==0xe851006a)) {
if (p1) goto inv;
p1=i+8;d1=(*(int *)p1)+p1+4;l++;
} 
if (((*(DWORD *)i)==0xe075ff50) && ((*(BYTE *)(i+4))==0xe8)) {
if (p2) goto inv;
p2=i+5;d2=(*(int *)p2)+p2+4;l++;
} 
if (((*(DWORD *)i)==0x000dac68) && ((*(WORD *)(i+4))==0x5000)) {
if (p3) goto inv;
p3=i+7;d3=(*(int *)p3)+p3+4;l++;
} 
if (l==3) i=j;
}
if ((l-3) || (d1-d2) || (d1-d3)) goto inv;
cksm=(int *)(gpa+12);
if (config("dllhook.ini")) return(20);
j=d1;
while ((j<0xbff70000) || (j>=0xc0000000)) {
if ((*(WORD *)j)-0xe860) goto endchk;
if ((*cksm)==(*(int *)(j+12))) {
j=MessageBox(0,"Configuration Checksum Matches Earlier Hook - Continue?",gpa+16,MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING);
if (j-IDYES) return(20);
}
j+=(*(int *)(j+8))+12;
}
endchk: j=(int)GetProcAddress(x,"GetProcAddress");
if (j==0) {MessageBox(0,"Cannot Find GetProcAddress Entry",gpa+16,MB_ICONERROR);return(20);}
if (*(unsigned char *)(j+0x2a)-0xe9) goto inv;
j=(*(int *)(j+0x2b))+j+0x2f;
if (*(unsigned char *)(j+0x1a)-0xe8) goto inv;
if (*(unsigned short *)(j+0x27)-0xd8b) goto inv;
if (*(unsigned char *)(j+0x5e)-0xe8) goto inv;
proc=(hprc)((*(int *)(j+0x1b))+j+0x1f);table= *(int ***)(j+0x29);
*(int *)(gpa+2)=((int)prochook)-((int)gpa)-6;*(int *)(gpa+8)=d1-((int)gpa)-12;
ring0();*(int *)p1=((int)gpa)-p1-4;
*(int *)p2=((int)gpa)-p2-4;*(int *)p3=((int)gpa)-p3-4;ring3();d=d1;
if (k&1) {
MessageBox(0,"SYSTEM DLL HOOK\nCopyright (c) 2009-2011\nby Rudolph R. Loew\nAll Rights Reserved\n\nDLLHOOK ACTIVE\n\nCLICK TO REMOVE\n",gpa+16,0);
}
else {
while(d) Sleep(1000);
}
rest: if (d) {
if ((*(int *)p1)-(((int)gpa)-p1-4)) {
MessageBox(0,"Other Hook(s) Added - Remove Other Hook(s) First",gpa+16,MB_ICONERROR);
return(20);
}
ring0();*(int *)p1=d1-p1-4;*(int *)p2=d1-p2-4;*(int *)p3=d1-p3-4;ring3();d=0;
}
return(0);
inv: MessageBox(0,"Unknown Version of KERNEL32.DLL",gpa+16,MB_ICONERROR);return(20);
}
