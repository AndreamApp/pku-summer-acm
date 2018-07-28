// http://icpcsummer.openjudge.cn/2018hw1/23/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;

int n, m;
int endx, endy;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

struct point{
	int x, y, steps;
	char key; // �����Կ���� 
	char layout; // ������������� 
	bool kill;
};

int S; // �������� 
char s[MAX][MAX]; // �����±� 
char maze[MAX][MAX];
bool flag[MAX][MAX][10][33]; // 0 <= lauout < 32
/*
 ״̬��point(x, y, steps, key, layout, kill), 0<=x<=n-1, 0<=y<=n-1, 0<=key<=9, 0<=layout<32, 0<=kill<=1, maze[x][y]='.'or'#'or'S'or'%d'  (flagҲ��״̬��һ���֣�����ʡ����)
 ת�ƣ�(x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key, layout, 0), maze[nx][ny] = '.', flag[nx][ny][key][layout] = 0 
       (x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key, layout, 1), maze[nx][ny] = 'S', flag[nx][ny][key][layout] = 0
       (x, y, steps, key, layout, 1) -> (x, y, steps+1, key, layout&~(1<<s[x][y]), 0), s��maze[x][y]����������±� 
       (x, y, steps, key, layout, 0) -> (nx, ny, steps+1, key+1, layout, 1), maze[nx][ny] = key+1+'0', flag[nx][ny][key][layout] = 0
       (nx, ny)����{(x-1, y), (x+1, y), (x, y-1), (x, y+1)}
 ��ʼ��(x, y, 0, 0, (1<<S)-1, 0), SΪ�������� 
 ��ֹ��(endx, endy, steps, m, layout, 0) , steps��Ϊ�𰸣�����ﲻ����ֹ״̬���޽� 
*/
int bfs(int x, int y, int m){
	// ״̬��� 
	queue<point> q;
	q.push(point{x, y, 0, 0, (1<<S)-1, 0});
	flag[x][y][0][(1<<S)-1] = 1;
	while(q.size()){
		// ���У�״̬�յ� 
		point p = q.front(); q.pop();
//		printf("visit (%d, %d), steps=%d, key=%d, layout=%d, kill=%d\n", p.x, p.y, p.steps, p.key, p.layout, p.kill);
		if(p.x == endx && p.y == endy && p.key == m){
			return p.steps;
		}
		// �����ɴ�״̬ 
		if(p.kill){
			p.steps++;
			p.layout &= ~(1<<s[p.x][p.y]);
			p.kill = 0;
			q.push(p);
		}
		else{
			for(int i = 0; i < 4; i++){
				int nx = p.x + dx[i];
				int ny = p.y + dy[i];
				if(nx >= 0 && nx < n && ny >= 0 && ny < n){
					// ״̬ת�� 
					// �ò�����Կ�׻���ɱ��������������ֱ����  
					bool gothrough = maze[nx][ny] == '.'
								 || maze[nx][ny] >= '1' && maze[nx][ny] <= '9' && maze[nx][ny] != p.key+1+'0'
								 || (maze[nx][ny] == 'S' && (p.layout&(1<<s[nx][ny])) == 0);
					if(gothrough && !flag[nx][ny][p.key][p.layout]){
						flag[nx][ny][p.key][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key, p.layout, 0});
					}
					// 'S' == maze[nx][ny] && (p.layout&(1<<s[nx][ny])) ��ʾ(nx, ny)�ڵ�ǰ������������ 
					else if('S' == maze[nx][ny] && (p.layout&(1<<s[nx][ny])) && !flag[nx][ny][p.key][p.layout]){
						flag[nx][ny][p.key][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key, p.layout, 1});
					}
					else if(maze[nx][ny] == p.key+1+'0' && !flag[nx][ny][p.key+1][p.layout]){
						flag[nx][ny][p.key+1][p.layout] = 1;
						q.push(point{nx, ny, p.steps+1, p.key+1, p.layout, 0});
					}
					else{
						continue;
					}
//					printf("push (%d, %d), steps=%d, key=%d, layout=%d, kill=%d\n", p.x, p.y, p.steps, p.key, p.layout, p.kill);
				}
			}
		}
	}
	return -1;
}

int main(){
//	freopen("in.txt", "r", stdin);
	// ע��ֻ��n=0��m=0��ֹͣ���п���n!=0����m=0 
	while(~scanf("%d%d", &n, &m) && (n != 0 || m != 0)){
		S = 0;
		int x, y;
		
		for(int i = 0; i < n; i++){
			scanf("%s", maze[i]);
			for(int j = 0; j < n; j++){
				// prepare for bfs
				memset(&flag[i][j], 0, sizeof(bool) * (10*33));
				if('K' == maze[i][j]){
					maze[i][j] = '.';
					x = i;
					y = j;
				}
				else if('T' == maze[i][j]){
					maze[i][j] = '.';
					endx = i;
					endy = j;
				}
				else if('S' == maze[i][j]){
					s[i][j] = S++; // ��¼�����±� 
				}
			}
		}
		int res = bfs(x, y, m);
		if(res == -1) printf("impossible\n");
		else printf("%d\n", res);
	}
	return 0;
}
