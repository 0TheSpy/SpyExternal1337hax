#pragma once
#include "main.h"
#include <fstream>

#ifdef SUPPORT_CFG
void LoadCfg()
{
	ifstream loadcfg(AY_OBFUSCATE("settings.txt")); $$$;
	string line; $$$;
	if (loadcfg.is_open())
	{
		while (getline(loadcfg, line))
		{
			size_t pos = line.find(": "); $$$;
			string name = line.substr(0, pos); $$$;
			string var = line.erase(0, pos + 2); $$$;
			cheat(name.c_str()).enabled = stoi(var); $$$;
		}
#ifdef DEBUG
		cout << AY_OBFUSCATE("Config loaded\n"); $$$;
#endif
		loadcfg.close();
	}
#ifdef DEBUG
	else cout << AY_OBFUSCATE("Unable to open configuration file\n"); $$$;
#endif
}

void SaveCfg()
{
	ofstream savecfg; $$$;
	savecfg.open(AY_OBFUSCATE("settings.txt")); $$$;
	for (int i = 0; i < cheat.Count() - 1; i++)
		savecfg << cheat(i).name << ": " << cheat(i).enabled << endl; $$$;
	savecfg.close(); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("Config saved\n"); $$$;
#endif
}
#endif

void MenuSelect()
{
	while (true)
	{
		if (tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_INSERT) < 0) {
			if (drawmenu == 0) { drawmenu = 1; $$$; }
			else { drawmenu = 0; $$$; }
			Sleep(200); $$$;
		}

		if (drawmenu == 1 && tWnd == GetForegroundWindow()) {
			if (GetAsyncKeyState(VK_DOWN) < 0) {
				if (menuselect < cheat.Count() - 1)
				{
					menuselect++; $$$;
				}
				else menuselect = 0; $$$;
				
				Sleep(100); $$$;
			}

			if (GetAsyncKeyState(VK_UP) < 0) {
				if (menuselect > 0)
				{
					menuselect--; $$$;
				}
				else menuselect = cheat.Count() - 1; $$$;
				
				Sleep(100); $$$;
			}

			if (GetAsyncKeyState(VK_RIGHT) < 0) {
				if (cheat(menuselect).enabled < cheat(menuselect).modes)
				{
					cheat(menuselect) = cheat(menuselect).enabled + 1; $$$;
				}
				else
				{
					cheat(menuselect) = 0; $$$;
				}

				Sleep(cheat(menuselect).sleep); $$$;
			}

			if (GetAsyncKeyState(VK_LEFT) < 0) {
				if (cheat(menuselect).enabled > 0)
				{
					cheat(menuselect) = cheat(menuselect).enabled - 1; $$$;
				}
				else
				{
					cheat(menuselect) = cheat(menuselect).modes; $$$;
				}

				Sleep(cheat(menuselect).sleep); $$$;
			}
		}

		Sleep(1); $$$;
	}
}

void DisExit() {
#ifdef SUPPORT_CFG
	SaveCfg(); $$$;
#endif
	for (i = 0; i < cheat.Count(); i++)
	{
		cheat(i) = 0; $$$;
	}

	Sleep(750); $$$;
	p_Object->Release(); $$$;

	_Exit(1); $$$;
}


void myInit() {
	position.x = 20; $$$;
	position.y = 20; $$$;

	auto clientBytes = new BYTE[client_dll_size + 1]; $$$;
	memset(clientBytes, 0, client_dll_size + 1); $$$;
	ReadProcessMemory(hProcess, PVOID(client_dll), clientBytes, client_dll_size, 0); $$$;
	auto engineBytes = new BYTE[engine_dll_size + 1]; $$$;
	memset(engineBytes, 0, engine_dll_size + 1); $$$;
	ReadProcessMemory(hProcess, PVOID(engine_dll), engineBytes, engine_dll_size, 0); $$$;

	dwClientState = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0")) + 0x1) - engine_dll; $$$;
	dwLocalPlayer = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF"), AY_OBFUSCATE("dwLocalPlayer")) + 0x3) - client_dll + 4; $$$;
	dwEntityList = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8")) + 0x1) - client_dll; $$$;
	dwViewMatrix = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")) + 0x3) - client_dll + 0xB0; $$$;
	bDormantOffset = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("8A 81 ? ? ? ? C3 32 C0")) + 0x2) + 8; $$$;
	dwClientState_ViewAngles = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("F3 0F 11 80 ? ? ? ? D9 46 04 D9 05")) + 0x4); $$$;
	dwClientState_PlayerInfo = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("8B 89 ? ? ? ? 85 C9 0F 84 ? ? ? ? 8B 01")) + 0x2); $$$;
	dwClientState_GetLocalPlayer = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("8B 80 ? ? ? ? 40 C3")) + 0x2); $$$;
	dwClientState_State = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("83 B8 ? ? ? ? ? 0F 94 C0 C3")) + 0x2); $$$;
	ClientCMD = engine_dll + SpyPatternScan(engineBytes, engine_dll_size,
		AY_OBFUSCATE("55 8B EC 8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 0C A1 ? ? ? ? 35 ? ? ? ? EB 05 8B 01 FF 50 34 50 A1"),
		AY_OBFUSCATE("ClientCMD")); $$$;
	nameExploit = engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("75 16 57 68 ? ? ? ? FF 15 ? ? ? ? 83 C4 08 5F 5E 5B 8B E5 5D C3 8B 06")); $$$;
	fnSetClanAddress = engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("53 56 57 8B DA 8B F9 FF 15"), "fnSetClanAdress"); $$$;
	m_szClan = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("C7 45 D0 ? 00 00 00 0F 10 45 C4 C7 45 F0 ? ? 00 00 C7 45 E4")) + 0xE); $$$;
	dwPlayerResource = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7")) + 0x2) - client_dll; $$$;
	dwForceJump = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02")) + 0x2) - client_dll; $$$;
	DWORD dwForce = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("55 8B EC 51 53 8A 5D 08")); $$$;
	dwForceRight = rvm<DWORD>(dwForce + 512) - client_dll; $$$;
	dwForceLeft = rvm<DWORD>(dwForce + 465) - client_dll; $$$;
	dwForceForward = rvm<DWORD>(dwForce + 245) - client_dll; $$$;
	dwForceBackward = rvm<DWORD>(dwForce + 287) - client_dll; $$$;
	interface_engine_cvar = rvm<DWORD>(FindSignature(vstdlib_dll, vstdlib_dll_size, AY_OBFUSCATE("\x8B\x0D\x00\x00\x00\x00\xC7\x05"), AY_OBFUSCATE("xx????xx")) + 0x2) - vstdlib_dll; $$$;
	dwGlowObjectManager = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("A1 ? ? ? ? A8 01 75 4B"), AY_OBFUSCATE("dwGlowObjectManager")) + 0x1) - client_dll + 4; $$$;
	fakePrime = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("83 F8 05 5E 0F 94 C0 C3")) + 0x2; $$$;
	fakeLevel = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("0F 45 05 ? ? ? ? F6 05")) + 0x3) - client_dll; $$$;
	fakeRank = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("A1 ? ? ? ? 8b 44 d0 ? 89 07")) + 0x1) - client_dll; $$$;
	radarHax = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("80 B9 ? ? ? ? ? 74 12 8B 41 08")) + 6; $$$;
	aimPunch = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("03 F3 0F 10 86 ? ? ? ? F3 0F 58 43")) - 3; $$$;
	rvm(aimPunch, &punchExtraOrigBytes); $$$;
	seeEnemyInfo = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("3B C6 5E 0F 95")); $$$;
	noSmoke = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size,
		AY_OBFUSCATE("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")) + 8); $$$;
	dwForceAttack = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size,
		AY_OBFUSCATE("89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04"),
		AY_OBFUSCATE("dwForceAttack")) + 2) - client_dll; $$$;
	reveal1 = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("3B 45 ? 75 06 C6"), AY_OBFUSCATE("reveal 1")) + 3; $$$;
	reveal2 = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("3B C6 74 27 8B CB E8"), AY_OBFUSCATE("reveal 2")); $$$;
	dwGameRulesProxy = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size,
		AY_OBFUSCATE("A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A"),
		AY_OBFUSCATE("dwGameRulesProxy")) + 1) - client_dll; $$$;
	convar_name_hash_table = rvm<DWORD>(FindSignature(vstdlib_dll, vstdlib_dll_size, AY_OBFUSCATE("\x8B\x3C\x85"), AY_OBFUSCATE("xxx")) + 3) - vstdlib_dll; $$$;
	freeCam = SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("F8 F3 0F 11 1F")) + 1; $$$;
	aimPunchAngle = rvm<DWORD>(client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("00 F3 0F 7E 82 ? ? 00 00 8B"), AY_OBFUSCATE("aimPunchAngle")) + 5); $$$;
	createMove = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("C2 08 00 8B 01 FF 75"), AY_OBFUSCATE("CreateMove")) + 5; $$$;
	rankOffsetThing = client_dll + SpyPatternScan(clientBytes, client_dll_size,
		AY_OBFUSCATE("55 8B EC 8B 0D ? ? ? ? 85 C9 75 28 A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 04 85 C0 74 0B 8B C8 E8 ? ? ? ? 8B C8 EB 02 33 C9 89 0D ? ? ? ? 8B 45 08"),
		AY_OBFUSCATE("rankOffset")); $$$;
	skyFunc = engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45"), AY_OBFUSCATE("skyFunc")); $$$;
	glowNoFlick = client_dll + SpyPatternScan(clientBytes, client_dll_size, AY_OBFUSCATE("8B B3 ? ? ? ? E8 ? ? ? ? 8A")); $$$;
	dwClientState_Map = rvm<DWORD>(engine_dll + SpyPatternScan(engineBytes, engine_dll_size, AY_OBFUSCATE("05 ? ? ? ? C3 CC CC CC CC CC CC CC A1"), AY_OBFUSCATE("dwClientState_Map")) + 1); $$$;
	
	DWORD dwWorld = client_dll + FindSignatureLocal(clientBytes, client_dll_size, AY_OBFUSCATE("DT_TEWorldDecal"), AY_OBFUSCATE("xxxxxxxxxxxxxxx")); $$$;
	DWORD dwClasses = rvm<DWORD>(client_dll + FindSignatureLocal(clientBytes, client_dll_size, (char*)&dwWorld, AY_OBFUSCATE("xxxx")) + 0x2B); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("dwClasses = ") << hex << dwClasses << endl; $$$;
#endif

	hObserverTarget = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BasePlayer"), AY_OBFUSCATE("hObserverTarget")); $$$;
	dwBoneMatrix = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BaseAnimating"), AY_OBFUSCATE("m_nForceBone")) + 28; $$$;
	vecOrigin = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("vecOrigin")); $$$;
	iHealth = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BasePlayer"), AY_OBFUSCATE("iHealth")); $$$;
	iTeamNum = FindNetvar(dwClasses, AY_OBFUSCATE("DT_World"), AY_OBFUSCATE("TeamNum")); $$$;
	iObserverMode = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BasePlayer"), AY_OBFUSCATE("iObserverMode")); $$$;
	m_lifeState = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BasePlayer"), AY_OBFUSCATE("m_lifeState")); $$$;
	flFlashMaxAlpha = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_flFlashMaxAlpha")); $$$;
	fFlags = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_fFlags")); $$$;
	vecViewOffset = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_vecViewOffset[0]")); $$$;
	bBombPlanted = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSGameRulesProxy"), AY_OBFUSCATE("m_bBombPlanted")); $$$;
	totalHitsOnServer = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("totalHitsOnServer")); $$$;
	nModelIndex = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BaseViewModel"), AY_OBFUSCATE("ModelIndex")); $$$;
	bIsScoped = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_bIsScoped")); $$$;
	defaultFOV = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("DefaultFOV")); $$$;
	iGlowIndex = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_flFlashDuration")) + 24; $$$;
	iCrosshairId = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_bHasDefuser")) + 92; $$$;
	hActiveWeapon = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("m_hActiveWeapon")); $$$;
	iItemDefinitionIndex = FindNetvar(dwClasses, AY_OBFUSCATE("DT_BaseAttributableItem"), AY_OBFUSCATE("ItemDefinitionIndex")); $$$;
	iItemDefinitionIndex += FindNetvar(dwClasses, AY_OBFUSCATE("DT_BaseCombatWeapon"), AY_OBFUSCATE("AttributeManager")); $$$;
	iItemDefinitionIndex += FindNetvar(dwClasses, AY_OBFUSCATE("DT_BaseCombatWeapon"), AY_OBFUSCATE("m_Item")); $$$;
	isDefusing = FindNetvar(dwClasses, AY_OBFUSCATE("DT_CSPlayer"), AY_OBFUSCATE("bIsDefusing")); $$$;

	delete engineBytes; $$$;
	delete clientBytes; $$$;

	cheat.New(AY_OBFUSCATE("Aimbot / Friendly Fire"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Aimbot FOV"), 99); $$$;
	cheat(AY_OBFUSCATE("Aimbot FOV")).sleep = 30; $$$;
	cheat(AY_OBFUSCATE("Aimbot FOV")) = 45; $$$;
	cheat.New(AY_OBFUSCATE("Recoil Control System")); $$$;
	cheat.New(AY_OBFUSCATE("Smoothing"), 99); $$$;
	cheat(AY_OBFUSCATE("Smoothing")).sleep = 60; $$$;
	cheat.New(AY_OBFUSCATE("Triggerbot")); $$$;
	cheat.New(AY_OBFUSCATE("Autopistol")); $$$;
	cheat.New(AY_OBFUSCATE("ESP & HP Bar & C4timer"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Player Glow & Color"), 3); $$$;
	cheat.New(AY_OBFUSCATE("Overhead Info & Radarhack"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Money; Rank Reveal"), 2); $$$;
	cheat.New(AY_OBFUSCATE("No Visual Recoil"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Crosshair Recoil & Spread")); $$$;
	cheat.New(AY_OBFUSCATE("Grenade Trajectory")); $$$;
	cheat.New(AY_OBFUSCATE("Reduce Flash & Smoke"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Skybox Changer"), 6);
	cheat(AY_OBFUSCATE("Skybox Changer")).sleep = 1001; $$$;
	cheat.New(AY_OBFUSCATE("No Hands & Scope & Postproc"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Bunnyhop & Autostrafe")); $$$;
	cheat.New(AY_OBFUSCATE("Hit Sound")); $$$;
	cheat.New(AY_OBFUSCATE("Spectator List")); $$$;
	cheat.New(AY_OBFUSCATE("Thirdperson; Free Cam"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Zoom; Field of View"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Slide Walk & No Duck Stamina"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Blockbot")); $$$;
	cheat.New(AY_OBFUSCATE("Name & ClanTag Stealer")); $$$;
	cheat.New(AY_OBFUSCATE("Various Name Exploits"), 4); $$$;
	cheat.New(AY_OBFUSCATE("Lobby Prime & Rank & lvl"), 2); $$$;
	cheat.New(AY_OBFUSCATE("Disable All & Close Cheat")); $$$;

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MenuSelect, 0, 0, 0); $$$;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aimbot, 0, 0, 0); $$$;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Bunnyhop, 0, 0, 0); $$$;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)NameStealer, 0, 0, 0); $$$;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TriggerCheck, 0, 0, 0); $$$;

#ifdef SUPPORT_CFG
	LoadCfg();
#endif

#ifdef DEBUG
	std::cout << AY_OBFUSCATE("initiated\n"); $$$;
#endif
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		//RENDER

		if (tWnd == GetForegroundWindow())
		{
			char * value = tWindowName; $$$;

			HWND newhwnd = FindWindow(NULL, value); $$$;
			if (newhwnd != NULL) {
				GetWindowRect(newhwnd, &rc); $$$;
			}
			else {
				ExitProcess(0); $$$;
			}

			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0); $$$;
			p_Device->BeginScene(); $$$;

			Draw(); $$$;

			p_Device->EndScene(); $$$;
			p_Device->Present(NULL, NULL, NULL, NULL); $$$;
		}
		else
		{
			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0); $$$;
			p_Device->BeginScene(); $$$;

			p_Device->EndScene(); $$$;
			p_Device->PresentEx(0, 0, 0, 0, 0); $$$;
		}

		break; 

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin); $$$;

		hProcess = get_process_handle(); $$$;
			
		if (!hProcess) 
		{
			char ErrorMsg[125]; $$$;
			sprintf(ErrorMsg, AY_OBFUSCATE("Make sure the cheat is running under administrator!")); $$$;
			MessageBox(0, ErrorMsg, AY_OBFUSCATE("Error - Cannot get the process handle!"), MB_OK | MB_ICONERROR); $$$;
			exit(1); $$$;
		}
			
		myInit(); $$$;

		break; 

	case WM_DESTROY:
		CloseHandle(hProcess); $$$;
		PostQuitMessage(1); $$$;
		return 0; 

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam); $$$;
		break; 
	}
	return 0; $$$;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
#ifdef DEBUG
	AllocConsole(); $$$;
	freopen("conin$", "r", stdin); $$$;
	freopen("conout$", "w", stdout); $$$;
	freopen("conout$", "w", stderr); $$$;
	printf(AY_OBFUSCATE("Debugging Window enabled\n")); $$$;
#endif

	Sleep(1000); $$$;

	TCHAR szExeFileName[MAX_PATH]; $$$;
	GetModuleFileName(NULL, szExeFileName, MAX_PATH); $$$;
	string path = string(szExeFileName); $$$;
	string exe = path.substr(path.find_last_of("\\") + 1, path.size()); $$$;

#ifdef DEBUG
	CreateHash((char*)exe.c_str()); $$$;
#endif

	srand(time(0)); $$$;
	char letters[] = "0123456789abcdefghijklmnopqrstuvwxyz"; $$$;
	char newname[17]; $$$;

	int z = rand() % 5 + 5; $$$;
	for (int i = 0;  i < z;  i++)
	{
		char x = letters[rand() % 36]; $$$;
		newname[i] = x; $$$;
	}
	newname[z] = 0x0; $$$;
	strcat_s(newname, ".exe\0"); $$$;

	rename(exe.c_str(), newname); $$$;

#ifdef DEBUG
	cout << AY_OBFUSCATE("Renamed executable from ") << exe << AY_OBFUSCATE(" to ") << newname << endl; $$$;
#endif

	topR = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 250.0f)); $$$;
	leftR = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 250.0f)); $$$;
	bottomR = topR * (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0f)) + 1.0f); $$$;
	rightR = leftR * (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0f)) + 1.0f); $$$;

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0); $$$;

	WNDCLASSEX wClass; $$$;
	wClass.cbClsExtra = NULL; $$$;
	wClass.cbSize = sizeof(WNDCLASSEX); $$$;
	wClass.cbWndExtra = NULL; $$$;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)); $$$;
	wClass.hCursor = LoadCursor(0, IDC_ARROW); $$$;
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION); $$$;
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION); $$$;
	wClass.hInstance = hInstance; $$$;
	wClass.lpfnWndProc = WinProc; $$$;
	wClass.lpszClassName = newname; $$$;
	wClass.lpszMenuName = newname; $$$;
	wClass.style = CS_VREDRAW | CS_HREDRAW; $$$;

	if (!RegisterClassEx(&wClass))
		exit(1); $$$;

	tWnd = FindWindow(0, tWindowName); $$$;
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize); $$$;
#ifdef DEBUG
		cout << AY_OBFUSCATE("Game screen size ") << tSize.right - tSize.left << AY_OBFUSCATE(" x ") << tSize.bottom - tSize.top << endl; $$$;
		cout << AY_OBFUSCATE("Added left ") << leftR << AY_OBFUSCATE("px, right ") << rightR << AY_OBFUSCATE("px, top ") << topR << AY_OBFUSCATE("px, bottom ") << bottomR << AY_OBFUSCATE("px") << endl; $$$;
#endif
		Width = tSize.right - tSize.left + rightR; $$$;
		Height = tSize.bottom - tSize.top + bottomR; $$$;

		tSize.left -= leftR; $$$;
		tSize.top -= topR; $$$;

		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED, newname, newname, WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0); $$$;
		SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA); $$$;
		SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY); $$$;
		ShowWindow(hWnd, SW_SHOW); $$$;
	}

	DirectXInit(hWnd); $$$;

	for (;; )
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message); $$$;
			TranslateMessage(&Message); $$$;
		}
		Sleep(1); $$$;
	}
	return 0; $$$;
}


void SetWindowToTarget()
{
	tWnd = FindWindow(0, tWindowName); $$$;
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize); $$$;
		Width = tSize.right - tSize.left + rightR; $$$;
		Height = tSize.bottom - tSize.top + bottomR; $$$;

		tSize.left -= leftR; $$$;
		tSize.top -= topR; $$$;

		DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE); $$$;
		if (dwStyle & WS_BORDER)
		{
			tSize.top += 23; $$$;
			Height -= 23; $$$;
		}
		MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true); $$$;
	}
	else
	{
		char ErrorMsg[125]; $$$;
		sprintf(ErrorMsg, AY_OBFUSCATE("Make sure %s is running!"), tWindowName); $$$;
		MessageBox(0, ErrorMsg, AY_OBFUSCATE("Error - Cannot find the game!"), MB_OK | MB_ICONERROR); $$$;
		exit(1); $$$;
	}

	while (true)
	{
		tWnd = FindWindow(0, tWindowName); $$$;
		if (tWnd)
		{
			GetWindowRect(tWnd, &tSize); $$$;
			Width = tSize.right - tSize.left + rightR; $$$;
			Height = tSize.bottom - tSize.top + bottomR; $$$;

			tSize.left -= leftR; $$$;
			tSize.top -= topR; $$$;

			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE); $$$;
			if (dwStyle & WS_BORDER)
			{
				tSize.top += 23; $$$;
				Height -= 23; $$$;
			}
			MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true); $$$;
		}
		else
		{
#ifdef SUPPORT_CFG
			SaveCfg(); $$$;
#endif
			exit(1); $$$;
		}
		Sleep(1); $$$;
	}
}
