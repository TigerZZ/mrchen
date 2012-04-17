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
//初始化二叉树  
void init_tree(Treep &root)  
{  
	root=NULL;  
	cout<<"初始化成功!"<<endl;  
}  

//创建二叉树  
void SecondOptimal(Treep &rt, char R[],int sw[], int low, int high)  
{  
	//由有序表R[low....high]及其累积权值表sw(其中sw[0]==0)递归构造次优查找树T  
	int i=low;  
	int min = fabs((double)(sw[high] - sw[low]));  
	int dw = sw[high] + sw[low-1];  
	for(int j=low+1; j<=high; ++j)        //选择最小的ΔPi值  
	{  
		if(fabs((double)(dw-sw[j]-sw[j-1])) < min)  
		{  
			i=j;  
			min=fabs((double)(dw-sw[j]-sw[j-1]));  
		}  
	}  
	rt=new Treenode;  
	rt->data=R[i];        //生成节点  
	if(i==low)            //左子树为空  
		rt->left = NULL;  
	else                //构造左子树  
		SecondOptimal(rt->left, R, sw, low, i-1);  

	if(i==high)            //右子树为空  
		rt->right = NULL;  
	else                //构造右子树  
		SecondOptimal(rt->right, R, sw, i+1, high);  
}//SecondOptimal  

//前序遍历二叉树  
void pre_order(Treep rt)  
{  
	if(rt)  
	{  
		cout<<rt->data<<"  ";  
		pre_order(rt->left);  
		pre_order(rt->right);  
	}  
}  

//中序遍历二叉树  
void in_order(Treep rt)  
{  
	if(rt)  
	{  
		in_order(rt->left);  
		cout<<rt->data<<"  ";  
		in_order(rt->right);  
	}  
}  

//后序遍历二叉树  
void post_order(Treep rt)  
{  
	if(rt)  
	{  
		post_order(rt->left);  
		post_order(rt->right);  
		cout<<rt->data<<"  ";  
	}  
}  

//查找二叉树中是否存在某元素  
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
				return 1;    //如果左右子树有一个搜索到，就返回1  
			else  
				return 0;    //如果左右子树都没有搜索到，返回0  
		}  
	}  
} 

int main()  
{  
	Treep root;  
	init_tree(root);        //初始化树  
	int low=1,high=10;  
	int *weight,*sw;  
	char *R;  
	int i;
	R=new char[high];  
	for(int i=low; i<high; i++)  
		R[i]='A'+i-1;  
	cout<<"构造次优查找树的点R[]:"<<endl;  
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
	cout<<"构造次优查找树的点的权值weight[]:"<<endl;  
	for(i=low; i<high; i++)  
		cout<<setw(3)<<weight[i]<<"  ";  
	cout<<endl;  

	sw=new int[high];  
	sw[0]=0;  
	for(i=low; i<high; i++)  
	{  
		sw[i]=sw[i-1]+weight[i];  
	}  
	cout<<"构造次优查找树的点累积权值sw[]:"<<endl;  
	for(i=low; i<high; i++)  
		cout<<setw(3)<<sw[i]<<"  ";  
	cout<<endl;  

	//创建二叉树  
	SecondOptimal(root, R, sw, low, high-1);  

	cout<<"前序遍历序列是:"<<endl;  
	pre_order(root);  
	cout<<endl;  

	cout<<"中序遍历序列是:"<<endl;  
	in_order(root);  
	cout<<endl;  

	cout<<"后序遍历序列是:"<<endl;  
	post_order(root);  
	cout<<endl;  

	//查找二叉树中是否存在某元素  
	cout<<"输入要查找的元素!"<<endl;  
	char ch;  
	cin>>ch;  
	if(seach_tree(root,ch)==1)  
		cout<<"yes!"<<endl;  
	else  
		cout<<"no!"<<endl;  

	return 0;  
} 