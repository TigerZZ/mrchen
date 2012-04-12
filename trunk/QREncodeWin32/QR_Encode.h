
#include <math.h>
#include <string.h>



//���־���ȼ�
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// ����ģʽ
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

//�汾��
#define QR_VRESION_S	0 // 1~9
#define QR_VRESION_M	1 // 10~26
#define QR_VRESION_L		2 // 27~40

#define MAX_ALLCODEWORD	 3706 // �����������ֵ
#define MAX_DATACODEWORD 2956 // �����������ֵ���汾40-L��
#define MAX_CODEBLOCK	  153 // ģ���������������ֵ������RS���֣�
#define MAX_MODULESIZE	  177 //  ģ�������ֵ177*177

#define QR_MARGIN	4
#define min(a,b) (((a) < (b)) ? (a) : (b))

/////////////////////////////////////////////////////////////////////////////

typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;		// ����������
	int ncAllCodeWord;	// ��������
	int ncDataCodeWord;	// ����������(��������-����������)

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
//QRcode�汾��Ϣ
typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;	   // �汾��1-40
	int ncAllCodeWord; // ��������
	int ncDataCodeWord[4];	// �������֣�������-RS���֣�

	int ncAlignPoint;	// У������
	int nAlignPoint[6];	// У��ͼ����������

	RS_BLOCKINFO RS_BlockInfo1[4]; // �������Ϣ
	RS_BLOCKINFO RS_BlockInfo2[4]; // �������Ϣ

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR_Encode ��

class CQR_Encode
{
// ���캯��
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;		// ����ˮƽ
	int m_nVersion;		// �汾

	int m_nMaskingNo;	// ��Ĥ��ʽ
public:
	int m_nSymbleSize;
	unsigned char m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; 

private:
	int m_ncDataCodeWordBit; // ��������λ
	unsigned char m_byDataCodeWord[MAX_DATACODEWORD]; //��������
	int m_ncDataBlock;
	unsigned char m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord; // ������
	unsigned char m_byAllCodeWord[MAX_ALLCODEWORD]; 
	unsigned char m_byRSWork[MAX_CODEBLOCK]; 


public:
	int EncodeData(int nLevel, int nVersion, int bAutoExtent, int nMaskingNo, const char * lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, const char * lpsSource, int ncLength);//��ñ���汾
	int EncodeSourceData(const char * lpsSource, int ncLength, int nVerGroup);//����

	int GetBitLength(unsigned char nMode, int ncData, int nVerGroup);//���λ������

	int SetBitStream(int nIndex, unsigned short wData, int ncData);

	int IsNumeralData(unsigned char c);//�Ƿ�������
	int IsAlphabetData(unsigned char c);//�Ƿ�����ĸ
	int IsHanjiData(unsigned char c1, unsigned char c2);//�Ƿ���

	unsigned char AlphabetToBinaly(unsigned char c);//�ַ�-->����
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


