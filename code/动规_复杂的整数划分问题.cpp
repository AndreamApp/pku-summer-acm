#include <bits/stdc++.h>

using namespace std;

const int MAX = 55;

int dp1[MAX][MAX];
int dp2[MAX][MAX];
int f[MAX][MAX];
int g[MAX][MAX];

int N = 50;
int K = 50;

void solve(){
	// dp1[i][j] ��ʾ����i����Ϊj���������ķ����� 
	// dp1[i-j][j]��ʾi�Ļ��ַ����в�����1�����
	// dp1[i-1][j-1]��ʾi�Ļ��ַ����а���1����� 
	dp1[1][1] = 1;
	for(int i = 2; i <= N; i++){
		for(int j = 1; j <= i; j++){
			dp1[i][j] = dp1[i-j][j] + dp1[i-1][j-1];
		}
	}
	
	// dp2[i][j] ��ʾ����i����Ϊ���ɸ�������j���������͵ķ����� 
	// dp2[i-j][j]��ʾi�Ļ��ַ����а���j����� 
	// dp2[i][j-1]��ʾi�Ļ��ַ����в�����j����� 
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			if(i > j) dp2[i][j] = dp2[i-j][j-1] + dp2[i][j-1];
			else if(i == j) dp2[i][j] = 1 + dp2[i][j-1];
			else dp2[i][j] = dp2[i][j-1];
		}
	}
	
	// f[i][j]��ʾ����i����Ϊj�����������͵ķ�����
	// g[i][j]��ʾ����i����Ϊj��ż�������͵ķ����� 
	// f[i-1][j-1]��ʾi�Ļ��ַ����а���1����� 
	// g[i-j][j]��ʾi�Ļ��ַ����в�����1����� 
	f[1][1] = 1;
	g[1][1] = 0;
	for(int i = 2; i <= N; i++){
		for(int j = 1; j <= i; j++){
			g[i][j] = f[i-j][j];
			f[i][j] = f[i-1][j-1] + g[i-j][j];
		}
	}
}

int main(){
	solve();
	while(~scanf("%d%d", &N, &K)){
		printf("%d\n", dp1[N][K]);
		printf("%d\n", dp2[N][N]);
		int res3 = 0;
		for(int j = 1; j <= N; j++){
			res3 += f[N][j];
		}
		printf("%d\n", res3);
	}
	return 0;
}

