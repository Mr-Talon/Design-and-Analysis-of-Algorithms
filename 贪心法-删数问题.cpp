#include<iostream>
#include<string>
using namespace std;

int MinNum(int num, int k);

int  main() {
	cout << MinNum(43002, 2) << endl;
	return 0;
}

int MinNum(int n, int k) {
	int index = 0;   //对于数字的游标
	string num = to_string(n);
	while (k>0&&index+1<num.length())       //向后比较，在还有数位没有删除和 游标不在数字的最低我位的时候可以运行
	{
		while (num[index]<=num[index+1])
		{
			index++;       //选定删除点
		}
		if (index + 1 < num.length()) {
			num.erase(index, 1);           //如果游标+1不是数字的最低位 就可以把这个数位删除 
			k--;                                    //同时需要删除的数位计数器 k --
			if (index) {
				index--;                              //游标往左移动一位
			}
		}
	}
	while (k>0)         //如果游标已经到达了最后一位并且k还没有清0
	{
		num.erase(index, 1);
		k--;
		index--;
	}

	n = stoi(num);      // 这个函数把字符串转换成数字  并且会删除高位不需要出现的0
	return n;
}