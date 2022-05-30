#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

int gcd(int m, int n) {
	if (m == 0) {
		return n;
	}
	if (n == 0) {
		return m;
	}
	if (m > n) {
		swap(m, n);
	}

	while (m>0)
	{
		int c = n % m;
		n = m;
		m = c;
	}
	return n;
}

int choiceE(int f) {
	int e = rand() % f + 1;
	while (gcd(e,f)!=1)
	{
		e = rand() % f + 1;
	}
	return e;
}

int ext_euclid(int a, int b, int f, int e){
	int m, n, t;
	if (e == 1) return b;
	m = f / e;
	n = f % e;
	t = a - b * m;
	ext_euclid(b, t, e, n);
}


void main()
{
	//��������p��q
	int p, q;
	cout << "����һ������p(��101):";
	cin >> p;
	cout << "����һ������q(��113):";
	cin >> q;//���n=p*q��ֵ
	int n = p * q;
	cout << "�������ʱ��ÿ������Ĵ�С���ܳ���n=p*q="<<n<<endl;

	//��æ�(n)=(p-1)*(q-1)��ֵ
	int f = (p - 1) * (q - 1);
	cout << "ģ��(n)=(p-1)*(q-1)=" << f << endl << endl;

	//ѡȡ���(n)���ʵĹ�Կe
	int e = choiceE(f);
	cout << "�������(n)���ʵĹ�Կe:"<<e<<endl;
	//��e�ͦ�(n)����˽Կd
	int d = ext_euclid(0, 1, f, e);
	while (d <= 0) d += f;
	cout << "ͨ��������չŷ������㷨�������ԿdΪ��" << d << endl;

	//�������ɵĹ�Կ{e,n}������M���м���
	int M, C;
	cout << "���ڹ�Կ{e,n}��˽Կ{d,n}����������ϡ�\n\n��������Ҫ������������ݽ��м���(��9726)��";
	cin >> M;
	C = 1;
	for (int i = 1; i <= e; i++)
	{
		C = C * M % n;    //ʹ�ð�ģ���㹫ʽ
	}
	cout << "����M=" << M << "�����ܺ�õ�����C=M^e(mod n)��" << C << endl;
	//�������ɵ�˽Կ˽Կ{e,n}������C���н���
	M = 1;
	for (int i = 1; i <= d; i++)
	{
		M = M * C % n;
	}
	cout << "����C=" << C << "�����ܺ�õ�����M=C^d(mod n)��" << M << endl;
}