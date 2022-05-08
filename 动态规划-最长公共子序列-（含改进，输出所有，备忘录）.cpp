#include<iostream>
#include<set>
using namespace std;

class LCS
{
public:
	LCS(int nx, int ny, char* x, char* y);
	~LCS();
	int LCSLength();
	int LCSLengthImprove();
	int LCSLengthImproveWith2row();
	int LCSLength_Memo();
	void CLCS();
	void CLCSImprove();
	void CLCSAllAnsImprove();

private:
	int** c;		//���ڶ�̬�滮��¼·�����ȵľ���
	int** s;       //���ڼ�¼·������ľ���
	int m;     // ��һ�������еĳ���
	int n;			//�ڶ��������еĳ���
	char* a;     //��һ��������
	char* b;      //�ڶ���������
	set<string> lcs;    //������������е����
	void CLCS(int i, int j);
	void CLCSImprove(int i, int j);
	void CLCSAllAnsImprove(int i ,int j ,string str);
	int LCSLength_Memo(int i,int j);
};

LCS::LCS(int nx, int ny, char* x, char* y) {
	this->a = x;
	this->b = y;
	m = nx;
	n = ny;
	this->c = new int* [m + 1];
	this->s = new int* [m + 1];
	for (int i = 0; i <= m; i++) {
		c[i] = new int[n + 1];
		s[i] = new int[n + 1];
	}
}

LCS::~LCS() {
	for (int i = 0; i <= m; i++) {
		delete c[i];
		delete s[i];
	}
	delete c;
	delete s;
}

int LCS::LCSLength() {
	//��ʼ��
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //��ӦԪ�����  ���Ͻ�Ԫ��+1
				c[i][j] = c[i - 1][j - 1] + 1;
				s[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {    // �����Ԫ�ر���ߵ�Ԫ�ش�  �ͼ�Ϊ�ϱߵ�Ԫ��
				c[i][j] = c[i - 1][j];
				s[i][j] = 2;
			}
			else {
				c[i][j] = c[i][j - 1];     // ��ߵ�Ԫ�ر��ϱߵĴ� �ͼ�Ϊ��ߵ�Ԫ��
				s[i][j] = 3;
			}
		}
	}
	return c[m][n];   // ���½ǵ�Ԫ�ؾ����������Ž�ֵ
}


//�Ľ���������ʡ����S����Ŀռ�
int LCS::LCSLengthImprove() {
	//��ʼ��
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //��ӦԪ�����  ���Ͻ�Ԫ��+1
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {    // �����Ԫ�ر���ߵ�Ԫ�ش�  �ͼ�Ϊ�ϱߵ�Ԫ��
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];     // ��ߵ�Ԫ�ر��ϱߵĴ� �ͼ�Ϊ��ߵ�Ԫ��
			}
		}
	}
	return c[m][n];   // ���½ǵ�Ԫ�ؾ����������Ž�ֵ
}


//�������Ҫ��������У��Ϳ���ֻ�����еľ����¼���
int LCS::LCSLengthImproveWith2row() {
	//��ʼ��
	c[1][0] = 0;                       // ���ֻ�������������������еĳ��ȣ����ǲ���Ҫ��¼ÿһ������Ľ��  ֻ��Ҫ���еľ���Ϳ��Լ������ĳ���
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //��ӦԪ�����  ���Ͻ�Ԫ��+1
				c[1][j] = c[0][j - 1] + 1;
			}
			else if (c[0][j] >= c[1][j - 1]) {    // �����Ԫ�ر���ߵ�Ԫ�ش�  �ͼ�Ϊ�ϱߵ�Ԫ��
				c[1][j] = c[0][j];
			}
			else {
				c[1][j] = c[1][j - 1];     // ��ߵ�Ԫ�ر��ϱߵĴ� �ͼ�Ϊ��ߵ�Ԫ��
			}
		}
		for (int j = 0; j <= n; j++) {
			c[0][j] = c[1][j];
		}
	}
	return c[1][n];   // ���½ǵ�Ԫ�ؾ����������Ž�ֵ
}


int LCS::LCSLength_Memo() {    //  ����¼�ݹ��㷨 �ǵݹ�ӿ�
	//��ʼ��
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			c[i][j] = 0;
		}
	}
	int ans=LCSLength_Memo(m, n);
	return ans;
}

int LCS::LCSLength_Memo(int i, int j) {
	if (i == 0 || j == 0) {
		return 0;
	}
	if (c[i][j] != 0) {
		return c[i][j];                //����¼ ����м�¼ֱ�ӷ��ؽ�� ����Ҫ�ݹ����
	}
	else {
		if (a[i] == b[j]) {
			c[i][j] += LCSLength_Memo(i - 1, j - 1) + 1;
			s[i][j] = 1;
		}
		else {
			if (LCSLength_Memo(i - 1, j) >= LCSLength_Memo(i, j - 1)) {
				c[i][j] = LCSLength_Memo(i - 1, j); 
				s[i][j] = 2;
			}
			else {
				c[i][j] = LCSLength_Memo(i, j - 1);
				s[i][j] = 3;
			}
		}
	}
	return c[i][j];
}

void LCS::CLCS() {
	CLCS(m, n);
}

//�������s������ݵõ�������
void LCS::CLCS(int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (s[i][j] == 1) {
		CLCS(i - 1, j - 1);
		cout << a[i];
	}
	else if (s[i][j] == 2) {
		CLCS(i - 1, j);
	}
	else {
		CLCS(i, j - 1);
	}
}

void LCS::CLCSImprove() {
	CLCSImprove(m, n);
}

//ͨ��c�������Ϣʡ��s����Ŀռ�
void LCS::CLCSImprove(int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (a[i] == b[j]) {
		CLCSImprove(i - 1, j - 1);
		cout << a[i];
	}
	else if (c[i - 1][j] >= c[i][j - 1]) {
		CLCSImprove(i - 1, j);
	}
	else {
		CLCSImprove(i, j - 1);
	}
}

//�����Ҫ�ó����е������� ��Ҫ���㷨���н�һ���ĸĽ�
void LCS::CLCSAllAnsImprove() {
	string str;    //��¼ÿһ��������
	CLCSAllAnsImprove(m, n, str);
	set<string>::iterator it = lcs.begin();
	for (; it != lcs.end(); it++)           //�������е�Ԫ�����
		cout << *it << endl;
}

void LCS::CLCSAllAnsImprove(int i, int j, string str) {     //�������������  û��ʹ��֮ǰ����ȫ�ݹ� ����ʹ��һ���ַ�������  
	while (i>0&&j>0)
	{
		if (a[i] == b[j]) {
			str.push_back(a[i]);     //�����ַ������ַ���� �����ַ�����str����
			i--;
			j--;
		}
		else
		{
			if (c[i - 1][j] > c[i][j - 1]) {
				i--;
			}
			else if (c[i - 1][j] < c[i][j - 1]) {
				j--;
			}
			else
			{
				CLCSAllAnsImprove(i - 1, j, str);          //��Ϊ�������ַ�����ȵ���c�������������Ԫ����� �������ֿ��ܵ�·�� ���Ժ���Ȼ���뵽�˵ݹ�
				CLCSAllAnsImprove(i, j - 1, str);
				return;
			}
		}
	}
	reverse(str.begin(), str.end());     //�����֮ǰ�İ汾��������ַ����ǴӺ���ǰ��˳��������Ҫ����һ�²������յĽ��
	lcs.insert(str);      //�������ŵ������б���
}


int main() {
	char a[8] = { '0','a','b','c','b','d','a','b' };
	char b[7] = { '0','b','d','c','a','b','a' };
	LCS demo1(7, 6, a, b);
	cout << "��������" << endl;
	cout << "����������еĳ����ǣ�" << demo1.LCSLength() << endl;
	demo1.CLCS();
	cout << endl<<endl;

	LCS demo2(7, 6, a, b);
	cout << "��ʹ��s����Ľ����" << endl;
	cout << "����������еĳ����ǣ�" << demo2.LCSLengthImprove() << endl;
	demo2.CLCSImprove();
	cout << endl<<endl;

	LCS demo3(7, 6, a, b);
	cout << "���û���������������Ľ����" << endl;
	cout << "����������еĳ����ǣ�" << demo3.LCSLengthImproveWith2row() << endl << endl;

	LCS demo4(7, 6, a, b);
	cout << "ʹ�ñ���¼�Ľ����" << endl;
	cout << "����������еĳ����ǣ�" << demo4.LCSLength_Memo() << endl;
	demo4.CLCS();
	cout << endl << endl;

	LCS demo5(7, 6, a, b);
	cout << "������������У�" << endl;
	cout << "����������еĳ����ǣ�" << demo5.LCSLengthImprove() << endl;
	demo5.CLCSAllAnsImprove();
	return 0;
}