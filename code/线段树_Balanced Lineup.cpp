#include <bits/stdc++.h>

using namespace std;

const int MAX = 50005;
const int inf = 1 << 30;

int n, q;

// + ���ȼ����� <<
// l << 1 + 1 ��ʵ�� l << (1 + 1)���Ǵ�� 
inline int L(int l){
	return (l << 1) + 1;
}

inline int R(int r){
	return (r << 1) + 2;
}

struct node{
	int l;
	int r;
	int maxv;
	int minv;
	
	int mid(){
		return (l+r) / 2;
	}
	
	bool single(){
		return l == r;
	}
	
	bool is(int a, int b){
		return l == a && r == b;
	}
};
node tree[MAX*3+1];

// ���v��Ӧ������Ϊ[l,r] 
// build(0, 0, n-1) -> long long a[n];
void build(int v, int l, int r){
	tree[v].l = l;
	tree[v].r = r;
	tree[v].maxv = -inf;
	tree[v].minv = +inf;
	if(!tree[v].single()){
		build(L(v), l, (l+r)/2);
		build(R(v), (l+r)/2+1, r);
	}
}

// ���ڵ�v��ʼ���ҵ�i��ֵ��������Ϊval
// insert(0, i, val) -> a[i] = val; 
void insert(int v, int i, int val){
	if(tree[v].is(i, i)){
		tree[v].maxv = max(val, tree[v].maxv);
		tree[v].minv = min(val, tree[v].minv);
		return;
	}
	
	tree[v].maxv = max(val, tree[v].maxv);
	tree[v].minv = min(val, tree[v].minv);
	
	if(i <= tree[v].mid()){
		insert(L(v), i, val);
	}
	else{
		insert(R(v), i, val);
	}
}

// ״̬��(l, r), 0<=l<=r<=n-1 
// ״ֵ̬��(sum, lazy) 
// ��ʼ��(tree[v].l, tree[v].r)  ��ֹ(l, r), l >= tree[v].l, r <= tree[v].r 
void query(int v, int l, int r, int & maxv, int & minv){
	// ��ֹ״̬ 
	if(tree[v].is(l, r)){
		maxv = max(tree[v].maxv, maxv);
		minv = min(tree[v].minv, minv);
		return;
	}
	
	// ���β�ѯ 
	int mid = tree[v].mid();
	if(r <= mid){
		query(L(v), l, r, maxv, minv);
	}
	else if(l > mid){
		query(R(v), l, r, maxv, minv);
	}
	else{
		// ����������������Ľ������ 
		query(L(v), l, mid, maxv, minv);
		query(R(v), mid+1, r, maxv, minv);
	}
} 


// �߶����������������ǰѶ�n�����Ĳ���ת��Ϊ��logn������Ĳ��������������ѯ��������� 
int main(){
//	freopen("in.txt", "r", stdin);
	int val;
	scanf("%d%d", &n, &q);
	build(0, 0, n-1);
	for(int i = 0; i < n; i++){
		scanf("%d", &val);
		insert(0, i, val);
	}
	int a, b;
	for(int i = 0; i < q; i++){
		scanf("%d%d", &a, &b);
		int maxv = -inf, minv = inf;
		query(0, a-1, b-1, maxv, minv); // ��Ҫ��ѯ����ֵ�������ô��Σ�����ȫ�ֱ����� 
		printf("%d\n", maxv - minv);
	}
	return 0;
}

