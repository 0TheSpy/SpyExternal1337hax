#pragma once
#define endfunc __asm _emit 0xCC __asm _emit 0xCC __asm _emit 0xCC __asm _emit 0xCC

__declspec(naked) void GlowNoFlick(void)
{
	__asm {
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	}
	endfunc
}

__declspec(naked) void SkyChange(void)
{
	__asm {
		mov ecx,0x00000000
		sub esp,0x134
	}
	endfunc
}

__declspec(naked) void SlideWalkFastCrouch(void)
{
	__asm {
		push eax
		push edx
		mov eax, [ebp + 0x0C]
		mov eax, [eax + 0x30]
		xor eax, 0x00000618 //pCmd->buttons ^= IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT
		or eax, 0x00400000 //pCmd->buttons |= IN_BULLRUSH
		mov edx, [ebp + 0x0C]
		mov[edx + 0x30], eax
		pop edx
		pop eax

		push[ebp + 0x0C]
		movss xmm0, [ebp + 0x08]
	}
	endfunc
}
