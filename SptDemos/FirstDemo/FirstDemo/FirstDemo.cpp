// FirstDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#include <string>
#include "highgui.h"

#define IMG_1	"..\\..\\data\\州哥.jpg"
#define L_IMG_1	L"..\\..\\data\\州哥.jpg"
#define TITLE	"州哥是条狗"

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

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	string strTemp = IMG_1;

	//if (!PathFileExists(L_IMG_1))
	//{
	//	::MessageBox(0, 0, L"File doesn't exist111!", 0);
	//	strTemp.insert(0,"..\\");
	//	if (!PathFileExists(str2wstr(strTemp).c_str()))
	//	{
	//		::MessageBox(0, 0, L"File doesn't exist222!", 0);
	//		return -1;
	//	}		
	//}

	IplImage * img = cvLoadImage(strTemp.c_str());
	cvNamedWindow(TITLE, CV_WINDOW_AUTOSIZE);
	cvShowImage(TITLE, img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow(TITLE);

	return 0;
}
