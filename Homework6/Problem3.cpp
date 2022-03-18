#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<cstdio>
using namespace std;
#define Max(a,b) ((a)>(b)?(a):(b))
int main()
{
	char ch;
	vector<char> str;
	while (scanf("%c ", &ch) != EOF)
		str.push_back(ch);
	int size = str.size();
	short** A = new short* [size];
	for (int i = 0; i < size; i++)
		A[i] = new short[size];
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = i; j <= size - 1; j++)
		{
			if (j == i)
				A[i][j] = 1;
			else if (j == i + 1)
				A[i][j] = (str[i] == str[j]) ? 2 : 1;
			else
			{
				if (str[i] == str[j]) 
					A[i][j] = A[i + 1][j - 1] + 2;
				else 
					A[i][j] = Max(A[i + 1][j], A[i][j - 1]);
			}
		}
	}
	printf("I have read the rules about plagiarism punishment\n");
	printf("%hd", A[0][size - 1]);
}
