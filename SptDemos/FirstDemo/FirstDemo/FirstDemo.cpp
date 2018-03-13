// FirstDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#include <string>
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

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	string strTemp = IMG_1;
	
//	ShowImage(strTemp,TITLE);
	
	PlayMovie(MOVIE_1, "小电影");
	return 0;
}
