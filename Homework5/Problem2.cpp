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
int num, scc_num;//��¼���������ǿ��ͨƬ����
stack<int> Stack;
vector<Vertex> V;//��¼���������ǿ��ͨƬ
vector<vector<int>> Graph;  //ԭͼ
vector<vector<int>> Graph_T;//ת��ͼ
vector<vector<int>> Graph_C;//ѹ��ͼ
vector<vector<int>> SCCs;   //��¼��ͨƬ�е�
void DFS(int u, Color* color);
void DFS_SCC(int u, vector<int>& scc, Color* color);
int  DFS_Influence(int u, Color* scc_color);
int main()
{
    //��������
    int u = 0, v = 0;
    string s;
    stringstream sstream;
    vector<int> temp;
    while (getline(cin, s))
    {
        num++;//��¼������
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
    //��һ��DFS���ڵ���ջ 
    Color* color = new Color[num];
    for (int i = 0; i < num; i++)
        color[i] = White;
    for (int i = 0; i < num; i++)
        if (color[i] == White)
            DFS(i, color);
    //ͼת��
    temp.clear();
    for (int i = 0; i < num; i++)
        Graph_T.push_back(temp);
    for (int i = 0; i < num; i++)
        for (int j = 0; j < Graph[i].size(); j++)
            Graph_T[Graph[i][j]].push_back(i);
    //Ѱ��ǿ��ͨƬ
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
    //��SCCs��ǿ��ͨƬΪ�㣬����ѹ��ͼ
    temp.clear();
    Color* color_scc = new Color[scc_num];
    for (int i = 0; i < scc_num; i++)
        Graph_C.push_back(temp);
    for (int i = 0; i < scc_num; i++)
    {
        for (int i = 0; i < scc_num; i++)//ȷ��һ��SCCֻ������һ��
            color_scc[i] = White;
        for (int j = 0; j < SCCs[i].size(); j++)
        {
            u = SCCs[i][j];//��ĳ��SCC�еĵ�u
            for (int k = 0; k < Graph[u].size(); k++)//�������ھӣ�����ѹ��ͼ
            {
                v = Graph[u][k];
                //V[v].scc != V[u].scc�������㲻��ͬһ��SCC��������SCC֮���бߣ���color��֤ÿ��SCCֻ������һ��
                if (V[v].scc != V[u].scc && color_scc[V[v].scc] == White)
                    Graph_C[V[u].scc].push_back(V[v].scc);
            }
        }
    }
    //DFS����ѹ��ͼ��ÿһ�㣬�õ����
    int influence = 0, max_influence = 0;
    int index = -1;
    for (int i = 0; i < scc_num; i++)
    {
        for (int i = 0; i < scc_num; i++)
            color_scc[i] = White;
        influence = DFS_Influence(i, color_scc) - 1;//��ǰ��ͨƬ�е�Ӱ�������������Լ�
        if (influence > max_influence)
        {
            max_influence = influence;
            index = i;
        }
    }
    //������
    printf("I have read the rules about plagiarism punishment\n");
    printf("%d\n", max_influence);
    sort(SCCs[index].begin(), SCCs[index].end());//����
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
    Stack.push(u);//��ջ
}
void DFS_SCC(int u, vector<int>& scc, Color* color)
{
    int v = 0;
    color[u] = Gray;
    V[u].scc = scc_num;//��scc_num��ǵ�
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