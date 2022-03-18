#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
using namespace std;
struct Node
{
	int val;
	int height;//以该点为根的树的高度
	Node* lchild;
	Node* rchild;
	Node() :val(0), height(0), lchild(NULL), rchild(NULL) {  }
};
int  diam;
int  Height(Node* root);
void Count_Diam(Node* root);
Node* Bulid_Tree(int* pre, int* in, int pre_left, int pre_right, int in_left, int in_right);
int main()
{
	int n = 0;
	scanf("%d", &n);
	int* Pre = new int[n]; //前序
	int* In = new int[n];  //中序
	
	for (int i = 0; i < n; i++)
		scanf("%d", &Pre[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &In[i]);

	Node* root = Bulid_Tree(Pre, In, 0, n - 1, 0, n - 1);
	int height = Height(root);
	Count_Diam(root);
	printf("I have read the rules about plagiarism punishment\n");
	printf("%d\n%d", height, diam);

	
}
Node* Bulid_Tree(int* pre, int* in, int pre_left, int pre_right, int in_left, int in_right)
{
	if (pre_left > pre_right) 
		return NULL;

	Node* root = new Node;
	root->val = pre[pre_left];
	if (pre_left == pre_right)return root;

	int pivot = 0;//查找下标
	for (int i = in_left; i <= in_right; i++)
		if (in[i] == pre[pre_left])
		{
			pivot = i;
			break;
		}
	int left = pivot - in_left;   //左子树节点数
	root->lchild = Bulid_Tree(pre, in, pre_left + 1, pre_left + left, in_left, pivot - 1);
	root->rchild = Bulid_Tree(pre, in, pre_left + left + 1, pre_right, pivot + 1, in_right);
	return root;
}
int Height(Node* root)
{
	if (root->lchild == NULL && root->rchild == NULL)
		return 0;
	int left = root->lchild == NULL ? 0 : Height(root->lchild);
	int right = root->rchild == NULL ? 0 : Height(root->rchild);
	root->height = (left > right ? left : right) + 1;
	return root->height;
}
void Count_Diam(Node* root)
{
	if(root == NULL) return;
	int left = -1, right = -1;
	if (root->lchild != NULL)
	{
		left = root->lchild->height;
		Count_Diam(root->lchild);
	}
	if (root->rchild != NULL)
	{
		right = root->rchild->height;
		Count_Diam(root->rchild);
	}
	if (diam < left + right + 2)
		diam = left + right + 2;
}