#include<vector>
#include<string>
#include<cstdio>
#include<sstream>
#include<iostream>
using namespace std;
#define min(a,b) ((a)>(b)?(b):(a))
vector<vector<int>> Graph;  //原图
int main()
{
    int u = 0, v = 0, num = 0;
    string s;
    stringstream sstream;
    vector<int> temp;
    while (getline(cin, s))
    {
        num++;//记录顶点数
        sstream.clear();
        sstream << s;
        temp.clear();
        sstream >> u;
        while (sstream >> u)
            temp.push_back(u);
        Graph.push_back(temp);
    }
    int* Cover_0 = new int[num];
    int* Cover_1 = new int[num];
    for (int i = 0; i < num; i++)
    {
        Cover_0[i] = 0;
        Cover_1[i] = 1;
    }
    for (int u = num - 1; u >= 0; u--)
    {
        for (int i = 0; i < Graph[u].size(); i++)
        {
            v = Graph[u][i];
            Cover_0[u] += Cover_1[v];
            Cover_1[u] += min(Cover_0[v], Cover_1[v]);
        }
    }
    printf("I have read the rules about plagiarism punishment\n");
    printf("%d", min(Cover_0[0], Cover_1[0]));
}