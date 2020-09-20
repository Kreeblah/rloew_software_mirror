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

int yy=0x12345678;
int xx=1;
int zz=0x87654321;


char gpa2[]={0xb1,1,0x60,0xe8,0,0,0,0,0x61,0xe9,0,0,0,0};
char gpa3[]={0xb1,2,0x60,0xe8,0,0,0,0,0x61,0xe9,0,0,0,0};

char gpa[]={
0xb1,0,0x60,0xe8,0,0,0,0,0x61,0xe9,0,0,0,0,
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
int d2=0;
int d3=0;
int d20=0;
int map[dsize/4]={0};
int n=0;
int p=dsize-1;
int flags=0;
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
int i,j;
h=GetModuleHandle(s);
if (h) s=0;
else if (f==0) h=LoadLibrary(s);
if (h) {
i=(*proc)(h);
if (i==0) goto bad;
i= *(short *)(i+16);i=(*table)[i];j= *(int *)(i+4);
if (j==0) goto bad;
return(f ? j : i);
}
return(0);
bad: if (s) FreeLibrary(h);
return(0);
}

void prochook(int a) {
int i,j,k,l,m,mm,*p,x,retres;
char s[128];
p=&a;x=p[6]&3;retres=0;flags&=13;

if (x==1) if ((p[6]&0xffffff00)==0) if ((d20-d1)==8) flags|=16;


if ((d1>0xbff70000) && (d1<0xc0000000)) {
if ((*(int *)p[11])==0x484c4c44) if ((*(int *)(p[11]+4))==0x5f4b4f4f) {
p[11]+=8;goto exit1;
}
if ((*(int *)p[11])==0x686c6c64) if ((*(int *)(p[11]+4))==0x5f6b6f6f) {
strcpyx(undec,(char *)(p[11]+8));p[11]=(int)undec;
goto exit1;
}
}
for (i=0;i<n;i+=4) {
if (map[i+1]== -1) goto nm;
if (map[i+1]) if (strcmpx((char *)p[11],(char *)(map[i+1]))) goto nm;

#ifdef DEMO
if (map[i]) if (setup("KERNEL32",1)-p[9]) goto nm;
#else
if (map[i]) if (setup((char *)(map[i]),1)-p[9]) goto nm;
#endif

if (map[i+3]) p[11]=map[i+3];
if (map[i+2]) if (k=setup((char *)(map[i+2]),0)) {
p[9]= *(int *)(k+4);

#ifndef DEMO
if (x==0) p[5]=k;
if (x==1) {
p[7]=k;p[6]=0;

xx=p[6];

if ((d20-d1)==8) flags|=16;
}
#endif

}
goto done;
nm:;
}
done:

#ifndef DEMO

if (flags&15) {
retry: i=p[9];j=p[10];k=p[11];l=p[15];m=p[2];mm=x ? p[7] : p[5];
switch(x) {
case 0: _asm {
        push [l]
        push [l]
        push [l]
        push ebp
        mov edx,[mm]
        mov eax,[d1]
        push [k]
        push [j]
        push [i]
        mov ebp,[m]
        call eax
        pop ebp
        add esp,12
        mov [retres],eax
        };
        break;
case 1: if (flags&16) {
        _asm {
        push ebp
        mov eax,[mm]
        mov edx,[d2]
        push [k]
        push [j]
        push [i]
        mov ebp,[m]
        add edx,23
        call edx
        pop ebp
        mov [retres],eax
        };
        }
        else {
        _asm {
        push ebp
        mov edx,[d2]
        push [k]
        push [j]
        push [i]
        mov ebp,[m]
        call edx
        pop ebp
        mov [retres],eax
        };
        }
        break;
case 2: _asm {
        push [k]
        push [j]
        push [i]
        mov eax,[d3]
        call eax
        mov [retres],eax
        };
};
if (retres==0) {
if ((flags&2)==0) {
flags|=2;
for (i=0;i<n;i+=4) {
if (map[i+1]+1) goto nm2;
if (map[i]) if (setup((char *)(map[i]),1)-p[9]) goto nm2;
if (map[i+3]) p[11]=map[i+3];
if (map[i+2]) if (k=setup((char *)(map[i+2]),0)) {
p[9]= *(int *)(k+4);
if (x==0) p[5]=k;
if (x==1) {
p[7]=k;p[6]=0;
if ((d20-d1)==8) flags|=16;
}
}
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
if (flags&4) MessageBox(0,s,gpa+18,MB_ICONERROR);
if (flags&8) {
i=_lopen("C:\\DLLHOOK.LOG",2);
if (i<0) i=_lcreat("C:\\DLLHOOK.LOG",0);
if (i>=0) {_llseek(i,0,2);strcat(s,"\r\n");_lwrite(i,s,strlen(s));_lclose(i);}
}
goto exit1;
}
}
p[7]=retres;
_asm {
mov esp,ebp
pop ebp
pop ebx
popad
ret 12
};
}
exit1: if (flags&16) {
_asm {
mov esp,ebp
pop ebp
pop ebx
popad
mov edx,[d2]
add edx,0x17
jmp edx
};
}
#endif

return;
}

// To test entry point __stdcall (*dx)(p[9],p[10],p[11]);

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
MessageBox(0,buff,gpa+18,MB_ICONERROR);return(20);
}
f=_lopen(buff,0);
if (f<0) {
strcpy(buff,"Cannot Open ");strcat(buff,file);strcat(buff,"\n");
MessageBox(0,buff,gpa+18,MB_ICONERROR);return(20);
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
default: MessageBox(0,"Unknown Option in INI File\n",gpa+18,MB_ICONERROR);return(20);
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
if ((i<3) || (i>4)) {MessageBox(0,"Incorrect Number of Arguments in INI File\n",gpa+18,MB_ICONERROR);return(20);}
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
if ((map[n+1]==0) || (map[n+1]== -1)) {
if (map[n]==0) goto bad;
if (map[n+2]==0) goto bad;
if (map[n+3]) goto bad;
}
if (n>((dsize/4)-4)) goto full;
for (i=0;i<4;i++) x[i]=map[n+i];
n+=4;goto lp;
}
if ((n<<2)>p) {
full: MessageBox(0,"Too Many Redirects\n",gpa+18,MB_ICONERROR);return(20);
bad: MessageBox(0,"Bad Global Redirect\n",gpa+18,MB_ICONERROR);return(20);
}
_lclose(f);return(0);
}

int WinMain(HINSTANCE hi,HINSTANCE hp,char *v,int s)
{
int i,j,k,l;
HINSTANCE x;
k=0;
if (v[0]=='/') {
switch(v[1]&0xdf) {
case 'E': k|=1;break;
case 'Q': k|=2;break;
case 'R': k|=6;break;
#ifdef DEMO
default: MessageBox(0,"DLLHOOK DEMO [/ExitPrompt | /Remove | /QuietRemove]",gpa+18,MB_ICONINFORMATION);return(20);
#else
default: MessageBox(0,"DLLHOOK [/ExitPrompt | /Remove | /QuietRemove]",gpa+18,MB_ICONINFORMATION);return(20);
#endif
};
}
i=(int)WinMain;
if (i>=0) {MessageBox(0,"Not Loaded in Shared Memory",gpa+18,MB_ICONERROR);return(20);}
x=LoadLibrary("KERNEL32");
if (x==0) {MessageBox(0,"Cannot Open KERNEL32",gpa+18,MB_ICONERROR);return(20);}
if (d) {
if (k&2) goto rest;
MessageBox(0,"DLLHOOK Already Loaded",gpa+18,MB_ICONERROR);return(20);
}
if (k&2) {
if (k&4) MessageBox(0,"DLLHOOK Not Running",gpa+18,MB_ICONERROR);
return(20);
}
i=(int)x;j=i+0x4dff8;l=0;
for (;i<j;i++) {
if (((*(DWORD *)i)==0x142474ff) && ((*(DWORD *)(i+4))==0xe851006a)) {
if (p1) goto inv;
p1=i+8;d1=(*(int *)p1)+p1+4;l++;
} 
if (((*(DWORD *)i)==0x75ff5056) && ((*(WORD *)(i+4))==0xe8e0)) {
if (p2) goto inv;
p2=i+6;d2=(*(int *)p2)+p2+4;l++;
} 
if (((*(DWORD *)i)==0x000dac68) && ((*(WORD *)(i+4))==0x5000)) {
if (p3) goto inv;
p3=i+7;d3=(*(int *)p3)+p3+4;l++;
} 
if (l==3) i=j;
}
d20=d2;
if (l-3) goto inv;

#ifdef DEMO
if (d2-d1) goto demok;
#endif

j=gpa2-gpa;
if (d2-d1-8) {
if (d2-d1-j) if ((d1-d2) || (d1-d3)) goto inv;
}
else {
if ((*(short *)d2)-0x25ff) goto invk;
d2= *(int *)(d2+2);d2= *(int *)d2;
if ((*(DWORD *)(d2+20))-0x5082048b) goto invk;
}
cksm=(int *)(gpa+14);
if (config("dllhook.ini")) return(20);
j=d1;
while ((j<0xbff70000) || (j>=0xc0000000)) {
if ((*(WORD *)j)-0xe860) goto endchk;
if ((*cksm)==(*(int *)(j+12))) {
j=MessageBox(0,"Configuration Checksum Matches Earlier Hook - Continue?",gpa+18,MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING);
if (j-IDYES) return(20);
}
j+=(*(int *)(j+8))+12;
}
endchk: j=(int)GetProcAddress(x,"GetProcAddress");
if (j==0) {MessageBox(0,"Cannot Find GetProcAddress Entry",gpa+18,MB_ICONERROR);return(20);}
if (*(unsigned char *)(j+0x2a)-0xe9) goto inv;
j=(*(int *)(j+0x2b))+j+0x2f;
if (*(unsigned char *)(j+0x1a)-0xe8) goto inv;
if (*(unsigned short *)(j+0x27)-0xd8b) goto inv;
if (*(unsigned char *)(j+0x5e)-0xe8) goto inv;
proc=(hprc)((*(int *)(j+0x1b))+j+0x1f);table= *(int ***)(j+0x29);
*(int *)(gpa+4)=((int)prochook)-((int)gpa)-8;
*(int *)(gpa+10)=d1-((int)gpa)-14;
*(int *)(gpa2+4)=((int)prochook)-((int)gpa2)-8;
*(int *)(gpa2+10)=d2-((int)gpa2)-14;
*(int *)(gpa3+4)=((int)prochook)-((int)gpa3)-8;
*(int *)(gpa3+10)=d3-((int)gpa3)-14;
if ((j=ring0())) {
if ((j&0xff800000)==0xff800000) {MessageBox(0,"Unsupported Hypervisor - Contact Author",gpa+18,MB_ICONERROR);return(20);}
else {MessageBox(0,"Unsupported Windows Version",gpa+18,MB_ICONERROR);return(20);}
}
*(int *)p1=((int)gpa)-p1-4;
*(int *)p2=((int)gpa2)-p2-4;
*(int *)p3=((int)gpa3)-p3-4;
ring3();d=d1;
if (k&1) {
MessageBox(0,"SYSTEM DLL HOOK Version 2.0\nCopyright (c) 2009-2012\nby Rudolph R. Loew\nAll Rights Reserved\n\nDLLHOOK ACTIVE\n\nCLICK TO REMOVE\n",gpa+18,0);
}
else {
while(d) Sleep(1000);
}
rest: if (d) {
if ((*(int *)p3)-(((int)gpa3)-p3-4)) {
MessageBox(0,"Other Hook(s) Added - Remove Other Hook(s) First",gpa+18,MB_ICONERROR);
return(20);
}
ring0();*(int *)p1=d1-p1-4;*(int *)p2=d20-p2-4;*(int *)p3=d3-p3-4;ring3();d=0;
}
return(0);
inv: MessageBox(0,"Unknown Version of KERNEL32.DLL",gpa+18,MB_ICONERROR);return(20);
invk: MessageBox(0,"Unknown Version of KERNELEX",gpa+18,MB_ICONERROR);return(20);
demok: MessageBox(0,"KERNELEX not supported in Demo Version",gpa+18,MB_ICONERROR);return(20);
}
