#include<iostream>
using namespace std;

int main() {
	int m, n;
	cout << "�����������Cmn��m��n��" << endl;
	cin >> m >> n;
	int row = m - n + 2;
	int col = n + 1;
	int** c = new int* [row];
	for (int i = 0; i < row; i++) {
		c[i] = new int[col];
	}

	//��ʼ��
	for (int i = 0; i < col; i++) {
		c[1][i] = 1;
	}
	for (int i = 0; i < row; i++) {
		c[i][1] = i ;
	}

	//���ݼ���
	for (int i = 2; i < row; i++) {
		for (int j = 2; j < col; j++) {
			c[i][j] = c[i - 1][j] + c[i][j - 1];
		}
	}

	for (int i =1; i < row; i++) {
		for (int j = 1; j < col; j++) {
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}
	cout << c[row-1][col-1] << endl;
}