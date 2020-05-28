#pragma once

#include "main.h"
#include "asm.cpp"

void SendCMD(const char *cmd)
{
#ifdef DEBUG
	printf("Sending %s\n", cmd);
#endif
	char* newcmd = (char*)cmd;
	size_t size = strlen(cmd);
	wpm(PVOID(cmdptr + 0x728 + 0x2004), 1, &size);
	wpm(PVOID(cmdptr + 0x728), size, static_cast<void*>(newcmd));
}


const auto sqrtss = [](float in)
{
	__m128 reg = _mm_load_ss(&in);
	return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
};


void menu()
{
	SetLayeredWindowAttributes(hWnd, NULL, NULL, NULL);
	DwmEnableBlurBehindWindow(hWnd, &bb);

	ID3DXFont* pFont;
	D3DXCreateFont(p_Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);

	DrawString((char*)"Spy External Multihax 1.1", 5, 5, 25, 255, 255, 255, pFont);

	if (drawmenu == 1) {
		DrawFilledRectangle(20, 300, 275 + border, 345 + border + cheat.Count() * 25, colorprim);
		DrawFilledRectangle(20 + border, 330, 275, 345 + cheat.Count() * 25, colorsec);

		DrawString((char*)"Spy External Multihax", 65, 305, colorsec, pFont);

		int menutop = 340;
		for (byte i = 0; i < cheat.Count(); i++)
		{
			if (menuselect == i) {
				color = D3DCOLOR_ARGB(255, 255, 255, 255);
			}
			else if (cheat(i).name == "Disable All & Exit")
			{
				color = D3DCOLOR_ARGB(255, 175, 125, 0);
			}
			else {
				color = colorprim;
			}

			DrawString((char*)cheat(i).name.c_str(), 35, menutop, color, pFont);

			if (cheat(i).name != "Speedhack")
			{
				if (cheat(i).enabled < 10)
					DrawString((char*)(std::to_string(cheat(i).enabled).c_str()), 255, menutop, color, pFont);
				else
					DrawString((char*)(std::to_string(cheat(i).enabled).c_str()), 255 - 4, menutop, color, pFont);
			}
			else
			{
				if (cheat(i).enabled != 100)
					DrawString((char*)(std::to_string((float)cheat(i).enabled / (float)10.f).c_str()), 248, menutop, 3, color, pFont);
				else
					DrawString((char*)"OMG", 255 - 20, menutop, color, pFont);
			}
			menutop += 25;
		}
	}
	pFont->Release();
}

void fakeLag() {
	
	
			if (cheat("Fake Lag") == 1)
				SpyInjectAndJump(FakeLag, PVOID(aobfakelag), 1);
			if (cheat("Fake Lag") != 1 && cheat("Fake Lag").trigger == 1)
			{
				byte bytes[] = { 0x0F, 0x94, 0xC0, 0x88, 0x45, 0xF4 };
				wvm(PVOID(aobfakelag), sizeof(bytes), bytes);
			}

			if (cheat("Fake Lag") == 2) //EXPERIMENTAL
			{
				wpm(0x12345, 0);
				byte bytes1[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
				wvm(PVOID(engine_dll_base + 0x42727 + enginedelta), sizeof(bytes1), bytes1); //comment for burst-fire
				byte bytes2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
				wvm(PVOID(engine_dll_base + 0x426D9 + enginedelta), sizeof(bytes2), bytes2);

				wpm(engine_dll_base + 0x3953bc - enginedelta, 22);
				wpm(engine_dll_base + 0x3953c0 - enginedelta, 31);

				wpm(engine_dll_base + 0x51f794 - enginedelta, 1); //sv cheats 1
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, 38.0f); //host_timescale
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 12.0f); //host_framerate
				SendCMD("cl_predictweapons 0");
			}

			if (cheat("Fake Lag") != 2 && cheat("Fake Lag").trigger == 2) 
			{
				dword2bytes dw2b3 = { engine_dll_base + 0x3953C0 - enginedelta };
				dword2bytes dw2b4 = { engine_dll_base + 0x3953bc - enginedelta };
				byte bytes3[] = { 0x83, 0x05, dw2b3.bytes[0],dw2b3.bytes[1],dw2b3.bytes[2],dw2b3.bytes[3], 0x01 };
				wvm(PVOID(engine_dll_base + 0x42727 + enginedelta), sizeof(bytes3), bytes3);
				byte bytes4[] = { 0xA3, dw2b4.bytes[0],dw2b4.bytes[1],dw2b4.bytes[2],dw2b4.bytes[3], 0xC7, 0x05, dw2b3.bytes[0],dw2b3.bytes[1],dw2b3.bytes[2],dw2b3.bytes[3], 0x00, 0x00, 0x00, 0x00 };
				wvm(PVOID(engine_dll_base + 0x426D9 + enginedelta), sizeof(bytes4), bytes4);

				wpm(engine_dll_base + 0x51f794 - enginedelta, 0); //sv cheats 0
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, 1.0f);	//host_timescale
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 0.0f); //host_framerate
				wpm(0x24000000 + 0x3E71E4, 4);
			}

			if (cheat("Fake Lag") == 3) //fake ping
				wpm(engine_dll_base + 0x4F5988 - enginedelta, 500.0f);
			if (cheat("Fake Lag") != 3 && cheat("Fake Lag").trigger == 3)
				wpm(engine_dll_base + 0x4F5988 - enginedelta, 0);

}

void WH() {
	if (cheat("Chameleon Wallhack") == 1) {
		SpyJmp(PVOID(d3d9_dll_base + dip9), asmWHcave, 0); 
		SendCMD("cl_ragdoll_physics_enable 0; cl_min_ct 3; cl_min_t 3");
		wpm(0x24000000 + 0x3F95EC, 1); //minmodels 1

		if (rpm(d3d9_dll_base + reset9) == 0x8B55FF8B)
			SpyInjectAndJump(d3d9Reset, PVOID(d3d9_dll_base + reset9), 0);

	}
	if (cheat("Chameleon Wallhack") == 0) {
		byte bytes[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC };
		wvm(PVOID(d3d9_dll_base + dip9), sizeof(bytes), bytes);
		SendCMD("cl_ragdoll_physics_enable 1");
		wpm(0x24000000 + 0x3F95EC, 0); //minmodels 0
	}
}

void Namestealer() {

	int maxplayers;
	TCHAR name[32];

	int rando, old = 65;
	while (true) {
		
		if (cheat("Namestealer | Light Spam") == 1) {
			rvm(PVOID(engine_dll_base + 0x366E74), 4, &maxplayers);
			rando = rand() % maxplayers;
			rvm(PVOID(0x24000000 + 0x39D4FC), 1, &myid);

			if (rando + 1 == (int)myid)
				continue;

			if (rando == old)
				continue;

			name[0] = 0x0;
			if (enginedelta)
				rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958A8) + 0x38) + 0x24) + 0x14 + (0x28 * (rando) ))), 32, &name);
			else
				rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958C8) + 0x38) + 0x24) + 0x14 + (0x28 * (rando) ))), 32, &name);

			if ((int)name[0] > 0x20 || (int)name[0] < 0)
			{
#ifdef DEBUG
				std::cout << rando << " set name to " << name << std::endl;
#endif
				char towrite[64] = "setinfo name \u0022";
				strcat_s(towrite, name);
				strcat_s(towrite, " \u0022");
				SendCMD(towrite);

				old = rando;
				Sleep(500);
			}
		}
		
		if (cheat("Namestealer | Light Spam") == 2)
		{
			SendCMD("impulse 100");
			Sleep(10);
		}
		Sleep(1);
	}
}

void Bunnyhop()
{
	#define FORCE_JUMP_BITMASK (1<<0)
	std::bitset<8> dwForceJumpBitMask{ 0b0000'0001 };
	int currJumpState{ 0 };

	float VisY, VisYnew;
	float VisYd;
	while (true)
	{
		if (cheat("Bunnyhop & Autostrafe") == 1 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0)
		{
			rvm(PVOID(0x24000000 + 0x3FD550), 4, &VisY); //read Y
			VisYnew = VisY;

			wpm(0x24000000 + 0x3E71E4, 6); //jump
			while (cheat("Bunnyhop & Autostrafe") == 1 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0)
			{
				rvm(PVOID(0x24000000 + 0x3FD550), 4, &VisYnew); //read new Y

				if (VisY != VisYnew) //Y changed?
				{
					boostsleep = 1;
					VisYd = VisY - VisYnew; 

					if (cheat("Spinbot & AntiAim") == 0) {
						if (VisYd < 0.0f)
						{
							wpm(0x24000000 + 0x3E7250, 0); //-moveright
							wpm(0x24000000 + 0x3E725C, 1); //+moveleft
						}
						else
						{
							wpm(0x24000000 + 0x3E7250, 1); //+moveright 
							wpm(0x24000000 + 0x3E725C, 0); //-moveleft
						}
					}

					else
					{
						if (VisYd < 0.0f)
						{
							wpm(0x24000000 + 0x3E7250, 1); //+moveright
							wpm(0x24000000 + 0x3E725C, 0); //-moveleft
						}
						else
						{
							wpm(0x24000000 + 0x3E7250, 0); //-moveright 
							wpm(0x24000000 + 0x3E725C, 1); //+moveleft
						}
					}

					wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 1.0f); //reset Z angle
					wpm(0x1234D, 5 * VisYd); //ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
					VisY = VisYnew; //set New Y as old Y
				}

				rvm( PVOID(0x24000000 + 0x3E71E4), sizeof(currJumpState), &currJumpState);
				if (rpm(0x24000000 + 0x3EA03C)) //onGround?
				{
					currJumpState |= FORCE_JUMP_BITMASK;
					wpm( PVOID(0x24000000 + 0x3E71E4), sizeof(currJumpState), &currJumpState);
#ifdef DEBUG
					cout << "jumping\n";
#endif
				}
				else 
				{
					currJumpState &= ~FORCE_JUMP_BITMASK;
					wpm( PVOID(0x24000000 + 0x3E71E4), sizeof(currJumpState), &currJumpState);
				}

				Sleep(1);
			}
			wpm(0x24000000 + 0x3E7250, 0); //-moveright 
			wpm(0x24000000 + 0x3E725C, 0); //-moveleft
			wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 1.0f); //reset Z angle
			wpm(0x1234D, 0); //ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		}


		if (cheat("Bunnyhop & Autostrafe") == 2 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0)
		{
			wpm(0x24000000 + 0x3E71A8, 5); //duck
			wpm(0x24000000 + 0x3E71E4, 6);
			while (cheat("Bunnyhop & Autostrafe") == 2 && tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_SPACE) < 0)
			{
				if (rpm(0x24000000 + 0x3EA03C)) //onGround
				{
					wpm(0x24000000 + 0x3E71E4, 6);
				}
				Sleep(1);
			}
			wpm(0x24000000 + 0x3E71A8, 4); //unduck
		}

		Sleep(1);
	}
}

void Flyhack()
{
	flycave = DWORD(SpyInject(Fly, LPVOID(0x24000000 + 0xB841B)));
	float vispos[3], flyangX, flyangY;
	while (true) {
		if (cheat("Free Cam") == 1) {
			rvm((PVOID)(localplayer + 0x29C), 12, &vispos);
			while (cheat("Free Cam") == 1 && tWnd == GetForegroundWindow()) {
				rvm(PVOID(0x24000000 + 0x3FD550 - 4), 4, &flyangX);
				rvm(PVOID(0x24000000 + 0x3FD550), 4, &flyangY);

				flyangY -= 90.0;
				if (GetAsyncKeyState(0x57) < 0) //W
				{
					vispos[0] += -sin(flyangY * PI / 180);
					vispos[1] += cos(flyangY * PI / 180);
					wpm((LPVOID)(localplayer + 0x29C), 4, &vispos[0]);
					wpm((LPVOID)(localplayer + +0x29C + 0x4), 4, &vispos[1]);
					vispos[2] += -sin(flyangX * PI / 180);
					wpm((LPVOID)(localplayer + +0x29C + 0x8), 4, &vispos[2]);
				}

				if (GetAsyncKeyState(0x53) < 0) //S
				{
					vispos[0] -= -sin(flyangY * PI / 180);
					vispos[1] -= cos(flyangY * PI / 180);
					wpm((LPVOID)(localplayer + 0x29C), 4, &vispos[0]);
					wpm((LPVOID)(localplayer + +0x29C + 0x4), 4, &vispos[1]);
					vispos[2] += sin(flyangX * PI / 180);
					wpm((LPVOID)(localplayer + +0x29C + 0x8), 4, &vispos[2]);
				}

				if (GetAsyncKeyState(0x41) < 0) //A
				{
					vispos[0] -= cos(flyangY * PI / 180);
					vispos[1] -= sin(flyangY * PI / 180);

					wpm((LPVOID)(localplayer + 0x29C), 4, &vispos[0]);
					wpm((LPVOID)(localplayer + +0x29C + 0x4), 4, &vispos[1]);
				}

				if (GetAsyncKeyState(0x44) < 0) //D
				{
					vispos[0] += cos(flyangY * PI / 180);
					vispos[1] += sin(flyangY * PI / 180);

					wpm((LPVOID)(localplayer + 0x29C), 4, &vispos[0]);
					wpm((LPVOID)(localplayer + +0x29C + 0x4), 4, &vispos[1]);
				}
				Sleep(1);
			}
		}
		Sleep(1);
	}
}

void Spinbot()
{
	float visX;
	float visY;

	float visYd = 0;

	freevisangX = SpyInject(FreeVisualAnglesX, PVOID(0x2415D32E));
	freevisangY = SpyInject(FreeVisualAnglesY, PVOID(0x2415D3A0));
	freevisangZ = SpyInject(FreeVisualAnglesZ, PVOID(0x2415D412));

	fixPredict = SpyInject(FixPredict, PVOID(0x240D46F9));

	SpyInjectAndJump(ZetToZero, PVOID(0x24000000 + 0x192B0), 4); 

	wpm(0x12300, 180.0f);
	wpm(0x12304, -180.0f);
	wpm(0x12308, 360.0f);

	while (true)
	{

		if (cheat("Spinbot & AntiAim") == 1)
		{
			SpyJmp(PVOID(0x24000000 + 0xF85A4), rotating, 5);			
			wpm(0x12334, 45.0f); //set spinhack speed
			wpm(0x12345, 90.0f); //set X ang
			wpm(0x12220, 1); //semaphore
			while (cheat("Spinbot & AntiAim") == 1) {
				
				if (GetAsyncKeyState(VK_LBUTTON) == 0)
				{	
					rvm(PVOID(0x12345), 4, &visX);
					if (visX != 90.0f && visX != -90.0f)
					wpm(0x12345, 90.0f);
				}

				if (GetAsyncKeyState(0x57) < 0 || GetAsyncKeyState(0x53) < 0) //w/s
				{
					if (GetAsyncKeyState(0x57) < 0) //w
						visYd = 90.0f;
					else //s
						visYd = -90.0f;
					//
					if (GetAsyncKeyState(0x57) < 0 && GetAsyncKeyState(0x41) < 0) //w+a
						visYd -= 45.0f;
					else
						if (GetAsyncKeyState(0x53) < 0 && GetAsyncKeyState(0x41) < 0) //s+a
							visYd -= -45.0f;

					if (GetAsyncKeyState(0x57) < 0 && GetAsyncKeyState(0x44) < 0) //w+d
						visYd -= -45.0f;
					else
						if (GetAsyncKeyState(0x53) < 0 && GetAsyncKeyState(0x44) < 0) //s+d
							visYd -= 45.0f;
					wpm(0x12330, visYd);
				}
				else
				{
					if (GetAsyncKeyState(0x41) < 0) //a
					{
						visYd = 0;
						wpm(0x12330, visYd);
					}
					if (GetAsyncKeyState(0x44) < 0) //d
					{
						visYd = 180;
						wpm(0x12330, visYd);
					}
				}

				wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 1.0f); //z
				Sleep(1);
			}
			wpm(0x12204, 1);

			wpm(0x12334, 0); //rotation to 0
			wpm(0x1234D, 0); //z to 0

			byte bytes2[] = { 0x8b, 0x4c, 0x24, 0x14, 0x89, 0x0b, 0x8b, 0x54, 0x24, 0x18 };
			wvm(PVOID(0x24000000 + 0xF85A4), sizeof(bytes2), bytes2);
		}

		if (cheat("Spinbot & AntiAim") == 2) //UPSIDE-DOWN
		{
			wpm(DWORD(freevisangX) + 1, 0xA13E9090);
			wpm(0x12345, 179.99f);
			while (cheat("Spinbot & AntiAim") == 2)
			{
				if (GetAsyncKeyState(VK_LBUTTON) == 0)
				{
					rvm(PVOID(0x24000000 + 0x3FD54C + 4), 4, &visY);
					visY += 180.0f;
					if (visY > 180.0f) visY -= 360.0f;
					if (visY < -180.0f) visY += 360.0f;
					wpm(0x12349, visY);

					rvm(PVOID(0x12345), 4, &visX);
					if (visX != 178.3999939f && visX != 178.5f)
						wpm(0x12345, 178.3999939f);
				}

				Sleep(1);
			}
			wpm(DWORD(freevisangX) + 1, 0xA13E2AEB);
		}

		if (cheat("Spinbot & AntiAim") == 3) //BACKWARDS
		{

			while (cheat("Spinbot & AntiAim") == 3)
			{

				if (GetAsyncKeyState(VK_LBUTTON) == 0)
				{
					rvm(PVOID(0x24000000 + 0x3FD54C + 4), 4, &visY);
					visY += 180.0f;
					if (visY > 180.0f) visY -= 360.0f;
					if (visY < -180.0f) visY += 360.0f;

					wpm(0x12345, 88.0f);
					wpm(0x12349, visY);
				}
				Sleep(1);
			}

		}

		Sleep(1);
	}
}

void CalcAngle(float *src, float *dst, float *angles)
{
	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	double hyp = sqrtss(delta[0] * delta[0] + delta[1] * delta[1]);
	angles[0] = (float)(atan(delta[2] / hyp) * 180.0 / 3.14159265);
	angles[1] = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;

	if (delta[0] >= 0.0) angles[1] += 180.0f;
}

void FastLadder(int z)
{
#ifdef DEBUG
	cout << "onladder\n";
#endif
	switch (z)
	{
	case 1:
		float myang[3];
		wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 1.0f); //set z ang

		while (rpm(localplayer + 0x134) == 9) {
			rvm(PVOID(0x24000000 + 0x3FD54C), 12, &myang);
			myang[0] = 0.0f;
			myang[2] = -90.0f;
			if (GetAsyncKeyState(0x57) < 0) //w pressed
			{
				wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				wpm(0x24000000 + 0x3E7250, 1); //+moveright
			}

			else if (GetAsyncKeyState(0x53) < 0) //s pressed
			{
				wpm(0x24000000 + 0x3E725C, 1); //+moveleft
				wpm(0x24000000 + 0x3E7250, 0); //-moveright
			}
			else
			{
				wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				wpm(0x24000000 + 0x3E7250, 0); //-moveright
			}
			wpm(PVOID(0x12345), 12, &myang);
		}
		wpm(0x24000000 + 0x3E725C, 0); //-moveleft
		wpm(0x24000000 + 0x3E7250, 0); //-moveright
		wpm(0x1234D, 0);

		//smooth x ang
		float realang, r;
		do {
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			rvm(PVOID(0x24000000 + 0x3FD54C), 4, &myang);
			rvm(PVOID(0x12345), 4, &realang);

			if (myang[0] > realang)
				realang += r;
			else realang -= r;

			wpm(0x12345, realang);
			Sleep(1);
		} while (abs(myang[0] - realang) > 3.0f);
		break;
	case 2:
		while (rpm(localplayer + 0x134) == 9) {
			rvm(PVOID(0x24000000 + 0x3FD54C), 8, &myang);
			float Up_down;
			if (myang[0] < 15.0f)
				Up_down = -89.0f;
			else Up_down = 89.0f;

			if (GetAsyncKeyState(0x57) < 0) //w pressed
			{
				myang[0] = Up_down;
				if (myang[1] > 135.0f && myang[1] <= 180.0f)
				{
					myang[1] = 90.0f;
					wpm(0x24000000 + 0x3E725C, 1); //+moveleft
					wpm(0x24000000 + 0x3E7250, 0); //-moveright
				}
				else if (myang[1] <= 135.0f && myang[1] >= 90.0f)
				{
					myang[1] = 179.0f;
					wpm(0x24000000 + 0x3E7250, 1); //+moveright
					wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				}
				else if (myang[1] <= -135.0f && myang[1] >= -180.0f)
				{
					myang[1] = -90.f;
					wpm(0x24000000 + 0x3E7250, 1); //+moveright
					wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				}
				else if (myang[1] <= 90.0f && myang[1] >= 45.0f)
				{
					myang[1] = 0;
					wpm(0x24000000 + 0x3E725C, 1); //+moveleft
					wpm(0x24000000 + 0x3E7250, 0); //-moveright
				}
				else if (myang[1] >= -90.0f && myang[1] <= -45.0f)
				{
					myang[1] = -0;
					wpm(0x24000000 + 0x3E7250, 1); //+moveright
					wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				}
				else if (myang[1] <= -90.0f && myang[1] >= -135.0f)
				{
					myang[1] = -179.0f;
					wpm(0x24000000 + 0x3E725C, 1); //+moveleft
					wpm(0x24000000 + 0x3E7250, 0); //-moveright
				}
				else if (myang[1] <= 45.0f && myang[1] > 0.0f)
				{
					myang[1] = 90.0f;
					wpm(0x24000000 + 0x3E7250, 1); //+moveright
					wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				}
				else if (myang[1] <= -0.0f && myang[1] >= -45.0f)
				{
					myang[1] = -90.0f;
					wpm(0x24000000 + 0x3E725C, 1); //+moveleft
					wpm(0x24000000 + 0x3E7250, 0); //-moveright
				}
				//duck
			}
			else
			{
				wpm(0x24000000 + 0x3E725C, 0); //-moveleft
				wpm(0x24000000 + 0x3E7250, 0); //-moveright
			}
			wpm(PVOID(0x12345), 8, &myang);
		}
		wpm(0x24000000 + 0x3E725C, 0); //-moveleft
		wpm(0x24000000 + 0x3E7250, 0); //-moveright
		break;
	}
}


void Aimbot()
{
	byte four = 4, five = 5, six = 6;

	DWORD boneptr;
	float mycoords[3];
	float myangle[2];
	float newangle[2];
	float enemycoords[3];
	double delta[3];
	double hyp;

	bool aiming = 0;

	DWORD ecx, eax;
	int randomseed;
	int realseed;
	float realup, realright;

	float myang[2], newangg[2];
	float punch[2]; DWORD punchptr;

	float xx, yy;

	while (true)
	{
		if (cheat("Triggerbot & Crosshair") == 1)
		{
			if (rpm(0x243E7208) == 0x00000002) 
			{
				Sleep(rand() % 15 + 100);
				wpm(0x243E71D8, 6);
				Sleep(rand() % 100 + 30);
			}
		}


		if (angleshack && GetAsyncKeyState(VK_LBUTTON) == 0  && cheat("Spinbot & AntiAim") == 0)
		{
			rvm(PVOID(0x24000000 + 0x3FD54C), 8, &myang);

			if (rpm(localplayer + 0x134) == 9 && cheat("Silent FastLadder").enabled > 0)
				FastLadder(cheat("Silent FastLadder").enabled);
			else	
				wpm(PVOID(0x12345), 8, &myang);

			Sleep(1);
		}

		if (tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_LBUTTON) < 0) {

			if (cheat("Aimbot") == 2)
				SetCursorPos(tSize.left + xl_closest_final, tSize.top + yl_closest_final);

			if (cheat("Aimbot") == 1) {
				rvm(PVOID(0x24000000 + 0x3FD5C4), 12, &mycoords);

				if (closest_final != -2) {

					rvm(PVOID(0x24000000 + 0x3BF1E4 + 0x10 * closest_final), 4, &boneptr);
					rvm(PVOID(boneptr + 0x4A8), 4, &boneptr);
					rvm((PVOID)(boneptr + 0x60 + 0x24C), 4, &enemycoords[0]);
					rvm((PVOID)(boneptr + 0x60 + 0x25C), 4, &enemycoords[1]);
					rvm((PVOID)(boneptr + 0x60 + 0x26C), 4, &enemycoords[2]);
					enemycoords[2] = enemycoords[2] + 2;
					CalcAngle(mycoords, enemycoords, newangle);

					if (newangle[1] < -180.0f)
						newangle[1] += 360.0f;
					else
						if (newangle[1] > 180.0f) newangle[1] -= 360.0f;

					if (!isnan(newangle[0])) {

						aiming = 1;

						if (cheat("Spinbot & AntiAim").enabled > 1 && cheat("No Recoil & No Spread") != 1) //metka1
						{
							if (cheat("Spinbot & AntiAim") == 2)
							{
								newangle[0] = -(newangle[0] + 180.0f);
								newangle[1] = newangle[1] + 180.0f;
							}
							wpm(PVOID(0x12345), 8, &newangle);
						}
						if (!angleshack)
						{
							wpm(PVOID(engine_dll_base + 0x395418 - enginedelta), 8, &newangle);
						}
					}
				}
			}

			if (cheat("No Recoil & No Spread") == 1)
			{
				if (tWnd == GetForegroundWindow() && GetAsyncKeyState(VK_LBUTTON) < 0)
				{
					if (aiming)
					{
						//readaimang
						myang[0] = newangle[0];
						myang[1] = newangle[1];
					}
					else
						rvm(PVOID(0x24000000 + 0x3FD54C), 8, &myang); //readvisang

					if (cheat("Spinbot & AntiAim") == 2) //metka2
					{
						myang[0] = -(myang[0] + 180.0f);
						myang[1] = myang[1] + 180.0f;
					}

					//read punch
					punchptr = rpm(0x24000000 + 0x3FB2F0);
					rvm(PVOID(punchptr + 0xBB0), 8, &punch);

					//read sequence
					rvm(PVOID(engine_dll_base + 0x3953c0 - enginedelta), 4, &ecx);
					rvm(PVOID(engine_dll_base + 0x3953bc - enginedelta), 4, &eax);
					randomseed = MD5_PseudoRandom(ecx + eax + 1) & 0x7FFFFFFF;
					randomseed &= 255;

					RandomSeed(randomseed + 1);
					xx = RandomFloat(-0.5f, 0.5f) + RandomFloat(-0.5f, 0.5f);
					yy = RandomFloat(-0.5f, 0.5f) + RandomFloat(-0.5f, 0.5f);

					if (cheat("Spinbot & AntiAim") != 2)
					{
						newangg[0] = myang[0] + (yy * 1.9f) - punch[0] * 1.9f;
						newangg[1] = myang[1] + (xx * 1.9f) - punch[1] * 1.9f;
					}
					else
					{
						newangg[0] = myang[0] + (yy * 1.9f) - punch[0] * 1.9f;
						newangg[1] = myang[1] - (xx * 1.9f) - punch[1] * 1.9f;
					}

					if (newangg[0] > 180.0f) newangg[0] -= 360.0f;
					if (newangg[0] < -180.0f) newangg[0] += 360.0f;
					if (newangg[1] > 180.0f) newangg[1] -= 360.0f;
					if (newangg[1] < -180.0f) newangg[1] += 360.0f;

					wpm(PVOID(0x12345), 8, &newangg);

					//fire
					wpm((LPVOID)0x243E71D8, 1, &six);

					Sleep(40);
				}
			}

			if (GetAsyncKeyState(VK_LBUTTON) < 0 && cheat("No Recoil & No Spread") != 1 && cheat("Spinbot & AntiAim") != 0 
				|| GetAsyncKeyState(VK_LBUTTON) < 0 && cheat("No Recoil & No Spread") != 1 && cheat("Silent FastLadder") != 0
				)
			{
				if (!aiming)
				{
					rvm(PVOID(0x24000000 + 0x3FD54C), 8, &myang);
					if (cheat("Spinbot & AntiAim") == 2) //metka3
					{
						myang[0] = -(myang[0] + 180.0f);
						myang[1] = myang[1] + 180.0f;
					}
					else
					{
						if (cheat("No Recoil & No Spread") != 2)
						{
							//read punch
							punchptr = rpm(0x24000000 + 0x3FB2F0);
							rvm(PVOID(punchptr + 0xBB0), 8, &punch);
							myang[0] = myang[0] - punch[0];
							myang[1] = myang[1] - punch[1];
						}
						
					}
				}
				else
				{
					
					myang[0] = newangle[0];
					myang[1] = newangle[1];

				}
				wpm(PVOID(0x12345), 8, &myang);

			}

			if (cheat("No Recoil & No Spread") == 2 )
			{
				wpm(engine_dll_base + 0x51f794 - enginedelta, 1);
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, 2.0f);
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 200.0f); //host_framerate

				//set sequence
				wpm(engine_dll_base + 0x3953bc - enginedelta, 0x6e);
				wpm(engine_dll_base + 0x3953c0 - enginedelta, 6);

				//fire
				wpm((LPVOID)0x243E71D8, 1, &six);

				Sleep(5);

				wpm(engine_dll_base + 0x51f794 - enginedelta, 0);
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, 1.0f);
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 0.0f); //host_framerate
				Sleep(10); 
			}
			aiming = 0;

			Sleep(5);
		}
		Sleep(1);
	}
}


void noSmokeFlash() {
	if (cheat("No Smoke & No Flash") == 1) {
		wpm(0x24000000 + 0x3E9C34, 0); //r_drawparticles 0
		SpyInjectAndJump(NoSmoke, PVOID(0x24000000+0x8E4F3), 0);
		BYTE twobytes[] = { 0x90, 0xE9 };
		wpm(PVOID(0x24000000 + 0x1D1D5D), 2, &twobytes);
	}
	if (cheat("No Smoke & No Flash") == 0) {
		wpm(0x24000000 + 0x3E9C34, 1); //r_drawparticles 1
		BYTE twobytes[] = { 0x0F, 0x8B };
		wpm(PVOID(0x24000000 + 0x1D1D5D), 2, &twobytes);
		BYTE fivebytes[] = { 0x8B, 0x01, 0xFF, 0x50, 0x04 };
		wpm(PVOID(0x24000000 + 0x8E4F3), sizeof(fivebytes), &fivebytes); 
	}
#ifdef DEBUG
	std::cout << "NoSmoke & NoFlash triggered\n";
#endif
}

void noHandsSky() {
	if (cheat("No Hands & No Sky") == 1) {
		wpm(0x24000000 + 0x3EEDFC, 0);
		wpm(0x24000000 + 0x3EE78C, 1);

		SpyInjectAndJump(NoHands, PVOID(materialsystem_dll_base + 0x1D193), 1); 
	}

	if (cheat("No Hands & No Sky") == 0) {
		wpm(0x24000000 + 0x3EEDFC, 1);
		wpm(0x24000000 + 0x3EE78C, 0);

		BYTE sixbytes[] = { 0x8B, 0x41, 0x0C, 0x83, 0xC4, 0x08 };
		wpm(PVOID(materialsystem_dll_base + 0x1D193), sizeof(sixbytes), &sixbytes); 
	}
}


bool WorldToScreen(float viewmatrix[][4], float coords[], float *x, float *y, float *w) {

	*x = viewmatrix[0][0] * coords[0] + viewmatrix[0][1] * coords[1] + viewmatrix[0][2] * coords[2] + viewmatrix[0][3];
	*y = viewmatrix[1][0] * coords[0] + viewmatrix[1][1] * coords[1] + viewmatrix[1][2] * coords[2] + viewmatrix[1][3];
	*w = viewmatrix[3][0] * coords[0] + viewmatrix[3][1] * coords[1] + viewmatrix[3][2] * coords[2] + viewmatrix[3][3];

	if (*w < 0.1f)
		return false;

	*x = *x / *w;
	*y = *y / *w;

	*x = (Width / 2 * *x) + (*x + Width / 2);
	*y = -(Height / 2 * *y) + (*y + Height / 2);

	return 1;
}

void timer() {
	float c4timer = rpm(0x22000000 + 0x5A4A7C);
#ifdef DEBUG
	printf("c4timer = %f\n", c4timer);
#endif
	chrono::system_clock::time_point mStartedTime = chrono::system_clock::now();
	for (;; Sleep(10)) {
		chrono::system_clock::time_point mElapsedTime = chrono::system_clock::now();
		std::chrono::duration<float> diff = mElapsedTime - mStartedTime;
		bomb = c4timer - diff.count();
		xd = 5.60 * (bomb * 100 / c4timer);
		if (!bombplanted) break;
	}
	bomb = 0.00f;
	xd = 0;
}

void Tab() {
	wchar_t shield[3] = L"\U0001F6E1", cross[3] = L"\U0001F7A7", skull[3] = L"\u2620", gun[3] = L"\U0001F5E1", net[3] = L"\U0001F5B3", bomb[3] = L"\U0001f4a3", tool[3] = L"\U0001F6E0";

	int charsize;
	int maxplayers;
	
	rvm(PVOID(engine_dll_base + 0x366E74), 4, &maxplayers);
	if (maxplayers <= 32) charsize = 15; else charsize = 15 - (maxplayers - 32) / 10; 

	ID3DXFont* pFont;
	D3DXCreateFont(p_Device, charsize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);

	DWORD entityT;
	int ctcount, tcount, speccount;
	int cti = 0, ti = 0, si = 0, ui = 0, topT, alivet = 0, alivect = 0;
	int intbuf1, intbuf2; char charint[32]; byte bytebuf; WORD twobytebuf;
	D3DCOLOR colorT;
	
	int topoffset = (64 - maxplayers) * 4;
	DrawFilledRectangle(305 - border, 20 + topoffset, 310 + (charsize*117.6) / 2 + border, 70 + border + (4 + maxplayers)*charsize + topoffset, colorprim ); 
	DrawFilledRectangle(305, 50 + topoffset, 310 + (charsize*117.6) / 2, 70 + (4 + maxplayers)*charsize + topoffset, colorsec ); 

	char hostname[64] = ""; char towrite[256] = "";
	rvm(PVOID(rpm(rpm(rpm(0x24000000 + 0x403430) + 0x18) + 0x20) + 0xC), 63, &hostname);
	
	strcat_s(towrite, hostname);
	strcat_s(towrite, " | ");
	rvm(PVOID(engine_dll_base + 0x3909C4 - enginedelta), 21, &hostname);
	strcat_s(towrite, hostname);
	strcat_s(towrite, " | ");
	rvm(PVOID(engine_dll_base + 0x390B41 - enginedelta), 21, &hostname);
	strcat_s(towrite, hostname);
	strcat_s(towrite, " | ");
	itoa(playerscount, charint, 10);
	strcat_s(towrite, charint);
	charint[0] = 0x0;
	strcat_s(towrite, "/");
	itoa(maxplayers, charint, 10);
	strcat_s(towrite, charint);
	charint[0] = 0x0;
	RECT FontPos{ 305,27 + topoffset,310 + (charsize*117.6) / 2,40 + topoffset };

	// UTF8 to UTF16
	intbuf1 = MultiByteToWideChar(CP_UTF8, 0, towrite, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[intbuf1];
	MultiByteToWideChar(CP_UTF8, 0, towrite, -1, wstr, intbuf1);
	pFont->DrawTextW(0, wstr, intbuf1, &FontPos, DT_CENTER, D3DCOLOR_XRGB(10, 45, 41));
	delete[] wstr;

	rvm(PVOID(rpm(rpm(0x24000000 + 0x3BDE14) + 0x8) + 0x46C ), 4, &tcount);
	rvm(PVOID(rpm(rpm(0x24000000 + 0x3BDE14) + 0xC) + 0x46C), 4, &ctcount);
	rvm(PVOID(rpm(rpm(0x24000000 + 0x3BDE14) + 0x4) + 0x46C), 4, &speccount);

	byte hasbomb = 0;
	rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0x12A0), 1, &hasbomb); 

	wpm(rpm(rpm(rpm(0x24000000 + 0x3E1A54) + 0x44) + 0x168) - 0x6d66, 6); //close showscores

	//Sort by kills
	vector<PlayerScore> CT, T;
	for (int i = 0; i < maxplayers; i++)
	{
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xF91 + i), 1, &bytebuf); //isconnected
		if (bytebuf == 0) continue;
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xFD8 + 4 * i), 4, &intbuf1); 
		if (intbuf1 == 1 || intbuf1 == 0) continue;
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xD8c + 4 * i), 4, &intbuf2);

		PlayerScore f;
		f.id = i;
		f.kills = intbuf2;
		if (intbuf1 == 3)
			CT.push_back(f);
		else
			T.push_back(f);
	}
	sort(CT.begin(), CT.end(), compareKills );
	for (int i = 0; i < CT.size(); i++)
		CT.at(i).place = i;
	sort(CT.begin(), CT.end(), compareID);

	sort(T.begin(), T.end(), compareKills);
	for (int i = 0; i < T.size(); i++)
		T.at(i).place = i;
	sort(T.begin(), T.end(), compareID);

	for (int i = 0; i < maxplayers; i++) {
		entityT = rpm(0x24000000 + 0x3CF214 + 8 * i);

		//STEAMID
		intbuf2 = rpm(rpm(engine_dll_base + 0x3958C8) + 0x38);
		if (enginedelta)
			rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958A8) + 0x38) + 0x24) + 0x14 + (0x28 * i)) + 0x24), 32, &charint);
		else
			rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958C8) + 0x38) + 0x24) + 0x14 + (0x28 * i)) + 0x24), 32, &charint);
		if ((int)charint[0] == 0x0) continue;

		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xF91 + i), 1, &bytebuf); //isConnected
		if (bytebuf != 0) 
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xFD8 + 4 * i), 4, &intbuf1); //TEAM
		else intbuf1 = 0;
		
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0x10d9 + i), 1, &bytebuf); //isAlive

		switch (intbuf1) {
		case(0): //unassigned
			colorT = D3DCOLOR_XRGB(255, 255, 255);
			topT = 55 + topoffset + (ctcount + tcount + speccount + ui + 4) * charsize;
			ui++;
			break;
		case(1): //spec
			colorT = D3DCOLOR_XRGB(255, 255, 255);
			topT = 55 + topoffset + (ctcount + tcount + si + 3) * charsize;
			si++;
			break;
		case(2): //t
			if (bytebuf) //alive
			{
				colorT = D3DCOLOR_XRGB(255, 125, 0);
				alivet++;
			}
			else
				colorT = D3DCOLOR_XRGB(255, 0, 0);

			if (ti < T.size()) 
				topT = 55 + topoffset + (ctcount + T.at(ti).place + 2) * charsize;
			else 
				topT = 55 + topoffset + (ctcount + ti + 2) * charsize;
			ti++;
			break;
		case(3): //ct
			if (bytebuf) { //alive
				colorT = D3DCOLOR_XRGB(0, 255, 255);
				alivect++;
			}
			else
				colorT = D3DCOLOR_XRGB(125, 125, 255); 

			if (cti < CT.size())
				topT = 55 + topoffset + (CT.at(cti).place + 1) * charsize;
			else 
				topT = 55 + topoffset + (cti + 1) * charsize;
			
			cti++;
			break;
		}
		rvm(PVOID(0x24000000 + 0x39D4FC), 1, &myid);
		if (i + 1 == (int)myid)
			colorT = D3DCOLOR_XRGB(255, 255, 0);

		//STEAMID
		DrawString((char*)charint, 310 + (charsize * 89.6) / 2, topT, colorT, pFont);
		charint[0] = 0x0;

		//ID
		itoa(i + 1, charint, 10);
		DrawString((char*)charint, 310, topT, colorT, pFont);
		charint[0] = 0x0;

		//NAME
		rvm(PVOID(ptr + offset - 0x138 + i * PLRSZ), 32, &charint);
		// UTF8 to UTF16
		intbuf1 = MultiByteToWideChar(CP_UTF8, 0, charint, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[intbuf1];
		MultiByteToWideChar(CP_UTF8, 0, charint, -1, wstr, intbuf1);
		DrawStringW(wstr, 330, topT, intbuf1, colorT, pFont);
		delete[] wstr;

		if (i+1 == hasbomb)
			DrawStringW(bomb, 310 + (charsize * 32) / 2, topT, 2, colorT, pFont); //BOMB 

		if (rpm(entityT + 0x1020))
			DrawStringW(tool, 310 + (charsize * 32) / 2, topT, 2, colorT, pFont); //DEFUSER 

		//KILLS
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xD8c + 4 * i), 4, &intbuf1);
		itoa(intbuf1, charint, 10);
		DrawStringW(gun, 310 + (charsize * 35) / 2, topT, 2, colorT, pFont); //KNIFE 
		DrawString((char*)charint, 310 + (charsize * 37.5) / 2, topT, colorT, pFont);
		charint[0] = 0x0;

		//DEATHS
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xE90 + 4 * i), 4, &intbuf2);
		itoa(intbuf2, charint, 10);
		DrawStringW(skull, 310 + (charsize * 42.5) / 2, topT, 2, colorT, pFont); //SKULL 
		DrawString((char*)charint, 310 + (charsize * 45) / 2, topT, colorT, pFont);
		charint[0] = 0x0;

		//K/D RATIO
		if (intbuf2 == 0) intbuf2 = 1;
		DrawString((char*)(std::to_string((float)intbuf1 / (float)intbuf2).c_str()), 310 + (charsize * 50) / 2, topT, 4, colorT, pFont);

		//HP
		DrawStringW(cross, 310 + (charsize * 55) / 2, topT, 2, colorT, pFont); //CROSS
		rvm(PVOID(ptr + offset - 0x114 + i * PLRSZ), 4, &intbuf2);
		itoa(intbuf2, charint, 10);
		DrawString((char*)charint, 310 + (charsize * 56.8) / 2, topT, colorT, pFont);
		charint[0] = 0x0;

		if (entityT) {
			//ARMOR
			rvm(PVOID(entityT + 0x1010), 4, &intbuf1);
			itoa(intbuf1, charint, 10);
			DrawStringW(shield, 310 + (charsize * 60.8) / 2, topT, 2, colorT, pFont); //SHIELD 
			DrawString((char*)charint, 310 + (charsize*62.6) / 2, topT, colorT, pFont);
			charint[0] = 0x0;

			//MONEY
			DrawString((char*)"$", 310 + (charsize*66.6) / 2 , topT, colorT, pFont); 
			rvm(PVOID(entityT + 0x1004), 4, &intbuf1);
			itoa(intbuf1, charint, 10);
			DrawString((char*)charint, 310 + (charsize * 67.6) / 2, topT, colorT, pFont);
			charint[0] = 0x0;

			//WEAPON
			if (bytebuf) { //if Alive
				rvm(PVOID(entityT + 0xB30), 2, &twobytebuf);
				twobytebuf &= 0x0FFF;
				rvm(PVOID(rpm(rpm(rpm(rpm(0x24000000 + 0x3CF20C + 8 * twobytebuf)) - 0x4) - 0x8) + 0xE), 24, &charint);
				for (int i = 0; i < 24; i++)
				{
					if (charint[i] == 0x40)
						charint[i] = 0x0;
				}
				DrawString((char*)charint, 310 + (charsize*73.6) / 2, topT, colorT, pFont);
				charint[0] = 0x0;
			}
		}

		//PING
		DrawStringW(net, 310 + (charsize * 110.6) / 2, topT, 2, colorT, pFont); //COMPUTER 
		rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xC88 + 4 * i), 4, &intbuf1); 
		itoa(intbuf1, charint, 10);
		DrawString((char*)charint, 310 + (charsize * 112.6) / 2, topT, colorT, pFont);
		charint[0] = 0x0;

	}
	playerscount = ctcount + tcount + speccount + ui;

	rvm(PVOID(rpm(rpm(0x24000000 + 0x3BDE14) + 0xC) + 0x494), 4, &intbuf1); //ctwins
	rvm(PVOID(rpm(rpm(0x24000000 + 0x3BDE14) + 0x8) + 0x494), 4, &intbuf2); //twins

	//Counter-Terrorists | %alivect of %ctcount alive | %ct score
	char towriteCT[256] = "Counter-Terrorists | ";
	itoa(alivect, charint, 10);
	strcat_s(towriteCT, charint);
	charint[0] = 0x0;
	strcat_s(towriteCT, " of ");
	itoa(ctcount, charint, 10);
	strcat_s(towriteCT, charint);
	charint[0] = 0x0;
	strcat_s(towriteCT, " alive | ");
	itoa(intbuf1, charint, 10);
	strcat_s(towriteCT, charint);
	charint[0] = 0x0;
	strcat_s(towriteCT, " score");
	DrawString((char*)towriteCT, 310, topoffset + 55, D3DCOLOR_XRGB(0, 255, 255), pFont);
	
	char towriteT[256] = "Terrorists | ";
	itoa(alivet, charint, 10);
	strcat_s(towriteT, charint);
	charint[0] = 0x0;
	strcat_s(towriteT, " of ");
	itoa(tcount, charint, 10);
	strcat_s(towriteT, charint);
	charint[0] = 0x0;
	strcat_s(towriteT, " alive | ");
	itoa(intbuf2, charint, 10);
	strcat_s(towriteT, charint);
	charint[0] = 0x0;
	strcat_s(towriteT, " score");
	DrawString((char*)towriteT, 310, topoffset + 55 + (ctcount + 1)*charsize, D3DCOLOR_XRGB(255, 125, 0), pFont);

	char towriteS[256] = "Spectators | ";
	itoa(speccount, charint, 10);
	strcat_s(towriteS, charint);
	charint[0] = 0x0;
	strcat_s(towriteS, " players");
	DrawString((char*)towriteS, 310, topoffset + 55 + (ctcount + tcount + 2) * charsize, D3DCOLOR_XRGB(255, 255, 255), pFont);

	char towriteU[256] = "Unassigned | ";
	itoa(ui, charint, 10);
	strcat_s(towriteU, charint);
	charint[0] = 0x0;
	strcat_s(towriteU, " players");
	DrawString((char*)towriteU, 310, topoffset + 55 + (ctcount + tcount + speccount + 3) * charsize, D3DCOLOR_XRGB(255, 255, 255), pFont);

	pFont->Release();
}

void myDraw() {

		menu();
		if (!rpm(vguimatsurface_dll_base + 0xB4274)) //0xB10F8
		{
			
			if (cheat("Radarhack") == 2) {
				rvm(PVOID(0x24000000 + 0x3BA3C0), 4, &radarhackptr);
				if (radarhackptr)
					wpm(PVOID(radarhackptr + 0x13D8), 64, &sf);
			}

			if (cheat("Radarhack") == 1) {
				sprite->Begin(D3DXSPRITE_ALPHABLEND);
				sprite->Draw(tex, NULL, NULL, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
				sprite->End();
			}

			if (cheat("Aimbot").enabled > 0) {
				aimfov = cheat("Aimbot FOV").enabled * 5;
				DrawCircle(Width / 2, Height / 2, aimfov, 0, 360, D3DCOLOR_ARGB(50, 255, 255, 0));
			}

			rvm(PVOID(0x24000000 + 0x3B51C4), 4, &localplayer);
			rvm(PVOID(localplayer + 0x90), 1, &myteam);

			if (myteam == 2) myteam = 64;
			if (myteam == 3) myteam = 255;

			if (cheat("Triggerbot & Crosshair").enabled >= 1) {
				wpm(0x22000000 + 0x5A4764, 1); //mp_playerid = 1
				rvm(PVOID(0x243E7208), 1, &who);
				switch (who)
				{
				case 1:
					color = D3DCOLOR_ARGB(100, 0, 255, 0);
					break;
				case 2:
					color = D3DCOLOR_ARGB(100, 255, 0, 0);
					break;
				default:
					color = D3DCOLOR_ARGB(100, 0, 0, 255);
					break;
				}

				wpm((LPVOID)0x243E7208, 1, &zero);

				scrCenterX = Width / 2;
				scrCenterY = Height / 2;

				D3DRECT rect1 = { scrCenterX - 13,  scrCenterY - 2,  scrCenterX + 13, scrCenterY + 2 };
				D3DRECT rect2 = { scrCenterX - 2,  scrCenterY - 13,  scrCenterX + 2, scrCenterY + 13 };

				IDirect3DDevice9_Clear(p_Device, 1, &rect1, D3DCLEAR_TARGET, color, 0, 0);
				IDirect3DDevice9_Clear(p_Device, 1, &rect2, D3DCLEAR_TARGET, color, 0, 0);
			}

			if (cheat("Aimbot").enabled > 0 || cheat("Radarhack").enabled == 1 || cheat("ESP").enabled > 0 || cheat("Serverinfo & Bombtimer") == 1)
			{
				rvm(PVOID(0x24000000 + 0x3FD5C4), 4, &myposX);
				rvm(PVOID(0x24000000 + 0x3EE0C8), 4, &myposY);
				rvm(PVOID(0x24000000 + 0x3FD550), 4, &myangY);

				rvm(PVOID(0x24000000 + 0x3FD5CC), 4, &myposZ);

				myangY -= 90;

				yl_closest = 1000; xl_closest = 1000;

				char charint[32]; int intbuf; WORD shintbuf; byte bytebuf;

				if (cheat("ESP") == 3) {
					ID3DXFont* pFont;
					D3DXCreateFont(p_Device, 12, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
					color = D3DCOLOR_XRGB(255, 255, 255);
					offs = 0;

					maxentityid = rpm(0x24000000 + 0x3CF208);
					for (i = 0; i <= maxentityid; i++)
					{
						rvm(PVOID(0x24000000 + 0x3BF1D4 + 0x10 * i), 4, &boneptr);
						rvm(PVOID(boneptr + 0x4A8), 4, &boneptr);
						rvm(PVOID(boneptr + 0x0c), 4, &coords[0]);
						rvm(PVOID(boneptr + 0x1c), 4, &coords[1]);
						rvm(PVOID(boneptr + 0x2c), 4, &coords[2]);

						if (WorldToScreen(viewmatrix, coords, &xl, &yl, &wl)) {

							ss << hex << i;
							s = ss.str();

							entity = rpm(0x24000000 + 0x3CF20C + 8 * i);
							entity = rpm(entity);
							entity = rpm(entity - 0x4);
							entity = rpm(entity - 0x8);
							charint[0] = 0x0;
							rvm(PVOID(entity + 0x8), 24, &charint);

							if ((char*)charint[0] == 0x0) //Unknown entity
							{
								ss.str("");
								continue;
							}
							s += ": ";

							if (abs(prevX - xl) < 5 && abs(prevY - yl) < 5)
							{
								DrawString(cstr, xl, yl + offs * 10, color, pFont);
								DrawString((char*)(charint), xl + 20, yl + offs * 10, color, pFont);
								offs++;
							}
							else
							{
								DrawString(cstr, xl, yl, color, pFont);
								DrawString((char*)(charint), xl + 20, yl, color, pFont);
							}

							prevX = xl; prevY = yl;
							ss.str("");

						}
					}
					pFont->Release();
				}
				for (i = 0; i < 64; i++)
				{
					rvm(PVOID(0x24000000 + 0x39D4FC), 1, &myid);
					if (i + 1 == (int)myid)
						continue;

					entity = rpm(0x24000000 + 0x3CF214 + 8 * i);

					if (cheat("Aimbot") != 2) {
						//rvm((PVOID)(ptr + 0x118 + i * 0x140), 12, &coords);
						rvm((PVOID)(entity + 0x1CC), 12, &coords);
						coords[2] = coords[2] + 65;
					}
					else {
						rvm(PVOID(0x24000000 + 0x3BF1E4 + 0x10 * i ), 4, &boneptr);
						rvm(PVOID(boneptr + 0x4A8), 4, &boneptr);
						rvm(PVOID(boneptr + 0x0c + 0x2A0), 4, &coords[0]);
						rvm(PVOID(boneptr + 0x1c + 0x2A0), 4, &coords[1]);
						rvm(PVOID(boneptr + 0x2c + 0x2A0), 4, &coords[2]);
						coords[2] = coords[2] + 1;
					}

					rvm((PVOID)(ptr + 0x118 + i * 0x140), 12, &radarcoords);
					rvm(PVOID(ptr + offset - 0x114 + i * PLRSZ), 4, &hp);
					rvm(PVOID(ptr + offset - 0x13A + i * PLRSZ), 1, &team);

					rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0x10d9 + i), 1, &bytebuf); //isAlive
					if (radarcoords[0] != 0 && bytebuf) { 
						//Radar trigonometry
						deltaX = myposX - radarcoords[0];
						deltaY = myposY - radarcoords[1];

						deltaZ = myposZ - coords[2];

						deltaXold = deltaX; deltaYold = deltaY;

						deltaX = deltaXold * cos(myangY * PI / 180) + deltaYold * sin(myangY* PI / 180);
						deltaY = -deltaXold * sin(myangY* PI / 180) + deltaYold * cos(myangY* PI / 180);

						if (sqrtss(pow(deltaX, 2) + pow(deltaY, 2)) > 1500) {
							float k = 1500 / sqrtss(pow(deltaX, 2) + pow(deltaY, 2));
							deltaX = k * deltaX;
							deltaY = k * deltaY;
						}

						if (cheat("Radarhack") == 1) {
							if ((int)team == (int)myteam)
								color = D3DCOLOR_ARGB(255, 0, 255, 0);
							else
								color = D3DCOLOR_ARGB(255, 255, 0, 0);
							DrawFilledRectangle(-fi * deltaX + 147 - 3, fi*deltaY + 147 - 3, -fi * deltaX + 147 + 3, fi*deltaY + 147 + 3, color);
						}

						rvm(PVOID(vmatrixptr + 0x5a0), 4, &flickerCheck);
						if (flickerCheck <= -1.0f)
							rvm(PVOID(vmatrixptr + 0x5B4), 64, &viewmatrix);

						//get3Ddist
						enemyDistance = sqrtss(deltaXold*deltaXold + deltaYold * deltaYold + deltaZ * deltaZ);

						
						rvm(PVOID(entity + 0x138), 1, &bDormant);

						if ((int)team == (int)myteam)
							color = D3DCOLOR_ARGB(255, 0, 255, 0);
						else color = D3DCOLOR_ARGB(255, 255, 0, 0);

						if (entity && !bDormant && WorldToScreen(viewmatrix, coords, &xl, &yl, &wl)) {
							if (cheat("ESP") == 1 || cheat("ESP") == 2)
							{
								DrawBorderBox(xl - 10000 / enemyDistance, yl - 10, 20000 / enemyDistance, 40000 / enemyDistance, 3, color);
								DrawFilledRectangle(
									xl - 10000 / enemyDistance,
									yl - 16,
									xl - (10000 / enemyDistance) + (20000 / enemyDistance / 100 * hp) + 3,
									yl - 13,
									D3DCOLOR_XRGB(255, 255, 255));
							}

							if (cheat("ESP") == 2)
							{
								color = D3DCOLOR_XRGB(255, 255, 255);
								ID3DXFont* pFont;
								D3DXCreateFont(p_Device, 12, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
								itoa(i + 1, charint, 10);
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 0, color, pFont); 
								charint[20] = 0x0;

								rvm(PVOID(ptr + offset - 0x138 + i * PLRSZ), 32, &charint);
								intbuf = MultiByteToWideChar(CP_UTF8, 0, charint, -1, NULL, 0);
								wchar_t* wstr = new wchar_t[intbuf];
								MultiByteToWideChar(CP_UTF8, 0, charint, -1, wstr, intbuf);
								DrawStringW(wstr, xl - 10000 / enemyDistance + 20000 / enemyDistance + 21, yl - 6 + 12 * 0, intbuf, color, pFont);
								delete[] wstr;
								charint[20] = 0x0;

								itoa(hp, charint, 10);
								DrawString((char*)"H", xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 1, color, pFont);
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 14, yl - 6 + 12 * 1, color, pFont);
								charint[0] = 0x0;

								rvm(PVOID(entity + 0xA4C + 0x5c4), 4, &intbuf);
								itoa(intbuf, charint, 10);
								DrawString((char*)"A", xl - 10000 / enemyDistance + 20000 / enemyDistance + 38, yl - 6 + 12 * 1, color, pFont);
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 45, yl - 6 + 12 * 1, color, pFont);
								charint[0] = 0x0;

								if (enginedelta)
									rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958A8) + 0x38) + 0x24) + 0x14 + (0x28 * i)) + 0x24), 32, &charint);
								else
									rvm(PVOID(rpm(rpm(rpm(rpm(engine_dll_base + 0x3958C8) + 0x38) + 0x24) + 0x14 + (0x28 * i)) + 0x24), 32, &charint);
								
								charint[20] = 0x0;
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 2, color, pFont);
								charint[0] = 0x0;

								rvm(PVOID(entity + 0x1004), 4, &intbuf);
								itoa(intbuf, charint, 10);
								DrawString((char*)"$", xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 3, color, pFont);
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 13, yl - 6 + 12 * 3, color, pFont);
								charint[0] = 0x0;

								rvm(PVOID(rpm(0x24000000 + 0x3BA3C0) + 0xC88 + 4*i), 4, &intbuf);
								itoa(intbuf, charint, 10);
								DrawString((char*)"ping: ", xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 5, color, pFont);
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 35, yl - 6 + 12 * 5, color, pFont);
								charint[0] = 0x0;

								rvm(PVOID(entity + 0xB30), 2, &shintbuf);
								shintbuf &= 0x0FFF;
								rvm(PVOID(rpm(rpm(rpm(rpm(0x24000000 + 0x3CF20C + 8 * shintbuf)) - 0x4) - 0x8) + 0xE), 24, &charint);
								for (int i = 0; i < 24; i++)
								{
									if (charint[i] == 0x40)
										charint[i] = 0x0;
								}
								DrawString((char*)charint, xl - 10000 / enemyDistance + 20000 / enemyDistance + 7, yl - 6 + 12 * 4, color, pFont);
								charint[0] = 0x0;

								pFont->Release();
							}
							//Calculate target that closest to the crosshair
							if (cheat("Aimbot").enabled > 0 && (int)team != (int)myteam)
							{
								hyp1 = sqrtss((xl - Width / 2) * (xl - Width / 2) + (yl - Height / 2) * (yl - Height / 2));
								hyp2 = sqrtss((xl_closest - Width / 2) * (xl_closest - Width / 2) + (yl_closest - Height / 2) * (yl_closest - Height / 2));

								if (hyp1 < hyp2 && hyp1 < aimfov)
								{
									xl_closest = xl;
									yl_closest = yl;
									closest = i;
								}
							}
						}
					}
				}

				if (xl_closest != 1000) {
					xl_closest_final = xl_closest;
					yl_closest_final = yl_closest;
					closest_final = closest;
				}
				else
				{
					xl_closest_final = 0 + Width / 2;
					yl_closest_final = 0 + Height / 2;
					closest_final = -2;
				}

				if (cheat("Serverinfo & Bombtimer") == 1)
				{
					bombplanted = rpm(0x24000000 + 0x3FAB68); //we have a bomb?
					if (bombplanted) 
					{
						if (!xd) 
						{
							CreateThread(0, 0, (LPTHREAD_START_ROUTINE)timer, 0, 0, 0);
							rvm(PVOID(0x24000000 + 0x3BF1D4 + 0x10 * i), 4, &boneptr);
							rvm(PVOID(boneptr + 0x4A8), 4, &boneptr);
							rvm(PVOID(boneptr + 0x0c), 4, &bombcoords[0]);
							rvm(PVOID(boneptr + 0x1c), 4, &bombcoords[1]);
						}
						if (bomb > 0) {
							ID3DXFont* pFont;
							D3DXCreateFont(p_Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
							DrawBorderBox(Width / 2 - 280 - border, Height / 2 + 300 - border, 565, 40 + border, border, colorprim);
							DrawFilledRectangle(Width / 2 - 280, Height / 2 + 300, Width / 2 - 280 + xd, Height / 2 + 340, colorsec);
							DrawString((char*)(std::to_string(bomb).c_str()), Width / 2 - 5, Height / 2 + 310, 4, D3DCOLOR_XRGB(255, 255, 255), pFont);
							pFont->Release();
						}
					}
				}
				
					if (cheat("Radarhack") == 1)
					{
						radar3ptr = rpm(0x24000000 + 0x4035c0);
						rvm(PVOID(radar3ptr + 0x63c4), 12, &bombcoords);

						deltaX = myposX - bombcoords[0];
						deltaY = myposY - bombcoords[1];

						deltaXold = deltaX; deltaYold = deltaY;

						deltaX = deltaXold * cos(myangY * PI / 180) + deltaYold * sin(myangY* PI / 180);
						deltaY = -deltaXold * sin(myangY* PI / 180) + deltaYold * cos(myangY* PI / 180);

						if (sqrtss(pow(deltaX, 2) + pow(deltaY, 2)) > 1500) {
							float k = 1500 / sqrtss(pow(deltaX, 2) + pow(deltaY, 2));
							deltaX = k * deltaX;
							deltaY = k * deltaY;
						}

						DrawFilledRectangle(144, 144, 151, 151, 100, 0, 255, 255); //white square on the center of the radar
						DrawFilledRectangle(-fi * deltaX + 147 - 3, fi*deltaY + 147 - 3, -fi * deltaX + 147 + 3, fi*deltaY + 147 + 3, D3DCOLOR_XRGB(200, 200, 200));
					}
			} //esp,radar,aim enabled?
			if (cheat("Serverinfo & Bombtimer") == 1 && GetAsyncKeyState(VK_TAB) < 0)
				Tab();
			
		} //not in menu? 
		if (rpm(engine_dll_base + 0x53B55C - enginedelta)) //in server ?
		{
			if (angleshack)
				wpm(rpm(0x24000000 + 0x3EA8C0), 0x00000031); //vispredict
		}
		else
		{
			cheat("Inputfromfile & Loopback") = 0;
			if (angleshack)
				wpm(rpm(0x24000000 + 0x3EA8C0), 0x00000030); //vispredict
		}
}


void visnrec(bool d) {
	if (d)
	{
		wvm(LPVOID(0x24000000 + 0x192d2 + 0x2), sizeof(DWORD), 0);
		wvm(LPVOID(0x24000000 + 0x192dc + 0x2), sizeof(DWORD), 0);
		SendCMD("cl_predictweapons 0");
#ifdef DEBUG
		cout << "visual norecoil enabled\n";
#endif
	}
	else
	{
		wvm(PVOID(0x24000000 + 0x192d2 + 0x2), 4, 0X00000bb0);
		wvm(PVOID(0x24000000 + 0x192dc + 0x2), 4, 0X00000BB4);
#ifdef DEBUG
		cout << "visual norecoil disabled\n";
#endif
	}
}

void Angleshack(bool d) {
	if (d)
	{
		angleshack = 1;

		SpyJmp(PVOID(0x2415D32E), freevisangX, 0);
		SpyJmp(PVOID(0x2415D3A0), freevisangY, 0);
		SpyJmp(PVOID(0x2415D412), freevisangZ, 0);
		SpyJmp(PVOID(0x240D46F9), fixPredict, 7);

		//cl_predictweapons 1 kill
		wpm(0x24000000 + 0x1e2858, 0x83068b9090909090);

		SendCMD("cl_predictweapons 0");
#ifdef DEBUG
		cout << "angleshack enabled\n";
#endif
	}
	else
	{
		angleshack = 0;

		//freevisang revert
		wpm(0x2415D32E, 0xCE8B51106A0C4D8B);
		wpm(0x2415D3A0, 0xCE8B51106A104D8B);
		wpm(0x2415D412, 0xCE8B51086A144D8B);

		//predict revert
		wpm(0x240D46F9, 0x8B0C5089);
		wpm(0x240D46F9 + 4, 0x50891051);
		wpm(0x240D46F9 + 8, 0x14518b10);

		//set Z to 0 
		wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 0);

		//cl_predictweapons 1 back
		wpm(0x24000000 + 0x1e2858, 0x83068bFFFF2803E8);
#ifdef DEBUG
		cout << "angleshack disabled\n";
#endif
	}
}

void StopMoving() {
	wpm(0x24000000 + 0x3E7274, 0);
	wpm(0x24000000 + 0x3E7268, 0);
	wpm(0x24000000 + 0x3E725C, 0);
	wpm(0x24000000 + 0x3E7250, 0);
	SendCMD("-moveleft; -moveright; -forward; -back");
}


void TriggerCheck()
{
	float speed;

	float boostang = 40.0f; 
	int sleeptim = 30;

	while (true)
	{
		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			if (tWnd == GetForegroundWindow())
				wpm(0x12204, 1);
			if (cheat("Fake Lag") == 2)
				wpm(0x24000000 + 0x3E71E4, 4); //jump
		}
		else
		{
			wpm(0x12204, 0);
			if (cheat("Fake Lag") == 2)
				wpm(0x24000000 + 0x3E71E4, 5); //unjump
		}
		

		if (tWnd == GetForegroundWindow() && cheat("Bunnyhop & Autostrafe") == 1 && GetAsyncKeyState(VK_SPACE) < 0)
		{

			while (GetAsyncKeyState(VK_SPACE) < 0)
			{
				if (cheat("Spinbot & AntiAim") != 1) {
					if (boostsleep)
					{
						Sleep(300);
						boostsleep = 0;
					}
					wpm(0x24000000 + 0x3E7250, 0); //-moveright
					wpm(0x24000000 + 0x3E725C, 1); //+moveleft
					wpm(engine_dll_base + 0x39541c + 4 - enginedelta, boostang); //set z ang
					wpm(0x1234D, boostang);
					Sleep(sleeptim);
					wpm(0x24000000 + 0x3E725C, 0); //-moveleft
					wpm(0x24000000 + 0x3E7250, 1); //+moveright
					wpm(engine_dll_base + 0x39541c + 4 - enginedelta, -boostang); //set z ang
					wpm(0x1234D, -boostang);
					Sleep(sleeptim);
				}
				else
				{
					wpm(0x12330, 180.0f);
					Sleep(sleeptim);
				}

			}
			wpm(engine_dll_base + 0x39541c + 4 - enginedelta, 1.0f); //reset Z angle
			wpm(0x1234D, 0); //ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
			wpm(0x24000000 + 0x3E725C, 0); //-moveleft
			wpm(0x24000000 + 0x3E7250, 0); //-moveright
		}

		if (cheat("Speedhack").enabled != 10 && tWnd == GetForegroundWindow() && GetAsyncKeyState(0x12) < 0) //alt pressed
		{
			speed = (float)cheat("Speedhack").enabled / 10;
			wpm(engine_dll_base + 0x51f794 - enginedelta, 1);

			if (cheat("Speedhack").enabled != 100) {
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, speed);
				//wpm(engine_dll_base + 0x4D2860 - enginedelta, 300.0f / speed); //framerate = fps/timescale
			}
			else 
			{
				byte bytes2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
				wvm(PVOID(engine_dll_base + 0x426D9 + enginedelta), sizeof(bytes2), bytes2);
				wpm(engine_dll_base + 0x4D28F0 - enginedelta, 100.0f);
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 50.0f); //framerate
			}

			//waiting
			while (GetAsyncKeyState(0x12) < 0)
				Sleep(1);

			wpm(engine_dll_base + 0x51f794 - enginedelta, 0); //svcheats
			wpm(engine_dll_base + 0x4D28F0 - enginedelta, 1.0f); //timescale
			//wpm(engine_dll_base + 0x4D2860 - enginedelta, 0.0f); //framerate
			if (cheat("Speedhack").enabled == 100) {
				dword2bytes dw2b3 = { engine_dll_base + 0x3953C0 - enginedelta };
				dword2bytes dw2b4 = { engine_dll_base + 0x3953bc - enginedelta };
				byte bytes4[] = { 0xA3, dw2b4.bytes[0],dw2b4.bytes[1],dw2b4.bytes[2],dw2b4.bytes[3], 0xC7, 0x05, dw2b3.bytes[0],dw2b3.bytes[1],dw2b3.bytes[2],dw2b3.bytes[3], 0x00, 0x00, 0x00, 0x00 };
				wvm(PVOID(engine_dll_base + 0x426D9 + enginedelta), sizeof(bytes4), bytes4);
				wpm(engine_dll_base + 0x4D2860 - enginedelta, 0.0f); //framerate
			}
		}

		if (tWnd == GetForegroundWindow() && GetAsyncKeyState(0x46) < 0 && !rpm(vguimatsurface_dll_base + 0xB10F8)) { //F pressed & not in menu
			if (!fullbright)
			{
				fullbright = 1;
				wpm(engine_dll_base + 0x4F0C44 - enginedelta, 1);
			}
			else
			{
				fullbright = 0;
				wpm(engine_dll_base + 0x4F0C44 - enginedelta, 0);
			}
			Sleep(200);
		}

		if (cheat.Triggered("No Recoil & No Spread"))
		{
			cheat.Update("No Recoil & No Spread");

			if (cheat("No Recoil & No Spread") != 0)
				visnrec(1);
			else
				visnrec(0);

			if (cheat("No Recoil & No Spread") == 1)
				if (!angleshack)
					Angleshack(1);

			if (cheat("No Recoil & No Spread") != 1)
				if (cheat("Spinbot & AntiAim") == 0 && cheat("Silent FastLadder") == 0 && angleshack)
					Angleshack(0);
		}

		if (cheat.Triggered("Silent FastLadder"))
		{
			cheat.Update("Silent FastLadder");

			if (cheat("Silent FastLadder").enabled > 0)
				if (!angleshack)
					Angleshack(1);

			if (cheat("Silent FastLadder") == 0)
				if (cheat("Spinbot & AntiAim") == 0 && cheat("No Recoil & No Spread") != 1 && angleshack)
					Angleshack(0);
		}

		if (cheat.Triggered("Spinbot & AntiAim"))
		{
			cheat.Update("Spinbot & AntiAim");
			if (cheat("Spinbot & AntiAim").enabled > 0)
			{
				if (cheat("Spinbot & AntiAim") == 1) //SPINBOT
				{
					// a is moveleft
					wpm(0x243E797C + 0x18, 0x240F6CE0);
					wpm(0x243E79A0 + 0x18, 0x240F6CF0);
					// w is moveleft
					wpm(0x243E7814 + 0x18, 0x240F6CE0);
					wpm(0x243E7838 + 0x18, 0x240F6CF0);
					// d is moveleft
					wpm(0x243E79C4 + 0x18, 0x240F6CE0);
					wpm(0x243E79E8 + 0x18, 0x240F6CF0);
					// s is moveleft
					wpm(0x243E785C + 0x18, 0x240F6CE0);
					wpm(0x243E7880 + 0x18, 0x240F6CF0);
					StopMoving();
				}
				if (cheat("Spinbot & AntiAim") == 2) //UPSIDE-DOWN
				{
					// a is moveright
					wpm(0x243E797C + 0x18, 0x240F6D70);
					wpm(0x243E79A0 + 0x18, 0x240F6D80);
					// w is forward
					wpm(0x243E7814 + 0x18, 0x240F6AA0);
					wpm(0x243E7838 + 0x18, 0x240F6AB0);
					// d is moveleft
					wpm(0x243E79C4 + 0x18, 0x240F6CE0);
					wpm(0x243E79E8 + 0x18, 0x240F6CF0);
					// s is back
					wpm(0x243E785C + 0x18, 0x240F6B30);
					wpm(0x243E7880 + 0x18, 0x240F6B40);
					StopMoving();
				}
				if (cheat("Spinbot & AntiAim") == 3) //BACKWARDS
				{
					// a is moveright
					wpm(0x243E797C + 0x18, 0x240F6D70);
					wpm(0x243E79A0 + 0x18, 0x240F6D80);
					// w is back
					wpm(0x243E7814 + 0x18, 0x240F6B30);
					wpm(0x243E7838 + 0x18, 0x240F6B40);
					// d is moveleft
					wpm(0x243E79C4 + 0x18, 0x240F6CE0);
					wpm(0x243E79E8 + 0x18, 0x240F6CF0);
					// s is forward
					wpm(0x243E785C + 0x18, 0x240F6AA0);
					wpm(0x243E7880 + 0x18, 0x240F6AB0);
					StopMoving();
				}

				if (!angleshack)
					Angleshack(1);
				Sleep(50);
			}
			else //RESET
			{
				// a is moveleft
				wpm(0x243E797C + 0x18, 0x240F6CE0);
				wpm(0x243E79A0 + 0x18, 0x240F6CF0);
				// w is forward
				wpm(0x243E7814 + 0x18, 0x240F6AA0);
				wpm(0x243E7838 + 0x18, 0x240F6AB0);
				// d is moveright
				wpm(0x243E79C4 + 0x18, 0x240F6D70);
				wpm(0x243E79E8 + 0x18, 0x240F6D80);
				// s is back
				wpm(0x243E785C + 0x18, 0x240F6B30);
				wpm(0x243E7880 + 0x18, 0x240F6B40);
				StopMoving();
				if (cheat("No Recoil & No Spread") != 1 && cheat("Silent FastLadder") == 0)
					Angleshack(0);
			}
		}

		if (cheat.Triggered("Inputfromfile & Loopback"))
		{
			DWORD thisptr;
			rvm(PVOID(0x24000000 + 0x3EDD00), 4, &thisptr);
			if (cheat("Inputfromfile & Loopback") == 1) {
				wpm(PVOID(aobconsole), 1, &nop);
				wpm(PVOID(aobconsole + 1), 1, &nop);
				wpm(thisptr + 0xD7C, 1);
				SendCMD("voice_loopback 1; +voicerecord");
				Sleep(100); 
				byte bytes[] = { 0xF3, 0xA4 };
				wpm(PVOID(aobconsole), 2, &bytes);
			}
			else {
				wpm(thisptr + 0xD7C, 0x00000000);
				SendCMD("voice_loopback 0");
				SendCMD("-voicerecord");
			}
			cheat("Inputfromfile & Loopback").trigger = cheat("Inputfromfile & Loopback").enabled;
			cheat.Update("Inputfromfile & Loopback");
		}

		if (cheat.Triggered("Radarhack"))
		{
			cheat.Update("Radarhack");

			if (cheat("Radarhack") == 1)
				//radaralpha = 1
				wpm(0x24000000 + 0x3FF464, 1);
			else {
				//radaralpha = 255
				wpm(0x24000000 + 0x3FF464, 255);
			}

			if (cheat("Radarhack") == 0 || cheat("Radarhack") == 2)
			{
				wpm(spec1, 0x085E89);
				wpm(spec1 + 3, 0x90909090);

				wpm(0x24000000 + 0x257351, 0x5E5F1FD9);
				wpm(0x24000000 + 0x257351 + 4, 0x000CC2);

				radar3ptr = rpm(0x24000000 + 0x4035c0);
				wpm(radar3ptr + 0x8, 3); //radar type
				wpm(localplayer + 0xD80, 0); //spec type
			}

			if (cheat("Radarhack") == 3)
			{
				wpm(spec1, 0x0846C7);
				wpm(spec1 + 3, 0x00000001);

				SpyJmp(LPVOID(0x24000000 + 0x257351), LPVOID(spec2), 2);

				radar3ptr = rpm(0x24000000 + 0x3E1A44);
				radar3ptr = rpm(radar3ptr + 0x4);
				wpm(radar3ptr + 0x5348, 0x243E1A44); //map size

				radar3ptr = rpm(0x24000000 + 0x4035c0);
				wpm(radar3ptr + 0x8, 1); //radar type
				wpm(localplayer + 0xD80, 5); //spec type
			}
		}

		if (cheat.Triggered("Free Cam"))
		{
			cheat.Update("Free Cam");
			if (cheat("Free Cam") == 1)
			{
				byte dontmove[] = { 0x90, 0x90, 0x90 };
				wpm(PVOID(0x24000000 + 0xF657C), 3, &dontmove);

				SpyJmp(LPVOID(0x24000000 + 0xB841B), LPVOID(flycave), 9);
				wpm(0x24000000 + 0x3BE9D8, 0);

				//disable predict
				wpm(0x24000000 + 0x12DA64, 0x7C832C75);
				wpm(0x24000000 + 0x12bb9a, 0x4F8B909090909090);

			}
			else {
				byte move[] = { 0x89, 0x48, 0x08 };
				wpm(PVOID(0x24000000 + 0xF657C), 3, &move);

				byte flydisbytes[] = { 0x89, 0x11, 0x8B, 0x50, 0x08, 0x89, 0x51, 0x04, 0x8b, 0x40, 0x0c, 0x89, 0x41, 0x08, 0xc3 };
				wpm(LPVOID(0x24000000 + 0xB841B), sizeof(flydisbytes), &flydisbytes);
				wpm(0x24000000 + 0x3BE9D8, 1.0f);

				//enable predict
				wpm(0x24000000 + 0x12DA64, 0x7C832C74);
				wpm(0x24000000 + 0x12bb9a, 0x4F8B000002a48689);
			}
#ifdef DEBUG
			std::cout << "flyhack triggered\n";
#endif
		}

		if (cheat.Triggered("Triggerbot & Crosshair"))
		{
			cheat.Update("Triggerbot & Crosshair");
			if (cheat("Triggerbot & Crosshair").enabled >= 1)
				wpm(0x24000000 + 0x3E208C, 0);
			else wpm(0x24000000 + 0x3E208C, 1);
#ifdef DEBUG
			std::cout << "xhair triggered\n";
#endif
		}

		if (cheat.Triggered("No Smoke & No Flash"))
		{
			noSmokeFlash();
			cheat.Update("No Smoke & No Flash");
		}

		if (cheat.Triggered("No Hands & No Sky"))
		{
			noHandsSky();
			cheat.Update("No Hands & No Sky");
		}

		if (cheat.Triggered("Disable All & Exit"))
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DisExit, 0, 0, 0);


		if (cheat.Triggered("Chameleon Wallhack"))
		{
			WH();
			cheat.Update("Chameleon Wallhack");
		}

		if (cheat.Triggered("Bunnyhop & Autostrafe"))
		{
			if (cheat("Bunnyhop & Autostrafe") == 1)
			SpyInjectAndJump(OngroundToZero, PVOID(0x24000000 + 0x220FBB), 1);
			else
			{
				byte bytes[] = { 0x83, 0x41, 0x20, 0xff, 0x89, 0x10 };
				wvm(PVOID(0x24000000 + 0x220FBB), sizeof(bytes), bytes);
			}
			cheat.Update("Bunnyhop & Autostrafe");
		}

		if (cheat.Triggered("Fake Lag"))
		{
			fakeLag();
			cheat.Update("Fake Lag");
		}

		if (cheat.Triggered("SteamID Spoof & No MOTD"))
		{
			if (cheat("SteamID Spoof & No MOTD") == 1) 
			{
				byte bytes[] = { 0x90, 0x90, 0x90 };
				wvm(PVOID(steam_dll_base + 0xB715), sizeof(bytes), bytes);
				wvm(PVOID(steam_dll_base + 0xB774), sizeof(bytes), bytes);
			}
			else
			{
				byte bytes1[] = { 0x88, 0x04, 0x3E };
				wvm(PVOID(steam_dll_base + 0xB715), sizeof(bytes1), bytes1);
				byte bytes2[] = { 0x89, 0x47, 0x54 };
				wvm(PVOID(steam_dll_base + 0xB774), sizeof(bytes2), bytes2);
			}
			cheat.Update("SteamID Spoof & No MOTD");
		}
		if (cheat("SteamID Spoof & No MOTD") == 1) {
			wpm(steam_dll_base + 0x4B170, rand()*rand()); //RevCrew's 
			wpm(engine_dll_base + 0x394BF0 - enginedelta, rand()*rand()); //Cupa's 
			wpm(rpm(rpm(rpm(0x24000000 + 0x403060) + 0x350) + 0x44) + 0x868, 0x160000); //no motd
		}

		Sleep(10);
	}
}
