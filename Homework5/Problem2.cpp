#define _CRT_SECURE_NO_WARNINGS
#include<stack>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;
struct Vertex
{
    int num;
    int scc;
    Vertex(int n) :num(n), scc(-1) {};
};
enum Color { White, Gray, Black };
int num, scc_num;//记录顶点个数和强连通片个数
stack<int> Stack;
vector<Vertex> V;//记录点和其所在强连通片
vector<vector<int>> Graph;  //原图
vector<vector<int>> Graph_T;//转置图
vector<vector<int>> Graph_C;//压缩图
vector<vector<int>> SCCs;   //记录连通片中点
void DFS(int u, Color* color);
void DFS_SCC(int u, vector<int>& scc, Color* color);
int  DFS_Influence(int u, Color* scc_color);
int main()
{
    //接收输入
    int u = 0, v = 0;
    string s;
    stringstream sstream;
    vector<int> temp;
    while (getline(cin, s))
    {
        num++;//记录顶点数
        sstream.clear();
        sstream << s;
        temp.clear();
        while (sstream >> u)
            temp.push_back(u);
        Graph.push_back(temp);
    }
    for (int i = 0; i < num; i++)
    {
        Vertex v = Vertex(i);
        V.push_back(v);
    }
    //第一轮DFS，节点入栈 
    Color* color = new Color[num];
    for (int i = 0; i < num; i++)
        color[i] = White;
    for (int i = 0; i < num; i++)
        if (color[i] == White)
            DFS(i, color);
    //图转置
    temp.clear();
    for (int i = 0; i < num; i++)
        Graph_T.push_back(temp);
    for (int i = 0; i < num; i++)
        for (int j = 0; j < Graph[i].size(); j++)
            Graph_T[Graph[i][j]].push_back(i);
    //寻找强连通片
    for (int i = 0; i < num; i++)
        color[i] = White;
    while (!Stack.empty())
    {
        u = Stack.top();
        Stack.pop();
        if (color[u] == White)
        {
            temp.clear();
            DFS_SCC(u, temp, color);
            scc_num++;
            SCCs.push_back(temp);
        }
    }
    //以SCCs中强连通片为点，构建压缩图
    temp.clear();
    Color* color_scc = new Color[scc_num];
    for (int i = 0; i < scc_num; i++)
        Graph_C.push_back(temp);
    for (int i = 0; i < scc_num; i++)
    {
        for (int i = 0; i < scc_num; i++)//确保一个SCC只被访问一次
            color_scc[i] = White;
        for (int j = 0; j < SCCs[i].size(); j++)
        {
            u = SCCs[i][j];//在某个SCC中的点u
            for (int k = 0; k < Graph[u].size(); k++)//遍历其邻居，构造压缩图
            {
                v = Graph[u][k];
                //V[v].scc != V[u].scc代表两点不在同一个SCC，则两个SCC之间有边，用color保证每个SCC只被访问一次
                if (V[v].scc != V[u].scc && color_scc[V[v].scc] == White)
                    Graph_C[V[u].scc].push_back(V[v].scc);
            }
        }
    }
    //DFS遍历压缩图中每一点，得到结果
    int influence = 0, max_influence = 0;
    int index = -1;
    for (int i = 0; i < scc_num; i++)
    {
        for (int i = 0; i < scc_num; i++)
            color_scc[i] = White;
        influence = DFS_Influence(i, color_scc) - 1;//当前连通片中的影响力，不包括自己
        if (influence > max_influence)
        {
            max_influence = influence;
            index = i;
        }
    }
    //输出结果
    printf("I have read the rules about plagiarism punishment\n");
    printf("%d\n", max_influence);
    sort(SCCs[index].begin(), SCCs[index].end());//排序
    for (int i = 0; i < SCCs[index].size(); i++)
        printf("%d ", SCCs[index][i]);
    return 0;
}
void DFS(int u, Color* color)
{
    int v = 0;
    color[u] = Gray;
    for (int i = 0; i < Graph[u].size(); i++)
    {
        v = Graph[u][i];
        if (color[v] == White)
            DFS(v, color);
    }
    color[u] = Black;
    Stack.push(u);//入栈
}
void DFS_SCC(int u, vector<int>& scc, Color* color)
{
    int v = 0;
    color[u] = Gray;
    V[u].scc = scc_num;//用scc_num标记点
    for (int i = 0; i < Graph_T[u].size(); i++)
    {
        v = Graph_T[u][i];
        if (color[v] == White)
            DFS_SCC(v, scc, color);
    }
    color[u] = Black;
    scc.push_back(u);
}
int  DFS_Influence(int u, Color* scc_color)
{
    int influence = SCCs[u].size();
    int v = 0;
    scc_color[u] = Gray;
    for (int i = 0; i < Graph_C[u].size(); i++)
    {
        v = Graph_C[u][i];
        if (scc_color[v] == White)
            influence += DFS_Influence(v, scc_color);
    }
    scc_color[u] = Black;
    return influence;
}