/*( dmake )*/

#define sz 8192

char *dmake();

main(c,v)
int c;
char **v;
{
char *b,*r;
int f1,f2,f3,m;
m=0;
if (c>1) if (v[1][0]=='-') {m=1;c--;v++;}
if (c<4) {printf("DIFFMAKE [-Undo] File Diff Dest\n");return(20);}
b=(char *)malloc(sz+sz);
if (b==0) {printf("Not Enough Memory\n");return(20);}
if ((f1=_open(v[1],0))<0) {printf("Cannot Open File\n");return(20);}
if ((f2=_open(v[2],0))<0) {printf("Cannot Open Diff File\n");return(20);}
if ((f3=_creat(v[3],0))<0) {printf("Cannot Create Dest File\n");return(20);}
r=dmake(f1,f2,f3,m,b);
if (r) {printf("%s\n",r);return(20);}
return(0);
}

