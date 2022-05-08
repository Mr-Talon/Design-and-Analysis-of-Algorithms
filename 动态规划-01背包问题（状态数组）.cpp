#include<iostream>
using namespace std;

class Knapstack{
public:
	Knapstack(int numOfObj, int M, int* p, int* w);
	~Knapstack();
	void  Cal_m();
	void Traceback();
private:
	int n;  //总共多少个物品
	int* p;      //存放每个物品的受益
	int* w;    //存放每个物品的重量
	int** m;    //状态数组m
	int M;    //背包的最大载重量
	int* x;  //结果向量
	int Cal_m(int* p, int* w, int** m,int n,int M);
	void Traceback(int i, int j, int* p, int* w, int** m, int* x);
};

Knapstack::Knapstack(int numOfObj,int M,int *p,int* w){
	this->n = numOfObj;
	this->M = M;
	this->p = p;
	this->w = w;
	//创建并初始化m
	for (int i = 0; i < n + 1; i++) {
		this->m = new int* [n+1];
	}
	for (int j = 0; j < M + 1; j++) {
		this->m[j] = new int[M+1];
	}
	for (int i = 0; i < n + 1; i++) {
		this->m[i][0] = 0;
	}
	for (int i = 0; i < M + 1; i++) {
		this->m[0][i] = 0;
	}
	x = new int[n];
}

Knapstack::~Knapstack(){
	delete x;
	for(int i=0;i<n;i++){
		delete m[i];
	}
	delete m;
}

void  Knapstack::Cal_m() {
	cout <<"背包问题的最大受益是：" << Cal_m(p, w, m, n, M) << endl;
}

int Knapstack::Cal_m(int* p, int* w, int** m, int n, int M) {
	//计算状态矩阵，返回最大受益
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			if (w[i-1] > j) {
				m[i][j] = m[i - 1][j];         //这种情况是放不下的这个物体，直接用上一行的数据
			}
			else
			{
				if (m[i - 1][j] > m[i - 1][j - w[i-1]] + p[i-1]) {
					m[i][j] = m[i - 1][j];             //对是否装下当前物体的受益进行比较
				}
				else
				{
					m[i][j] = m[i - 1][j - w[i-1]] + p[i-1];
				}
			}
		}
	}

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < M + 1; j++) {
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
	return m[n][M];
}

void Knapstack::Traceback() {
	Traceback(n, M, p, w, m, x);
	cout << "背包问题的结果向量是：（";
	for (int i = 0; i < n; i++) {
		cout << x[i] << "， ";
	}
	cout << ")";
}

void Knapstack::Traceback(int i, int j, int* p, int* w, int** m, int* x) {
	if (i == 0) {
		return;
	}
	else
	{
		if (m[i][j] == m[i-1][j])
		{
			x[i-1] = 0;     //状态数组当前行的数据等于上一行的数据  就是没有装进物体，从上一行开始递归
			Traceback(i - 1, j, p, w, m, x);
		}
		else
		{
			x[i-1] = 1;
			Traceback(i - 1, j - w[i - 1], p, w, m, x);
		}
	}
}

int main() {
	int p[6] = { 8,10,6,3,7,2 };
	int w[6] = { 4,6,2,2,5,1 };
	Knapstack demo1 (6, 12, p, w);
	demo1.Cal_m();
	demo1.Traceback();
	return 0;
}
