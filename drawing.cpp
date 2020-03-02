#include "drawing.h"

void drawing::reset(LPD3DXFONT pFont)
{

	if (pFont)
	{
		pFont->OnLostDevice();
		pFont->OnResetDevice();
	}

}

void drawing::drawText(int x, int y, DWORD color, LPD3DXFONT pFont, LPCSTR message)
{
	RECT fontPos = { x, y, x + 120, y + 16 };

	pFont->DrawTextA(NULL, message, -1, &fontPos, DT_NOCLIP, color);
	drawing::reset(pFont);
}

void drawing::drawShadowedText(int x, int y, DWORD color, LPD3DXFONT pFont, LPCSTR message)
{
	DWORD shadowColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	drawing::drawText(x - 1, y, shadowColor, pFont,message);
	drawing::drawText(x + 1, y, shadowColor, pFont, message);
	drawing::drawText(x, y - 1, shadowColor, pFont, message);
	drawing::drawText(x, y + 1, shadowColor, pFont, message);

	RECT fontPos = { x, y, x + 120, y + 16 };

	pFont->DrawTextA(NULL, message, -1, &fontPos, DT_NOCLIP, color);
	drawing::reset(pFont);
}

void drawing::drawLine(LPDIRECT3DDEVICE9 Device, int baseX, int baseY, int baseW, int baseH, D3DCOLOR Cor)
{
	D3DRECT BarRect = { baseX, baseY, baseX + baseW, baseY + baseH };
	Device->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Cor, 0, 0);
}

void drawing::drawCornerBox(LPDIRECT3DDEVICE9 Device, int x, int y, int w, int h, int borderPx, DWORD borderColor)
{
	drawing::drawLine(Device, x - (w / 2), (y - h + borderPx), w / 3, borderPx, borderColor); //bottom 
	drawing::drawLine(Device, x - (w / 2) + w - w / 3, (y - h + borderPx), w / 3, borderPx, borderColor); //bottom 
	drawing::drawLine(Device, x - (w / 2), (y - h + borderPx), borderPx, w / 3, borderColor); //left 
	drawing::drawLine(Device, x - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3, borderColor); //left 
	drawing::drawLine(Device, x - (w / 2), y, w / 3, borderPx, borderColor); //top 
	drawing::drawLine(Device, x - (w / 2) + w - w / 3, y, w / 3, borderPx, borderColor); //top 
	drawing::drawLine(Device, (x + w - borderPx) - (w / 2), (y - h + borderPx), borderPx, w / 3, borderColor);//right 
	drawing::drawLine(Device, (x + w - borderPx) - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3, borderColor);//right 
}

std::string drawing::intToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string drawing::floatToString(float number)
{
	number = floorf(number);
	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string drawing::hexToString(DWORD address)
{
	std::stringstream ss;
	ss << std::hex << address;
	return ss.str();
}