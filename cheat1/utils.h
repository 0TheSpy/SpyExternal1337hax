#pragma once
 
extern DWORD ClientCMD;
void SendCMD(const char *cmd)
{
#ifdef DEBUG
	printf(AY_OBFUSCATE("Sending %s\n"), cmd); $$$;
#endif
	char* newcmd = (char*)cmd; $$$;
	size_t size = strlen(cmd); $$$;

	LPVOID Address = VirtualAllocEx(
		hProcess,
		0,
		256,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	); $$$;

	WriteProcessMemory(hProcess, PVOID(Address), static_cast<void*>(newcmd), size, 0); $$$;
	wvm<BYTE>((DWORD)Address + size, 0); $$$;
	HANDLE Thread = CreateRemoteThread(hProcess, NULL, 0, LPTHREAD_START_ROUTINE(ClientCMD), LPVOID(Address), 0, NULL); $$$;
	CloseHandle(Thread); $$$;
	WaitForSingleObject(Thread, 0xFFFFFFFF); $$$;

	VirtualFreeEx(hProcess, Address, 256, MEM_RELEASE); $$$;
}

const auto sqrtss = [](float in)
{
	__m128 reg = _mm_load_ss(&in);
	return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
};

extern DWORD convar_name_hash_table;
int GetStringHash(const char *name)
{
	int codes[256]; $$$;
	rvm(vstdlib_dll + convar_name_hash_table, &codes); $$$;

	int v2 = 0; $$$;
	int v3 = 0; $$$;
	for (int i = 0; i < strlen(name); i += 2)
	{
		v3 = codes[v2 ^ toupper(name[i])]; $$$;
		if (i + 1 == strlen(name))
			break; $$$;
		v2 = codes[v3 ^ toupper(name[i + 1])]; $$$;
	}
	return v2 | (v3 << 8);
}

extern DWORD interface_engine_cvar;
DWORD GetConVarAddress(const char *name) {
	int hash = GetStringHash(name); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("hash of ") << name << AY_OBFUSCATE(" is ") << hash << AY_OBFUSCATE(" / 0x") << hex << (int)((BYTE)hash) << endl; $$$;
#endif
	DWORD CvarEngine = rvm<DWORD>(vstdlib_dll + interface_engine_cvar); $$$;
	DWORD Pointer = rvm<DWORD>(rvm<DWORD>(CvarEngine + 0x34) + ((BYTE)hash * 4)); $$$;
	while (Pointer)
	{
		if (rvm<DWORD>(Pointer) == hash)
		{
			DWORD ConVarPointer = rvm<DWORD>(Pointer + 0x4); $$$;
			char* varname[32]; $$$;
			rvm(rvm<DWORD>(ConVarPointer + 0xC), &varname); $$$;
			if (!strcmp((char*)varname, name))
			{
#ifdef DEBUG
				cout << AY_OBFUSCATE("ConVarPointer of ") << name << AY_OBFUSCATE(" is ") << hex << ConVarPointer << "\n"; $$$;
#endif
				return ConVarPointer; $$$;
			}
		}
		Pointer = rvm<DWORD>(Pointer + 0xC); $$$;
	}
}

string getValue(const char *name) {
	char dummy[255]; $$$;
	rvm(rvm<DWORD>(GetConVarAddress(name) + 0x24), &dummy); $$$;
	return string(dummy); $$$;
}

void SetValue(const char *name, float val)
{
	DWORD addr = GetConVarAddress(name); $$$;
	wvm<int>(addr + 0x2C, *(int*)&val ^ addr); $$$;
}

void SetValue(const char *name, int val)
{
	DWORD addr = GetConVarAddress(name); $$$;
	wvm<int>(addr + 0x30, val ^ addr); $$$;
}

extern DWORD fnSetClanAddress;
void SetClanTag(const char* tag)
{
	unsigned char Shellcode[] =
		"\x51"                    //push ecx 
		"\x52"                    //push edx 
		"\xB9\x00\x00\x00\x00"    //mov ecx,00000000 { 0 } 
		"\xBA\x00\x00\x00\x00"    //mov edx,00000000 { 0 } 
		"\xE8\x00\x00\x00\x00"    //call 0 
		"\x83\x04\x24\x0A"        //add dword ptr [esp],0A { 10 } 
		"\x68\x00\x00\x00\x00"    //push engine.dll+9AC90 
		"\xC3"                    //ret 
		"\x5A"                    //pop edx 
		"\x59"                    //pop ecx 
		"\xC3"                    //ret 
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10] 
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10] 
		; $$$;

	static unsigned int SHELLCODE_SIZE = sizeof(Shellcode) - 0x21; $$$;
	unsigned int TAG_SIZE = (strlen(tag) > 15) ? 15 : strlen(tag); $$$;
	unsigned int DATA_SIZE = TAG_SIZE + 1; $$$;

	LPVOID pShellCodeAdress = VirtualAllocEx(
		hProcess,
		0,
		SHELLCODE_SIZE + DATA_SIZE,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	); $$$;

	DWORD tagAdress = (DWORD)pShellCodeAdress + SHELLCODE_SIZE; $$$;
	memcpy(Shellcode + 0x3, &tagAdress, sizeof(DWORD)); $$$;
	memcpy(Shellcode + 0x16, &fnSetClanAddress, sizeof(DWORD)); $$$;
	memcpy(Shellcode + SHELLCODE_SIZE, tag, TAG_SIZE); $$$;
	wvmb((DWORD)pShellCodeAdress, &Shellcode); $$$;
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellCodeAdress, NULL, NULL, NULL); $$$;
	WaitForSingleObject(hThread, INFINITE); $$$;
	VirtualFreeEx(hProcess, pShellCodeAdress, 0, MEM_RELEASE); $$$;
}

extern DWORD nameExploit;

union dword2bytes
{
	DWORD dw;
	BYTE bytes[sizeof(DWORD)];
};

void NameExploit(const char *name) {
	LPVOID FreeMem = VirtualAllocEx(
		hProcess,
		0,
		256,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	); $$$;
	char* newname = (char*)name; $$$;
	size_t size = strlen(name); $$$;
	WriteProcessMemory(hProcess, PVOID(FreeMem), static_cast<void*>(newname), size, 0); $$$;
	wvm<BYTE>((DWORD)FreeMem + size, 0); $$$;
	dword2bytes dw2b = { (DWORD)FreeMem }; $$$;
	BYTE origBytes[10]; $$$;
	rvm(nameExploit, &origBytes); $$$;
	BYTE shellCode[] = { 0xC7,0x44,0x24,0x10,dw2b.bytes[0],dw2b.bytes[1],dw2b.bytes[2],dw2b.bytes[3],0xEB,0x0E }; $$$;
	wvmb(nameExploit, &shellCode); $$$;
	SendCMD(AY_OBFUSCATE("setinfo name bug")); $$$;
	Sleep(100); $$$;
	wvmb(nameExploit, &origBytes); $$$;
	VirtualFreeEx(hProcess, FreeMem, 256, MEM_RELEASE); $$$;
}

D3DXVECTOR3 CalcAngle(register const D3DXVECTOR3& src, register const D3DXVECTOR3& dst)
{
	D3DXVECTOR3 angles; $$$;
	D3DXVECTOR3 delta = src - dst; $$$;
	float hyp = sqrtss(delta.x * delta.x + delta.y * delta.y); $$$;
	angles.x = atan(delta.z / hyp)		* (180.0f / PI); $$$; //asinf
	angles.y = atanf(delta.y / delta.x)	* (180.0f / PI) + !((*(DWORD*)&delta.x) >> 31 & 1) * 180.0f; $$$;
	angles.z = 0.0f; $$$;
	return angles;
}

typedef struct {
	float Matrix[3][4];
} Matrix3x4_t;

extern DWORD dwBoneMatrix;
D3DXVECTOR3	getEntBonePos(DWORD playerBase, int boneID)
{
	Matrix3x4_t boneMatrix = rvm<Matrix3x4_t>(rvm<DWORD>(playerBase + dwBoneMatrix) + boneID * 0x30); $$$;

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	}; $$$;
}

D3DXVECTOR3 ClampAngle(D3DXVECTOR3 qaAng)
{
	if (qaAng.x > 89.0f)
		qaAng.x = 89.0f; $$$;
	if (qaAng.x < -89.0f)
		qaAng.x = -89.0f; $$$;
	while (qaAng.y > 180.0f)
		qaAng.y -= 360.0f; $$$;
	while (qaAng.y < -180.0f)
		qaAng.y += 360.0f; $$$;
	qaAng.z = 0; $$$;
	return qaAng; $$$;
}

extern int Width, Height; 
extern LONG rightR, bottomR; 
extern float bomb, bombLine;
extern BOOL bombplanted;

bool WorldToScreen(float viewmatrix[][4], float coords[], float *x, float *y, float *w) {
	*x = viewmatrix[0][0] * coords[0] + viewmatrix[0][1] * coords[1] + viewmatrix[0][2] * coords[2] + viewmatrix[0][3]; $$$;
	*y = viewmatrix[1][0] * coords[0] + viewmatrix[1][1] * coords[1] + viewmatrix[1][2] * coords[2] + viewmatrix[1][3]; $$$;
	*w = viewmatrix[3][0] * coords[0] + viewmatrix[3][1] * coords[1] + viewmatrix[3][2] * coords[2] + viewmatrix[3][3]; $$$;

	if (*w < 0.1f)
		return false; $$$;

	*x = *x / *w; $$$;
	*y = *y / *w; $$$;

	int ww = Width - rightR; $$$;
	int hh = Height - bottomR; $$$;

	*x = (ww / 2 * *x) + (*x + ww / 2); $$$;
	*y = -(hh / 2 * *y) + (*y + hh / 2); $$$;

	return 1; $$$;
}

void timer() {
	float c4timer = stof(getValue(AY_OBFUSCATE("mp_c4timer"))); $$$;
#ifdef DEBUG
	printf(AY_OBFUSCATE("c4timer = %f\n"), c4timer); $$$;
#endif
	chrono::system_clock::time_point mStartedTime = chrono::system_clock::now(); $$$;
	for (;; Sleep(10)) {
		chrono::system_clock::time_point mElapsedTime = chrono::system_clock::now(); $$$;
		std::chrono::duration<float> diff = mElapsedTime - mStartedTime; $$$;
		bomb = c4timer - diff.count(); $$$;
		bombLine = 5.60 * (bomb * 100 / c4timer); $$$;
		if (!bombplanted) break; $$$;
	}
	bomb = 0.00f; $$$;
	bombLine = 0; $$$;
}

extern DWORD localplayer, dwEntityList, hActiveWeapon, iItemDefinitionIndex;
bool isActivePistol()
{
	short mywepID = rvm<short>(localplayer + hActiveWeapon) & 0xFFF; $$$;
	BYTE mywep = rvm<BYTE>(rvm<DWORD>(client_dll + dwEntityList + (mywepID - 1) * 0x10) + iItemDefinitionIndex); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("ACTIVE WEP ID = ") << dec << (int)mywep << endl; $$$;
#endif
	switch (mywep)
	{
	case 1: //DEagle
	case 2: //Dual Berettas
	case 3: //Five-SeveN
	case 4: //Glock-18
	case 5: //P228
	case 6: //USP
	case 30: //Tec-9
	case 31: //Taser
	case 32: //P2000
	case 36: //P250
	case 61: //USP-S
		return 1; $$$;
		break;
	default:
		return 0; $$$;
		break; 
	}
}
