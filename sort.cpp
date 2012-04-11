#include <stdio.h>
#include <vector>
void InsertSort(int *a,int length);
void BubbleSort(int *a,int length);
void QuickSort(int *a, int length);
void MergeSort(int *a,int first, int last);
void Merge(int*a, int begin, int middle, int end);
void main(){
	int a[7] = {49,38,65,97,76,13,27};
	/*InsertSort(a,7);
	BubbleSort(a,7);*/
	//QuickSort(a,7);
	MergeSort(a,0,6);
	for( int i = 0; i < 7; i++)
		printf("%d,",a[i]);
}
void InsertSort(int *a,int length){//��������
	int i,j;
	int temp;
	for (i =1; i < length;i++)
	{
		if (a[i]<a[i-1])//�ж��費��Ҫ��
		{
			temp = a[i];//����һ��
			a[i] = a[i-1];//����Ų
			for (j = i-1; temp < a[j];j--)
				a[j+1] = a[j];//����Ų
			a[j+1] = temp;
		}
	}
}
void BubbleSort(int *a,int length){//ð������
int i,j;
for (i = 0; i < length;i++)
{
	for (j = i +1; j < length;j++)
	{
		if (a[i] >a[j])
		{
			a[i] ^= a[j];
			a[j] ^= a[i];
			a[i] ^= a[j];
		}
	}
}
}
void QuickSort(int *a, int length){
	int i = 0; 
	int j = length-1;
	int key = a[0];
	int f = 0;
	int checked = 0;
	int x = 0;
	while ( i != j)
	{
		while(a[j] > key)
			j--;
		a[i]  ^= a[j];
		a[j] ^= a[i];
		a[i] ^= a[j];

		while(a[i] < key)
			i++;
		a[i]  ^= a[j];
		a[j] ^= a[i];
		a[i] ^= a[j];

	
	}



}


void MergeSort(int *a,int first, int last){
		if (first < last){	
				int mid = 0;
				mid = (first+last)/2;
				MergeSort(a,mid+1,last);
				MergeSort(a,first,mid);
				Merge(a,first,mid,last);
		}
}
void Merge(int*a, int begin, int middle, int end){
	std::vector<int> temp; //�����ռ�
	  int i = begin, j = middle+1;
	  int size = end - begin + 1;
	  /* ͬʱ�����������У���С�Ĵ��븨�������� */
 while(i <= middle && j <= end) 
{
	if(a[i] <= a[j]) 
		temp.push_back(a[i++]);
    else
		temp.push_back(a[j++]);        
}
   /* �������е�ʣ���Ԫ��ֱ�Ӵ��븨�������У���ʱ��һ����Ϊ��*/
    while(j <= end) 
		temp.push_back(a[j++]);    
   while(i <= middle) 
	   temp.push_back(a[i++]);
    /* ���ƻ�ԭ����*/
    for(i = 0; i != size; ++i)
        a[begin+i] = temp.at(i);
    temp.clear();
}