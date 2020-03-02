#include "includes.h"
#include "offsets.h"
#include "drawing.h"
#include "mem.h"
#include "dllmain.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

typedef											   HRESULT(__stdcall* fBeginScene)(IDirect3DDevice9* pDevice);
typedef												 HRESULT(__stdcall* fEndScene)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* fReset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
fReset					oReset;
fEndScene            oEndScene;
fBeginScene		   oBeginScene;
LPD3DXFONT tahomaFont { NULL };
D3DVIEWPORT9		  viewPort;
RECT			    windowRect;



int textX			  { 300 };
int textY			   { 28 };
int screenX			 { NULL };
int screenY			 { NULL };
bool fontInit	    { false };
bool showText		{ false };
bool showEsp        { false };
bool bHop			{ false };
bool thirdPerson    { false };
float matrix			 [16];

struct Vector2
{
	float x, y;
};

struct Vector3
{
	float x, y, z;
};

struct Vector4
{
	float x, y, z, w;
};

struct values
{
	DWORD localPlayer;
	DWORD gameModule;
	DWORD entityList;
}values;

class CPlayer
{
public:
	char pad_0x0000[0xF4]; //0x0000
	__int32 teamID; //0x00F4 
	char pad_0x00F8[0x8]; //0x00F8
	__int32 health; //0x0100 
	__int32 flags; //0x0104 
	char pad_0x0108[0x24]; //0x0108
	float velocity; //0x012C 
	char pad_0x0130[0x8]; //0x0130
	Vector3 origin; //0x0138 
	char pad_0x0144[0x2EE8]; //0x0144
	float aimPunchAngle; //0x302C 
	char pad_0x3030[0x8]; //0x3030
	float aimPunchVel; //0x3038 
	char pad_0x303C[0x1A8]; //0x303C
	__int32 fov; //0x31E4 
	__int32 fovStart; //0x31E8 
	char pad_0x31EC[0x18C]; //0x31EC
	__int32 observerMode; //0x3378 
	char pad_0x337C[0x234]; //0x337C
	char N00001A9C[10]; //0x315888 
	char pad_0x35BA[0x35E]; //0x35BA
	__int32 N00001B76; //0x3918 
	char pad_0x391C[0x6A64]; //0x391C
	__int32 shotsFired; //0xA380 
	char pad_0xA384[0xFD8]; //0xA384
	__int32 hasHelmet; //0xB35C 
	char pad_0xB360[0x78]; //0xB360
	__int32 crossHairID; //0xB3D8 
	char pad_0xB3DC[0xC2C]; //0xB3DC

}; //Size=0xC008



class clientInfo
{
public:
	CPlayer* entityPtr; //0x0000 
	__int32 N00000236; //0x0004 
	clientInfo* bLink; //0x0008 
	clientInfo* fLink; //0x000C 

}; //Size=0x0010



class CBaseEntityList
{
public:
	char pad_0x0000[0x10]; //0x0000
	clientInfo entityList[64]; //0x0010 
	char pad_0x0020[0xB50]; //0x0020
}; //Size=0x0B70



CPlayer * localPlayer;

HRESULT __stdcall hBeginScene(IDirect3DDevice9* pDevice)
{

}

HRESULT __stdcall hReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{

}

HRESULT __stdcall hEndScene(IDirect3DDevice9* pDevice)
{

	pDevice->GetViewport(&viewPort);

	int screenX = viewPort.Width;
	int screenY = viewPort.Height;

	if (!fontInit)
	{
		D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Tahoma", &tahomaFont);
		fontInit = true;
	}
	
	std::string localPlayerString =			     drawing::hexToString(values.localPlayer);
	std::string entityListString =				  drawing::hexToString(values.entityList);
	std::string playerHealthString =			drawing::intToString(localPlayer->health);

	std::string x, y, z;

	x =								drawing::floatToString(localPlayer->origin.x);
	y =								drawing::floatToString(localPlayer->origin.y);
	z =								drawing::floatToString(localPlayer->origin.z);
	std::string resX =								drawing::intToString(screenX);
	std::string resY =								drawing::intToString(screenY);

	if (GetAsyncKeyState(VK_INSERT) & 1) showText = !showText;

	if (GetAsyncKeyState(VK_END) & 1)	   showEsp = !showEsp;

	if (GetAsyncKeyState(VK_F8) & 1)			 bHop = !bHop;

	if (GetAsyncKeyState(VK_F9) & 1)
	{
		thirdPerson = !thirdPerson;
	}

	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		values.localPlayer = *(DWORD*)(values.gameModule + dwLocalPlayer);
		localPlayer = reinterpret_cast<CPlayer*>(values.localPlayer);
	}

	

	if (showText)
	{	
		drawing::drawShadowedText(textX, textY, D3DCOLOR_ARGB(255, 182, 36, 227), tahomaFont, "FAT KID HACK");
		drawing::drawShadowedText(textX, textY + 14, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, localPlayerString.c_str());
		drawing::drawShadowedText(textX, textY + 26, D3DCOLOR_ARGB(255, 255, 255, 255), tahomaFont, "ESP: ");
		drawing::drawShadowedText(textX, textY + 38, D3DCOLOR_ARGB(255, 255, 255, 255), tahomaFont, "BHOP: ");
		drawing::drawShadowedText(textX, textY + 50, D3DCOLOR_ARGB(255, 255, 255, 255), tahomaFont, "THIRDP: ");
		drawing::drawShadowedText(textX, textY + 62, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, resX.c_str());
		drawing::drawShadowedText(textX, textY + 74, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, resY.c_str());
		drawing::drawShadowedText(textX, textY + 86, D3DCOLOR_ARGB(255, 232, 242, 36), tahomaFont, x.c_str());
		drawing::drawShadowedText(textX, textY + 98, D3DCOLOR_ARGB(255, 232, 242, 36), tahomaFont, y.c_str());
		drawing::drawShadowedText(textX, textY + 110, D3DCOLOR_ARGB(255, 232, 242, 36), tahomaFont, z.c_str());
		drawing::drawShadowedText(textX, textY + 122, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, playerHealthString.c_str());


		if (showEsp)
		{
			drawing::drawShadowedText(textX + 80, textY + 26, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, "ON");
		}
		
		if (!showEsp)
		{
			drawing::drawShadowedText(textX + 80, textY + 26, D3DCOLOR_ARGB(255, 255, 0, 0), tahomaFont, "OFF");
		}

		if (bHop)
		{
			drawing::drawShadowedText(textX + 80, textY + 40, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, "ON");
		}

		if (!bHop)
		{
			drawing::drawShadowedText(textX + 80, textY + 40, D3DCOLOR_ARGB(255, 255, 0, 0), tahomaFont, "OFF");
		}

		if (thirdPerson)
		{
			drawing::drawShadowedText(textX + 80, textY + 54, D3DCOLOR_ARGB(255, 0, 255, 0), tahomaFont, "ON");
		}

		if (!thirdPerson)
		{
			drawing::drawShadowedText(textX + 80, textY + 54, D3DCOLOR_ARGB(255, 255, 0, 0), tahomaFont, "OFF");
		}

	}

	if (bHop)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (localPlayer->flags > 256)
			{
				*(int*)(values.gameModule + dwForceJump) = 6;
			}
		}
	}

	CBaseEntityList* entityList = (CBaseEntityList*)(values.gameModule + dwEntityList);

	for (auto e : entityList->entityList)
	{
		if (e.entityPtr)
		{
			
			

		}
	}

	return oEndScene(pDevice);

}

DWORD __stdcall mainThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	values.gameModule = (DWORD)GetModuleHandleA("client_panorama.dll");

	values.localPlayer = *(DWORD*)(values.gameModule + dwLocalPlayer);

	

	if (!values.localPlayer)
		while (!values.localPlayer)
			values.localPlayer = *(DWORD*)(values.gameModule + dwLocalPlayer);

	localPlayer = reinterpret_cast<CPlayer*>(values.localPlayer);	

	std::cout << "{+} Local Player 0x" << std::hex << values.localPlayer << "\n";

	static DWORD directDevice{ NULL };

	while (!directDevice)
		directDevice = **(DWORD**)(mem::Pattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x1);

	void** pVTable = *reinterpret_cast<void***>(directDevice);

	oEndScene = (fEndScene)DetourFunction((PBYTE)pVTable[42], (PBYTE)hEndScene);
	oBeginScene = (fBeginScene)DetourFunction((PBYTE)pVTable[41], (PBYTE)hBeginScene);
	oReset = (fReset)DetourFunction((PBYTE)pVTable[16], (PBYTE)hReset);

	std::cout << "{+} Endscene 0x" << oEndScene << "\n";

	system("CLS");

	return true;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainThread, hModule, 0, 0);
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}