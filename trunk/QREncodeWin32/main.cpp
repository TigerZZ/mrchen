#include <stdio.h>
#include <afxwin.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "QR_Encode.h"


int m_bDataEncoded;//�Ƿ��Ѿ�����
int nLevel = 0;
int nVersion = 0;
int bAutoExtent = 1;   // ֻ�����
int nMaskingNo   =  -1; // ֻ�����

int **resize(unsigned char p[177][177], int m,int n)//mΪԭʼͼ���С,nΪ�Ŵ�Ĵ�С
{
int **temp;
	int x,y;
	temp = (int **)malloc(n*m*sizeof(int));//Ĭ����������
	memset(temp,0,n*m*sizeof(int));
	for (int i =0 ; i < n*m; i++)
	{
		temp[i] = (int*)malloc(n*m*sizeof(int));
		memset(temp[i],0, n*m*sizeof(int));
	}
	for (int i = 0 ; i < m; i++)
	{
		for (int j= 0 ; j < m; j ++)
		{
			if (p[i][j] == 0)
			{
				for (x = 0; x < n; x++)
				{
					for (y = 0; y < n; y++)
					{
						temp[n*i+x][n*j+y] = 0;
					}
				}
			}
			else
				if (p[i][j] == 1)
			{

				for (x = 0; x < n; x++)
				{
					for (y = 0; y < n; y++)
					{
						temp[n*i+x][n*j+y] = 255;
					}
				}
			}
		}
		
	}
	//for (int i = 0 ; i < n*m; i++)
	//{
	//	for (int j= 0 ; j < n*m; j ++)
	//	{
	//		printf("%u",temp[i][j]);
	//	}
	//	printf("\n");
	//}
	return temp;
}
void SetBmpInfoHeader(PBITMAPINFOHEADER pbmpih,int h, int w)
{
	
	pbmpih->biSize          = 40;
	/* 18~21: λͼ�Ŀ�ȣ�������pixelΪ��λ�� */
	pbmpih->biWidth         = w;  
	/* 22~25: λͼ�ĸ߶� */
	pbmpih->biHeight        = h;  
	/* 26~27: Ŀ���豸�ļ���, �̶�ֵ��1 */
	pbmpih->biPlanes        = 1;   
	/* 28~29: һ��������ռbit���� �����ǣ�1��˫ɫ����4��16ɫ����8��256ɫ��
	��16��65536ɫ����24�����ɫ2^24����ɫ����32�����ɫ2^32����ɫ�����������MSDN��
	����24λ���ɫλͼ�� һ������ռ�������ֽ�,��24 bits */
	pbmpih->biBitCount      = 24;   
	/* 30~33��ָ���Ƿ�ѹ���� �����ѹ���ˣ����õ�ѹ����ʽ��
	����Ϊ�� BI_RGB��BI_RLE4��BI_RLE8��BI_BITFIELDS��BI_PNG��BI_JPEG
	�е�λͼ������γ̳��ȱ��룺BI_RLE4��BI_RLE8 
	ѹ�����Խ�ʡ�ռ䣬 �������ڱ�̶�д��BI_RGB��ʾ������ѹ������ */
	pbmpih->biCompression  = BI_RGB; 
	/* 34~37: λͼ��������ռ�ֽ������й̶��ļ��㹫ʽ */
	pbmpih->biSizeImage     = ((((pbmpih->biWidth * pbmpih->biBitCount) + 31) & ~31) / 8) * pbmpih->biHeight;
	/* 38~41: λͼˮƽ�ֱ��ʣ�ÿ�������� */
	pbmpih->biXPelsPerMeter = 0L;
	/* 42~45: λͼ��ֱ�ֱ��ʣ�ÿ�������� */
	pbmpih->biYPelsPerMeter = 0L;
	/* 46~49: λͼʵ��ʹ����ɫ������ɫ���������е�ɫ���λͼ��˵ʵ�����ǵ�ɫ������ɫ������
	24λ���ɫλͼ����Ҫ��ɫ�壬 ��Ϊ0�� 8λ�Ҷ�λͼΪ256��2^8����ɫ���� */
	pbmpih->biClrUsed      = 0;      
	/* 50~53: ��ʾλͼ������ɫ�� */
	pbmpih->biClrImportant = 0L;      
}

void SetBmpFileHeader(PBITMAPFILEHEADER pbmpfh, const PBITMAPINFOHEADER pbmpih)
{
	/* 0~1: �̶�ֵ�� "BM"����0x4D42��������������λͼ��һ����bmpΪ�ļ�����׺��*/
	pbmpfh->bfType      = *(WORD *)"BM"; 
	/* 2~5: λͼ�ļ��ܴ�С��ռ�����ֽ����� �����ļ�ͷ����Ϣͷ����ɫ�塢λͼ������ռ���ֽ�����*/
	pbmpfh->bfSize      = pbmpih->biSizeImage + 54 + pbmpih->biClrUsed * sizeof(RGBQUAD);     
	/* 6~7: �̶�ֵ0�� Ŀǰûʲô�ã� ��������������չ��Ҳ�еĽṹ����������������Ϊ���ڴ���� */
	pbmpfh->bfReserved1 = 0;   
	/* 8~9: �̶�ֵ */
	pbmpfh->bfReserved2 = 0;    
	/* 10~13: λͼ��������ʼλ�ã� ���㷽��Ϊ��
	λͼ�ļ�ͷ14���ֽ�+λͼ��Ϣͷ40���ֽ�+λͼ��ɫ����ռ�ֽ����� 
	����Ҫ��������һ��24λλͼ���޵�ɫ�壩��������Ϊ54 Ҳ���ԡ�*/
	pbmpfh->bfOffBits   = 54 + pbmpih->biClrUsed * sizeof(RGBQUAD);     
}
unsigned char *bitSrtream(const char *src,int *length,int m){//m��ʾ�Ŵ���
	//int m = 5;
	struct COLOR 
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
	};
	struct COLOR  white ={255,255,255};
	struct COLOR  black ={0,0,0};
	int i,j;
	CQR_Encode* pQR_Encode = new CQR_Encode;
	m_bDataEncoded = pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo,src );

	int **q = resize(pQR_Encode->m_byModuleData,pQR_Encode->m_nSymbleSize,m);

	int w = pQR_Encode->m_nSymbleSize*m;
	int h  = pQR_Encode->m_nSymbleSize*m;
	//for (int i = 0 ; i < h; i++)
	//{
	//	for (int j= 0 ; j < w; j ++)
	//	{
	//		printf("%u",q[i][j]);
	//	}
	//	printf("\n");
	//}
	BITMAPINFOHEADER info_head;//�ֽ�
	BITMAPFILEHEADER file_head;//14�ֽ�
	SetBmpInfoHeader(&info_head,h,w);
	SetBmpFileHeader(&file_head,&info_head);
	unsigned char * temp = (unsigned char *)malloc(file_head.bfSize);
	*length = file_head.bfSize;
	BITMAPFILEHEADER file;
	BITMAPINFOHEADER info;
	memset(temp,0,file_head.bfSize);	
	memcpy(temp,&file_head,14);
	memcpy(&file,temp,14);
	temp+=14;
	memcpy(temp,&info_head,40);
	memcpy(&info,temp,40);
	temp += 40;
	for(i = 0 ; i < h;i++){
		for(j = 0 ;j < w;j++){
			if(q[i][j]== 255){				
					memcpy(temp,&black,3);
					temp+=3;
			}
			else  if (q[i][j] == 0)
			{
				memcpy(temp,&white,3);
				temp+=3;
			}
		}
	int fillbits = ( 4 - (w * 3 ) % 4 ) % 4;
	int fill = 0;
	memcpy(temp,&fill,fillbits);
	temp+= fillbits;
	}
	temp -= file_head.bfSize;
return temp;
}
int main()
{
	//char *dstBMp = "dst.bmp";
	//char *src = "www.baidu.com";
	//struct COLOR 
	//{
	//	unsigned char B;
	//	unsigned char G;
	//	unsigned char R;
	//};
	//struct COLOR  white ={255,255,255};
	//struct COLOR  black ={0,0,0};
	//int i,j;
	// fpos_t pos = 0;
	//CQR_Encode* pQR_Encode = new CQR_Encode;
	//m_bDataEncoded = pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo,src );
	//int w = pQR_Encode->m_nSymbleSize;
	//int h  = pQR_Encode->m_nSymbleSize;
	//BITMAPINFOHEADER info_head;//�ֽ�
	//BITMAPFILEHEADER file_head;//14�ֽ�
	//SetBmpInfoHeader(&info_head,h,w);
	//SetBmpFileHeader(&file_head,&info_head);
	//int fillbits = ( 4 - (w * 3 ) % 4 ) % 4;
	//unsigned char  fillbit = 0;
	//FILE *outBmp;
	//outBmp = fopen(dstBMp,"wb");//��д�򿪻����½�һ���������ļ�
	// fwrite(&file_head,sizeof(file_head),1,outBmp);
	// fwrite(&info_head,sizeof(info_head),1,outBmp);
	//
	//
	// fgetpos(outBmp,&pos);

	//for(i = 0 ; i < w;i++){
	//	for(j = 0 ;j < w;j++){
	//		if(pQR_Encode->m_byModuleData[i][j] == 1){
	//				fwrite(&black,3,1,outBmp);
	//		}
	//		else  if (pQR_Encode->m_byModuleData[i][j] == 0)
	//		{
	//			fwrite(&white,3,1,outBmp);
	//		}
	//	}
	//	fwrite(&fillbit,1,1,outBmp);
	//}
	//fclose(outBmp);

	////system("mspaint dst.bmp");
	int length = 0;
	unsigned char * p = bitSrtream("www.baidu.com",&length,10);
	char *dstBMp = "dst.bmp";
	FILE *outBmp;
	outBmp = fopen(dstBMp,"wb");//��д�򿪻����½�һ���������ļ�
	fwrite(p,length,1,outBmp);
	fclose(outBmp);
	system("mspaint dst.bmp");
	return 0;
}