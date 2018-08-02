#include <bits/stdc++.h>

using namespace std;

struct homework{
	char name[51];
	int d; // deadline
	int c; // �������ʱ�� 
};

// Q: ���ֻ��Ҫ������Ϳ۷֣���Щ״ֵ̬�Ǳ�Ҫ�ģ�
// Q: ΪʲôҪ�������״ֵ̬����ʲô�ã� 
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
					int pre = i & ~(1<<k); // Q: i & ~(1<<k) �ĺ�����ʲô�� 
					int finish = dp[pre].finishDay + h[k].c;
					int score = max(finish - h[k].d, 0) + dp[pre].score;
					// ��ǰ״̬������С
					if(score < dp[i].score){  
						dp[i] = state{score, finish, pre, k};
					}
					// ��ǰ״̬��Ȼ������ͬ�������ֵ����С 
					else if(score == dp[i].score && getPath(pre) < getPath(dp[i].pre)){ 
						dp[i] = state{score, finish, pre, k};
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

