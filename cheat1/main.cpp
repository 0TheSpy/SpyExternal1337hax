#pragma once
#include "main.h"

void MenuSelect()
{
	while (true)
	{

		if (tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_INSERT) < 0) {
			if (drawmenu == 0) drawmenu = 1; else drawmenu = 0;
			Sleep(200);
		}

		if (drawmenu == 1 && tWnd == GetForegroundWindow()) {
			if (GetAsyncKeyState(VK_DOWN) < 0) {
				if (menuselect < cheat.Count() - 1)
					menuselect++; else menuselect = 0;
				Sleep(200);
			}

			if (GetAsyncKeyState(VK_UP) < 0) {
				if (menuselect > 0)
					menuselect--; else menuselect = cheat.Count() - 1;
				Sleep(200);
			}

			if (GetAsyncKeyState(VK_RIGHT) < 0) {
				if (cheat(menuselect).enabled < cheat(menuselect).modes)
					cheat(menuselect) = cheat(menuselect).enabled + 1;
				else
					cheat(menuselect) = 0;

				Sleep(cheat(menuselect).sleep);
			}

			if (GetAsyncKeyState(VK_LEFT) < 0) {
				if (cheat(menuselect).enabled > 0)
					cheat(menuselect) = cheat(menuselect).enabled - 1;
				else
					cheat(menuselect) = cheat(menuselect).modes;

				Sleep(cheat(menuselect).sleep);
			}
		}

		Sleep(1);
	}
}


void DisExit() {
	for (i = 0; i < cheat.Count(); i++)
		cheat(i) = 0;

	wpm(engine_dll_base + 0x4F0C44 - enginedelta, 0);

#ifdef DISCMSG
	char* discmsg = (char*)"Disconnect by user.";
	size_t size = strlen(discmsg);
	wvm(PVOID(engine_dll_base + 0x2E15C8), size, static_cast<void*>(discmsg));
#endif

	Sleep(1500);
	p_Device->Release();
	p_Object->Release();

	_Exit(1);
}

void myInit() {

	position.x = 20;
	position.y = 20;

	
	ptr = rpm( rpm(0x24000000 + 0x3E1A44) + 0x4);

	rvm(PVOID(vgui2_dll_base + 0x6cbc8), 4, &cmdptr);
	rvm(PVOID(cmdptr + 0xf5c), 4, &cmdptr);
	rvm(PVOID(cmdptr + 0x24), 4, &cmdptr);
	rvm(PVOID(cmdptr + 0x2b0), 4, &cmdptr);

	LPVOID xhairCave = VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#ifdef DEBUG
	std::cout << "xhair code cave allocated at: " << xhairCave << "\n";
#endif

	BYTE Xhairbytes[] = { 0x50, 0x0f, 0xcb, 0x88, 0xd8, 0x3c, 0x0e, 0x58, 0x74, 0x2e, 0x0f, 0x1f, 0x40,
						  0x00, 0x83, 0xff, 0x00, 0x74, 0x25, 0x0f, 0x1f, 0x40, 0x00, 0x39, 0xc7, 0x74,
						  0x13, 0x0f, 0x1f, 0x40, 0x00, 0xc7, 0x05, 0x08, 0x72, 0x3e, 0x24, 0x02, 0x00,
						  0x00, 0x00, 0xeb, 0x0d, 0x0f, 0x1f, 0x00, 0xc7, 0x05, 0x08, 0x72, 0x3e,
						  0x24, 0x01, 0x00, 0x00, 0x00, 0x0f, 0xcb, 0x68, 0xa8, 0xe2, 0x1b, 0x24, 0xc3 };

	WriteProcessMemory(hProcess, xhairCave, &Xhairbytes, sizeof(Xhairbytes), NULL);

	BYTE caveaddr[sizeof(DWORD)];
	DWORD dxhairCave = 0xFFFFFFFF - (0x24000000 + 0x1BE2A2 + 0x4 - (DWORD)xhairCave);
	memcpy(caveaddr, &dxhairCave, sizeof(DWORD));

	WriteProcessMemory(hProcess, LPVOID(0x24000000 + 0x1BE2A2), &jmp, sizeof(BYTE), NULL);
	WriteProcessMemory(hProcess, LPVOID(0x24000000 + 0x1BE2A2 + sizeof(BYTE)), &caveaddr, sizeof(DWORD), NULL);
	WriteProcessMemory(hProcess, LPVOID(0x24000000 + 0x1BE2A2 + sizeof(BYTE) + sizeof(DWORD)), &nop, sizeof(BYTE), NULL);

	DWORD colorifptr;
	rvm(PVOID(gameui_dll_base + 0x1BB95C), 4, &colorifptr);
	rvm(PVOID(colorifptr + 0x3A4), 4, &colorifptr);

	//DWORD concol = 0xFFABE707;
	DWORD concol = 0xFF6F6FCB;
	wpm(PVOID(colorifptr + 0x4CC), 4, &concol); //set console text color
	SendCMD("echo Spy External Multihax ACTIVATED");
	Sleep(100);
	concol = 0xFFD8D8D8;
	wpm(PVOID(colorifptr + 0x4CC), 4, &concol); //reset console text color
	rvm(PVOID(0x24000000 + 0x3EDB98), 4, &vmatrixptr);

	char pattern2[] = "\x74\x07\x80\x7c\x24\x34\x00\x75\x02";
	char mask2[] = "xxxxxxxxx";
	aobcmdnum = ExternalAoBScan(hProcess, engine_dll_base, pattern2, mask2);
#ifdef DEBUG
	printf("Sequence AOBscan result = %0x\n", aobcmdnum);
#endif
	enginedelta = aobcmdnum - engine_dll_base - 0x42580;
#ifdef DEBUG
	printf("Sequence delta = %0x\n", enginedelta);
#endif

	char pattern3[] = "\xF3\xA4\x8B\x43\x40";
	char mask3[] = "xxxxx";
	aobconsole = ExternalAoBScan(hProcess, engine_dll_base, pattern3, mask3);
	SendCMD("alias name");

	spec1 = DWORD(SpyInjectAndJump(Spec1, LPVOID(0x24000000 + 0x2076BE), 4));
	spec2 = DWORD(SpyInject(Spec2, LPVOID(0x24000000 + 0x257351))); //2

	rotating = SpyInject(Rotatingg, PVOID(0x24000000 + 0xF85A4));

	//for chams colors
	byte chamscolors[] = { 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF };
	wpm(PVOID(0x17154), sizeof(chamscolors), &chamscolors);

	byte createcolors[] = { 0x0F, 0xB6, 0x05, 0xDB, 0x73, 0x01, 0x00, 0x83, 0xF8, 0x04, 0x0F, 0x8D, 0x47, 0x01, 0x00, 0x00, 
		0x8B, 0xF4, 0x6A, 0x00, 0x0F, 0xB6, 0x05, 0xDB, 0x73, 0x01, 0x00, 0x8D, 0x0C, 0x85, 0x74, 0x75, 0x01, 0x00, 0x51, 0x6A, 
		0x00, 0x6A, 0x15, 0x6A, 0x00, 0x6A, 0x01, 0x6A, 0x08, 0x6A, 0x08, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x4D, 0x08, 0x51, 
		0x8B, 0x50, 0x5C, 0xFF, 0xD2, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 0x40, 0x00, 0x8B, 0xF4, 0x6A, 0x00, 0x68, 0x1C, 
		0x74, 0x01, 0x00, 0x6A, 0x02, 0x6A, 0x15, 0x6A, 0x00, 0x6A, 0x01, 0x6A, 0x08, 0x6A, 0x08, 0x8B, 0x45, 0x08, 0x8B, 0x08, 
		0x8B, 0x55, 0x08, 0x52, 0x8B, 0x41, 0x5C, 0xFF, 0xD0, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 0x40, 0x00, 0x8B, 0xF4, 
		0x68, 0x00, 0x48, 0x00, 0x00, 0x6A, 0x00, 0x68, 0x20, 0x74, 0x01, 0x00, 0x6A, 0x00, 0xA1, 0x1C, 0x74, 0x01, 0x00, 0x8B, 
		0x08, 0x8B, 0x15, 0x1C, 0x74, 0x01, 0x00, 0x52, 0x8B, 0x41, 0x4C, 0xFF, 0xD0, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 
		0x40, 0x00, 0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x0C, 0x0F, 0x1F, 0x00, 0x8B, 0x45, 0xF8, 0x83, 0xC0, 0x01, 
		0x89, 0x45, 0xF8, 0x83, 0x7D, 0xF8, 0x40, 0x73, 0x20, 0x0F, 0x1F, 0x40, 0x00, 0x0F, 0xB6, 0x05, 0xDB, 0x73, 0x01, 0x00, 
		0x8B, 0x4D, 0xF8, 0x8B, 0x15, 0x24, 0x74, 0x01, 0x00, 0x8B, 0x04, 0x85, 0x54, 0x71, 0x01, 0x00, 0x89, 0x04, 0x8A, 0xEB, 
		0xD1, 0x8B, 0xF4, 0x6A, 0x00, 0xA1, 0x1C, 0x74, 0x01, 0x00, 0x8B, 0x08, 0x8B, 0x15, 0x1C, 0x74, 0x01, 0x00, 0x52, 0x8B, 
		0x41, 0x50, 0xFF, 0xD0, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 0x40, 0x00, 0x0F, 0xB6, 0x05, 0xDB, 0x73, 0x01, 0x00, 
		0x8B, 0xF4, 0x8B, 0x0C, 0x85, 0x74, 0x75, 0x01, 0x00, 0x51, 0x8B, 0x15, 0x1C, 0x74, 0x01, 0x00, 0x52, 0x8B, 0x45, 0x08, 
		0x8B, 0x08, 0x8B, 0x55, 0x08, 0x52, 0x8B, 0x41, 0x7C, 0xFF, 0xD0, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 0x40, 0x00, 
		0xA1, 0x1C, 0x74, 0x01, 0x00, 0x8B, 0x08, 0x8B, 0xF4, 0x8B, 0x15, 0x1C, 0x74, 0x01, 0x00, 0x52, 0x8B, 0x41, 0x08, 0xFF, 
		0xD0, 0x39, 0xE6, 0xF2, 0x75, 0x05, 0x0F, 0x1F, 0x40, 0x00, 0xA0, 0xDB, 0x73, 0x01, 0x00, 0x04, 0x01, 0xA2, 0xDB, 0x73, 
		0x01, 0x00, 0xE9, 0xA9, 0xFE, 0xFF, 0xFF
	,0xC3}; //ret
	LPVOID ColorsCave = VirtualAllocEx(hProcess, NULL, sizeof(createcolors), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	wpm (ColorsCave, sizeof(createcolors), &createcolors);
	wpm(0x12420, DWORD(ColorsCave));
#ifdef DEBUG
	cout << "ColorsCave = 0x" << hex << DWORD(ColorsCave) << endl;
#endif

#ifdef DISCMSG
	char* discmsg = (char*)"SpyExternalMultihax";
	size_t size = strlen(discmsg);
	wvm(PVOID(engine_dll_base + 0x2E15C8), size, static_cast<void*>(discmsg));
#endif

	char pattern4[] = "\x0F\x94\xC0\x88\x45\xF4\xE8";
	char mask4[] = "xxxxxxx";
	aobfakelag = ExternalAoBScan(hProcess, engine_dll_base, pattern4, mask4);
#ifdef DEBUG
	printf("FakeLag AOBscan result = %0x\n", aobfakelag);
#endif

	cheat.New("Aimbot", 2);
	cheat.New("Aimbot FOV", 99); 
	cheat("Aimbot FOV").sleep = 30;
	cheat("Aimbot FOV") = 45;
	cheat.New("ESP", 3);
	cheat.New("Chameleon Wallhack");
	cheat.New("Radarhack", 3);
	cheat.New("Serverinfo & Bombtimer");
	cheat.New("Triggerbot & Crosshair",2);
	cheat.New("No Recoil & No Spread", 3);
	cheat.New("No Smoke & No Flash");
	cheat.New("No Hands & No Sky");
	cheat.New("Bunnyhop & Autostrafe", 2);
	cheat.New("Speedhack",100);
	cheat("Speedhack") = 10;
	cheat("Speedhack").sleep = 60;
	cheat.New("Spinbot & AntiAim",3); 
	cheat.New("Silent FastLadder",2);
	cheat.New("Fake Lag", 3);
	cheat.New("SteamID Spoof & No MOTD");
	cheat.New("Inputfromfile & Loopback");
	cheat.New("Namestealer | Light Spam",2);
	cheat.New("Free Cam");
	cheat.New("Disable All & Exit");

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MenuSelect, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aimbot, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Bunnyhop, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Namestealer, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TriggerCheck, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Flyhack, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Spinbot, 0, 0, 0);
#ifdef DEBUG
	std::cout << "initiated\n";
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
			char * value = tWindowName;

			HWND newhwnd = FindWindow(NULL, value);
			if (newhwnd != NULL) {
				GetWindowRect(newhwnd, &rc);
			}
			else {
				ExitProcess(0);
			}

			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
			p_Device->BeginScene();

			myDraw();

			p_Device->EndScene();
			p_Device->Present(NULL, NULL, NULL, NULL);
		}
		else
		{
			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
			p_Device->BeginScene();

			p_Device->EndScene();
			p_Device->PresentEx(0, 0, 0, 0, 0);
		}
		
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin);

#ifdef DEBUG
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		printf("Debugging Window:\n");
#endif

		hProcess = get_process_handle();
		myInit();

		break;

	case WM_DESTROY:
		CloseHandle(hProcess);
		PostQuitMessage(1);
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);
	
	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = lWindowName;
	wClass.lpszMenuName = lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wClass))
		exit(1);

	tWnd = FindWindow(0, tWindowName);
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize);
		Width = tSize.right - tSize.left;
		Height = tSize.bottom - tSize.top;
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED, lWindowName, lWindowName, WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0);
		SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
		SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
		ShowWindow(hWnd, SW_SHOW);
	}

	DirectXInit(hWnd);

	//
	DWORD* vtablePtr = (DWORD*)(*((DWORD*)p_Device));
	DWORD hD3D9 = (DWORD)GetModuleHandle("d3d9.dll");
	dip9 = vtablePtr[82] - (DWORD)hD3D9; //DrawIndexedPrimitive
	reset9 = vtablePtr[16] - (DWORD)hD3D9; //RESET
	asmWHcave = SpyInject(asmWH, PVOID(d3d9_dll_base + dip9)); 
	wpm(0x12440, d3d9_dll_base + dip9);
#ifdef DEBUG
	cout << "DrawIndexedPrimitive9 = d3d9.dll+0x" << hex << dip9 << endl;
	cout << "Reset9 = d3d9.dll+0x" << hex << reset9 << endl;
#endif
	for (;;)
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message);
			TranslateMessage(&Message);
		}
		Sleep(1);
	}
	return 0;
}


void SetWindowToTarget()
{
	tWnd = FindWindow(0, tWindowName);
	if (tWnd)
	{
		GetWindowRect(tWnd, &tSize);
		Width = tSize.right - tSize.left;
		Height = tSize.bottom - tSize.top;
		DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
		if (dwStyle & WS_BORDER)
		{
			tSize.top += 23;
			Height -= 23;
		}
		MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true);
	}
	else
	{
		char ErrorMsg[125];
		sprintf(ErrorMsg, "Make sure %s is running!", tWindowName);
		MessageBox(0, ErrorMsg, "Error - Cannot find the game!", MB_OK | MB_ICONERROR);
		exit(1);
	}

	while (true)
	{
		tWnd = FindWindow(0, tWindowName);
		if (tWnd)
		{
			GetWindowRect(tWnd, &tSize);
			Width = tSize.right - tSize.left;
			Height = tSize.bottom - tSize.top;
			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				tSize.top += 23;
				Height -= 23;
			}
			MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true);
		}
		else
		{
			exit(1);
		}
		Sleep(1);
	}
}
