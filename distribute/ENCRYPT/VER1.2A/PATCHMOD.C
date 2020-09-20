//char *n1="FMINST.COM";
//char *n2="PATCHMOD.DAT";
char n3[]={0x93,0xa6,0xb4,0xa6,0xb3,0xb7,0xa6,0xa5,0x6f,0x61,0x61,0x41};

#define slen 11

main(c,v)
int c;
char **v;
{
int f,i,j,k,l;
char b[24576],sn[8];
if (c>1) if (v[1][0]=='/') if (v[1][1]=='?') {printf("PATCHMOD [ProgramFile [UpdateFile]]\n");return(20);}
if (c>1) n1=v[1];
if (c>2) n2=v[2];
f=_open(n1,0);
if (f<0) {printf("Cannot Open Program File\n");return(20);}
i=_read(f,b,24576);_close(f);
if (i==24576) {printf("File Too Large\n");return(20);}
j=0;
while((n3[j])-=0x41) j++;
for (j=0;j<(i-slen);j++) if (strncmp(b+j,n3,slen)==0) {
for (k=slen;k<(slen+8);k++) if ((b[j+k]&0x80)==0) goto nfnd;
for (k=0;k<8;k++) sn[k]=b[j+k+slen];
for (k=j-96;k<(j+128);k++) if (strncmp(b+k,"Time",4)==0) goto bad;
goto ok;
nfnd:;
}
bad: printf("Not Valid Patch Program File\n");return(20);
ok: f=_open(n2,0);
if (f<0) {printf("Cannot Open Update File\n");return(20);}
i=_read(f,b,24576);_close(f);
if (i==24576) {printf("File Too Large\n");return(20);}
for (j=0;j<i;j++) b[j]^=0x37;
k=b[i-1];
for (j=i-2;j>=0;j--) {l=b[j];b[j]-=k;k=l;}
for (j=0;j<i;j++) b[j]^=0x73;
k=b[0];
for (j=1;j<i;j++) {l=b[j];b[j]-=k;k=l;}
k=0x1234567;
for (j=0;j<i;j++) {k*=13;b[j]^=k>>16;}

for (j=0;j<(i-slen);j++) if (strncmp(b+j,n3,slen)==0) {
for (k=slen;k<(slen+8);k++) if ((b[j+k]&0x80)==0) goto nfnd2;
for (k=0;k<8;k++) b[j+k+slen]=sn[k];
goto ok2;
nfnd2:;
}
printf("Cannot Verify Update File\n");return(20);
ok2: f=_creat(n1,0);
if (f<0) {printf("Cannot Update Program File\n");return(20);}
if (_write(f,b,i)-i) {printf("Error Writing File\n");return(20);}
_close(f);return(0);
}
