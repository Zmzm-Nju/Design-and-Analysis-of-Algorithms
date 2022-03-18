#include<string>
#include<cstring>
#include<iostream>
using namespace std;
class word
{
public:
	word() 
	{
		s = "\0";
		memset(hash, 0, sizeof(hash));
	}
	void set()
	{
		for (int i = 0; i < s.length(); i++)
			hash[s[i] - 'a']++;
	}
	bool operator <(word w)
	{
		for (int i = 0; i < 26; i++)
		{
			if (this->hash[i] == w.hash[i])continue;
			else if (this->hash[i] > w.hash[i]) return false;
			else if (this->hash[i] < w.hash[i]) return true;
		}
		return false;
	}
	bool operator >(word w)
	{
		for (int i = 0; i < 26; i++)
		{
			if (this->hash[i] == w.hash[i])continue;
			else if (this->hash[i] > w.hash[i]) return true;
			else if (this->hash[i] < w.hash[i]) return false;
		}
		return false;
	}
	bool operator ==(word w)
	{
		for (int i = 0; i < 26; i++)
		{
			if (this->hash[i] == w.hash[i])continue;
			else if (this->hash[i] > w.hash[i]) return false;
			else if (this->hash[i] < w.hash[i]) return false;
		}
		return true;
	}
	word& operator =(word& w)
	{
		s = w.s;
		for (int i = 0; i < 26; i++)
			hash[i] = w.hash[i];
		return *this;
	}
	string s;
	char hash[26];
};
void Swap(word& a, word& b);
int  Patition(word* array, int left, int right, int tag);
void Quick_Sort(word* array, int left, int right, int tag);
int main()
{
	int num = 0, cnt = 0, tmp_cnt = 0;
	cin >> num;
	word* words = new word[num];
	for (int i = 0; i < num; i++)
	{
		cin >> words[i].s;
		words[i].set();
	}
	Quick_Sort(words, 0, num - 1, 0);
	word ans[5000], temp[50];
	for (int i = 0; i < num - 1; i++)
	{
		if (words[i] == words[i + 1])
		{
			tmp_cnt = 0;
			while (i + 1 < num && words[i] == words[i + 1])
			{
				temp[tmp_cnt++] = words[i];
				i++;
			}
			temp[tmp_cnt++] = words[i];
			Quick_Sort(temp, 0, tmp_cnt - 1, 1);
			ans[cnt++] = temp[0];
		}
	}
	Quick_Sort(ans, 0, cnt - 1, 1);
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	cout << cnt << endl;
	for (int i = 0; i < cnt; i++)
		cout << ans[i].s << endl;
}

void Swap(word& a, word& b)
{
	word temp = a;
	a = b;
	b = temp;
}

int Patition(word* array, int left, int right,int tag)
{
	int p = left;
	word pivot = array[right];
	for (int i = left; i < right; i++)
	{
		if (tag == 0 && array[i] < pivot)
		{
			if (p != i)
				Swap(array[p], array[i]);
			p++;
		}
		if (tag == 1 && array[i].s < pivot.s)
		{
			if (p != i)
				Swap(array[p], array[i]);
			p++;
		}
	}
	Swap(array[p], array[right]);
	return p;
}

void Quick_Sort(word* array, int left, int right,int tag)
{
	if (right <= left)return;
	int pivot = Patition(array, left, right, tag);
	Quick_Sort(array, left, pivot - 1, tag);
	Quick_Sort(array, pivot + 1, right, tag);
}