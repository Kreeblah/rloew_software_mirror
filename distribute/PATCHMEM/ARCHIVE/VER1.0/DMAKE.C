/*( -nl )*/

#define sz 8192

char *dmake(f1,f2,f3,m,b1)
int f1,f2,f3,m;
char *b1;
{
unsigned long i,j,k;
char *b2,z[5];
b2=b1+sz;
lp: i=_read(f2,z,5);
if (i==0) {
if (_read(f1,b1,1)>0) return("Incorrect Diff File");
return(0);
}
if (i-5) goto derr;
if (m) if (z[4]>1) z[4]^=1;
i= *(unsigned long *)z;
//if (z[4]) if (i>sz) return("Block Too Large");
switch(z[4]) {
case 0: while(i>0) {
        j=i;
        if (j>sz) j=sz;
        if (_read(f1,b1,j)<j) goto rerr;
        if (_write(f3,b1,j)<j) goto werr;
        i-=j;
        }
        goto lp;
case 1: while(i>0) {
        k=i;
        if (k>sz) k=sz;
        if (_read(f1,b1,k)<k) goto rerr;
        if (_read(f2,b2,k)<k) goto derr;
        for (j=0;j<k;j++) b1[j]^=b2[j];
        if (_write(f3,b1,k)<k) goto werr;
        i-=k;
        }
        goto lp;
case 2: while(i>0) {
        j=i;
        if (j>sz) j=sz;
        if (_read(f2,b2,j)<j) goto derr;
        if (_write(f3,b2,j)<j) goto werr;
        i-=j;
        }
        goto lp;
case 3: while(i>0) {
        k=i;
        if (k>sz) k=sz;
        if (_read(f1,b1,k)<k) goto rerr;
        if (_read(f2,b2,k)<k) goto derr;
        for (j=0;j<k;j++) if (b1[j]-b2[j]) return("Incorrect Diff File or Already Patched");
        i-=k;
        }
        goto lp;
case 4: if (_read(f2,b2,4)<4) goto rerr;
        while(i>0) {
        k=i;
        if (k>sz) k=sz;
        for (j=4;j<k;j+=4) *(unsigned long *)(b2+j)= *(unsigned long *)b2;
        if (_write(f3,b2,k)<k) goto werr;
        i-=k;
        }
        goto lp;
case 5: if (_read(f2,b2,4)<4) goto rerr;
        while(i>0) {
        k=i;
        if (k>sz) k=sz;
        if (_read(f1,b1,k)<k) goto rerr;
        for (j=4;j<k;j+=4) *(unsigned long *)(b2+j)= *(unsigned long *)b2;
        for (j=0;j<k;j++) if (b1[j]-b2[j]) return("Incorrect Diff File or Already Patched");
        i-=k;
        }
        goto lp;
default: return("Unknown Block");
};
rerr: return("Source Too Short");
derr: return("Error Reading Diff File");
werr: return("Error Writing Dest");
}
