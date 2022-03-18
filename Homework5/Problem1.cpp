#define _CRT_SECURE_NO_WARNINGS
#define defaultsize 10000
#include<cstdio>
#include<cstdlib>
using namespace std;
class Edge
{
public:
	Edge() :u(0), v(0), val(0) {}
	Edge(int u0, int v0, int val0) :u(u0), v(v0), val(val0) {}
	Edge operator = (Edge e)
	{
		this->u = e.u;
		this->v = e.v;
		this->val = e.val;
		return *this;
	}
	bool operator < (Edge& e) { return this->val < e.val; }
	bool operator > (Edge& e) { return this->val > e.val; }
	bool operator == (Edge& e) { return this->val == e.val; }
	int Get_U() { return u; }
	int Get_V() { return v; }
	int Get_Val() { return val; }
private:
	int u;
	int v;
	int val;
};
template<class T>
class MinHeap
{
public:
	MinHeap() :cursize(0), maxsize(defaultsize) 
	{ datas = new T[defaultsize]; }
	T GetRoot() { return datas[0]; }
	void Insert(T data);
	void Delete();
	void DealWithOverflow();
private:
	int cursize;
	int maxsize;
	T* datas;
};
class UnionSet
{
public:
	UnionSet(int n) :size(n) 
	{ 
		datas = new int[n];
		for (int i = 0; i < n; i++)
			datas[i] = -1;
	}
	int FindParent(int u);
	void WeightedUnion(int u, int v);
	bool Equal(int u, int v) { return FindParent(u) == FindParent(v); }
private:
	int size;
	int* datas;
};
int main()
{
	int n = 0, u = 0, v = 0, val = 0;
	scanf("%d", &n);
	UnionSet Set(n);
	MinHeap<Edge> Heap;
	while (scanf("%d %d %d", &u, &v, &val) != EOF)
	{
		Edge e(u, v, val);
		Heap.Insert(e);
	}
	int ans = 0;
	for (int i = 0; i < n - 1;)
	{
		Edge e = Heap.GetRoot();
		Heap.Delete();
		if (Set.Equal(e.Get_U(), e.Get_V()))continue;
		ans += e.Get_Val();
		Set.WeightedUnion(e.Get_U(), e.Get_V());
		i++;
	}
	printf("%d\n", ans);
}
template<class T>
void MinHeap<T>::Insert(T data)
{
	if (cursize == maxsize)
		DealWithOverflow();
	datas[cursize++] = data;
	int i = cursize - 1, j = (i - 1) / 2;
	while (j >= 0 && datas[i] < datas[j])
	{
		T temp = datas[i];
		datas[i] = datas[j];
		datas[j] = temp;
		if (j == 0)break;
		i = j;
		j = (i - 1) / 2;
	}
}
template<class T>
void MinHeap<T>::Delete()
{
	datas[0] = datas[--cursize];
	int i = 0, j = 2 * i + 1;
	while (j < cursize)
	{
		if (j + 1 < cursize && datas[j + 1] < datas[j])j++;
		if (datas[j] < datas[i])
		{
			T temp = datas[i];
			datas[i] = datas[j];
			datas[j] = temp;
			i = j;
			j = 2 * i + 1;
		}
		else break;
	}
}
template<class T>
void MinHeap<T>::DealWithOverflow()
{
	maxsize = maxsize * 2;
	T* temp = new T[maxsize];
	for (int i = 0; i < cursize; i++)
		temp[i] = datas[i];
	delete []datas;
	datas = temp;
}
int UnionSet::FindParent(int u)
{
	int parent = u;
	while (datas[parent] >= 0)
		parent = datas[parent];
	return parent;
}
void UnionSet::WeightedUnion(int u, int v)
{
	int p1 = FindParent(u);
	int p2 = FindParent(v);
	if (p1 == p2)return;
	else if (datas[p1] > datas[p2]) {
		datas[p2] += datas[p1];
		datas[p1] = p2;
	}
	else {
		datas[p1] += datas[p2];
		datas[p2] = p1;
	}
}