#include <stdio.h>
#include <afxwin.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "QR_Encode.h"


int m_bDataEncoded;//是否已经编码
int nLevel = 0;
int nVersion = 0;
int bAutoExtent = 1;   // 只用这个
int nMaskingNo   =  -1; // 只用这个

int **resize(unsigned char p[177][177], int m,int n)//m为原始图像大小,n为放大的大小
{
int **temp;
	int x,y;
	temp = (int **)malloc(n*m*sizeof(int));//默认扩大两倍
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
	/* 18~21: 位图的宽度（以像素pixel为单位） */
	pbmpih->biWidth         = w;  
	/* 22~25: 位图的高度 */
	pbmpih->biHeight        = h;  
	/* 26~27: 目标设备的级别, 固定值：1 */
	pbmpih->biPlanes        = 1;   
	/* 28~29: 一个像素所占bit数， 可以是：1（双色）、4（16色）、8（256色）
	、16（65536色）、24（真彩色2^24种颜色）、32（真彩色2^32种颜色），具体参阅MSDN。
	对于24位真彩色位图， 一个像素占用三个字节,即24 bits */
	pbmpih->biBitCount      = 24;   
	/* 30~33：指定是否压缩， （如果压缩了）采用的压缩格式。
	可以为： BI_RGB、BI_RLE4、BI_RLE8、BI_BITFIELDS、BI_PNG、BI_JPEG
	有的位图会进行游程长度编码：BI_RLE4、BI_RLE8 
	压缩可以节省空间， 但不便于编程读写。BI_RGB表示不进行压缩处理 */
	pbmpih->biCompression  = BI_RGB; 
	/* 34~37: 位图数据区所占字节数，有固定的计算公式 */
	pbmpih->biSizeImage     = ((((pbmpih->biWidth * pbmpih->biBitCount) + 31) & ~31) / 8) * pbmpih->biHeight;
	/* 38~41: 位图水平分辨率，每米像素数 */
	pbmpih->biXPelsPerMeter = 0L;
	/* 42~45: 位图垂直分辨率，每米像素数 */
	pbmpih->biYPelsPerMeter = 0L;
	/* 46~49: 位图实际使用颜色表中颜色数（对于有调色板的位图来说实际上是调色板中颜色项数，
	24位真彩色位图不需要调色板， 设为0， 8位灰度位图为256（2^8种颜色）。 */
	pbmpih->biClrUsed      = 0;      
	/* 50~53: 显示位图所需颜色数 */
	pbmpih->biClrImportant = 0L;      
}

void SetBmpFileHeader(PBITMAPFILEHEADER pbmpfh, const PBITMAPINFOHEADER pbmpih)
{
	/* 0~1: 固定值： "BM"（或0x4D42），即表明这是位图（一般以bmp为文件名后缀）*/
	pbmpfh->bfType      = *(WORD *)"BM"; 
	/* 2~5: 位图文件总大小（占用总字节数， 包括文件头、信息头、调色板、位图数据区占用字节数）*/
	pbmpfh->bfSize      = pbmpih->biSizeImage + 54 + pbmpih->biClrUsed * sizeof(RGBQUAD);     
	/* 6~7: 固定值0： 目前没什么用， 可能留作将来扩展。也有的结构体中有这样的域是为了内存对齐 */
	pbmpfh->bfReserved1 = 0;   
	/* 8~9: 固定值 */
	pbmpfh->bfReserved2 = 0;    
	/* 10~13: 位图数据区起始位置， 计算方法为：
	位图文件头14个字节+位图信息头40个字节+位图调色板所占字节数， 
	这里要创建的是一张24位位图（无调色板），故设置为54 也可以。*/
	pbmpfh->bfOffBits   = 54 + pbmpih->biClrUsed * sizeof(RGBQUAD);     
}
unsigned char *bitSrtream(const char *src,int *length,int m){//m表示放大倍数
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
	BITMAPINFOHEADER info_head;//字节
	BITMAPFILEHEADER file_head;//14字节
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
	//BITMAPINFOHEADER info_head;//字节
	//BITMAPFILEHEADER file_head;//14字节
	//SetBmpInfoHeader(&info_head,h,w);
	//SetBmpFileHeader(&file_head,&info_head);
	//int fillbits = ( 4 - (w * 3 ) % 4 ) % 4;
	//unsigned char  fillbit = 0;
	//FILE *outBmp;
	//outBmp = fopen(dstBMp,"wb");//可写打开或者新建一个二进制文件
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
	outBmp = fopen(dstBMp,"wb");//可写打开或者新建一个二进制文件
	fwrite(p,length,1,outBmp);
	fclose(outBmp);
	system("mspaint dst.bmp");
	return 0;
}