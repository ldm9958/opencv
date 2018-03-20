// MyCyberOCR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <shlwapi.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include "Common.h"
#include "opencv\highgui.h"

int ScreenShotImgByPlots(std::wstring strImgPath, int iPlotA_x,int iPlotA_y, int iPlotB_x, int iPlotB_y, int iPlotC_x, int iPlotC_y, int iPlotD_x, int iPlotD_y)
{
	if (::PathFileExists(strImgPath.c_str()))
	{
		std::cout << "File" << strImgPath.c_str() << "doesn't exist!!" <<std::endl;
		return ERROR_FILE_NOT_EXIST;
	}

	int iLength,iHeight		= 0;
	double tanX,sinX,cosX	= 0.0;
	iLength = (int)sqrt((iPlotA_x - iPlotC_x)*(iPlotA_x - iPlotC_x) + (iPlotA_y - iPlotC_y)*(iPlotA_y - iPlotC_y));
	iHeight = (int)sqrt((iPlotA_x - iPlotB_x)*(iPlotA_x - iPlotB_x) + (iPlotA_y - iPlotB_y)*(iPlotA_y - iPlotB_y));
	if (iPlotA_y - iPlotC_y = 0)
	{
		if (iPlotA_x - iPlotC_x > 0)
		{
			sinX = 0;
			cosX = 1;
		}
	}
	else
	{
		tanX	= 0;
	}	
	do 
	{
		IplImage * img = cvLoadImage(strImgPath.c_str());
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
}

