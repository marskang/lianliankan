#include "D2DResources.h"
#include "ImageResources.h"
#include "GameEntity.h"
#include <windows.h>

D2DResources::D2DResources() {
}


D2DResources::~D2DResources() {
}

HRESULT D2DResources::CreateDeviceResources() {
	HRESULT hr = NULL;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	return hr;
}

void D2DResources::DiscardDeviceResources() {
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
	SafeRelease(&m_pBlueBrush);
	SafeRelease(&m_pFontBrush);
	SafeRelease(&m_pRedBrush);
	SafeRelease(&m_pDWriteFactory);
}

HRESULT D2DResources::CreateDeviceIndependentResources() {
	HRESULT hr = S_OK;
	if (!m_pRenderTarget) {
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
			);

		if (SUCCEEDED(hr)) {
			initResources(m_pRenderTarget);
		}
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush);
		}
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&m_pCornflowerBlueBrush);
		}
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Blue),
				&m_pBlueBrush
				);
		}
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Red),
				&m_pRedBrush
				);
		}
		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::DarkGray),
				&m_pFontBrush);
		}
		if (SUCCEEDED(hr)) {
			if (!m_pDWriteFactory) {
				hr = DWriteCreateFactory(
					DWRITE_FACTORY_TYPE_SHARED,
					__uuidof(IDWriteFactory),
					reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
					);
			}
			if (SUCCEEDED(hr)) {
				hr = m_pDWriteFactory->CreateTextFormat(
						L"Consolas",                   // Font family name
						NULL,                          // Font collection(NULL sets it to the system font collection)
						DWRITE_FONT_WEIGHT_REGULAR,    // Weight
						DWRITE_FONT_STYLE_NORMAL,      // Style
						DWRITE_FONT_STRETCH_NORMAL,    // Stretch
						24,                         // Size    
						L"en-us",                      // Local
						&m_pTextFormat                 // Pointer to recieve the created object
					);
			}
		}
	}
	return hr;
}

HRESULT D2DResources::OnRender() {
	HRESULT hr = S_OK;
	hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr)) {
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(0xc5c5c5, 0.1f));
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
		int width = static_cast<int> (rtSize.width);
		int height = static_cast<int> (rtSize.height);
		/*for (int x = 0; x < width; x += 10) {
			m_pRenderTarget->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
				m_pLightSlateGrayBrush, 0.5f
				);
		}
		for (int y = 0; y < height; y += 10) {
			m_pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				m_pLightSlateGrayBrush, 0.5f);
		}*/
		int sourceLeft = nowFrame * 58;
		//D2D1_RECT_F destinationRectangle = D2D1::RectF(0, 0, 58, 58);
		//D2D1_RECT_F sourceRectangle = D2D1::RectF(sourceLeft, 0, sourceLeft + 58, 58);
		//m_pRenderTarget->DrawBitmap(bmpAisi, &destinationRectangle, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &sourceRectangle);
		D2D1_RECT_F rect = D2D1::RectF(90, 90, 100, 100);
		//m_pRenderTarget->FillRectangle(&rect, m_pBlueBrush);
		for (int i = 1; i <= ROW; i++) {
			int y = (i-1) * eachWidth + startY;
			for (int j = 1; j <= COL; j++) {
				if (!gameMap[i][j]) continue;
				int x = (j - 1) * eachWidth + startX;
				int right = x + eachWidth - 2;
				int bottom = y + eachWidth - 2;
				D2D1_RECT_F rect = D2D1::RectF(x, y, right, bottom);
				D2D1_RECT_F destinationRectangle = D2D1::RectF(x, y, right, bottom);
				int sx1 = (gameMap[i][j] - 1) * 50;
				int sy1 = 0;
				int sx2 = sx1 + 50;
				int sy2 = 50;
				D2D1_RECT_F sourceRectangle = D2D1::RectF(sx1, 0, sx2, 50);
				m_pRenderTarget->DrawBitmap(bmpHaizei, &destinationRectangle, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &sourceRectangle);
				if (i == nowPoint.x && j == nowPoint.y) {
					m_pRenderTarget->DrawRectangle(&rect, m_pRedBrush);
				} else {
					//m_pRenderTarget->DrawRectangle(&rect, m_pBlueBrush);
				}
				//m_pRenderTarget->FillRectangle(&rect, m_pBlueBrush);
			/*	D2D1_RECT_F rectFont = D2D1::RectF(x + 3, y - 2, right , bottom);
				WCHAR num[2];
				num[0] = gameMap[i][j] + 48;
				num[1] = '\0';
				m_pRenderTarget->DrawTextA(
					num,
					ARRAYSIZE(num) - 1,
					m_pTextFormat,
					rectFont,
					m_pCornflowerBlueBrush);*/
			}
		}
		//²¥·Å¶¯»­
		/*if (animationNum != (nowFrame - 1)) {
			DWORD tNow = GetTickCount();
			if ((tNow - tPre) >= 30) {
				int aniX = animationPath[nowFrame].x;
				int aniY = animationPath[nowFrame].y;
				D2D1_POINT_2F startP = D2D1::Point2F();
				m_pRenderTarget->DrawLine()
				tPre = tNow;
			}
		}*/
		if (animationNum != 0) {
			for (int i = 0; i < animationNum - 1; i++) {
				int aStartX = animationPath[i].y;
				int aStartY = animationPath[i].x;
				int aEndX = animationPath[i + 1].y;
				int aEndY = animationPath[i + 1].x;
				D2D1_POINT_2F startP = D2D1::Point2F(
					(aStartX*eachWidth) + startX - 25, 
					(aStartY*eachWidth) + startY - 25);
				D2D1_POINT_2F endP = D2D1::Point2F(
					(aEndX*eachWidth) + startX - 25,
					(aEndY*eachWidth) + startY - 25);
				m_pRenderTarget->DrawLine(startP, endP, m_pBlueBrush, 0.5f);
			}
		}
		hr = m_pRenderTarget->EndDraw();
		if (animationNum != 0) {
			Sleep(500);
			animationNum = 0;
		}
		if (hr == D2DERR_RECREATE_TARGET) {
			hr = S_OK;
			DiscardDeviceResources();
		}
		return hr;
	}
	return hr;
}

void D2DResources::SizeUpdate(HWND hwnd) {
	RECT rc;
	GetClientRect(hwnd, &rc);
	m_pRenderTarget->Resize(
		D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));
}

void D2DResources::nextFrame() {
	nowFrame = (nowFrame + 1) % 10;
}