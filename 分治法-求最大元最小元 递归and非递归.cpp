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
	void MaxMin(int i, int j, T& max, T& min)const {
		//i��j��ʾ�������ķ�Χ   max��min���������ڷ������ֵ����Сֵ
		T max1, min1;
		/*����ģС��һ���̶ȿ���ֱ�ӵõ���������*/
		if (i == j) {
			max = min = l[i];
		}
		else if (i == j - 1) {
			if (l[i] < l[j]) {
				max = l[j];
				min = l[i];
			}
			else
			{
				max = l[i];
				min = l[j];
			}
		}
		/*��ģ���Ƚϴ� ��Ҫ�ֽ�*/
		else
		{
			int m = (i + j) / 2;
			MaxMin(i, m, max, min);
			MaxMin(m + 1, j, max1, min1);
			//��С��ģ����Ľ�ϲ��ɴ�����Ľ�
			if (max < max1) {
				max = max1;
			}
			if (min > min1) {
				min = min1;
			}
		}
	}

	void MaxMinWithoutRecursion(int i, int j, T& max, T& min)const {
		int index = 2;
		if (l[0] > l[1]) {
			max = l[0];
			min = l[1];
		}
		else
		{
			max = l[1];
			min = l[0];
		}
		for (int k = 2; k < n-1; k+=2) {
			int tempMax, tempMin;
			if (l[k] > l[k + 1]) {
				tempMax = l[k];
				tempMin = l[k + 1];
			}
			else
			{
				tempMax = l[k + 1];
				tempMin = l[k];
			}
			if (tempMax > max) {
				max = tempMax;
			}
			if (tempMin < min) {
				min = tempMin;
			}
		}
	}
private:
	T* l;    //һ��ָ��  ���ڶ�̬����һά����
	int maxSize;
	int n;
};


int main() {
	int N = 8;
	int a[8] = { 5,1,8,3,4,6,2,0 };
	int Max, Min;
	SortbleList<int> list(20, N, a);
	list.MaxMin(0, N - 1, Max, Min);
	cout << "Max=" << Max << " " << "Min=" << Min << endl;
	int Max1, Min1;
	list.MaxMinWithoutRecursion(0, N-1 , Max1, Min1);
	cout << "Max1=" << Max1 << " " << "Min1=" << Min1 << endl;
	return 0;
}