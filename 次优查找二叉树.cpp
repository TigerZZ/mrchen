#include <iostream>  
#include <cmath> 
#include<iomanip>
using namespace std;  
typedef struct treenode  
{  
	char data;  
	int weight;  
	treenode *left;  
	treenode *right;  
}Treenode,*Treep;  
//��ʼ��������  
void init_tree(Treep &root)  
{  
	root=NULL;  
	cout<<"��ʼ���ɹ�!"<<endl;  
}  

//����������  
void SecondOptimal(Treep &rt, char R[],int sw[], int low, int high)  
{  
	//�������R[low....high]�����ۻ�Ȩֵ��sw(����sw[0]==0)�ݹ鹹����Ų�����T  
	int i=low;  
	int min = fabs((double)(sw[high] - sw[low]));  
	int dw = sw[high] + sw[low-1];  
	for(int j=low+1; j<=high; ++j)        //ѡ����С�Ħ�Piֵ  
	{  
		if(fabs((double)(dw-sw[j]-sw[j-1])) < min)  
		{  
			i=j;  
			min=fabs((double)(dw-sw[j]-sw[j-1]));  
		}  
	}  
	rt=new Treenode;  
	rt->data=R[i];        //���ɽڵ�  
	if(i==low)            //������Ϊ��  
		rt->left = NULL;  
	else                //����������  
		SecondOptimal(rt->left, R, sw, low, i-1);  

	if(i==high)            //������Ϊ��  
		rt->right = NULL;  
	else                //����������  
		SecondOptimal(rt->right, R, sw, i+1, high);  
}//SecondOptimal  

//ǰ�����������  
void pre_order(Treep rt)  
{  
	if(rt)  
	{  
		cout<<rt->data<<"  ";  
		pre_order(rt->left);  
		pre_order(rt->right);  
	}  
}  

//�������������  
void in_order(Treep rt)  
{  
	if(rt)  
	{  
		in_order(rt->left);  
		cout<<rt->data<<"  ";  
		in_order(rt->right);  
	}  
}  

//�������������  
void post_order(Treep rt)  
{  
	if(rt)  
	{  
		post_order(rt->left);  
		post_order(rt->right);  
		cout<<rt->data<<"  ";  
	}  
}  

//���Ҷ��������Ƿ����ĳԪ��  
int seach_tree(Treep &rt,char key)  
{  
	if(rt==NULL)   
		return 0;   
	else   
	{   
		if(rt->data==key)   
		{  
			return 1;  
		}  
		else  
		{  
			if(seach_tree(rt->left,key) || seach_tree(rt->right,key))  
				return 1;    //�������������һ�����������ͷ���1  
			else  
				return 0;    //�������������û��������������0  
		}  
	}  
} 

int main()  
{  
	Treep root;  
	init_tree(root);        //��ʼ����  
	int low=1,high=10;  
	int *weight,*sw;  
	char *R;  
	int i;
	R=new char[high];  
	for(int i=low; i<high; i++)  
		R[i]='A'+i-1;  
	cout<<"������Ų������ĵ�R[]:"<<endl;  
	for(int i=low; i<high; i++)  
		cout<<setw(3)<<R[i]<<"  ";  
	cout<<endl;  

	weight=new int[high];  
	weight[0]=0;  
	weight[1]=1;  
	weight[2]=1;  
	weight[3]=2;  
	weight[4]=5;  
	weight[5]=3;  
	weight[6]=4;  
	weight[7]=4;  
	weight[8]=3;  
	weight[9]=5;  
	cout<<"������Ų������ĵ��Ȩֵweight[]:"<<endl;  
	for(i=low; i<high; i++)  
		cout<<setw(3)<<weight[i]<<"  ";  
	cout<<endl;  

	sw=new int[high];  
	sw[0]=0;  
	for(i=low; i<high; i++)  
	{  
		sw[i]=sw[i-1]+weight[i];  
	}  
	cout<<"������Ų������ĵ��ۻ�Ȩֵsw[]:"<<endl;  
	for(i=low; i<high; i++)  
		cout<<setw(3)<<sw[i]<<"  ";  
	cout<<endl;  

	//����������  
	SecondOptimal(root, R, sw, low, high-1);  

	cout<<"ǰ�����������:"<<endl;  
	pre_order(root);  
	cout<<endl;  

	cout<<"�������������:"<<endl;  
	in_order(root);  
	cout<<endl;  

	cout<<"�������������:"<<endl;  
	post_order(root);  
	cout<<endl;  

	//���Ҷ��������Ƿ����ĳԪ��  
	cout<<"����Ҫ���ҵ�Ԫ��!"<<endl;  
	char ch;  
	cin>>ch;  
	if(seach_tree(root,ch)==1)  
		cout<<"yes!"<<endl;  
	else  
		cout<<"no!"<<endl;  

	return 0;  
} 