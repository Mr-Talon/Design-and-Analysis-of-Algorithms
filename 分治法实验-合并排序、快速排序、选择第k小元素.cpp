#include <iostream>
using namespace std;

template<class K, class D>
struct E
{
	//定义可排序表类每一个元素的结构
	//重载类型转换运算符
	operator K()const {
		return key;
	}
	K key;
	D data;
};

template<class T>
class SortableList
{
	//定义可排序表类
private:
	T* l;    //一个指针  用于动态生成一维数组
	int maxSize;
	const int INF = 2147483647;    //哨兵元素
	int n;

	/*合并排序*/
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
			l[k++] = temp[i++];     //输出
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

	/*快速排序*/
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
		srand((unsigned)time(NULL)); //用当前时间作为种子
		int i = rand() % (right - left) + left; //产生一个left~right范围内的随机数
		Swap(i, left);
		return Partition(left, right); //调用Partition函数
	}

	void QuickSortRandom(int left, int right) {
		if (left < right) {
			int j = RandomizedPartition(left, right); //调用RandomizedPartition函数
			QuickSort(left, j - 1);
			QuickSort(j + 1, right);
		}
	}

	/*选择第k小元素*/
	void InsertSort(int left ,int right) {
		int insertItem;   //每一趟待插入的元素
		int j;
		for (int i = 1; i <right-left+1; i++) {
			insertItem = l[left+i];       //从待排序序列的第二个元素开始，作为待插入元素  因为第一个元素自身一个的话就是有序的
			for (j = left+i - 1; j >= left; j--) {    //在有序序列中 从后往前，找到需要插入的位置，移动数组 让待插入元素插入
				if (insertItem < l[j]) {
					l[j + 1] = l[j];
				}
				else
				{
					break;     //不出现逆序说明已经找到位置  退出移动数组这个模块
				}
			}
			l[j + 1] = insertItem;   //在正确位置插入待插入元素
		}
	}
	int Select(int k, int left, int right, int r) {
		//每个分组r个元素，寻找第k小元素
		
		int n = right - left + 1;

		if (n <= r) {
			//若问题足够小，使用直接插入排序   特殊情况直接处理
			InsertSort(left, right);
			return left + k - 1; //取其中的第k小元素，其下标为left+k-1
		}

		for (int i = 1; i <= n / r; i++) {
			//二次取中规则求每组的中间值
			InsertSort(left + (i - 1) * r, left + i * r - 1);     //每r个元素一组，对每组的元素进行排序
			Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);     //将每组的中间值交换到子表前部集中存放
		}

		int j = Select( (int)ceil((double)n / r /  2) , left , left + (n / r) - 1 , r);      //求二次中间值，(int)ceil((double)n / r /  2)得到的就是中间的值   返回下标为j
		Swap(left, j); //二次中间值为枢纽元，并换至left处

		j = Partition(left, right); //对表（子表）进行分划操作
		if (k == j - left + 1) {
			return j; //返回第k小元素下标
		}
		else if (k < j - left + 1) {
			return Select(k, left, j - 1, r);//在左子表求第k小元素
		}
		else {
			return Select(k - (j - left + 1), j + 1, right, r);
			//在右子表求第k-(j-left+1)小元素
		}
	}

public:
	SortableList(int mSize) {
		maxSize = mSize;
		l = new T[maxSize+1];
		n = 0;    //当前元素个数
	}
	~SortableList() {
		delete[] l;
	}

	void Input(int * a, int num) {
		for (int i = 0; i < num; i++) {
			l[i] = a[i];
			n++;
		}
		l[n] = INF;    //设置哨兵元素
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
	cout << "合并排序的结果：";
	listForMergeSort.Output();

	SortableList<int> listForQuickSort(20);
	listForQuickSort.Input(a, N);
	listForQuickSort.QuickSort();
	cout << "快速排序的结果：";
	listForQuickSort.Output();

	SortableList<int> listForQuickSortRandom(20);
	listForQuickSortRandom.Input(a, N);
	listForQuickSortRandom.QuickSortRandom();
	cout << "快速排序（随机分划）的结果：";
	listForQuickSortRandom.Output();

	SortableList<int> listForSelect(20);
	listForSelect.Input(a, N);
	int k;
	cout << "请输入需要查找的元素序号：" ;
	cin >> k;
	cout << "选择第"<<k<<"小元素的索引是：";
	cout << listForSelect.Select(k) << endl;
	cout << "目前的序列是：";
	listForSelect.Output();
	cout << "第" << k << "小元素是：";
	listForSelect.OutPutByIndex(k-1);
	return 0;
}
