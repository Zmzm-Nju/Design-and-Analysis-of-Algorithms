#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<iostream>
using namespace std;
int main()
{
    int u = 0, v = 0, n = 0;
    string s;
    stringstream str;
    vector<vector<int>> Graph;
    while (getline(cin, s))
    {
        n++;
        str.clear();
        str << s;
        str >> u;
        vector<int> tmp;
        while (str >> v)
            tmp.push_back(v);
        Graph.push_back(tmp);
    }
    /*
    for (int i = 0; i < n; i++)
    {
        Vertex* head = Graph[i].next;
        while (head)
        {
            printf("%d ", head->v);
            head = head->next;
        }
        printf("\n");
    }
    */
    queue<int> Q;
    int* color = new int[n];
    memset(color, 0, 4 * n);
    color[0] = 1;//给点染色
    Q.push(0);
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        for (int i = 0; i < Graph[u].size(); i++)
            if (color[Graph[u][i]] == 0)//未染色
            {
                color[Graph[u][i]] = -color[u];
                Q.push(Graph[u][i]);
            }
    }
    printf("wo yi yue du guan yu chao xi de shuo ming\n");
    for (int i = 0; i < n; i++)
        if (color[i] == 1)
            printf("%d\n", i);
}