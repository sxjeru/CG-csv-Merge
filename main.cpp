#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <imgcodecs.hpp>
#include <core.hpp>
#include <highgui.hpp>
using namespace std;
using namespace cv;
int main(void) {
	//获取屏幕分辨率 (用于自动调整预览窗口尺寸)
	//int width{ GetSystemMetrics(SM_CXSCREEN) };
	//int height{ GetSystemMetrics(SM_CYSCREEN) };
	//cout << width << "	" << height << endl;
	//获取csv文件数量 (外循环用)
	int csvNum = 0, c;
	int sum1=0, sum2=0;	//统计处理图片数
	system("dir event\\*l.csv /b > filelist.txt");
	FILE* filelist = fopen("filelist.txt", "r");
	do {
		c = fgetc(filelist);
		if (c == '\n')		csvNum++;
	} while (c != EOF);
	//将csv文件名存入数组csvName
	rewind(filelist);
	char csvName[200][100] = { {0} };
	for (int i = 1; i <= csvNum * 2; i++) {
		fgets(csvName[i], 10, filelist);
	}
	//读取csv文件，存入数组para
	//并得到差分数量 (内循环用)
	string para[300];
	string line;
	for (int i = 0; i < csvNum; i++) {	//外循环 (以csv文件为单位)
		int diffNum = 0;
		string csvPath = "event\\";
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
			/*
			（原本的文件名拼接方案）
			string imgOpath = csvName[1], imgDpath;
			imgOpath = imgOpath.substr(0, imgOpath.length() - 5);
			imgDpath = imgOpath + "_02" + "l.jpg";
			imgOpath += "_01l.jpg";
			*/
			string imgOpath, imgDpath;		//原始图片 Origin 与差分图片 Diff 路径
			imgOpath = "event\\" + para[j * 10 + 1] + ".jpg";
			imgDpath = "event\\" + para[j * 10] + ".jpg";
			//合并差分CG (merge)
			vector <int> compression_params;
			compression_params.push_back(IMWRITE_JPEG_QUALITY);
			compression_params.push_back(95);	//输出jpg质量
			if (para[j * 10 + 2] != "") {
				Mat imgO = imread(imgOpath);
				Mat imgD = imread(imgDpath);
				int x = stoi(para[j * 10 + 3]), y = stoi(para[j * 10 + 4]), w = stoi(para[j * 10 + 5]), h = stoi(para[j * 10 + 6]);	//string -> int
				Mat roi(imgO(Rect(x, y, w, h)));
				imgD.copyTo(roi);
				namedWindow("Viewer", WINDOW_NORMAL);
				resizeWindow("Viewer", 1200, 675);
				imwrite("result\\"+para[j*10]+".jpg", imgO, compression_params);
				imshow("Viewer", imgO);
				waitKey(1);
				sum1++;
			}
			else {
				Mat imgO = imread(imgOpath);
				namedWindow("Viewer", WINDOW_NORMAL);
				resizeWindow("Viewer", 1200, 675);
				imwrite("result\\"+para[j*10+1]+".jpg", imgO, compression_params);
				imshow("Viewer", imgO);
				waitKey(1);
				sum2++;
			}
		}
	}
	fclose(filelist);
	system("del filelist.txt");
	cout << "本次成功合并" << sum1 << "张差分图，并保留了" << sum2 << "张原图。" << endl;
	cout << "共计获得CG " << sum1 + sum2 << "张，请便~~"<<endl;
	system("pause");
	return 0;
}