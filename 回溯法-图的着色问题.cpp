#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //表示元素不存在
#define Duplicate 5  //表示有重复元素
using namespace std;

/*
----------------------------------------------------------------------------
下面都是图的邻接矩阵相关的函数
----------------------------------------------------------------------------
*/
typedef int ElemType;

//图的邻接矩阵存储
typedef struct mGrapg {
	ElemType** a;    //动态二维数组的指针
	int n;  //图的顶点个数
	int e;  //图当前的边数
	ElemType noEdge;  //两个顶点之间没有边的时候在矩阵中的数值
}MGraph;

//邻接矩阵相关函数
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //初始化    【该函数有一些改动，由于题目要求是完全图，所以初始化工作中，除了主对角线的都是1】
void DestoryOfM(MGraph* mg);  //撤销
int ExistOfM(MGraph* mg, int u, int v);  //查找<u,v>这条边是否存在
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //插入<u,v>这条边
int RemoveOfM(MGraph* mg, int u, int v);//删除<u,v>这条边
void OutputOfM(MGraph* mg);

//图的相关操作
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue) {
	mg->n = nSize;
	mg->e = 0;
	mg->noEdge = noEdgeValue;
	mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));  //动态二维数组第一维度，创建nsize个位置，存放指针
	if (!mg->a) {
		return ERROR;
	}
	for (int i = 0; i < mg->n; i++) {
		mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));  //动态二维数组第二个维度
		for (int j = 0; j < mg->n; j++) {
			mg->a[i][j] = 1;
		}
		mg->a[i][i] = 0;
	}
	return OK;
} 
void DestoryOfM(MGraph* mg) {
	for (int i = 0; i < mg->n; i++) {
		free(mg->a[i]);
	}
	free(mg->a);
}
int ExistOfM(MGraph* mg, int u, int v) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge) {
		return ERROR;
	}
	return OK;
}
int InsertOfM(MGraph* mg, int u, int v, ElemType w) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v) {
		return ERROR;
	}
	if (mg->a[u][v] != mg->noEdge) {
		return Duplicate;
	}
	mg->a[u][v] = w;
	mg->e++;
	return OK;
}
int RemoveOfM(MGraph* mg, int u, int v) {
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v) {
		return ERROR;
	}
	if (mg->a[u][v] == mg->noEdge) {
		return NotPresent;
	}
	mg->a[u][v] = mg->noEdge;
	mg->e--;
	return OK;
}
void OutputOfM(MGraph* mg) {
	printf("邻接矩阵是：\n");
	for (int i = 0; i < mg->n; i++) {
		for (int j = 0; j < mg->n; j++) {
			printf("%d ", mg->a[i][j]);
		}
		printf("\n");
	}
	cout << endl;
}


/*
----------------------------------------------------------------------------
下面是图的着色问题相关算法
----------------------------------------------------------------------------
*/
void NextValue(int k, int m, int* x, MGraph* mg) {
	//参数m是可以使用的颜色的个数    参数x是解向量    mg是图的邻接矩阵   参数k是当前考查的解向量的下标
	do
	{
		x[k] = (x[k] + 1) % (m + 1);    //从1开始循环尝试解状态   最后会到达0
		if (!x[k]) {
			return;    //尝试了所有可能的解 都没有答案就直接返回                此时x[k]是0  在上一级函数mColoring会对此进行判定
		}
		int j = 0;
		for ( j = 0; j < k; j++) {     //考查相邻的结点颜色是否一样   因为是动态生成解向量  所以只会循环到k
			if (mg->a[k][j] && x[k] == x[j]) {
				break;        //颜色相同直接终止循环    回到do while语句 尝试下一个颜色
			}
		}
		if (j == k) {
			return;            //上面循环判断都通过了  j会到达k
		}
	} while (1);
}

void mColoring(int k, int m, int* x, MGraph* mg) {
	//参数m是可以使用的颜色的个数    参数x是解向量    mg是图的邻接矩阵   参数k是当前考查的解向量的下标
	do
	{
		NextValue(k, m, x,mg);
		if (!x[k]) {     //在本级函数对x的值进行判定   返回的是0  代表没有找到合适的颜色     回到上一次递归
			break;
		}
		if (k == m - 1) {         //满足输出条件 将当前解向量输出
			for (int i = 0; i < m; i++) {
				cout << x[i] << " ";
			}
			cout << endl;
		}
		else
		{
			mColoring(k + 1, m, x, mg);              //不能输出  但是在下标为k的地方确定了一个解答  就向下一层递归
		}
	} while (1);
}

void mColoring(int m, int* x, MGraph* mg) {
	//参数m是可以使用的颜色的个数    参数x是解向量    mg是图的邻接矩阵
	mColoring(0, m, x,mg);
}

int main() {
	MGraph mg;
	int n = 2;   //图的结点个数
	int m = n/2;
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}
	InitOfM(&mg, n, 0);
	OutputOfM(&mg);
	cout << "图的着色问题可行解：" << endl;
	LARGE_INTEGER Freq, start, end;
	double time;
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&start);
	mColoring(m,x,&mg);
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / (double)Freq.QuadPart * 1000;
	printf("time= %0.3f ms\n\n", time);


	DestoryOfM(&mg);
	return 0;
}
