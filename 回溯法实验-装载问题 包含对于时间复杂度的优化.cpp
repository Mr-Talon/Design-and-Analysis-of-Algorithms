#include<iostream>
#include <iomanip>
using namespace std;

template <class T>
class Loading{
private:
	int n, //集装箱数
		* x, //当前解  长度为n 的0-1数组
		* bestx; //当前第一艘船的最优解  长度为n 的0-1数组
	int index;  //当前最优解的下标变量，为实现改进策略(2)增设的变量
	T c1, //第一艘轮船的核定载重量
		c2, //第二艘轮船的核定载重量
		* w, //集装箱重量数组
		total=0, //所有集装箱重量之和
		cw, //当前第一艘船的载重量
		bestw, //当前第一艘船的最优载重量    最优解值
		r; //剩余集装箱总重量

	void Backtrack(int i); //找到最接近第一艘轮船载重c1的最佳装载方案，最优载重值bestw，最优解数组bestx。
	void BacktrackImprove2(int i);    //动态生成bestx  防止不必要的覆盖
	void BacktrackImprove1(int i, int* bestw);    //运行最优解值计算，求得最优解值bestw 然后直接通过最优解值作为条件
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
		//对外接口
		Backtrack(0);
	}
	void Show();//输出整个装载方案
	void MaxLoading();   //非递归算法
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
void Loading<T>::Backtrack(int i){ //搜索第i层结点
	if (i == n){//到达叶节点
		if (cw > bestw){    //只有在当前解大于迄今为止的最优解的时候，才会把最优解和最优解值进行更新
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		return;
	}
	//搜索子树
	r -= w[i];      //不论一个结点是否加入  剩余的重量都会减少

	/*搜索左子树*/
	if (cw + w[i] <= c1){       //x[i]=1时的可行解约束条件  
		x[i] = 1;
		cw += w[i];
		Backtrack(i + 1);
		cw -= w[i];          // 这是左子树递归的返回点  当前载重量在回到父节点的时候需要将当前装载进去的取出   修改cw值
	}

	/*搜索右子树*/
	if (cw + r > bestw) {   //x[i]=0时增加的约束函数，剪去不含最优解的分枝
		x[i] = 0;
		Backtrack(i + 1);
	}
	r += w[i];               //这是递归的返回点【左子树右子树都会经过这个语句】   向父节点返回的时候 记录剩余重量的值需要增加相应的值
}

template<class T>
void Loading<T>::MaxLoading() {
	int i = 0;   //使用一个变量标记递归深度

	while (true){
		//搜索左子树
		while (i<n&& cw + w[i] <= c1){
			r -= w[i];
			x[i] = 1;
			cw += w[i];
			i++;
		}
		//到达叶结点
		if (i  == n) {
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		//左子树没有一直搜索到叶结点，就进入右子树
		else{
				r -= w[i];        //这里只是进入右子树一次
				x[i] = 0;
				i++;
		}

		//如果满足了不能生成右子树的条件   就会向上回溯
		while (cw + r <= bestw) {
			i--;    //先向上一层
			while (i > 0 && !x[i]) {     //除非到顶或者已经搜索过右子树（搜索过右子树这个结点就不用再看了）
				r += w[i];
				i--;
			}
			if (i == 0) {
				return;
			}
			//如果这个顶点只搜索了左子树 还有右子树没有搜索 就会进入右子树
			x[i] = 0;  
			cw -= w[i];
			i++;
		}
	}
}

template <class T>
void Loading<T>::Show(){
	//后处理函数
	//对于整个类  通过Backtrack函数已经得到了 最优解向量bestx    最优解值bestw

	int totalW = this->total;
	int c1W = 0;     //第一艘船总载重
	int i;

	for (i = 0; i < n; i++)
	{
		if (bestx[i] == 1) {    //根据解向量 计算第一艘船的总载重量
			c1W += w[i];
		}
	}

	if (totalW - c1W > c2)       //如果第一艘船剩下的重量无法全部装在第二艘船上    方案失败
	{
		cout << "  没有合理的装载方案!" << endl;
		return;                     //直接返回 没有后续输出
	}

	//下面是第一艘船尽可能大的装载  第二艘可以装下剩余的货物的情况   就是方案成功

	cout << "  最优解(第一艘船)：(";
	for (i = 0; i < n-1; i++) {
		cout << bestx[i] << ",";
	}
	cout << bestx[i] << ")" << endl;

	cout << "  最优解(第二艘船)：(";
	for (i = 0; i < n - 1; i++) {
		cout << !bestx[i] << ",";      //第二艘船的装载情况就是第一艘船取反
	}
	cout << !bestx[i] << ")" << endl;

	//一些额外输出
	cout << "  装载方案如下: " << endl;
	cout << "  第一艘船装载:" << endl;
	for (i = 0; i < n; i++) {
		if (bestx[i] == 1) {
			cout << "    集装箱" << i << ": " << setw(2) << w[i] << endl;
		}
	}
	cout << "     总载重: " << c1W;
	if (c1 - c1W == 0) {
		cout << "，装满！" << endl;
	}
	else {
		cout << "，剩余载重量" << c1 - c1W << "！" << endl;
	}

	cout << "  第二艘船装载:" << endl;
	for (i = 0; i < n; i++) {
		if (!bestx[i] == 1) {
			cout << "    集装箱" << i << ": " << setw(2) << w[i] << endl;
		}
	}
	cout << "     总载重: " << totalW - c1W;
	if (c2 - (totalW - c1W) == 0) {
		cout << "，装满！" << endl;
	}
	else {
		cout << "，剩余载重量" << c2 - (totalW - c1W) << "！" << endl;
	}
}

template<class T>
void Loading<T>::BacktrackImprove1(int i,int* bestw) {
	if (i == n) {//到达叶节点
		if (cw > *bestw) {    //只有在当前解大于迄今为止的最优解的时候，才会把最优解和最优解值进行更新
			*bestw = cw;
		}
		return;
	}
	//搜索子树
	r -= w[i];      //不论一个结点是否加入  剩余的重量都会减少

	/*搜索左子树*/
	if (cw + w[i] <= c1) {       //x[i]=1时的可行解约束条件  
		x[i] = 1;
		cw += w[i];
		BacktrackImprove1(i + 1,bestw);
		cw -= w[i];          // 这是左子树递归的返回点  当前载重量在回到父节点的时候需要将当前装载进去的取出   修改cw值
	}

	/*搜索右子树*/
	if (cw + r > *bestw) {   //x[i]=0时增加的约束函数，剪去不含最优解的分枝
		x[i] = 0;
		BacktrackImprove1(i + 1,bestw);
	}
	r += w[i];               //这是递归的返回点【左子树右子树都会经过这个语句】   向父节点返回的时候 记录剩余重量的值需要增加相应的值
}

template<class T>
void Loading<T>::BacktrackImprove2(int i) {
	//搜索第i层结点
	if (i == n){          //到达叶节点
		index = n-1;   //到达叶节点，置index=n。该语句是改进策略(2)增加的
		bestw = cw;
		cout << setw(45) << "修正bestw=" << bestw << endl;
		return;
	}

	//搜索子树
	r -= w[i];
	if (cw + w[i] <= c1){
	    //搜索左子树
		x[i] = 1;
		cw += w[i];
		BacktrackImprove2(i + 1);
		if (index == i){     //回溯上一层时，若index等于i，
			bestx[i] = x[i]; //则将x[i]存入bestx[i]
			index--;
		}
		cw -= w[i];
	}

	if (cw + r > bestw){
		//搜索右子树
		x[i] = 0;
		BacktrackImprove2(i + 1);
		if (index == i){      //回溯上一层时，若index等于i，
			bestx[i] = x[i]; //则将x[i]存入bestx[i]
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

