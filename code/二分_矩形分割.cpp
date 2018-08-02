// http://icpcsummer.openjudge.cn/2018hw1/03/
// ��һЩС���η�Ϊ���������֣�ʹ��������>=�ұ�
// ͬʱ�����������֮����С������������������ܴ�
/*
�������뵽ʹ�ö���������
�⣺��������������k, kΪ���� 
��ռ䣺[0, R] �е�����
�б�����f(k) = ���С������� - �ұ�С�����������������
�ⷨ�����ַ���k0ʹ��f(k0) >= 0��Ȼ����k1���½�ʹ��f(k1) == f(k0) 

ע�⣺
1. �����ı߽�( [0,R] or [0,R+1] )
2. ����������( upperbound or lowerbound ) 
*/ 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 10005;

struct rect{
	long long left, right, width, height;
};

int R, N;
rect r[MAX];

// judge(k) ��ʾk��ߵľ��� - k�ұߵľ������
// ��֤judge(k)����k�������� 
long long judge(int k){
	long long lsum = 0, rsum = 0;
	for(int i = 0; i < N; i++){
		if(r[i].right <= k){
			lsum += r[i].width * r[i].height;
		}
		else if(r[i].left >= k){
			rsum += r[i].width * r[i].height;
		}
		else{
			lsum += (k - r[i].left) * r[i].height;
			rsum += (r[i].right - k) * r[i].height;
		}
	}
	return lsum - rsum;
}

int search(int a, int b){
	// find the minimum positive fk
	// b��������Ҫ�Ľ����b��ȡ(0,R] 
	long long fk;
	while(b - a > 1){
		int m = (a + b) / 2;
		fk = judge(m);
		if(fk > 0){
			b = m;
		}
		else if(fk < 0){
			a = m;
		}
		else{
			a = b = m;
			break;
		}
	}
	// find the upper bound of fk
	double fk0 = judge(b) + 0.5;
	a = 0, b = R+1; // ע��a��������Ҫ�Ľ��, Ϊ��ʹa�ܱ�ȡ[0,R]������b=R+1 
	while(b - a > 1){
		int m = (a + b) / 2;
		fk = judge(m);
		if(fk > fk0){
			b = m;
		}
		else if(fk < fk0){
			a = m;
		}
	}
	return a;
}

int main(){
	scanf("%d%d", &R, &N);
	long long t;
	for(int i = 0; i < N; i++){
		scanf("%lld%lld%lld%lld", &r[i].left, &t, &r[i].width, &r[i].height);
		r[i].right = r[i].width + r[i].left;
	}
	
	printf("%d", search(0, R));
	
	return 0;
}
