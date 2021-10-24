//链接器-命令行中添加"/FORCE:MULTIPLE "以忽略LNK2005报错
#include <iostream>
#include <windows.h>
using namespace std;
void merge3() {
	//输出操作说明
	string cont;
	int ch, line = 0;
	FILE* help3 = fopen("config\\help-merge-3.txt", "r");
	do {
		ch = fgetc(help3);
		if (ch == '\n')		line++;
	} while (ch != EOF);
	rewind(help3);		//指针返回开头
	char temp1[100];
	string temp2 = "";
	for (int i = 1; i <= line * 2; i++) {
		fgets(temp1, 101, help3);	//单行内容不超过100字
		if (temp2 != temp1) {	//去重
			cout << temp1;
			temp2 = temp1;
		}
	}
	system("pause");
}