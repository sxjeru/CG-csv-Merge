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
void merge1() {
	//��ȡ��Ļ�ֱ��� (�����Զ�����Ԥ�����ڳߴ�)
	//int width{ GetSystemMetrics(SM_CXSCREEN) };
	//int height{ GetSystemMetrics(SM_CYSCREEN) };
	//cout << width << "	" << height << endl;

	//��ȡcsv�ļ����� (��ѭ����)
	int csvNum = 0, c;
	int sum1 = 0, sum2 = 0;	//ͳ�ƴ���ͼƬ��
	system("dir event\\*l.csv /b > filelist.txt");	//ֻ�� *l.* �ļ�������
	FILE* filelist = fopen("filelist.txt", "r");
	do {
		c = fgetc(filelist);
		if (c == '\n')		csvNum++;
	} while (c != EOF);

	//��csv�ļ�����������csvName
	rewind(filelist);
	char csvName[2001][100] = { {0} };	//csv���� <= 1000
	for (int i = 1; i <= csvNum * 2; i++) {
		fgets(csvName[i], 10, filelist);		//csv�ļ������� <= 9 (������׺��)
	}

	//��ȡcsv�ļ�����������para
	//���õ�������� (��ѭ����)
	string para[1010];	//ÿ��CG�����Ĳ���� <= 100
	string line;
	for (int i = 0; i < csvNum; i++) {	//��ѭ�� (��csv�ļ�Ϊ��λ)
		int diffNum = 0;
		string csvPath = "event\\";
		csvPath += csvName[i * 2 + 1];
		ifstream csv(csvPath);
		getline(csv, line);	//�������б�ͷ
		while (getline(csv, line)) {
			string num, capitalTemp;
			diffNum++;
			stringstream readstr(line);
			for (int j = 0; j < 10; j++) {
				getline(readstr, num, ',');
				capitalTemp = num.c_str();
				transform(capitalTemp.begin(), capitalTemp.end(), capitalTemp.begin(), ::tolower);		//��дתСд
				para[(diffNum - 1) * 10 + j] = capitalTemp;
				//cout << (diffNum - 1) * 10 + j << "	" << para[(diffNum - 1) * 10 + j] << endl;
			}
		}
		//���CG·��
		for (int j = 0; j < diffNum; j++) {
			/*
			��ԭ�����ļ���ƴ�ӷ�����
			string imgOpath = csvName[1], imgDpath;
			imgOpath = imgOpath.substr(0, imgOpath.length() - 5);
			imgDpath = imgOpath + "_02" + "l.jpg";
			imgOpath += "_01l.jpg";
			*/
			string imgOpath, imgDpath;		//ԭʼͼƬ Origin ����ͼƬ Diff ·��
			imgOpath = "event\\" + para[j * 10 + 1] + ".jpg";
			imgDpath = "event\\" + para[j * 10] + ".jpg";

			//�ϲ����CG (merge)��������
			vector <int> compression_params;
			compression_params.push_back(IMWRITE_JPEG_QUALITY);
			compression_params.push_back(95);	//���jpg����
			if (para[j * 10 + 2] != "") {
				Mat imgO = imread(imgOpath);
				Mat imgD = imread(imgDpath);
				if (!imgO.data || !imgD.data)		goto jump;		//�ж�ͼƬ�Ƿ����
				int x = stoi(para[j * 10 + 3]), y = stoi(para[j * 10 + 4]), w = stoi(para[j * 10 + 5]), h = stoi(para[j * 10 + 6]);	//string -> int
				Mat roi(imgO(Rect(x, y, w, h)));
				imgD.copyTo(roi);
				namedWindow("Viewer", WINDOW_NORMAL);
				resizeWindow("Viewer", 1200, 675);
				imwrite("result\\" + para[j * 10] + ".jpg", imgO, compression_params);
				imshow("Viewer", imgO);
				waitKey(1);
				sum1++;
			}
			else {
				Mat imgO = imread(imgOpath);
				if (!imgO.data)		goto jump;//�ж�ͼƬ�Ƿ����
				namedWindow("Viewer", WINDOW_NORMAL);
				resizeWindow("Viewer", 1200, 675);
				imwrite("result\\" + para[j * 10 + 1] + ".jpg", imgO, compression_params);
				imshow("Viewer", imgO);
				waitKey(1);
				sum2++;
			}
		jump: ;
		}
	}
	fclose(filelist);
	system("del filelist.txt");
	cout << "\n���γɹ��ϲ� " << sum1 << " �Ų��ͼ���������� " << sum2 << " ��ԭͼ��" << endl;
	cout << "���ƻ�� " << sum1 + sum2 << " �� CG����Ү~~\n" << endl;
	waitKey(1000);
	destroyWindow("Viewer");
}