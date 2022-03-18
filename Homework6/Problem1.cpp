#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
struct Edge
{
	short v;
	short val;
};
vector<vector<Edge>>Graph;   //ԭͼ
vector<vector<Edge>>Graph_T; //ת��ͼ
void DFS(int u, int* Topo_Order, int* Topo_Num, int* Color);
int main()
{
	int num = 0;
	int u = 0, v = 0, val = 0;
	scanf("%d", &num);
	vector<Edge>temp;
	for (int i = 0; i < num; i++)
	{
		Graph.push_back(temp);
		Graph_T.push_back(temp);
	}
	while (scanf("%d %d %d", &u, &v, &val) != EOF)
	{
		Edge e;
		e.v = v, e.val = val;
		Graph[u].push_back(e);
		e.v = u, e.val = val;
		Graph_T[v].push_back(e);
	}
	int  Topo_Num = num;
	int* Topo_Order = new int[num];
	int* Color = new int[num];
	for (int i = 0; i < num; i++)
		Color[i] = 0;
	DFS(0, Topo_Order, &Topo_Num, Color);
	delete[]Color;

	int* Distance = new int[num];
	Distance[0] = 0;
	for (int i = 1; i < num; i++)
		Distance[i] = -1;
	for (int i = 1; i < num; i++)
	{
		u = Topo_Order[i];
		for (int j = 0; j < Graph_T[u].size(); j++)
		{
			v = Graph_T[u][j].v;
			val = Graph_T[u][j].val;
			if (Distance[v] + val > Distance[u])
				Distance[u] = Distance[v] + val;
		}
	}
	printf("I have read the rules about plagiarism punishment\n");
	for (int i = 1; i < num; i++)
		printf("%d ", Distance[i]);
}
void DFS(int u, int* Topo_Order, int* Topo_Num, int* Color)
{
	Color[u] = 1;
	for (int i = 0; i < Graph[u].size(); i++)
	{
		int v = Graph[u][i].v;
		if (Color[v] == 0)
			DFS(v, Topo_Order, Topo_Num, Color);
	}
	(*Topo_Num)--;
	Topo_Order[*Topo_Num] = u;
}