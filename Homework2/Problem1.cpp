#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void Swap(int* a, int* b);
int  Find_Rank_K(int* array, int left, int right, int k);//最小的Rank当作1
int  Patition(int* array, int left, int right);
void Quick_Sort(int* array, int left, int right);
int main()
{
	//get input
	int m = 0, k = 0;
	scanf("%d %d", &k, &m);
	int* num = new int[m];
	for (int i = 0; i < m; i++)
		scanf("%d", &num[i]);

	//calculate the index
	int mid_rank = (m + 1) / 2;
	int left_rank = mid_rank - k;
	int right_rank = mid_rank + k;

	//Do Partion and Sort
	int left_num = Find_Rank_K(num, 0, m - 1, left_rank);
	int right_num = Find_Rank_K(num, left_rank, m - 1, 2 * k);
	Quick_Sort(num, left_rank - 1, right_rank - 1);

	//Print Answers
	printf("%d", num[left_rank - 1]);
	for (int i = left_rank; i <= right_rank - 1; i++)
		printf(" %d", num[i]);
	printf("\n");
	return 0;
}
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int  Find_Rank_K(int* array, int left, int right, int k)
{
	if (left >= right) return array[left];
	int pivot = Patition(array, left, right);
	if (pivot - left + 1 == k)return array[pivot];
	else if (pivot - left + 1 < k)return Find_Rank_K(array, pivot + 1, right, k - (pivot - left + 1) ); //递归到右边
	else if (pivot - left + 1 > k)return Find_Rank_K(array, left, pivot - 1, k); //递归到左边
}
int  Patition(int* array, int left, int right)
{
	int p = left;
	int pivot = array[right];
	for (int i = left; i < right; i++)
	{
		if (array[i] < pivot)
		{
			if (p != i)
				Swap(&array[p], &array[i]);
			p++;
		}
	}
	Swap(&array[p],&array[right]);
	return p;
}
void Quick_Sort(int* array, int left, int right)
{
	if (right <= left)return;
	int pivot = Patition(array, left, right);
	Quick_Sort(array, left, pivot - 1);
	Quick_Sort(array, pivot + 1, right);
}