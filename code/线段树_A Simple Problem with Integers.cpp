#include <bits/stdc++.h>

using namespace std;

const int MAX = 100005;

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
	long long sum;
	long long lazy;
	
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

void sync(int v){
	tree[v].sum += tree[v].lazy * (tree[v].r-tree[v].l+1);
	if(!tree[v].single()){
		tree[L(v)].lazy += tree[v].lazy;
		tree[R(v)].lazy += tree[v].lazy;
	}
	tree[v].lazy = 0;
}

// ���v��Ӧ������Ϊ[l,r] 
// build(0, 0, n-1) -> long long a[n];
void build(int v, int l, int r){
	tree[v].l = l;
	tree[v].r = r;
	tree[v].sum = 0;
	tree[v].lazy = 0;
	if(!tree[v].single()){
		build(L(v), l, (l+r)/2);
		build(R(v), (l+r)/2+1, r);
	}
}

// ���ڵ�v��ʼ���ҵ�i��ֵ��������Ϊval
// insert(0, i, val) -> a[i] = val; 
void insert(int v, int i, long long val){
	if(tree[v].is(i, i)){
		tree[v].sum = val;
		return;
	}
	
	tree[v].sum += val;
	
	if(i <= tree[v].mid()){
		insert(L(v), i, val);
	}
	else{
		insert(R(v), i, val);
	}
}

// a[i:j] += val;
// ���¹�����Ҳ���ǲ�ѯ
// ��n�������и��£������ʵ����ֻ�Ǹ����˲�ѯ������logn���ֽ�����
// �����ǰ�logn�������ѯ������Ȼ���lazyֵ����val 
// ����lazy���뷨�ܳ��������������ڴ��lazy page fault 
void add(int v, int l, int r, long long val){
	if(tree[v].is(l, r)){ // [l, r] = [tree[v].l, tree[v].r]
		tree[v].lazy += val;
		return;
	}
	
	tree[v].sum += val * (r-l+1); //!  [l, r] �� [tree[v].l, tree[v].r]�����Ӽ�
	
	int mid = tree[v].mid();
	if(r <= mid){
		add(L(v), l, r, val);
	}
	else if(l > mid){
		add(R(v), l, r, val);
	}
	else{
		add(L(v), l, mid, val);
		add(R(v), mid+1, r, val);
	}
}

// ״̬��(l, r), 0<=l<=r<=n-1 
// ״ֵ̬��(sum, lazy) 
// ��ʼ��(tree[v].l, tree[v].r)  ��ֹ(l, r), l >= tree[v].l, r <= tree[v].r 
long long query(int v, int l, int r){
	// ��ֹ״̬ 
	if(tree[v].is(l, r)){
		sync(v);
		return tree[v].sum;
	}
	
	// ��ѯ��ʱ����ͬ��lazy 
	sync(v);
	
	// ���β�ѯ 
	int mid = tree[v].mid();
	if(r <= mid){
		return query(L(v), l, r);
	}
	else if(l > mid){
		return query(R(v), l, r);
	}
	else{
		return query(L(v), l, mid) + query(R(v), mid+1, r);
	}
} 


// �߶����������������ǰѶ�n�����Ĳ���ת��Ϊ��logn������Ĳ��������������ѯ��������� 
int main(){
	freopen("in.txt", "r", stdin);
	long long val;
	scanf("%d%d", &n, &q);
	build(0, 0, n-1);
	for(int i = 0; i < n; i++){
		scanf("%lld", &val);
		insert(0, i, val);
	}
	char cmd[2];
	int a, b;
	long long c;
	for(int i = 0; i < q; i++){
		scanf("%s%d%d", cmd, &a, &b);
		if('C' == cmd[0]){
			scanf("%lld", &c);
			add(0, a-1, b-1, c);
		}
		else{
			long long res = query(0, a-1, b-1);
			printf("%lld\n", res);
		}
	}
	return 0;
}

