#pragma once
#include <windows.h>
// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <string.h>
#include <WinBase.h>

#include <Wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <atlconv.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
HRESULT initResources(ID2D1RenderTarget *pRenderTarget);
VOID getAbsolutePath(ID2D1RenderTarget *pRenderTarget);
WCHAR * getImagePath(WCHAR * imageName);
HRESULT LoadBitmapFromFile(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	ID2D1Bitmap **ppBitmap
	);
extern ID2D1Bitmap *bmpChessboard;
extern ID2D1Bitmap * bmpChessBlack;
extern ID2D1Bitmap * bmpChessWhite;
extern ID2D1Bitmap * bmpAisi;
extern ID2D1Bitmap * bmpHaizei;

extern TCHAR exeDirPath[256];
extern WCHAR dirPath[256];
extern ID2D1RenderTarget * pRenderTarget;