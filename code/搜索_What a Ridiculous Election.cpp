// http://icpcsummer.openjudge.cn/2018hw1/26/
#include <bits/stdc++.h>
#include <map>

using namespace std;

map<string, int> res;

char s[6];

void dfs(int op2, int op3, int steps){
//	cout << "dfs:" << s << endl;
	if(res.count(s)){
		if(steps >= res[s]){ // �����Լ�֦ 
			return;
		}
		else{
			res[s] = steps;
		}
	}
	else{
		res[s] = steps;
	}
	for(int i = 0; i < 4; i++){
		swap(s[i], s[i+1]);
		dfs(op2, op3, steps+1);
		swap(s[i], s[i+1]);
	}
	if(op2 > 0){
		for(int i = 0; i < 5; i++){
			char old = s[i];
			s[i] = (old - '0' + 1) % 10 + '0';
			dfs(op2-1, op3, steps+1);
			s[i] = old;
		}
	}
	if(op3 > 0){
		for(int i = 0; i < 5; i++){
			char old = s[i];
			s[i] = ((old - '0') * 2) % 10 + '0';
//			cout << s << " -> " << s2 << endl;
			dfs(op2, op3-1, steps+1);
			s[i] = old;
		}
	}
}

/*
˼·1����ÿһ��������bfs����(s, op2, op3)��12345���õ����·�� 
�ŵ㣺�Ե��������ٶȿ졣��������̫�࣬������һ���������������������״̬���ѽ���������� 
*/
int main(){
	ios::sync_with_stdio(false);
	sprintf(s, "12345");
	dfs(3, 2, 0);
	string s;
	while(cin >> s){
		if(res.count(s)){
			cout << res[s] << endl;
		}
		else{
			cout << -1 << endl;
		}
	}
	return 0;
}
