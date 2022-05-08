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
class SortableList
{
	//������������
private:
	T* l;    //һ��ָ��  ���ڶ�̬����һά����
	int maxSize;
	const int INF = 2147483647;    //�ڱ�Ԫ��
	int n;

	/*�ϲ�����*/
	void Merge(int left, int mid, int right) {
		int* temp = new int[right - left + 1];
		int i = left, j = mid + 1, k = 0;
		while ((i <= mid) && (j <= right)) {
			if (l[i] <= l[j]) {
				temp[k++] = l[i++];
			}
			else {
				temp[k++] = l[j++];
			}
		}
		while (i <= mid) {
			temp[k++] = l[i++];
		}
		while (j <= right) {
			temp[k++] = l[j++];
		}
		for (i = 0, k = left; k <= right;) {
			l[k++] = temp[i++];     //���
		}
	}
	void MergeSort(int left, int right) {
		if (left < right) {
			int mid = (left + right) / 2;
			MergeSort(left, mid);
			MergeSort(mid + 1, right);
			Merge(left, mid, right);
		}
	}

	/*��������*/
	void Swap(int i, int j) {
		int c = l[i];
		l[i] = l[j];
		l[j] = c;
	}
	int Partition(int left, int right) {
		int i = left, j = right + 1;
		do {
			do{
				i++;
			}while (l[i] < l[left]);
			do {
				j--;
			}while (l[j] > l[left]);
			if (i < j){
				Swap(i, j);
			}
		}while (i < j);
		Swap(left, j);
		return j;
	}
	void QuickSort(int left, int right) {
		if (left < right){
			int j = Partition(left, right);
			QuickSort(left, j - 1);
			QuickSort(j + 1, right);
		}
	}

	int RandomizedPartition(int left, int right)
	{
		srand((unsigned)time(NULL)); //�õ�ǰʱ����Ϊ����
		int i = rand() % (right - left) + left; //����һ��left~right��Χ�ڵ������
		Swap(i, left);
		return Partition(left, right); //����Partition����
	}

	void QuickSortRandom(int left, int right) {
		if (left < right) {
			int j = RandomizedPartition(left, right); //����RandomizedPartition����
			QuickSort(left, j - 1);
			QuickSort(j + 1, right);
		}
	}

	/*ѡ���kСԪ��*/
	void InsertSort(int left ,int right) {
		int insertItem;   //ÿһ�˴������Ԫ��
		int j;
		for (int i = 1; i <right-left+1; i++) {
			insertItem = l[left+i];       //�Ӵ��������еĵڶ���Ԫ�ؿ�ʼ����Ϊ������Ԫ��  ��Ϊ��һ��Ԫ������һ���Ļ����������
			for (j = left+i - 1; j >= left; j--) {    //������������ �Ӻ���ǰ���ҵ���Ҫ�����λ�ã��ƶ����� �ô�����Ԫ�ز���
				if (insertItem < l[j]) {
					l[j + 1] = l[j];
				}
				else
				{
					break;     //����������˵���Ѿ��ҵ�λ��  �˳��ƶ��������ģ��
				}
			}
			l[j + 1] = insertItem;   //����ȷλ�ò��������Ԫ��
		}
	}
	int Select(int k, int left, int right, int r) {
		//ÿ������r��Ԫ�أ�Ѱ�ҵ�kСԪ��
		
		int n = right - left + 1;

		if (n <= r) {
			//�������㹻С��ʹ��ֱ�Ӳ�������   �������ֱ�Ӵ���
			InsertSort(left, right);
			return left + k - 1; //ȡ���еĵ�kСԪ�أ����±�Ϊleft+k-1
		}

		for (int i = 1; i <= n / r; i++) {
			//����ȡ�й�����ÿ����м�ֵ
			InsertSort(left + (i - 1) * r, left + i * r - 1);     //ÿr��Ԫ��һ�飬��ÿ���Ԫ�ؽ�������
			Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);     //��ÿ����м�ֵ�������ӱ�ǰ�����д��
		}

		int j = Select( (int)ceil((double)n / r /  2) , left , left + (n / r) - 1 , r);      //������м�ֵ��(int)ceil((double)n / r /  2)�õ��ľ����м��ֵ   �����±�Ϊj
		Swap(left, j); //�����м�ֵΪ��ŦԪ��������left��

		j = Partition(left, right); //�Ա��ӱ����зֻ�����
		if (k == j - left + 1) {
			return j; //���ص�kСԪ���±�
		}
		else if (k < j - left + 1) {
			return Select(k, left, j - 1, r);//�����ӱ����kСԪ��
		}
		else {
			return Select(k - (j - left + 1), j + 1, right, r);
			//�����ӱ����k-(j-left+1)СԪ��
		}
	}

public:
	SortableList(int mSize) {
		maxSize = mSize;
		l = new T[maxSize+1];
		n = 0;    //��ǰԪ�ظ���
	}
	~SortableList() {
		delete[] l;
	}

	void Input(int * a, int num) {
		for (int i = 0; i < num; i++) {
			l[i] = a[i];
			n++;
		}
		l[n] = INF;    //�����ڱ�Ԫ��
	}
	void Output() {
		for (int i = 0; i < n; i++) {
			cout << l[i] << ", ";
		}
		cout << endl;
	}
	void OutPutByIndex(int index) {
		cout << l[index];
	}

	void MergeSort() {
		MergeSort(0, n - 1);
	}
	void QuickSort() {
		QuickSort(0,n-1);
	}
	void QuickSortRandom() {
		QuickSortRandom(0, n - 1);
	}

	int Select(int k) {
		return Select(k, 0, n - 1, 5);
	}
};


int main() {
	int N = 10;
	int a[10] = {1,20,15,18,25,63,456,451,22,23};
	SortableList<int> listForMergeSort(20);
	listForMergeSort.Input(a, N);
	listForMergeSort.MergeSort();
	cout << "�ϲ�����Ľ����";
	listForMergeSort.Output();

	SortableList<int> listForQuickSort(20);
	listForQuickSort.Input(a, N);
	listForQuickSort.QuickSort();
	cout << "��������Ľ����";
	listForQuickSort.Output();

	SortableList<int> listForQuickSortRandom(20);
	listForQuickSortRandom.Input(a, N);
	listForQuickSortRandom.QuickSortRandom();
	cout << "������������ֻ����Ľ����";
	listForQuickSortRandom.Output();

	SortableList<int> listForSelect(20);
	listForSelect.Input(a, N);
	int k;
	cout << "��������Ҫ���ҵ�Ԫ����ţ�" ;
	cin >> k;
	cout << "ѡ���"<<k<<"СԪ�ص������ǣ�";
	cout << listForSelect.Select(k) << endl;
	cout << "Ŀǰ�������ǣ�";
	listForSelect.Output();
	cout << "��" << k << "СԪ���ǣ�";
	listForSelect.OutPutByIndex(k-1);
	return 0;
}
