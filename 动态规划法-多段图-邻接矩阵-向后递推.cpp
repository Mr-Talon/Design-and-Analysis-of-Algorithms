#include <iostream>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //表示元素不存在
#define Duplicate 5  //表示有重复元素
using namespace std;
typedef int ElemType;

class Grapg
{
public:
	Grapg(int nSize, ElemType noEdgeValue) {
		n = nSize;
		noEdge = noEdgeValue;
		e = 0;
		a = new ElemType * [nSize];
		for (int i = 0; i < n; i++) {
			a[i] = new ElemType[nSize];  //动态二维数组第二个维度
			for (int j = 0; j < n; j++) {
				a[i][j] = noEdge;
			}
			a[i][i] = 0;
		}
	}

	~Grapg() {
		for (int i = 0; i < n; i++) {
			delete[] a[i];
		}
		delete a;
	}

	int ExistOfM(int u, int v) {
		if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v || a[u][v] == noEdge) {
			return ERROR;
		}
		return OK;
	}

	int InsertOfM( int u, int v, ElemType w) {
		if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v) {
			return ERROR;
		}
		if (a[u][v] != noEdge) {
			return Duplicate;
		}
		a[u][v] = w;
		e++;
		return OK;
	}

	int RemoveOfM( int u, int v) {
		if (u<0 || v<0 || u>n - 1 || v>n - 1 || u == v) {
			return ERROR;
		}
		if (a[u][v] == noEdge) {
			return NotPresent;
		}
		a[u][v] = noEdge;
		e--;
		return OK;
	}

	void OutputOfM( ) {
		printf("邻接矩阵是：\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("\t%d ", a[i][j]);
			}
			printf("\n");
		}
	}

	int FMultiGraph(int k, int* p) {
		int c,q;
		int* cost = new int[n];
		int* d = new int[n];

		cost[0] = 0, d[0] = -1;    //初始化向后递推式
		for (int j = 1; j < n; j++) {
			float min = INFINITY;
			for (int i =0; i < n; i++) {
				if (a[i][j] == noEdge||a[i][j]==0) {
					continue;
				}
				int v =i;
				if (a[i][j] + cost[v] < min) {
					min = a[i][j] + cost[v];
					q = v;
				}
			}
			cost[j] = min, d[j ] = q;
		}
		for (int i = 0; i < n; i++) {
			cout << cost[i] << " " << d[i] << endl;
		}
		//下面是导出结果
		p[0] = 0;
		p[k - 1] = n - 1;
		c = cost[n-1];
		for (int j = k-2; j >0 ; j--) {
			p[j] = d[p[j + 1]];
		}
		delete[] cost;
		delete[] d;
		return c;
	}

private:
	ElemType** a;    //动态二维数组的指针
	int n;  //图的顶点个数
	int e;  //图当前的边数
	ElemType noEdge;  //两个顶点之间没有边的时候在矩阵中的数值
};

int main() {
	Grapg g(9, 999);
	g.InsertOfM(0, 1, 5);
	g.InsertOfM(0, 2, 2);
	g.InsertOfM(1, 3, 3);
	g.InsertOfM(1, 5, 3);
	g.InsertOfM(2, 3, 6);
	g.InsertOfM(2, 4, 5);
	g.InsertOfM(2, 5, 8);
	g.InsertOfM(3, 6, 1);
	g.InsertOfM(3, 7, 4);
	g.InsertOfM(4, 6, 6);
	g.InsertOfM(4, 7, 2);
	g.InsertOfM(5, 6, 6);
	g.InsertOfM(5, 7, 2);
	g.InsertOfM(6, 8, 7);
	g.InsertOfM(7, 8, 3);
	g.OutputOfM();

	int* p = new int[5];
	int c = g.FMultiGraph(5, p);
	for (int i = 0; i < 5; i++) {
		cout << p[i] << " ";
	}
	return 0;
}


