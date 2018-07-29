#include <bits/stdc++.h>

using namespace std;

/*
 �����⣺��ȡǰn����λ���º���������ֵ -> ��ȡǰi����λ���º���������ֵ
 ��һά����i����λ��״̬j�� 
 
 j = 0, 213  312
 j = 1, 123
 j = 2, 321
 j = 3��132  231 
 
 ״̬��dp[i][j] ��ʾǰi����λ�������ڵ�i����λ״̬Ϊjʱȡ�õ��������ֵ��1<=i<=n, 0<=j<=3 
 ת�ƣ�dp[i][0] = max(dp[i-1][2], dp[i-1][3]) + a[i] 
       dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + b[i] 
       dp[i][2] = max(dp[i-1][2], dp[i-1][3]) + b[i] 
       dp[i][3] = max(dp[i-1][0], dp[i-1][1]) + c[i] 
 ������do[1][0] = a[1], dp[1][1] = -inf, dp[1][2] = b[1], dp[1][3] = -inf 
*/

const int inf = 1 << 30;

const int MAX = 10005;

int n;
int dp[MAX][4];
int a[MAX];
int b[MAX];
int c[MAX];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d", &b[i]);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d", &c[i]);
	}
	
	dp[1][0] = a[1];
	dp[1][1] = -inf;
	dp[1][2] = b[1];
	dp[1][3] = -inf;
	
	for(int i = 2; i <= n; i++){
		dp[i][0] = max(dp[i-1][2], dp[i-1][3]) + a[i];
		dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + b[i];
		dp[i][2] = max(dp[i-1][2], dp[i-1][3]) + b[i];
		dp[i][3] = max(dp[i-1][0], dp[i-1][1]) + c[i];
	}
	
	int res = max(dp[n][0], dp[n][1]);
	printf("%d", res);
	return 0;
}
