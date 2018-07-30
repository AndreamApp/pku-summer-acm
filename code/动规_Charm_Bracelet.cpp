// http://icpcsummer.openjudge.cn/2018hw1/19/
/*
״̬��dp[i][j] ��ʾǰi����������������j�������Ʒ������ֵ��1<=i<=N��1<=j<=M����dp[N][M]
������dp[0][j] = 0 (1<=j<=M)
���̣�dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + d[i]), 1<=i<=N, 1<=j<=M (j-w[i] >= 0)
���Ӷȣ�O(NM)*O(1)  �ռ临�Ӷȣ�O(NM)

���������Ż��ռ临�Ӷȣ�
״̬��dp[j] ��ʾǰi����������������j�������Ʒ������ֵ��1<=i<=N��1<=j<=M����i=Nʱ��dp[M] 
������dp[j] = 0 (1<=j<=M)
���̣�dp[j] = max(dp[j], dp[j-w[i]] + d[i]), 1<=i<=N, M>=j>=1 (j-w[i] >= 0)
���Ӷȣ�O(NM)*O(1)  �ռ临�Ӷȣ�O(M)

ע�⣺
1. ȷ��ÿ���±��ȡֵ��Χ����ѭ����Χ 
2. ÿһ���±궼Ӧ��>=0��ȷ����Ȼ������ 
3. ��Ҫ�ظ������ʼ������
   ��ʼ����Ϊi=0��������ʹ�i=1��ʼ���㣻�����������ָ��򵥣� 
   ��ʼ����Ϊi=1��������ʹ�i=2��ʼ���㣻 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAXN = 3410;
const int MAXM = 12890;

int w[MAXN];
int d[MAXN];
int dp[MAXM];

int main(){
	int N, M;
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; i++){
		scanf("%d%d", &w[i], &d[i]); 
	}
	// dp[j] = max(dp[j], dp[j-w[i]] + d[i]), 1<=i<=N, M>=j>=1 (j-w[i] >= 0)
	for(int i = 1; i <= N; i++){
		for(int j = M; j >= w[i]; j--){
			dp[j] = max(dp[j], dp[j-w[i]] + d[i]);
		}
	}
	printf("%d", dp[M]);
	return 0;
}


