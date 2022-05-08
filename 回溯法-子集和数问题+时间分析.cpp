#include<iostream>
#include <time.h>
#include <Windows.h>
using namespace std;



void SumOfSub(float s, int k, float r, int* x, float m, float* w) {
	//�ݹ麯��
	//���� sΪ�±�Ϊk��֮ǰ�ĺ�   kΪ��ǰ�����±�   rΪk֮��Ԫ�صĺ�   xΪ������   wΪ����    mΪ��Ҫ���ĺ���
	x[k] = 1;
	if (s + w[k] == m) {   //���뵱ǰ����Ԫ������������Ҫ��  ��ֱ�������ǰ������
		for (int j = 0; j <= k; j++) {
			cout << x[j] << " ";
		}
		cout << endl;
	}
	else if (s + w[k] + w[k + 1] <= m) {  //������������������ ������һ�����֮��û�дﵽ����
		SumOfSub(s + w[k], k + 1, r - w[k], x, m, w);
	}
	
	if ((s + r - w[k] >= m) && (s + w[k + 1] <= m)) {  //������������������ �����ӵ�ǰ��������»��л���ӵ�m    ����������һ��Ԫ��֮��  ���ᳬ��m
		x[k] = 0;
		SumOfSub(s, k + 1, r - w[k], x, m, w);
	}
}

void SumOfSub(int* x, int n ,float m, float* w) {
	//�ǵݹ麯��  
	//����xΪ������   wΪ����    nΪ���ϵĳ���   mΪ��Ҫ���ĺ���
	float r = 0;   
	for (int i = 0; i < n; i++) {
		r += w[i];
	}
	if (r >= m && w[0] < m) {
		SumOfSub(0, 0, r, x, m, w);
	}
}

int main() {
	float w1[] = { 5,7,10,12,15,18,20 };
	int n1 = sizeof(w1) / sizeof(int);
	int* x = new int[n1];
	float m = 35;
	LARGE_INTEGER Freq, start, end;
	double time;
	QueryPerformanceFrequency(&Freq);

	QueryPerformanceCounter(&start);
	SumOfSub(x,n1,m,w1);
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / (double)Freq.QuadPart * 1000;
	printf("time= %0.3f ms\n\n", time);

	float w2[] = { 20,18,15,12,10,7,5 };
	int n2 = sizeof(w2) / sizeof(int);
	int* x2 = new int[n2];
	QueryPerformanceCounter(&start);
	SumOfSub(x2, n2, m, w2);
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / (double)Freq.QuadPart * 1000;
	printf("time= %0.3f ms\n\n", time);

	float w3[] = {15,7,20,5,18,10,12};
	int n3 = sizeof(w3) / sizeof(int);
	int* x3 = new int[n3];
	QueryPerformanceCounter(&start);
	SumOfSub(x3, n3, m, w3);
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / (double)Freq.QuadPart * 1000;
	printf("time= %0.3f ms\n\n", time);
}