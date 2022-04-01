#pragma once
#include <d3d11_2.h>
#include <d2d1_3helper.h>
#include <dwrite_3.h>
#include <dcomp.h>
#include <wincodec.h>
#include "colors.h"
#include "xor.h"
#include "driver.h"

#define DEBUG

//deleted

DWORD SwapEffect = 1;
DWORD ManualW_H = 0;
DWORD ManualWidth = 1920;
DWORD ManualHeight = 1080;
DWORD AntiScreenshot = 1;
int Width;
int Height;
DWORD VSync = 0;

#define RET_CHK(x) if ( x != S_OK ) { TerminateProcess(GetCurrentProcess(), 0); return; }
#define RET_CHK2(x) if ( x != S_OK ) { set_thread( remote_window, remote_thread ); TerminateProcess(GetCurrentProcess(), 0); return; }

class d2d_window_t
{
public:
	d2d_window_t()
	{
		//deleted
};

extern "C" HRESULT D2D1CreateFactory2(D2D1_FACTORY_TYPE factoryType, REFIID riid, const D2D1_FACTORY_OPTIONS * pFactoryOptions, void** ppIFactory);

class d2d_renderer_t
{
public:
	d2d_renderer_t(bool start, HWND hGameWnd) : is_destroyed(false)
	{
		//deleted
		if (!start)
		{
			return;
		}
	}

	void LoadGameHijack(HWND local_window_handle, HWND process_window_handle)
	{
		//deleted
		if (local_window_handle != NULL && process_window_handle != NULL)
		{
			
		}
	}

	HRESULT LoadBitmapFromHandle(HFILE hfile, ID2D1DeviceContext* target, ID2D1Bitmap** pBitmap)
	{
		//deleted
		HRESULT hr = S_FALSE;
		
		return hr;
	}

	void DrawFillRect(int x, int y, float w, float w2, int h, ID2D1SolidColorBrush* col)
	{
		//deleted
	}

	void DrawFillRectOld(int x, int y, float w, float w2, ID2D1SolidColorBrush* col)
	{
		//deleted
	}

	void DrawRect(float x, float y, float width, float height, ID2D1SolidColorBrush* col)
	{
		//deleted
	}

	void DrawStrokeText(int x, int y1, ID2D1SolidColorBrush* col, std::string text, float size)
	{
		//deleted
	}

	void DrawPlayerName(int x, int y1, ID2D1SolidColorBrush* col, const wchar_t* text, float size)
	{
		//deleted
	}

	void DrawBox(float x, float y, float width, float height, ID2D1SolidColorBrush* col, float thickness, bool filled)
	{
		//deleted
	}

	void DrawLine(float x1, float y1, float x2, float y2, ID2D1SolidColorBrush* col, float thickness)
	{
		//deleted
	}

	void DrawCircle(float x, float y, float radius, ID2D1SolidColorBrush* col, bool fill)
	{
		//deleted
	}

	void DrawImage(float x, float y, float w, float h, ID2D1Bitmap* bitmap, float opacity)
	{
		//deleted
	}

	void DrawIco(float x, float y, ID2D1Bitmap* bitmap, float opacity)
	{
		//deleted
	}

	void HealthBar(float x, float y, float w, float h, float HP, ID2D1SolidColorBrush* col, float thickness)
	{
		//deleted
	}

	void begin_scene()
	{
		//deleted
	}

	void end_scene()
	{
		//deleted
	}

	void manual_destruct()
	{
		//deleted
	}

	//deleted
};
