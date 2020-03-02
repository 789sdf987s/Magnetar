#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <sstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace drawing
{
	void drawShadowedText(int x, int y, DWORD color, LPD3DXFONT pFont, LPCSTR message);
	void drawLine(LPDIRECT3DDEVICE9 Device, int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor);
	void drawCornerBox(LPDIRECT3DDEVICE9 Device, int x, int y, int w, int h, int borderPx, DWORD borderColor);
	void drawText(int x, int y, DWORD color, LPD3DXFONT pFont, LPCSTR message);
	std::string floatToString(float number);
	std::string intToString(int number);
	void reset(LPD3DXFONT pFont);
	std::string hexToString(DWORD address);
}
