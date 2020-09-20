/*( getnum )*/

/*

Diagnostic:

Mapped 0xFFC00000 to 2:00000000 (PSE)
If 2:00000000 = 'RRLD'
Calls [2:00000004]

*/

#define max 0x6000

#define DEMO

char v3name[256],v3back[256];
char vname[256],vback[256];
char cname[256],cback[256];
char *b,*diff,*buff;             // buff is Duplicate of b
int f,f2,n,np;
long cbase,table[1024],lseek();
int mnum,cntx,cntv,cntc;
long base,dta;
int m16=0;
int au=0;
int r3=0;

struct info {
char *data,*mask;
int len;
long addr,*cmd;
};

struct mod {
int len;
long addr,*cmd;
} listx[8],listv[29],listc[4];

#ifdef SELF
char cr[]="                Windows 9X RAM Limitation Patch 6.1B Copyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.        ";
#endif

#ifdef PRO
char cr[]="                Windows 9X RAM Limitation Patch 6.1B Copyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.€€€€€€€€";
#endif

#ifdef DEMO
char cr[]="                Windows 9X RAM Limitation Patch 6.1B  (DEMO) Copyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.";
#endif

char subr[2796];
int reloff,*rel;

char mz[]={
0x4d,0x5a,0,0,6,0,0,0,4,0,0,0,0xff,0xff,0,0,
0xb8,0,0,0,0,0,0,0,0x40,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0x80,0,0,0,
0xe,0x1f,0xba,0xe,0,0xb4,9,0xcd,0x21,0xb8,1,0x4c,0xcd,0x21,0x54,0x68,
0x69,0x73,0x20,0x70,0x72,0x6f,0x67,0x72,0x61,0x6d,0x20,0x63,0x61,0x6e,0x6e,0x6f,
0x74,0x20,0x62,0x65,0x20,0x72,0x75,0x6e,0x20,0x69,0x6e,0x20,0x44,0x4f,0x53,0x20,
0x6d,0x6f,0x64,0x65,0x2e,0xd,0xa,0x24,0,0,0,0,0,0,0,0,
};

int comp98[]={
0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x26,
0x2e,0x33,0x38,0x56,0x6e,0x77,0x7c,0x86,
0xad,0xa6d,0xa88,0xac3,0xacd,0xad8,0xae0,0
};

int compme[]={
0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x26,
0x2e,0x33,0x38,0x56,0x6e,0x77,0x7c,0x86,
0xac,0xa6c,0xa87,0xac2,0xacc,0xad7,0xadf,0
};

char msk20[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF
};

char mgetd[]={0xB4,0x08,0xFF,0x1E,0x00,0x00,0x0B,0xC0,0x0F,0x84,0x00,0x00,0x66,0x0F,0xB7,0xC8,0x8B,0xD0,0x66,0x51,0xB4,0x09};
char mgetm[]={0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
long mgetc[]={1,0x80,-6,0x74c00966,-10,0xc1896613,-14,0x90c28966,21,0x80,0,0};

char sigvd[]={0x52,0x52,0x4C,0x00};

char sigxd[]={0x52,0x52,0x4C,0x00};

long lenc[]={0,0x91e4,0,0};

char tab1d[]={0x3d,0x34,0x08,0x00,0x00,0x72,0x05,0xb8,0x34,0x08,0x00,0x00};
long tab1c[]={1,0x65c,8,0x65c,0,0};

char tab2ad[]={
0xC7,0x44,0x24,0x18,0xD0,0x52,0x00,0x00,0xC7,0x44,0x24,0x14,0xD0,0x52,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0xE8,0x00,0x00,0x00,0x00
};

char tab2am[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00
};
long tab2ac[]={4,0x3f00,12,0x3f00,52,0x50,57,1,-58,-1    ,0,0};
// JMP pat98

char cmtd[]={0x68,0x08,0x00,0x02,0x20,0x6a,0x00,0x6a,0x04,0x6a,0x06,0x8b};
long cmtc[]={9,0x400,0,0};

char tab2bd[]={0xC7,0x44,0x24,0x30,0x00,0x00,0xA0,0x00,0xC7,0x44,0x24,0x2C,0x00,0x60,0x00,0x00};
long tab2bc[]={12,0x4000,0,0};

char flgd[]={
0x80,0xE1,0x81,0x80,0xC9,0x01,0x88,0x48,0x02,0xFF,0x05,0x00,0x00,0x00,0x00,0xEB,
0x00,0x66,0xC7,0x45,0x00,0x00,0x00,0x8A,0x48,0x02,0x80,0xE1,0x84,0x80,0xC9,0x04,
0x88,0x48,0x02
};

char flgm[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,
0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF
};

long flgc[]={2,-0x80,28,-0x80,0,0};

char pat98d[]={
0x05,0x00,0x00,0x00,0x00,0x50,0xE8,0x00,0x00,0x00,0x00,0xE9,0x00,0x00,0x00,0x00,
// Diagnostic Supplement
0x50,0xf,0x20,0xe0,0xc,0x10,0xf,0x22,0xe0,0xc7,5,0xfc,0xef,0xbf,0xff,0xe7,
0x40,0,0,0xf,0x20,0xd8,0xf,0x22,0xd8,0x81,0x3d,0,0,0xc0,0xff,0x52,
0x52,0x4c,0x44,0x75,8,0x60,0xff,0x15,4,0,0xc0,0xff,0x61,0x58,0xe9,0xfa,
0xff,0xf,0
};

// ME

long mlenc[]={0,0x11000,0,0};

char patme1d[]={0x81,0xC6,0x00,0x00,0x00,0x00,0x8B,0xFA,0x8B,0xD6,0x2B,0xD7,0xC3};
//2 1D4C->16DF0

char patme2d[]={
0xC7,0x45,0xE4,0x0A,0x00,0x00,0x00,0xC7,0x45,0xF0,0x04,0x00,0x00,0x00,0xC7,0x45,
0xF8,0x08,0x00,0x02,0x20,0xE9,0x00,0x00,0x00,0x00
};
// 22   JMP     6E0B9

char mtabp1d[]={0x57,0xBE,0x00,0x00,0x00,0x00,0x8B,0xFA,0x8B,0xD6,0x2B,0xD7,0x2B,0xC1};
char mtabp1m[]={0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
long mtabp1c[]={6,0x5D,-7,-1  ,11,-0x47,0,0};
// 3 CALL 15-E000

char mtab1d[]={0x8D,0x78,0xFF,0xB8,0x34,0x08,0x00,0x00,0x3B,0xF8};
long mtab1c[]={4,0x8bc,0,0};

char mtab2ad[]={
0xC1,0xE0,0x04,0x05,0x00,0x00,0x00,0x00,0xA3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB8,0xD0,0x52,
0x00,0x00,0x89,0x45,0xE8,0x89,0x45,0xEC,0x8D,0x45,0xE4,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x00,0xC7,0x45,0xE4,0x0A,0x00,
0x00,0x00,0xC7,0x45,0xF0,0x04,0x00,0x00,0x00,0xC7,0x45,0xF8,0x08,0x00,0x02,0x20
};

char mtab2am[]={
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

long mtab2ac[]={0,0x8b842a,62,0x5D30,86,0x50,91,-0x9A,-92,0x8360,96,0xE950,-98,-1  ,-102,0x0504e0c1,-106,-1  ,110,0x73e9,0,0};
// 13 JMP 15-E00D
// 17 1D5C->16E00

char mcmtd[]={0x6a,0x00,0x6a,0x04,0x6a,0x06,0xc1};
long mcmtc[]={4,0x400,0,0};

char mtab2bd[]={0xC7,0x45,0xD0,0x00,0x60,0x00,0x00,0xC7,0x45,0xD4,0x00,0x00,0xA0,0x00};
long mtab2bc[]={3,0x4000,0,0};

// VCACHE

char sigcd[]={0x52,0x52,0x4C,0x00};

char vcd[]={
0xA1,0x00,0x00,0x00,0x00,0x3D,0x00,0x20,0x03,0x00,0x72,0x17,0xB8,0x00,0x20,0x03,
0x00,0xA3,0x00,0x00,0x00,0x00,0x39,0x05,0x00,0x00,0x00,0x00,0x72,0x05,0xA3,0x00,
0x00,0x00,0x00
};

char vcm[]={
0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00
};

long vcc[]={6, -1,13,-1  ,0,0};

#ifdef DEMO
char demojd[]={0x90,0xcd,0x20,0x01,0x00,0x05,0x00};
long demojc[]={1,0x1b,-2,-1  ,6,0x90,0,0};
// 3 CALL DEMOPD

char demopd[]={
0x57,0x65,0x6c,0x63,0x6f,0x6d,0x65,0x20,0x74,0x6f,0x20,0x25,0x73,0x27,0x73,0x20,
0x64,0x65,0x62,0x75
};
long demopc[]={0,0x9c94bb76,4,0x679296,8,0xdae0915b,12,0xe980d8ca,16, 0x4e9c0d9c,0,0};
#endif

#ifdef SELF
char ring31d[]={0x0D,0x03,0x02,0x00,0x00,0x8B,0x54,0x24,0x04,0x89,0x02};
char ring32d[]={0xC7,0x44,0x24,0x24,0x08,0x00,0x02,0x20};
char ring33d[]={0x3B,0xE8,0x72,0x21,0x68,0x08,0x00,0x02,0x20};
char ring34d[]={0x3D,0x00,0x10,0x00,0x00,0x72,0x22,0x68,0x08,0x00,0x02,0x20};
char ring35d[]={0x00,0x00,0x68,0x08,0x00,0x02,0x20,0x6A,0x00,0x6A,0x04,0x6A,0x06};
char ring36d[]={0xC7,0x44,0x24,0x3C,0x08,0x00,0x02,0x20};
char ring37d[]={0x00,0x00,0x68,0x08,0x00,0x02,0x20,0x6A,0x00,0x6A,0x04,0x6A,0x01};
char ring38d[]={0x77,0x27,0x68,0x08,0x00,0x02,0x20};
long ring31c[]={1,4,0,0};
long ring32c[]={6,4,0,0};
long ring33c[]={7,4,0,0};
long ring34c[]={10,4,0,0};
long ring35c[]={5,4,0,0};
long ring36c[]={6,4,0,0};
long ring37c[]={5,4,0,0};
long ring38c[]={5,4,0,0};

char ring31md[]={0x0D,0x03,0x02,0x00,0x00,0x8B,0x54,0x24,0x04,0x89,0x02};
// char ring32md[]={0xC7,0x45,0xF8,0x08,0x00,0x02,0x20};  // R3 Mod in Patch
char ring33md[]={0xBF,0x08,0x00,0x02,0x20,0x3B,0x4D,0x08};
char ring34md[]={0x2B,0xCA,0x68,0x08,0x00,0x02,0x20,0x6A,0x00};
long ring31mc[]={1,4,0,0};
// long ring32mc[]={5,4,0,0};
long ring33mc[]={3,4,0,0};
long ring34mc[]={5,4,0,0};
#endif

char prothk1d[]={0x60,0xBE,0x34,0x00,0x00,0x00};
char prothk2d[]={0xBC,0x00,0x00,0x00,0x00,0x66,0x8C,0xD8,0x66,0x8E,0xD0};
char prothk3d[]={
0x3d,0x4c,0x4c,0x52,0x52,0x74,0x06,0xbe,0x34,0x00,0x00,0x00,0xc3,0x8b,0xec,0x8b,
0x5d,0x28,0xf6,0x45,0x32,0x02,0x74,0x09,0x0f,0xb7,0x45,0x2c,0xc1,0xe0,0x04,0x03,
0xd8,0x2e,0x8b,0x03,0x3d,0x0f,0x20,0xc0,0x90,0x75,0xdc,0x83,0x45,0x28,0x06,0x83,
0xc3,0x08,0x66,0xb8,0x30,0x00,0x66,0x8e,0xd8,0x66,0x8e,0xc0,0x58,0x89,0x5d,0x24,
0x61,0x58,0xff,0xe0,
};
char prothk2m[]={0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
long prothk1c[]={1,0x2A,-2,-1   ,0,0};
//JMP [mod1+prothk2+1]-0x400 = prothk3

char agp1d[]={0xbd,0x00,0x00,0x0c,0x00};
char agp2d[]={
0xbd,0x00,0x00,0x0c,0x00,0xa8,0x08,0x75,0x0f,
0x81,0x7c,0x24,0x40,0x00,0x10,0x00,0x00,0x72,0x05,0xbd,0x00,0x00,0x08,0x00,0xc3
};
long agp1c[]={0,0x2B,-1,-1   ,0,0};
long agplenc[]={0,25,0,0};

char agpm1d[]={0xc7,0x45,0x08,0x00,0x00,0x0c,0x00};
char agpm2d[]={
0xc7,0x45,0x08,0x00,0x00,0x0c,0x00,0xf6,0xc1,0x08,0x75,0x0e,
0x3d,0x00,0x10,0x00,0x00,0x72,0x07,0xc7,0x45,0x08,0x00,0x00,0x08,0x00,0xc3
};
long agpm1c[]={0,0x21,-1,-1   ,5,0x9084,0,0};
long agpmlenc[]={0,27,0,0};



long noch[]={0,0};

char mem01d[]={0xb4,0x08,0xff,0x1e,0x00,0x00,0x0b,0xc0,0x75};
char mem01m[]={0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff};
long mem01c[]={-2,-1   ,0,0};
//+4 = HIMEM PTR.W  +1 -> call memp01, nop

char mem02d[]={0x66,0x33,0xc9,0x66,0x51,0xe8};
long mem02c[]={0,-1   ,0,0};
//+0 -> call memp01+0x13 - old

char memp01[]={0x50,0xb4,0x09,0xba,0x00,0x3c,0xff,0x1e,0x00,0x00,0xe8,0x13,0x00,0x58,0xff,0x1e,0x00,0x00,0xc3,
0xe8,0x0a,0x00,0xb4,0x0a,0xff,0x1e,0x00,0x00,0x66,0x31,0xc9,0xc3,
0xe8,0x03,0x00,0xc3,0x00,0x00,0x58,0x50,0x53,0x89,0xc3,0x2e,0x87,0x57,0x01,0x5b,0xc3
};
//+8 +10 +1A <- HIMEM PTR.W

char mpad[]={'M','P','A','D','M','P','A','D'};

struct info win98[]={             // Order must be maintained  Ref  0,2,6
{0,0,0,-1,lenc},
{tab1d,msk20,12,-1,tab1c},
{tab2ad,tab2am,62,-1,tab2ac},
{cmtd,msk20,12,-1,cmtc},
{tab2bd,msk20,16,-1,tab2bc},
{flgd,flgm,35,-1,flgc},
{pat98d,0,-16,-1,0},

#ifdef DEMO
{demojd,msk20,7,-1,demojc},
{demopd,msk20,20,-1,demopc},
#endif

{0,0,0,0,0}
};

struct info winme[]={             // Order must be maintained  Ref 0,1,2,3,5 
{0,0,0,-1,mlenc},
{patme1d,0,-13,-1,0},
{patme2d,0,-26,-1,0},
{mtabp1d,mtabp1m,14,-1,mtabp1c},
{mtab1d,msk20,10,-1,mtab1c},
{mtab2ad,mtab2am,112,-1,mtab2ac},
{mcmtd,msk20,7,-1,mcmtc},
{mtab2bd,msk20,14,-1,mtab2bc},

#ifdef DEMO
{demojd,msk20,7,-1,demojc},
{demopd,msk20,20,-1,demopc},
#endif

{0,0,0,0,0}
};

struct info realm[]={
{mgetd,mgetm,22,-1,mgetc},
{0,0,0,0,0}
};

#ifdef SELF
struct info win98r3[]={
{ring31d,msk20,11,-1,ring31c},
{ring32d,msk20,8,-1,ring32c},
{ring33d,msk20,9,-1,ring33c},
{ring34d,msk20,12,-1,ring34c},
{ring35d,msk20,13,-1,ring35c},
{ring36d,msk20,8,-1,ring36c},
{ring37d,msk20,13,-1,ring37c},
{ring38d,msk20,7,-1,ring38c},
{0,0,0,0,0}
};

struct info winmer3[]={
{ring31md,msk20,11,-1,ring31mc},
// {ring32md,msk20,7,-1,ring32mc},
{ring33md,msk20,8,-1,ring33mc},
{ring34md,msk20,9,-1,ring34mc},
{0,0,0,0,0}
};
#endif

struct info prothk[]={             // Order must be maintained  Ref  0,1,2
{prothk1d,msk20,6,-1,prothk1c},
{prothk2d,prothk2m,11,-1,noch},
{prothk3d,0,-68,-1,0},
{0,0,0,0,0}
};

struct info agp[]={                // Order must be maintained  Ref  0,1,2
{0,0,0,-1,agplenc},
{agp1d,msk20,5,-1,agp1c},
{agp2d,0,-25,-1,0},
{0,0,0,0,0}
};

struct info agpm[]={               // Order must be maintained  Ref  0,1,2
{0,0,0,-1,agpmlenc},
{agpm1d,msk20,7,-1,agpm1c},
{agpm2d,0,-27,-1,0},
{0,0,0,0,0}
};

struct info sigs[]={              // Order must be maintained  Ref 0,1,2
{sigvd,0,-4,-1,0},
{sigvd,0,-4,-1,0},
{cr,0,-124,-1,0},
{0,0,0,0,0}
};

struct info sigx[]={              // Order must be maintained  Ref 0
{sigxd,0,-4,-1,0},
{0,0,0,0,0}
};

struct info vc[]={                // Order must be maintained  Ref 0,1,2,3,5 
{sigcd,0,-4,-1,0},
{vcd,vcm,35,-1,vcc},
{0,0,0,0,0}
};

struct info mem[]={               // Order must be maintained  Ref 2,3
{mem01d,mem01m,9,-1,mem01c},
{mem02d,msk20,6,-1,mem02c},
{mpad,msk20,8,-1,noch},
{memp01,0,-49,-1,0},
{0,0,0,0,0}
};

int scan(f,b,w)
int f;
char *b;
struct info *w;
{
int p1,p2,i,j,k;
long a;
char *s1,*s2;
lseek(f,0L,0);p1=p2=0;a=0;
lp: if (p1>(p2-64)) {
memcpy(b,b+p1,p2-p1);p2-=p1;p1=0;
i=_read(f,b+p2,max-p2);
if (i<0) return(-1);
p2+=i;
if (p1>(p2-64)) goto done;
}
i=0;
while(w[i].addr) {
if (w[i].len>0) {
s1=w[i].data;s2=w[i].mask;k=w[i].len;
for (j=0;j<k;j++) if ((b[p1+j]^s1[j])&s2[j]) goto miss;
if (w[i].addr>=0) return(-2);
w[i].addr=a;
}
miss: i++;
}
a++;p1++;goto lp;
done: i=0;
while(w[i].addr) {
if (w[i].len>0) {
if (w[i].addr<0) return(-3);
}
i++;
}
return(0);
}

long getic(f,b,p,l,m)
int f,m;
long *b,*p,*l;
{
int i,j;
long x,z,*bb;
x=0x3c;
lseek(f,x,0);
if (_read(f,&x,4)<4) return(-1);
lseek(f,x,0);
if (_read(f,b,4)<4) return(-1);
if (m) {
if ((b[0]&65535)-0x454c) return(-2);
vc[0].addr=x-4;return(x);
}
switch (b[0]&65535) {
case 0x3357: sigs[0].addr=x-4;x+=0x400;break;
case 0x454c: sigs[0].addr=x-4;break;
case 0x3457: sigx[0].addr=x-4;return(-4);
default: return(-2);
};
if (m==0) {sigs[1].addr=x-4;sigs[2].addr=x-128;}
base=x;lseek(f,x,0);
if (_read(f,b,0x800)<0x800) return(-1);
if ((b[0]&65535)-0x454c) return(-2);
dta=b[0x20];
bb=b+(b[0x10]>>2);j=b[0x11];z=0;
for (i=0;i<j;i++) {
if (bb[(6*i)+5]==0x444f4349) {*p=x+b[0x10]+(i*24);*l=bb[i*6];mnum=i+1;goto ok;}
z+=bb[(i*6)+4];
}
return(-3);
ok: bb=b+(b[0x12]>>2);z=(bb[z]>>16)-1;z<<=12;z+=b[0x20];return(z);
}

long getseg(f,b,p,l,s)
int f;
long *b,*p,*l,s;
{
int i,j;
long z,*bb;
lseek(f,base,0);
if (_read(f,b,0x800)<0x800) return(-1);
bb=b+(b[0x10]>>2);j=b[0x11];z=0;
for (i=0;i<j;i++) {
if (bb[(6*i)+5]==s) {*p=base+b[0x10]+(i*24);*l=bb[i*6];goto ok;}
z+=bb[(i*6)+4];
}
return(-3);
ok: bb=b+(b[0x12]>>2);z=(bb[z]>>16)-1;z<<=12;z+=b[0x20];return(z);
}

int comp(f)
int f;
{
int i,j;
long x;
char *b;
lseek(f,0L,0);
if (read(f,buff,0x6000)<0x6000) return(0);
for (i=0x228;i<0x5500;i++) if ((*(long *)(buff+i))==0x2e061e60) if ((*(int *)(buff+i+4))==0x3689) {
b=buff+i-0x28;j=0;
while(comp98[j]) (*(int *)(b+comp98[j++]))-=i;
x=0;
for (j=0;j<2792;j+=4) x+= *(long *)(b+j);
j=0;
while(comp98[j]) (*(int *)(b+comp98[j++]))+=i;
if (x==0xaaca1cbd) {j=1;goto ok;}
j=0;
while(compme[j]) (*(int *)(b+compme[j++]))-=i;
x=0;
for (j=0;j<2792;j+=4) x+= *(long *)(b+j);
j=0;
while(compme[j]) (*(int *)(b+compme[j++]))+=i;
if (x==0xf1583ad2) {j=2;goto ok;}
}
return(0);
ok: reloff=i-0x228;memcpy(subr,buff+i-0x28,2792);return(j);
}

long findrel(f,b,x)
int f;
char *b;
long x;
{
int i,j,k;
long a,c,d,e;
a=(x-dta)>>12;
c= *(long *)(buff+0x68);c+=a<<2;
e= *(long *)(buff+0x6c);
d= *(long *)(buff+c+4);
c= *(long *)(buff+c);d-=c;
if (d>(max-0x1000)) return(-1);
c+=e+base;lseek(f,c,0);
if (_read(f,b+0x1000,max-0x1000)<(max-0x1000)) return(-1);
a=(x-dta)&4095;k=d+0x1000;
i=0x1000;
while(i<k) {
if (b[i+1]&16) {
switch(b[i]) {
case 7:
case 8:    c= *(unsigned int *)(b+i+2);
           if (a-c) {i+=9;goto next;}
           if (b[i+4]-mnum) return(-10);
           return(*(long *)(b+i+5));
case 0x27:
case 0x28: for (j=0;j<b[i+2];j++) {
           c= *(unsigned int *)(b+i+8+j+j);
           if (a-c) goto next1;
           if (b[i+3]-mnum) return(-10);
           return(*(long *)(b+i+4));
           next1:;
           }
           i+=8+j+j;goto next;
default:   return(-1);
};
}
else {
switch(b[i]) {
case 7:
case 8:    c= *(unsigned int *)(b+i+2);
           if (a-c) {i+=7;goto next;}
           if (b[i+4]-mnum) return(-10);
           return(*(unsigned int *)(b+i+5));
case 0x27:
case 0x28: for (j=0;j<b[i+2];j++) {
           c= *(unsigned int *)(b+i+6+j+j);
           if (a-c) goto next2;
           if (b[i+3]-mnum) return(-10);
           return(*(unsigned short *)(b+i+4));
           next2:;
           }
           i+=6+j+j;goto next;
default: return(-1);
};
}
next:;
}
return(-2);
}

int build(x,list,cnt)
struct info *x;
struct mod *list;
int *cnt;
{
int i;
long t,*tt;
lp: if (x[0].len==0) if (x[0].cmd==0) return(0);
if (x[0].len>=0) {list[*cnt].len=0;list[*cnt].cmd=x[0].cmd;}
else {list[*cnt].len= -(x[0].len);list[*cnt].cmd=(long *)(x[0].data);}
if ((list[*cnt].addr=x[0].addr)<0) return(-1);
i= *cnt;
lp1: if (i) if (list[i].addr<list[i-1].addr) {
t=list[i].len;list[i].len=list[i-1].len;list[i-1].len=t;
t=list[i].addr;list[i].addr=list[i-1].addr;list[i-1].addr=t;
tt=list[i].cmd;list[i].cmd=list[i-1].cmd;list[i-1].cmd=tt;
i--;goto lp1;
}
x++;(*cnt)++;goto lp;
}

int procv(f,tag)
int f,tag;
{
int c,i,m,*cnt;
long a,b,x,y,z;
unsigned char *ch;
struct mod *list;

#ifdef DEMO
tag+=0x40;
#endif

m=comp(f);
if ((m-1)&0xfffe) return(-1);
if (m16) {
c=scan(f,buff,&mem);
if (mem[2].addr== -1) return(-2);
mem[3].addr=mem[2].addr;
lseek(f,mem[0].addr+4,0);
if (_read(f,&c,2)<2) goto rerr;
*(int *)(memp01+8)= *(int *)(memp01+16)= *(int *)(memp01+26)=c;
y=mem[2].addr-mem[0].addr-5;y=0x900000e8+(y<<8);mem01c[1]=y;
y=mem[2].addr-mem[1].addr+16;y=(y<<8)-0xc9327e;mem02c[1]=y;
mem[2].addr-=64;
}
if (m==1) {
c=scan(f,buff,&realm);
if (c) return(-2);
}
x=getic(f,buff,&y,&z,0);
if (x== -4) {
cnt=&cntx;list=listx;*cnt=0;sigxd[3]=tag+(m&2);
if (m==1) if (build(&realm,list,cnt)) goto bad1;
if (m16) if (build(&mem,list,cnt)) goto bad1;
if (build(&sigx,list,cnt)) goto bad1;
m|=4;goto skip;
}
cnt=&cntv;list=listv;*cnt=0;sigvd[3]=tag+(m&2);
if (x<0) return(-3);
if (m==1) {
if ((y&0xfff)>0xff0) return(-4);
win98[0].addr=y;
c=scan(f,buff,&win98);
if (c) return(-5);
y=win98[2].addr;
lseek(f,y,0);
if (_read(f,buff,62)<62) goto rerr;
x+=z;y+=62;
win98[6].addr=x;tab2ac[9]=x-y;
if (((*(long *)(buff+53))==0) || ((*(long *)(buff+53))==0)) return(-6);
*(long *)(pat98d+1)=z+20-(*(long *)(buff+53));
*(long *)(pat98d+7)=(*(long *)(buff+58))+y-x-11;
*(long *)(pat98d+12)=y-x-16;
if (r3&4) {
win98[6].len= -67;
*(long *)(pat98d+7)=5;
*(long *)(pat98d+63)=(*(long *)(buff+58))+y-x-67;
}

#ifdef DEMO
demojc[3]=win98[8].addr-win98[7].addr-6;
#endif

#ifdef SELF
if (r3&1) {
c=scan(f,buff,&win98r3);
if (c) return(-7);
if (build(&win98r3,list,cnt)) goto bad1;
}
#endif

if (r3&8) {
c=scan(f,buff,&agp);
if (c) return(-8);
x=getseg(f,buff,&y,&z,0x52434854);
if (x<0) goto bad1;
agp[0].addr=y;
agp[2].addr=x+z;
agp1c[3]=agp[2].addr-agp[1].addr-5;
if (build(&agp,list,cnt)) goto bad1;
}
if (build(&realm,list,cnt)) goto bad1;
if (m16) if (build(&mem,list,cnt)) goto bad1;
if (build(&sigs,list,cnt)) goto bad1;
if (build(&win98,list,cnt)) goto bad1;
}
if (m==2) {

#ifdef SELF
if (r3&1) patme2d[0x13]+=4;
#endif

winme[0].addr=y;
c=scan(f,buff,&winme);
if (c) return(-8);
lseek(f,base,0);
if (_read(f,buff,max)<max) goto rerr;
c= *(int *)(buff+0x14);
i=(*(int *)(buff+0x48))+2;
for (m=1;m<=c;m++) {
if (m-(*(int *)(buff+i))) return(-9);
i+=4;
}
m=2;
a=findrel(f,buff,winme[3].addr+2);
if (a<0) goto bad;
b=findrel(f,buff,winme[5].addr+4);
if (b-a-16) goto bad;
b=findrel(f,buff,winme[5].addr+87);
if (b-a-0x8360) goto bad;
winme[1].addr=x+a+0xc000;*(long *)(patme1d+2)=z-a;
winme[2].addr=x+a+0xc00d;*(long *)(patme2d+22)=winme[5].addr+0x56-winme[2].addr;
mtabp1c[3]=winme[1].addr-winme[3].addr-11;
mtab2ac[13]=winme[2].addr-winme[5].addr-102;
mtab2ac[17]=z-a;

#ifdef DEMO
demojc[3]=winme[9].addr-winme[8].addr-6;
#endif

#ifdef SELF
if (r3&1) {
c=scan(f,buff,&winmer3);
if (c) return(-10);
if (build(&winmer3,list,cnt)) goto bad1;
}
#endif

if (r3&8) {
c=scan(f,buff,&agpm);
if (c) return(-8);
x=getseg(f,buff,&y,&z,0x52434854);
if (x<0) goto bad1;
agpm[0].addr=y;
agpm[2].addr=x+z;
agpm1c[3]=agpm[2].addr-agpm[1].addr-5;
if (build(&agpm,list,cnt)) goto bad1;
}
if (m16) if (build(&mem,list,cnt)) goto bad1;
if (build(&sigs,list,cnt)) goto bad1;
if (build(&winme,list,cnt)) goto bad1;
}
if (r3&2) {
c=scan(f,buff,&prothk);
if (c) return(-10);
lseek(f,base,0);
if (_read(f,buff,max)<max) goto rerr;
mnum=1;
z=findrel(f,buff,prothk[1].addr+1);
if (z<0) goto bad;
prothk[2].addr=z=z+dta-0x400;
prothk1c[3]=z-prothk[0].addr-6;
if (build(&prothk,list,cnt)) goto bad1;
}
skip:;
return(m);
rerr: return(-11);
bad: return(-12);
bad1:



printf("%x %x %x\n",cntx,cntv,cntc); // **********************


return(-13);
}

int procc(f,tag,cache)
int f,tag;
long cache;
{
int c,i;
long a,b,x;
unsigned char *ch;
cntc=0;sigcd[3]=tag;
vcc[1]=vcc[3]=cache-0x32000;
x=getic(f,buff,0,0,1);
if (x<0) return(-1);
c=scan(f,buff,&vc);
if (c) return(-2);
if (build(&vc,&listc,&cntc)) goto bad1;
return(0);
bad1: return(-3);
}

int xfer(f,f2,l)
int f,f2;
long l;
{
int i,j;
while(l) {
j=l;
if (l>max) j=max;
i=_read(f,buff,j);
if (i<0) return(-1);
if (_write(f2,buff,i)<i) return(-1);
if (i-j) return(1);
l-=j;
}
return(0);
}

int patch(f,f2,list,cnt)
int f,f2,*cnt;
struct mod *list;
{
int i,j;
long a,b,c,*d;
a=b=0;lseek(f,0L,0);
for (i=0;i<(*cnt);i++) {
c=list[i].addr-a;
if (c>(b-256)) {
if (c<b) {
j=c;
if (_write(f2,buff,j)<j) return(-1);
memcpy(buff,buff+c,b-c);a+=c;b-=c;
c=_read(f,buff+b,max-b);
if (c<0) return(-1);
b+=c;
}
else {
if (b) {
j=b;
if (_write(f2,buff,j)<j) return(-1);
a+=b;
}
if (xfer(f,f2,list[i].addr-a)) return(-2);
a=list[i].addr;b=_read(f,buff,max);
}
c=0;
}
if (c>(b-256)) return(-3);
if (list[i].len) memcpy(buff+c,list[i].cmd,list[i].len);
else {
j=0;d=list[i].cmd;
while(d[j] || d[j+1]) {
if (d[j]>=0) (*(long *)(buff+c+d[j]))+=d[j+1];
else (*(long *)(buff+c-d[j]))=d[j+1];
j+=2;
}
}
}
if (b) {
j=b;
if (_write(f2,buff,j)<j) return(-4);
}
if (xfer(f,f2,0x7fffffff)<0) return(-5);
return(0);
}

void reset1(x)
struct info *x;
{
int i;
i=0;
while(x[i].data || x[i].cmd) {x[i].addr= -1;i++;}
}

void reset()
{
reset1(&win98);
reset1(&winme);
reset1(&realm);
reset1(&sigs);
reset1(&sigx);
reset1(&vc);
reset1(&mem);
}

int rl(f,b)
int f;
char *b;
{
int i,j;
i=0;
lp: j=_read(f,b+i,1);
if (j<1) return(0);
if (b[i]<32) {
if (i==0) goto lp;
b[i]=0;return(i);
}
if (i<255) i++;
goto lp;
}

uncomp(src,dest)
int src,dest;
{
int i,j,k,l[2];
j=(int)(&subr);k=(int)(&l);
if (rel) {
*(long *)(subr+2792)=0xcbf53de8;  // 0xe8,0x3d,0xf5,0xcb   call $-0xaco  retf
i=0;
while(rel[i]) {(*(int *)(subr+rel[i]))+=j-reloff;i++;}
rel=0;
}
j+=0xae8;
_asm {
db 0x60
push ds
push es
push ds
pop es
cld
mov bx,[k]
mov ax,[j]
mov [bx],ax
mov [bx+2],ds
mov si,[src]
mov di,[dest]
mov ax,0x2000
db 0xff,0x1f
pop es
pop ds
mov [i],ax
db 0x61
};
return(i);
}

int readx(a,bb,l)
long a;
char *bb;
int l;
{
long y,z;
int i,j;
a-=cbase;
while(l) {
y=a>>13;
if (y-np) {
lseek(f,table[y],0);
z=table[y+1]-table[y];i=z;
if (z>0x2000) return(-1);
if (z<0x2000) {
if (_read(f,b+0x6000,i)<i) return(-1);
if (uncomp(b+0x6000,b+0x4000)-8192) return(-1);
}
else {
if (_read(f,b+0x4000,8192)<8192) return(-1);
}
np=y;
}
i=a&8191;j=8192-i;
if (l<j) j=l;
memcpy(bb,b+0x4000+i,j);a+=j;bb+=j;l-=j;
}
return(1);
}

int bakname(n,b,e,r)
char *n,*b,*e;
int *r;
{
int i,j,k,l;
b[0]=0;*r=0;
if (n[0]) {
strcpy(b,n);i=strlen(b);k=l= -1;
for (j=0;j<i;j++) {
if (b[j]=='.') k=j;
if (b[j]=='\\') {k= -1;l=j;}
}
if (k<0) strcat(b,".BAK");
else strcpy(b+k+1,"BAK");
if (strlen(b)>(l+13)) {printf("Invalid %s Name\n",e);return(20);}
if (stricmp(n,b)==0) {printf("%s Name Conflicts with Backup Name\n",e);return(20);}
(*r)=4;
i=_open(n,0);
if (i>0) {_close(i);(*r)|=1;}
i=_open(b,0);
if (i>0) {_close(i);(*r)|=2;}
}
return(0);
}

main(c,v)
int c;
char **v;
{
int exist,i,j,k,maxc,h,un,vmmflag,vcflag;
long x,y,z,header[256];
char *a;

#ifdef SELF
printf("\nWindows 98/SE/ME RAM Limitation Patch  Version 6.1B RRL\nCopyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.\n\n");
#endif

#ifdef PRO
printf("\nWindows 98/SE/ME RAM Limitation Patch  Version 6.1B\nCopyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.\n\n");
#endif

#ifdef DEMO
printf("\nWindows 98/SE/ME RAM Limitation Patch  (DEMO)  Version 6.1B\nCopyright (C) 2007-2009 by Rudolph R. Loew. All Rights Reserved.\n\n");
#endif

un=1;maxc=512;f2= -1;vmmflag=vcflag=0x20;
args: if (c>1) if (v[1][0]=='/') {
switch(v[1][1]&0xdf) {
case 'A': r3|=8;break;
case 'C': if (v[1][2]-':') goto badarg;
          maxc=getnum(v[1]+3);break;
case 'I': au|=2;break;
case 'M': m16=1;break;
case 'P': r3|=2;break;

#ifdef SELF
case 'D': r3|=4;break;
case 'N': au|=1;break;
case 'R': r3|=1;break;
case 'U': au|=5;break;
#endif

default: goto badarg;
};
c--;v++;goto args;
badarg:

#ifdef DEMO
        printf("PATCHM [Options] [VMM32File VMMFile VCACHEFile]\n\n");
#else
        printf("PATCHMEM [Options] [VMM32File VMMFile VCACHEFile]\n\n");
#endif

        printf("Options:  /A    Move AGP and Unfixed Tables >=16MB to Shared Arena\n");
        printf("          /C:#  Set Absolute Max File Cache (MB)  Default = 512MB\n");

#ifdef SELF
        printf("          /D    Setup Diagnostic Page FFC00000 (64-Bit PSE)\n");
#endif

        printf("          /I    Install Only\n");
        printf("          /M    Move VXD Data above 16MB\n");

#ifdef SELF
        printf("          /N    No Query on Uninstall\n");
#endif

        printf("          /P    Install PROTHOOK\n");

#ifdef SELF
        printf("          /R    Enable Ring 3 Access to Memory Tables\n");
        printf("          /U    Uninstall Only\n");
#endif

return(20);
}
if ((c>1) && (c-4)) goto badarg;

v3name[0]=vname[0]=cname[0]=0;
buff=b=(char *)malloc(32767);
if (b==0) {printf("Not Enough Memory\n");return(20);}
f=_open("C:\\MSDOS.SYS",0);
if (f<0) goto nodir;
while((i=rl(f,b))>0) if (i>9) {
if (b[6]=='=') b[6]=0;
if (stricmp(b,"WINDIR")==0) if (v3name[0]==0) strcpy(v3name,(char *)b+7);
}
_close(f);
nodir: if (v3name[0]) {
strcpy(vname,v3name);strcat(vname,"\\SYSTEM\\VMM32\\VMM.VXD");
strcpy(cname,v3name);strcat(cname,"\\SYSTEM\\VMM32\\VCACHE.VXD");
strcat(v3name,"\\SYSTEM\\VMM32.VXD");
}
if (c>1) {
if (v[1][0]=='-') v3name[0]=0;
else if (v[1][0]-'*') strcpy(v3name,v[1]);
if (v[2][0]=='-') vname[0]=0;
else if (v[2][0]-'*') strcpy(vname,v[2]);
if (v[3][0]=='-') cname[0]=0;
else if (v[3][0]-'*') strcpy(cname,v[3]);
}
else {
if (v3name[0]==0) {printf("Cannot Locate Windows Directory\n");return(20);}
}
exist=0;
if (bakname(v3name,v3back,"VMM32",&i)) return(20);
exist|=i;
if (bakname(vname,vback,"VMM",&i)) return(20);
exist|=i<<4;
if (bakname(cname,cback,"VCACHE",&i)) return(20);
exist|=i<<8;
if ((exist&0x444)==0) {printf("No Files Specified for Update\n");return(20);}
if ((exist&3)==2) {
printf("VMM32 Backup Found without VMM32 File - Rename (Y/N) ? (N) ");read(0,&i,4);
if ((i&0xdf)-'Y') return(20);
if (rename(v3back,v3name)) {printf("Unable To Rename Backup\n");return(20);}
exist--;
}
if ((exist&0x30)==0x20) {
printf("VMM Backup Found without VMM File - Rename (Y/N) ? (N) ");read(0,&i,4);
if ((i&0xdf)-'Y') return(20);
if (rename(vback,vname)) {printf("Unable To Rename Backup\n");return(20);}
exist-=0x10;
}
if ((exist&0x300)==0x200) {
printf("VCACHE Backup Found without VCACHE File - Rename (Y/N) ? (N) ");read(0,&i,4);
if ((i&0xdf)-'Y') return(20);
if (rename(cback,cname)) {printf("Unable To Rename Backup\n");return(20);}
exist-=0x100;
}
if ((exist&1)==0) {
if (c<4) {printf("%s Missing\n",v3name);return(20);}
if ((exist&0x50)==0x40) {printf("%s File Not Found - VMM32File Required\n",vname);return(20);}
if ((exist&0x500)==0x400) {printf("%s File Not Found - VMM32File Required\n",cname);return(20);}
}
if ((exist&5)==5) {
f=_open(v3name,0);
if (f<0) {printf("Cannot Open VMM32 File\n");return(20);}
if (_read(f,b,64)<64) {printf("Error Reading VMM32 Header\n");return(20);}
z= *(long *)(b+0x3c);
lseek(f,z-4,0);
if (_read(f,b,4)<4) {printf("Error Reading VMM32 Patch Flag\n");return(20);}
z= *(long *)b;
if (z) {
if ((z&0xffffff)-0x4c5252) {printf("VMM32 File Overwritten by Unknown File\n");return(20);}
if ((exist&2)==0) {
printf("\nWARNING: Patched VMM32 File Found Without Backup - Skipping\n");
exist&=0xfff0;
if ((exist&0x50)==0x40) {printf("%s File Not Found - Unpatched VMM32File Required\n",vname);return(20);}
if ((exist&0x500)==0x400) {printf("%s File Not Found - Unpatched VMM32File Required\n",cname);return(20);}
}
}
else {
if (exist&2) {printf("VMM32 File Updated by Other Program\n");return(20);}
}
_close(f);
}
if ((exist&0x50)==0x50) {
f=_open(vname,0);
if (f<0) {printf("Cannot Open VMM File\n");return(20);}
if (_read(f,b,64)<64) {printf("Error Reading VMM Header\n");return(20);}
z= *(long *)(b+0x3c);
lseek(f,z-4,0);
if (_read(f,b,4)<4) {printf("Error Reading VMM Patch Flag\n");return(20);}
z= *(long *)b;
if (z) {
if ((z&0xffffff)-0x4c5252) {printf("VMM File Overwritten by Unknown File\n");return(20);}
if ((exist&0x20)==0) {
printf("\nWARNING: Patched VMM File Found Without Backup - Skipping\n");
exist&=0xff0f;
}
}
else {
if (exist&0x20) {printf("VMM File Updated by Other Program\n");return(20);}
}
_close(f);
}
if ((exist&0x500)==0x500) {
f=_open(cname,0);
if (f<0) {printf("Cannot Open VCACHE File\n");return(20);}
if (_read(f,b,64)<64) {printf("Error Reading VCACHE Header\n");return(20);}
z= *(long *)(b+0x3c);
lseek(f,z-4,0);
if (_read(f,b,4)<4) {printf("Error Reading VCACHE Patch Flag\n");return(20);}
z= *(long *)b;
if (z) {
if ((z&0xffffff)-0x4c5252) {printf("VCACHE File Overwritten by Unknown File\n");return(20);}
if ((exist&0x200)==0) {
printf("\nWARNING: Patched VCACHE File Found Without Backup - Skipping\n");
exist&=0xf0ff;
}
}
else {
if (exist&0x200) {printf("VCACHE File Updated by Other Program\n");return(20);}
}
_close(f);
}
i=j=0;
if ((exist&6)==6) i++;
if ((exist&6)==4) j++;
if ((exist&0x60)==0x60) i++;
if ((exist&0x60)==0x40) j++;
if ((exist&0x600)==0x600) i++;
if ((exist&0x600)==0x400) j++;
if (i && j) {
printf("Incomplete Installation Detected - Continue/UnInstall/Quit (C/U/Q) ? (Q) ");
read(0,&i,4);
if ((i&0xdf)=='C') goto inst;
if ((i&0xdf)=='U') goto uninst;
return(20);
}
if (j) {
if (au&4) {printf("\nPatch Not Installed\n");return(5);}
goto inst;
}
if (i==0) {printf("\nNo Changes Made\n\n");return(1);}

#ifndef DEMO
//#ifdef SELF
if (au&2) {printf("\nPatch Already Installed\n");return(5);}
if (au&1) {printf("\nPatch Already Installed - Uninstalling\n");goto uninst;}
#endif

printf("\nPatch Already Installed - Uninstall (Y/N) ? (N) ");read(0,&i,4);
if ((i&0xdf)-'Y') return(1);
uninst: _close(f);_close(f2);
if (exist&8) {
if (unlink(v3name)) printf("Cannot Remove VMM32 File\n");
else if (rename(v3back,v3name)) printf("Cannot Rename Backup VMM32 File\n");
exist&=0xfff0;
}
if (exist&0x80) {
if (unlink(vname)) printf("Cannot Remove VMM File\n");
else if (rename(vback,vname)) printf("Cannot Rename Backup VMM File\n");
exist&=0xff0f;
}
if (exist&0x800) {
if (unlink(cname)) printf("Cannot Remove VCACHE File\n");
else if (rename(cback,cname)) printf("Cannot Rename Backup VCACHE File\n");
exist&=0xf0ff;
}
if ((exist&7)==7) {
f=_open(v3back,0);
if (f<0) {printf("Error Opening %s\n",v3back);return(20);}
if (unlink(v3name)) {printf("Cannot Remove Patched VMM32 File\n");return(20);}
_close(f);
if (rename(v3back,v3name)) {printf("Cannot Rename VMM32 Backup\n");return(20);}
}
if ((exist&0x70)==0x70) {
z=0;
f=_open(vname,0);
if (f<0) {printf("Cannot Open VMM File\n");return(20);}
if (_read(f,b,64)<64) {printf("Error Reading VMM Header\n");goto unvm;}
z= *(long *)(b+0x3c);
lseek(f,z-4,0);
if (_read(f,b,4)<4) {printf("Error Reading VMM Patch Flag\n");goto unvm;}
z= *(long *)b;
unvm: _close(f);
f=_open(vback,0);
if (f<0) {printf("Error Opening %s\n",vback);return(20);}
if (unlink(vname)) {printf("Cannot Remove Patched VMM File\n");return(20);}
_close(f);
if (z&0x10000000) {
if (unlink(vback)) {printf("Cannot Remove VMM Backup\n");return(20);}
}
else {
if (rename(vback,vname)) {printf("Cannot Rename VMM Backup\n");return(20);}
}
}
if ((exist&0x700)==0x700) {
z=0;
f=_open(cname,0);
if (f<0) {printf("Cannot Open VCACHE File\n");return(20);}
if (_read(f,b,64)<64) {printf("Error Reading VCACHE Header\n");goto unvc;}
z= *(long *)(b+0x3c);
lseek(f,z-4,0);
if (_read(f,b,4)<4) {printf("Error Reading VCACHE Patch Flag\n");goto unvc;}
z= *(long *)b;
unvc: _close(f);
f=_open(cback,0);
if (f<0) {printf("Error Opening %s\n",cback);return(20);}
if (unlink(cname)) {printf("Cannot Remove Patched VCACHE File\n");return(20);}
_close(f);
if (z&0x10000000) {
if (unlink(cback)) {printf("Cannot Remove VCACHE Backup\n");return(20);}
}
else {
if (rename(cback,cname)) {printf("Cannot Rename VCACHE Backup\n");return(20);}
}
}
if (un) printf("\nUninstall Completed\n\n");
return(0);
inst: un=0;reset();
if (exist&1) {
f=_open(v3name,0);
if (f<0) {printf("Cannot Open %s\n",v3name);return(20);}
i=procv(f,0x20);
switch(i) {
case 5: rel=comp98;break;
case 6: rel=compme;break;
default: printf("Unknown, Invalid or Uncompressed VMM32 File\n");return(20);
};
if (((exist&0x70)==0x40) || ((exist&0x700)==0x400)) {
lseek(f,0L,0);
if (_read(f,b,64)<64) goto bad;
cbase= *(long *)(b+0x3c);x=lseek(f,0L,2);lseek(f,cbase,0);
if (_read(f,b,16)<16) goto bad;
i= *(int *)(b+4);
if (i-0x2000) goto bad;
n= *(int *)(b+6);np= -1;
if (n>1022) goto bad;
table[n]=x;table[n+1]=0;i=n<<2;
if (_read(f,table,i)<i) goto bad;
if (readx(cbase,b,8192)<1) {printf("Decompression Error\n");return(20);}
i= *(int *)b;
if (i-0x3357) goto bad;
i=b[0x470];
switch(i&255) {
case 0x5f: break;
case 0xa8: /* t|=1; */ break;
case 0x64: /* t|=2; */ break;
default: goto bad;
};
memcpy(header,b,1024);
if (header[4]-0x204d4d56) {printf("Unexpected VMM32 Format\n");return(20);}
if ((exist&0x70)==0x40) {
f2=_creat(vname,0);
if (f2<0) {printf("Cannot Create New VMM File\n");return(20);}
lseek(f,0L,0);
if (_read(f,b,64)<64) goto badvmr;
(*(long *)(b+0x3c))+=0x400;
if (_write(f2,b,64)<64) goto badvmw;
y=cbase-64;
while(y) {
i=y;
if (y>0x4000) i=0x4000;
if (_read(f,b,i)<i) goto badvmr;
if (_write(f2,b,i)<i) goto badvmw;
y-=i;
}
x=cbase;
if (readx(x,b,0x484)<1) goto badvcr;
y= *(long *)(b+0x414);z= *(long *)(b+0x42c);z=(4096-z)&4095;y=(y<<12)-z;
y+= *(long *)(b+0x480) - cbase;
for (i=32;i<1024;i++) b[i]=0;
b[4]=1;i=0x484;goto vmp;
while(y) {
i=y;
if (y>0x4000) i=0x4000;
if (readx(x,b,i)<1) goto badvmr;
vmp: if (_write(f2,b,i)<i) goto badvmw;
y-=i;x+=i;
}
_close(f2);
vmmflag|=0x10;exist|=0x10;printf("VMM File Extracted\n");
}
if ((exist&0x700)==0x400) {
for (i=4;i<256;i+=4) {
if ((header[i]==0x43414356) && (header[i+1]==0x20204548)) goto vcok;
}
printf("VCACHE Module Not in VMM32 File\n");return(20);
vcok: f2=_creat(cname,0);
if (f2<0) {printf("Cannot Create New VCACHE File\n");return(20);}
if (_write(f2,mz,128)<128) goto badvcw;
x=header[i+2];
if (readx(x,b,132)<1) goto badvcr;
y= *(long *)(b+0x14);z= *(long *)(b+0x2c);z=(4096-z)&4095;y=(y<<12)-z;
z= *(long *)(b+0x70);
if (z>0xb80) goto badvcr;
z= *(long *)(b+0x80) - x;
if (z<0xc00) goto badvcr;
if (z>0x4000) goto badvcr;
(*(long *)(b+128))=0xc00;
if (_write(f2,b,132)<132) goto badvcw;
if (readx(x+132,b,0xafc)<1) goto badvcr;
if (_write(f2,b,0xafc)<0xafc) goto badvcw;
x+=z;
while(y) {
i=y;
if (y>0x4000) i=0x4000;
if (readx(x,b,i)<1) goto badvcr;
if (_write(f2,b,i)<i) goto badvcw;
y-=i;x+=i;
}
_close(f2);
vcflag|=0x10;exist|=0x100;printf("VCACHE File Extracted\n");
}
}
_close(f);
}
reset();
if ((exist&0x70)==0x50) {
f=_open(vname,0);
if (f<0) {printf("Cannot Open VMM File\n");return(20);}
i=procv(f,vmmflag);
if ((i-1)&0xfffe) {printf("Unknown, Invalid or Compressed VMM File\n");return(20);}
_close(f);
}
reset();
if ((exist&0x700)==0x500) {
f=_open(cname,0);
if (f<0) {printf("Cannot Open VCACHE File\n");return(20);}
y=maxc;y<<=8;
i=procc(f,vcflag,y);
if (i) {printf("Unknown or Invalid VCACHE File\n");return(20);}
_close(f);
}
if ((exist&7)==5) {
if (rename(v3name,v3back)) {printf("Cannot Rename VMM32 File\n");return(20);}
exist|=8;
f=_open(v3back,0);
if (f<0) {printf("Cannot Open Old VMM32 File\n");goto uninst;}
f2=_creat(v3name,0);
if (f2<0) {printf("Cannot Create New VMM32 File\n");goto uninst;}
exist|=2;
i=patch(f,f2,&listx,&cntx);
if (i) {printf("VMM32 Patch Failed\n");goto uninst;}
_close(f);_close(f2);
printf("VMM32 Patched\n");
exist&=0xfff7;
}
if ((exist&0x70)==0x50) {
if (rename(vname,vback)) {printf("Cannot Rename VMM File\n");goto uninst;}
exist|=80;
f=_open(vback,0);
if (f<0) {printf("Cannot Open Old VMM File\n");goto uninst;}
f2=_creat(vname,0);
if (f2<0) {printf("Cannot Create New VMM File\n");goto uninst;}
exist|=0x20;
i=patch(f,f2,&listv,&cntv);
if (i) {printf("VMM Patch Failed\n");goto uninst;}
_close(f);_close(f2);

#ifdef DEMO
printf("VMM Patched (DEMO)\n");
#else
printf("VMM Patched\n");
#endif

exist&=0xff7f;
}
if ((exist&0x700)==0x500) {
if (rename(cname,cback)) {printf("Cannot Rename VCACHE File\n");goto uninst;}
exist|=0x800;
f=_open(cback,0);
if (f<0) {printf("Cannot Open Old VCACHE File\n");goto uninst;}
f2=_creat(cname,0);
if (f2<0) {printf("Cannot Create New VCACHE File\n");goto uninst;}
exist|=0x200;
i=patch(f,f2,&listc,&cntc);
if (i) {printf("VCACHE Patch Failed\n");goto uninst;}
_close(f);_close(f2);
printf("VCACHE Patched\n");
exist&=0xf7ff;
}

#ifdef DEMO
printf("\nDEMO Patch Installed Successfully - Use for less than 10 Minutes Only\n\n");
#else
printf("\nPatch Installed Successfully\n\n");
#endif

return(0);
bad: printf("Invalid VMM32 File\n");return(20);
badvmr: printf("Invalid VMM32 File\n");_close(f);_close(f2);
if (unlink(vname)) printf("Unable to remove bad VMM File\n");
return(20);
badvmw: printf("Error Writing VMM File\n");_close(f);_close(f2);
if (unlink(vname)) printf("Unable to remove bad VMM File\n");
return(20);
badvcr: printf("Invalid VMM32 File\n");_close(f);_close(f2);
if (unlink(cname)) printf("Unable to remove bad VCACHE File\n");
return(20);
badvcw: printf("Error Writing VCACHE File\n");_close(f);_close(f2);
if (unlink(cname)) printf("Unable to remove bad VCACHE File\n");
return(20);
}
