#include<iostream>
using namespace std;

bool Place(int k, int i, int* x) {
	//�ж������ʺ��Ƿ���ͬһ�л�����ͬһб����
	//k�ǵ�ǰ�ʺ�ĸ���    i��k+1���ʺ��ܷ���ڵ�i��
	for (int j = 0; j < k; j++) {
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k))) {
			return false;
		}
	}
	return true;
}

void NQueens(int k, int n, int* x) {
	for (int i = 0; i < n; i++) {       //��ʽԼ��   ��ǰ�ݹ����ѭ��n���л���û���ҵ�����ͻ�ͨ���ݹ���û���
		if (Place(k, i, x)) {                //���Է��ûʺ�   ��Լ��������
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
	//�ݹ����
	NQueens(0, n, x);
}

void NQueens1(int k, int n, int* x, int* flag) {
	//���һ�����֮��Ͳ���������Ľ����  �ڶ�����õ�ʱ�򴫵�һ��flag������ָ�룩  һ�������һ�����
	for (int i = 0; i < n&&!*flag; i++) {       //��ʽԼ��   ��ǰ�ݹ����ѭ��n���л���û���ҵ�����ͻ�ͨ���ݹ���û���
		if (Place(k, i, x)) {                //���Է��ûʺ�   ��Լ��������
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
				//�����һ����֮��  ��ص���һ���ݹ���õ�  ֱ��return��
			}
		}
	}
}

void NQueens1(int n, int* x) {
	//�ݹ����
	int flag = 0;
	NQueens1(0, n, x, &flag);
}

void NQueens2(int k, int n, int* x) {
	//ֻ���һ�� ��һ���ö�ż�������
	if (k == 0) {
		for (int i = 0; i < ceil((double)n / 2); i++) {       //��ʽԼ��   ��ǰ�ݹ����ѭ��n���л���û���ҵ�����ͻ�ͨ���ݹ���û���
			x[k] = i;
			NQueens2(k + 1, n, x);
		}
	}
	else
	{
		for (int i = 0; i < n; i++) {       //��ʽԼ��   ��ǰ�ݹ����ѭ��n���л���û���ҵ�����ͻ�ͨ���ݹ���û���
			if (Place(k, i, x)) {                //���Է��ûʺ�   ��Լ��������
				x[k] = i;
				if (k == n - 1) {
					for (int j = 0; j < n; j++) {
						cout << x[j] << " ";
					}
					cout << endl;

					if (n - 1 - x[0] != x[0]) {
						for (int j = 0; j < n; j++) {    //�۲�õ� ÿһ�й������ĶԳ�
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
	//�ݹ����
	cout << "���ݶ�ż���ʵó���" << endl;     
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