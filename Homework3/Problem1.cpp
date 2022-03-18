#define _CRT_SECURE_NO_WARNINGS
#define min(x,y) ((x)>(y)?(y):(x))
#define max(x,y) ((x)<(y)?(y):(x))
#include<cstdio>
using namespace std;
int main()
{
	int n = 0, ans = 0;
	scanf("%d", &n);
	int* A = new int[n];
	int* B = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &B[i]);
	int A_left = 0, A_right = n - 1, A_mid = (A_left + A_right) / 2;
	int B_left = 0, B_right = n - 1, B_mid = (B_left + B_right) / 2;
	int rank = n;
	while (A_left <= A_right && B_left <= B_right)
	{
		if (A[A_mid] < B[B_mid])
		{
			if ((A_right - A_left + 1) % 2 == 0)//偶数个数字
			{
				rank = rank - (A_mid - A_left + 1);
				A_left = A_mid + 1;
			}
			else
			{
				rank = rank - (A_mid - A_left);
				A_left = A_mid;
			}
			B_right = B_mid;
			A_mid = (A_left + A_right) / 2;
			B_mid = (B_left + B_right) / 2;
		}
		if (A[A_mid] > B[B_mid])
		{
			if ((B_right - B_left + 1) % 2 == 0)//偶数个数字
			{
				rank = rank - (B_mid - B_left + 1);
				B_left = B_mid + 1;
			}
			else
			{
				rank = rank - (B_mid - B_left);
				B_left = B_mid;
			}
			A_right = A_mid;
			B_mid = (B_left + B_right) / 2;
			A_mid = (A_left + A_right) / 2;
		}
		if (rank == 1)
		{
			ans = min(A[A_mid], B[B_mid]);
			break;
		}
	}
	printf("%d", ans);
}