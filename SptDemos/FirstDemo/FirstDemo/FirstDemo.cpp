// FirstDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#include <string>
#include "opencv2\opencv.hpp"
#include <iostream>
#include "FirstDemo.h"
#include "highgui.h"

std::wstring str2wstr(const std::string wstrSrc, UINT CodePage = CP_UTF8)
{
	if (wstrSrc.length() == 0)
		return L"";

	int buflen = MultiByteToWideChar(CodePage, 0, wstrSrc.c_str(), -1, NULL, 0) + 1;
	if (buflen == 0)
		return L"";

	wchar_t * buf = new wchar_t[buflen];
	std::wstring retn = L"";
	if (buf)
	{
		memset(buf, 0, buflen * 2);
		::MultiByteToWideChar(CodePage, 0, wstrSrc.c_str(), -1, buf, buflen);
		retn = buf;
		delete[]buf;
	}
	return retn;
}

int ShowImage(std::string strImagePath,const std::string strTitle)
{
	IplImage * img = cvLoadImage(strImagePath.c_str());
	cvNamedWindow(strTitle.c_str(), CV_WINDOW_AUTOSIZE);
	cvShowImage(strTitle.c_str(), img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow(strTitle.c_str());
	return E_SUCCESS;
}

int PlayMovie(std::string strMoviePath,std::string strTitle)
{
	if (!PathFileExists(str2wstr(strMoviePath).c_str()))
	{
		::MessageBox(0, 0, L"File doesn't exist!!",0);
		return E_FILE_NOT_EXIST;
	}
	cvNamedWindow(strTitle.c_str(), CV_WINDOW_AUTOSIZE);
	CvCapture * capture = cvCreateFileCapture(strMoviePath.c_str());
	IplImage * frame;
	while (TRUE)
	{
		frame = cvQueryFrame(capture);
		if (frame == NULL)
		{
			::MessageBox(0, 0, L"Finished!", 0);
			break;
		}
		cvShowImage(strTitle.c_str(), frame);
		char c = cvWaitKey(33);
		if (c == 27)
		{
			break;
		}		
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow(strTitle.c_str());

	return E_SUCCESS;
}

int KNNTest(int a)
{
	using namespace std;
	using namespace cv;
	using namespace cv::ml;
	Mat img = imread(DIGITS);
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);							//将图片灰度矩阵赋给gray
	int b = 20;
	int m = gray.rows / b;										//原图为1000*2000
	int n = gray.cols / b;										//裁剪为5000个20*20的小图块
	Mat  data, labels;											//特征矩阵
	for (int i = 0; i < n; i++)
	{
		int offsetCol = i*b;									//列上的偏移量
		for (int j = 0; j < m; j++)								// j行 i列
		{ 
			int offsetRow = j*b;								//行上的偏移量
															    //截取20*20的小块
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);
			data.push_back(tmp.reshape(0, 1));					//序列化后放入特征矩阵
			labels.push_back((int)j / 5);						//对应的标注
		}

	}
	data.convertTo(data, CV_32F);								//uchar型转换为cv_32f 即单精度float
	int samplesNum = data.rows;
	int trainNum = 2500;
	Mat trainData, trainLabels;
	trainData = data(Range(0, trainNum), Range::all());			//前2500个样本为训练数据
	trainLabels = labels(Range(0, trainNum), Range::all());

	//使用KNN算法
	int K = a;
	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabels);
	Ptr<KNearest> model = KNearest::create();
	model->setDefaultK(K);										//设置默认K值
	model->setIsClassifier(true);
	model->train(tData);

	//预测分类
	double train_hr = 0, test_hr = 0;
	Mat response;
	// compute prediction error on train and test data
	for (int i = 0; i < samplesNum; i++)
	{
		Mat sample = data.row(i);
		float r = model->predict(sample);   //对所有行进行预测
											//预测结果与原结果相比，相等为1，不等为0
		r = std::abs(r - labels.at<int>(i)) <= FLT_EPSILON ? 1.f : 0.f;

		if (i < trainNum)
			train_hr += r;  //累积正确数
		else
			test_hr += r;
	}

	test_hr /= samplesNum - trainNum;
	train_hr = trainNum > 0 ? train_hr / trainNum : 1.;

	printf("accuracy:K=%d train = %.1f%%, test = %.1f%%\n",
		a,train_hr*100., test_hr*100.);
	waitKey(0);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	string strTemp = IMG_1;
	
//	ShowImage(strTemp,TITLE);
	
//	PlayMovie(MOVIE_1, "小电影");
	for (int a=1;a<20;a++)
	{
		KNNTest(a);
	}

	system("pause");
	return 0;
}
