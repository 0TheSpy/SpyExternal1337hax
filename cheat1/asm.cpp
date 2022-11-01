#pragma once
#define endfunc __asm _emit 0xCC __asm _emit 0xCC __asm _emit 0xCC __asm _emit 0xCC

#define allocmem_ 0x19000000

__declspec(naked) void NoHands(void)
{
	__asm {
		mov eax, [ecx + 0x0C]
		cmp eax, 0x400800//4196352
		jne exitt
		cmp esp, 0x19DB08
		jne exitt
		mov eax, 0x400804
		exitt :
		add esp, 0x08
	}
	endfunc
}

__declspec(naked) void FakeLag(void)
{
	__asm {
		push eax
		push edx

		mov eax, dword ptr ds:[allocmem_ + 0x12444]
		cmp eax, 0x10 //// if packet number == 0x10
		je yes

		mov edx, dword ptr ds:[allocmem_ + 0x12204] //if we fire
		cmp edx, 1
		je yes

		mov[ebp - 0x0C], 0 //bSendPacket =  1
		jmp nexttt

		yes :
		mov dword ptr ds:[allocmem_ + 0x12444], 0
		mov eax, 0
		mov[ebp - 0x0C], 1 //bSendPacket = 0

		nexttt:
		inc eax
		mov dword ptr ds:[allocmem_ + 0x12444], eax

		pop edx
		pop eax
	}
	endfunc
}

__declspec(naked) void NoSmoke(void)
{
	__asm {
		mov eax, [ecx]
		cmp eax, 0x24336C98
		jne nosmoke
		call dword ptr[eax + 04]
		nosmoke:
	}
	endfunc
}

__declspec(naked) void d3d9Reset(void)
{
	__asm {
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push esp

		cmp byte ptr ds : [0x30173DB], 0
		je orig 

		mov byte ptr ds:[0x30173DB], 00 //17403
		mov eax, 0x00000004
		imul ecx, eax, 00
		mov edx, dword ptr ds : [ecx + 0x3017574] //17570
		mov eax, 0x00000004
		imul ecx, eax, 00
		mov eax, dword ptr ds : [ecx + 0x3017574] //
		mov ecx, [edx]
		mov esi, esp
		push eax
		mov edx, dword ptr ds:[ecx + 0x08]
		call edx
		cmp esi, esp

		mov eax, 0x00000004
		shl eax, 00
		mov ecx, dword  ptr ds : [eax + 0x3017574]//
		mov edx, 00000004
		shl edx, 00
		mov eax, dword ptr ds : [edx + 0x3017574]//
		mov ecx, [ecx]
		mov esi, esp
		push eax
		mov edx, dword ptr ds : [ecx + 0x08]
		call edx
		cmp esi, esp

		mov eax, 0x00000004
		shl eax, 1
		mov ecx, dword ptr ds : [eax + 0x3017574]//
		mov edx, 0x00000004
		shl edx, 1
		mov eax, dword ptr ds : [edx + 0x3017574]//
		mov ecx, [ecx]
		mov esi, esp
		push eax
		mov edx, dword ptr ds : [ecx + 0x08]
		call edx
		cmp esi, esp


		mov eax, 0x00000004
		imul ecx, eax, 0x03
		mov edx, dword ptr ds : [ecx + 0x3017574]//
		mov eax, 0x00000004
		imul ecx, eax, 0x03
		mov eax, dword ptr ds : [ecx + 0x3017574]//
		mov ecx, [edx]
		mov esi, esp
		push eax
		mov edx, dword ptr ds : [ecx + 0x08]
		call edx
		cmp esi, esp
		

		orig:
		pop esp
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

		mov edi, edi
		push ebp
		mov ebp, esp
	}
	endfunc
}

__declspec(naked) void asmWH(void)
{
	__asm {
		mov edi, edi
		push ebp
		mov ebp, esp

		cmp dword ptr ds : [0x3012435], 0x1
		je backs

		//ebp+0x20 - PrimCount, ebp+0x18 - NumVert
		//CT model
		cmp dword ptr ds : [ebp + 0x20], 433
		jne try2
		cmp dword ptr ds : [ebp + 0x18], 409
		je paintCT
		try2 :
		cmp dword ptr ds : [ebp + 0x20], 533
			jne try3
			cmp dword ptr ds : [ebp + 0x18], 499
			je paintCT
			try3 :
		cmp dword ptr ds : [ebp + 0x20], 1007
			jne try4
			cmp dword ptr ds : [ebp + 0x18], 929
			je paintCT
			try4 :
		cmp dword ptr ds : [ebp + 0x20], 1822
			jne try5
			cmp dword ptr ds : [ebp + 0x18], 1498
			je paintCT
			try5 :
		cmp dword ptr ds : [ebp + 0x20], 2998
			jne try6
			cmp dword ptr ds : [ebp + 0x18], 2245
			je paintCT
			try6 :
		cmp dword ptr ds : [ebp + 0x20], 5030
			jne try7
			cmp dword ptr ds : [ebp + 0x18], 3417
			je paintCT
			try7 :

		//T model
		cmp dword ptr ds : [ebp + 0x20], 344
			jne try8
			cmp dword ptr ds : [ebp + 0x18], 408
			je paintT
			try8 :
		cmp dword ptr ds : [ebp + 0x20], 509
			jne try9
			cmp dword ptr ds : [ebp + 0x18], 554
			je paintT
			try9 :
		cmp dword ptr ds : [ebp + 0x20], 899
			jne try10
			cmp dword ptr ds : [ebp + 0x18], 835
			je paintT
			try10 :
		cmp dword ptr ds : [ebp + 0x20], 1819
			jne try11
			cmp dword ptr ds : [ebp + 0x18], 1488
			je paintT
			try11 :
		cmp dword ptr ds : [ebp + 0x20], 3015
			jne try12
			cmp dword ptr ds : [ebp + 0x18], 2292
			je paintT
			try12 :
		cmp dword ptr ds : [ebp + 0x20], 4503
			jne backs
			cmp dword ptr ds : [ebp + 0x18], 3210
			je paintT

			paintCT :
		mov BYTE PTR ds : [0x30173E1], 0x00
			jmp paint

			paintT :
		mov byte ptr ds : [0x30173e1], 0x02

			paint :
			call dword ptr ds : [0x3012420] //call ColorsCave
			mov dword ptr ds : [0x3012410], 0

			zdisable :
			mov esi, esp
			mov eax, dword ptr ds : [0x3012410]
			push eax
			push 0x07
			mov eax, [ebp + 0x08]
			mov ecx, [eax]
			mov edx, [ebp + 0x08]
			push edx
			mov eax, [ecx + 0xe4]
			call eax
			cmp esi, esp

			//settexture :
		movzx eax, byte ptr ds : [0x30173e1] //ct or t
			add eax, dword ptr ds : [0x3012410]
			mov esi, esp
			mov ecx, dword ptr ds : [eax * 4 + 0x3017574]//
			push ecx
			push 00
			mov edx, [ebp + 0x08]
			mov eax, [edx]
			mov ecx, [ebp + 0x08]
			push ecx
			mov edx, [eax + 0x104]
			call edx
			cmp esi, esp

			//calldip :
		mov esi, esp
			mov eax, [ebp + 0x20]
			push eax
			mov ecx, [ebp + 0x1c]
			push ecx
			mov edx, [ebp + 0x18]
			push edx
			mov eax, [ebp + 0x14]
			push eax
			mov ecx, [ebp + 0x10]
			push ecx
			mov edx, [ebp + 0x0c]
			push edx
			mov eax, [ebp + 0x08]
			push eax
			mov dword ptr ds : [0x3012435], 0x1
			call dword ptr ds : [0x3012440] //call drawindexedprimitive
			cmp esi, esp

			//zenable :
		cmp dword ptr ds : [0x3012410], 1
			je backs
			add dword ptr ds : [0x3012410], 1
			jmp zdisable

			backs :
		mov dword ptr ds : [0x3012435], 0x0
			
	}
	endfunc
}


__declspec(naked) void Fly(void)
{
	__asm {
		push eax
		mov eax, dword ptr ds:[0x243B51C4]
		add eax, 0x29C
		cmp ecx, eax
		pop eax
		je exitt

		mov[ecx], edx
		mov edx, [eax + 0x08]
		mov[ecx + 0x04], edx
		mov eax, [eax + 0x0c]
		mov[ecx + 0x08], eax

		exitt :
	}
	endfunc
}


__declspec(naked) void OngroundToZero(void)
{
	__asm {
		mov dword ptr ds:[ecx + 0x20], 0
		mov[eax], edx
	}
	endfunc
}


__declspec(naked) void FreeVisualAnglesX(void)
{
	__asm {
		push eax
		jmp nospin2

		mov eax, dword ptr ds : [allocmem_ + 0x12204]
		cmp eax, 1
		je nospin2

		mov eax, dword ptr ds : [allocmem_ + 0x12345]
		cmp eax, 0x43326666//178.4f
		je plusx
		mov eax, 0x43326666//178.4f
		jmp movx
		plusx :
		mov eax, 0x43328000 // 178.5f
			movx :
			mov dword ptr ds : [allocmem_ + 0x12345], eax
		nospin2 :
		pop eax

		mov ecx, dword ptr ds : [allocmem_ + 0x12345]
		push 0x10
	}
	endfunc
}

__declspec(naked) void FreeVisualAnglesY(void)
{
	__asm {
		push eax
		mov eax, 0
		sub eax, dword ptr ds : [allocmem_ + 0x12220]
		mov dword ptr ds : [allocmem_ + 0x12220], eax
		pop eax

		mov ecx, dword ptr ds : [allocmem_ + 0x12349]
		push 0x10
	}
	endfunc
}

__declspec(naked) void FreeVisualAnglesZ(void)
{
	__asm {
		mov ecx, dword ptr ds : [allocmem_ + 0x1234D]
		push 0x08
	}
	endfunc
}

__declspec(naked) void Rotatingg(void)
{
	__asm {
		push eax
		mov eax, dword ptr ds : [allocmem_ + 0x12204]
		cmp eax, 1
		je aktion

		//ROTATE OUR PLAYER
		fld dword ptr ds : [allocmem_ + 0x12349] //real Y
		fadd dword ptr ds : [allocmem_ + 0x12334] //33.0f

		fcom dword ptr ds : [allocmem_ + 0x12300] //180.0
		fnstsw ax
		test ah, 0x41
		jne next1
		fsub dword ptr ds : [allocmem_ + 0x12308] //360.0
		next1 :
		fcom dword ptr ds : [allocmem_ + 0x12304] //-180.0
		fnstsw ax
		test ah, 0x05
		jp next2
		fadd dword ptr ds : [allocmem_ + 0x12308] //360.0
		next2 :
		fstp dword ptr ds : [allocmem_ + 0x12349]

		//FLIP X
		mov eax, dword ptr ds : [allocmem_ + 0x12220]
		cmp eax, dword ptr ds : [allocmem_ + 0x12224]
		je noflip
		fild dword ptr ds : [allocmem_ + 0x12200] //0
		fsub dword ptr ds : [allocmem_ + 0x12345] //x*(-1)
		fstp dword ptr ds : [allocmem_ + 0x12345]
		noflip :
		mov dword ptr ds : [allocmem_ + 0x12224], eax

		aktion :

		//CALCULATE Z ANG
		mov eax, 0x42B40000 //90.0f
		cmp eax, dword ptr ds : [allocmem_ + 0x12345]
		je bigger

		fld dword ptr ds : [allocmem_ + 0x12200] //0
		fsub dword ptr ds : [allocmem_ + 0x12330] // load -z angle
		fadd dword ptr ds : [0x243FD550] // plus visual y 
		fsub dword ptr ds : [allocmem_ + 0x12349] // minus real y 
		jmp store

		bigger :
		fld dword ptr ds : [allocmem_ + 0x12330] // load z angle 
		fsub dword ptr ds : [0x243FD550] // minus visual x
		fadd dword ptr ds : [allocmem_ + 0x12349] // plus real x

		store :
		fstp dword ptr ds : [allocmem_ + 0x1234D] //store Z

		pop eax
		//originalcode
		mov ecx, [esp + 0x14]
		mov[ebx], ecx
		mov edx, [esp + 0x18]
	}
	endfunc
}

__declspec(naked) void ZetToZero(void) //visual z
{
	__asm {
		mov dword ptr[edi + 0x08], 0
		mov ecx, DWORD PTR ds : [0x2439D4F4]
	}
	endfunc
}

__declspec(naked) void FixPredict(void) //visual z
{
	__asm {
		push eax
		pop eax

		mov edx, dword ptr ds : [allocmem_ + 0x12345]
		mov[eax + 0x0C], edx
		mov edx, dword ptr ds : [allocmem_ + 0x12349]

		mov[eax + 0x10], edx
		mov edx, dword ptr ds : [allocmem_ + 0x1234D]
	}
	endfunc
}


__declspec(naked) void Spec1(void)
{
	__asm {
		mov[esi + 0x08], ebx
		nop
		nop
		nop
		nop
		call dword ptr[eax + 0x000000CC]
	}
	endfunc
}

__declspec(naked) void Spec2(void)
{
	__asm {
		fstp dword ptr[edi]
		mov dword ptr[edi], 0x3F800000
		pop edi
		pop esi
		ret 0x000C
	}
	endfunc
}


