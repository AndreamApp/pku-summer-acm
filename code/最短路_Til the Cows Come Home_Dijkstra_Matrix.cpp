#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005;
const int inf = 0x3f3f3f3f;

int n;
int t;

struct Edge{
	int v;
	int w;
};

int G[MAX][MAX];

int d[MAX];
bool T[MAX];
int next_i(){
	int id = 0;
	int val = inf;
	for(int i = 1; i <= n; i++){
		// ����T�е������� 
		if(!T[i] && d[i] < val){
			val = d[i];
			id = i;
		}
	}
	T[id] = 1;
	return id;
}

// ǰ�᣺��Դ·���������и�Ȩ�� 
// ���Ϊ1����1�����е�ľ��롣��Ϊd[n] 
int dijkstra(int s){
	for(int i = 1; i <= n; i++){
		d[i] = s == i ? 0 : inf;
	}
	for(int i = 1; i <= n; i++){
		// �ҵ���һ������T�е������� 
		int id = next_i();
		// if(id == 0) break; ����Ҫ����Ϊ���ѭ����Ҫִ��n�� 
		// ��������id���ڣ��Ҳ���T�еĽ����� 
		for(int j = 1; j <= n; j++){
			if(!T[j] && G[id][j]){
				d[j] = min(d[j], d[id] + G[id][j]);
			}
		}
	}
	return d[n];
}

int main(){
	// Ϊ��������رߣ�һ��ʼ��Ϊ����� 
	memset(G, inf, sizeof G);
	scanf("%d%d", &t, &n);
	int u, v, w;
	for(int i = 0; i < t; i++){
		scanf("%d%d%d", &u, &v, &w);
		// �ر�ȡ��̱� 
		if(w < G[u][v]){
			G[u][v] = w;
			G[v][u] = w;
		}
	}
	printf("%d", dijkstra(1));
	return 0; 
} 
