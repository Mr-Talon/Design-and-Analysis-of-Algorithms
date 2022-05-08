#include<iostream>
using namespace std;

enum tower
{
	A='X',B='Y',C='Z'
};

void Move(int n, tower x, tower y) {
	cout <<"Բ��" << n << "��" << char(x) << "��" << char(y) << "�Ķ���" << endl;
}

void Hanoi(int n, tower x, tower y, tower z) {
	if (n) {
		Hanoi(n - 1, x, z, y);
		Move(n, x, y);
		Hanoi(n - 1, z, y, x);
	}
}

void main() {
	Hanoi(4, A, B, C);
}