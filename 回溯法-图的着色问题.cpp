#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4   //��ʾԪ�ز�����
#define Duplicate 5  //��ʾ���ظ�Ԫ��
using namespace std;

/*
----------------------------------------------------------------------------
���涼��ͼ���ڽӾ�����صĺ���
----------------------------------------------------------------------------
*/
typedef int ElemType;

//ͼ���ڽӾ���洢
typedef struct mGrapg {
	ElemType** a;    //��̬��ά�����ָ��
	int n;  //ͼ�Ķ������
	int e;  //ͼ��ǰ�ı���
	ElemType noEdge;  //��������֮��û�бߵ�ʱ���ھ����е���ֵ
}MGraph;

//�ڽӾ�����غ���
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue);  //��ʼ��    ���ú�����һЩ�Ķ���������ĿҪ������ȫͼ�����Գ�ʼ�������У��������Խ��ߵĶ���1��
void DestoryOfM(MGraph* mg);  //����
int ExistOfM(MGraph* mg, int u, int v);  //����<u,v>�������Ƿ����
int InsertOfM(MGraph* mg, int u, int v, ElemType w);  //����<u,v>������
int RemoveOfM(MGraph* mg, int u, int v);//ɾ��<u,v>������
void OutputOfM(MGraph* mg);

//ͼ����ز���
int InitOfM(MGraph* mg, int nSize, ElemType noEdgeValue) {
	mg->n = nSize;
	mg->e = 0;
	mg->noEdge = noEdgeValue;
	mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));  //��̬��ά�����һά�ȣ�����nsize��λ�ã����ָ��
	if (!mg->a) {
		return ERROR;
	}
	for (int i = 0; i < mg->n; i++) {
		mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));  //��̬��ά����ڶ���ά��
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
	printf("�ڽӾ����ǣ�\n");
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
������ͼ����ɫ��������㷨
----------------------------------------------------------------------------
*/
void NextValue(int k, int m, int* x, MGraph* mg) {
	//����m�ǿ���ʹ�õ���ɫ�ĸ���    ����x�ǽ�����    mg��ͼ���ڽӾ���   ����k�ǵ�ǰ����Ľ��������±�
	do
	{
		x[k] = (x[k] + 1) % (m + 1);    //��1��ʼѭ�����Խ�״̬   ���ᵽ��0
		if (!x[k]) {
			return;    //���������п��ܵĽ� ��û�д𰸾�ֱ�ӷ���                ��ʱx[k]��0  ����һ������mColoring��Դ˽����ж�
		}
		int j = 0;
		for ( j = 0; j < k; j++) {     //�������ڵĽ����ɫ�Ƿ�һ��   ��Ϊ�Ƕ�̬���ɽ�����  ����ֻ��ѭ����k
			if (mg->a[k][j] && x[k] == x[j]) {
				break;        //��ɫ��ֱͬ����ֹѭ��    �ص�do while��� ������һ����ɫ
			}
		}
		if (j == k) {
			return;            //����ѭ���ж϶�ͨ����  j�ᵽ��k
		}
	} while (1);
}

void mColoring(int k, int m, int* x, MGraph* mg) {
	//����m�ǿ���ʹ�õ���ɫ�ĸ���    ����x�ǽ�����    mg��ͼ���ڽӾ���   ����k�ǵ�ǰ����Ľ��������±�
	do
	{
		NextValue(k, m, x,mg);
		if (!x[k]) {     //�ڱ���������x��ֵ�����ж�   ���ص���0  ����û���ҵ����ʵ���ɫ     �ص���һ�εݹ�
			break;
		}
		if (k == m - 1) {         //����������� ����ǰ���������
			for (int i = 0; i < m; i++) {
				cout << x[i] << " ";
			}
			cout << endl;
		}
		else
		{
			mColoring(k + 1, m, x, mg);              //�������  �������±�Ϊk�ĵط�ȷ����һ�����  ������һ��ݹ�
		}
	} while (1);
}

void mColoring(int m, int* x, MGraph* mg) {
	//����m�ǿ���ʹ�õ���ɫ�ĸ���    ����x�ǽ�����    mg��ͼ���ڽӾ���
	mColoring(0, m, x,mg);
}

int main() {
	MGraph mg;
	int n = 2;   //ͼ�Ľ�����
	int m = n/2;
	int* x = new int[n];
	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}
	InitOfM(&mg, n, 0);
	OutputOfM(&mg);
	cout << "ͼ����ɫ������н⣺" << endl;
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
