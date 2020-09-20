#define max 0x7ffe

main(c,v)
int c;
char **v;
{
int f,i,j,k,l;
unsigned char b[max];
if (c<2) {printf("INCSERNO FILE\n");return(20);}
f=_open(v[1],0);
if (f<0) {printf("Cannot Open Source\n");return(20);}
i=_read(f,b,max);_close(f);
if (i<4096) {printf("Bad File\n");return(20);}
if (i>(max-2)) {printf("File Too Big\n");return(20);}
i-=8;l= -1;
for (j=0;j<i;j++) if (((*(unsigned long *)(b+j))&0xf0f0f0f0)==0x80808080) if (((*(unsigned long *)(b+j+4))&0xf0f0f0f0)==0x80808080) {
if (l>=0) {printf("Duplicate Serial Key Found\n");return(20);}
l=b[j+3]-128;l*=10;
l+=b[j+2]-128;l*=10;
l+=b[j+1]-128;l*=10;
l+=b[j]-127;k=l;
if (l>9999) {printf("Cannot Increment Serial Number Above 9999\n");return(20);}
b[j]=b[j+7]=128+(k%10);k/=10;
b[j+1]=b[j+6]=128+(k%10);k/=10;
b[j+2]=b[j+5]=128+(k%10);k/=10;
b[j+3]=b[j+4]=128+k;
}
if (l>=0) {
i+=8;f=_creat(v[1],0);
if (f<0) {printf("Cannot Create Dest\n");return(20);}
if (_write(f,b,i)<i) {printf("Error Writing Dest\n");return(20);}
_close(f);printf("\n\nNEW SERIAL NUMBER = %d\n\n",l);return(0);
}
printf("Serial Key Not Found\n");return(20);
}

