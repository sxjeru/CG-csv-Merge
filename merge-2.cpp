#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <imgcodecs.hpp>
#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include "config.h"
using namespace std;
using namespace cv;
using namespace Json;
void merge2() {
	//获取屏幕分辨率 (用于自动调整预览窗口尺寸)
	//int width{ GetSystemMetrics(SM_CXSCREEN) };
	//int height{ GetSystemMetrics(SM_CYSCREEN) };
	//cout << width << "	" << height << endl;

	//读取配置文件
	int quality;
	Value root;
	ifstream json("config\\config.json", ios::binary);
	Reader reader;
	if (reader.parse(json, root))
	{
		quality = root["qualityPNGfile"].asInt();
	}
	else {
		cout << "配置文件解析错误，请检查文件是否丢失，或存在语法错误！" << endl;
	}

	bool empty = false;
	//获取csv文件数量 (外循环用)
	int csvNum = 0, c;
	int sum1 = 0, sum2 = 0;	//统计处理图片数
	system("dir char\\*l.csv /b > filelist.txt");	//只对 *l.* 文件作处理
	FILE* filelist = fopen("filelist.txt", "r");
	do {
		c = fgetc(filelist);
		if (c == '\n')		csvNum++;
	} while (c != EOF);

	//将csv文件名存入数组csvName
	rewind(filelist);
	char csvName[2001][100] = { {0} };	//csv总数 <= 1000
	for (int i = 1; i <= csvNum * 2; i++) {
		fgets(csvName[i], 10, filelist);		//csv文件名字数 <= 9 (包含后缀名)
	}

	//读取csv文件，存入数组para
	//并得到差分数量 (内循环用)
	string para[10010];	//每张人物立绘包含的差分数 <= 1000
	string line;
	for (int i = 0; i < csvNum; i++) {	//外循环 (以csv文件为单位)
		int diffNum = 0;
		string csvPath = "char\\";
		csvPath += csvName[i * 2 + 1];
		ifstream csv(csvPath);
		getline(csv, line);	//跳过首行表头
		while (getline(csv, line)) {
			string num, capitalTemp;
			diffNum++;
			stringstream readstr(line);
			for (int j = 0; j < 10; j++) {
				getline(readstr, num, ',');
				capitalTemp = num.c_str();
				transform(capitalTemp.begin(), capitalTemp.end(), capitalTemp.begin(), ::tolower);		//大写转小写
				para[(diffNum - 1) * 10 + j] = capitalTemp;
				//cout << (diffNum - 1) * 10 + j << "	" << para[(diffNum - 1) * 10 + j] << endl;
			}
		}
		//获得CG路径
		for (int j = 0; j < diffNum; j++) {
			string imgOpath, imgDpath;		//原始图片 Origin 与差分图片 Diff 路径
			imgOpath = "char\\" + para[j * 10 + 1] + ".png";
			imgDpath = "char\\" + para[j * 10 + 2] + ".png";
			//合并差分CG (merge)，并保存
			vector <int> compression_params;
			compression_params.push_back(IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(quality);	//输出png压缩程度
			if (para[j * 10 + 2] != "") {
				Mat imgO = imread(imgOpath, IMREAD_UNCHANGED);	//读取透明png
				Mat imgD = imread(imgDpath, IMREAD_UNCHANGED);
				if (!imgO.data || !imgD.data) {
					goto jump;		//判断图片是否存在
					empty = true;
				}
				if (imgD.channels() != 4) {
					cvtColor(imgD, imgD, COLOR_BGR2BGRA);	//RGB -> RGBA
				}
				int x = stoi(para[j * 10 + 3]), y = stoi(para[j * 10 + 4]), w = stoi(para[j * 10 + 5]), h = stoi(para[j * 10 + 6]);	//string -> int
				Mat roi(imgO(Rect(x, y, w, h)));
				imgD.copyTo(roi);
				namedWindow("Viewer", WINDOW_NORMAL);
				moveWindow("Viewer", 1, 1);
				resizeWindow("Viewer", imgO.cols / 5.5, imgO.rows / 5.5);
				imwrite("result\\" + para[j * 10] + ".png", imgO, compression_params);
				imshow("Viewer", imgO);
				waitKey(1);
				sum1++;
			}
			else {
				Mat imgO = imread(imgOpath, IMREAD_UNCHANGED);
				if (!imgO.data) {
					goto jump;		//判断图片是否存在
					empty = true;
				}
 				namedWindow("Viewer", WINDOW_NORMAL);
				resizeWindow("Viewer", imgO.cols / 5.5, imgO.rows / 5.5);
 				imwrite("result\\" + para[j * 10 + 1] + ".png", imgO, compression_params);
				cvtColor(imgO, imgO, COLOR_BGRA2BGR);
				imshow("Viewer", imgO);
				waitKey(1);
				sum2++;
			}
		jump: ;
		}
	}
	fclose(filelist);
	system("del filelist.txt");
	if (empty) {
		cout << "警告：有部分图片无法读取，请手动检查！" << endl;
	}
	cout << "\n本次成功合并 " << sum1 << " 张差分图，并保留了 " << sum2 << " 张原图。" << endl;
	cout << "共计获得 " << sum1 + sum2 << " 张人物立绘，好耶~~\n" << endl;
	waitKey(1000);
	destroyWindow("Viewer");
}