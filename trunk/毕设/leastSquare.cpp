#include "cv.h"
#include "highgui.h"
#include <vector>
#include <stdio.h>
#include <math.h>
#include<time.h>

#include<windows.h>
using std::vector;
/************************************************************************/
/* 全局函数                                                                     */
/************************************************************************/
#define  UP 1
#define  DOWN 2
#define  LEFT 3
#define  RIGHT 4

IplImage *src;
IplImage *src1;
IplImage *grayImage;//gray Image
IplImage *tempImage;//temp Image
IplImage *BinaryImage;//Bool Image
IplImage *XAxis;//Sobel算子之后的X方向分量
IplImage *YAxis;//Sobel算子之后的Y方向分量
const char *SrcWindowName = "src";
const char *DstWindowName="dst";

struct  LinePoint
{
	CvPoint upLinePoint[2];
	CvPoint downLinePoint[2];
	CvPoint leftLinePoint[2];
	CvPoint rightLinePoint[2];
} linepoint;

/************************************************************************/
/*                                  函数                           */
/************************************************************************/

void leastSquare(CvMat *mat1, CvMat *mat2, double* k, double* b);
bool floatBigThanZero(float m);
void showTempImage(vector<CvPoint> p1);
void initMat(CvMat *mat1, CvMat *mat2,vector<CvPoint> p);
void deleteElement(vector<CvPoint> *p, double k, double b, int flag);
void LeastSquaresIterat(CvMat *mat1, CvMat *mat2, vector<CvPoint> *p, double *k, double*b,int iterateTimes , int flag);
void getWhichEdge(vector<CvPoint>  *Position, IplImage *image, int flag);

CvPoint getPoint(double vk ,double vb, double hk,double hb);
/************************************************************************/
/* 主函数                                                                     */
/************************************************************************/
int main(int argc, char* argv[])
{
	cvNamedWindow(DstWindowName);
	cvNamedWindow(SrcWindowName);
	CvPoint p1,p2;
	double K[4] = {0};
	double B[4]={0};
	CvPoint vertex[4];
	double k = 0;//斜率
	double b = 0;//截距
	//src1 = cvLoadImage(str,1);//读入图像，彩色的方式
	src1 = cvLoadImage("待处理图片01.bmp",1);
		//src1 = cvLoadImage("C:\\Users\\mrchen\\Desktop\\test1.bmp",1);
	src = cvCreateImage(cvSize(400,400),src1->depth,src1->nChannels);
	cvResize(src1,src);
	grayImage = cvCreateImage(cvSize(src->width,src->height),src->depth,1);
	BinaryImage = cvCreateImage(cvSize(src->width,src->height),src->depth,1);//Bool Image
	int h = src->height;
	int w = src->width;
	cvSmooth(src,src,CV_MEDIAN,3,0,0,0);//用中值滤波平滑图像
	cvCvtColor(src,grayImage,CV_RGB2GRAY);//转为灰度图
	cvThreshold(grayImage,BinaryImage,NULL,255,CV_THRESH_OTSU);
	cvMorphologyEx(BinaryImage,BinaryImage,NULL,NULL,CV_MOP_OPEN,15);
	cvCanny(BinaryImage,grayImage,50,10);//获得轮廓

	//UP
	std::vector<CvPoint>  Position;//表示图像上点的坐标
	getWhichEdge(&Position,grayImage,UP);
	CvMat* mat1=cvCreateMat(1,Position.size(),CV_64FC1);//x
	CvMat* mat2=cvCreateMat(1,Position.size(),CV_64FC1);//y
	LeastSquaresIterat(mat1,mat2,&Position,&k,&b,6,UP);
	Position.clear();
	p1 = cvPoint(0,cvRound(b));
	p2 = cvPoint(w,cvRound(w*k+b));
	K[0] = k;
	B[0] = b;
	linepoint.upLinePoint[0] = p1;
	linepoint.upLinePoint[1] = p2;
	//DOWN
	getWhichEdge(&Position,grayImage,DOWN);
	LeastSquaresIterat(mat1,mat2,&Position,&k,&b,3,DOWN);
	Position.clear();
	p1 = cvPoint(0,cvRound(b));
	p2 = cvPoint(w,cvRound(w*k+b));
	K[1] = k;
	B[1] = b;
	linepoint.downLinePoint[0] = p1;
	linepoint.downLinePoint[1] = p2;
	//LEFT
	getWhichEdge(&Position,grayImage,LEFT);
	LeastSquaresIterat(mat1,mat2,&Position,&k,&b,3,LEFT);
	Position.clear();
	p1 = cvPoint(cvRound(b),0);
	p2 = cvPoint(cvRound(h*k+b),h);
	K[2] = k;
	B[2] = b;
	linepoint.leftLinePoint[0] = p1;
	linepoint.leftLinePoint[1] = p2;
	//RIGHT
	getWhichEdge(&Position,grayImage,RIGHT);
	LeastSquaresIterat(mat1,mat2,&Position,&k,&b,3,RIGHT);
	Position.clear();
	p1 = cvPoint(cvRound(b),0);
	p2 = cvPoint(cvRound(h*k+b),h);
	K[3] = k;
	B[3] = b;
	linepoint.rightLinePoint[0] = p1;
	linepoint.rightLinePoint[1] = p2;

	cvLine(src,linepoint.upLinePoint[0],linepoint.upLinePoint[1],CV_RGB(255,0,0));
cvShowImage(SrcWindowName,src);
	vertex[0] = getPoint(K[2],B[2],K[0],B[0]);
	vertex[1] = getPoint(K[3],B[3],K[0],B[0]);
	vertex[2] = getPoint(K[2],B[2],K[1],B[1]);
	vertex[3] = getPoint(K[3],B[3],K[1],B[1]);




	cvCircle(src,vertex[0],4,CV_RGB(255,0,0),2,CV_FILLED);
	cvCircle(src,vertex[1],4,CV_RGB(255,0,0),2,CV_FILLED);
	cvCircle(src,vertex[2],4,CV_RGB(255,0,0),2,CV_FILLED);
	cvCircle(src,vertex[3],4,CV_RGB(255,0,0),2,CV_FILLED);
	
	CvPoint2D32f  srcQuad[4]; //源图像中的点
	CvPoint2D32f dstQuad[4]; //目标图像中的点
	CvMat * wrap_matrix = cvCreateMat(3,3,CV_32FC1);
	IplImage *dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);
	//cvmSet(dst,dst->height,dst->width,255);




	srcQuad[0].x = vertex[0].x;
	srcQuad[0].y = vertex[0].y;
	srcQuad[1].x = vertex[1].x;
	srcQuad[1].y = vertex[1].y;

	srcQuad[2].x = vertex[2].x;
	srcQuad[2].y = vertex[2].y;

	srcQuad[3].x = vertex[3].x;
	srcQuad[3].y = vertex[3].y;

	dstQuad[0].x = src->width/6;
	dstQuad[0].y = src->height/6;
	dstQuad[1].x = src->width*5/6;
	dstQuad[1].y = src->height/6;
	dstQuad[2].x = src->width/6;
	dstQuad[2].y = src->height*5/6;
	dstQuad[3].x = src->width*5/6;
	dstQuad[3].y = src->height*5/6;


	cvGetPerspectiveTransform(srcQuad,dstQuad,wrap_matrix);
	cvWarpPerspective(src,dst,wrap_matrix);
	//cvLine( src, linepoint.upLinePoint[0], linepoint.upLinePoint[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
	//cvLine( src, linepoint.downLinePoint[0], linepoint.downLinePoint[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
	//cvLine( src, linepoint.leftLinePoint[0], linepoint.leftLinePoint[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
	//cvLine( src, linepoint.rightLinePoint[0], linepoint.rightLinePoint[1], CV_RGB(255,0,0), 3, CV_AA, 0 );
	//DWORD end = GetCurrentTime();
	//printf("%d",end-start);
	cvShowImage(DstWindowName,dst);
	
	//cvSaveImage("校正结果.bmp",dst);
	cvWaitKey(0);
	return 0;
}
bool floatBigThanZero(float m)
{
	const float EPSINON = 0.00001;
	if ((m >= -EPSINON)&&(m <= EPSINON))
	{
		return false;
	}
	else
		return true;
}

void leastSquare(CvMat *mat1, CvMat *mat2, double *k, double *b)
{
	CvMat * mattmp = cvCreateMat(mat1->rows, mat1->cols,CV_64FC1);
	double A,B,C,D;
	double tmp=0;
	cvMul(mat1,mat1,mattmp,1);
	A = cvSum(mattmp).val[0];
	B = cvSum(mat1).val[0];
	cvMul(mat1,mat2,mattmp,1);
	C = cvSum(mattmp).val[0];
	D = cvSum(mat2).val[0];
	tmp = A*mat1->cols-B*B;
	*k = (C*mat1->cols-B*D)/tmp;
	*b = (A*D-C*B)/tmp;
	 cvReleaseMat(&mattmp);
}

void showTempImage(vector<CvPoint> p1)
{
	//显示下要拟合的图形
	IplImage *	HalfImage = cvCreateImage(cvGetSize(grayImage),8,1);
	cvZero(HalfImage);
	for(int i = 0; i < p1.size(); i ++)
	{
		uchar *ptr = (uchar *)(HalfImage->imageData);
		ptr[cvRound(p1.at(i).x+HalfImage->widthStep*p1.at(i).y)] = 255;
	}
	cvShowImage(SrcWindowName,HalfImage);
}
void initMat(CvMat *mat1, CvMat *mat2,vector<CvPoint> p)
{
	for (int i = 0; i < p.size(); i++ )
	{
		cvmSet(mat1,0,i,p.at(i).x);
		cvmSet(mat2,0,i,p.at(i).y);
	}
}
void deleteElement(vector<CvPoint> *p, double k, double b, int flag) 
{
	switch (flag)
	{
	case UP:
		for(vector<CvPoint>::iterator iter=p->begin(); iter!=p->end();)
		{
			if ((iter->y) >cvRound(iter->x * k +b) )
			{
				iter = p->erase(iter);
			}
			else
				iter++;		
		}
		break;
	case DOWN:
		for(vector<CvPoint>::iterator iter=p->begin(); iter!=p->end();)
		{
			if ((iter->y) <cvRound(iter->x * k +b) )
			{
				iter = p->erase(iter);
			}
			else
				iter++;		
		}
		break;
	case LEFT:
		for(vector<CvPoint>::iterator iter=p->begin(); iter!=p->end();)
		{
			if ((iter->y) >cvRound(iter->x * k +b) )
			{
				iter = p->erase(iter);
			}
			else
				iter++;		
		}
		break;
	case RIGHT:
		for(vector<CvPoint>::iterator iter=p->begin(); iter!=p->end();)
		{
			if ((iter->y) <cvRound(iter->x * k +b) )
			{
				iter = p->erase(iter);
			}
			else
				iter++;		
		}
		break;
	}
	
}
void LeastSquaresIterat(CvMat *mat1, CvMat *mat2, vector<CvPoint> *p, double *k, double*b , int times, int flag)
{
	for (int i = 0; i < times; i++)
	{
		/*if (mat2 != NULL)
		{
			cvReleaseMat(&mat2);
		}
		if (mat1!= NULL)
		{
			cvReleaseMat(&mat1);
		}*/
		mat1=cvCreateMat(1,p->size(),CV_64FC1);//x
		mat2=cvCreateMat(1,p->size(),CV_64FC1);//y
		initMat(mat1,mat2,*p);
		leastSquare(mat1,mat2,k,b);//最小二乘法拟合
	/*	CvPoint p1,p2;
		p1 = cvPoint(0,cvRound(b));
		p2 = cvPoint(w,cvRound(w**k+*b));*/
		//showTempImage(*p);
		deleteElement(p,*k,*b,flag);
		cvReleaseMat(&mat1);
		cvReleaseMat(&mat2);
	}
}
void getWhichEdge(vector<CvPoint> *Position, IplImage *image, int flag)
{
	int h = image->height;
	int w = image->width;
	switch (flag)
	{
	case UP:
		for(int i = 0; i < h/2; i ++)
		{
			uchar *ptr = (uchar *)(image->imageData+ i * image->widthStep);
			for (int j= 0; j < w; j++)
			{	
				if (ptr[j]  == 255) 
				{
					CvPoint tempPoint = cvPoint(j,i);
					Position->push_back(tempPoint);
				}
			}
		}
		break;
	case DOWN:
		for(int i = h/2; i < h; i ++)
		{
			uchar *ptr = (uchar *)(image->imageData+ i * image->widthStep);
			for (int j= 0; j < w; j++)
			{	
				if (ptr[j]  == 255) 
				{
					CvPoint tempPoint = cvPoint(j,i);
					Position->push_back(tempPoint);
				}
			}
		}


		break;
	case LEFT:
		for(int i = 0; i < h; i ++)
		{
			uchar *ptr = (uchar *)(image->imageData+ i * image->widthStep);
			for (int j= 0; j < w/2; j++)
			{	
				if (ptr[j]  == 255) 
				{
					CvPoint tempPoint = cvPoint(i,j);
					Position->push_back(tempPoint);
				}
			}
		}
		break;
	case RIGHT:
		for(int i = h/2; i < h; i ++)
		{
			uchar *ptr = (uchar *)(image->imageData+ i * image->widthStep);
			for (int j= 0; j < w; j++)
			{	
				if (ptr[j]  == 255) 
				{
					CvPoint tempPoint = cvPoint(j,i);
					Position->push_back(tempPoint);
				}
			}
		}

		break;
	}
}
CvPoint getPoint(double vk ,double vb, double hk,double hb)//参数先竖直的，再水平的
{
	CvPoint p;
	p.y= (hb +hk*vb)/(1-hk*vk);
	p.x = p.y*vk+vb;
	return p;
}