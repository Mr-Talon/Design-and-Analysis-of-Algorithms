#include<iostream>
using namespace std;

bool Place(int k, int i, int* x) {
	//判断两个皇后是否在同一列或者是同一斜线上
	//k是当前皇后的个数    i是k+1个皇后能否放在第i列
	for (int j = 0; j < k; j++) {
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k))) {
			return false;
		}
	}
	return true;
}

void NQueens(int k, int n, int* x) {
	for (int i = 0; i < n; i++) {       //显式约束   当前递归调用循环n个列还是没有找到结果就会通过递归调用回溯
		if (Place(k, i, x)) {                //可以放置皇后：   （约束函数）
			x[k] = i;
			if (k == n - 1) {
				for (int j = 0; j < n; j++) {
					cout << x[j] << " ";
				}
				cout << endl;
			}
			else
			{
				NQueens(k + 1, n, x);
			}
		}
	}
}

void NQueens(int n, int* x) {
	//递归入口
	NQueens(0, n, x);
}

void NQueens1(int k, int n, int* x, int* flag) {
	//输出一个解答之后就不输出其他的解答了  在顶层调用的时候传递一个flag变量（指针）  一旦输出了一个解答
	for (int i = 0; i < n&&!*flag; i++) {       //显式约束   当前递归调用循环n个列还是没有找到结果就会通过递归调用回溯
		if (Place(k, i, x)) {                //可以放置皇后：   （约束函数）
			x[k] = i;
			if (k == n - 1) {
				for (int j = 0; j < n; j++) {
					cout << x[j] << " ";
				}
				cout << endl;
				*flag = 1;
			}
			else {
				NQueens1(k + 1, n, x, flag);
				//当输出一个解之后  会回到上一个递归调用点  直接return掉
			}
		}
	}
}

void NQueens1(int n, int* x) {
	//递归入口
	int flag = 0;
	NQueens1(0, n, x, &flag);
}

void NQueens2(int k, int n, int* x) {
	//只输出一半 另一半用对偶性质输出
	if (k == 0) {
		for (int i = 0; i < ceil((double)n / 2); i++) {       //显式约束   当前递归调用循环n个列还是没有找到结果就会通过递归调用回溯
			x[k] = i;
			NQueens2(k + 1, n, x);
		}
	}
	else
	{
		for (int i = 0; i < n; i++) {       //显式约束   当前递归调用循环n个列还是没有找到结果就会通过递归调用回溯
			if (Place(k, i, x)) {                //可以放置皇后：   （约束函数）
				x[k] = i;
				if (k == n - 1) {
					for (int j = 0; j < n; j++) {
						cout << x[j] << " ";
					}
					cout << endl;

					if (n - 1 - x[0] != x[0]) {
						for (int j = 0; j < n; j++) {    //观察得到 每一行关于中心对称
							cout << n - x[j] - 1 << " ";
						}
						cout << endl;
					}
				}
				else
				{
					NQueens2(k + 1, n, x);
				}
			}
		}
	}

}

void NQueens2(int n, int* x) {
	//递归入口
	cout << "根据对偶性质得出：" << endl;     
	NQueens2(0, n, x);
}

int main() {
	int n = 5;
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		x[i] = -1;
	}
	//NQueens(n, x);
	NQueens1(n, x);
	//NQueens2(n, x);
}