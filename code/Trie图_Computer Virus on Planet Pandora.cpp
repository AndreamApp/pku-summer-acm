// (POJ 3691 (DNA Repair))[http://poj.org/problem?id=3691]
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int BRANCH = 26;
const int MAX = 260000;
const int inf = 0x3f3f3f3f;

bool visit[MAX];

class TrieMap {
private:
	struct Node {
		Node * childs[BRANCH];
		Node * prev; // ǰ׺ָ�� 
		int bad; // Σ�ս�� 
	};

	Node tree[MAX]; // N * L <= 250 * 1000 = 250000
	int nodeCount; // ��ʼ��Ϊ1��0�Ž�㵥����ʼ�� 

public:
	void init() {
		nodeCount = 1;
		memset(tree, 0, sizeof tree);
		memset(visit, 0, sizeof visit);
	}

	inline int hash(char c) {
		return c - 'A';
	}

	// ��ģʽ������Trie���� 
	void insertTrieTree(char * dna) {
		Node * root = &tree[0];
		int c;
		for (int i = 0; dna[i]; i++) {
			c = hash(dna[i]);
			if (root->childs[c] == NULL) {
				root->childs[c] = tree + nodeCount;
				nodeCount++;
			}
			root = root->childs[c];
		}
		root->bad = true;
	}

	// ��Trie�������ǰ׺ָ�룬����Trieͼ����Ϊ���н�����ú��ʵ�prev��bad 
	void buildTrieMap() {
		queue<Node*> q;
		Node * root = &tree[0];
		for (int i = 0; i < BRANCH; i++) {
			if (root->childs[i]) {
				root->childs[i]->prev = root;
				q.push(root->childs[i]);
			}
			else {
				root->childs[i] = root;
			}
		}
		root->prev = NULL;

		while (q.size()) {
			Node * p = q.front(); q.pop();
			for (int i = 0; i < BRANCH; i++) {
				if (p->childs[i]) {
					p->childs[i]->prev = p->prev->childs[i];
					p->childs[i]->bad += p->prev->childs[i]->bad;
					q.push(p->childs[i]);
				}
				else {
					p->childs[i] = p->prev->childs[i];
				}
			}
		}
	}

	int match(char * dna, int begin, int end, int delta) {
		Node * p = &tree[0];
		int res = 0;
		int c;
		for (int i = begin; i != end; i += delta) {
			c = hash(dna[i]);
			while (1) {
				if (p->childs[c]) {
					// �ӽڵ��Ҳ�����ȥǰ׺ָ���� 
					//					if(p->childs[c] == tree){
					//						p = p->prev;
					//					}
					// ƥ�䵽һ��Σ�ս�� 
					if (p->childs[c]->bad) {
						p = p->childs[c];
						if(!visit[p - tree]){
							visit[p - tree] = 1;
							res += p->bad;
						}
						break;
					}
					// �ӽڵ��ǰ�ȫ��� 
					else {
						p = p->childs[c];
						break;
					}
				}
				else {
					break;
				}
			}
		}
		return res;
	}

};

int decimal(int n) {
	int cnt = 0;
	while (n) {
		n /= 10;
		cnt++;
	}
	return cnt;
}

TrieMap trie;
char dna[5100050];
char rna[5100050];

int main() {
	int n, m;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		trie.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", dna);
			trie.insertTrieTree(dna);
		}
		trie.buildTrieMap();
		scanf("%s", dna);
		int i = 0, q;
		char c;
		for (int j = 0; dna[j]; j++) {
			if ('[' == dna[j]) {
				sscanf(dna + j, "[%d%c]", &q, &c);
				j += decimal(q) + 2;
				for (int k = 0; k < q; k++) {
					rna[i] = c;
					i++;
				}
			}
			else {
				rna[i] = dna[j];
				i++;
			}
		}
		printf("%d\n", trie.match(rna, 0, strlen(rna), 1) + trie.match(rna, strlen(rna) - 1, -1, -1));
	}
	return 0;
}

