// stdafx.cpp : 只包括标准包含文件的源文件
// QRDecode.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


// QRcode相关信息

//版本信息，共40个
QR_VERSIONINFO QR_VersonInfo[] = {{0}, // Ver.0
{ 1, // Ver.1
26,   19,   16,   13,    9,//总码字数与四个数据码字
1,   14,   0,   0,   0,   0,   0,//校正点数与校正图形中心坐标
1,  26,  19,
1,  26,  16,
1,  26,  13,
1,  26,   9,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0},
{ 2, // Ver.2
44,   34,   28,   22,   16,
1,  18,   0,   0,   0,   0,   0,
1,  44,  34,
1,  44,  28,
1,  44,  22,
1,  44,  16,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0},
{ 3, // Ver.3
70,   55,   44,   34,   26,
1,  22,   0,   0,   0,   0,   0,
1,  70,  55,
1,  70,  44,
2,  35,  17,
2,  35,  13,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0},
{ 4, // Ver.4
100,   80,   64,   48,   36,
1,  26,   0,   0,   0,   0,   0,
1, 100,  80,
2,  50,  32,
2,  50,  24,
4,  25,   9,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0},
{ 5, // Ver.5
134,  108,   86,   62,   46,
1,  30,   0,   0,   0,   0,   0,
1, 134, 108,
2,  67,  43,
2,  33,  15,
2,  33,  11,
0,   0,   0,
0,   0,   0,
2,  34,  16,
2,  34,  12},
{ 6, // Ver.6
172,  136,  108,   76,   60,
1,  34,   0,   0,   0,   0,   0,
2,  86,  68,
4,  43,  27,
4,  43,  19,
4,  43,  15,
0,   0,   0,
0,   0,   0,
0,   0,   0,
0,   0,   0},
{ 7, // Ver.7
196,  156,  124,   88,   66,
2,  22,  38,   0,   0,   0,   0,
2,  98,  78,
4,  49,  31,
2,  32,  14,
4,  39,  13,
0,   0,   0,
0,   0,   0,
4,  33,  15,
1,  40,  14},
{ 8, // Ver.8
242,  194,  154,  110,   86,
2,  24,  42,   0,   0,   0,   0,
2, 121,  97,
2,  60,  38,
4,  40,  18,
4,  40,  14,
0,   0,   0,
2,  61,  39,
2,  41,  19,
2,  41,  15},
{ 9, // Ver.9
292,  232,  182,  132,  100,
2,  26,  46,   0,   0,   0,   0,
2, 146, 116,
3,  58,  36,
4,  36,  16,
4,  36,  12,
0,   0,   0,
2,  59,  37,
4,  37,  17,
4,  37,  13},
{10, // Ver.10
346,  274,  216,  154,  122,
2,  28,  50,   0,   0,   0,   0,
2,  86,  68,
4,  69,  43,
6,  43,  19,
6,  43,  15,
2,  87,  69,
1,  70,  44,
2,  44,  20,
2,  44,  16},
{11, // Ver.11
404,  324,  254,  180,  140,
2,  30,  54,   0,   0,   0,   0,
4, 101,  81,
1,  80,  50,
4,  50,  22,
3,  36,  12,
0,   0,   0,
4,  81,  51,
4,  51,  23,
8,  37,  13},
{12, // Ver.12
466,  370,  290,  206,  158,
2,  32,  58,   0,   0,   0,   0,
2, 116,  92,
6,  58,  36,
4,  46,  20,
7,  42,  14,
2, 117,  93,
2,  59,  37,
6,  47,  21,
4,  43,  15},
{13, // Ver.13
532,  428,  334,  244,  180,
2,  34,  62,   0,   0,   0,   0,
4, 133, 107,
8,  59,  37,
8,  44,  20,
12,  33,  11,
0,   0,   0,
1,  60,  38,
4,  45,  21,
4,  34,  12},
{14, // Ver.14
581,  461,  365,  261,  197,
3,  26,  46,  66,   0,   0,   0,
3, 145, 115,
4,  64,  40,
11,  36,  16,
11,  36,  12,
1, 146, 116,
5,  65,  41,
5,  37,  17,
5,  37,  13},
{15, // Ver.15
655,  523,  415,  295,  223,
3,  26,  48,  70,   0,   0,   0,
5, 109,  87,
5,  65,  41,
5,  54,  24,
11,  36,  12,
1, 110,  88,
5,  66,  42,
7,  55,  25,
7,  37,  13},
{16, // Ver.16
733,  589,  453,  325,  253,
3,  26,  50,  74,   0,   0,   0,
5, 122,  98,
7,  73,  45,
15,  43,  19,
3,  45,  15,
1, 123,  99,
3,  74,  46,
2,  44,  20,
13,  46,  16},
{17, // Ver.17
815,  647,  507,  367,  283,
3,  30,  54,  78,   0,   0,   0,
1, 135, 107,
10,  74,  46,
1,  50,  22,
2,  42,  14,
5, 136, 108,
1,  75,  47,
15,  51,  23,
17,  43,  15},
{18, // Ver.18
901,  721,  563,  397,  313,
3,  30,  56,  82,   0,   0,   0,
5, 150, 120,
9,  69,  43,
17,  50,  22,
2,  42,  14,
1, 151, 121,
4,  70,  44,
1,  51,  23,
19,  43,  15},
{19, // Ver.19
991,  795,  627,  445,  341,
3,  30,  58,  86,   0,   0,   0,
3, 141, 113,
3,  70,  44,
17,  47,  21,
9,  39,  13,
4, 142, 114,
11,  71,  45,
4,  48,  22,
16,  40,  14},
{20, // Ver.20
1085,  861,  669,  485,  385,
3,  34,  62,  90,   0,   0,   0,
3, 135, 107,
3,  67,  41,
15,  54,  24,
15,  43,  15,
5, 136, 108,
13,  68,  42,
5,  55,  25,
10,  44,  16},
{21, // Ver.21
1156,  932,  714,  512,  406,
4,  28,  50,  72,  94,   0,   0,
4, 144, 116,
17,  68,  42,
17,  50,  22,
19,  46,  16,
4, 145, 117,
0,   0,   0,
6,  51,  23,
6,  47,  17},
{22, // Ver.22
1258, 1006,  782,  568,  442,
4,  26,  50,  74,  98,   0,   0,
2, 139, 111,
17,  74,  46,
7,  54,  24,
34,  37,  13,
7, 140, 112,
0,   0,   0,
16,  55,  25,
0,   0,   0},
{23, // Ver.23
1364, 1094,  860,  614,  464,
4,  30,  54,  78, 102,   0,   0,
4, 151, 121,
4,  75,  47,
11,  54,  24,
16,  45,  15,
5, 152, 122,
14,  76,  48,
14,  55,  25,
14,  46,  16},
{24, // Ver.24
1474, 1174,  914,  664,  514,
4,  28,  54,  80, 106,   0,   0,
6, 147, 117,
6,  73,  45,
11,  54,  24,
30,  46,  16,
4, 148, 118,
14,  74,  46,
16,  55,  25,
2,  47,  17},
{25, // Ver.25
1588, 1276, 1000,  718,  538,
4,  32,  58,  84, 110,   0,   0,
8, 132, 106,
8,  75,  47,
7,  54,  24,
22,  45,  15,
4, 133, 107,
13,  76,  48,
22,  55,  25,
13,  46,  16},
{26, // Ver.26
1706, 1370, 1062,  754,  596,
4,  30,  58,  86, 114,   0,   0,
10, 142, 114,
19,  74,  46,
28,  50,  22,
33,  46,  16,
2, 143, 115,
4,  75,  47,
6,  51,  23,
4,  47,  17},
{27, // Ver.27
1828, 1468, 1128,  808,  628,
4,  34,  62,  90, 118,   0,   0,
8, 152, 122,
22,  73,  45,
8,  53,  23,
12,  45,  15,
4, 153, 123,
3,  74,  46,
26,  54,  24,
28,  46,  16},
{28, // Ver.28
1921, 1531, 1193,  871,  661,
5,  26,  50,  74,  98, 122,   0,
3, 147, 117,
3,  73,  45,
4,  54,  24,
11,  45,  15,
10, 148, 118,
23,  74,  46,
31,  55,  25,
31,  46,  16},
{29, // Ver.29
2051, 1631, 1267,  911,  701,
5,  30,  54,  78, 102, 126,   0,
7, 146, 116,
21,  73,  45,
1,  53,  23,
19,  45,  15,
7, 147, 117,
7,  74,  46,
37,  54,  24,
26,  46,  16},
{30, // Ver.30
2185, 1735, 1373,  985,  745,
5,  26,  52,  78, 104, 130,   0,
5, 145, 115,
19,  75,  47,
15,  54,  24,
23,  45,  15,
10, 146, 116,
10,  76,  48,
25,  55,  25,
25,  46,  16},
{31, // Ver.31
2323, 1843, 1455, 1033,  793,
5,  30,  56,  82, 108, 134,   0,
13, 145, 115,
2,  74,  46,
42,  54,  24,
23,  45,  15,
3, 146, 116,
29,  75,  47,
1,  55,  25,
28,  46,  16},
{32, // Ver.32
2465, 1955, 1541, 1115,  845,
5,  34,  60,  86, 112, 138,   0,
17, 145, 115,
10,  74,  46,
10,  54,  24,
19,  45,  15,
0,   0,   0,
23,  75,  47,
35,  55,  25,
35,  46,  16},
{33, // Ver.33
2611, 2071, 1631, 1171,  901,
5,  30,  58,  86, 114, 142,   0,
17, 145, 115,
14,  74,  46,
29,  54,  24,
11,  45,  15,
1, 146, 116,
21,  75,  47,
19,  55,  25,
46,  46,  16},
{34, // Ver.34
2761, 2191, 1725, 1231,  961,
5,  34,  62,  90, 118, 146,   0,
13, 145, 115,
14,  74,  46,
44,  54,  24,
59,  46,  16,
6, 146, 116,
23,  75,  47,
7,  55,  25,
1,  47,  17},
{35, // Ver.35
2876, 2306, 1812, 1286,  986,
6,  30,  54,  78, 102, 126, 150,
12, 151, 121,
12,  75,  47,
39,  54,  24,
22,  45,  15,
7, 152, 122,
26,  76,  48,
14,  55,  25,
41,  46,  16},
{36, // Ver.36
3034, 2434, 1914, 1354, 1054,
6,  24,  50,  76, 102, 128, 154,
6, 151, 121,
6,  75,  47,
46,  54,  24,
2,  45,  15,
14, 152, 122,
34,  76,  48,
10,  55,  25,
64,  46,  16},
{37, // Ver.37
3196, 2566, 1992, 1426, 1096,
6,  28,  54,  80, 106, 132, 158,
17, 152, 122,
29,  74,  46,
49,  54,  24,
24,  45,  15,
4, 153, 123,
14,  75,  47,
10,  55,  25,
46,  46,  16},
{38, // Ver.38
3362, 2702, 2102, 1502, 1142,
6,  32,  58,  84, 110, 136, 162,
4, 152, 122,
13,  74,  46,
48,  54,  24,
42,  45,  15,
18, 153, 123,
32,  75,  47,
14,  55,  25,
32,  46,  16},
{39, // Ver.39
3532, 2812, 2216, 1582, 1222,
6,  26,  54,  82, 110, 138, 166,
20, 147, 117,
40,  75,  47,
43,  54,  24,
10,  45,  15,
4, 148, 118,
7,  76,  48,
22,  55,  25,
67,  46,  16},
{40, // Ver.40
3706, 2956, 2334, 1666, 1276,
6,  30,  58,  86, 114, 142, 170,
19, 148, 118,
18,  75,  47,
34,  54,  24,
20,  45,  15,
6, 149, 119,
31,  76,  48,
34,  55,  25,
61,  46,  16}
};

//版本信息纠错信息
int VersionInfoBit[] = {
    0x07C94,0x085BC,0x09A99,0x0A4D3,0x0BBF6,0x0C762,0x0D847,
    0x0E60D,0x0F928,0x10B78,0x1145D,0x12A17,0x13532,0x149A6,
    0x15683,0x168C9,0x177EC,0x18EC4,0x191E1,0x1AFAB,0x1B08E,
    0x1CC1A,0x1D33F,0x1ED75,0x1F250,0x209D5,0x216F0,0x228BA,
    0x2379F,0x24B0B,0x2542E,0x26A64,0x27541,0x28C69
};
//格式信息纠错信息
int FormatInfoBit[] = {
    0x0000,0x0537,0x0a6e,0x0f59,0x11eb,0x14dc,0x1b85,0x1eb2,
    0x23d6,0x26e1,0x29b8,0x2c8f,0x323d,0x370a,0x3853,0x3d64,
    0x429b,0x47ac,0x48f5,0x4dc2,0x5370,0x5647,0x591e,0x5c29,
    0x614d,0x647a,0x6b23,0x6e14,0x70a6,0x7591,0x7ac8,0x7fff
};

// 字符数位长指示(版本组（S, M, L）)
extern int nIndicatorLenNumeral[]  = {10, 12, 14};
extern int nIndicatorLenAlphabet[] = { 9, 11, 13};
extern int nIndicatorLen8Bit[]	   = { 8, 16, 16};
extern int nIndicatorLenHanzi[]	   = { 8, 10, 12};