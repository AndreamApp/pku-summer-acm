// http://icpcsummer.openjudge.cn/2018hw1/23/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 18;

int n;
int d[MAX][MAX];
int t;
int mint = 1 << 30;

int dp[1<<15][20]; // dp[i][j]��ʾ��i״̬����󾭹�j����̾��룬���ڼ�֦ 
bool visit[MAX]; 
int state;
// i��ʾ��ǰȥ���ĵ��������� k��ʾ���ȥ�ĵ� 
void dfs(int i, int k){
	// ��ֹ״̬ 
	if(i == n-1){
		t += d[k][n-1];
		if(t < mint) mint = t;
		t -= d[k][n-1];
		return;
	}
	visit[k] = 1;
	for(int j = 0; j < n-1; j++){
		// �������пɴ�״̬ 
		if(!visit[j]){ 
			// ״̬ת�ƣ��ƶ�����һ���㣬ʱ�����ӣ�state�仯 
			t += d[k][j];
			state |= 1<<k;
			if(t < mint && t < dp[state][j]){ // ���Ż���֦ 
				dp[state][j] = t;
				dfs(i+1, j);
			}
			state &= ~(1<<k);
			t -= d[k][j];
		}
	}
	visit[k] = 0;
}

int main(){
//	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &d[i][j]);
		}
	}
	memset(dp, 0x3f3f3f3f, sizeof dp); 
	dfs(1, 0);
	printf("%d", mint);
	return 0;
}
