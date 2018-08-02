// http://icpcsummer.openjudge.cn/2018hw1/01/
// ע��ʹ��double����
// ���������Ӧ%lf 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 50005;

int L, N, M;
int a[MAX];

// m�ǳ���������ʾ�������ߵ�ʯͷ��
// judge��ʾ����̲���d�������£��ܷ����
// ��judge�����ǹ���d�ĵ����ݼ���������a < b����judge(a) >= judge(b)�����ö��ֲ��ҷֽ�� 
bool judge(int d, int m){
	long long sum = 0;
	for(int i = 1; i <= N+1 && m >= 0; i++){
		sum += a[i] - a[i-1];
		if(sum < d){
			m--;
		}
		else{
			sum = 0;
		}
	}
	return m >= 0;
}

int search(int a, int b){
	while(b > a + 1){
		int m = (a + b) / 2;
		if(judge(m, M)){
			a = m;
		}
		else{
			b = m;
		}
	}
	// Q: ѭ��������b-a��ȡֵ��Χ�Ƕ��٣� 
	if(judge(b, M)) return b; // Q: ������������������ʲô����»���� 
	return a;
}

int main(){
	scanf("%d%d%d", &L, &N, &M);
	for(int i = 1; i <= N; i++){
		scanf("%d", &a[i]);
	}
	a[N+1] = L;
	
	printf("%d", search(0, L));
	
	return 0;
}
