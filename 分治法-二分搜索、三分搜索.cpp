#include <iostream>
using namespace std;

template<class K, class D>
struct E
{
	//������������ÿһ��Ԫ�صĽṹ
	//��������ת�������
	operator K()const {
		return key;
	}
	K key;
	D data;
};

template<class T>
class SortbleList
{
	//������������
public:
	SortbleList(int mSize, int N, int* a) {
		maxSize = mSize;
		l = new T[maxSize];
		n = N;
		for (int i = 0; i < n; i++) {
			l[i] = a[i];
		}
	}
	~SortbleList() {
		delete[] l;
	}
	int TSearch(const T& c, int left, int right)const {
		if (left == right) {
			if (left == c) {
				return left;
			}
		}
		if (left < right) {
			int m1 = left+(right-left) / 3;
			int m2 = (int)(right - (right - left) / 3);
			if (c < l[m1]) {
				return TSearch(c, left, m1 - 1);
			}
			else if (c == l[m1]) {
				return m1;
			}
			else if (c < l[m2] && c>l[m1]) {
				return TSearch(c, m1 + 1, m2 - 1);
			}
			else if (c == l[m2])
			{
				return m2;
			}
			else {
				return TSearch(c, m2 + 1, right);
			}
		}
		return -1;
	}
private:
	T* l;    //һ��ָ��  ���ڶ�̬����һά����
	int maxSize;
	int n;
};


int main() {
	int N =10;
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	SortbleList<int> list(20, N, a);
	int result = list.TSearch(5, 0, 9);
	cout << "��������ǣ�" <<result<< endl;
	return 0;
}
