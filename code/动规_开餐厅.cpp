// http://icpcsummer.openjudge.cn/2018hw1/16/
/*
״̬��dp[i] ��ʾ���ص�Ϊ��i��ʱ���������1<=i<=n����dp[n] 
������dp[i] = i; 1<=i<=n
���̣�dp[i] = max(dp[j]) + p[i], 1<=i<=n, 1<=j<=i-1, m[j]<=m[i]-k-1
���Ӷȣ�O(n)*O(n) = O(n^2) 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int N = 105;

int m[N];
int p[N];
int dp[N];

int main(){
	int T, n, k;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++){
			scanf("%d", &m[i]);
		}
		for(int i = 1; i <= n; i++){
			scanf("%d", &p[i]);
			dp[i] = p[i]; // ���ú���ĳ�ʼ��������dp�ж� 
		}
		
		for(int i = 1; i <= n; i++){
			// ��һ��������������j��ֵ 
			for(int j = i-1; j >= 1; j--){
				if(m[j] <= m[i]-k-1){
					dp[i] = max(dp[i], dp[j] + p[i]);
				}
			}
		}
		
		// �����ս���������ֵ 
		int res = 0;
		for(int i = 1; i <= n; i++){
			if(dp[i] > res) res = dp[i];
		}
		printf("%d\n", res);
	}
	return 0;
}
