#include <bits/stdc++.h>
#include <set>

/*
ʹ���߶���ģ���������Ĺ��̣�������=������£���ѯĳ��������û�к���=�����ѯ 
�߶���������洢�������Ƿ�ȫ������(cover)���������������cover=1
����һ�����������䷶Χ̫��(1<=l<=r<=10000000)������ʵʵ�ʺ���������10000��
���Խ�����ɢ��Ԥ����ѹ�����䡣Ԥ������߶�����ʵ���Ƕ����ģ�ֻ�����Ƕ����������һ��ת���� 
*/

using namespace std;

const int MAX = 100005;

int n;
int ll[MAX];
int rr[MAX];
int discreteArr[MAX<<2];

set<int> a;
map<int, int> fix;
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
	bool cover;
	
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
node tree[MAX*15+1];

void sync(int v){
	if(!tree[v].single() && tree[v].cover){
		tree[L(v)].cover = 1;
		tree[R(v)].cover = 1;
	}
}

// ���v��Ӧ������Ϊ[l,r] 
// build(0, 0, n-1) -> long long a[n];
void build(int v, int l, int r){
	tree[v].l = l;
	tree[v].r = r;
	tree[v].cover = 0;
	if(!tree[v].single()){
		build(L(v), l, (l+r)/2);
		build(R(v), (l+r)/2+1, r);
	}
}

// ���ڵ�v��ʼ���ҵ�i��ֵ��������Ϊval
// insert(0, i, val) -> a[i] = val; 
void insert(int v, int l, int r){
	if(l == tree[v].l && r == tree[v].r){
		tree[v].cover = 1;
		return;
	}
	
	int mid = tree[v].mid();
	if(r <= mid){
		insert(L(v), l, r);
	}
	else if(l > mid){
		insert(R(v), l, r);
	}
	else{
		insert(L(v), l, mid);
		insert(R(v), mid+1, r);
	}
}

// ״̬��(l, r), 0<=l<=r<=n-1 
// ״ֵ̬��(sum, lazy) 
// ��ʼ��(tree[v].l, tree[v].r)  ��ֹ(l, r), l >= tree[v].l, r <= tree[v].r 
bool query(int v, int l, int r){
	// ��ֹ״̬ 
	if(l == tree[v].l && r == tree[v].r){
		sync(v);
		return tree[v].cover;
	}
	
	// ��ѯ��ʱ����ͬ��lazy 
	sync(v);
	
	// ���β�ѯ 
	int mid = tree[v].mid();
	bool res;
	if(r <= mid){
		res = query(L(v), l, r);
	}
	else if(l > mid){
		res = query(R(v), l, r);
	}
	else{
		// ���������ֵ���¸����� 
		res = query(L(v), l, mid) & query(R(v), mid+1, r);
	}
	tree[v].cover = tree[L(v)].cover & tree[R(v)].cover;
	return res;
} 

int input(){
	int disN = 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &ll[i], &rr[i]);
		discreteArr[disN++] = ll[i];
		discreteArr[disN++] = rr[i];
	}
	sort(discreteArr+1, discreteArr+disN);

	int j = 2;
	for (int i = 2; i < disN; i++)
	{
		if (discreteArr[i] != discreteArr[i-1]) 
			discreteArr[j++] = discreteArr[i];
	}
	for (int i = j-1; i > 1; i--)
	{
		if (discreteArr[i] != discreteArr[i-1] + 1)
			discreteArr[j++] = discreteArr[i-1] + 1;
	}
	sort(discreteArr + 1, discreteArr + j);
	return j;
}

int biSearch(int arr[], int key, int n)
{
	int l = 1, r = n-1, m = -1;
	while (l <= r)
	{
		m = l + ((r-l)>>1);
		if (arr[m] < key) l = m+1;
		else if (key < arr[m]) r = m-1;
		else break;
	}
	return m;
}

// �߶����������������ǰѶ�n�����Ĳ���ת��Ϊ��logn������Ĳ��������������ѯ��������� 
int main(){
//	freopen("in.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
//		for(int i = 0; i < n; i++){
//			scanf("%d%d", &ll[i], &rr[i]);
//			a.insert(ll[i]);
//			a.insert(rr[i]); 
//		}
//		
//		int i = 0;
//		for(set<int>::iterator it = a.begin(); it != a.end(); it++){
//			fix[*it] = i;
//			i++;
//		}
//		printf("n=%d\n", a.size());
		int j = input();
		build(0, 0, j + 100);
		
		int res = 0, l, r;
		for(int i = n-1; i >= 0; i--){
//			l = fix[ll[i]];
//			r = fix[rr[i]];
			int ql = biSearch(discreteArr, ll[i], j);
			int qr = biSearch(discreteArr, rr[i], j);
			bool cover = query(0, ql, qr);
//			printf("[%d, %d] cover=%d\n", l, r, cover);
			if(!cover){
				insert(0, ql, qr);
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

