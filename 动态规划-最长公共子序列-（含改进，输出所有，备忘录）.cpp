#include<iostream>
#include<set>
using namespace std;

class LCS
{
public:
	LCS(int nx, int ny, char* x, char* y);
	~LCS();
	int LCSLength();
	int LCSLengthImprove();
	int LCSLengthImproveWith2row();
	int LCSLength_Memo();
	void CLCS();
	void CLCSImprove();
	void CLCSAllAnsImprove();

private:
	int** c;		//用于动态规划记录路径长度的矩阵
	int** s;       //用于记录路径方向的矩阵
	int m;     // 第一个子序列的长度
	int n;			//第二个子序列的长度
	char* a;     //第一个子序列
	char* b;      //第二个子序列
	set<string> lcs;    //存放所有子序列的输出
	void CLCS(int i, int j);
	void CLCSImprove(int i, int j);
	void CLCSAllAnsImprove(int i ,int j ,string str);
	int LCSLength_Memo(int i,int j);
};

LCS::LCS(int nx, int ny, char* x, char* y) {
	this->a = x;
	this->b = y;
	m = nx;
	n = ny;
	this->c = new int* [m + 1];
	this->s = new int* [m + 1];
	for (int i = 0; i <= m; i++) {
		c[i] = new int[n + 1];
		s[i] = new int[n + 1];
	}
}

LCS::~LCS() {
	for (int i = 0; i <= m; i++) {
		delete c[i];
		delete s[i];
	}
	delete c;
	delete s;
}

int LCS::LCSLength() {
	//初始化
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //对应元素相等  左上角元素+1
				c[i][j] = c[i - 1][j - 1] + 1;
				s[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {    // 上面的元素比左边的元素大  就记为上边的元素
				c[i][j] = c[i - 1][j];
				s[i][j] = 2;
			}
			else {
				c[i][j] = c[i][j - 1];     // 左边的元素比上边的大 就记为左边的元素
				s[i][j] = 3;
			}
		}
	}
	return c[m][n];   // 右下角的元素就是最后的最优解值
}


//改进方法就是省略了S数组的空间
int LCS::LCSLengthImprove() {
	//初始化
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //对应元素相等  左上角元素+1
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {    // 上面的元素比左边的元素大  就记为上边的元素
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];     // 左边的元素比上边的大 就记为左边的元素
			}
		}
	}
	return c[m][n];   // 右下角的元素就是最后的最优解值
}


//如果不需要输出子序列，就可以只用两行的矩阵记录结果
int LCS::LCSLengthImproveWith2row() {
	//初始化
	c[1][0] = 0;                       // 如果只是输出最后的最长公共子序列的长度，我们不需要记录每一个计算的结果  只需要两行的矩阵就可以计算最后的长度
	for (int i = 1; i <= n; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {    //对应元素相等  左上角元素+1
				c[1][j] = c[0][j - 1] + 1;
			}
			else if (c[0][j] >= c[1][j - 1]) {    // 上面的元素比左边的元素大  就记为上边的元素
				c[1][j] = c[0][j];
			}
			else {
				c[1][j] = c[1][j - 1];     // 左边的元素比上边的大 就记为左边的元素
			}
		}
		for (int j = 0; j <= n; j++) {
			c[0][j] = c[1][j];
		}
	}
	return c[1][n];   // 右下角的元素就是最后的最优解值
}


int LCS::LCSLength_Memo() {    //  备忘录递归算法 非递归接口
	//初始化
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			c[i][j] = 0;
		}
	}
	int ans=LCSLength_Memo(m, n);
	return ans;
}

int LCS::LCSLength_Memo(int i, int j) {
	if (i == 0 || j == 0) {
		return 0;
	}
	if (c[i][j] != 0) {
		return c[i][j];                //备忘录 如果有记录直接返回结果 不需要递归计算
	}
	else {
		if (a[i] == b[j]) {
			c[i][j] += LCSLength_Memo(i - 1, j - 1) + 1;
			s[i][j] = 1;
		}
		else {
			if (LCSLength_Memo(i - 1, j) >= LCSLength_Memo(i, j - 1)) {
				c[i][j] = LCSLength_Memo(i - 1, j); 
				s[i][j] = 2;
			}
			else {
				c[i][j] = LCSLength_Memo(i, j - 1);
				s[i][j] = 3;
			}
		}
	}
	return c[i][j];
}

void LCS::CLCS() {
	CLCS(m, n);
}

//常规根据s数组回溯得到子序列
void LCS::CLCS(int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (s[i][j] == 1) {
		CLCS(i - 1, j - 1);
		cout << a[i];
	}
	else if (s[i][j] == 2) {
		CLCS(i - 1, j);
	}
	else {
		CLCS(i, j - 1);
	}
}

void LCS::CLCSImprove() {
	CLCSImprove(m, n);
}

//通过c矩阵的信息省略s矩阵的空间
void LCS::CLCSImprove(int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (a[i] == b[j]) {
		CLCSImprove(i - 1, j - 1);
		cout << a[i];
	}
	else if (c[i - 1][j] >= c[i][j - 1]) {
		CLCSImprove(i - 1, j);
	}
	else {
		CLCSImprove(i, j - 1);
	}
}

//如果想要得出所有的子序列 需要对算法进行进一步的改进
void LCS::CLCSAllAnsImprove() {
	string str;    //记录每一个子序列
	CLCSAllAnsImprove(m, n, str);
	set<string>::iterator it = lcs.begin();
	for (; it != lcs.end(); it++)           //将集合中的元素输出
		cout << *it << endl;
}

void LCS::CLCSAllAnsImprove(int i, int j, string str) {     //输出所有子序列  没有使用之前的完全递归 而是使用一个字符串保存  
	while (i>0&&j>0)
	{
		if (a[i] == b[j]) {
			str.push_back(a[i]);     //两个字符串的字符相等 将该字符送入str保存
			i--;
			j--;
		}
		else
		{
			if (c[i - 1][j] > c[i][j - 1]) {
				i--;
			}
			else if (c[i - 1][j] < c[i][j - 1]) {
				j--;
			}
			else
			{
				CLCSAllAnsImprove(i - 1, j, str);          //因为当两个字符不相等但是c矩阵的上下两个元素相等 会有两种可能的路径 所以很自然的想到了递归
				CLCSAllAnsImprove(i, j - 1, str);
				return;
			}
		}
	}
	reverse(str.begin(), str.end());     //相比于之前的版本，这里的字符串是从后往前的顺序，所以需要反向一下才是最终的结果
	lcs.insert(str);      //将结果存放到集合中保存
}


int main() {
	char a[8] = { '0','a','b','c','b','d','a','b' };
	char b[7] = { '0','b','d','c','a','b','a' };
	LCS demo1(7, 6, a, b);
	cout << "常规结果：" << endl;
	cout << "最长公共子序列的长度是：" << demo1.LCSLength() << endl;
	demo1.CLCS();
	cout << endl<<endl;

	LCS demo2(7, 6, a, b);
	cout << "不使用s数组的结果：" << endl;
	cout << "最长公共子序列的长度是：" << demo2.LCSLengthImprove() << endl;
	demo2.CLCSImprove();
	cout << endl<<endl;

	LCS demo3(7, 6, a, b);
	cout << "如果没有输出子序列需求的结果：" << endl;
	cout << "最长公共子序列的长度是：" << demo3.LCSLengthImproveWith2row() << endl << endl;

	LCS demo4(7, 6, a, b);
	cout << "使用备忘录的结果：" << endl;
	cout << "最长公共子序列的长度是：" << demo4.LCSLength_Memo() << endl;
	demo4.CLCS();
	cout << endl << endl;

	LCS demo5(7, 6, a, b);
	cout << "输出所有子序列：" << endl;
	cout << "最长公共子序列的长度是：" << demo5.LCSLengthImprove() << endl;
	demo5.CLCSAllAnsImprove();
	return 0;
}