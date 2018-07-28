// http://icpcsummer.openjudge.cn/2018hw1/30/
#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <vector>

using namespace std;

const int MAX = 12;

int n, k;
int cnt;

char maze[MAX][MAX];
bool row[MAX];
bool col[MAX];
// ״̬��(r, m, maze, row, col), 0<=r<=n-1, 0<=m<=k
// ת�ƣ�(r, m, maze, row, col) -> (r+1, m-1, maze', row', col') 
void dfs(int top, int m){
	if(m == 0) { // �õ�һ����: ��ǰ��maze 
		cnt++;
		return;
	}
	if(top == n) return;
	// �̶�r��m��ö���ҵ���ת�Ƶ�״̬������ת�ơ�ָ�����µ�״̬��״̬�ռ��к͵�ǰ״̬���� 
	for(int r = top; r < n; r++){
		for(int i = 0; i < n; i++){
			if(maze[r][i] == '#' && !row[r] && !col[i]) {
				// ת�ƣ�(r, m, maze, col) -> (r+1, m-1, maze', col') 
				maze[r][i] = '*';
				col[i] = 1;
				dfs(r+1, m-1);
				col[i] = 0;
				maze[r][i] = '#';
			}
		}
	}
}

int main(){
//	freopen("in.txt", "r", stdin);
	while(~scanf("%d%d", &n, &k) && n != -1 && k != -1){
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
		}
		cnt = 0;
		dfs(0, k);
		printf("%d\n", cnt);
	}
	
	return 0;
}
