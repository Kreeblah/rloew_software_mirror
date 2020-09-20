#define st 34
#define sz 92

void cnvt(n,b1,b2)
int n;
unsigned char *b1,*b2;
{
unsigned int i,j,l,b;
unsigned long x1,x2;
unsigned char k[4];
j=n*52;
for (i=0;i<j;i++) b1[i]=0;
n<<=4;
for (b=i=j=0;i<n;i++,b+=26) {
x1=b2[j+3]-st;
x2=b2[j+2]-st;
x1=(x1*sz)+x2;
x2=b2[j+1]-st;
x1=(x1*sz)+x2;
x2=b2[j]-st;
x1=(x1*sz)+x2;
j+=4;
l=b&7;x1=(x1<<6)>>l;
k[3]=b1[b>>3];
k[2]=b1[(b>>3)+1];
k[1]=b1[(b>>3)+2];
k[0]=b1[(b>>3)+3];
*(long *)(&k)|=x1;
b1[b>>3]=k[3];
b1[(b>>3)+1]=k[2];
b1[(b>>3)+2]=k[1];
b1[(b>>3)+3]=k[0];
if ((i&15)==15) j+=2;
}
}

int main(c,v)
int c;
char **v;
{
unsigned long x,y,z;
int f1,f2,i,j,k,l;
unsigned char b1[13*512],b2[(16*512)+256];
if (c<3) {printf("REPACKER Source Dest\n");return(20);}
f1=_open(v[1],0);
if (f1<0) {printf("Cannot Open Source\n");return(20);}
f2=_creat(v[2],0);
if (f2<0) {printf("Cannot Create Dest\n");return(20);}
lp: i=_read(f1,b2,(16*512)+256);
if (i==0) return(0);
j=i/66;l=0;
if (b2[(j*66)-2]-13) {l=b2[(j*66)-2]-st;l-=52;}
cnvt(j,b1,b2);
k=(j*52)+l;
if (_write(f2,b1,k)-k) goto werr;
if (l==0) goto lp;
return(0);
werr: printf("Write Error\n");return(20);
}
