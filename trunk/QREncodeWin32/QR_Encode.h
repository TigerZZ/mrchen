
#include <math.h>
#include <string.h>



//四种纠错等级
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// 编码模式
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

//版本组
#define QR_VRESION_S	0 // 1~9
#define QR_VRESION_M	1 // 10~26
#define QR_VRESION_L		2 // 27~40

#define MAX_ALLCODEWORD	 3706 // 码字总数最大值
#define MAX_DATACODEWORD 2956 // 数据码字最大值（版本40-L）
#define MAX_CODEBLOCK	  153 // 模块数据码字数最大值（包括RS码字）
#define MAX_MODULESIZE	  177 //  模块数最大值177*177

#define QR_MARGIN	4
#define min(a,b) (((a) < (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////////////////////

typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// 纠错码字输
	int ncAllCodeWord;	// 总码字数
	int ncDataCodeWord;	// 数据码字数(总码字数-纠错码字数)

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
//QRcode版本信息
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // 版本号1-40
	int ncAllCodeWord; // 总码字数
	int ncDataCodeWord[4];	// 数据码字（总码字-RS码字）

	int ncAlignPoint;	// 校正点数
	int nAlignPoint[6];	// 校正图形中心坐标

	RS_BLOCKINFO RS_BlockInfo1[4]; // 纠错块信息
	RS_BLOCKINFO RS_BlockInfo2[4]; // 纠错块信息

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR_Encode 类

class CQR_Encode
{
// 构造函数
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// 纠错水平
	int m_nVersion;		// 版本

	int m_nMaskingNo;	// 掩膜方式
public:
	int m_nSymbleSize;
	unsigned char m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; 

private:
	int m_ncDataCodeWordBit; // 数据码字位
	unsigned char m_byDataCodeWord[MAX_DATACODEWORD]; //数据码字
	int m_ncDataBlock;
	unsigned char m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // 总码字
	unsigned char m_byAllCodeWord[MAX_ALLCODEWORD]; 
	unsigned char m_byRSWork[MAX_CODEBLOCK]; 


public:
	int EncodeData(int nLevel, int nVersion, int bAutoExtent, int nMaskingNo, const char * lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, const char * lpsSource, int ncLength);//获得编码版本
	int EncodeSourceData(const char * lpsSource, int ncLength, int nVerGroup);//编码

	int GetBitLength(unsigned char nMode, int ncData, int nVerGroup);//获得位流长度

	int SetBitStream(int nIndex, unsigned short wData, int ncData);

	int IsNumeralData(unsigned char c);//是否是数字
	int IsAlphabetData(unsigned char c);//是否是字母
	int IsHanjiData(unsigned char c1, unsigned char c2);//是否汉字

	unsigned char AlphabetToBinaly(unsigned char c);//字符-->数字
	unsigned short KanjiToBinaly(unsigned short wc);
	void GetRSCodeWord(unsigned char *lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

private:
	void FormatModule();
	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};


