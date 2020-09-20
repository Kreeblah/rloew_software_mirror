main(c,v)
int c;
char **v;
{
int f,i,j,k;
char b[28672];
if (c<3) {printf("ENCOD137 Source Dest\n");return(20);}
f=_open(v[1],0);
if (f<0) {printf("Cannot Open Source\n");return(20);}
i=_read(f,b,28672);_close(f);
if (i==28672) {printf("File Too Large\n");return(20);}
k=0x1234567;
for (j=0;j<i;j++) {k*=13;b[j]^=k>>16;}
k=0;
for (j=0;j<i;j++) {k+=b[j];b[j]=k;}
for (j=0;j<i;j++) b[j]^=0x73;
k=0;
for (j=i-1;j>=0;j--) {k+=b[j];b[j]=k;}
for (j=0;j<i;j++) b[j]^=0x37;
f=_creat(v[2],0);
if (f<0) {printf("Cannot Create Dest\n");return(20);}
if (_write(f,b,i)-i) {printf("Error Writing File\n");return(20);}
_close(f);return(0);
}

