#include <bits/stdc++.h>

using namespace std;

struct homework{
	char name[51];
	int d; // deadline
	int c; // �������ʱ�� 
};

struct state{
	int score; // ��ɸ�״̬��������ҵ��ķ��� 
	int finishDay; // ��ɸ�״̬��������ҵ��ʱ�� 
	int pre; // �ﵽ��״̬����һ��״̬ 
	int last; // �ﵽ��״̬��ɵ����һ����ҵ 
};

const int inf = 1 << 30;

int N;
homework h[17];
state dp[1<<15];

// ����pre��last����ȡ�����ĳ��״̬��·�� 
vector<int> getPath(int state){
	vector<int> path;
	while(state != 0){
		path.push_back(dp[state].last);
		state = dp[state].pre;
	}
	reverse(path.begin(), path.end());
	return path; 
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		for(int i = 0; i < N; i++){
			scanf("%s%d%d", h[i].name, &h[i].d, &h[i].c);
		}
		
		dp[0].score = 0;
		dp[0].finishDay = 0;
		int n = 1 << N;
		for(int i = 1; i < n; i++){ // ���dp[i]
			dp[i].score = inf;
			for(int k = 0; k < N; k++){ 
				if(i & (1 << k)){
					int pre = i & ~(1<<k);
					int finish = dp[pre].finishDay + h[k].c;
					int score = max(finish - h[k].d, 0) + dp[pre].score;
					if(score < dp[i].score){ // ��ǰ״̬������С 
						dp[i].score = score;
						dp[i].finishDay = finish;
						dp[i].pre = pre;
						dp[i].last = k;
					}
					else if(score == dp[i].score){ // ��ǰ״̬��Ȼ������ͬ�������ֵ����С 
						if(getPath(pre) < getPath(dp[i].pre)){
							dp[i].finishDay = finish;
							dp[i].pre = pre;
							dp[i].last = k;
						} 
					}
				}
			}
		}
		

		vector<int> path = getPath(n-1);
		printf("%d\n", dp[n-1].score);
		int S = path.size();
		for(int i = 0; i < S; i++){
			printf("%s\n", h[path[i]].name);
		}
	}
	return 0;
} 

