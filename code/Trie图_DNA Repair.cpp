// (POJ 3691 (DNA Repair))[http://poj.org/problem?id=3691]
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int BRANCH = 4;
const int MAX = 1005;
const int inf = 0x3f3f3f3f;

class TrieMap{
private:
	struct Node{
		Node * childs[BRANCH];
		Node * prev; // ǰ׺ָ�� 
		bool bad; // Σ�ս�� 
	};
	
	Node tree[MAX]; // N * L <= 50 * 20 = 1000
	int nodeCount; // ��ʼ��Ϊ1��0�Ž�㵥����ʼ�� 
	
	/*
	 ״̬��dp[i][j]��ʾĸ������Ϊi��ǰ׺����������ڵ�j����ȫ�ڵ㣩����Ҫ�޸ĵ����ٴ��������j��Σ�ս�㣬��dp[i][j]��������� 
	       0<=i<=len(str), 0<=j<nodeCount��min(dp[len][j])���Ǵ� 
	 ������dp[0][0] = 0; ��ʾĸ������Ϊ0��ǰ׺ֻ���޸�0�ξ��ܵ���0�Ž�㣨���ڵ㣩
	       ������dp[i][j] = inf; 
	 ת�ƣ�dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
	       son(j)��j���ɴ�İ�ȫ�ӽڵ� 
	       Char(j, son(j)) != str[i] ��ʾĸ���ĵ�i+1���ַ��Ƿ��j����son(j)������ַ���ͬ
		   ��ĸ���Ƿ���Ҫ���޸�һ���ַ����ܵ���son(j) 
	*/
	int dp[MAX][MAX];
	
	int hash[256];
	
public:
	void init(){
		nodeCount = 1;
		memset(tree, 0, sizeof tree);
		hash['A'] = 0; hash['G'] = 1;
		hash['C'] = 2; hash['T'] = 3;
	}
	
	//inline int hash(char c){
	//	return 'A' == c ? 0
	//		: 'G' == c ? 1
	//		: 'C' == c ? 2
	//		: 3;
	//}
	
	// ��ģʽ������Trie���� 
	void insertTrieTree(char * dna){
		Node * root = &tree[0];
		int c;
		for(int i = 0; dna[i]; i++){
			c = hash[dna[i]];
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
	
	int minimumModify(char * dna){
		memset(dp, inf, sizeof dp);
		dp[0][0] = 0;
		
		int now = 0, pre = 1;
		// ĸ����ǰi���ַ� 
		for(int i = 0; dna[i]; i++){
			now ^= 1, pre ^= 1;
			memset(dp[now], inf, sizeof dp[now]); // ��������ر� 
			int c = hash[dna[i]];
			// ���ﰲȫ���j 
			for(int j = 0; j < nodeCount; j++){
				if(dp[pre][j] == inf) continue; // ĸ��i���ɴ���j -> ĸ��i+1���ɴ�sonj 
				Node * p = &tree[j];
				// �����޸Ĵ���dp[i+1][sonj] = min(dp[i][j] + (c != k));
				// ����Ϊ���ˡ��Ͷ��� 
				for(int k = 0; k < BRANCH; k++){
					if(!p->childs[k]->bad){
						int sonj = p->childs[k] - tree;
						dp[now][sonj] = min(dp[now][sonj], dp[pre][j] + (c != k));
					}
				}
			}
		}
		// min(dp[len][j]) ��Ϊ�� 
		int ans = inf;
		for(int j = 0; j < nodeCount; j++){
			ans = min(ans, dp[now][j]);
		}
		if(ans == inf) ans = -1;
		return ans;
	}

};

TrieMap trie;
char dna[1005];

int main(){
	int n, m;
	int t = 0;
	while(~scanf("%d", &n) && n){
		trie.init();
		for(int i = 0; i < n; i++){
			scanf("%s", dna);
			trie.insertTrieTree(dna);
		}
		trie.buildTrieMap();
		scanf("%s", dna);
		printf("Case %d: %d\n", ++t, trie.minimumModify(dna));
	}
	return 0;
}

