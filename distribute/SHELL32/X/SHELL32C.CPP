/*( shell32a resource.res /DEF:shell32d.def /DLL /SECTION:CODE,ER /OUT:SHELL32.DLL )*/
#include <windows.h>
HINSTANCE sh,sh2;
int cnt=0;
char cpyrt[]="SHELL32 REDIRECT  VERSION 1.0                   DLL REDIRECTOR  COPYRIGHT (C)   2014 by RUDOLPH R. LOEW  -  ALL RIGHTS RESERVED";
extern "C" {
int table[712];
}
char lib[]="SHELLXX.DLL";
int start=2,end=712;
BOOL APIENTRY DllMain( HANDLE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
int i;
switch (ul_reason_for_call) {
case DLL_PROCESS_ATTACH: if ((cnt++)==0) {
if ((sh=LoadLibrary(lib))==0) return(0);
for (i=start;i<end;i++) table[i-start]=(int)GetProcAddress(sh,(char *)i);
if ((sh2=LoadLibrary("SHFOLDXX.DLL"))==0) return(0);
table[710]=(int)GetProcAddress(sh2,"SHGetFolderPathA");
table[711]=(int)GetProcAddress(sh2,"SHGetFolderPathW");
for (i=710;i<712;i++) if (table[i]==0) return(0);
}
break;
case DLL_THREAD_ATTACH:
case DLL_THREAD_DETACH: break;
case DLL_PROCESS_DETACH: if (--cnt) break;
FreeLibrary(sh);break;
}
return TRUE;
}
