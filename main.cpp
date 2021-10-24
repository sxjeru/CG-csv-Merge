#include "merge-1.cpp"
#include "merge-2.cpp"
#include "merge-3.cpp"
//链接器-命令行中添加"/FORCE:MULTIPLE "以忽略LNK2005报错
#include <iostream>
#include <windows.h>
using namespace std;
int main() {
	//输出"option.txt"内容
	string cont;
	int ch, line = 0;
	FILE* option = fopen("config\\options.txt", "r");
	do {
		ch = fgetc(option);
		if (ch == '\n')		line++;
	} while (ch != EOF);
	rewind(option);		//指针返回开头
	char temp1[100];
	string temp2="";
	for (int i = 1; i <= line*2; i++) {
		fgets(temp1, 101, option);	//单行内容不超过100字
		if (temp2 != temp1) {	//去重
			cout << temp1;
			temp2 = temp1;
		}
	}
	cout << "请输入：";
	char input=getchar();
	cout << endl;
	if (input == '1')	merge1();
	if (input == '2')	merge2();
	if (input == '3') {
		merge3();
		merge1();
		merge2();
	}
	system("pause");
	return 0;
}