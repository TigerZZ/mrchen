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
void InsertSort(int *a,int length){//插入排序
	int i,j;
	int temp;
	for (i =1; i < length;i++)
	{
		if (a[i]<a[i-1])//判断需不需要插
		{
			temp = a[i];//保存一份
			a[i] = a[i-1];//往后挪
			for (j = i-1; temp < a[j];j--)
				a[j+1] = a[j];//往后挪
			a[j+1] = temp;
		}
	}
}
void BubbleSort(int *a,int length){//冒泡排序
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
	std::vector<int> temp; //辅助空间
	  int i = begin, j = middle+1;
	  int size = end - begin + 1;
	  /* 同时遍历两个序列，将小的存入辅助向量中 */
 while(i <= middle && j <= end) 
{
	if(a[i] <= a[j]) 
		temp.push_back(a[i++]);
    else
		temp.push_back(a[j++]);        
}
   /* 将子序列的剩余的元素直接存入辅助向量中，此时另一个已为空*/
    while(j <= end) 
		temp.push_back(a[j++]);    
   while(i <= middle) 
	   temp.push_back(a[i++]);
    /* 复制回原序列*/
    for(i = 0; i != size; ++i)
        a[begin+i] = temp.at(i);
    temp.clear();
}