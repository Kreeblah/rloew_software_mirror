#include <windows.h>
#include <stdio.h>

main(int c,char **v)
{
int f,i,j,l1,l2,*x1,*x2;
char *b1,*b2;
b1=(char *)malloc(2000000);
if (b1==0) {printf("Not Enough Memory\n");return(20);}
b2=b1+1900000;x1=(int *)b1;x2=(int *)b2;
f=_lopen(v[1],0);
if (f<0) {printf("Cannot Open %s\n",v[1]);return(20);}
i=_lread(f,b1,1900000);
if (i==1900000) {printf("File %s Too Long\n",v[1]);return(20);}
l1= *(int *)(b1+8);
if (i-l1) {printf("Error Reading %s or Bad File\n",v[1]);return(20);}
_lclose(f);
f=_lopen(v[2],0);
if (f<0) {printf("Cannot Open %s\n",v[2]);return(20);}
i=_lread(f,b2,100000);
if (i==100000) {printf("File %s Too Long\n",v[2]);return(20);}
l2= *(int *)(b2+8);
if (i-l2) {printf("Error Reading %s or Bad File\n",v[2]);return(20);}
_lclose(f);
*(int *)(b1+0xa81)= *(int *)(b2+0x36);
j=x1[23];x1[23]=x2[2]-x2[9]+x1[21];x1[2]+=x1[23]-j;
f=_lcreat(v[1],0);
if (f<0) {printf("Cannot Create %s\n",v[1]);return(20);}
if (_lwrite(f,b1,x1[21])-x1[21]) goto werr;
if (_lwrite(f,b2+0x49,l2-0x49)-l2+0x49) goto werr;
if (_lwrite(f,b1+j,l1-j)-l1+j) goto werr;
_lclose(f);return(0);
werr: printf("Error Writing %s\n",v[1]);return(20);
}
