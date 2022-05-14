#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

class nqueen{
public:
	nqueen(int N);              //构造函数
	~nqueen();                  //析构函数
	void nqueens();
	void Out_Solutions();       //输出Solutions数组中的12个独立解
private:
	bool Place(int k, int i);   //约束函数, 判断两个皇后是否在同一列或同一斜线，不冲突返回true
	void nqueens(int k);     //皇后问题主函数
	bool Constructing(int num); //判断是否独立解，是则返回true。
	bool Test(int num);

	int* y;                     //临时保存变换后的可行解
	int** solutions;            //存12个独立解。由于递归，solutions数组不能只开12行，否则输出结果出错！
	int number;                 //独立解的个数
	int n;                      //n-皇后问题
	int* x;                     //存放一个解
};

nqueen::nqueen(int N)  //构造函数
{
	n = N;  number = 0;
	x = new int[n];
	solutions = new int* [20];
	for (int i = 0; i < 20; i++) {
		solutions[i] = new int[n];
	}
	y = new int[n];
}

nqueen::~nqueen()      //析构函数
{
	delete[]x;
	for (int i = 0; i < 20; i++) {
		delete[]solutions[i];
	}
	delete[]solutions;
	delete[]y;
}

//输出solutions数组中的12个独立解
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

//约束函数, 判断两个皇后是否在同一列或同一斜线，不冲突返回true
bool nqueen::Place(int k, int i)
{
	for (int j = 0; j < k; j++)
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
			return false;	//在同一列或同一斜线，返回false 
	return true;
}

void nqueen::nqueens()
{
	nqueens(0);
}

void nqueen::nqueens(int k)
{
	for (int i = 0; i < n; i++){
		if (Place(k, i)){    //判断第k个皇后能否放在下标i列  
			x[k] = i;
			if (k == n - 1){
				for (i = 0; i < n; i++) {
					solutions[number][i] = x[i];  //第x[i]列元素放在第number个解的第i个位置，即将一个解x[]放到solutions数组中的number行。
				}
				if (Constructing(number)) {    //判断是否独立解   判断通过给number+1   number记录了独立解的个数
					number++;          
				}	  		
			}
			else {
				nqueens(k + 1);
			}
		}
	}
}

bool nqueen::Constructing(int num){   	//把新得到的解x[]做7种变换后，得到的结果保存到y[]中,和之前的独立解比较，相同返回false，不同返回true 
	int j, k;			

	//把新得到的解x[]旋转90°保存到y[]中
	for (j = 0; j < n; j++) { 
		y[ solutions[num][j] ] = n - 1 - j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {    //test判断是否有相同  只有返回相同  才会走到return语句 直接让Constructing返回否定  这个解是重复解
			return false;
		}
	}

	//把新得到的解x[]旋转180°保存到y[]中
	for (j = 0; j < n; j++) {                      
		y[n-1-j] = n -1 - solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//把新得到的解x[]旋转270°保存到y[]中
	for (j = 0; j < n; j++) {
		y[n - 1 - solutions[num][j]] = j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//把新得到的解x[]上下对称变换后保存到y[]中
	for (j = 0; j < n; j++) {
		y[n - 1 - j] =solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//把新得到的解x[]左右对称变换后保存在y[]中
	for (j = 0; j < n; j++) {
		y[j] = n - 1 - solutions[num][j];
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//把新得到的解x[]关于y=x对角线对称变换后保存到y[]中
	for (j = 0; j < n; j++) {
		y[solutions[num][j]] = j ;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	//把新得到的解x[]关于y=-x对角线对称变换后保存到y[]中
	for (j = 0; j < n; j++) {
		y[n - 1 - solutions[num][j]] = n - 1 - j;
	}
	for (k = 0; k < num; k++) {
		if (Test(k)) {
			return false;
		}
	}

	return true;                            //与之前得到的独立解不同，返回true
}

//判断变换后得到的解y[]与之前得到的独立解solutions[num][]是否相同
bool nqueen::Test(int num){
	for (int i = 0; i < n; i++){
		if (y[i] != solutions[num][i]) {
			return false;                //不相同，返回false，该解为独立解
		}
	}
	return true;                   //相等，返回true，该解为重复解
}

void main()
{
	int n = 8;
	nqueen solution(n);
	cout << "8-皇后问题的12个独立解(solutions数组)：" << endl;
	solution.nqueens();
	solution.Out_Solutions();
}
