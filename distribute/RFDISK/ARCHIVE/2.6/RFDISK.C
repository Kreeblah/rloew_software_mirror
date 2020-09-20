/*( getnum parsearg farint13 int13raw )*/

// #define DEMO

#define mod40d 0xff000000

unsigned char mbr[]={
0x33,0xc0,0x8e,0xd0,0xbc,0,0x7c,0xfb,0xfc,0x8e,0xd8,0x8e,0xc0,0xbe,0x1b,0x7c,
0xbf,0x1b,6,0xb9,0xe5,1,0x50,0x57,0xf3,0xa4,0xcb,0xb1,4,0x33,0xed,0xbe,
0xbe,7,0x38,4,0x74,8,0x23,0xed,0x75,0xf,0x8b,0xee,0x8b,0x14,0x83,0xc6,
0x10,0xe2,0xef,0x23,0xed,0x75,9,0xcd,0x18,0x8d,0x36,0x1f,7,0xe9,0x83,0,
0xc7,6,0xfe,0x7d,0x55,0xaa,0x8a,0x46,4,0x33,0xff,0x3c,0xb,0x72,7,0x3c,
0xd,0x73,3,0xbf,6,0,0x3c,0x10,0x73,9,0x8d,0x1e,0xf,7,0xd7,0x22,
0xc0,0x74,0xd6,0x50,0xb4,0x41,0xbb,0xaa,0x55,0xcd,0x13,0x58,0x72,0x61,0x81,0xfb,
0x55,0xaa,0x75,0x5b,0xf6,0xc1,1,0x74,0x56,0x88,0x46,4,0xb9,0x10,0,0x33,
0xc0,0xbb,0,0x7c,0x50,0x50,0xff,0x76,0xa,0xff,0x76,8,0xe,0x53,0x50,0x51,
0x8b,0xf4,0xb8,0,0x42,0xc6,0x44,2,1,0xcd,0x13,0x72,5,0xe8,0x58,0,
0x74,0x52,0x33,0xc0,0xcd,0x13,0x83,0xf9,8,0x75,7,1,0x7c,8,0x83,0x54,
0xa,0,0xe2,0xde,0xe8,0x41,0,0x74,6,0x8d,0x36,0x54,7,0xeb,4,0x8d,
0x36,0x37,7,0xac,0x74,0xfe,0xb4,0xe,0xbb,7,0,0xcd,0x10,0xeb,0xf4,0xbe,
0x10,0,0xbb,0,0x7c,0x8b,0x4e,2,0xb8,1,2,0xcd,0x13,0x72,5,0xe8,
0x16,0,0x74,0x10,0x33,0xc0,0xcd,0x13,0x83,0xfe,8,0x75,2,3,0xcf,0x4e,
0x75,0xe6,0xeb,0xc0,0x8b,0xf5,0xff,0xe3,0x81,0x3e,0xfe,0x7d,0x55,0xaa,0xc3,0,
0x52,0x75,0x64,0x6f,0x6c,0x70,0x68,0x20,0x52,0x2e,0x20,0x4c,0x6f,0x65,0x77,0,
0xe,2,3,0xe,0,0xe,7,8,9,0xa,0xc,0xc,0xd,0xe,0,0x49,
0x6e,0x76,0x61,0x6c,0x69,0x64,0x20,0x50,0x61,0x72,0x74,0x69,0x74,0x69,0x6f,0x6e,
0x20,0x54,0x61,0x62,0x6c,0x65,0,0x44,0x69,0x73,0x6b,0x20,0x45,0x72,0x72,0x6f,
0x72,0x20,0x4c,0x6f,0x61,0x64,0x69,0x6e,0x67,0x20,0x50,0x61,0x72,0x74,0x69,0x74,
0x69,0x6f,0x6e,0,0x50,0x61,0x72,0x74,0x69,0x74,0x69,0x6f,0x6e,0x20,0x4e,0x6f,
0x74,0x20,0x46,0x6f,0x72,0x6d,0x61,0x74,0x74,0x65,0x64,0,0,0,0,0};

#define mbrl  (sizeof(mbr))
#define mbrd  (mbrl-4)

unsigned char mbr2[]={
0xeb,0xa,0xbe,0,0x7e,0xbf,0,0xa,0xeb,0x18,0x52,0x4c,0xfa,0xfc,0xe,0x1f,
0xe,7,0xe,0x17,0xbc,0xfc,7,0x6a,0xd,0xba,0x80,0,0xbe,0,0x7c,0xbf,
0,8,0x57,0xb9,0,1,0xf3,0xa5,0x5e,0xe9,0,0x8c,0x8b,0xc2,5,0xb0,
0xd,0xcd,0x10,0xbd,0x3e,0xe,0xb4,0x12,0xcd,0x16,0x80,0xe4,3,0x75,0x12,0xbb,
0xfa,7,0x80,0x3f,0xd,0x75,0xa,0xb8,0x2d,0xe,0xcd,0x10,0xc6,7,0xd,0xeb,
0x29,0xb8,0x3c,0xe,0xcd,0x10,0x8a,0x84,0xb0,1,0xe8,0x38,1,0x8b,0xc5,0xcd,
0x10,0xb4,0,0xcd,0x16,0xa2,0xfa,7,0x3c,0x3f,0xb4,0xe,0x74,4,0x3c,0x2a,
0x75,4,0x8b,0xe8,0xeb,0xe7,0x3c,0xd,0x75,4,0x8a,0x84,0xb0,1,0x50,0xe8,
0x13,1,0x58,0x3c,0x3f,0x74,0xd6,0x72,2,0x24,0xdf,0x3c,0x2a,0x74,0xe3,0xbb,
0,0x7c,0xb9,2,0,0x80,0xfa,0x80,0x75,0x26,0x60,0x8a,0x8c,0xaf,1,0x22,
0xc9,0x74,0xa,0xe8,0xfa,0,0x72,5,0xff,0xd3,0x4e,0xeb,0xee,0x61,0xeb,0x12,
0x3c,0x20,0x74,0x47,0x80,0x3e,0xfa,7,0xd,0x74,0x57,0xb8,0x3f,0xe,0xeb,0x9f,
0xb7,0xc,0x50,0xe8,0xda,0,0x58,0x72,0xf2,0x80,0xbf,0xfe,1,0,0x74,0xe0,
0x8a,0xa7,0xff,1,0x3c,0x40,0x75,3,0xa2,0xfa,7,0x80,0xfa,0x80,0x74,7,
0x80,0xfc,1,0x75,0xc,0xeb,4,0x3c,0x40,0x74,0x10,0x3a,0x87,0xfe,1,0x74,
0xa,0x22,0xe4,0x75,2,0xfe,0xc4,2,0xcc,0xeb,0xc7,0x81,0xfd,0x3f,0xe,0x74,
6,0x81,0xfd,0x2a,0xe,0x75,7,0x8b,0xdd,0x8a,0xc3,0xa2,0xfa,7,0x88,0x84,
0xb0,1,0x88,0xe,0xfb,7,0x56,0x80,0xfa,0x80,0x75,0x1e,0x22,0xe4,0x75,0x12,
0xbe,0xbe,0xd,0xbb,0,0xc,0xb9,2,0,0xe8,0x74,0,0x73,7,0x5e,0xe9,
0x2b,0xff,0xbe,0xbe,0x7d,0xbf,0xbe,9,0xeb,6,0xbe,0xbe,0xd,0xbf,0xbe,0xb,
0xb9,0x20,0,0xf3,0xa5,0x5e,0x80,0x3e,0xfa,7,0xd,0x74,0xb,0xb8,1,3,
0x8b,0xde,0xb1,1,0xcd,0x13,0x72,0xd7,0xbb,0,0x7e,0x80,0xfa,0x80,0x75,0x15,
0xa0,0xff,0x7d,0x3c,2,0x72,0xe,0xb7,0x7c,0x8a,0xe,0xfb,7,0xb4,2,0xcd,
0x13,0x72,0xbc,0x53,0xc3,0xb1,1,0x42,0xe8,0x25,0,0x72,0x14,0x81,0x3e,0xfe,
0x7f,0x55,0xaa,0x75,0xf0,0x81,0x3e,0xa,0x7e,0x52,0x4c,0x75,0xe8,0x68,2,0x7e,
0xc3,0x68,0,0x7c,0xc3,0xcd,0x10,0xb0,0xd,0xcd,0x10,0xb0,0xa,0xcd,0x10,0xc3,
0xb8,1,2,0xcd,0x13,0xc3,0,0,0,0,0,0,0,0,0,0,
0x3f,0,0x52,0x4c};

#define mbr2len (sizeof(mbr2))
#define mbr2l (mbr2len-4)  // Length of Code + Overlay Table
#define mbr2d 0x1a6        // DateStamp Offset (This Version Only)
#define ovlo  (mbr2d+4)    // Offset of Overlay Table
#define ovll  (mbr2l-ovlo) // Length of Overlay Table

unsigned char dos[]={
0xbe,0,0x7c,0xbf,0,0xa,0xb9,0,1,0xf3,0xa5,0xe9,0,0x8e,0xbb,0xc2,
9,0x8a,7,0x3c,6,0x74,5,0x83,0xc3,0x10,0xeb,0xf5,0xb8,1,2,0x8b,
0x4f,0xfe,0x8b,0x57,0xfc,0xbb,0,0x7c,0xcd,0x13,0xbe,0x38,0xa,0xbf,0x38,0x7c,
0xb9,0xe5,0,0xf3,0xa5,0xe9,0xc8,0x71,0x54,0x31,0x36,0x20,0x20,0x20,0xfa,0x33,
0xc0,0x8e,0xd0,0xbc,0,0x7c,0x16,7,0xbb,0x78,0,0x36,0xc5,0x37,0x1e,0x56,
0x16,0x53,0xbf,0x3e,0x7c,0xb9,0xb,0,0xfc,0xf3,0xa4,6,0x1f,0xc6,0x45,0xfe,
0xf,0x8b,0xe,0x18,0x7c,0x88,0x4d,0xf9,0x89,0x47,2,0xc7,7,0x3e,0x7c,0xfb,
0xcd,0x13,0x72,0x79,0x33,0xc0,0x39,6,0x13,0x7c,0x74,8,0x8b,0xe,0x13,0x7c,
0x89,0xe,0x20,0x7c,0xa0,0x10,0x7c,0xf7,0x26,0x16,0x7c,3,6,0x1c,0x7c,0x13,
0x16,0x1e,0x7c,3,6,0xe,0x7c,0x83,0xd2,0,0xa3,0x50,0x7c,0x89,0x16,0x52,
0x7c,0xa3,0x49,0x7c,0x89,0x16,0x4b,0x7c,0xb8,0x20,0,0xf7,0x26,0x11,0x7c,0x8b,
0x1e,0xb,0x7c,3,0xc3,0x48,0xf7,0xf3,1,6,0x49,0x7c,0x83,0x16,0x4b,0x7c,
0,0xbb,0,5,0x8b,0x16,0x52,0x7c,0xa1,0x50,0x7c,0xe8,0x92,0,0x90,0x90,
0xb0,1,0xe8,0xb1,0,0x72,0x16,0x8b,0xfb,0xb9,0xb,0,0xbe,0xe6,0x7d,0xf3,
0xa6,0x75,0xa,0x8d,0x7f,0x20,0xb9,0xb,0,0xf3,0xa6,0x74,0x18,0xbe,0xa3,0x7d,
0xe8,0x5f,0,0x33,0xc0,0xcd,0x16,0x5e,0x1f,0x8f,4,0x8f,0x44,2,0xcd,0x19,
0x58,0x58,0x58,0xeb,0xe8,0x8b,0x47,0x1a,0x48,0x48,0x8a,0x1e,0xd,0x7c,0x32,0xff,
0xf7,0xe3,3,6,0x49,0x7c,0x13,0x16,0x4b,0x7c,0xbb,0,7,0xb9,3,0,
0x50,0x52,0x51,0xe8,0x3a,0,0x90,0x90,0xb0,1,0xe8,0x59,0,0x59,0x5a,0x58,
0x72,0xbb,5,1,0,0x83,0xd2,0,3,0x1e,0xb,0x7c,0xe2,0xe2,0x8a,0x2e,
0x15,0x7c,0x8a,0x16,0x24,0x7c,0x8b,0x1e,0x49,0x7c,0xa1,0x4b,0x7c,0xea,0,0,
0x70,0,0xac,0xa,0xc0,0x74,0x2e,0xb4,0xe,0xbb,7,0,0xcd,0x10,0xeb,0xf2,
0x51,0x50,0x89,0xd0,0x31,0xd2,0xf7,0x36,0x18,0x7c,0x89,0xc1,0x58,0xf7,0x36,0x18,
0x7c,0xfe,0xc2,0x88,0x16,0x4f,0x7c,0x89,0xca,0x59,0xf7,0x36,0x1a,0x7c,0x88,0x16,
0x25,0x7c,0xa3,0x4d,0x7c,0xc3,0xb4,2,0x8b,0x16,0x4d,0x7c,0xb1,6,0xd2,0xe6,
0xa,0x36,0x4f,0x7c,0x8b,0xca,0x86,0xe9,0x8a,0x16,0x24,0x7c,0x8a,0x36,0x25,0x7c,
0xcd,0x13,0xc3,0xd,0xa,0x4e,0x6f,0x6e,0x2d,0x53,0x79,0x73,0x74,0x65,0x6d,0x20,
0x64,0x69,0x73,0x6b,0x20,0x6f,0x72,0x20,0x65,0x72,0x72,0x6f,0x72,0xd,0xa,0x52,
0x65,0x70,0x6c,0x61,0x63,0x65,0x20,0x61,0x6e,0x64,0x20,0x70,0x72,0x65,0x73,0x73,
0x20,0x61,0x6e,0x79,0x20,0x6b,0x65,0x79,0x20,0x77,0x68,0x65,0x6e,0x20,0x72,0x65,
0x61,0x64,0x79,0xd,0xa,0,0x49,0x4f,0x20,0x20,0x20,0x20,0x20,0x20,0x44,0x4f,
0x53,0x4d,0x53,0x44,0x4f,0x53,0x20,0x20,0x20,0x44,0x4f,0x53,0,0,0x44,0};

unsigned char win[]={
0x33,0xc0,0x8e,0xd0,0xbc,0,0x7c,0xfb,0xfc,0x8e,0xd8,0x8e,0xc0,0xbe,0x1b,0x7c,
0xbf,0x1b,6,0xb9,0xe5,1,0x50,0x57,0xf3,0xa4,0xcb,0xb8,1,2,0xbb,0,
8,0xb9,2,0,0xba,0x80,0,0xcd,0x13,0xf,0x82,0xa4,0,0xb1,4,0x33,
0xed,0xbe,0xbe,9,0x38,4,0x74,8,0x23,0xed,0x75,0xf,0x8b,0xee,0x8b,0x14,
0x83,0xc6,0x10,0xe2,0xef,0x23,0xed,0x75,9,0xcd,0x18,0x8d,0x36,0x74,7,0xe9,
0x83,0,0xc7,6,0xfe,0x7d,0x55,0xaa,0x8a,0x46,4,0x33,0xff,0x3c,0xb,0x72,
7,0x3c,0xd,0x73,3,0xbf,6,0,0x3c,0x10,0x73,9,0x8d,0x1e,0x64,7,
0xd7,0x22,0xc0,0x74,0xd6,0x50,0xb4,0x41,0xbb,0xaa,0x55,0xcd,0x13,0x58,0x72,0x61,
0x81,0xfb,0x55,0xaa,0x75,0x5b,0xf6,0xc1,1,0x74,0x56,0x88,0x46,4,0xb9,0x10,
0,0x33,0xc0,0xbb,0,0x7c,0x50,0x50,0xff,0x76,0xa,0xff,0x76,8,0xe,0x53,
0x50,0x51,0x8b,0xf4,0xb8,0,0x42,0xc6,0x44,2,1,0xcd,0x13,0x72,5,0xe8,
0x9c,0,0x74,0x52,0x33,0xc0,0xcd,0x13,0x83,0xf9,8,0x75,7,1,0x7c,8,
0x83,0x54,0xa,0,0xe2,0xde,0xe8,0x85,0,0x74,6,0x8d,0x36,0xa9,7,0xeb,
4,0x8d,0x36,0x8c,7,0xac,0x74,0xfe,0xb4,0xe,0xbb,7,0,0xcd,0x10,0xeb,
0xf4,0xbe,0x10,0,0xbb,0,0x7c,0x8b,0x4e,2,0xb8,1,2,0xcd,0x13,0x72,
5,0xe8,0x5a,0,0x74,0x10,0x33,0xc0,0xcd,0x13,0x83,0xfe,8,0x75,2,3,
0xcf,0x4e,0x75,0xe6,0xeb,0xc0,0xbe,0,0x7d,0x66,0x81,0x3c,0x49,0x4f,0x20,0x20,
0x75,0xa,0x66,0x81,0x7c,4,0x20,0x20,0x20,0x20,0x74,9,0x46,0x81,0xfe,0xf4,
0x7d,0x72,0xe6,0xeb,0x25,0x83,0xc6,8,0xad,0x8a,0xc,0x8b,0x3e,0xf8,7,0x8a,
0x2e,0xfa,7,0x89,0x7c,0xfe,0x88,0x2c,0x83,0xc6,0xb,0x81,0xfe,0xfe,0x7d,0x73,
9,0x3b,0x44,0xfe,0x75,4,0x3a,0xc,0x74,0xe9,0x8b,0xf5,0xff,0xe3,0x81,0x3e,
0xfe,0x7d,0x55,0xaa,0xc3,0x52,0x75,0x64,0x6f,0x6c,0x70,0x68,0x20,0x52,0x2e,0x20,
0x4c,0x6f,0x65,0x77,0,0xe,2,3,0xe,0,0xe,7,8,9,0xa,0xc,
0xc,0xd,0xe,0,0x49,0x6e,0x76,0x61,0x6c,0x69,0x64,0x20,0x50,0x61,0x72,0x74,
0x69,0x74,0x69,0x6f,0x6e,0x20,0x54,0x61,0x62,0x6c,0x65,0,0x44,0x69,0x73,0x6b,
0x20,0x45,0x72,0x72,0x6f,0x72,0x20,0x4c,0x6f,0x61,0x64,0x69,0x6e,0x67,0x20,0x50,
0x61,0x72,0x74,0x69,0x74,0x69,0x6f,0x6e,0,0x50,0x61,0x72,0x74,0x69,0x74,0x69,
0x6f,0x6e,0x20,0x4e,0x6f,0x74,0x20,0x46,0x6f,0x72,0x6d,0x61,0x74,0x74,0x65,0x64,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0x53,0x59,0x53,0,0,0,0x57,0};

#define winext 0x1f8

unsigned char rotdrv[]={
0x33,0xc0,0x8e,0xd0,0xbc,0,0x7c,0xfb,0xfc,0x8e,0xd8,0xa1,0x13,4,0xbe,0x26,
0x7c,0x48,0x8d,0x3e,0x26,0,0xa3,0x13,4,0xc1,0xe0,6,0x8e,0xc0,0xb9,0xda,
1,6,0x57,0xf3,0xa4,0xcb,0xb4,8,0xba,0x80,0,0xcd,0x13,0x73,2,0xcd,
0x18,0xb6,0,0x8b,0xca,0x2e,0x88,0x16,0x1b,1,0x1e,7,0xba,0x80,0,0x51,
0xb8,1,2,0xbb,0,0x7c,0xb9,1,0,0xcd,0x13,0x72,0x18,0x81,0x3e,0xfe,
0x7d,0x55,0xaa,0x75,0x10,0xbf,0xbe,0x7d,0xb9,4,0,0x80,0x3d,0,0x75,0xb,
0x83,0xc7,0x10,0xe2,0xf6,0x59,0x42,0xe2,0xd6,0xcd,0x18,0x80,0xe2,0x7f,0x2e,0x88,
0x16,0x1c,1,0xb0,0x30,2,0xc2,0x2e,0xa2,0x4f,1,0x8d,0x36,0x35,1,0xe,
0x1f,0xb4,0xe,0xac,0x22,0xc0,0x74,4,0xcd,0x10,0xeb,0xf5,0x33,0xc0,0x8e,0xd8,
0x66,0xa1,0x4c,0,0x66,0x2e,0xa3,0xb0,0,0x8d,0x1e,0xb5,0,0x89,0x1e,0x4c,
0,0x8c,0xc8,0xa3,0x4e,0,0x1e,0x68,0,0x7c,0xcb,0x9c,0x80,0xc2,0x80,0x9a,
0,0,0,0,0xc3,0x80,0xfc,0xff,0x75,0xc,0xe,7,0x8d,0x1e,0x1f,1,
0xb8,0xaa,0x55,0xca,2,0,0x2e,0x80,0x3e,0x1e,1,0,0x74,0x15,0x80,0xfa,
0x81,0x75,0xa,0x2e,0xc6,6,0x1e,1,1,0xf9,0xca,2,0,0x2e,0x80,0x26,
0x1e,1,2,0x2e,0x88,0x16,0x1d,1,0x80,0xea,0x80,0x73,6,0xe8,0xbb,0xff,
0xca,2,0,0x2e,0x38,0x16,0x1b,1,0x76,0xf3,0x2e,2,0x16,0x1c,1,0x2e,
0x38,0x16,0x1b,1,0x77,5,0x2e,0x2a,0x16,0x1b,1,0x80,0xfc,8,0x74,0xdd,
0xe8,0x98,0xff,0x2e,0x8a,0x16,0x1d,1,0xca,2,0,0,0,0,2,0x41,
0x45,0x52,0x4d,0x48,0x31,0x33,0x56,0x52,0x4c,0,0xe,2,3,0xe,5,0xe,
7,8,9,0xa,0xc,0x44,0x72,0x69,0x76,0x65,0x20,0x53,0x65,0x71,0x75,0x65,
0x6e,0x63,0x65,0x20,0x52,0x6f,0x74,0x61,0x74,0x65,0x64,0x20,0x62,0x79,0x20,0x3f,
0xd,0xa,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

struct part {
struct part *next,*lpart;
unsigned long start,len,base;
unsigned char type,btype,clear,valid,heads,sectors,active[63],partsec[63],xp[10];
};

struct drive {
struct drive *next;
unsigned char drive,heads,sectors,partsecs,install,hd8,sec8,mb;
unsigned int cyl8,seclen,fmtlen,sig;
unsigned long length,cyls,cylex,hdex,secex,exts;
unsigned char id[63],id0[63],xp[10],active,err,tlen,ovl[ovll];
struct part *list;
};

struct table {
unsigned char act,shead,ssec,scyl,type,ehead,esec,ecyl;
unsigned long off,len;
};

struct sector {
unsigned short mb;
unsigned char x0[0x11];
unsigned short slen;
unsigned char x1[3];
int secs,heads;
unsigned long off,len;
unsigned char x2[0x12];
long type;
unsigned char type1;
unsigned char x3[0x17];
long type2;
unsigned char x4[0x15a],def,tlen;
int id;
unsigned char xp[10];
struct table parts[4];
unsigned int tag;
};

struct drive *disks=0;

void build(),buildl(),addl(),addx(),show(),freed(),valid(),lock(),memclr();
long int1308(),fb,farmalloc(),getnum(),getnumz();
struct part *add(),*find();
char *fmt();

int enab=0,mode=0,brk;
long hide=0x3fffffff;
unsigned long mod40=0xffffffff;
int f0=0,f1=0,ov=1,sr=1,xt=0;

void brkp(int i)
{
brk=i;
}

void die(int i)
{
exit(i);
}

main(c,v)
int c;
char **v;
{
int i,j,k,m,mm,x,cc,xxx[2];
unsigned long e,l,ll,d[8],mult,xx[4],z,blk;
struct drive *disk,*dd,*cdisk;
struct sector sec;
struct part *p,*ep;
unsigned char cmd[128],*s,*ss,*(vv[6]);
unsigned char wsp1[512],wsp2[512];
fb=farmalloc(32768L);
if (fb==0) {printf("Not Enough Memory\n");return(20);}
mm=0;m=0x90;
arg: if (c>1) if (v[1][0]=='-') {
c--;v++;
if ((v[0][1]&0xdf)=='R') {mode|=1;goto arg;}
if ((v[0][1]&0xdf)=='C') {mode|=2;goto arg;}
if ((v[0][1]&0xdf)=='E') {mod40=mod40d;goto arg;}
if ((v[0][1]&0xdf)=='O') {ov=0;goto arg;}
if ((v[0][1]&0xdf)=='N') {sr=0;goto arg;}
if ((v[0][1]&0xdf)=='X') {xt=1;goto arg;}
m=getnum(v[0]+1);
if (m==0) {printf("Invalid Option\n");return(20);}
m+=128;mm=m;goto arg;
}
if (c<2) {printf("* [-RAW] [-CHS] [-XT] [-ExtMBR] [-Overlap] [-NoSwap] [-#(MaxDrive)] Write|Diag\n");return(20);}

#ifdef DEMO
else printf("\nR. Loew Electronics Drive Partitioning Program Version 2.6 (DEMO)\nCopyright (C) 2008-2011, All Rights Reserved\n\n");
#else
else printf("\nR. Loew Electronics Drive Partitioning Program Version 2.6\nCopyright (C) 2008-2011, All Rights Reserved\n\n");
#endif
if ((v[1][0]&0xdf)=='W') enab=1;
start: cdisk=0;
for (i=0x80;i<m;i++) {
if (mode&1) {
if (int13raw(2,i,0L,0L,&sec)==0) j=rawsize(512);
else j=0;
}
else j=farsecsz(i,fb);
if (int13(0x42,i,0L,&sec)==0) {
if (mm==0) if (i<254) if (i>(m-2)) m=i+2;
disk=(struct drive *)calloc(sizeof(struct drive),1);
if (disk==0) goto nomem;
e=int1308(i);disk->cyl8=e>>16;disk->hd8=e>>8;disk->sec8=e;
disk->drive=i;disk->heads=disk->hd8;disk->sectors=disk->sec8;
if (disk->sec8==0) {disk->heads=255;disk->sectors=63;}
d[4]=d[5]=d[6]=0;int13(0x48,i,0L,d);disk->length=d[4];
if (d[5]) {
disk->length= -2;
if (mod40+1) disk->length=mod40+((d[5]&255)<<16)+((d[4]>>16)&0xff00);
}
disk->cylex=d[1];disk->hdex=d[2];disk->secex=d[3];disk->fmtlen=0;
if ((mode&1)==0) disk->seclen=d[6]&0xffff;
if (disk->seclen==0) disk->seclen=j;
if (disk->tlen=sec.tlen) disk->fmtlen=512;
if (disk->tlen>63) disk->fmtlen=1<<(disk->tlen-64);
if (disk->length==0) disk->length=0xffffffff;
disk->partsecs=1;disk->id[0]='-';disk->active=sec.def;
memcpy(disk->xp,&(sec.xp),10);
if (sec.tag==0xaa55) {
for (j=0;j<4;j++) if (sec.parts[j].type) if ((sec.parts[j].off&0xff000000)-mod40) goto fnd;
goto notfnd;
fnd: disk->heads=sec.parts[j].ehead+1;disk->sectors=sec.parts[j].esec&63;
notfnd: disk->cyls=disk->length/disk->heads/disk->sectors;
for (l=0;l<ovll;l++) disk->ovl[l]=0;
disk->mb=2;j=(int)(&sec);disk->sig= *(int *)(j+10);
if (disk->sig-0x4c52)  disk->mb=3;
if ((*(int *)(j+0x16c))==0x4c52) disk->mb=4;
if ((*(int *)(j+0x180))==0x4c52) disk->mb=4;
if (cmpx(mbr,&sec,mbrd)==0) disk->mb=0;
if (cmpx(mbr2,&sec,mbr2d)==0) disk->mb=1;
if (sec.id==0x4c52) {
memcpy(disk->ovl,((int)&sec)+ovlo,ovll);disk->ovl[0]=0;
for (l=1;l<disk->sectors;l++) {
if (int13(0x42,i,l,&sec)==0) {
if (sec.tag&255) {
k=sec.tag>>8;
if (k) {j=l;disk->id[l]=sec.tag;build(disk,j,&sec);}
else {
j=sec.tag&0xff;
if (j=='W') disk->exts= *(long *)(((int)(&sec))+winext);
if ((j>='A') && (j<='Z')) j+=32;
else j='*';
disk->id0[l]=j;
}
if (k>1) l+=k-1;
}
else {disk->partsecs=l;l=64;disk->id[0]=0;}
}
else {printf("Error Reading Disk %02x Sector %02u\n",i-0x80,l);disk->err|=1;}
}
}
else build(disk,0,&sec);
}
else disk->install=1;
if (disks) {
dd=disks;
while (dd->next) dd=dd->next;
dd->next=disk;
}
else disks=disk;
}
}
if (disks==0) {
if (mode==0) {
printf("No Extended INT13 Disks Detected - Switching to CHS\n");mode=2;goto start;
}
printf("No Disks Detected\n");return(20);
}
if (disks->next==0) cdisk=disks;
lp: if (cdisk) show(cdisk);
else {
dd=disks;
while (dd) {show(dd);dd=dd->next;}
}
lp1: if (f0==0) printf("\n> ");
i=0;
while (read(f0,cmd+i,1)>0) { 
i++;
if (i==126) goto lp0;
if (cmd[i-1]==10) goto lp0;
}
if (f0==0) return(0);
close(f0);f0=0;goto lp1;
lp0: cmd[i]=0;
if (i==0) return(0);
if (cmd[0]==10) goto lp;


if (cmd[0]=='?') {
if (cdisk) {
printf("Add Type Start End [+Head1]        Change Type Start NewType [NewEnd]\n");
printf("Remove Type Start                  KillAll\n");
printf("Link Type Start Profile            UnLink Type Start Profile\n");
printf("NewProfile Profile                 SetActiveProfile Profile\n");
printf("ToggleActive Type Start [Profile]  EraseBootToggle Type Start\n");
printf("ZeroFillExt Add|Remove             Geometry Heads Sectors [Cylinders]\n");
printf("Find [Start [All]]                 Validate Type Start\n");
printf("Build SaveFile                     MBR\n");
printf(">SectorImageFile (Save)            <SectorImageFile (Load)\n");

#ifdef DEMO
printf("Write (Disabled in Demo Version)   @ Refresh Overlay Table\n\n");
#else
printf("Write [W_Extension]                @ Refresh Overlay Table\n\n");
#endif

}
printf("Install/Uninstall_Multi_Boot_MBR Drive# [UninstFromProfile]\n\n");

#ifdef DEMO
printf("PutMBR (Disabled in Demo Version)  Xcise (Disabled in Demo Version)\n");
#else
printf("PutMBR Drive# [Profile]            Xcise Drive# Profile\n");
#endif

printf("Drive [#]                          Hide [#] (0=Ext)\n");
printf("OldValues                          +InputFile\n");
printf("Quit\n");
goto lp1;
}
cc=parsearg(vv,cmd,6,32);
if (cc>1) {xx[0]=getnumz(vv[1]);xxx[0]=getnumx(vv[1]);}
if (cc>2) xx[1]=getnumz(vv[2]);
if (cc>3) {xx[2]=getnumz(vv[3]);xxx[1]=getnumx(vv[3]);}
if (cc>4) xx[3]=getnumz(vv[4]);
if (cmd[0]>0x40) cmd[0]&=0xdf;

if (cmd[0]=='I') {
time(mbr+mbrd);time(mbr2+mbr2d);
cmd[56]='0';i=xx[0];
if (cc>2) strcpy(cmd+56,vv[2]);
if (cc<2) {printf("Drive Not Specified\n");goto lp1;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) goto iok;
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
iok: if (enab==0) {
if (dd->partsecs==1) printf("Cannot Install Multi Boot MBR in DIAG Mode\n");
else printf("Cannot Remove Multi Boot MBR in DIAG Mode\n");
goto lp1;
}
if (dd->mb==4) {
printf("\nWARNING: R. Loew BOOTMAN Disk Manager Installed - Overwrite ? (Y/N) (N) ");read(0,&ll,4);
if ((ll&0xdf)-'Y') goto lp1;
}
cdisk=0;s=(char *)calloc(1,1024);
if (s==0) {printf("Not Enough Memory\n");goto lp1;}
if (dd->partsecs==1) {
if (cmd[56]-'0') {printf("From Profile valid only when Uninstalling\n");goto iquit;}
if (int13(0x42,i,0L,s+512)) {printf("Error Reading MBR Sector\n");dd->err|=1;goto iquit;}
printf("\nUNWRITTEN CHANGES WILL BE DISCARDED\n\nInstall Multi Boot MBR ? (Y/N/MBR) (N) ");read(0,&l,4);
if (((l&0xdf)-'M') && ((l&0xdf)-'Y')) goto iquit;
memcpy(s,rotdrv,512);
if ((l&0xdf)-'M') if (int13(0x43,i,2L,s)) {printf("Error Writing End Sector\n");goto ierr;}
memcpy(s,mbr2,mbr2len);memcpy(s+512,mbr,mbrl);memcpy(s+0x1b4,s+0x3b4,0x4a);
for (j=0;j<ovll;j++) dd->ovl[j]=0;
if ((l&0xdf)-'M') {
for (j=(mbrl+512);j<0x3b4;j++) s[j]=0;
s[1022]=0x30;s[1023]=1;
if (int13(0x43,i,1L,s+512)) {printf("Error Writing Default Sector\n");goto ierr;}
}
}
else {
if ((cmd[56]>='a') && (cmd[56]<='z')) cmd[56]-=32;
for (l=1;l<dd->partsecs;l++) {
if (int13(0x42,i,l,s)) {printf("Error Reading Sector %lu\n",l);dd->err|=1;goto ierr;}
if (s[510]==cmd[56]) goto iun;
}
printf("Profile Not Found\n");goto iquit;
iun: printf("\nUNWRITTEN CHANGES WILL BE DISCARDED\n\nUninstall Multi Boot MBR ? (Y/N) (N) ");read(0,&l,4);
if ((l&0xdf)-'Y') goto ierr;
}
s[510]=0x55;s[511]=0xaa;
if (int13(0x43,i,0L,s)) {printf("Error Writing MBR Sector\n");goto ierr;}
iend: freed();free(s);goto start;
ierr: freed();
iquit: free(s);goto lp1;
}

#ifndef DEMO

if (cmd[0]=='P') {
cmd[56]='0';i=xx[0];
if (cc>2) strcpy(cmd+56,vv[2]);
if (cc<2) {printf("Drive Not Specified\n");goto lp1;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) goto pok;
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
pok: if (enab==0) {
printf("Cannot Install Multi Boot MBR in DIAG Mode\n");goto lp1;
}
j=cmd[56];
if ((j>='a') && (j<='z')) j-=32;
if ((j=='D') || (j=='W')) {printf("Cannot Put MBR in DOS or Windows Boot Sector\n");goto lp1;}
cdisk=0;s=(char *)calloc(1,1024);
if (s==0) {printf("Not Enough Memory\n");goto lp1;}
if (int13(0x42,i,1L,s+512)) {printf("Error Reading Second Sector\n");goto iquit;}
k=s[1022];
if (s[1023]-1) k=0;
if (int13(0x42,i,0L,s+512)) {printf("Error Reading MBR Sector\n");cdisk->err|=1;goto iquit;}
if ((s[522]==0x52) && (s[523]==0x4c)) {printf("Cannot Move Multi Boot MBR\n");goto iquit;}
printf("\nUNWRITTEN CHANGES WILL BE DISCARDED\n\nInstall Multi Boot MBR ? (Y/N) (N) ");read(0,&l,4);
if ((l&0xdf)-'Y') goto iquit;
s[1022]=j;s[1023]=1;
memcpy(s,rotdrv,512);
if (k-'0') {
if (j=='0') {
if (int13(0x43,i,2L,s)) {printf("Error Writing End Sector\n");goto ierr;}
}
else {
if (int13(0x43,i,3L,s)) {printf("Error Writing End Sector\n");goto ierr;}
if (int13(0x43,i,2L,s+512)) {printf("Error Writing New Entry\n");goto ierr;}
memcpy(s+512,mbr,mbrl);s[1022]=0x30;
for (j=(mbrl+512);j<0x3fe;j++) s[j]=0;
}
if (int13(0x43,i,1L,s+512)) {printf("Error Writing Default Sector\n");goto ierr;}
imbr: memcpy(s,mbr2,mbr2len);memcpy(s+0x1b4,s+0x3b4,0x4c);s[510]=0x55;s[511]=0xaa;
if (int13(0x43,i,0L,s)) {printf("Error Writing MBR Sector\n");goto ierr;}
}
else {
for (l=1;l<62;l++) {
if (int13(0x42,i,l,s)) {printf("Error Reading Sector %lu\n",l);goto ierr;}
if (s[510]==0) {
if (int13(0x43,i,l+1,s)) {printf("Error Writing End Sector\n");goto ierr;}
if (int13(0x43,i,l,s+512)) {printf("Error Writing New Entry\n");goto ierr;}
goto imbr;
}
if (s[510]==j) {
if (int13(0x43,i,l,s+512)) {printf("Error Writing New Entry\n");goto ierr;}
goto imbr;
}
}
printf("Bad SwitchBoot Structure\n");goto ierr;
}
goto iend;
}

if (cmd[0]=='X') {
cmd[56]=0;i=xx[0];
if (cc>2) strcpy(cmd+56,vv[2]);
if (cc<2) {printf("Drive Not Specified\n");goto lp1;}
if (cmd[56]==0) {printf("Profile Not Specified\n");goto lp1;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) goto xok;
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
xok: if (enab==0) {
printf("Cannot Remove Multi Boot Entry in DIAG Mode\n");goto lp1;
}
if (dd->partsecs==1) {printf("No Multi Boot MBR on Drive\n");goto lp1;}
j=cmd[56];
if ((j>='a') && (j<='z')) j-=32;
if ((j=='D') || (j=='W')) j+=32;
if (j=='0') {printf("Cannot Remove Default Profile\n");goto lp1;}
cdisk=0;s=(char *)calloc(1,512);
if (s==0) {printf("Not Enough Memory\n");goto lp1;}
for (l=2;l<63;l++) {
if (int13(0x42,i,l,s)) {printf("Error Reading Sector %lu\n",l);goto iquit;}
if (s[510]==j) goto xfnd;
if (s[510]==0) goto xbad;
}
xbad: printf("Profile Not Found\n");goto iquit;
xfnd: printf("\nUNWRITTEN CHANGES WILL BE DISCARDED\n\nRemove Profile ? (Y/N) (N) ");read(0,&ll,4);
if ((ll&0xdf)-'Y') goto iquit;
for (l++;l<63;l++) {
if (int13(0x42,i,l,s)) {printf("Error Reading Sector %lu\n",l);goto ierr;}
if (int13(0x43,i,l-1,s)) {printf("Error Writing Sector %lu\n",l-1);goto ierr;}
if (s[510]==0) goto iend;
}
printf("Bad Multi Boot Structure\n");goto ierr;
}

#endif

if (cmd[0]=='+') {
if (f0) close(f0);
f0=strlen(cmd);
if (cmd[f0-1]==10) cmd[f0-1]=0;
f0=open(cmd+1,0);
if (f0<0) {printf("Cannot Open Input File\n");f0=0;}
goto lp1;
}

if (cmd[0]=='Q') return(0);

if (cmd[0]=='O') {freed();goto start;}

if (cmd[0]=='D') {
i=xx[0];
if (cc<2) {cdisk=0;goto lp;}
i+=128;dd=disks;
while(dd) {
if (dd->drive==i) {cdisk=dd;goto lp;}
dd=dd->next;
}
printf("Invalid Drive\n");goto lp1;
}

if (cmd[0]=='H') {
hide=xx[0];
if (cc<2) hide=0x3fffffff;
goto lp;
}
if (cdisk==0) {printf("Invalid Command\n");goto lp1;}
mult=cdisk->heads*cdisk->sectors;
switch(cmd[0]) {
case '>': i=strlen(cmd);
          if (cmd[i-1]==10) cmd[i-1]=0;
          s=(char *)calloc(1,1024);
          if (s==0) {printf("Not Enough Memory\n");_close(i);goto lp1;}
          i=_creat(cmd+1,0);
          if (i<0) {printf("Cannot Create Image File\n");free(s);goto lp1;}
          l=cdisk->partsecs;
          for (ll=0;ll<l;ll++) {
          if (int13(0x42,cdisk->drive,ll,s)) {printf("Error Reading Sector %lu\n",ll);cdisk->err|=1;goto sf1;}
          if (_write(i,s,512)-512) {printf("Error Writing Image File\n");goto sf1;}
          }
          free(s);_close(i);goto lp1;
          sf1: free(s);_close(i);goto lp1;
case '<': i=strlen(cmd);
          if (cmd[i-1]==10) cmd[i-1]=0;
          s=(char *)calloc(1,1024);
          if (s==0) {printf("Not Enough Memory\n");_close(i);goto lp1;}
          i=_open(cmd+1,0);
          if (i<0) {printf("Cannot Open Image File\n");free(s);goto lp1;}
          l=lseek(i,0L,2);lseek(i,0L,0);
          if (l&511) {
          badlf: printf("Invalid Image File\n");_close(i);free(s);goto lp1;
          }
          printf("Load Image File ? (Y/N) (N) ");read(0,&ll,4);
          if ((ll&0xdf)-'Y') {_close(i);free(s);goto lp;}
          ll=0;
          while(_read(i,s,512)==512) {
          if (ll==0) if ((s[510]-0x55) || (s[511]-0xaa)) goto badlf;
          if (int13(0x43,cdisk->drive,ll++,s)) {printf("Error Writing Sector %lu\n",ll-1);goto lf1;}
          }
          for (j=0;j<512;j++) s[j]=0;
          if (int13(0x43,cdisk->drive,ll++,s)) printf("Error Writing Sector %lu\n",ll-1);
          lf1: _close(i);freed();free(s);goto start;
case 'A': cmd[60]=0;
          i=xxx[0];l=xx[1];ll=xx[2];
          if (cc>4) strcpy(cmd+60,vv[4]);
          if (cc<4) goto bad;
          if (validate(((i==5) || (i==15)) ? 3 : 2,mult,l,ll)) goto lp1;
          if (mode>=2) if (ll>(xt ? 4096 : 1024)) {printf("Invalid CHS Cylinder\n");goto lp1;}
          if ((i==5) || (i==15)) {
          if (l==0) {printf("Invalid Start\n");goto lp1;}
          if (cmd[60]=='+') {printf("Cannot Offset Extended Partition\n");goto lp1;}
          }
          if ((l&0xff000000)-mod40) l*=mult;
          if ((ll&0xff000000)-mod40) ll*=mult;
          addx(cdisk,i,l,ll,(cmd[60]=='+') ? ((cmd[61]=='+') ? 2 : 1) : 0);goto lp;
case 'B': f1=strlen(cmd);
          if (cmd[f1-1]==10) cmd[f1-1]=0;
          f1=0;
          while (cmd[f1] && (cmd[f1]-32)) f1++;
          while (cmd[f1] && (cmd[f1]==32)) f1++;
          if (cmd[f1]==0) {f1=0;goto bad;}
          f1=creat(cmd+f1,0x80);
          if (f1<0) {f1=0;printf("Cannot Create SaveFile\n");goto lp1;}
          show(cdisk);close(f1);f1=0;goto lp;
case 'C': ll=0;
          i=xxx[0];l=xx[1];j=xxx[1];
          if (cc<4) goto bad;
          if (cc>4) {
          ll=xx[3];
          if (validate(((i==5) || (i==15)) ? 3 : 2,mult,l,ll)) goto lp1;
          if (mode>=2) if (ll>(xt ? 4096 : 1024)) {printf("Invalid CHS Cylinder\n");goto lp1;}
          }
          else {
          if (validate(1,mult,l)) goto lp1;
          }
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if ((ll&0xff000000)-mod40) ll=ll*mult;
          if (ll==0) ll=p->start+p->len;
          if (ll<=p->start) {printf("Invalid End\n");goto lp1;}
          p->len=ll-p->start;p->type=j;valid(cdisk,p);
          goto lp;
case 'R': i=xxx[0];l=xx[1];
          if (cc<3) goto bad;      
          if (validate(1,mult,l)) goto lp1;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          free1(p);goto lp;
case 'K': while(cdisk->list) free1(cdisk->list);
          cdisk->err=0;goto lp;
case 'L': cmd[60]='-';
          i=xxx[0];l=xx[1];
          if (cc>3) strcpy(cmd+60,vv[3]);
          if (cc<3) goto bad;
          if (validate(1,mult,l)) goto lp1;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto lfnd;
          printf("Unknown Partition ID\n");goto lp1;
lfnd:     for (i=0;i<63;i++) {
          if (p->partsec[i]==0) {p->partsec[i]=j;goto lp;}
          if (p->partsec[i]==j) {printf("Already Linked\n");goto lp1;}
          }
          printf("List Full\n");goto lp1;
case 'U': cmd[60]='-';
          i=xxx[0];l=xx[1];
          if (cc>3) strcpy(cmd+60,vv[3]);
          if (cc<3) goto bad;
          if (validate(1,mult,l)) goto lp1;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto ufnd;
          printf("Unknown Partition ID\n");goto lp1;
ufnd:     for (i=0;i<63;i++) {
          if (p->partsec[i]==0) {printf("Link Not Found\n");goto lp1;}
          if (p->partsec[i]==j) {
          for (;i<62;i++) p->partsec[i]=p->partsec[i+1];
          p->partsec[62]=0;;goto lp;
          }
          }
          printf("Link Not Found\n");goto lp1;
case 'N': cmd[60]='0';
          if (cc>1) strcpy(cmd+60,vv[1]);
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          if (cdisk->partsecs==1) {printf("No Multi Boot MBR\n");goto lp1;}
          if ((cmd[60]=='D') || (cmd[60]=='W')) cmd[60]+=32;
          for (j=0;j<63;j++) if ((cdisk->id[j]==cmd[60]) || (cdisk->id0[j]==cmd[60])) {
          printf("Partition ID Exists\n");goto lp1;
          }
          j=64;
          for (i=0;i<ovll;i++) if (cdisk->ovl[i]) if (cdisk->ovl[i]<j) j=cdisk->ovl[i];
          if (cdisk->partsecs>=(j-2)) {printf("List Full\n");goto lp1;}
          if ((cmd[60]=='d') || (cmd[60]=='w')) {
          cdisk->id0[cdisk->partsecs++]=cmd[60];
          }
          else cdisk->id[cdisk->partsecs++]=cmd[60];
          goto lp;
case 'S': cmd[60]=0;
          if (cc>1) strcpy(cmd+60,vv[1]);
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          if (cdisk->partsecs==1) {printf("No Multi Boot MBR\n");goto lp1;}
          if (cmd[60]==0) {cmd[60]=32;goto sok;}
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto sok;
          if ((cmd[60]-'?') && (cmd[60]-'*')) printf("\nID Not Listed Assuming Boot Overlay\n");
sok:      cdisk->active=cmd[60];goto lp;
case 'M': if (cdisk->mb==4) {
          printf("\nWARNING: R. Loew BOOTMAN Disk Manager Installed - Overwrite ? (Y/N) (N) ");read(0,&ll,4);
          if ((ll&0xdf)-'Y') goto lp;
          }
          cdisk->install=1;cdisk->mb=1;goto lp;
case 'T': cmd[60]='-';
          i=xxx[0];l=xx[1];
          if (cc>3) strcpy(cmd+60,vv[3]);
          if (cc<3) goto bad;
          if (validate(1,mult,l)) goto lp1;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          if ((cmd[60]>='a') && (cmd[60]<='z')) cmd[60]-=32;
          for (j=1;j<64;j++) if (cdisk->id[j-1]==cmd[60]) goto tfnd;
          printf("Unknown Partition ID\n");goto lp1;
tfnd:     for (i=0;i<63;i++) {
          if (p->active[i]==0) {p->active[i]=j;goto lp;}
          if (p->active[i]==j) {
          for (;i<62;i++) p->active[i]=p->active[i+1];
          p->active[62]=0;goto lp;
          }
          }
          printf("List Full\n");goto lp1;
case 'E': i=xxx[0];l=xx[1];
          if (cc<3) goto bad;
          if (validate(1,mult,l)) goto lp1;
          if ((i==5) || (i==15)) {printf("Cannot Erase Extended Partition\n");goto lp1;}
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          p->valid^=4;goto lp;
case 'V': i=xxx[0];l=xx[1];
          if (cc<3) goto bad;
          if (validate(1,mult,l)) goto lp1;
          if ((p=find(cdisk,i,l))==0) {printf("Partition Not Found\n");goto lp1;}
          valid(cdisk,p);
          goto lp;
case 'G': e=0;
          i=xx[0];j=xx[1];
          if (cc>3) e=xx[2];
          if ((cc<3) || (i<1) || (j<1) || (i>255) || (j>255)) goto bad;
          cdisk->heads=i;cdisk->sectors=j;
          if (e) {cdisk->cyls=e;cdisk->length=e*mult;}
          else cdisk->cyls=cdisk->length/cdisk->heads/cdisk->sectors;
          goto lp;
case 'Z': cmd[60]=0;
          if (cc>1) strcpy(cmd+60,vv[1]);
          p=cdisk->list;
          while(p) {
          if ((p->type==5) || (p->type==15)) {
          switch(cmd[60]&0xdf) {
          case 'A': l=p->start;e=l+p->len;ep=p->lpart;
                    while(ep) {
                    ll=ep->start-cdisk->sectors;
                    if (ll>l) addx(cdisk,0,l,ll,0);
                    l=ep->start+ep->len;
                    ep=ep->next;
                    }
                    if (e>l) addx(cdisk,0,l,e,0);
                    break;
          case 'R':
zfnd1:              if (p->lpart==0) break;
                    if (p->lpart->type==0) {free1(p->lpart);goto zfnd1;}
                    ep=p->lpart;
zfnd2:              if (ep->next==0) break;
                    if (ep->next->type==0) {free1(ep->next);goto zfnd2;}
                    ep=ep->next;goto zfnd2;
          default:  printf("Invalid Option\n");goto lp1;
          };
          }
          p=p->next;
          }
          goto lp;
case 'F': l=ll=0;cmd[60]=0;
          if (cc>1) l=xx[0];
          if (validate(1,mult,l)) goto lp1;
          if (cc>2) strcpy(cmd+60,vv[2]);
          switch(cmd[60]&0xdf) {
          case 'A': ll=1;
          case 0:   break;
          default:  printf("Invalid Option\n");goto lp1;
          };
          if (l==0) {
          for (l=1;l<64;l++) if (l-cdisk->sectors) if (int13(0x42,cdisk->drive,l,&sec)==0) if (sec.tag==0xaa55) {
          if (sec.len==0) sec.len=sec.slen;
          switch(sec.type) {
          case 0: printf("Unexpected EXT Record at Sector %lu\n",l);break;
          case 0x33544146: printf("Unexpected FAT32 Record at Sector %lu: Off=%lu Len=%lu Heads=%u Secs=%u\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
          case 0x31544146: if (sec.type1=='6') {
                           printf("Unexpected FAT16 Record at Sector %lu: Off=%lu Len=%lu Heads=%u Secs=%u\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
                           }
                           if (sec.type1=='2') {
                           printf("Unexpected FAT12 Record at Sector %lu: Off=%lu Len=%lu Heads=%u Secs=%u\n",l,sec.off,sec.len,sec.heads,sec.secs);
                           break;
                           }
          default: printf("Unexpected Record at Sector %lu\n",l);
          };
          }
          l=0;
          }
          if ((l&0xff000000)-mod40) l*=mult;
          brk=0;signal(2,brkp);
          for (;l<cdisk->length;l+=((l&0xff000000)-mod40) ? mult : 256) {
f0:       if (brk) {printf("BREAK\n");goto f3;}
          if (mode>=2) if (l>=(mult<<(xt ? 12 : 10))) goto f3;
          if (l>=(hide*mult)) {printf("*\n");goto f3;}
          if (l) {
          if (int13(0x42,cdisk->drive,l,&sec)) goto f3;
          if (sec.tag==0xaa55) {
          if (sec.type==0) sec.type=sec.type2;
          if (sec.len==0) sec.len=sec.slen;
          fmt(&sec,cdisk,l);
          fmt(&(sec.x3),cdisk,l+sec.len);
          fmt(&(sec.parts),cdisk,sec.off);
          switch(sec.type) {
          case 0: printf("EXT   Record at %s\n",&sec);break;
          case 0x33544146: printf("FAT32 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
          case 0x31544146: if (sec.type1=='6') {
                           printf("FAT16 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
                           }
                           if (sec.type1=='2') {
                           printf("FAT12 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f1;
                           }
          default: printf("Unknown Record at %s\n",&sec);
          };
          }
          }
          if (int13(0x42,cdisk->drive,l+cdisk->sectors,&sec)) goto f3;
          if (sec.tag==0xaa55) {
          if (sec.type==0) sec.type=sec.type2;
          if (sec.len==0) sec.len=sec.slen;
          fmt(&sec,cdisk,l+cdisk->sectors);
          fmt(&(sec.x3),cdisk,l+sec.len+cdisk->sectors);
          fmt(&(sec.parts),cdisk,sec.off);
          switch(sec.type) {
          case 0: printf("Unexpected EXT Record at %s\n",&sec);break;
          case 0x33544146: printf("FAT32 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
          case 0x31544146: if (sec.type1=='6') {
                           printf("FAT16 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
                           }
                           if (sec.type1=='2') {
                           printf("FAT12 Record at %s: End = %s   Off = %s Heads=%u Secs=%u\n",&sec,&(sec.x3),&(sec.parts),sec.heads,sec.secs);
                           goto f2;
                           }
          default: printf("Unknown Record at %s\n",fmt(&sec,cdisk,l));
          };
          }
          }
          goto f3;
f1:       l+=ll ? mult : sec.len;
          goto f0;
f2:       i=(l ? 1 : 0);
          l+=ll ? mult : (sec.len+cdisk->sectors);
          if (i==0) if (int13(0x42,cdisk->drive,mult,&sec)==0) if (sec.tag==0xaa55) {
          printf("Unexpected Record at Cylinder 1\n");
          }
          goto f0;
f3:       signal(2,die);goto lp1;

#ifndef DEMO

case 'W': cmd[60]=0;
          if (cc>1) strcpy(cmd+60,vv[1]);
          if (cmd[60]) {
          if (strlen(cmd+60)-3) {printf("Extension Must be Three Characters\n");goto lp1;}
          for (j=60;j<63;j++) if ((cmd[j]>='a') && (cmd[j]<='z')) cmd[j]-=32;
          cdisk->exts= *(long *)(cmd+60);
          }
          if (cdisk->err) {
          printf("\nPARTITIONS HAVE BEEN LOST DUE TO ");
          switch(cdisk->err) {
          case 1: printf("DISK READ ERRORS");break;
          case 2: printf("OVERLAPS");break;
          case 3: printf("DISK READ ERRORS AND OVERLAPS");break;
          };
          printf("\nTHESE PARTITIONS WILL BE REMOVED PERMANENTLY - Continue ? (Y/N) (N) ");read(0,&ll,4);
          if ((ll&0xdf)-'Y') goto lp1;
          }
          if (cdisk->tlen) if (cdisk->fmtlen-cdisk->seclen) {
          printf("\nPREVIOUSLY PARTITIONED WITH DIFFERENT SECTOR LENGTH - Continue ? (Y/N) (N) ");read(0,&ll,4);
          if ((ll&0xdf)-'Y') goto lp1;
          }
          if (cdisk->partsecs>1) {
          p=cdisk->list;
          while(p) {
          if (p->partsec[0]==0) goto noref;
          p=p->next;
          }
          goto allref;
noref:    printf("\nUNREFERENCED PARTITION(S) WILL BE REMOVED - Continue ? (Y/N) (N) ");read(0,&ll,4);
          if ((ll&0xdf)-'Y') goto lp1;
allref:;
          }
          time(mbr+mbrd);time(mbr2+mbr2d);
          j=cdisk->partsecs;
          s=(char *)calloc(j+1,enab ? 512 : 1024);
          if (s==0) {printf("Not Enough Memory\n");goto lp1;}
          for (i=0;i<=j;i++) {
          l=i;
          if (int13(0x42,cdisk->drive,l,s+(i<<9))) {printf("Error Reading Sector %lu\n",l);cdisk->err|=1;free(s);goto lp1;}
          }
          if (enab==0) memcpy(s+((j+1)<<9),s,(j+1)<<9);
          if (cdisk->install) {
          if (cdisk->partsecs>1) {
          memcpy(s,mbr2,0x1b0);s[0x1b2]='R';s[0x1b3]='L';
          }
          else {
          memcpy(s,mbr,mbrl);
          for (i=mbrl;i<0x1b4;i++) s[i]=0;
          }
          s[0x1fe]=0x55;s[0x1ff]=0xaa;
          }
          if (cdisk->partsecs>1) memcpy(s+ovlo,cdisk->ovl,ovll);
          memcpy(s+0x1b4,cdisk->xp,10);
          s[0x1b1]=cdisk->sectors;i=cdisk->seclen;
          if (i>512) {
          s[0x1b1]=64;
          while(i>>=1) (s[0x1b1])++;
          if ((*(int *)(s+0x1b2))==0) *(int *)(s+0x1b2)=0x6c72;
          }
          for (ss=s,i=0;i<=j;ss+=512,i++) {
          if (i) if (cdisk->id[i]) if (cdisk->id[i]-s[(i<<9)+0x1fe]) {
          memcpy(ss,s+512,512);ss[0x1fe]=cdisk->id[i];ss[0x1ff]=1;ss[0x3fe]=0;
          }
          if (i) if (cdisk->id0[i]) {
          if (cdisk->install || (cdisk->id0[i]-s[(i<<9)+0x1fe])) {
          if (cdisk->id0[i]=='d') memcpy(ss,dos,512);
          if (cdisk->id0[i]=='w') {
          memcpy(ss,win,512);
          if (cdisk->exts) *(long *)(ss+winext)=cdisk->exts;
          }
          ss[0x3fe]=0;
          }
          }
          if (cdisk->id[i]) {
          for (k=0x1be;k<0x1fe;k++) ss[k]=0;
          ep=p=cdisk->list;k=0x1be;
          while(ep) {
          for (x=0;x<63;x++) if (p->partsec[x]==(i+1)) {
          if (k==0x1fe) {printf("Too Many Partitions in Sector %u\n",i);goto lp3;}
          for (x=0;x<63;x++) if (p->active[x]==(i+1)) {ss[k]=0x80;x=63;}
          l=p->start;
          *(long *)(ss+k+8)=l;
          ss[k+1]=(l/p->sectors)%p->heads;
          ss[k+2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[k+1]+=(x>>4)&192;
          ss[k+3]=x;ss[k+2]+=(x>>2)&192;
          ss[k+4]=p->type;
          l+=p->len;
          *(long *)(ss+k+12)=p->len;
          if ((p->start&0xff000000)==mod40) {
          z=(p->len+255)& -256;*(long *)(ss+k+12)=z<<16;
          if ((*(long *)(ss+k+12))==0) *(long *)(ss+k+12)= -1;
          ss[k+1]=p->heads-1;ss[k+2]=192+p->sectors;ss[k+3]=255;
          }
          l--;
          ss[k+5]=(l/p->sectors)%p->heads;
          ss[k+6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[k+5]+=(x>>4)&192;
          ss[k+7]=x;ss[k+6]+=(x>>2)&192;
          if (((l^ll)&0xfffffc00) || ((p->start&0xff000000)==mod40)) {
          ss[k+5]=p->heads-1;ss[k+6]=192+p->sectors;ss[k+7]=255;
          }
          x=63;k+=16;
          }
          if ((p->type==5) || (p->type==15)) p=p->lpart;
          else {
          if (p-ep) p=p->next;
          else p=0;
          }
          if (p==0) p=ep=ep->next;
          }
          if (sr) if (ss[0x1be]==0) for (k=0x1ce;k<0x1fe;k+=16) if (ss[k]) {
          memcpy(cmd,ss+k,16);memcpy(cmd+16,ss+0x1be,k-0x1be);
          memcpy(ss+0x1be,cmd,k-0x1ae);goto swapd;
          }
swapd:    for (k=0x1be,x=0;k<0x1fe;k+=16) if (ss[k]) x++;
          if (x>1) {
          printf("\nMULTIPLE ACTIVE PARTITIONS - Continue ? (Y/N) (N) ");read(0,&x,4);
          if ((x&0xdf)-'Y') goto lp1;
          }
          for (k=0x1c2,x=0;k<0x1fe;k+=16) if ((ss[k]==5) || (ss[k]==15)) x++;
          if (x>1) {
          printf("\nMULTIPLE EXTENDED PARTITIONS - Continue ? (Y/N) (N) ");read(0,&x,4);
          if ((x&0xdf)-'Y') goto lp1;
          }
          }
          }
          if (cdisk->partsecs>1) {
          s[0x1b0]=cdisk->active;
          if (cdisk->active-32) {
          if ((cdisk->active-'?') && (cdisk->active-'*')) {
          for (i=1;i<63;i++) if (cdisk->id[i]==cdisk->active) goto saok;
          i=1;
          saok: memcpy(s+0x1be,s+0x1be+(i<<9),64);
          }
          }
          else memclr(s+0x1be,64);
          }
          p=cdisk->list;
          while(p) {
          if (p->lpart) {
          ep=p->lpart;
          while(ep) {
          blk=ep->base;
          if (int13(0x42,cdisk->drive,ep->base,wsp1)) {printf("Error Reading Sector %lu in Cylinder %lu\n",ep->base,ep->base/p->heads/p->sectors);cdisk->err|=1;goto lp3;}
          if (enab==0) memcpy(wsp2,wsp1,512);
          memcpy(wsp1+0x1b4,ep->xp,10);
          for (i=0x1be;i<0x1fe;i++) wsp1[i]=0;
          wsp1[0x1fe]=0x55;wsp1[0x1ff]=0xaa;
          l=ep->start;ss=wsp1+0x1be;
          *(long *)(ss+8)=ep->start-ep->base;
          ss[1]=(l/p->sectors)%p->heads;
          ss[2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[1]+=(x>>4)&192;
          ss[3]=x;ss[2]+=(x>>2)&192;
          ss[4]=ep->type;
          l+=ep->len;
          *(long *)(ss+12)=ep->len;
          if ((ep->start&0xff000000)==mod40) {
          z=(ep->len+255)& -256;*(long *)(ss+12)=z<<16;
          if ((*(long *)(ss+12))==0) *(long *)(ss+12)= -1;
          ss[1]=p->heads-1;ss[2]=192+p->sectors;ss[3]=255;
          }
          l--;
          ss[5]=(l/p->sectors)%p->heads;
          ss[6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[5]+=(x>>4)&192;
          ss[7]=x;ss[6]+=(x>>2)&192;
          if (((l^ll)&0xfffffc00) || ((ep->start&0xff000000)==mod40)) {
          ss[5]=p->heads-1;ss[6]=192+p->sectors;ss[7]=255;
          }
          ep=ep->next;
          if (ep) {
          l=ep->base;ss=wsp1+0x1ce;
          *(long *)(ss+8)=ep->base-p->start;
          ss[1]=(l/p->sectors)%p->heads;
          ss[2]=(l%p->sectors)+1;
          x=ll=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[1]+=(x>>4)&192;
          ss[3]=x;ss[2]+=(x>>2)&192;
          ss[4]=5;
          l=ep->start+ep->len;
          *(long *)(ss+12)=l-ep->base;
          l--;
          ss[5]=(l/p->sectors)%p->heads;
          ss[6]=(l%p->sectors)+1;
          x=l=l/p->heads/p->sectors;
          if (xt) if (p->heads<=64)  ss[5]+=(x>>4)&192;
          ss[7]=x;ss[6]+=(x>>2)&192;
          if ((l^ll)&0xfffffc00) {ss[5]=p->heads-1;ss[6]=192+p->sectors;ss[7]=255;}
          }
          if (enab) {
          if (int13(0x43,cdisk->drive,blk,wsp1)) {printf("Error Writing Extended Chain Sector %lu in Cylinder %lu\n",blk,blk/cdisk->heads/cdisk->sectors);goto lp3;}
          }
          else {
          for (i=0;i<512;i++) if (wsp1[i]-wsp2[i]) printf("Sector %lxh Mismatch %x: %02x %02x\n",blk,i,wsp2[i],wsp1[i]);
          }
          }
          }
          p=p->next;
          }
          if (j>1) memcpy(s+(j<<9),rotdrv,512);
          if (enab) {
          for (i=0;i<=j;i++) if ((j>1) || (i<j)) {
          l=i;
          if (int13(0x43,cdisk->drive,l,s+(i<<9))) {printf("Error Writing Sector %lu\n",l);goto lp3;}
          }
          }
          p=cdisk->list;
          while(p) {
          if (p->valid&4) {
          k=1;
          if ((p->type==0xb) || (p->type==0xc)) k=9;
          for (i=0;i<k;i++) {
          if (enab) if (int13(0x43,cdisk->drive,p->start+i,s+(j<<9))) {printf("Error Writing Boot Blk Sector %lu in Cyl %lu\n",p->start+i,p->start/p->heads/p->sectors);goto lp3;}
          if (enab==0) printf("Erasing %lu\n",p->start+i);
          }
          }
          ep=p->lpart;
          while(ep) {
          if (ep->valid&4) {
          k=1;
          if ((ep->type==0xb) || (ep->type==0xc)) k=9;
          for (i=0;i<k;i++) {
          if (enab) if (int13(0x43,cdisk->drive,ep->start+i,s+(j<<9))) {printf("Error Writing Boot Blk Sector %lu in Cyl %lu\n",ep->start+i,ep->start/p->heads/p->sectors);goto lp3;}
          if (enab==0) printf("Erasing %lu\n",ep->start+i);
          }
          }
          ep=ep->next;
          }
          p=p->next;
          }
          if (enab) cdisk=0;
          else {
          l=k=(j+1)<<9;
          if (k==1024) k=512;
          for (i=0;i<k;i++) if (s[i]-s[i+l]) printf("Diff %x: %02x %02x\n",i,s[i+l],s[i]);
          printf("END DIAG LIST\n");
          }
lp3:      free(s);
          if (cdisk==0) {freed();goto start;}
          goto lp1;
#endif

case '@': if (cdisk->partsecs==1) {printf("Multi Boot Profile Not Enabled\n");goto lp1;}
          for (i=0;i<ovll;i++) cdisk->ovl[i]=0;
          i=ovll-1;j=cdisk->sectors;
          s=(char *)malloc(512);
          if (s==0) {printf("Not Enough Memory\n");goto lp;}
          for (l=cdisk->sectors-1;l>cdisk->partsecs+1;l--) {
          if (int13(0x42,cdisk->drive,l,s)) {printf("Error Reading Sector %lu\n",l);free(s);goto lp;}
          if ((*(int *)(s+0x1fe))==0x4c52) {
          if ((s[0x1fd]+l)>j) printf("WARNING - Damaged Overlay Skipped\n");
          if (i<=0) {printf("Overlay Table Overflowed\n");free(s);goto lp;}
          cdisk->ovl[i--]=l+1;j=l;
          }
          }
          free(s);goto lp;

default:  printf("Invalid Command\n");goto lp1;
};
nomem: printf("Not Enough Memory\n");return(20);
bad: printf("Missing Argument\n");goto lp1;
}

void build(disk,n,s)
struct drive *disk;
struct sector *s;
int n;
{
int i;
struct part *p;
for (i=0;i<4;i++) if (s->parts[i].esec) {
p=add(disk,n,&(s->parts[i]));
if (p) if ((s->parts[i].type==5) || (s->parts[i].type==15)) {
buildl(disk,p,s->parts[i].off,s->parts[i].off,s->parts[i].type);
}                                                                                         
}
}

void buildl(disk,p,o,e,b)
struct drive *disk;
struct part *p;
unsigned long o,e;
unsigned char b;
{
int i;
struct sector s2;
if (int13(0x42,disk->drive,o,&s2)) {printf("Error Reading Disk %u Sector %lu in Cylinder %lu\n",disk->drive-0x80,o,o/disk->heads/disk->sectors);disk->err|=1;return;}
for (i=0;i<4;i++) if (s2.parts[i].esec) {
if ((s2.parts[i].type-5) && (s2.parts[i].type-15)) {
addl(disk,p,o,&(s2.parts[i]),b,&(s2.xp));
}
}
for (i=0;i<4;i++) if (s2.parts[i].esec) {
if ((s2.parts[i].type==5) || (s2.parts[i].type==15)) {
buildl(disk,p,s2.parts[i].off+e,e,b);
}                                                                                         
}
}

struct part *add(disk,n,t)
struct drive *disk;
struct table *t;
int n;
{
int i;
long x;
struct part *p,*pp,*ppp;
struct sector s;
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
p->start=t->off;p->len=t->len;p->type=t->type;p->partsec[0]=n+1;
if ((p->start&0xff000000)==mod40) {
p->len=((p->len>>16)& -256)-(p->start&255);
if (p->len==0) p->len=0x1000000;
}
p->heads=t->ehead+1;p->sectors=t->esec&63;
if (t->act) p->active[0]=n+1;
if (p->start<disk->sectors) goto ng;
if (disk->list==0) {disk->list=p;goto chk;}
pp=disk->list;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;disk->list=p;goto chk;
}
ppp=0;
lp: if (pp->next) if (pp->next->start<=p->start) {pp=pp->next;goto lp;}

if ((p->type-5) && (p->type-15)) if (pp->lpart) {ppp=pp;pp=pp->lpart;goto lp;}
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);
i=0;
while(pp->partsec[i]) i++;
pp->partsec[i]=n+1;
if (t->act) {
i=0;
while(pp->active[i]) i++;
pp->active[i]=n+1;
}
return(0);
}
if (ov) if ((pp->start+pp->len)>p->start) if ((pp->type-5) && (pp->type-15)) goto overlap;
if (ppp) pp=ppp;
p->next=pp->next;pp->next=p;goto chk;
overlap: printf("Overlap on drive %02x\n",disk->drive);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n",p->partsec[0],p->type,p->start,p->start+p->len);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n\n",pp->partsec[0],pp->type,pp->start,pp->start+pp->len);
disk->err|=2;free(p);return(0);
ng: printf("Bad Partition on drive %02x  Range %02x - %08lx\n",disk->drive,disk->sectors,disk->length);
printf("Part=%2d Type=%02x Start=%08lx End=%08lx\n",p->partsec[0],p->type,p->start,p->start+p->len);
disk->err|=2;free(p);return(0);
chk: valid(disk,p);return(p);
}

void addl(disk,ep,o,t,b,xp)
struct drive *disk;
struct part *ep;
struct table *t;
unsigned long o;
unsigned char b,*xp;
{
int i;
long x;
struct part *p,*pp,*ppp;
struct sector s;
p=ppp=disk->list;
while(p) {
if (p->start==(t->off+o)) if (p->len==t->len)  if (p->type==t->type) {
if (p==ppp) disk->list=p->next;
else ppp->next=p->next;
p->next=0;goto extr;
}
ppp=p;p=p->next;
}
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
extr: p->start=t->off+o;p->len=t->len;p->base=o;p->btype=b;p->type=t->type;
if ((p->start&0xff000000)==mod40) {
p->len=((p->len>>16)& -256)-(p->start&255);
if (p->len==0) p->len=0x1000000;
}
p->heads=t->ehead+1;p->sectors=t->esec&63;memcpy(p->xp,xp,10);
if (p->start<ep->start) goto ng;
if ((p->start+p->len)>(ep->start+ep->len)) goto ng;
if (ep->lpart==0) {ep->lpart=p;goto chk;}
pp=ep->lpart;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;ep->lpart=p;goto chk;
}
lp: if (pp->next==0) goto fnd;
if (pp->next->start<p->start) {pp=pp->next;goto lp;}
if (ov) if ((pp->start+pp->len)>p->start) goto overlap;
fnd: p->next=pp->next;pp->next=p;goto chk; 
overlap: printf("Overlap on drive %02x\n",disk->drive);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n",p->type,p->start,p->start+p->len);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n\n",pp->type,pp->start,pp->start+pp->len);
disk->err|=2;free(p);return;
ng: printf("Bad Logical Partition on drive %02x\n",disk->drive);
printf("Logical Part Type=%02x Start=%08lx End=%08lx\n",p->type,p->start,p->start+p->len);
printf("Extend  Part Type=%02x Start=%08lx End=%08lx\n\n",ep->type,ep->start,ep->start+ep->len);
disk->err|=2;free(p);return;
chk: valid(disk,p);
}

void addx(disk,t,s,l,h)
int t,h;
unsigned long s,l;
struct drive *disk;
{
int i;
unsigned long j,k;
struct part *p,*pp,*ep;
i=0;
if (h || (s==0)) i=disk->sectors;
if (s<mod40) {
if (h==2) i+=(i&1) ? i : 1;
}
if (l<=(s+i)) {printf("Invalid End\n");return;}
p=(struct part *)calloc(sizeof(struct part),1);
if (p==0) {printf("Not Enough Memory\n");exit(20);}
p->base=s;s+=i;l-=s;
p->start=s;p->len=l;p->type=t;p->heads=disk->heads;p->sectors=disk->sectors;
if (p->start<disk->sectors) goto ng;
if ((p->start+p->len)>disk->length) printf("WARNING: Partition Goes Past End of Disk\n");
j=p->heads;k=p->sectors;
if (xt) if ((p->start+p->len)>(j*k<<10)) printf("WARNING: XT Format Partition Not Supported by DOS\n");
if (disk->list==0) {disk->list=p;goto chk1;}
pp=disk->list;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;disk->list=p;goto chk1;
}
lp: if (pp->next) if (pp->next->start<=p->start) {pp=pp->next;goto lp;}
if (ov) if (pp->next) if (pp->next->start<(p->start+p->len)) goto overlap;
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);printf("Partition Already Exists\n");return;
}
if ((pp->start+pp->len)>p->start) {
if ((pp->type-5) && (pp->type-15)) {
if (ov) goto overlap;
goto prim;
}
if (h==0) {p->start+=disk->sectors;p->len-=disk->sectors;}
p->btype=pp->type;ep=pp;
if (p->start<ep->start) goto ng;
if ((p->start+p->len)>(ep->start+ep->len)) goto ng;
if (ep->lpart==0) {ep->lpart=p;goto chke;}
pp=ep->lpart;
if (pp->start>p->start) {
if (ov) if ((p->start+p->len)>pp->start) goto overlap;
p->next=pp;ep->lpart=p;goto chke;
}
lpe: if (pp->next) if (pp->next->start<p->start) {pp=pp->next;goto lpe;}
if (ov) if (pp->next) if (pp->next->start<(p->start+p->len)) goto overlap;
if (p->start==pp->start) if (p->len==pp->len) if (p->type==pp->type) {
free(p);printf("Partition Already Exists\n");return;
}
if (ov) if ((pp->start+pp->len)>p->start) goto overlap;
p->next=pp->next;pp->next=p; 
chke: valid(disk,p);return;
}
prim: p->next=pp->next;pp->next=p;
chk1: if (disk->partsecs==1) p->partsec[0]=1;
chk: valid(disk,p);return;
ng: printf("Invalid Partition Parameters\n");free(p);return;
overlap: printf("Partition Overlaps Another\n");free(p);return;
}

void valid(disk,p)
struct drive *disk;
struct part *p;
{
struct sector s;
long i;
p->valid=0;
switch(p->type) {
case 1:
case 4:
case 6:
case 11:
case 12:
case 14: if (int13(0x42,disk->drive,p->start,&s)) printf("Error Reading Boot Blk on Disk %u Sector %lu in Cyl %lu\n",disk->drive-0x80,p->start,p->start/p->heads/p->sectors);
         if (s.tag-0xaa55) break;
         if (s.len==0) s.len=s.slen;
         p->valid=1;i=p->len;
         if ((p->start&0xff000000)==mod40) {i=(i+255)& -256;i<<=16;}
         if (s.len==i) {
         if (s.off==p->start) {
         if (p->btype==0) p->valid=2;
         if (p->btype==15) p->valid=2;
         if (p->btype==5) p->valid=3;
         }
         if (s.off==(p->start-p->base)) {
         if (p->btype==15) p->valid=3;
         if (p->btype==5) p->valid=2;
         }
         }
         break;
};
if (p->valid==0) if ((p->type==11) || (p->type==12)) {
for (i=1;i<9;i++) {
if (int13(0x42,disk->drive,p->start+i,&s)) printf("Error Reading Boot Sectors on Disk %u Sector %lu\n",disk->drive-0x80,p->start+i,p->start/p->heads/p->sectors);
if (s.tag==0xaa55) {p->valid=1;return;}
}
}
}

void overly(disk)
struct drive *disk;
{
char s[512];
int i,j;
long l;
for (i=0;i<ovll;i++) if (disk->ovl[i]) goto fnd;
return;
fnd: printf("\nOVERLAYS: ");
for (i=ovll-1;i>=0;i--) {
if ((l=disk->ovl[i])==0) {printf("\n\n");return;}
l--;
if (int13(0x42,disk->drive,l,&s)) printf("Error Reading Overlay Sector on Disk %u Sector %lu\n",disk->drive-0x80,l);
else {
if ((*(short *)(s+0x1fe))-0x4c52) printf(" UNK[%lu]",l);
else {
j=0x1fc;s[0x1fd]=0;
while (j && s[j]) j--;
printf(" %s",s+j+1);
}
}
}
printf(" **** Overlay Table Overflow\n\n");
}

char *fmt(s,d,x)
char *s;
struct drive *d;
unsigned long x;
{
unsigned long i,j,k;
if ((x&0xff000000)==mod40) {
i=(x>>16)&255;
j=(x>>8)&255;
k=d->sectors;
x&=255;
if (x==0) {sprintf(s,"%2ld:%03ld  ",i,j);return(s);}
if (x==k) {sprintf(s,"%2ld:%03ld+ ",i,j);return(s);}
k+=(k&1) ? k : 1;
if (x==k) {sprintf(s,"%2ld:%03ld++",i,j);return(s);}
sprintf(s,"%2ld:%03ld/%03ld ",i,j,x);return(s);
}
i=x/d->heads/d->sectors;j=i*d->heads*d->sectors;k=d->sectors;
if (x==j) {sprintf(s,"%6ld  ",i);return(s);}
if (x==(j+k)) {sprintf(s,"%6ld+ ",i);return(s);}
k+=(k&1) ? k : 1;
if (x==(j+k)) {sprintf(s,"%6ld++",i);return(s);}
sprintf(s,"%6ld/%03ld/%02ld ",i,(x-j)/d->sectors,((x-j)%d->sectors)+1);
return(s);
}

void show(dd)
struct drive *dd;
{
struct part *entry,*lg;
char *b,s1[16],s2[16],s3[16];
int h,a,aa,x;
long i,j,k;
h=x=0;
if (dd->length-0xffffffff) {
if ((dd->length&0xff000000)==mod40) {
printf("\nDrive=%2d Cyls=%lu Heads=%u Secs=%u SecLen=%u PartSecs=%u [",dd->drive-128,mod40/dd->heads/dd->sectors,dd->heads,dd->sectors,dd->seclen,dd->partsecs);
}
else printf("\nDrive=%2d Cyls=%lu Heads=%u Secs=%u SecLen=%u PartSecs=%u [",dd->drive-128,dd->length/dd->heads/dd->sectors,dd->heads,dd->sectors,dd->seclen,dd->partsecs);
}
else printf("\nDrive=%u Cyls=???? Heads=%3d Secs=%2d SecLen=%u PartSecs=%u [",dd->drive-128,dd->heads,dd->sectors,dd->seclen,dd->partsecs);
for (i=0;i<dd->partsecs;i++) {
if (dd->id[i]) printf("%c",dd->id[i]);
else {
if (dd->id0[i]) printf("%c",dd->id0[i]);
else printf(".");
}
}
post("K\n");
if (dd->partsecs>1) {printf("] Act= %c\n",dd->active);post("S %c\n",dd->active);}
else printf("]\n");
if ((dd->length&0xff000000)==mod40) {
a=(dd->length>>16)&255;aa=(dd->length>>8)&255;printf("ExtMBR   %d:%d\n",a,aa);
}
if (dd->length==0xfffffffe) printf("Drive Larger Than 2TiB - Use ExtMBR Option to Partition above 2TiB\n\n");
printf("\n");
if (dd->mb==4) printf("NOTICE: R. Loew Disk Boot Manager Installed\n");
else if (dd->mb>=2) printf("WARNING: Unrecognized, Obsolete or Corrupted MBR\n");
if ((dd->partsecs>1) && (dd->drive-128) && (dd->mb==3)) printf("WARNING: Multi Boot MBR Not Executable\n");
if ((dd->partsecs>1) && (dd->mb==0)) printf("WARNING: Multi Boot MBR Overwritten\n");
if ((dd->partsecs<2) && (dd->sig==0x4c52)) printf("WARNING: Multi Boot MBR with No Profiles\n");
if (((dd->length/dd->heads/dd->sectors)-dd->cylex) || (dd->heads-dd->hdex) || (dd->sectors-dd->secex)) {
if (mode==0) printf("CAUTION: INT13(48) Reports Cylinders=%lu Heads=%lu Sectors=%lu SecLen=%u\n",dd->cylex,dd->hdex,dd->secex,dd->seclen);
//i=1;
}
if (dd->sec8) {
if (((dd->cyl8<1024) && (dd->cyl8-dd->cyls)) || (dd->heads-dd->hd8) || (dd->sectors-dd->sec8)) {
if (mode==0) printf("CAUTION: INT13(8)  Reports Cylinders=%u Heads=%u Sectors=%u\n",dd->cyl8,dd->hd8,dd->sec8);
//i=1;
}
}
if (dd->fmtlen) if (dd->fmtlen-dd->seclen) printf("WARNING: Drive Partitioned Using %u Byte Sectors\n",dd->fmtlen);
if (dd->err&2) printf("WARNING: Overlapping Partitions Removed From List\n");
if (dd->err&1) printf("WARNING: Errors Reading Partition Information\n");
printf("\n");
entry=dd->list;
while (entry) {
i=entry->start/dd->heads/dd->sectors;
a=strlen(fmt(s1,dd,entry->start));
if (s1[a-1]=='+') {s1[a-1]=0;aa='+';}
else aa=32;
if (s1[a-2]=='+') {s1[a-2]=0;a='+';}
else a=32;
post("A %x %s %s %c%c\n",entry->type,s1,fmt(s2,dd,entry->start+entry->len),a,aa);
b=entry->partsec;
while (*b) post("L %x %s %c\n",entry->type,s1,dd->id[*(b++) -1]);
b=entry->active;
while (*b) post("T %x %s %c\n",entry->type,s1,dd->id[*(b++) -1]);
if (hide) if (i>=hide) {printf("*");h=1;goto skip;}
printf("Part  Type=%02x Start=%s End=%s",entry->type,fmt(s1,dd,entry->start),fmt(s2,dd,entry->start+entry->len));
switch(entry->valid) {
case 0: printf("      ");break;
case 1: printf("Inv   ");break;
case 2: printf("Valid ");break;
case 3: printf("DosOf ");break;
default: printf("ERASE!");
};
printf(" Pro= ");b=entry->partsec;
plp: printf("%c",dd->id[*(b++) -1]);
if (*b) goto plp;
printf("  Act= ");b=entry->active;
alp: printf("%c",dd->id[*(b++) -1]);
if (*b) goto alp;
printf("\n");
if ((entry->start&0xff000000)-mod40) if ((entry->heads-dd->heads) || (entry->sectors-dd->sectors)) printf("WARNING: Partition Geometry Set To %u Heads %u Sectors\n",entry->heads,entry->sectors);
if ((entry->start+entry->len)>dd->length) printf("WARNING: Partition Goes Past End Of Disk\n");
j=entry->heads;k=entry->sectors;
if (xt) if ((entry->start+entry->len)>(j*k<<10)) printf("WARNING: XT Format Partition Not Supported by DOS\n");
lg=entry->lpart;
if ((hide==0) && lg) {printf("*\n");goto skip;}
while(lg) {
i=lg->start/dd->heads/dd->sectors;
a=strlen(fmt(s1,dd,lg->start));
if (s1[a-1]=='+') {s1[a-1]=0;aa='+';}
else aa=32;
if (s1[a-2]=='+') {s1[a-2]=0;a='+';}
else a=32;
post("A %x %s %s %c%c\n",lg->type,s1,fmt(s2,dd,lg->start+lg->len),a,aa);
if (dd->next==0) x=lg->type;
if (hide) if (i>=hide) {printf("*");h=1;goto skip1;}
printf("LPart Type=%02x Start=%s End=%s",lg->type,fmt(s1,dd,lg->start),fmt(s2,dd,lg->start+lg->len));
switch(lg->valid) {
case 0: printf("      ");break;
case 1: printf("Inv   ");break;
case 2: printf("Valid ");break;
case 3: printf("DosOf ");break;
default: printf("ERASE!");
};
b=lg->partsec;
if ((*b) || (*lg->active)) {
printf(" PART: ");
printf(" Pro= ");
plp1: printf("%c",dd->id[*(b++) -1]);
if (*b) goto plp1;
b=lg->active;printf("  Act= ");
alp1: printf("%c",dd->id[*(b++) -1]);
if (*b) goto alp1;
}
printf("\n");
if ((lg->heads-dd->heads) || (lg->sectors-dd->sectors)) printf("WARNING: Partition Geometry Set To %u Heads %u Sectors\n",lg->heads,lg->sectors);
if ((lg->start+lg->len)>dd->length) printf("WARNING: Partition Goes Past End Of Disk\n");
j=lg->heads;k=lg->sectors;
if (xt) if ((lg->start+lg->len)>(j*k<<10)) printf("WARNING: XT Format Partition Not Supported by DOS\n");
skip1: lg=lg->next;
}
skip: entry=entry->next;
}
if (h) printf("\n");
overly(dd);
switch(x) {
case 0:
case 1:
case 4:
case 6:
case 0xb:
case 0xc:
case 0xe: return;
default: printf("\nWARNING: Last LPART on Last Drive NON-DOS\n");
};
}

void freed()
{
struct drive *d;
struct part *p,*p1,*e,*e1;
while(d=disks) {
disks=d->next;p=d->list;
while(p1=p) {
p=p->next;e=p1->lpart;
while(e1=e) {e=e->next;free(e1);}
free(p1);
}
free(d);
}
}

int free1(n)
struct part *n;
{
struct drive *d;
struct part *p,*p1,*e,*e1;
d=disks;
while(d) {
p=d->list;
if (n==p) {d->list=p->next;free(p);return(1);}
while(p) {
p1=p->next;
if (n==p1) {
while (e=p1->lpart) {p1->lpart=e->next;free(e);}
p->next=p1->next;free(p1);return(1);
}
e=p->lpart;
if (n==e) {p->lpart=e->next;free(e);return(1);}
while(e) {
e1=e->next;
if (n==e1) {e->next=e1->next;free(e1);return(1);}
e=e1;
}
p=p1;
}
d=d->next;
}
return(0);
}

struct part *find(d,t,s)
struct drive *d;
int t;
unsigned long s;
{
unsigned long ss;
struct part *p,*e;
ss=256;
if ((s&0xff000000)-mod40) {ss=d->heads*d->sectors;s*=ss;}
ss+=s;
p=d->list;
while(p) {
if (p->type==t) if ((p->start>=s) && (p->start<ss)) return(p);
e=p->lpart;
while(e) {
if (e->type==t) if ((e->start>=s) && (e->start<ss)) return(e);
e=e->next;
}
p=p->next;
}
return(0);
}

int cmpx(a,b,l)
char *a,*b;
int l;
{
while(l--) if (a[l]-b[l]) return(1);
return(0);
}

int post(a,b,c,d,e,f)
char *a,*b,*c,*d,*e,*f;
{
char x[64];
if (f1) {sprintf(x,a,b,c,d,e,f);write(f1,x,strlen(x));}
return(0);
}

void memclr(s,l)
char *s;
int l;
{
while(l--) *(s++)=0;
}

int int13(c,d,y,b)
int c,d;
unsigned long y,*b;
{
unsigned int j,k,l;
unsigned long x;
if (mode==1) {l=int13raw(c,d,0L,y,b);return(l);}
if (mode==3) {l=int13raw(c-0x40,d,0L,y,b);return(l);}
if (mode==2) c-=0x40;
if (c==8) {
x=int1308(d);
if (x==0) return(-1);
j=x&255;k=(x>>8)&255;
b[1]=(x>>16)&65535;b[2]=k;b[3]=j;b[4]=b[1]*b[2]*b[3];return(0);
}
if (c==0x48) return(int1348(d,b));
l=fint512(c,d,y,b,fb,32768);
if (l==0xfffe) {printf("CHS Out of Bounds ");return(-2);}
if (l) {
lock(0x84b,d+0x100,2);l=fint512(c,d,y,b,fb,32768);lock(0x86b,d+0x100,2);
}
return(l);
}

void lock(m,d,p)
int m,d,p;
{
asm {
push bx
push cx
push dx
mov ax,0x440d
mov bx,[d]
mov cx,[m]
mov dx,[p]
int 0x21
pop dx
pop cx
pop bx
}
}

int getnumx(s)
char *s;
{
char x[16];
if (s[0]=='0') if ((s[1]&0xdf)=='X') return(getnum(s));
x[0]='0';x[1]='x';strncpy(x+2,s,12);return(getnum(x));
}

long getnumz(s)
char *s;
{
unsigned long i,j;
i=0;
while(s[++i]) if (s[i]==':') goto fnd;
return(getnum(s));
fnd: if (mod40==0xffffffff) return(-1);
j=getnum(s+i+1);i=getnum(s);
if (((i|j)& -256)) return(-1);
if (i==0) if ((j<<24)<=mod40) return(-1);
return(mod40+(i<<16)+(j<<8));
}

int validate(l,m,s,e)
unsigned long m,s,e;
int l;
{
unsigned long i;
i=mod40/m;
if (s==0xffffffff) {printf("Partition Requires Extended MBR Enabled\n");return(1);}
if (s<mod40) if (s>i) goto bads;
if (l==1) return(0);
if (e==0xffffffff) goto bade;
if (e<mod40) if (e>i) goto bade;
if (l==2) if (s<mod40) if (e>mod40) goto badr;
if (e<s) goto badr;
if ((s<mod40) || (e<mod40) || (l==3)) return(0);
if (e<=(s+0x10000)) return(0);
badr: printf("Invalid Range\n");return(3);
bads: printf("Invalid Start\n");return(1);
bade: printf("Invalid End\n");return(2);
}
