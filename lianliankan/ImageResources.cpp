#include "ImageResources.h"

ID2D1Bitmap * bmpChessboard;
ID2D1Bitmap * bmpChessBlack;
ID2D1Bitmap * bmpChessWhite;
ID2D1Bitmap * bmpAisi;
ID2D1Bitmap * bmpHaizei;


TCHAR exeDirPath[256];
WCHAR dirPath[256];
ID2D1RenderTarget *pRenderTarget;

HRESULT initResources(ID2D1RenderTarget *pRenderTarget) {
	IWICImagingFactory * pIWICFactory;
	HRESULT hr;
	CoInitialize(NULL);
	getAbsolutePath(pRenderTarget);
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pIWICFactory);
	OutputDebugString("´ó¼ÒºÃ°¡\n");
	OutputDebugStringW(getImagePath(L"chessboard.png"));
	OutputDebugString("\n");
	//LoadBitmapFromFile(pRenderTarget, pIWICFactory, getImagePath(L"chessboard.png"), &bmpChessboard);
	//LoadBitmapFromFile(pRenderTarget, pIWICFactory, getImagePath(L"black.png"), &bmpChessBlack);
	//LoadBitmapFromFile(pRenderTarget, pIWICFactory, getImagePath(L"white.png"), &bmpChessWhite);
	//LoadBitmapFromFile(pRenderTarget, pIWICFactory, getImagePath(L"aisi.jpg"), &bmpAisi);
	LoadBitmapFromFile(pRenderTarget, pIWICFactory, getImagePath(L"haizei.png"), &bmpHaizei);
	if (pIWICFactory) {
		pIWICFactory->Release();
	}
	return NULL;
}




VOID getAbsolutePath(ID2D1RenderTarget *pRenderTarget) {
	GetModuleFileName(NULL, exeDirPath, MAX_PATH);
	OutputDebugString(exeDirPath);
	int nLen = strlen(exeDirPath);
	int nwLen = MultiByteToWideChar(CP_ACP, 0, exeDirPath, nLen, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, exeDirPath, nLen, dirPath, nwLen);


	int index = 0;
	for (int i = 0; dirPath[i] != '\0'; i++) {
		if (dirPath[i] == '\\') {
			index = i;
		}
	}
	char dir[] = "images\\";
	int j = 0;
	while (dir[j] != '\0') {
		dirPath[++index] = dir[j++];
	}
	dirPath[index+1] = '\0';
}

WCHAR * getImagePath(WCHAR * imageName) {
	WCHAR *result = (WCHAR *)malloc(sizeof(WCHAR) * 256);
	//result = L"images";
	WCHAR * temp = result;
	WCHAR * dirTemp = dirPath;
	while (*dirTemp != '\0') {
		*result++ = *dirTemp++;
	}
	while ((*result++ = *imageName++) != '\0') {}
	return temp;
}

HRESULT LoadBitmapFromFile(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	ID2D1Bitmap **ppBitmap
	) {
	HRESULT hr = S_OK;
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);
	if (SUCCEEDED(hr)) {

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		//UINT uiFrameCount = 0;
		//hr = pDecoder->GetFrameCount(&uiFrameCount);
	}
	if (SUCCEEDED(hr)) {
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	UINT originalWidth, originalHeight;
	/*if (SUCCEEDED(hr)) {
	hr = pSource->GetSize(&originalWidth, &originalHeight);
	}
	hr = pIWICFactory->CreateBitmapScaler(&pScaler);
	if (SUCCEEDED(hr)) {
	hr = pScaler->Initialize(pSource, originalWidth, originalHeight, WICBitmapInterpolationModeCubic);
	}*/
	if (SUCCEEDED(hr)) {
		/*hr = pConverter->Initialize(pScaler,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL, 0.f, WICBitmapPaletteTypeMedianCut);*/
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);
	}

	if (SUCCEEDED(hr)) {
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);
	}
	if (pDecoder) {
		pDecoder->Release();
	}
	if (pSource) {
		pSource->Release();
	}
	if (pStream) {
		pStream->Release();
	}
	if (pConverter) {
		pConverter->Release();
	}
	if (pScaler) {
		pScaler->Release();
	}
	return hr;
}