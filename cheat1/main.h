#pragma once

#define DEBUG
#define DISCMSG

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
#include <stdlib.h>     /* srand, rand */
#include "checksum_md5.h"
#include "random.h"
#include <bitset>
#include <algorithm> //vector sort

using namespace std;
using std::stringstream;

#include "spymemory.h"
#include "d3d9.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow);
void SetWindowToTarget();

HANDLE hProcess;
HANDLE get_process_handle();

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
const MARGINS Margin = { 0, 0, Width, Height };
char lWindowName[256] = " ";
HWND hWnd;
char tWindowName[256] = "Counter-Strike Source";
//char tWindowName[256] = "CS:S v34 ClientMod v3";
HWND tWnd;
RECT tSize;
MSG Message;

IDirect3DDevice9Ex* p_Device = 0;
RECT rc;
D3DCOLOR color;
D3DXVECTOR3 position;

DWM_BLURBEHIND bb = { DWM_BB_ENABLE | DWM_BB_BLURREGION, true, CreateRectRgn(0, 0, -1, -1), true };

D3DCOLOR colorprim = D3DCOLOR_ARGB(255, 203, 111, 111); //PRIMARY CHEAT COLOR 
D3DCOLOR colorsec = D3DCOLOR_ARGB(200, 5, 0, 0); //SECONDARY CHEAT COLOR 
int border = 4; //CHEAT BORDER

union dword2bytes
{
	DWORD dw;
	BYTE bytes[sizeof(DWORD)];
};

#define PI 3.14159265
#define PLRSZ 0x140     
const DWORD offset = 0x228;

stringstream ss;
string s;
BYTE who = 0, zero = 0, ret = 0xC3, jmp = 0xE9, nop = 0x90, call = 0xE8, push = 0x68, drawmenu = 0, menuselect = 0, myid, wepid, bDormant;
DWORD engine_dll_base, gameui_dll_base, vgui2_dll_base, vguimatsurface_dll_base, d3d9_dll_base, steam_dll_base, materialsystem_dll_base,
localplayer, ptr, cmdptr, aobconsole, aobcmdnum, aobfakelag, enginedelta, boneptr, vmatrixptr, entity, spec1, spec2, radarhackptr, 
scrCenterX, scrCenterY, entptr, radar3ptr, dip9, reset9, flycave, whAddr, shaderapidx9_dll, d3d9Resetcave;
float myposX, myposY, myangY, deltaX, deltaY, fi = 0.08, coords[3], radarcoords[2], xl, yl, wl, xl_closest = 0, yl_closest = 0,
xl_closest_final = 0, yl_closest_final = 0, viewmatrix[4][4], hyp1, hyp2, deltaXold, deltaYold, deltaZ, myposZ, enemyDistance, 
 bomb, xd = 0, bombcoords[3], prevX, prevY, flickerCheck;
int closest, closest_final, aimfov, menutop = 340, i, hp, team, myteam, maxentityid, offs, playerscount;
char *cstr = &s[0];
BOOL boostsleep = 0, angleshack = 0, bombplanted = 0, fullbright = 0;
PVOID rotating, freevisangX, freevisangY, freevisangZ, asmWHcave, fixPredict;
byte sf[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

DWORD allocmem = 0x19000000;

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
	Feature& operator()(string name) {
		for (int i = 0; i < cheats.size(); i++)
		{
			if (cheats[i].name == name)
			{
				return cheats[i];
				break;
			}
		}
#ifdef DEBUG
		cout << "ERROR: Can't find " << name << endl;
#endif
		system("pause");
	}

	Feature& operator()(int i) {
		return cheats[i];
	}

	void New(string name)
	{
		Feature f;
		f.name = name;
		f.trigger = 0;
		cheats.push_back(f);
	}

	void New(string name, int mode)
	{
		Feature f;
		f.name = name;
		f.modes = mode;
		f.trigger = 0;
		cheats.push_back(f);
	}

	int Count() {
		return cheats.size();
	}

	BOOL Triggered(string name) {

		for (int i = 0; i < cheats.size(); i++)
			if (cheats[i].name == name)
				return cheats[i].trigger != cheats[i].enabled ? true : false;
#ifdef DEBUG
		cout << "Trigger ERROR: Can't find " << name << endl;
		system("pause");
#endif
	}

	BOOL Update(string name) {

		for (int i = 0; i < cheats.size(); i++)
		{
			if (cheats[i].name == name)
			{
				cheats[i].trigger = cheats[i].enabled;
				return 1;
			}
		}
#ifdef DEBUG
		cout << "Update ERROR: Can't find " << name << endl;
		system("pause");
#endif
	}

};

Cheat cheat;

bool operator==(Feature f, int enabled)
{
	return (f.enabled == enabled) ? true : false;
}

bool operator==(int enabled, Feature f)
{
	return (f.enabled == enabled) ? true : false;
}

bool operator!=(Feature f, int enabled)
{
	return (f.enabled != enabled) ? true : false;
}

bool operator!=(int enabled, Feature f)
{
	return (f.enabled != enabled) ? true : false;
}

void MenuSelect();
void DisExit();

struct PlayerScore {
	int id, kills, place;
};
// Compares two players according to their frags. 
bool compareKills(PlayerScore i1, PlayerScore i2)
{
	return (i1.kills > i2.kills);
}
bool compareID(PlayerScore i1, PlayerScore i2)
{
	return (i1.id < i2.id);
}

#include "cheat.cpp"

