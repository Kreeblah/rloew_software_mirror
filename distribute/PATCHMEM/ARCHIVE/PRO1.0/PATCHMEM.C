#define PRO

char win98[]={
// 0xfc,0xff,0,0,0,                 
// 4,0,0,0,1,0x52,0x52,0x4c,0x80,
// 0x14,4,0,0,0,                        Skip Past Header
   0x14,0,0,0,0,
1,0,0,0,1,0x3b,0x1b,0,0,0,0,2,0,
0,0,1,0xda,7,0x26,0,0,0,0,5,0,0,0,1,0x24,
0,0,0,0x2c,0xb,0,0,0,0,9,0,0,0,1,0xe4,0,
0,0,0xd8,3,0,0,0xf6,7,0,0,0,0,1,0,0,0,
1,0xf6,0x10,0,0,0,0,1,0,0,0,1,0xf0,0x2f,0,0,
0,0,1,0,0,0,1,0xf0,0xa,0,0,0,0,2,0,0,
0,1,0x2c,3,0x5e,0,0,0,0,2,0,0,0,1,0x1c,0xb2,
0xe,0,0,0,0,1,0,0,0,1,9,0x13,0,0,0,0,
1,0,0,0,1,0x17,0x17,0,0,0,0,1,0,0,0,1,
0xb,0x17,0,0,0,0,1,0,0,0,1,0x7b,0x17,0,0,0,
0,1,0,0,0,1,0xf,0x17,0,0,0,0,1,0,0,0,
1,9,0x17,0,0,0,0,1,0,0,0,1,0xb,0x17,0,0,
0,0,1,0,0,0,1,9,0x17,0,0,0,0,1,0,0,
0,1,0x17,0x17,0,0,0,0,1,0,0,0,1,0x19,0x17,0,
0,0,0,1,0,0,0,1,0x17,0x17,0,0,0,0,1,0,
0,0,1,9,0x17,0,0,0,0,1,0,0,0,1,0xb,0x17,
0,0,0,0,1,0,0,0,1,9,0x17,0,0,0,0,1,
0,0,0,1,9,0x17,0,0,0,0,1,0,0,0,1,0xb,
0x17,0,0,0,0,1,0,0,0,1,9,0x17,0,0,0,0,
1,0,0,0,1,0x37,0x17,0,0,0,0,1,0,0,0,1,
0x3b,0xed,0,0,0,0,0x24,0,0,0,2,0x43,0,0,0,0x44,
0,0,0,0x45,0,0,0,0x46,0,0,0,0x47,0,0,0,0x48,
0,0,0,0x49,0,0,0,0x4a,0,0,0,0x4b,0,0,0,0x28,
0,0,0,0,0x24,0,0,0,3,0x43,0,0,0,0x44,0,0,
0,0x45,0,0,0,0x46,0,0,0,0x47,0,0,0,0x48,0,0,
0,0x49,0,0,0,0x4a,0,0,0,0x4b,0,0,0,0x36,0,0,
0,0,0x24,0,0,0,2,0,0,0x5a,0,0,0,0x5b,0,0,
0,0x5c,0,0,0,0x5d,0,0,0,0x5e,0,0,0,0x5f,0,0,
0,0x60,0,0,0,0x61,0,0,0,0x62,0,0xa9,0,0,0,0,
0xcd,0,0,0,1,0xe,0,0,0,2,0,0,0,6,0,0,
0,6,0,0,0,2,0,0,0,0x1e,0,0,0,6,0,0,
0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,
0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,
0,6,0,0,0,6,0,0,0,6,0,0,0,0xe,0,0,
0,0xc1,0xfc,0,0,0x54,0xfa,0,0,0xa9,0xfb,0,0,0x7f,0xfb,0,
0,0x55,0xfb,0,0,0x36,0xfb,0,0,0x77,0xf9,0,0,0x77,0xf9,0,
0,0xb0,0xed,0,0,0x9d,0x11,0,0,8,0x17,0,0,0xe,0x11,0,
0,0xd4,0x11,0,0,0xf6,0x10,0,0,0xb6,0x1d,0,0,0xe1,0x1c,0,
0,0xc9,0x19,0,0,3,0x32,0,0,0xa4,0x30,0,0,0x37,0x30,0,
0,0x3a,0x32,0,0,0x37,0x33,0,0,0xa,0x3d,0,0,0x26,0x32,0,
0,0x25,0x30,0,0,0xe2,0x33,0,0,0x98,0xc,0,0,0x78,0xc,0,
0,0x32,0xc,0,0,0xc5,9,0,0,0xfe,0x16,0,0,0x14,0x1a,0,
0,0xc7,0x24,0,0,0,2,0xaa,0,0,0x58,0xab,0,0,0xbb,0xad,
0,0,0xd4,0xad,0,0,0x79,0xaf,0,0,0x94,0xaf,0,0,0xa5,0xaf,
0,0,0x97,0xb1,0,0,0x48,0xb2,0,0,0x98,0xec,1,0,0,0,
2,0,0,0,1,0x2c,0x3f,0xdd,3,0,0,0,2,0,0,0,
1,0x2c,0x3f,0xcb,4,0,0,0,2,0,0,0,1,0x14,0x3f,0xf9,
8,0,0,0,2,0,0,0,1,0x14,0x3f,0x77,2,0,0,0,
2,0,0,0,1,0x34,0x3f,0x46,0x28,0,0,0,2,0,0,0,
1,0x14,0x3f,7,0,0,0,0,2,0,0,0,1,0x14,0x3d,0x39,
1,0,0,0,2,0,0,0,1,0x1c,0x3f,0xb,0,0,0,0,
2,0,0,0,1,0x14,0x3f,0x42,0,0,0,0,2,0,0,0,
1,0x3c,0x3f,0x19,0,0,0,0,2,0,0,0,1,0x34,0x3f,0x41,
1,0,0,0,2,0,0,0,1,0x1c,0x3f,0x4e,0,0,0,0,
2,0,0,0,1,0x3c,0x3f,0xb7,8,0,0,0,2,0,0,0,
1,0x14,0x3f,0x13,5,0,0,0,2,0,0,0,1,0x14,0x3f,0xc2,
1,0,0,0,2,0,0,0,1,0x34,0x3f,0xf3,0x17,0,0,0,
2,0,0,0,1,0x1c,0x3f,0x89,0,0,0,0,2,0,0,0,
1,0x14,0x3f,0xb0,1,0,0,0,6,0,0,0,1,0x10,0,0,
0,0x90,0xa6,2,0,0,0,2,1,0,0x1d,0,0,0,0,2,
0,0,0,1,0x14,0x3f,0x65,0,0,0,0,2,0,0,0,1,
0x1c,0x3f,0xf4,1,0,0,0,2,0,0,0,1,0x14,0x3f,0xee,8,
0,0,0,2,0,0,0,1,0x34,0x3f,0xda,0xc,0,0,0,2,
0,0,0,1,0x34,0x3f,0x79,0x11,0,0,0,2,0,0,0,1,
0x34,0x3f,0xc0,4,0,0,0,2,0,0,0,1,0x14,0x3f,0xa4,2,
0,0,0,2,0,0,0,1,0x14,0x3f,0xe,8,0,0,0,2,
0,0,0,1,0x14,0x3f,1,1,0,0,0,2,0,0,0,1,
0x2c,0x3f,0x88,0,0,0,0,2,0,0,0,1,0x1c,0x3f,0x39,6,
0,0,0,2,0,0,0,1,0x14,0x3f,0xa,2,0,0,0,2,
0,0,0,1,0x14,0x3f,0xef,0,0,0,0,2,0,0,0,1,
0x14,0x3f,0x8f,4,0,0,0,0x4a,0,0,0,3,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0xe4,5,0,0,0,2,0,0,0,1,
0x2c,0x3f,0x48,0,0,0,0,2,0,0,0,1,0x2c,0x3f,0x12,0,
0,0,0,2,0,0,0,1,0x2c,0x3f,0x2d,0x21,0,0,0,2,
0,0,0,1,0x2c,0x3f,0x39,0x1a,0,0,0,2,0,0,0,1,
0x14,0x3f,0x3b,0,0,0,0,2,0,0,0,1,0x14,0x3f,0xb4,0x33,
0,0,0,2,0,0,0,1,0x14,0x3f,0x42,0,0,0,0,2,
0,0,0,1,0x14,0x3f,0x4a,0x14,0,0,0,2,0,0,0,1,
0x34,0x3f,0x53,0,0,0,0,2,0,0,0,1,0x34,0x3f,0xa5,0,
0,0,0,2,0,0,0,1,0x34,0x3f,0x59,0,0,0,0,2,
0,0,0,1,0x34,0x3f,0x19,0,0,0,0,2,0,0,0,1,
0x34,0x3f,0x28,0,0,0,0,2,0,0,0,1,0x34,0x3f,0x79,0,
0,0,0,2,0,0,0,1,0x34,0x3f,0x13,0,0,0,0,2,
0,0,0,1,0x34,0x3f,0x99,0,0,0,0,2,0,0,0,1,
0x34,0x3f,0xbc,0x98,0,0,0,6,0,0,0,1,0x14,0x3f,0,0,
0x14,0x3d,0x8a,0xb,0,0,0,2,0,0,0,1,0x34,0x3f,0x6a,1,
0,0,0,2,0,0,0,1,0x14,0x3f,0x35,2,0,0,0,2,
0,0,0,1,0x3c,0x3f,0xb,0,0,0,0,2,0,0,0,1,
0x1c,0x3f,0x13,0,0,0,0,2,0,0,0,1,0x3c,0x3f,0xf,0,
0,0,0,2,0,0,0,1,0x1c,0x3f,0x4b,0x14,0,0,0,2,
0,0,0,1,0x1c,0x3f,0xe,0,0,0,0,2,0,0,0,1,
0x3c,0x3f,0xf,0,0,0,0,2,0,0,0,1,0x1c,0x3f,0x19,0,
0,0,0,2,0,0,0,1,0x3c,0x3f,0xaf,0x3d,0,0,0,2,
0,0,0,1,0x14,0x3f,0x5f,0,0,0,0,2,0,0,0,1,
0x14,0x3f,8,0,0,0,0,2,0,0,0,1,0x14,0x3f,0xc0,2,
0,0,0,2,0,0,0,1,0x14,0x3f,0xf7,0xd,0,0,0,2,
0,0,0,1,0x14,0x3f,0x83,0,0,0,0,2,0,0,0,1,
0x14,0x3f,0x8e,1,0,0,0,2,0,0,0,1,0x14,0x3f,0xf2,0,
0,0,0,2,0,0,0,1,0x34,0x3f,0xa3,0xb6,0,0,0,2,
0,0,0,1,0x14,0x3f,0xab,3,0,0,0,2,0,0,0,1,
0x1c,0x3f,0xa3,3,0,0,0,2,0,0,0,1,0x1c,0x3f,0x90,0,
0,0,0,2,0,0,0,1,0xa4,6,5,0,0,0,0,2,
0,0,0,1,0xa4,6,0x23,1,0,0,0,2,0,0,0,1,
0x30,0xc3,6,0,0,0,0,2,0,0,0,1,0x30,0xc3,0x27,0,
0,0,0,3,0,0,0,1,0x90,0xa6,1,0x3f,0,0,0,0,
2,0,0,0,1,0x14,0x3f,0x6b,0,0,0,0,2,0,0,0,
1,0x14,0x3f,0x26,0,0,0,0,2,0,0,0,1,0x14,0x3f,0x2e,
0,0,0,0,2,0,0,0,1,0x14,0x3f,0x35,0,0,0,0,
2,0,0,0,1,0x14,0x3f,0x2c,0,0,0,0,2,0,0,0,
1,0x14,0x3f,0x37,1,0,0,0,1,0,0,0,1,0xc,0x3e,0,
0,0,0,1,0,0,0,1,0xc0,0x73,0,0,0,0,2,0,
0,0,1,0x14,0x3f,0x12,0,0,0,0,2,0,0,0,1,0x14,
0x3f,0x87,2,0,0,0,2,0,0,0,1,0x14,0x3f,0x16,0,0,
0,0,2,0,0,0,1,0x14,0x3f,0x2f,0,0,0,0,2,0,
0,0,1,0x14,0x3f,0xdb,0,0,0,0,1,0,0,0,1,0x80,
0x19,0,0,0,0,1,0,0,0,1,0x80,0x50,2,0,0,0,
2,0,0,0,1,0x14,0x3f,0x38,0,0,0,0,1,0,0,0,
1,0x24,0xbe,0x21,0,0,0,2,0,0,0,1,0x34,0x3f,0x6f,3,
0,0,0,2,0,0,0,1,0x34,0x3f,0x54,0,0,0,0,2,
0,0,0,1,0x34,0x3f,0x4f,0xf5,0,0,0,0,0x90,0,0,4,
0,0,0,0,0xdf,0x12,0,0,0,2,0,0,0,1,0x34,0x3f,
0xaa,0xbd,0,0,0,2,0,0,0,1,0x34,0x3f,0xc7,0x2e,0,0,
0,2,0,0,0,1,0x14,0x3f,0x1d,6,0,0,0,2,0,0,
0,1,0x14,0x3f,0xb2,0x3f,0,0,0,2,0,0,0,1,0x14,0x3f,
0xa0,1,0,0,0,2,0,0,0,1,0x14,0x3f,0xfd,0,0,0,
0,2,0,0,0,1,0x14,0x3f,0x88,0,0,0,0,2,0,0,
0,1,0x2c,0x3f,9,0,0,0,0,2,0,0,0,1,0x2c,0x3f,
0x6c,0,0,0,0,2,0,0,0,1,0x2c,0x3f,0xc8,0,0,0,
0,2,0,0,0,1,0x2c,0x3f,0xfb,3,0,0,0,2,0,0,
0,1,0x1c,0x3f,0x2c,0,0,0,0,2,0,0,0,1,0x1c,0x3f,
0xb7,0x45,0,0,0,2,0,0,0,1,0x14,0x3f,0x2d,0,0,0,
0,2,0,0,0,1,0x14,0x3f,0xfa,5,0,0,0,2,0,0,
0,1,0x14,0x3f,0x29,1,0,0,0,2,0,0,0,1,0x14,0x3f,
0xe4,0x17,0,0,0,2,0,0,0,1,0x14,0x3f,0x98,0,0,0,
0,2,0,0,0,1,0x14,0x3f,0x95,0,0,0,0,2,0,0,
0,1,0x14,0x3f,0x66,0,0,0,0,2,0,0,0,1,0x14,0x3f,
0xb0,0x4d,0,0,0,0,0,0,0,-1
};
char winse[]={
// 0xfc,0xff,0,0,0,
// 4,0,0,0,1,0x52,0x52,0x4c,0x81,
// 0x14,4,0,0,0,                        Skip Past Header
   0x14,0,0,0,0,
1,0,0,0,1,0x3b,0x1b,0,0,0,0,1,0,
0,0,1,0x2a,0x27,0,0,0,0,5,0,0,0,1,0x24,0,
0,0,0x2c,0xb,0,0,0,0,9,0,0,0,1,0xe4,0,0,
0,0xd8,3,0,0,0x5a,7,0,0,0,0,1,0,0,0,1,
0x5a,0x10,0,0,0,0,1,0,0,0,1,0xf0,0x2f,0,0,0,
0,1,0,0,0,1,0xf0,0xa,0,0,0,0,2,0,0,0,
1,0x2c,1,0x5e,0,0,0,0,2,0,0,0,1,0x1c,0xb2,0xe,
0,0,0,0,1,0,0,0,1,9,0x13,0,0,0,0,1,
0,0,0,1,0x17,0x17,0,0,0,0,1,0,0,0,1,0xb,
0x17,0,0,0,0,1,0,0,0,1,0x7b,0x17,0,0,0,0,
1,0,0,0,1,0xf,0x17,0,0,0,0,1,0,0,0,1,
9,0x17,0,0,0,0,1,0,0,0,1,0xb,0x17,0,0,0,
0,1,0,0,0,1,9,0x17,0,0,0,0,1,0,0,0,
1,0x17,0x17,0,0,0,0,1,0,0,0,1,0x19,0x17,0,0,
0,0,1,0,0,0,1,0x17,0x17,0,0,0,0,1,0,0,
0,1,9,0x17,0,0,0,0,1,0,0,0,1,0xb,0x17,0,
0,0,0,1,0,0,0,1,9,0x17,0,0,0,0,1,0,
0,0,1,9,0x17,0,0,0,0,1,0,0,0,1,0xb,0x17,
0,0,0,0,1,0,0,0,1,9,0x17,0,0,0,0,1,
0,0,0,1,0x37,0x17,0,0,0,0,1,0,0,0,1,0x3b,
0xed,0,0,0,0,0x24,0,0,0,2,0x43,0,0,0,0x44,0,
0,0,0x45,0,0,0,0x46,0,0,0,0x47,0,0,0,0x48,0,
0,0,0x49,0,0,0,0x4a,0,0,0,0x4b,0,0,0,0x28,0,
0,0,0,0x24,0,0,0,3,0x43,0,0,0,0x44,0,0,0,
0x45,0,0,0,0x46,0,0,0,0x47,0,0,0,0x48,0,0,0,
0x49,0,0,0,0x4a,0,0,0,0x4b,0,0,0,0x36,0,0,0,
0,0x24,0,0,0,2,0,0,0x5a,0,0,0,0x5b,0,0,0,
0x5c,0,0,0,0x5d,0,0,0,0x5e,0,0,0,0x5f,0,0,0,
0x60,0,0,0,0x61,0,0,0,0x62,0,0xa9,0,0,0,0,0xcd,
0,0,0,1,2,0,0,0,2,0,0,0,6,0,0,0,
6,0,0,0,2,0,0,0,0xe,0,0,0,6,0,0,0,
6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,
6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,
6,0,0,0,6,0,0,0,6,0,0,0,0x1e,0,0,0,
0xc1,0xfc,0,0,0x54,0xfa,0,0,0xf9,0xfb,0,0,0x8f,0xfb,0,0,
0x55,0xfb,0,0,0x76,0xfb,0,0,0xb7,0xf9,0,0,0xb7,0xf9,0,0,
0xab,0xee,0,0,0xef,0x11,0,0,0x7a,0x17,0,0,0x98,0x11,0,0,
0xd2,0x11,0,0,0x28,0x10,0,0,6,0x1d,0,0,0xc3,0x1c,0,0,
0xf5,0x19,0,0,0xfb,0x31,0,0,0xa9,0x30,0,0,0x18,0x30,0,0,
0x19,0x32,0,0,6,0x33,0,0,0x29,0x3d,0,0,0x29,0x32,0,0,
0x32,0x30,0,0,0x9d,0x30,0,0,0x92,0xf,0,0,0x98,0xc,0,0,
0x32,0xc,0,0,0x43,9,0,0,0x6a,0x16,0,0,0x14,0x1a,0,0,
0x45,0x24,0,0,0,2,0xaa,0,0,0xa1,0xab,0,0,4,0xae,0,
0,0x1d,0xae,0,0,0xc2,0xaf,0,0,0xdd,0xaf,0,0,0xee,0xaf,0,
0,0xe0,0xb1,0,0,0x91,0xb2,0,0,0xe1,0xe2,1,0,0,0,2,
0,0,0,1,0x2c,0x3d,0x17,4,0,0,0,2,0,0,0,1,
0x2c,0x3d,0x5b,4,0,0,0,2,0,0,0,1,0x14,0x3d,0xeb,8,
0,0,0,2,0,0,0,1,0x14,0x3d,0xd9,2,0,0,0,2,
0,0,0,1,0x34,0x3d,0xe7,0x27,0,0,0,2,0,0,0,1,
0x14,0x3d,7,0,0,0,0,2,0,0,0,1,0x14,0x3d,0x4a,1,
0,0,0,2,0,0,0,1,0x1c,0x3d,0xb,0,0,0,0,2,
0,0,0,1,0x14,0x3d,0x47,0,0,0,0,2,0,0,0,1,
0x3c,0x3d,0xb,0,0,0,0,2,0,0,0,1,0x34,0x3d,0x34,1,
0,0,0,2,0,0,0,1,0x1c,0x3d,0x61,0,0,0,0,2,
0,0,0,1,0x3c,0x3d,0xc7,8,0,0,0,2,0,0,0,1,
0x14,0x3d,0x2e,5,0,0,0,2,0,0,0,1,0x14,0x3d,0x8a,1,
0,0,0,2,0,0,0,1,0x34,0x3d,6,0x18,0,0,0,2,
0,0,0,1,0x1c,0x3d,0x95,0,0,0,0,2,0,0,0,1,
0x14,0x3d,0xa5,1,0,0,0,6,0,0,0,1,0x10,0,0,0,
0x90,0xa6,2,0,0,0,2,1,0,0x2f,0,0,0,0,2,0,
0,0,1,0x14,0x3d,0x6e,0,0,0,0,2,0,0,0,1,0x1c,
0x3d,0xa7,1,0,0,0,2,0,0,0,1,0x14,0x3d,4,9,0,
0,0,2,0,0,0,1,0x34,0x3d,0x12,0xd,0,0,0,2,0,
0,0,1,0x34,0x3d,0xdd,0x11,0,0,0,2,0,0,0,1,0x34,
0x3d,0x77,4,0,0,0,2,0,0,0,1,0x14,0x3d,0xce,2,0,
0,0,2,0,0,0,1,0x14,0x3d,0x3c,8,0,0,0,2,0,
0,0,1,0x14,0x3d,5,1,0,0,0,2,0,0,0,1,0x2c,
0x3d,0x78,0,0,0,0,2,0,0,0,1,0x1c,0x3d,0x17,6,0,
0,0,2,0,0,0,1,0x14,0x3d,0x2d,2,0,0,0,2,0,
0,0,1,0x14,0x3d,0xf1,0,0,0,0,2,0,0,0,1,0x14,
0x3d,0x3f,4,0,0,0,0x4a,0,0,0,3,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0xe4,5,0,0,0,2,0,0,0,1,0x2c,
0x3d,0x48,0,0,0,0,2,0,0,0,1,0x2c,0x3d,0x12,0,0,
0,0,2,0,0,0,1,0x2c,0x3d,0x2d,0x21,0,0,0,2,0,
0,0,1,0x2c,0x3d,0x39,0x1a,0,0,0,2,0,0,0,1,0x14,
0x3d,0x3b,0,0,0,0,2,0,0,0,1,0x14,0x3d,0xe4,0x33,0,
0,0,2,0,0,0,1,0x14,0x3d,0x42,0,0,0,0,2,0,
0,0,1,0x14,0x3d,0x4a,0x14,0,0,0,2,0,0,0,1,0x34,
0x3d,0x53,0,0,0,0,2,0,0,0,1,0x34,0x3d,0xa5,0,0,
0,0,2,0,0,0,1,0x34,0x3d,0x59,0,0,0,0,2,0,
0,0,1,0x34,0x3d,0x19,0,0,0,0,2,0,0,0,1,0x34,
0x3d,0x28,0,0,0,0,2,0,0,0,1,0x34,0x3d,0x79,0,0,
0,0,2,0,0,0,1,0x34,0x3d,0x13,0,0,0,0,2,0,
0,0,1,0x34,0x3d,0x99,0,0,0,0,2,0,0,0,1,0x34,
0x3d,0x44,0x99,0,0,0,6,0,0,0,1,0x14,0x3d,0,0,0x14,
0x3d,0x82,0xb,0,0,0,2,0,0,0,1,0x34,0x3d,0x6a,1,0,
0,0,2,0,0,0,1,0x14,0x3d,0x35,2,0,0,0,2,0,
0,0,1,0x3c,0x3d,0xb,0,0,0,0,2,0,0,0,1,0x1c,
0x3d,0x13,0,0,0,0,2,0,0,0,1,0x3c,0x3d,0xf,0,0,
0,0,2,0,0,0,1,0x1c,0x3d,0x5b,0x14,0,0,0,2,0,
0,0,1,0x1c,0x3d,0xe,0,0,0,0,2,0,0,0,1,0x3c,
0x3d,0xf,0,0,0,0,2,0,0,0,1,0x1c,0x3d,0x19,0,0,
0,0,2,0,0,0,1,0x3c,0x3d,0xef,0x3c,0,0,0,2,0,
0,0,1,0x14,0x3d,0x5f,0,0,0,0,2,0,0,0,1,0x14,
0x3d,8,0,0,0,0,2,0,0,0,1,0x14,0x3d,0xc0,2,0,
0,0,2,0,0,0,1,0x14,0x3d,0xf7,0xd,0,0,0,2,0,
0,0,1,0x14,0x3d,0x83,0,0,0,0,2,0,0,0,1,0x14,
0x3d,0x8e,1,0,0,0,2,0,0,0,1,0x14,0x3d,0xf2,0,0,
0,0,2,0,0,0,1,0x34,0x3d,0xa3,0xb6,0,0,0,2,0,
0,0,1,0x14,0x3d,0xab,3,0,0,0,2,0,0,0,1,0x1c,
0x3d,0xa3,3,0,0,0,2,0,0,0,1,0x1c,0x3d,0x90,0,0,
0,0,2,0,0,0,1,0xa4,6,5,0,0,0,0,2,0,
0,0,1,0xa4,6,0x23,1,0,0,0,2,0,0,0,1,0x30,
0xc3,6,0,0,0,0,2,0,0,0,1,0x30,0xc3,0x27,0,0,
0,0,3,0,0,0,1,0x90,0xa6,1,0x3f,0,0,0,0,2,
0,0,0,1,0x14,0x3d,0x6b,0,0,0,0,2,0,0,0,1,
0x14,0x3d,0x26,0,0,0,0,2,0,0,0,1,0x14,0x3d,0x2e,0,
0,0,0,2,0,0,0,1,0x14,0x3d,0x35,0,0,0,0,2,
0,0,0,1,0x14,0x3d,0x2c,0,0,0,0,2,0,0,0,1,
0x14,0x3d,0x35,1,0,0,0,1,0,0,0,1,0xc,0x3e,0,0,
0,0,1,0,0,0,1,0xc0,0x73,0,0,0,0,2,0,0,
0,1,0x14,0x3d,0x12,0,0,0,0,2,0,0,0,1,0x14,0x3d,
0x89,2,0,0,0,2,0,0,0,1,0x14,0x3d,0x16,0,0,0,
0,2,0,0,0,1,0x14,0x3d,0x2f,0,0,0,0,2,0,0,
0,1,0x14,0x3d,0xdb,0,0,0,0,1,0,0,0,1,0x80,0x19,
0,0,0,0,1,0,0,0,1,0x80,0x50,2,0,0,0,2,
0,0,0,1,0x14,0x3d,0x38,0,0,0,0,1,0,0,0,1,
0x24,0xbe,0x21,0,0,0,2,0,0,0,1,0x34,0x3d,0x6f,3,0,
0,0,2,0,0,0,1,0x34,0x3d,0x54,0,0,0,0,2,0,
0,0,1,0x34,0x3d,0x4f,0xf5,0,0,0,0,0x90,0,0,4,0,
0,0,0,0xdf,0x12,0,0,0,2,0,0,0,1,0x34,0x3d,0xaa,
0xbd,0,0,0,2,0,0,0,1,0x34,0x3d,0xf7,0x2e,0,0,0,
2,0,0,0,1,0x14,0x3d,0x1d,6,0,0,0,2,0,0,0,
1,0x14,0x3d,0x82,0x3f,0,0,0,2,0,0,0,1,0x14,0x3d,0xa0,
1,0,0,0,2,0,0,0,1,0x14,0x3d,0xfd,0,0,0,0,
2,0,0,0,1,0x14,0x3d,0x88,0,0,0,0,2,0,0,0,
1,0x2c,0x3d,9,0,0,0,0,2,0,0,0,1,0x2c,0x3d,0x6c,
0,0,0,0,2,0,0,0,1,0x2c,0x3d,0xc8,0,0,0,0,
2,0,0,0,1,0x2c,0x3d,0xfb,3,0,0,0,2,0,0,0,
1,0x1c,0x3d,0x2c,0,0,0,0,2,0,0,0,1,0x1c,0x3d,0xb7,
0x45,0,0,0,2,0,0,0,1,0x14,0x3d,0x2d,0,0,0,0,
2,0,0,0,1,0x14,0x3d,0xfa,5,0,0,0,2,0,0,0,
1,0x14,0x3d,0x29,1,0,0,0,2,0,0,0,1,0x14,0x3d,0xe4,
0x17,0,0,0,2,0,0,0,1,0x14,0x3d,0x98,0,0,0,0,
2,0,0,0,1,0x14,0x3d,0x95,0,0,0,0,2,0,0,0,
1,0x14,0x3d,0x66,0,0,0,0,2,0,0,0,1,0x14,0x3d,0xb0,
0x4d,0,0,0,0,0,0,0,-1
};

char *winx;

#ifdef SELF
char cr[]="                Windows 98 RAM Limitation Patch 1.0  Copyright (C) 2007 by Rudolph R. Loew. All Rights Reserved.            ";
#endif

#ifdef PRO
char cr[]="                Windows 98 RAM Limitation Patch 1.0  Copyright (C) 2007 by Rudolph R. Loew. All Rights Reserved.  €€€€€€€€  ";
#endif

#ifdef DEMO
char cr[]="                Windows 98 RAM Limitation Patch 1.0  (DEMO)  Copyright (C) 2007 by Rudolph R. Loew. All Rights Reserved.    ";
char dem[]={0xd,3,2,0,0,0x25,-1,-1,0x3f,0,0xc3};
#endif

#define relincr 0x4a
#define expand 0x9000

char subr[2796];

int rel[]={
0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x26,
0x2e,0x33,0x38,0x56,0x6e,0x77,0x7c,0x86,
0xad,0xa6d,0xa88,0xac3,0xacd,0xad8,0xae0,0
};

char vname[256],hname[256],vback[256],hback[256],wname[256],*b;
int f,f2,n,np;
long base,no,table[1024],header[256],lseek();

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
*(long *)(subr+2792)=0xcbf53de8;  // 0xe8,0x3d,0xf5,0xcb   call $-0xaco  retf
i=0;j=(int)(&subr);k=(int)(&l);
while(rel[i]) {(*(int *)(subr+rel[i]))+=j-0x3ea2;i++;}
rel[0]=0;j+=0xae8;
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

int readx(b1,l)
char *b1;
int l;
{
int i,j;
long x;
i=l;
while(i) {
if (no<8192) {
j=8192-no;
if (j>i) j=i;
memcpy(b1,b+0x4000+no,j);no+=j;i-=j;b1+=j;
}
else {
np++;no=0;x=table[np+1]-table[np];
if ((x<0) || (x>8192)) return(0);
lseek(f,table[np],0);
if (x==8192) {
if (_read(f,b+0x4000,8192)<8192) return(0);
}
else {
j=x;
if (_read(f,b+0x6000,j)<j) return(0);
if (uncomp(b+0x6000,b+0x4000)-8192) return(0);
}
}
}
return(l);
}

int ready(b1,l)
char *b1;
int l;
{
memcpy(b1,winx,l);winx+=l;return(l);
}

char *dmake(b1)
char *b1;
{
unsigned long i,j,k;
char *b2,z[5];
b2=b1+8192;
lp: i=ready(z,5);
if (i-5) goto derr;
i= *(unsigned long *)z;
switch(z[4]) {
case -1: return(0);
case 0: while(i>0) {
        j=i;
        if (j>8192) j=8192;
        if (readx(b1,j)<j) goto rerr;
        if (_write(f2,b1,j)<j) goto werr;
        i-=j;
        }
        goto lp;
case 1: while(i>0) {
        k=i;
        if (k>8192) k=8192;
        if (readx(b1,k)<k) goto rerr;
        if (ready(b2,k)<k) goto derr;
        for (j=0;j<k;j++) b1[j]^=b2[j];
        if (_write(f2,b1,k)<k) goto werr;
        i-=k;
        }
        goto lp;
case 2: while(i>0) {
        j=i;
        if (j>8192) j=8192;
        if (ready(b2,j)<j) goto derr;
        if (_write(f2,b2,j)<j) goto werr;
        i-=j;
        }
        goto lp;
case 3: while(i>0) {
        k=i;
        if (k>8192) k=8192;
        if (readx(b1,k)<k) goto rerr;
        if (ready(b2,k)<k) goto derr;
        for (j=0;j<k;j++) if (b1[j]-b2[j]) return("Corrupted File");
        i-=k;
        }
        goto lp;
case 4: if (ready(b2,4)<4) goto rerr;
        while(i>0) {
        k=i;
        if (k>8192) k=8192;
        for (j=4;j<k;j+=4) *(unsigned long *)(b2+j)= *(unsigned long *)b2;
        if (_write(f2,b2,k)<k) goto werr;
        i-=k;
        }
        goto lp;
case 5: if (ready(b2,4)<4) goto rerr;
        while(i>0) {
        k=i;
        if (k>8192) k=8192;
        if (readx(b1,k)<k) goto rerr;
        for (j=4;j<k;j+=4) *(unsigned long *)(b2+j)= *(unsigned long *)b2;
        for (j=0;j<k;j++) if (b1[j]-b2[j]) return("Corrupted File");
        i-=k;
        }
        goto lp;
default: return("Unknown Block");
};
rerr: return("Source Too Short");
derr: return("Error in Update Data");
werr: return("Error Writing Dest");
}

main(c,v)
int c;
char **v;
{
int i,j,k,l,p,t,h;
long x,y,z;
char *a;

#ifdef DEMO
if ((c& -2)==2) {printf("PATCHM [VMM32File HimemFile WinInitFile]\n");return(20);}
printf("\nWindows 98 and 98SE RAM Limitation Patch  (DEMO) Version 1.0\nCopyright (C) 2007 by Rudolph R. Loew. All Rights Reserved.\n\n");
#else
if ((c& -2)==2) {printf("PATCHMEM [VMM32File HimemFile WinInitFile]\n");return(20);}
printf("\nWindows 98 and 98SE RAM Limitation Patch  Version 1.0\nCopyright (C) 2007 by Rudolph R. Loew. All Rights Reserved.\n\n");
#endif

b=(char *)malloc(32767);
if (b==0) {printf("Not Enough Memory\n");return(20);}
vname[0]=hname[0]=wname[0]=0;
if (c>2) {
if (v[1][0]-'-') strcpy(vname,v[1]);
if (v[2][0]-'-') strcpy(hname,v[2]);
if (v[3][0]-'-') strcpy(wname,v[3]);
}
if ((vname[0]==0) || (hname[0]==0) || (wname[0]==0)) {
f=_open("C:\\MSDOS.SYS",0);
if (f<0) {printf("Cannot Open C:\\MSDOS.SYS\n");return(20);}
while((i=rl(f,b))>0) if (i>9) {
if (b[6]=='=') b[6]=0;
if (stricmp(b,"WINDIR")==0) {
if (vname[0]==0) strcpy(vname,(char *)b+7);
if (wname[0]==0) strcpy(wname,(char *)b+7);
}
if (i>13) {
if (b[10]=='=') b[10]=0;
if (hname[0]==0) if (stricmp(b,"WINBOOTDIR")==0) strcpy(hname,(char *)b+11);
}
}
_close(f);
if ((vname[0]==0) || (wname[0]==0)) {printf("Cannot Locate Windows Directory\n");return(20);}
if (hname[0]==0) {printf("Cannot Locate Windows Boot Directory\n");return(20);}
strcat(vname,"\\SYSTEM\\VMM32.VXD");strcat(hname,"\\HIMEM.SYS");
strcat(wname,"\\WININIT.INI");
}
strcpy(vback,vname);i=strlen(vback);k=l= -1;
for (j=0;j<i;j++) {
if (vback[j]=='.') k=j;
if (vback[j]=='\\') {k= -1;l=j;}
}
if (k<0) strcat(vback,".BAK");
else strcpy(vback+k+1,"BAK");
if (strlen(vback)>(l+13)) {printf("Invalid VMM32 Name\n");return(20);}
strcpy(hback,hname);i=strlen(hback);k=l= -1;
for (j=0;j<i;j++) {
if (hback[j]=='.') k=j;
if (hback[j]=='\\') {k= -1;l=j;}
}
if (k<0) strcat(hback,".BAK");
else strcpy(hback+k+1,"BAK");
if (strlen(hback)>(l+13)) {printf("Invalid HIMEM Name\n");return(20);}
if (stricmp(vname,vback)==0) {printf("VMM32 Name Conflicts with Backup Name\n");return(20);}
if (stricmp(hname,hback)==0) {printf("HIMEM Name Conflicts with Backup Name\n");return(20);}
f=_open(hname,0);
if (f<0) {printf("Cannot Open %s\n",hname);return(20);}
lseek(f,0x6992L,0);
if (_read(f,b,1)<1) {printf("Invalid HIMEM File\n");return(20);}
switch(b[0]) {
case 0x30: h=0;break;
case 0x50: h=1;break;
default: printf("Unrecognized HIMEM File\n");return(20);
};
_close(f);
f=_open(vname,0);
if (f<0) {printf("Cannot Open %s\n",vname);return(20);}
i=_read(f,b,0x6000);
if (i<0x4c00) goto bad;
if ((*(long *)(b+0x40ca))-0x2e061e60) goto bad;
memcpy(subr,b+0x40a2,2792);base= *(long *)(b+0x3c);
lseek(f,base-4,0);
if (_read(f,b,4)<4) goto bad;
x= *(long *)b;t=(x>>24)&255;
if (x==0) goto new;
if ((x&0xffffff)-0x4c5252) goto bad;
if (x>0) {printf("Cannot Uninstall Update Installed Before Combining\n");return(20);}
_close(f);
if (h) printf("Update Already Installed");
else printf("Update Partially Installed");
printf(" - Uninstall (Y/N) ? (N) ");read(0,b,4);
if ((b[0]&0xdf)-'Y') return(1);
f=_open(vback,0);
if (f<0) {printf("Cannot Open %s\n",vback);return(20);}
if (unlink(vname)) {printf("Cannot Remove VMM32 File\n");return(20);}
_close(f);
if (rename(vback,vname)) {printf("Cannot Rename VMM32 Backup\n");return(20);}
if (h) {
f=_open(hback,0);
if (f<0) {printf("Cannot Open %s\n",hback);return(20);}
if (unlink(hname)) {printf("Cannot Remove HIMEM File\n");return(20);}
_close(f);
if (rename(hback,hname)) {printf("Cannot Rename HIMEM Backup\n");return(20);}
}
f=_open(wname,0);
if (f>=0) {
_close(f);
if (unlink(wname)) {printf("Cannot Remove WININIT File\n");return(20);}
}
if (t&0x40) printf("Demo ");
printf("Update Uninstalled\n\n");return(0);

new: f2=_open(wname,0);
if (f2>=0) {printf("WININIT File Exists - Execute WININIT.EXE before Updating\n");return(20);}
x=lseek(f,0L,2);lseek(f,base,0);
if (_read(f,b,16)<16) goto bad;
i= *(int *)b;
if (i-0x3457) {printf("Not Compressed VMM32 File\n");return(20);}
i= *(int *)(b+4);
if (i-0x2000) goto bad;
n= *(int *)(b+6);np= -1;no=8192;
if (n>1022) goto bad;
table[n]=x;table[n+1]=0;i=n<<2;
if (_read(f,table,i)<i) goto bad;
i=table[1]-table[0];
if (_read(f,b+0x2000,i)<i) goto bad;
if (uncomp(b+0x2000,b)-8192) {printf("Decompression Error\n");return(20);}
i= *(int *)b;
if (i-0x3357) goto bad;
i=b[0x470];
switch(i&255) {
case 0x5f: winx=win98;break;
case 0xa8: winx=winse;t|=1;break;
default: goto bad;
};
memcpy(header,b,1024);p=header[1];header[7]+=relincr;
for (i=1;i<p;i++) header[(i<<2)+6]+=expand;
unlink(vback);f2=_open(vback,0);
if (f2>=0) {printf("Cannot Remove VMM32 Backup\n");return(20);}
close(f);
if (rename(vname,vback)) {printf("Cannot Rename VMM32 File\n");return(20);}
f=_open(vback,0);
if (f<0) {printf("Cannot Reopen VMM32 File\n");goto undo;}
f2=_creat(vname,0);
if (f2<0) {printf("Cannot Create New VMM32 File\n");goto undo;}
_close(f2);
f2=_open(vname,0x44);
if (f2<0) {printf("Cannot ReOpen New VMM32 File\n");goto undo;}

x=base-128;
while(x) {
i=x;
if (x>0x6000) i=0x6000;
if (_read(f,b,i)<i) goto bad1;
if (_write(f2,b,i)<i) goto werr;
x-=i;
}
if (_read(f,b,128)<128) goto bad1;
if (_write(f2,cr,124)<124) goto werr;
strcpy(b,"RRL");b[3]=0x80+t;

#ifdef DEMO
b[3]|=0x40;
#endif

if (_write(f2,b,4)<4) goto werr;
if (readx(b,1024)<1024) goto bad1;
if (_write(f2,header,1024)<1024) goto werr;
a=dmake(b);
if (a) {printf("VMM32: %s\n",a);goto undo;}

#ifdef DEMO
lseek(f2,0x10524L,0);b[0]=0x10;
if (_write(f2,b,1)<1) goto werr;
lseek(f2,0x40c56L,0);*(long *)b=0x1bba5e8;
if (_write(f2,b,4)<4) goto werr;
lseek(f2,0x5c800L,0);
if (_write(f2,dem,11)<11) goto werr;
lseek(f2,0L,2);
#endif

for (i=1;i<p;i++) {
x=header[(i<<2)+10]-header[(i<<2)+6];
if (readx(b,4096)<4096) goto bad1;
if (x<0) {
x= *(long *)(b+0x14);x<<=12;y= *(long *)(b+0x2c);y=(4096-y)&4095;x-=y;
y=(*(long *)(b+0x80))+expand-header[(i<<2)+6];x+=y;
}
j=4096;z=0;goto cpy;
while(x) {
j=readx(b,4096);
if (j<4096) goto bad1;
cpy: if (z==0) (*(long *)(b+0x80))+=expand;
if ((header[(i<<2)+4]==0x43414356) && (header[(i<<2)+5]==0x20204548)) {
if (z==0x6000) *(int *)(b+0x125)= *(int *)(b+0x12c)= 0x200;
}
if (x<j) j=x;
if (_write(f2,b,j)<j) goto werr;
x-=j;z+=j;
}
}
_close(f);_close(f2);
unlink(hback);f2=_open(hback,0);
if (f2>=0) {printf("Cannot Remove HIMEM Backup\n");return(20);}
close(f);
if (rename(hname,hback)) {printf("Cannot Rename HIMEM File\n");return(20);}
f=_open(hback,0);
if (f<0) {printf("Cannot Reopen HIMEM File\n");goto undo1;}
f2=_creat(hname,0);
if (f2<0) {printf("Cannot Create New HIMEM File\n");goto undo1;}
x=0;
while((i=_read(f,b,0x7000))>0) {
if ((x++)==0) b[0x6992]=0x50;
if (_write(f2,b,i)<i) goto werr1;
}      
_close(f);_close(f2);
f=_creat(wname,0);
if (f<0) {printf("Cannot Create WININIT File\n");return(20);}
if (_write(f,"[CombineVxDs]\r\n=",16)<16) goto werr2;
if ((vname[0]-'\\') && (vname[0]-'.') && (vname[1]-':')) if (_write(f,".\\",2)<2) goto werr2;
if (_write(f,vname,strlen(vname))<strlen(vname)) goto werr2;
if (_write(f,"\r\n\r\n[SetupOptions]\r\nCombine=1\r\n\r\n",33)<33) goto werr2;
_close(f);

#ifdef DEMO
printf("Demo Update Completed - Run Windows in Safe Mode Only\n");
#else
printf("Update Completed\n");
#endif

return(0);
werr2: printf("Error Writing New WININIT File\n");return(20);
werr1: printf("Error Writing New HIMEM File\n");
undo1: _close(f);_close(f2);unlink(hname);
if (rename(hback,hname)) printf("Cannot Rename HIMEM Backup\n");
return(20);
bad1: printf("Invalid VMM32 File\n");goto undo;
werr: printf("Error Writing New VMM32 File\n");
undo: _close(f);_close(f2);unlink(vname);
if (rename(vback,vname)) printf("Cannot Rename VMM32 Backup\n");
return(20);
bad: printf("Invalid VMM32 File\n");return(20);
}
