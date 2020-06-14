#pragma once

///* JUNK CODE EXAMPLE ONE
#define $$$ __asm      \
{                      \
	__asm _emit 0xEB      \
	__asm _emit 0x05      \
	__asm _emit 0xAA\
	__asm _emit 0xBB\
	__asm _emit 0xDD\
	__asm _emit 0xCC\
	__asm _emit 0xEE\
} 


/* JUNK CODE EXAMPLE TWO
#define $$$ __asm      \
{                      \
    __asm pushfd      \
    __asm pushad      \
    __asm xor ebx, ecx\
	__asm inc edx\
	__asm dec eax\
    __asm popad          \
    __asm popfd          \
} */

//#define $$$ {} //disable junk code
//#define DEBUG
#define STRING_OBFUSCATOR
#define BSP_PARSER
#define SUPPORT_CFG

#define PI 3.14159265
#include <Windows.h>
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#include <iostream>
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")	
#include <Psapi.h>
#include <tchar.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <string>
#include <intrin.h> //for sqrtss
#include <chrono> //for timer
#include <vector>
#include <stdlib.h> /* srand, rand */
#include <bitset>
#include <algorithm> //vector sort

using namespace std;
using std::stringstream;

#include "memory.h"
#include "resource1.h"
#include "obfuscator.h"
#include "utils.h"


HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(IDR_WAVE1), "WAVE");
HANDLE hRes = LoadResource(NULL, hResInfo);
LPVOID lpRes = LockResource(hRes);
	
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow);
void SetWindowToTarget();

HANDLE hProcess;
HANDLE get_process_handle();

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
const MARGINS Margin = { 0, 0, Width, Height };
HWND hWnd;
char tWindowName[256] = "Counter-Strike: Global Offensive";
HWND tWnd;
RECT tSize;
MSG Message;

IDirect3DDevice9Ex* p_Device = 0;
RECT rc;
D3DCOLOR color;
D3DXVECTOR3 position;

LONG topR = 0, leftR = 0, rightR = 0, bottomR = 0;

float xl, yl, wl, xl_closest = 0, yl_closest = 0, xl_closest_final = 0, yl_closest_final = 0, viewmatrix[4][4], hyp1, hyp2,
deltaXold, deltaYold, enemyDistance, bomb, bombLine = 0;
int closest, closest_final, aimfov, menutop = 340, i, hp, team, myteam, playerscount, intbuf, hits = 0, totalhits = 0;

DWORD engine_dll, engine_dll_size, vstdlib_dll, vstdlib_dll_size, client_dll, client_dll_size, iItemDefinitionIndex, glowNoFlick,
iGlowIndex, dwBoneMatrix, aimPunchAngle, iCrosshairId, hObserverTarget, vecOrigin, iTeamNum, iHealth, iObserverMode, hActiveWeapon,
m_lifeState, flFlashMaxAlpha, fFlags, vecViewOffset, dwGameRulesProxy, bBombPlanted, convar_name_hash_table, dwLocalPlayer,
dwEntityList, dwViewMatrix, dwPlayerResource, dwClientState, totalHitsOnServer, dwClientState_ViewAngles, bDormantOffset, isDefusing,
dwForceJump, dwForceLeft, dwForceRight, nModelIndex, interface_engine_cvar, dwClientState_PlayerInfo, dwGlowObjectManager, dwClientState_Map,
dwForceAttack, bIsScoped, dwClientState_GetLocalPlayer, dwClientState_State, m_szClan, defaultFOV, dwForceBackward, dwForceForward,
localplayer, entityList, clientstate, ClientCMD, nameExploit, fnSetClanAddress, fakePrime, fakeRank, fakeLevel, fakeLobby[3],
radarHax, monRev, aimPunch, seeEnemyInfo, noSmoke, reveal1, reveal2, revealOrig, freeCam, createMove, rankOffsetThing, skyFunc;

float bbdeltaX, bbdeltaY; BYTE standing = 0;

PVOID SWshellcode, SCshellcode, skyName, GLOWshellcode;
D3DXVECTOR3 glowcolor, mycoords, coords, delta, enemyhead;
BYTE head = 8, spec, who, myid, drawmenu, menuselect, bDormant, punchExtraOrigBytes[22];
char charint[32];
BOOL bombplanted = 0, wrongname = false;

string folder;

#pragma comment(lib, "winmm.lib")
dword2bytes playercolor = { 0xFFFFFFFF };

struct Feature
{
	string name;
	int modes = 1;
	int enabled = 0;
	int trigger = 0; 
	int sleep = 200;

	void operator=(int enabled) {
		this->enabled = enabled;
	}
};

class Cheat {
	vector<Feature> cheats;
public:
	Feature& operator()(const char* name) {
		for (int i = 0; i < cheats.size(); i++)
		{
			$$$;
			if (cheats[i].name == name)
			{
				return cheats[i]; $$$;
				break; $$$;
			}
		}
		char ErrorMsg[125]; $$$;
		sprintf(ErrorMsg, AY_OBFUSCATE("Can't find %s feature!"), name); $$$;
		MessageBox(0, ErrorMsg, AY_OBFUSCATE("Critical Error"), MB_OK | MB_ICONERROR); $$$;
		_Exit(1); $$$;
	}

	Feature& operator()(int i) {
		return cheats[i]; $$$;
	}

	void New(const char* name)
	{
		Feature f; $$$;
		f.name = name; $$$;
		f.trigger = 0; $$$;
		cheats.push_back(f); $$$;
	}

	void New(const char* name, int mode)
	{
		Feature f; $$$;
		f.name = name; $$$;
		f.modes = mode; $$$;
		f.trigger = 0; $$$;
		cheats.push_back(f); $$$;
	}

	int Count() {
		return cheats.size(); $$$;
	}

	BOOL Triggered(const char* name) {
		for (int i = 0; i < cheats.size(); i++)
			if (cheats[i].name == name)
				return cheats[i].trigger != cheats[i].enabled ? true : false;
		char ErrorMsg[125]; $$$;
		sprintf(ErrorMsg, AY_OBFUSCATE("Can't find %s feature!"), name); $$$;
		MessageBox(0, ErrorMsg, AY_OBFUSCATE("Trigger Error"), MB_OK | MB_ICONERROR); $$$;
		_Exit(1); $$$;
	}

	BOOL Update(const char* name) {
		for (int i = 0; i < cheats.size(); i++)
		{
			$$$;
			if (cheats[i].name == name)
			{
				cheats[i].trigger = cheats[i].enabled; $$$;
				return 1;
			}
		}
		char ErrorMsg[125]; $$$;
		sprintf(ErrorMsg, AY_OBFUSCATE("Can't find %s feature!"), name); $$$;
		MessageBox(0, ErrorMsg, AY_OBFUSCATE("Update Error"), MB_OK | MB_ICONERROR); $$$;
		_Exit(1); $$$;
	}

};

Cheat cheat;

#include "d3d9.h"

bool operator==(Feature f, int enabled)
{
	return (f.enabled == enabled) ? true : false; $$$;
}

bool operator==(int enabled, Feature f)
{
	return (f.enabled == enabled) ? true : false; $$$;
}

bool operator!=(Feature f, int enabled)
{
	return (f.enabled != enabled) ? true : false; $$$;
}

bool operator!=(int enabled, Feature f)
{
	return (f.enabled != enabled) ? true : false; $$$;
}

void MenuSelect();
void DisExit();

struct GlowObject {
	D3DXVECTOR3 glowColor = { 0,0,0 };
	float glowAlpha = 255.0f;
	bool glowAlphaCappedByRenderAlpha = 0;
	float glowAlphaFunctionOfMaxVelocity = 0;
	float glowAlphaMax = 255.0f;
	float glowPulseOverdrive = 0;
	bool renderWhenOccluded = 1;
	bool renderWhenUnoccluded = 0;
	bool fullBloomRender = 0;
	int fullBloomStencilTestValue = 0;
	int glowStyle = 0;
	
}; GlowObject go;

#include "cheat.cpp"

#ifdef DEBUG
#include <Wincrypt.h>

enum HashType
{
	HashSha1, HashMd5, HashSha256
};

#define BUFSIZE 1024
#define MD5LEN  16
DWORD CreateHash(char * filename)
{
	DWORD dwStatus = 0; $$$;
	BOOL bResult = FALSE; $$$;
	HCRYPTPROV hProv = 0; $$$;
	HCRYPTHASH hHash = 0; $$$;
	HANDLE hFile = NULL; $$$;
	BYTE rgbFile[BUFSIZE]; $$$;
	DWORD cbRead = 0; $$$;
	BYTE rgbHash[MD5LEN]; $$$;
	DWORD cbHash = 0; $$$;
	CHAR rgbDigits[] = "0123456789abcdef"; $$$;

	// Logic to check usage goes here.
	hFile = CreateFile(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwStatus = GetLastError(); $$$;
		printf(AY_OBFUSCATE("Error opening file %s\nError: %d\n"), filename,
			dwStatus); $$$;
		return dwStatus; $$$;
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT))
	{
		dwStatus = GetLastError(); $$$;
		printf(AY_OBFUSCATE("CryptAcquireContext failed: %d\n"), dwStatus); $$$;
		CloseHandle(hFile); $$$;
		return dwStatus; $$$;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
	{
		dwStatus = GetLastError(); $$$;
		printf(AY_OBFUSCATE("CryptAcquireContext failed: %d\n"), dwStatus);
		CloseHandle(hFile); $$$;
		CryptReleaseContext(hProv, 0); $$$;
		return dwStatus; $$$;
	}

	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
		&cbRead, NULL))
	{
		if (0 == cbRead)
		{
			break; $$$;
		}

		if (!CryptHashData(hHash, rgbFile, cbRead, 0))
		{
			dwStatus = GetLastError(); $$$;
			printf(AY_OBFUSCATE("CryptHashData failed: %d\n"), dwStatus); $$$;
			CryptReleaseContext(hProv, 0); $$$;
			CryptDestroyHash(hHash); $$$;
			CloseHandle(hFile); $$$;
			return dwStatus; $$$;
		}
	}

	if (!bResult)
	{
		dwStatus = GetLastError();
		printf(AY_OBFUSCATE("ReadFile failed: %d\n"), dwStatus); $$$;
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return dwStatus;
	}

	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		printf(AY_OBFUSCATE("MD5 hash of file %s is: "), filename); $$$;
		for (DWORD i = 0; i < cbHash; i++)
		{
			printf(AY_OBFUSCATE("%c%c"), rgbDigits[rgbHash[i] >> 4],
				rgbDigits[rgbHash[i] & 0xf]); $$$;
		}
		printf("\n"); $$$;
	}
	else
	{
		dwStatus = GetLastError(); $$$;
		printf(AY_OBFUSCATE("CryptGetHashParam failed: %d\n"), dwStatus); $$$;
	}

	CryptDestroyHash(hHash); $$$;
	CryptReleaseContext(hProv, 0); $$$;
	CloseHandle(hFile); $$$;

	return dwStatus; $$$;
}

#endif
