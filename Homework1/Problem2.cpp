#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
long Merge_Count(char** s, long left, long right);
int main()
{
	long num = 0, ans = 0;
	cin >> num;
	char** s = new char*[num];
	for (int i = 0; i < num; i++)
	{
		s[i] = new char[11];
		cin >> s[i];
	}
	ans = Merge_Count(s, 0, num - 1);
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	cout << ans << endl;
}

long Merge_Count(char** s, long left, long right)
{
	if (left >= right)return 0;
	long mid = (left + right) / 2, inv = 0;
	long a = Merge_Count(s, left, mid);
	long b = Merge_Count(s, mid + 1, right);
	char** s1 = new char*[mid - left + 1];
	for (int i = left; i <= mid; i++)
	{
		s1[i - left] = new char[11];
		strcpy(s1[i - left], s[i]);
	}
	char** s2 = new char* [right - mid];
	for (int i = mid + 1; i <= right; i++)
	{
		s2[i - mid - 1] = new char[11];
		strcpy(s2[i - mid - 1], s[i]);
	}
	int i = left, j = 0, k = 0;
	while (j < mid - left + 1 && k < right - mid)
	{
		if (strcmp(s1[j], s2[k]) <= 0)
		{
			strcpy(s[i++], s1[j++]);
		}
		else if (strcmp(s1[j], s2[k]) > 0)
		{
			strcpy(s[i++], s2[k++]);
			inv += (mid - left + 1 - j);
		}
	}
	while (j < mid - left + 1)
		strcpy(s[i++], s1[j++]);
	while (k < right - mid)
		strcpy(s[i++], s2[k++]);
	for (int i = left; i <= mid; i++)
		delete s1[i - left];
	for (int i = mid + 1; i <= right; i++)
		delete s2[i - mid - 1];
	delete []s1;
	delete []s2;
	return a + b + inv;
}