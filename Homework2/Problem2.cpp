//#define _CRT_SECURE_NO_WARNINGS
//#include<cstdio>
//#include<cstdlib>
//#include<iostream>
//#define defaultsize 100
//using namespace std;
//void Swap(int* a, int* b);
//class MinHeap
//{
//public:
//	MinHeap()
//	{
//		cur_size = 0;
//		max_size = defaultsize;
//		data = new int[max_size];
//	}
//	void Extension()
//	{
//		int* temp = data;
//		data = new int[max_size * 2];
//		for (int i = 0; i < max_size; i++)
//			data[i] = temp[i];
//		max_size *= 2;
//		delete[]temp;
//	}
//	void Insert(int n)
//	{
//		if (cur_size == max_size)
//			Extension();
//		data[cur_size++] = n;
//		int i = cur_size - 1;//最后的下标
//		int j = (i - 1) / 2; //父节点下标
//		while (j >= 0)
//		{
//			if (data[i] < data[j])
//			{
//				Swap(&data[i], &data[j]);
//				i = j;
//				j = (i - 1) / 2;
//			}
//			else break;
//		}
//	}
//	void Delete()
//	{
//		data[0] = data[--cur_size];
//		FixHeap(0);
//	}
//	void FixHeap(int index)
//	{
//		int i = 2 * index + 1;
//		if (i <= cur_size - 1)
//		{
//			if (i + 1 <= cur_size - 1 && data[i + 1] < data[i]) i++;
//			if (data[i] < data[index])
//			{
//				Swap(&data[i], &data[index]);
//				FixHeap(i);
//			}
//		}
//	}
//	int cur_size;
//	int max_size;
//	int* data;
//};
//class MaxHeap
//{
//public:
//	MaxHeap()
//	{
//		cur_size = 0;
//		max_size = defaultsize;
//		data = new int[max_size];
//	}
//	void Extension()
//	{
//		int* temp = data;
//		data = new int[max_size * 2];
//		for (int i = 0; i < max_size; i++)
//			data[i] = temp[i];
//		max_size *= 2;
//		delete[]temp;
//	}
//	void Insert(int n)
//	{
//		if (cur_size == max_size)
//			Extension();
//		data[cur_size++] = n;
//		int i = cur_size - 1;//最后的下标
//		int j = (i - 1) / 2; //父节点下标
//		while (j >= 0)
//		{
//			if (data[i] > data[j])
//			{
//				Swap(&data[i], &data[j]);
//				i = j;
//				j = (i - 1) / 2;
//			}
//			else break;
//		}
//	}
//	void Delete()
//	{
//		data[0] = data[--cur_size];
//		FixHeap(0);
//	}
//	void FixHeap(int index)
//	{
//		int i = 2 * index + 1;
//		if (i <= cur_size - 1)
//		{
//			if (i + 1 <= cur_size - 1 && data[i + 1] > data[i]) i++;
//			if (data[i] > data[index])
//			{
//				Swap(&data[i], &data[index]);
//				FixHeap(i);
//			}
//		}
//	}
//	int cur_size;
//	int max_size;
//	int* data;
//};
//class MidHeap
//{
//public:
//	void Insert(int n)
//	{
//		if (max.cur_size == 0)max.Insert(n);
//		else 
//		{
//			int mid = max.data[0];
//			if (n >= mid)min.Insert(n);
//			if (n < mid)max.Insert(n);
//			FixHeap();
//		}
//	}
//	void FixHeap()
//	{
//		if (max.cur_size == min.cur_size - 1)
//		{
//			int temp = min.data[0];
//			min.Delete();
//			max.Insert(temp);
//		}
//		if (max.cur_size == min.cur_size);    //不需要fix
//		if (max.cur_size == min.cur_size + 1);//不需要fix
//		if (max.cur_size == min.cur_size + 2)
//		{
//			int temp = max.data[0];
//			max.Delete();
//			min.Insert(temp);
//		}
//	}
//	MaxHeap max;
//	MinHeap min;
//};
//int main()
//{
//	MidHeap mid;
//	int n = 0;
//	while (scanf("%d", &n) != EOF)
//	{
//		mid.Insert(n);
//		printf("%d ", mid.max.data[0]);
//	}
//}
//
//void Swap(int* a, int* b)
//{
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
