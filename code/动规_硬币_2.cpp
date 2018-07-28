// http://icpcsummer.openjudge.cn/2018hw1/19/
/*
״̬��dp[j] ��ʾǰi���������ճ�j�ķ�������1<=i<=n��1<=j<=x
������dp[0] = 1 
���̣�dp[j] = dp[j] + dp[j-a[i]], 1<=i<=n, x>=j>=a[i] (j-a[i] >= 0)
���Ӷȣ�O(nx)  �ռ临�Ӷȣ�O(x)

ע�⣺
1. ȷ��ÿ���±��ȡֵ��Χ����ѭ����Χ 
2. ÿһ���±궼Ӧ��>=0��ȷ����Ȼ������ 
3. ��Ҫ�ظ������ʼ������
   ��ʼ����Ϊi=0��������ʹ�i=1��ʼ���㣻 
   ��ʼ����Ϊi=1��������ʹ�i=2��ʼ���㣻 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector> 

using namespace std;

const int MAXN = 205;
const int MAXX = 10005;

int a[MAXN];
int dp[MAXX];
int kind[MAXX];

int main(){
//	freopen("in.txt", "r", stdin);
	int n, x;
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]); 
	}
	dp[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = x; j >= a[i]; j--){
			dp[j] = dp[j] + dp[j - a[i]];
		}
	}
	vector<int> res;
	for(int i = 1; i <= n; i++){
		// kind[j] ��ʾû�е�i������ʱ���j�ķ����� 
		kind[0] = 1;
		for(int j = 1; j <= x; j++){
			if(j >= a[i])
				kind[j] = dp[j] - kind[j - a[i]];
			else
				kind[j] = dp[j];
		}
		if(kind[x] == 0){
			res.push_back(a[i]);
		}
	}
	
	int S = res.size();
	printf("%d\n", S);
	for(int i = 0; i < S; i++){
		if(i != 0) printf(" ");
		printf("%d", res[i]);
	}
	return 0;
}
