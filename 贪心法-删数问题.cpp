#include<iostream>
#include<string>
using namespace std;

int MinNum(int num, int k);

int  main() {
	cout << MinNum(43002, 2) << endl;
	return 0;
}

int MinNum(int n, int k) {
	int index = 0;   //�������ֵ��α�
	string num = to_string(n);
	while (k>0&&index+1<num.length())       //���Ƚϣ��ڻ�����λû��ɾ���� �α겻�����ֵ������λ��ʱ���������
	{
		while (num[index]<=num[index+1])
		{
			index++;       //ѡ��ɾ����
		}
		if (index + 1 < num.length()) {
			num.erase(index, 1);           //����α�+1�������ֵ����λ �Ϳ��԰������λɾ�� 
			k--;                                    //ͬʱ��Ҫɾ������λ������ k --
			if (index) {
				index--;                              //�α������ƶ�һλ
			}
		}
	}
	while (k>0)         //����α��Ѿ����������һλ����k��û����0
	{
		num.erase(index, 1);
		k--;
		index--;
	}

	n = stoi(num);      // ����������ַ���ת��������  ���һ�ɾ����λ����Ҫ���ֵ�0
	return n;
}