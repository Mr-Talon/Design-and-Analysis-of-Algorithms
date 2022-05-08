#include <iostream>
#include "math.h"
#include <iomanip>
using namespace std;

class MatrixChain
{
public:
	MatrixChain(int mSize, int* q);	//������ά����m��s��һά����p������ʼ��
	int MChain();						             //һ�㶯̬�滮�������Ž�ֵ
	int LookupChain();		            	//����¼���������Ž�ֵ������7-4��
	void Traceback();			           	//�������Ž�Ĺ��к���
	void Output();
	~MatrixChain();
private:
	void Traceback(int i, int j);		  //�������Ž��˽�еݹ麯��
	int LookupChain(int i, int j);		//����¼����˽�еݹ飨����7-4��
	int* p;            //p���ڴ洢�����ά����Ϣ
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
	for (int i = 0; i < n; i++) {     //��ʼ������Խ���
		m[i][i] = 0;
	}

	for (int r = 2; r <= n; r++) {    //   r���Ʋ�ͬ����Խ���֮��Ĳ���
		for (int i = 0; i < n - r + 1; i++) {      //    i���Ƽ�����ʼ������
			int j = i + r - 1;                           //     ����ƫ�������������
			m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];      //ʡ����m[i][i]=0��  
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)     //�������зָ�Ԫ��
			{
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];   //���㵱ǰ��������
				if (t < m[i][j])
				{
					m[i][j] = t;                //���µ�ǰ��m�����s����
					s[i][j] = k;
				}
			}
		}
	}
	return m[0][n-1];
}

void MatrixChain::Traceback(int i, int j){
	if (i == j) {         //����ǵ������� ֱ�����
		cout << 'A' << i << " ";
		return;
	}
	//iС�ڷָ�Ԫ�أ��ã������ָ�Ԫ���ڵľ������˰������ҵݹ����
	if (i < s[i][j]) {
		cout << '(';
	}
	Traceback(i, s[i][j]);
	if (i < s[i][j]) {
		cout << ')';
	}
	//i���ڷָ�Ԫ�أ��ã������ָ�Ԫ���ڵľ������˰������ҵݹ����
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
	//����㷨�е�m����� s����
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
			if (i < j) cout << setw(6) << m[i][j];  //setw(6), ָ��������Ϊ6
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
	if (m[i][j] > 0) {            //��������Ѿ��õ���� ֱ�ӷ��ؽ��
		return m[i][j];
	}
	if (i == j) {
		return 0;     //�Խ�����ֵΪ0
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
	int nn = 6;     //����ĸ���
	int k; 
	int pp[7] = { 30,35,15,5,10,20,25 };    //6���������˵ľ����7��ά����Ϣ
	MatrixChain mm(nn, pp);

	cout << endl << "1.���ñ���¼������������˵��������ٴ���" << endl;
	k = mm.MChain();    
	cout << "  �������˴���k=" << k << endl;       
	mm.Traceback();                               
	cout << endl;
	mm.Output();

	//�����Ǳ���¼����
	cout << endl << "2.�ñ���¼������������˵��������ٴ���" << endl;
	MatrixChain a(nn, pp);
	k = a.LookupChain();   cout << "  �������˴���k=" << k << endl;
	a.Traceback();
	cout << endl;
	a.Output();
}
