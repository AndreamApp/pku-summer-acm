#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int BRANCH = 4;
const int inf = 0x3f3f3f3f;

struct Node{
	Node * childs[BRANCH];
	Node * prev; // ǰ׺ָ�� 
	bool bad; // Σ�ս�� 
};

Node tree[1005]; // N * L <= 50 * 20 = 1000
int nodeCount; // ��ʼ��Ϊ2��0�Ž���1�Ž�㵥����ʼ�� 

/*
 ״̬��dp[i][j]��ʾĸ������Ϊi��ǰ׺����������ڵ�j����ȫ�ڵ㣩����Ҫ�޸ĵ����ٴ���
       0<=i<=len(str), 1<=j<nodeCount��min(dp[len][j])���Ǵ� 
 ������dp[0][1] = 0; ��ʾĸ������Ϊ0��ǰ׺ֻ���޸�0�ξ��ܵ���1�Ž�㣨���ڵ㣩
       ������dp[i][j] = inf; 
 ת�ƣ�dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
       Char(j, son(j)) != str[i] ��ʾĸ���ĵ�i+1���ַ��Ƿ��j����son(j)������ַ���ͬ����ĸ���Ƿ���Ҫ���޸�һ���ַ����ܵ���son(j) 
*/
int dp[1005][1005];

inline int hash(char c){
	return 'A' == c ? 0
		: 'G' == c ? 1
		: 'C' == c ? 2
		: 3;
//	return c - 'a';
}

Node * newNode(){
	Node * node = tree + nodeCount;
	nodeCount++;
	return node;
}

// ��ģʽ������Trie���� 
void insertTrieTree(char * dna){
	Node * root = &tree[0];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL){
			root->childs[c] = tree + nodeCount;
			nodeCount++;
		}
		root = root->childs[c];
	}
	root->bad = true;
}

// ��Trie�������ǰ׺ָ�룬����Trieͼ����Ϊ���н�����ú��ʵ�prev��bad 
void buildTrieMap(){
	queue<Node*> q;
	Node * root = &tree[0];
	for(int i = 0; i < BRANCH; i++){
		if(root->childs[i]){
			root->childs[i]->prev = root;
			q.push(root->childs[i]);
		}
		else{
			root->childs[i] = root;
		}
	}
	root->prev = NULL;
	
	while(q.size()){
		Node * p = q.front(); q.pop();
		for(int i = 0; i < BRANCH; i++){
			if(p->childs[i]){
				p->childs[i]->prev = p->prev->childs[i];
				p->childs[i]->bad |= p->prev->childs[i]->bad;
				q.push(p->childs[i]);
			}
			else{
				p->childs[i] = p->prev->childs[i];
			}
		}
	}
}

int searchPattern(char * dna){
	memset(dp, inf, sizeof dp);
	dp[0][0] = 0;
	
	int now = 0, pre = 1;
	for(int i = 0; dna[i]; i++){
		now ^= 1, pre ^= 1;
		memset(dp[now], inf, sizeof dp[now]); // ��������ر� 
		int c = hash(dna[i]);
		for(int j = 0; j < nodeCount; j++){
			if(dp[pre][j] == inf) continue;
			Node * p = &tree[j];
			for(int k = 0; k < BRANCH; k++){
				if(!p->childs[k]->bad){
					int sonj = p->childs[k] - tree;
					dp[now][sonj] = min(dp[now][sonj], dp[pre][j] + (c != k));
				}
			}
		}
	}
	
	int len = strlen(dna);
	int ans = inf;
	for(int i = 0; i < nodeCount; i++){
		ans = min(ans, dp[now][i]);
	}
	if(ans == inf) ans = -1;
	return ans;
}

int main(){
	int n, m;
	char dna[1005];
	int t = 0;
	while(~scanf("%d", &n) && n){
		memset(tree, 0, sizeof tree);
		nodeCount = 1;
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

