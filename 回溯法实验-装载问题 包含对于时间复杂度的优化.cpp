#include<iostream>
#include <iomanip>
using namespace std;

template <class T>
class Loading{
private:
	int n, //��װ����
		* x, //��ǰ��  ����Ϊn ��0-1����
		* bestx; //��ǰ��һ�Ҵ������Ž�  ����Ϊn ��0-1����
	int index;  //��ǰ���Ž���±������Ϊʵ�ָĽ�����(2)����ı���
	T c1, //��һ���ִ��ĺ˶�������
		c2, //�ڶ����ִ��ĺ˶�������
		* w, //��װ����������
		total=0, //���м�װ������֮��
		cw, //��ǰ��һ�Ҵ���������
		bestw, //��ǰ��һ�Ҵ�������������    ���Ž�ֵ
		r; //ʣ�༯װ��������

	void Backtrack(int i); //�ҵ���ӽ���һ���ִ�����c1�����װ�ط�������������ֵbestw�����Ž�����bestx��
	void BacktrackImprove2(int i);    //��̬����bestx  ��ֹ����Ҫ�ĸ���
	void BacktrackImprove1(int i, int* bestw);    //�������Ž�ֵ���㣬������Ž�ֵbestw Ȼ��ֱ��ͨ�����Ž�ֵ��Ϊ����
public:
	Loading(int n,T c1,T c2,T* w ){
		this->n = n;
		this->x = new int[n];
		this->bestx = new int[n];
		this->c1 = c1;
		this->c2 = c2;
		this->w = w;
		this->index = 0;
		for (int i = 0; i < n; i++) {
			this->total += w[i];
		}
		cw = 0;
		bestw = 0;
		r = total;
	}
	~Loading(){
		delete bestx;
		delete x;
	}
	void Backtrack() {
		//����ӿ�
		Backtrack(0);
	}
	void Show();//�������װ�ط���
	void MaxLoading();   //�ǵݹ��㷨
	void BacktrackImprove2() {
		BacktrackImprove2(0);
	}
	void BacktrackImprove1() {
		int bestw = 0;
		BacktrackImprove1(0,&bestw);
		cout << bestw;
	}
};

template <class T>
void Loading<T>::Backtrack(int i){ //������i����
	if (i == n){//����Ҷ�ڵ�
		if (cw > bestw){    //ֻ���ڵ�ǰ���������Ϊֹ�����Ž��ʱ�򣬲Ż�����Ž�����Ž�ֵ���и���
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		return;
	}
	//��������
	r -= w[i];      //����һ������Ƿ����  ʣ��������������

	/*����������*/
	if (cw + w[i] <= c1){       //x[i]=1ʱ�Ŀ��н�Լ������  
		x[i] = 1;
		cw += w[i];
		Backtrack(i + 1);
		cw -= w[i];          // �����������ݹ�ķ��ص�  ��ǰ�������ڻص����ڵ��ʱ����Ҫ����ǰװ�ؽ�ȥ��ȡ��   �޸�cwֵ
	}

	/*����������*/
	if (cw + r > bestw) {   //x[i]=0ʱ���ӵ�Լ����������ȥ�������Ž�ķ�֦
		x[i] = 0;
		Backtrack(i + 1);
	}
	r += w[i];               //���ǵݹ�ķ��ص㡾���������������ᾭ�������䡿   �򸸽ڵ㷵�ص�ʱ�� ��¼ʣ��������ֵ��Ҫ������Ӧ��ֵ
}

template<class T>
void Loading<T>::MaxLoading() {
	int i = 0;   //ʹ��һ��������ǵݹ����

	while (true){
		//����������
		while (i<n&& cw + w[i] <= c1){
			r -= w[i];
			x[i] = 1;
			cw += w[i];
			i++;
		}
		//����Ҷ���
		if (i  == n) {
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		//������û��һֱ������Ҷ��㣬�ͽ���������
		else{
				r -= w[i];        //����ֻ�ǽ���������һ��
				x[i] = 0;
				i++;
		}

		//��������˲�������������������   �ͻ����ϻ���
		while (cw + r <= bestw) {
			i--;    //������һ��
			while (i > 0 && !x[i]) {     //���ǵ��������Ѿ���������������������������������Ͳ����ٿ��ˣ�
				r += w[i];
				i--;
			}
			if (i == 0) {
				return;
			}
			//����������ֻ������������ ����������û������ �ͻ����������
			x[i] = 0;  
			cw -= w[i];
			i++;
		}
	}
}

template <class T>
void Loading<T>::Show(){
	//������
	//����������  ͨ��Backtrack�����Ѿ��õ��� ���Ž�����bestx    ���Ž�ֵbestw

	int totalW = this->total;
	int c1W = 0;     //��һ�Ҵ�������
	int i;

	for (i = 0; i < n; i++)
	{
		if (bestx[i] == 1) {    //���ݽ����� �����һ�Ҵ�����������
			c1W += w[i];
		}
	}

	if (totalW - c1W > c2)       //�����һ�Ҵ�ʣ�µ������޷�ȫ��װ�ڵڶ��Ҵ���    ����ʧ��
	{
		cout << "  û�к����װ�ط���!" << endl;
		return;                     //ֱ�ӷ��� û�к������
	}

	//�����ǵ�һ�Ҵ������ܴ��װ��  �ڶ��ҿ���װ��ʣ��Ļ�������   ���Ƿ����ɹ�

	cout << "  ���Ž�(��һ�Ҵ�)��(";
	for (i = 0; i < n-1; i++) {
		cout << bestx[i] << ",";
	}
	cout << bestx[i] << ")" << endl;

	cout << "  ���Ž�(�ڶ��Ҵ�)��(";
	for (i = 0; i < n - 1; i++) {
		cout << !bestx[i] << ",";      //�ڶ��Ҵ���װ��������ǵ�һ�Ҵ�ȡ��
	}
	cout << !bestx[i] << ")" << endl;

	//һЩ�������
	cout << "  װ�ط�������: " << endl;
	cout << "  ��һ�Ҵ�װ��:" << endl;
	for (i = 0; i < n; i++) {
		if (bestx[i] == 1) {
			cout << "    ��װ��" << i << ": " << setw(2) << w[i] << endl;
		}
	}
	cout << "     ������: " << c1W;
	if (c1 - c1W == 0) {
		cout << "��װ����" << endl;
	}
	else {
		cout << "��ʣ��������" << c1 - c1W << "��" << endl;
	}

	cout << "  �ڶ��Ҵ�װ��:" << endl;
	for (i = 0; i < n; i++) {
		if (!bestx[i] == 1) {
			cout << "    ��װ��" << i << ": " << setw(2) << w[i] << endl;
		}
	}
	cout << "     ������: " << totalW - c1W;
	if (c2 - (totalW - c1W) == 0) {
		cout << "��װ����" << endl;
	}
	else {
		cout << "��ʣ��������" << c2 - (totalW - c1W) << "��" << endl;
	}
}

template<class T>
void Loading<T>::BacktrackImprove1(int i,int* bestw) {
	if (i == n) {//����Ҷ�ڵ�
		if (cw > *bestw) {    //ֻ���ڵ�ǰ���������Ϊֹ�����Ž��ʱ�򣬲Ż�����Ž�����Ž�ֵ���и���
			*bestw = cw;
		}
		return;
	}
	//��������
	r -= w[i];      //����һ������Ƿ����  ʣ��������������

	/*����������*/
	if (cw + w[i] <= c1) {       //x[i]=1ʱ�Ŀ��н�Լ������  
		x[i] = 1;
		cw += w[i];
		BacktrackImprove1(i + 1,bestw);
		cw -= w[i];          // �����������ݹ�ķ��ص�  ��ǰ�������ڻص����ڵ��ʱ����Ҫ����ǰװ�ؽ�ȥ��ȡ��   �޸�cwֵ
	}

	/*����������*/
	if (cw + r > *bestw) {   //x[i]=0ʱ���ӵ�Լ����������ȥ�������Ž�ķ�֦
		x[i] = 0;
		BacktrackImprove1(i + 1,bestw);
	}
	r += w[i];               //���ǵݹ�ķ��ص㡾���������������ᾭ�������䡿   �򸸽ڵ㷵�ص�ʱ�� ��¼ʣ��������ֵ��Ҫ������Ӧ��ֵ
}

template<class T>
void Loading<T>::BacktrackImprove2(int i) {
	//������i����
	if (i == n){          //����Ҷ�ڵ�
		index = n-1;   //����Ҷ�ڵ㣬��index=n��������ǸĽ�����(2)���ӵ�
		bestw = cw;
		cout << setw(45) << "����bestw=" << bestw << endl;
		return;
	}

	//��������
	r -= w[i];
	if (cw + w[i] <= c1){
	    //����������
		x[i] = 1;
		cw += w[i];
		BacktrackImprove2(i + 1);
		if (index == i){     //������һ��ʱ����index����i��
			bestx[i] = x[i]; //��x[i]����bestx[i]
			index--;
		}
		cw -= w[i];
	}

	if (cw + r > bestw){
		//����������
		x[i] = 0;
		BacktrackImprove2(i + 1);
		if (index == i){      //������һ��ʱ����index����i��
			bestx[i] = x[i]; //��x[i]����bestx[i]
			index--;
		}
	}
	r += w[i];
}

int main(){
	int w[5] = { 22,35,24,15,3 };
	Loading<int> ld1(5,60,40,w);  
	Loading<int> ld2(5, 60, 40, w);
	Loading<int> ld3(5, 60, 40, w);
	Loading<int> ld4(5, 60, 40, w);
	ld1.Backtrack();
	ld1.Show();
	cout << endl;
	ld2.MaxLoading();
	ld2.Show();
	cout << endl;
	ld3.BacktrackImprove2();
	ld3.Show();
	cout << endl;
	ld4.BacktrackImprove1();
	return 0;
}

