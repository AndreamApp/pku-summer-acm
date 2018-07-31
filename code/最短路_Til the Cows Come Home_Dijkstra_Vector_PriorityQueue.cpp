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

struct Point{
	int v;
	int dis;
	bool operator<(const Point & d) const{
		return dis > d.dis;
	}
	Point(int V, int Dis) : v(V), dis(Dis){
	}
};

vector<Edge> G[MAX];

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
	priority_queue<Point> q;
	q.push(Point(s, 0));
	while(q.size()){
		// �ҵ���һ������T�е�*���*���
		// ���ȶ��б�֤����� 
		Point p = q.top(); q.pop();
		int u = p.v;
		if(T[u]) continue;
		T[u] = 1;
		// ��������id���ڣ��Ҳ���T�еĽ����� 
		for(int j = 0; j < G[id].size(); j++){
			int v = G[id][j].v;
			if(!T[v]){
				if(d[v] > d[u] + G[u][j].w){
					d[v] = d[u] + G[u][j].w;
					q.push(Point(v, d[v])); // ���µ�ͬʱ������У���֤����Ľ���ܱ��ҵ� 
				}
			}
		}
	}
	return d[n];
}

int main(){
	scanf("%d%d", &t, &n);
	int u, v, w;
	for(int i = 0; i < t; i++){
		scanf("%d%d%d", &u, &v, &w);
		// ʹ���ڽӾ����������رߣ��ڼ���ʱ��Ȼ�ῼ�������ر� 
		G[u].push_back(Edge{v, w});
		G[v].push_back(Edge{u, w});
	}
	printf("%d", dijkstra(1));
	return 0; 
} 
