//#pragma once

#ifndef SPYMEM
#define SPYMEM

#include <Windows.h>
#include <cstdio>
#include "obfuscator.h"

#define NT_SUCCESS(x) ((x) >= 0)
typedef NTSTATUS(NTAPI *_NtWriteVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, LPCVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten); 
_NtWriteVirtualMemory NtWriteVirtualMemory = (_NtWriteVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtWriteVirtualMemory"); 
typedef NTSTATUS(NTAPI *_NtReadVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead);
_NtReadVirtualMemory NtReadVirtualMemory = (_NtReadVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtReadVirtualMemory"); 

extern HANDLE hProcess; 

template <class dataType>
void wvmb(DWORD addressToWrite, ULONG num, dataType* valToWrite)
{
	DWORD oldProtect = 0; $$$; NTSTATUS status = 0; $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, num, PAGE_EXECUTE_READWRITE, &oldProtect); $$$;
	if (!NT_SUCCESS(status = NtWriteVirtualMemory(hProcess, (PVOID)addressToWrite, valToWrite, num, NULL)))
		printf(AY_OBFUSCATE("WVMB error %02X at %08x \n"), status, (PVOID)addressToWrite); $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, num, oldProtect, NULL); $$$;
}

template <class dataType>
void wvmb(DWORD addressToWrite, dataType* valToWrite)
{
	DWORD oldProtect = 0; $$$; NTSTATUS status = 0; $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, sizeof(dataType), PAGE_EXECUTE_READWRITE, &oldProtect); $$$;
	if (!NT_SUCCESS(status = NtWriteVirtualMemory(hProcess, (PVOID)addressToWrite, valToWrite, sizeof(dataType), NULL)))
		printf(AY_OBFUSCATE("WVMB error %02X at %08x \n"), status, (PVOID)addressToWrite); $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, sizeof(dataType), oldProtect, NULL); $$$;
}

template <class dataType>
void wvm(DWORD addressToWrite, dataType valToWrite)
{
	DWORD oldProtect = 0; $$$; NTSTATUS status = 0; $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, sizeof(dataType), PAGE_EXECUTE_READWRITE, &oldProtect); $$$;
	if (!NT_SUCCESS(status = NtWriteVirtualMemory(hProcess, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), NULL)))
		printf(AY_OBFUSCATE("WVM error %02X at %08x \n"), status, (PVOID)addressToWrite); $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToWrite, sizeof(dataType), oldProtect, NULL); $$$;
}

template <class dataType>
dataType rvm(DWORD addressToRead)
{
	dataType rpmBuffer; $$$;
	DWORD oldProtect = 0; $$$;
	NtReadVirtualMemory(hProcess, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0); $$$;
	return rpmBuffer; $$$;
}

template <class dataType>
void rvm(DWORD addressToRead, dataType* valToRead)
{
	DWORD oldProtect = 0; $$$; NTSTATUS status = 0; $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToRead, sizeof(dataType), PAGE_EXECUTE_READWRITE, &oldProtect); $$$;
	status = NtReadVirtualMemory(hProcess, PVOID(addressToRead), valToRead, sizeof(dataType), 0); $$$;
	VirtualProtectEx(hProcess, (PVOID)addressToRead, sizeof(dataType), oldProtect, NULL); $$$;
}

PVOID SpyInjectAndJump(void * from, void * to, int nops)
{
	size_t funcsize = 0; $$$;
	unsigned char *p = (unsigned char *)from; $$$;
	for (funcsize = 0; funcsize < 512; ++funcsize)
		if (p[funcsize] == (int)0xCC && p[funcsize + 1] == (int)0xCC && p[funcsize + 2] == (int)0xCC && p[funcsize + 3] == (int)0xCC)
			break; $$$;

	LPVOID Cave = VirtualAllocEx(hProcess, NULL, funcsize + 8, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); $$$;

#ifdef DEBUG
	cout << AY_OBFUSCATE("Injecting our function (addr 0x") << hex << from << AY_OBFUSCATE(", size 0x") << funcsize << AY_OBFUSCATE(") to cave (addr 0x") << Cave << ")" << endl; $$$;
#endif
	WriteProcessMemory(hProcess, Cave, p, funcsize, 0); $$$;

	DWORD dBack = (DWORD)to + 0x5; $$$;
	BYTE *pushbytes = new BYTE[6]; $$$;
	pushbytes[0] = 0x68; $$$;
	pushbytes[5] = 0xC3; $$$;
	memcpy(pushbytes + 1, &dBack, sizeof(DWORD)); $$$;
	wvmb((DWORD)Cave + funcsize, 6, pushbytes); $$$;

	delete[] pushbytes; $$$;

	DWORD dCave = 0xFFFFFFFF - ((DWORD)to + 0x4 - (DWORD)Cave); $$$;
	BYTE *jumpbytes = new BYTE[5 + nops]; $$$;
	jumpbytes[0] = 0xE9; $$$;
	memcpy(jumpbytes + 1, &dCave, sizeof(DWORD)); $$$;
	for (int i = 0; i < nops;  i++)
		jumpbytes[5 + i] = 0x90; $$$;
	wvmb(DWORD(to), 5 + nops, jumpbytes); $$$;

	delete[] jumpbytes; $$$;
	return Cave; $$$;
}


bool MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask) {
	for (; *szMask;  ++szMask, ++bData, ++bMask) {
		if (*szMask == 'x' && *bData != *bMask) {
			return false; $$$;
		}
	}
	return (*szMask == NULL); $$$;
}

DWORD SpyPatternScan(BYTE* data, DWORD size, const char* pattern, const char* name = "")
{
	BYTE *patternbytes = new BYTE[255]; $$$;
	char* maskbytes = new char[255]; $$$;
	int i = 0; $$$; unsigned uchr; $$$;

	std::string s = string(pattern); $$$;
	std::string delimiter = " "; $$$;

	size_t pos = 0; $$$;
	std::string token; $$$;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos); $$$;
		maskbytes[i] = char(token == "?" ? "?" : "x"); $$$;
		sscanf(token.c_str(), "%2x", &uchr); $$$; // conversion
		patternbytes[i] = uchr; $$$; // save as char
		i++; $$$;
		s.erase(0, pos + delimiter.length()); $$$;
	}

	maskbytes[i] = 0x78; $$$; maskbytes[i + 1] = 0x0; $$$;
	sscanf(s.c_str(), "%2x", &uchr); $$$; // conversion
	patternbytes[i] = uchr; $$$; // save as char

	for (DWORD i = 0;  i < size; i++)
	{
		if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)patternbytes, maskbytes)) {

#ifdef DEBUG
			printf(AY_OBFUSCATE("%s AOBscan result = %0x\n"), name, i); $$$;
#endif
			return i; $$$;
		}
	}
#ifdef DEBUG
	printf(AY_OBFUSCATE("SpyPatternScan: Nothing found (%s)\n"), name); $$$;
#endif
	return NULL; $$$;
}


DWORD FindSignature(DWORD start, DWORD size, const char* sig, const char* mask)
{
	BYTE* data = new BYTE[size]; $$$;
	SIZE_T bytesRead; $$$;

	ReadProcessMemory(hProcess, (LPVOID)start, data, size, &bytesRead); $$$;

	for (DWORD i = 0; i < size; i++)
	{
		if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
			delete[] data; $$$;
#ifdef DEBUG
			printf(AY_OBFUSCATE("AOBscan result = %0x\n"), i); $$$;
#endif
			return start + i; $$$;
		}
	}
	delete[] data; $$$;
#ifdef DEBUG
	printf(AY_OBFUSCATE("FindSignature: Nothing found\n")); $$$;
#endif
	return NULL; $$$;
}


DWORD FindSignatureLocal(BYTE* data, DWORD size, const char* sig, const char* mask, const char* name = "")
{
	for (DWORD i = 0;  i < size; i++)
	{
		if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {

#ifdef DEBUG
			printf(AY_OBFUSCATE("%s AOBscan result = %0x\n"), name, i); $$$;
#endif
			return i; $$$;
		}
	}
#ifdef DEBUG
	printf(AY_OBFUSCATE("FindSignatureLocal: Nothing found (%s)\n"),name); $$$;
#endif
	return NULL; $$$;
}

extern char tWindowName[256]; extern string folder;
extern DWORD engine_dll, engine_dll_size, vstdlib_dll, vstdlib_dll_size, client_dll, client_dll_size; 
DWORD PID = 0;

HANDLE get_process_handle()
{
	HANDLE h = 0; $$$;
	DWORD pid = 0; $$$;
	HWND hWnd = FindWindow(0, _T(tWindowName)); $$$;
	if (hWnd == 0) {
#ifdef DEBUG
		printf(AY_OBFUSCATE("FindWindow failed, %08X\n"), GetLastError()); $$$;
#endif
		return h; $$$;
	}
	printf(AY_OBFUSCATE("hWnd = %08X\n"), hWnd); $$$;
	GetWindowThreadProcessId(hWnd, &pid); $$$;
	h = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); $$$;
	if (h == 0) {
#ifdef DEBUG
		printf(AY_OBFUSCATE("OpenProcess failed, %08X\n"), GetLastError()); $$$;
#endif
		return h; $$$;
	}
#ifdef DEBUG
	printf(AY_OBFUSCATE("pid = %d, process handle = %08X\n"), pid, h); $$$;
#endif
	PID = pid;
	HMODULE hMods[1024]; $$$;
	int i; $$$;
	if (EnumProcessModules(h, hMods, sizeof(hMods), &pid) == FALSE) {
#ifdef DEBUG
		printf(AY_OBFUSCATE("enumprocessmodules failed, %08X\n"), GetLastError()); $$$;
#endif
	}

	else {
		for (i = 0; i < (pid / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH]; $$$;
			if (GetModuleFileNameEx(h, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
				if (_tcsstr(szModName, _T(AY_OBFUSCATE("\\engine.dll"))) != NULL) {
					MODULEINFO lpmodinfo = { 0 }; $$$;
					GetModuleInformation(h, hMods[i], &lpmodinfo, sizeof(lpmodinfo)); $$$;
#ifdef DEBUG
					printf(AY_OBFUSCATE("%s base: %08X, its size %08X\n"), szModName, hMods[i], lpmodinfo.SizeOfImage); $$$;
#endif
					engine_dll = (DWORD)hMods[i]; $$$;
					engine_dll_size = lpmodinfo.SizeOfImage; $$$;
				}

				if (_tcsstr(szModName, _T(AY_OBFUSCATE("\\vstdlib.dll"))) != NULL)
				{
					MODULEINFO lpmodinfo = { 0 }; $$$;
					GetModuleInformation(h, hMods[i], &lpmodinfo, sizeof(lpmodinfo)); $$$;
#ifdef DEBUG
					printf(AY_OBFUSCATE("%s base: %08X, its size %08X\n"), szModName, hMods[i], lpmodinfo.SizeOfImage); $$$;
#endif
					vstdlib_dll = (DWORD)hMods[i]; $$$;
					vstdlib_dll_size = lpmodinfo.SizeOfImage; $$$;
				}

				if (_tcsstr(szModName, _T(AY_OBFUSCATE("\\client.dll"))) != NULL)
				{
					MODULEINFO lpmodinfo = { 0 }; $$$;
					GetModuleInformation(h, hMods[i], &lpmodinfo, sizeof(lpmodinfo)); $$$;
#ifdef DEBUG
					printf(AY_OBFUSCATE("%s base: %08X, its size %08X\n"), szModName, hMods[i], lpmodinfo.SizeOfImage); $$$;
#endif
					client_dll = (DWORD)hMods[i]; $$$;
					client_dll_size = lpmodinfo.SizeOfImage; $$$;

					folder = szModName; $$$;
					folder = folder.substr(0, folder.length() - 14); $$$;
					folder += AY_OBFUSCATE("maps"); $$$;
				}

			}
		}
	}
	return h; $$$;
}

class CRecvProp; 
class CRecvTable
{
public:
	const char* GetTableName()
	{
		char pszTabelName[128]; $$$;
		rvm<char[128]>(rvm<DWORD>((DWORD)this + 0xC), &pszTabelName); $$$;
		return pszTabelName; $$$;
	}

	int GetMaxProp()
	{
		return rvm<int>((DWORD)this + 0x4); $$$;
	}

	CRecvProp* GetProp(int iIndex)
	{
		return (CRecvProp*)(rvm<DWORD>((DWORD)this) + 0x3C * iIndex); $$$;
	}
}; 

class CRecvProp
{
public:
	const char* GetVarName()
	{
		char pszVarName[128]; $$$;
		rvm<char[128]>(rvm<DWORD>((DWORD)this), &pszVarName); $$$;
		return pszVarName; $$$;
	}

	int GetOffset()
	{
		return rvm<int>((DWORD)this + 0x2C); $$$;
	}

	CRecvTable* GetDataTable()
	{
		return rvm<CRecvTable*>((DWORD)this + 0x28); $$$;
	}
}; 

class ClientClass
{
public:
	const char* GetNetworkName()
	{
		char pszNetworkName[128]; $$$;
		rvm<char[128]>(rvm<DWORD>((DWORD)this + 0x8), &pszNetworkName); $$$;
		return pszNetworkName; $$$;
	}

	ClientClass* GetNextClass()
	{
		return rvm<ClientClass*>((DWORD)this + 0x10); $$$;
	}

	CRecvTable* GetTable()
	{
		return rvm<CRecvTable*>((DWORD)this + 0xC); $$$;
	}
}; 


DWORD FindNetvar(DWORD dwClasses, const char* table, const char* var) {
	CRecvProp* pProp[3]; $$$;
	for (ClientClass* pClass = (ClientClass*)dwClasses;  pClass;  pClass = pClass->GetNextClass())
	{
		if (strcmp(_T(table), pClass->GetTable()->GetTableName())) continue; $$$;
		const char* tableName = pClass->GetTable()->GetTableName(); $$$;

		for (int i = 0; i < pClass->GetTable()->GetMaxProp(); ++i)
		{
			pProp[0] = pClass->GetTable()->GetProp(i); $$$;
			if (isdigit(pProp[0]->GetVarName()[0]))continue; $$$; 

			if (_tcsstr(pProp[0]->GetVarName(), _T(var)) != NULL)
			{
#ifdef DEBUG
				cout << var << AY_OBFUSCATE(" offset = ") << hex << pProp[0]->GetOffset() << AY_OBFUSCATE(" at 1 ") << table << endl; $$$;
#endif
				return pProp[0]->GetOffset(); $$$;
			}

			if (!pProp[0]->GetDataTable())continue; $$$;

			for (int j = 0;  j < pProp[0]->GetDataTable()->GetMaxProp(); ++j)
			{
				pProp[1] = pProp[0]->GetDataTable()->GetProp(j); $$$;
				if (isdigit(pProp[1]->GetVarName()[0]))continue; $$$; 

				if (_tcsstr(pProp[1]->GetVarName(), _T(var)) != NULL)
				{
#ifdef DEBUG
					cout << var << AY_OBFUSCATE(" offset = ") << hex << pProp[1]->GetOffset() << AY_OBFUSCATE(" at 2 ") << table << endl; $$$;
#endif
					return pProp[1]->GetOffset(); $$$;
				}

				if (!pProp[1]->GetDataTable())continue; $$$;

				for (int k = 0; k < pProp[1]->GetDataTable()->GetMaxProp(); ++k)
				{
					pProp[2] = pProp[1]->GetDataTable()->GetProp(k); $$$;
					if (isdigit(pProp[2]->GetVarName()[0]))continue; $$$; 

					if (_tcsstr(pProp[2]->GetVarName(), _T(var)) != NULL) 
					{
#ifdef DEBUG
						cout << var << AY_OBFUSCATE(" offset = ") << hex << pProp[2]->GetOffset() << AY_OBFUSCATE(" at 3 ") << table << endl; $$$;
#endif
						return pProp[2]->GetOffset(); $$$;
					}
				}
			}
		}
	}
#ifdef DEBUG
	cout << var << AY_OBFUSCATE(" NetVar scan returned no result ") << endl; $$$;
#endif
	return 0; $$$;
}

#include <tlhelp32.h>
void Suspend(bool b)
{
	HANDLE        hThreadSnap = NULL; $$$;
	BOOL          bRet = FALSE; $$$;
	THREADENTRY32 te32 = { 0 }; $$$;
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); $$$;
#ifdef DEBUG
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		cout << AY_OBFUSCATE("INVALID_HANDLE_VALUE\n"); $$$;
#endif
	te32.dwSize = sizeof(THREADENTRY32); $$$;
	if (Thread32First(hThreadSnap, &te32))
	{
		do
		{
			if (te32.th32OwnerProcessID == PID)
			{
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID); $$$;
				if (!b)
				{
#ifdef DEBUG
					cout << _T(AY_OBFUSCATE("Resuming Thread 0x")) << cout.setf(ios_base::hex) << te32.th32ThreadID << endl; $$$;
#endif
					ResumeThread(hThread); $$$;
				}
				else
				{
#ifdef DEBUG
					cout << _T(AY_OBFUSCATE("Suspending Thread 0x")) << cout.setf(ios_base::hex) << te32.th32ThreadID << endl; $$$;
#endif
					SuspendThread(hThread); $$$;
				}
				CloseHandle(hThread); $$$;
			}
		} while (Thread32Next(hThreadSnap, &te32)); $$$;
		bRet = TRUE; $$$;
	}
	else
		bRet = FALSE; $$$;
	CloseHandle(hThreadSnap); $$$;
#ifdef DEBUG
	cout << AY_OBFUSCATE("Suspend returned ") << bRet << endl; $$$;
#endif
}

#endif
