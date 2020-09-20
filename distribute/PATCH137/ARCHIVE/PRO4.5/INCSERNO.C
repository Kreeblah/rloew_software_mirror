main(c,v)
int c;
char **v;
{
int f,i,j,k,l;
unsigned char b[16384];
if (c<2) {printf("INCSERNO FILE\n");return(20);}
f=_open(v[1],0);
if (f<0) {printf("Cannot Open Source\n");return(20);}
i=_read(f,b,16384);_close(f);
if (i<4096) {printf("Bad File\n");return(20);}
if (i>16382) {printf("File Too Big\n");return(20);}
i-=8;l= -1;
for (j=2;j<i;j++) if ((*(unsigned long *)(b+j))==0x80808080) {
if ((*(unsigned int *)(b+j+4))==0x8080) j++;
j-=2;
if (l>=0) {printf("Duplicate Serial Key Found\n");return(20);}
k=b[j+1]-128;l=b[j]-128;l=(k*10)+l+1;
if (l>99) {printf("Cannot Increment Serial Number Above 99\n");return(20);}
b[j]=b[j+7]=128+(l%10);b[j+1]=b[j+6]=128+(l/10);j+=8;
}
if (l>=0) {
i+=8;f=_creat(v[1],0);
if (f<0) {printf("Cannot Create Dest\n");return(20);}
if (_write(f,b,i)<i) {printf("Error Writing Dest\n");return(20);}
_close(f);printf("\n\nNEW SERIAL NUMBER = %d\n\n",l);return(0);
}
printf("Serial Key Not Found or Greater Than 99\n");return(20);
}

