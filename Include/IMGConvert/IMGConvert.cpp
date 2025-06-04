#include "StdAfx.h"
#include "IMGConvert.h"


static HINSTANCE gLibIMGConv = NULL;

SETCURRENTPATH SetCurrentPath;
LOADIMGFILE LoadImgFile;
HANDLELOADIMGFILE HandleLoadImgFile;
IMGCONTOURTRACING ImageContourTracing;
IMGBLOBCOLORINGHATCH ImageBlobColoringHatch;
GETIMGCONVERTWIDTH GetImgConvertWidth;
GETIMGCONVERTHEIGHT GetImgConvertHeight;
GETBITMAPHEADER GetBitMapHeader;
IMAGEBITTOVECTORDATA ImageBitToVectorData;
SETIMGCONVERTTYPE SetImgConvertType;

int IMGConvertOpen(CString path)
{
	CString cwdPath;
	cwdPath.Format("%s%s", path, "\\IMGConvert.dll");
	SetCurrentDirectoryA(path);
	gLibIMGConv = AfxLoadLibrary("IMGConvert.dll");

	if (!gLibIMGConv)
		return -1;

	SetCurrentPath = (SETCURRENTPATH) GetProcAddress(gLibIMGConv, "SetCurrentPath");
	LoadImgFile = (LOADIMGFILE) GetProcAddress(gLibIMGConv, "LoadImgFile");
	HandleLoadImgFile = (HANDLELOADIMGFILE) GetProcAddress(gLibIMGConv, "HandleLoadImgFile");
	ImageContourTracing = (IMGCONTOURTRACING) GetProcAddress(gLibIMGConv, "ImageContourTracing");
	ImageBlobColoringHatch = (IMGBLOBCOLORINGHATCH) GetProcAddress(gLibIMGConv, "ImageBlobColoringHatch");
	GetImgConvertWidth = (GETIMGCONVERTWIDTH) GetProcAddress(gLibIMGConv, "GetImgConvertWidth");
	GetImgConvertHeight = (GETIMGCONVERTHEIGHT) GetProcAddress(gLibIMGConv, "GetImgConvertHeight");
	GetBitMapHeader = (GETBITMAPHEADER) GetProcAddress(gLibIMGConv, "GetBitMapHeader");
	ImageBitToVectorData = (IMAGEBITTOVECTORDATA) GetProcAddress(gLibIMGConv, "ImageBitToVectorData");
	SetImgConvertType = (SETIMGCONVERTTYPE) GetProcAddress(gLibIMGConv, "SetConvertType");

	return 0;
}

int IMGConvertClose()
{
	if (gLibIMGConv != NULL)
	{
		int ret = AfxFreeLibrary(gLibIMGConv);
		gLibIMGConv = NULL;
		return ret;
	}
	return 0;
}