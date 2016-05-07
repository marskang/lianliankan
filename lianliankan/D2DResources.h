#pragma once
#include <windows.h>
// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <Wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

class D2DResources {
public:

	D2DResources();
	~D2DResources();
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory = 0;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	ID2D1SolidColorBrush* m_pBlueBrush;
	ID2D1SolidColorBrush* m_pFontBrush;
	ID2D1SolidColorBrush* m_pRedBrush;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	HRESULT OnRender();
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void SizeUpdate(HWND hwnd);
	void nextFrame();
	int nowFrame = 0;
	DWORD tPre = GetTickCount();
	template<class Interface>
	inline void SafeRelease(Interface **ppInterfaceToRelease) {
		if (*ppInterfaceToRelease != NULL) {
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
		}
	}
};

