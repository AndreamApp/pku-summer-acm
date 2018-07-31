#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;
const int inf = 0x3f3f3f3f;

int n;

struct Edge{
	int v;
	int w;
};

struct Point{
	int v;
	int dis;
	bool operator<(const Point & d) const{
		return dis > d.dis;
	}
	Point(int V, int Dis) : v(V), dis(Dis){
	}
};

int G[MAX][MAX];

int d[MAX];
bool used[MAX];

int prim(int s){
	int totalWeight = 0;
	memset(d, inf, sizeof d);
	memset(used, 0, sizeof used);
	d[s] = 0;
	// ��ʼ״̬ 
	Point p(s, 0);
	priority_queue<Point> q;
	q.push(p);
	while(q.size()){
		// �ҵ���һ�������������е�*���*���
		do{
			p = q.top(); q.pop();
		} while(used[p.v] && q.size());
		int u = p.v;
		if(!used[u]){ 
			used[u] = 1;
			totalWeight += p.dis; // �Ǹ�����Ľ�㣬������С��������һ����� 
			// ���������������ڽ�����̾��� 
			for(int j = 0; j < n; j++){
				if(!used[j]){
					if(d[j] > G[u][j]){ 
//						d[j] = d[u] + G[u][j];
						d[j] = G[u][j]; // Dijkstra��d[j]�������s��j����̾��룬��Prim��d[j]���������������j����̾��� 
						q.push(Point(j, d[j])); // ���µ�ͬʱ������У���֤����Ľ���ܱ��ҵ� 
					}
				}
			}
		}
	}
	return totalWeight;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &G[i][j]);
			}
		}
		printf("%d\n", prim(0));
	}
	return 0; 
} 
