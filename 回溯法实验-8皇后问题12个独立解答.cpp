#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

class nqueen{
public:
	nqueen(int N);              //���캯��
	~nqueen();                  //��������
	void nqueens();
	void Out_Solutions();       //���Solutions�����е�12��������
private:
	bool Place(int k, int i);   //Լ������, �ж������ʺ��Ƿ���ͬһ�л�ͬһб�ߣ�����ͻ����true
	void nqueens(int k);     //�ʺ�����������
	bool Constructing(int num); //�ж��Ƿ�����⣬���򷵻�true��
	bool Test(int num);

	int* y;                     //��ʱ����任��Ŀ��н�
	int** solutions;            //��12�������⡣���ڵݹ飬solutions���鲻��ֻ��12�У���������������
	int number;                 //������ĸ���
	int n;                      //n-�ʺ�����
	int* x;                     //���һ����
};

nqueen::nqueen(int N)  //���캯��
{
	n = N;  number = 0;
	x = new int[n];
	solutions = new int* [20];
	for (int i = 0; i < 20; i++) {
		solutions[i] = new int[n];
	}
	y = new int[n];
}

nqueen::~nqueen()      //��������
{
	delete[]x;
	for (int i = 0; i < 20; i++) {
		delete[]solutions[i];
	}
	delete[]solutions;
	delete[]y;
}

//���solutions�����е�12��������
void nqueen::Out_Solutions()
{
	int i, j;

	for (i = 0; i < number; i++)
	{
		cout << setw(4) << i + 1 << " (";
		for (j = 0; j < n - 1; j++) {
			cout << solutions[i][j] << ",";
		}
		cout << solutions[i][j] << ")" << endl;
	}
}

//Լ������, �ж������ʺ��Ƿ���ͬһ�л�ͬһб�ߣ�����ͻ����true
bool nqueen::Place(int k, int i)
{
	for (int j = 0; j < k; j++)
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
			return false;	//��ͬһ�л�ͬһб�ߣ�����false 
	return true;
}

void nqueen::nqueens()
{
	nqueens(0);
}

void nqueen::nqueens(int k)
{
	for (int i = 0; i < n; i++){
		if (Place(k, i)){    //�жϵ�k���ʺ��ܷ�����±�i��  
			x[k] = i;
			if (k == n - 1){
				for (i = 0; i < n; i++) {
					solutions[number][i] = x[i];  //��x[i]��Ԫ�ط��ڵ�number����ĵ�i��λ�ã�����һ����x[]�ŵ�solutions�����е�number�С�
				}
				if (Constructing(number)) {    //�ж��Ƿ������   �ж�ͨ����number+1   number��¼�˶�����ĸ���
					number++;          
				}	  		
			}
			else {
				nqueens(k + 1);
			}
		}
	}
}

bool nqueen::Constructing(int num){   	//���µõ��Ľ�x[]��7�ֱ任�󣬵õ��Ľ�����浽y[]��,��֮ǰ�Ķ�����Ƚϣ���ͬ����false����ͬ����true 
	int j, k;			

	//���µõ��Ľ�x[]��ת90�㱣�浽y[]��
	for (j = 0; j < n; j++) { 
		y[ solutions[num][j] ] = n - 1 - j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {    //test�ж��Ƿ�����ͬ  ֻ�з�����ͬ  �Ż��ߵ�return��� ֱ����Constructing���ط�  ��������ظ���
			return false;
		}
	}

	//���µõ��Ľ�x[]��ת180�㱣�浽y[]��
	for (j = 0; j < n; j++) {                      
		y[n-1-j] = n -1 - solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//���µõ��Ľ�x[]��ת270�㱣�浽y[]��
	for (j = 0; j < n; j++) {
		y[n - 1 - solutions[num][j]] = j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//���µõ��Ľ�x[]���¶ԳƱ任�󱣴浽y[]��
	for (j = 0; j < n; j++) {
		y[n - 1 - j] =solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//���µõ��Ľ�x[]���ҶԳƱ任�󱣴���y[]��
	for (j = 0; j < n; j++) {
		y[j] = n - 1 - solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//���µõ��Ľ�x[]����y=x�Խ��߶ԳƱ任�󱣴浽y[]��
	for (j = 0; j < n; j++) {
		y[solutions[num][j]] = j ;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//���µõ��Ľ�x[]����y=-x�Խ��߶ԳƱ任�󱣴浽y[]��
	for (j = 0; j < n; j++) {
		y[n - 1 - solutions[num][j]] = n - 1 - j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	return true;                            //��֮ǰ�õ��Ķ����ⲻͬ������true
}

//�жϱ任��õ��Ľ�y[]��֮ǰ�õ��Ķ�����solutions[num][]�Ƿ���ͬ
bool nqueen::Test(int num){
	for (int i = 0; i < n; i++){
		if (y[i] != solutions[num][i]) {
			return false;                //����ͬ������false���ý�Ϊ������
		}
	}
	return true;                   //��ȣ�����true���ý�Ϊ�ظ���
}

void main()
{
	int n = 8;
	nqueen solution(n);
	cout << "8-�ʺ������12��������(solutions����)��" << endl;
	solution.nqueens();
	solution.Out_Solutions();
}
