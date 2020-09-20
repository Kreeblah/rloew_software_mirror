/*( getnum )*/

#define sz 8192
#define szm (sz-1)
#define szh (sz>>1)

unsigned char *buff1,*buff2;
char *buff3;
unsigned long addr1,addr2,ptr1,ptr2;
long compmem(),getnum(),d,dm,dp;
void insert(long,long);
int f3;

main(c,v)
int c;
char **v;
{
int f1,f2;
long lim,lim1,step,ce,cm,cn,fd1,fd2,i,j,k,l;
unsigned long fill1,fill2;
if (c<4) {printf("MAKEDIFF File1 File2 Dest [Step [Limit [M [N [E]]]]]\n");return(20);}
if ((buff1=(unsigned char *)malloc(sz+sz+sz))==0) {printf("Not Enough Memory\n");return(20);}
buff2=buff1+sz;buff3=(char *)(buff2+sz);
if ((f1=_open(v[1],0))<0) {printf("Cannot Open File1\n");return(20);}
if ((f2=_open(v[2],0))<0) {printf("Cannot Open File2\n");return(20);}
if ((f3=_creat(v[3],0))<0) {printf("Cannot Create Dest File\n");return(20);}
lim=512;cm=12;cn=16;ce=4;step=1;addr1=addr2=ptr1=ptr2=d=dm=dp=0;fd1=fd2=1;
if (c>4) step=getnum(v[4]);
if (c>5) lim=getnum(v[5]);
if (c>6) cm=getnum(v[6]);
if (c>7) cn=getnum(v[7]);
if (c>8) ce=getnum(v[8]);
fill1=_read(f1,buff1,sz);
if (fill1== -1) {printf("Cannot Read File1\n");return(20);}
fill2=_read(f2,buff2,sz);
if (fill2== -1) {printf("Cannot Read File2\n");return(20);}
if (fill1<sz) fd1=0;
if (fill2<sz) fd2=0;
loop: if ((fd1) && ((fill1-addr1)<=szh)) {
i=_read(f1,buff1+(fill1&szm),szh);
if (i<0) {printf("Read Error on File1\n");i=0;}
fill1+=i;
if (i<szh) fd1=0;
}
if ((fd2) && ((fill2-addr2)<=szh)) {
i=_read(f2,buff2+(fill2&szm),szh);
if (i<0) {printf("Read Error on File2\n");i=0;}
fill2+=i;
if (i<szh) fd2=0;
}
if (addr1>=fill1) {
i=(fill2-addr2)&(-16);
if (i) {insert(0,i);addr2+=i;goto loop;}
insert(0,fill2-addr2);goto done;
}
if (addr2>=fill2) {
i=(fill1-addr1)&(-16);
if (i) {insert(i,0);addr1+=i;goto loop;}
insert(fill1-addr1,0);goto done;
}
more: i=fill1-addr1-szh;
j=fill2-addr2-szh;
if (j<i) i=j;
j=sz-(addr1&szm);
if (j<i) i=j;
j=sz-(addr2&szm);
if (j<i) i=j;
k=i;
if (i<1) i=1;
j=compmem(buff1+(addr1&szm),buff2+(addr2&szm),i);
if (j==0) {
addr1+=i;addr2+=i;
if (k>0) goto more;
goto loop;
}
addr1+=j-1;addr2+=j-1;addr1&= -step;addr2&= -step;
lim1=fill1-addr1-cn;i=fill2-addr2-cn;
if (i<lim1) lim1=i;
if (lim<lim1) lim1=lim;
if (lim1<step) {lim1+=cn;goto term;}
for (i=step;i<=lim1;i+=step) {
k=ce;
for (l=0;l<ce;l++) if (buff1[(addr1+i+l)&szm]!=buff2[(addr2+i+l)&szm]) k= -cn;
for (l=ce;l<cn;l++) if (buff1[(addr1+i+l)&szm]==buff2[(addr2+i+l)&szm]) k++;
if (k>=cm) {
insert(i,i);addr1+=i;addr2+=i;goto loop;
}
for (j=0;j<i;j+=step) {
k=ce;
for (l=0;l<ce;l++) if (buff1[(addr1+i+l)&szm]!=buff2[(addr2+j+l)&szm]) k= -cn;
for (l=ce;l<cn;l++) if (buff1[(addr1+i+l)&szm]==buff2[(addr2+j+l)&szm]) k++;
if (k>=cm) {
insert(i,j);addr1+=i;addr2+=j;goto loop;
}
k=ce;
for (l=0;l<ce;l++) if (buff1[(addr1+j+l)&szm]!=buff2[(addr2+i+l)&szm]) k= -cn;
for (l=ce;l<cn;l++) if (buff1[(addr1+j+l)&szm]==buff2[(addr2+i+l)&szm]) k++;
if (k>=cm) {
insert(j,i);addr1+=j;addr2+=i;goto loop;
}
}
}
term: insert(lim1,lim1);addr1+=lim1;addr2+=lim1;goto loop;
done: if (dm || dp) printf("Deviation Ranges From %ld To %ld\n",dm,dp);
else printf("Replacement Only - No Deviations\n");
return(0);
}

void insert(l1,l2)
long l1,l2;
{
unsigned long i,j;
char z[5];
d+=l2-l1;
if (d>dp) dp=d;
if (d<dm) dm=d;
i=addr1-ptr1;j=addr2-ptr2;
if (i-j) {printf("Matched Area Sizes Unequal\n");exit(20);}
if (i) {
*(unsigned long *)z=i;z[4]=0;ptr1=addr1;ptr2=addr2;
if (_write(f3,z,5)<5) goto werr;
}
i=l1;
if (l2<i) i=l2;
if (i) {
for (j=0;j<i;j++) buff3[j]=buff1[(addr1+j)&szm]^=buff2[(addr2+j)&szm];
*(unsigned long *)z=i;z[4]=1;ptr1+=i;ptr2+=i;
if (_write(f3,z,5)<5) goto werr;
if (_write(f3,buff3,i)<i) goto werr;
}
if (l2>l1) {
for (j=0;j<(l2-l1);j++) buff3[j]=buff2[(addr2+i+j)&szm];
*(unsigned long *)z=l2-l1;z[4]=2;ptr2+=l2-l1;
if (_write(f3,z,5)<5) goto werr;
if (_write(f3,buff3,l2-l1)<(l2-l1)) goto werr;
}
if (l1>l2) {
for (j=0;j<(l1-l2);j++) buff3[j]=buff1[(addr1+i+j)&szm];
*(unsigned long *)z=l1-l2;z[4]=3;ptr1+=l1-l2;
if (_write(f3,z,5)<5) goto werr;
if (_write(f3,buff3,l1-l2)<(l1-l2)) goto werr;
}
return;
werr: printf("Error Writing Dest\n");exit(20);
}

long compmem(s1,s2,l)
unsigned char *s1, *s2;
long l;
{
long i;
for (i=0;i<l;i++) if (s1[i]-s2[i]) return(i+1);
return(0);
}
