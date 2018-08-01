#include <bits/stdc++.h>

using namespace std;

const int CHILD = 26;

struct Node{
	Node * childs[CHILD];
	Node * prev; // ǰ׺ָ�� 
	bool bad; // Σ�ս�� 
};

Node tree[500000]; // 250 * 1000 <= 500000
int nodeCount;

inline int hash(char c){
	return c - 'A';
}

// ��ģʽ������Trie���� 
void insertTrieTree(char * dna){
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL)
			root->childs[c] =  tree + nodeCount++;
		root = root->childs[c];
	}
	root->bad = true;
}

// ��Trie�������ǰ׺ָ�룬����Trieͼ����Ϊ���н�����ú��ʵ�prev��bad 
void buildTrieMap(){
	for(int i = 0; i < CHILD; i++){
		tree[0].childs[i] = &tree[1];
	}
	tree[0].prev = NULL;
	tree[1].prev = &tree[0];
	// ʹ��ջģ������������� 
	deque<Node*> q;
	q.push_back(&tree[1]);
	while(q.size()){
		Node * root = q.back(); q.pop_back();
		// ����ÿһ���ӽڵ� 
		for(int i = 0; i < CHILD; i++){
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
				// �ݹ鹹��ǰ׺ָ�� 
				q.push_back(child);
			}
		}
	}
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
int searchPattern(char * dna){
	int res = 0;
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->bad){
			res++;
		}
		if(root->childs[c]){
			root = root->childs[c];
			if(dna[i+1] == 0 && root->bad){
				res++;
			}
		}
		else{
			Node * prev = root->prev;
			while(prev){
				if(prev->childs[c]){ // �ҵ�ĳ����׺ƥ�䣬���Լ������� 
					root = prev->childs[c];
					break;
				}
				prev = prev->prev;
			}
			// ͨ��ǰ׺ָ���ҵ�0�Ž���ˣ�û��ƥ���ģʽ�� 
			if(prev == NULL){
				break;
			}
		}
	}
	return res;
}

int main(){
	int t, n;
	char virus[1005]; 
	char program[1005]; 
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%s", virus);
			insertTrieTree(virus);
		} 
		buildTrieMap();
		scanf("%s", program);
		printf("%d", searchPattern(program));
	}
	return 0;
}

