#include <iostream>
#include "math.h"
#include <iomanip>
using namespace std;

class MatrixChain
{
public:
	MatrixChain(int mSize, int* q);	//创建二维数组m和s，一维数组p，并初始化
	int MChain();						             //一般动态规划法求最优解值
	int LookupChain();		            	//备忘录方法求最优解值（程序7-4）
	void Traceback();			           	//构造最优解的公有函数
	void Output();
	~MatrixChain();
private:
	void Traceback(int i, int j);		  //构造最优解的私有递归函数
	int LookupChain(int i, int j);		//备忘录方法私有递归（程序7-4）
	int* p;            //p用于存储矩阵的维度信息
	int** m;
	int** s;
	int n;
};

MatrixChain::MatrixChain(int mSize, int* q)
{
	n = mSize;
	m = new int* [n];   
	s = new int* [n];   
	p = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		m[i] = new int[n];  
		m[i][i] = 0;
		s[i] = new int[n];   
		s[i][i] = i;
		p[i] = q[i];
	}
	p[n] = q[n];
}

MatrixChain::~MatrixChain() {
	for (int i = 0; i <n; i++) {
		delete m[i];
		delete s[i];
	}
	delete m;
	delete s;
	delete p;
}

int MatrixChain::MChain(){
	for (int i = 0; i < n; i++) {     //初始化矩阵对角线
		m[i][i] = 0;
	}

	for (int r = 2; r <= n; r++) {    //   r控制不同级别对角线之间的步长
		for (int i = 0; i < n - r + 1; i++) {      //    i控制计算起始的行数
			int j = i + r - 1;                           //     根据偏移量计算出列数
			m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];      //省略了m[i][i]=0项  
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)     //遍历所有分割元素
			{
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];   //计算当前计算数量
				if (t < m[i][j])
				{
					m[i][j] = t;                //更新当前的m矩阵和s矩阵
					s[i][j] = k;
				}
			}
		}
	}
	return m[0][n-1];
}

void MatrixChain::Traceback(int i, int j){
	if (i == j) {         //如果是单个矩阵 直接输出
		cout << 'A' << i << " ";
		return;
	}
	//i小于分割元素，用（）将分割元素内的矩阵连乘包裹并且递归调用
	if (i < s[i][j]) {
		cout << '(';
	}
	Traceback(i, s[i][j]);
	if (i < s[i][j]) {
		cout << ')';
	}
	//i大于分割元素，用（）将分割元素内的矩阵连乘包裹并且递归调用
	if (s[i][j] + 1 < j) {
		cout << '(';
	}
	Traceback(s[i][j] + 1, j);
	if (s[i][j] + 1 < j) {
		cout << ')';
	}
}

void MatrixChain::Traceback(){
	cout << '(';
	Traceback(0, n - 1);
	cout << ')' << endl;
}

void MatrixChain::Output(){
	//输出算法中的m矩阵和 s矩阵
	int i, j;
	cout << "  m=" << endl;
	cout << "  ";
	for (j = 0; j < n; j++)
		if (j < 2) cout << setw(4) << j;
		else cout << setw(6) << j;
	cout << endl;

	for (i = 0; i < n; i++)
	{
		cout << "  " << i << " ";
		for (j = 0; j < n; j++)
		{
			if (i < j) cout << setw(6) << m[i][j];  //setw(6), 指定输出域宽为6
			else if (i == j) cout << setw(2) << m[i][j];
			else cout << setw(6) << " ";
		}
		cout << endl;
	}

	cout << "  s=" << endl;
	cout << "    ";
	for (j = 0; j < n; j++) cout << j << " ";
	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << "  " << i << " ";
		for (j = 0; j < n; j++)
		{
			if (i <= j) cout << s[i][j] << " ";
			else cout << "  ";
		}
		cout << endl;
	}
}

int MatrixChain::LookupChain(int i, int j){
	if (m[i][j] > 0) {            //如果问题已经得到解决 直接返回结果
		return m[i][j];
	}
	if (i == j) {
		return 0;     //对角线上值为0
	}
	m[i][j] = LookupChain(i + 1, j) + p[i] * p[i + 1] * p[j + 1];      
	s[i][j] = i;
	for (int k = i + 1; k < j; k++){
		int v = LookupChain(i, k) + LookupChain(k + 1, j) + p[i] * p[k + 1] * p[j + 1];
		if (v < m[i][j]){
			m[i][j] = v;
			s[i][j] = k;
		}
	}
	return m[i][j];
}

int MatrixChain::LookupChain(){
	return LookupChain(0, n - 1);
}

void main()
{
	int nn = 6;     //矩阵的个数
	int k; 
	int pp[7] = { 30,35,15,5,10,20,25 };    //6个可以连乘的矩阵的7个维度信息
	MatrixChain mm(nn, pp);

	cout << endl << "1.不用备忘录方法求矩阵连乘的数乘最少次数" << endl;
	k = mm.MChain();    
	cout << "  最少数乘次数k=" << k << endl;       
	mm.Traceback();                               
	cout << endl;
	mm.Output();

	//下面是备忘录方法
	cout << endl << "2.用备忘录方法求矩阵连乘的数乘最少次数" << endl;
	MatrixChain a(nn, pp);
	k = a.LookupChain();   cout << "  最少数乘次数k=" << k << endl;
	a.Traceback();
	cout << endl;
	a.Output();
}
