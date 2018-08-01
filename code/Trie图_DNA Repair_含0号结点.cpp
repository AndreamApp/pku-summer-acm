#include <bits/stdc++.h>

using namespace std;


const int BRANCH = 4;
const int inf = 0x3f3f3f3f;

struct Node{
	Node * childs[BRANCH];
	Node * prev; // ǰ׺ָ�� 
	bool bad; // Σ�ս�� 
	int level; // ���ڹ��ѵ�ʱ��dp 
};

Node tree[2000]; // N * L <= 50 * 20 = 1000
int nodeCount; // ��ʼ��Ϊ2��0�Ž���1�Ž�㵥����ʼ�� 

/*
 ״̬��dp[i][j]��ʾĸ������Ϊi��ǰ׺����������ڵ�j����ȫ�ڵ㣩����Ҫ�޸ĵ����ٴ���
       0<=i<=len(str), 1<=j<nodeCount��min(dp[len][j])���Ǵ� 
 ������dp[0][1] = 0; ��ʾĸ������Ϊ0��ǰ׺ֻ���޸�0�ξ��ܵ���1�Ž�㣨���ڵ㣩
       ������dp[i][j] = inf; 
 ת�ƣ�dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
       Char(j, son(j)) != str[i] ��ʾĸ���ĵ�i+1���ַ��Ƿ��j����son(j)������ַ���ͬ����ĸ���Ƿ���Ҫ���޸�һ���ַ����ܵ���son(j) 
*/
int dp[200][2000];

inline int hash(char c){
	return 'A' == c ? 0
		: 'G' == c ? 1
		: 'C' == c ? 2
		: 3;
//	return c - 'a';
}

// ��ģʽ������Trie���� 
void insertTrieTree(char * dna){
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL){
			root->childs[c] =  tree + nodeCount;
			nodeCount++;
		}
		root = root->childs[c];
	}
	root->bad = true;
}

// ��Trie�������ǰ׺ָ�룬����Trieͼ����Ϊ���н�����ú��ʵ�prev��bad 
void buildTrieMap(){
	for(int i = 0; i < BRANCH; i++){
		tree[0].childs[i] = &tree[1];
	}
	tree[0].prev = NULL;
	tree[1].prev = &tree[0];
	
	// �������ν���ǰ׺ָ�� 
	deque<Node*> q;
	tree[1].level = 0;
	q.push_back(&tree[1]);
	while(q.size()){
		Node * root = q.front(); q.pop_front();
		// ����ÿһ���ӽڵ� 
		for(int i = 0; i < BRANCH; i++){
			Node * child = root->childs[i];
			if(child){
				// ���Ÿ��ڵ��ǰ׺��� 
				Node * prev = root->prev;
				while(prev){
					if(prev->childs[i]){ // ƥ����ͬ��׺ 
						child->prev = prev->childs[i];
						if(child->prev->bad) child->bad = true; // Σ�ս�� 
						break;
					}
					prev = prev->prev;
				}
				// ������У����ϲ㵽�²㹹��ǰ׺ָ��
				q.push_back(child);
			}
		}
	}
}

int searchPattern(char * dna){
	memset(dp, inf, sizeof dp);
	dp[0][1] = 0;
	
	for(int i = 0; dna[i]; i++){
		int c = hash(dna[i]);
		for(int j = 1; j < nodeCount; j++){
			Node * p = &tree[j];
			bool safe = false;
			while(p){
				if(p - tree == 0){
					dp[i+1][1] = min(dp[i+1][1], dp[i][j] + 1);
					if(!safe) return -1;
				}
				else{
					// j����ֱ���ӽڵ� 
					for(int k = 0; k < BRANCH; k++){
						if(p->childs[k]){
							if(!p->childs[k]->bad){
								int sonj = p->childs[k] - tree;
								dp[i+1][sonj] = min(dp[i+1][sonj], dp[i][j] + (c != k));
								safe = true;
							}
						}
					}
				}
				// j���ǰ׺�����ӽڵ�
				p = p->prev;
			}
		}
	}
	
	int len = strlen(dna);
	
//	for(int i = 0; i <= len; i++){
//		for(int j = 1; j < nodeCount; j++){
//			printf("%d ", dp[i][j] == inf ? -1 : dp[i][j]);
//		}
//		printf("\n");
//	}
	int ans = inf;
	for(int i = 1; i < nodeCount; i++){
		ans = min(ans, dp[len][i]);
	}
	if(ans == inf) ans = -1;
	return ans;
}

/*
��ROOT���������յ�ǰ������һ
���ַ�ch�����������ϵ��ƶ�������ǰ��P������ͨ��ch
���ӵĶ��ӣ���ô����P��ǰ׺ָ��ָ��Ľڵ�Q�������
�޷��ҵ�ͨ��ch���ӵĶ��ӽڵ㣬�ٿ���Q��ǰ׺ָ�롭
ֱ���ҵ�ͨ��ch���ӵĶ��ӣ��ټ���������

������������о�����ĳ����ֹ�ڵ㣬��˵��S��������
ֹ�ڵ�����ģʽ��.

������������о�����ĳ������ֹ�ڵ��Σ�սڵ㣬
����Զ϶�S����ĳ��ģʽ����Ҫ�ҳ����ĸ�������Σ��
�ڵ��ǰ׺ָ�����ߣ�������ֹ�ڵ㼴�ɡ�
*/
bool match(char * dna){
	Node * p = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		while(1){
			if(p->childs[c]){
				p = p->childs[c];
				if(p->bad) return true;
				break;
			}
			else{
				p = p->prev;
			}
		}
	}
	return false;
}

int main(){
	int n, m;
	char dna[1005];
	int t = 0;
	while(~scanf("%d", &n) && n){
		nodeCount = 2;
		memset(tree, 0, sizeof tree);
		for(int i = 0; i < n; i++){
			scanf("%s", dna);
			insertTrieTree(dna);
		}
		buildTrieMap();
		scanf("%s", dna);
		printf("Case %d: %d\n", ++t, searchPattern(dna));
	}
	return 0;
}

