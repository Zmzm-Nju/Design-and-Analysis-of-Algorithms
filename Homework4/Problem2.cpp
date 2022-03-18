#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define min(x,y) ((x)<(y)?(x):(y))
enum Color { White, Gray, Black };
int time = 0;
vector<int> Point;
vector<vector<int>> Bridge;
vector<vector<int>> Graph;
void DFS(int u, int parent, Color* color, int* discovertime, int* back, bool root);
bool Complare(vector<int> a, vector<int> b);
int main()
{
	int u = 0, v = 0, n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		vector<int>tmp;
		Graph.push_back(tmp);
	}
	while (scanf("%d %d", &u, &v) != EOF)
	{
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}
	Color* color = new Color[n];
	memset(color, 0, sizeof(Color) * n);
	int* back = new int[n];
	int* discovertime = new int[n];
	memset(back, 0, sizeof(int) * n);
	memset(discovertime, 0, sizeof(int) * n);
	for (int i = 0; i < n; i++)
	{
		if (color[i] == White)
			DFS(i, -1, color, discovertime, back, true);
	}
	sort(Point.begin(), Point.end());
	sort(Bridge.begin(), Bridge.end(), Complare);
	printf("wo yi yue du guan yu chao xi de shuo ming\n");
	for (int i = 0; i < Point.size(); i++)
		printf("%d\n", Point[i]);
	for (int i = 0; i < Bridge.size(); i++)
		printf("%d %d\n", Bridge[i][0], Bridge[i][1]);
}
void DFS(int u, int parent, Color* color, int* discovertime, int* back, bool root)
{
	color[u] = Gray;
	time = time + 1;
	discovertime[u] = time;
	back[u] = time;
	int n = 0, push = 0;
	for (int i = 0; i < Graph[u].size(); i++)
	{
		int v = Graph[u][i];
		if (color[v] == White)
		{
			n++;
			DFS(v, u, color, discovertime, back, false);
			if (!root && !push && back[v] >= discovertime[u])
			{
				Point.push_back(u);
				push = 1;
			}
			if (back[v] > discovertime[u])
			{
				vector<int> tmp;
				if (u < v)
				{
					tmp.push_back(u);
					tmp.push_back(v);
				}
				else {
					tmp.push_back(v);
					tmp.push_back(u);
				}
				Bridge.push_back(tmp);
			}
			back[u] = min(back[u], back[v]);
		}
		else if (color[v] == Gray && v != parent)
			back[u] = min(back[u], back[v]);
	}
	if (n >= 2 && root)
		Point.push_back(u);
}
bool Complare(vector<int> a, vector<int> b)
{
	if (a[0] != b[0])
		return a[0] < b[0];
	else
		return a[1] < b[1];
}