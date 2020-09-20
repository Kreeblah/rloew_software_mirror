/*( getnum )*/

#define sz 8192

long getnum();

main(c,v)
int c;
char **v;
{
char *b1,z[12];
int f1,f2,m;
unsigned long i,j,x,y,fill;
fill=0;
if (c>1) if (v[1][0]=='-') {m=1;c--;v++;}
if (c<6) {
badarg: printf("PADDIFF Diff Dest Add/Remove Offset Length [Fill.L]\n");
return(20);
}
switch(v[3][0]&0xdf) {
case 'A': m=0;break;
case 'R': m=1;break;
default: goto badarg;
};
x=getnum(v[4]);y=getnum(v[5]);
if (c>6) fill=getnum(v[6]);
b1=(char *)malloc(sz+sz);
if (b1==0) {printf("Not Enough Memory\n");return(20);}
if ((f1=_open(v[1],0))<0) {printf("Cannot Open Diff File\n");return(20);}
if ((f2=_creat(v[2],0))<0) {printf("Cannot Create Dest File\n");return(20);}
lp: i=_read(f1,z,5);
if (i==0) {
if (m) {
if (x) {printf("Pad After End of File\n");return(20);}
*(long *)b1=y;b1[4]=4;*(long *)(b1+5)=fill;
if (_write(f2,b1,9)<9) goto werr;
return(0);
}
printf("No Pad To Remove\n");return(20);
}
if (i-5) goto derr;
if (m) if (z[4]>1) z[4]^=1;
i= *(unsigned long *)z;
if (z[4]) if (i>sz) {printf("Block Too Large\n");return(20);}
switch(z[4]) {
case 0: if (i<=x) {
        if (_write(f2,z,5)<5) goto werr;
        x-=i;goto lp;
        }
        if (x) {
        *(long *)z=x;
        if (_write(f2,z,5)<5) goto werr;
        i-=x;
        }
        *(long *)b1=y;b1[4]=4+m;*(long *)(b1+5)=fill;
        if (_write(f2,b1,9)<9) goto werr;
        *(long *)z=i;
        if (_write(f2,z,5)<5) goto werr;
        goto rest;
case 1:
case 2: if (i<=x) {
        if (_write(f2,z,5)<5) goto werr;
        x-=i;
        if (_read(f1,b1,i)<i) goto rerr;
        if (_write(f2,b1,i)<i) goto werr;
        goto lp;
        }
        if (x) {
        *(long *)z=x;
        if (_write(f2,z,5)<5) goto werr;
        i-=x;
        if (_read(f1,b1,x)<x) goto rerr;
        if (_write(f2,b1,x)<x) goto werr;
        }
        *(long *)b1=y;b1[4]=4+m;*(long *)(b1+5)=fill;
        if (_write(f2,b1,9)<9) goto werr;
        *(long *)z=i;
        if (_write(f2,z,5)<5) goto werr;
        if (_read(f1,b1,i)<i) goto rerr;
        if (_write(f2,b1,i)<i) goto werr;
        goto rest;
case 3: if (_read(f1,b1,i)<i) goto rerr;
        if (_write(f2,z,5)<5) goto werr;
        if (_write(f2,b1,i)<i) goto derr;
        goto lp;
case 4: if (y<i) {printf("Nested Pads\n");return(20);}
        y-=i;
case 5: if (_read(f1,z+5,4)<4) goto rerr;
        if (_write(f2,z,9)<9) goto werr;
        goto lp;
default: free(b1);printf("Unknown Block\n");return(20);
};
rest: while (i=_read(f1,b1,sz)) {
if (i>sz) goto rerr;
if (_write(f2,b1,i)<i) goto derr;
}
return(0);
rerr: printf("Source Too Short\n");return(20);
derr: printf("Error Reading Diff File\n");return(20);
werr: printf("Error Writing Dest\n");return(20);
}
