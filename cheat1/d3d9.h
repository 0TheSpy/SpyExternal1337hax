#ifndef D3D9
#define D3D9

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

DWM_BLURBEHIND bb = { DWM_BB_ENABLE | DWM_BB_BLURREGION, true, CreateRectRgn(0, 0, -1, -1), true };
D3DCOLOR colorprim = D3DCOLOR_ARGB(255, 203, 111, 111); //PRIMARY CHEAT COLOR 
D3DCOLOR colorsec = D3DCOLOR_ARGB(200, 5, 0, 0); //SECONDARY CHEAT COLOR 
int border = 4; //CHEAT BORDER

extern IDirect3DDevice9Ex* p_Device;
#define PI 3.14159265 
extern LONG leftR, topR, bottomR;
extern int border; extern D3DCOLOR color; extern BYTE drawmenu, menuselect;

void DrawFilledRectangle(float x, float y, float w, float h, int a, int r, int g, int b)
{
	x += leftR; $$$;
	y += topR; $$$;
	w += leftR; $$$;
	h += topR; $$$;
	D3DCOLOR color = D3DCOLOR_ARGB(a, r, g, b); $$$;
	D3DRECT rect = { x, y, w, h }; $$$;
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0); $$$;
}

void DrawFilledRectangle(float x, float y, float w, float h, D3DCOLOR color)
{
	x += leftR; $$$;
	y += topR; $$$;
	w += leftR; $$$;
	h += topR; $$$;
	D3DRECT rect = { x, y, w, h }; $$$;
	p_Device->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0); $$$;
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, int a, int r, int g, int b)
{
	DrawFilledRectangle(x, y, x + w, y + thickness, a, r, g, b); $$$;
	DrawFilledRectangle(x, y, x + thickness, y + h, a, r, g, b); $$$;
	DrawFilledRectangle(x, y + h, x + w, y + h + thickness, a, r, g, b); $$$;
	DrawFilledRectangle(x + w, y, x + w + thickness, y + h + thickness, a, r, g, b); $$$;
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR color)
{
	DrawFilledRectangle(x, y, x + w, y + thickness, color); $$$;
	DrawFilledRectangle(x, y, x + thickness, y + h, color); $$$;
	DrawFilledRectangle(x, y + h, x + w, y + h + thickness, color); $$$;
	DrawFilledRectangle(x + w, y, x + w + thickness, y + h + thickness, color); $$$;
}

void DrawString(char* String, int x, int y, int a, int r, int g, int b, ID3DXFont* font)
{
	x += leftR; $$$;
	y += topR; $$$;
	RECT FontPos; $$$;
	FontPos.left = x; $$$;
	FontPos.top = y; $$$;
	font->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b)); $$$;
}


void DrawString(char* String, int x, int y, D3DCOLOR color, ID3DXFont* font)
{
	x += leftR; $$$;
	y += topR; $$$;
	RECT FontPos; $$$;
	FontPos.left = x; $$$;
	FontPos.top = y; $$$;
	font->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, color); $$$;
}

void DrawString(char* String, int x, int y, int len, D3DCOLOR color, ID3DXFont* font)
{
	x += leftR; $$$;
	y += topR; $$$;
	RECT FontPos; $$$;
	FontPos.left = x; $$$;
	FontPos.top = y; $$$;
	font->DrawTextA(0, String, len, &FontPos, DT_NOCLIP, color); $$$;
}


void DrawStringW(wchar_t* String, int x, int y, int len, D3DCOLOR color, ID3DXFont* font)
{
	x += leftR; $$$;
	y += topR; $$$;
	RECT FontPos; $$$;
	FontPos.left = x; $$$;
	FontPos.top = y; $$$;
	font->DrawTextW(0, String, len, &FontPos, DT_NOCLIP, color); $$$;
}

LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL; 
struct vertex {
	FLOAT x, y, z,
		rhw; 
	DWORD color; 
}; 

void DrawCircle(float x, float y, float rad, float rotate, int resolution, DWORD color)
{
	x += leftR; $$$;
	y += topR; $$$;
	vector<vertex> circle(resolution + 2); $$$;
	float angle = rotate * PI / 180; $$$;

	circle[0].x = x - rad; $$$;
	circle[0].y = y; $$$;
	circle[0].z = 0; $$$;
	circle[0].rhw = 1; $$$;
	circle[0].color = color; $$$;

	for (int i = 1; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - rad * cos(PI*((i - 1) / (resolution / 2.0f)))); $$$;
		circle[i].y = (float)(y - rad * sin(PI*((i - 1) / (resolution / 2.0f)))); $$$;
		circle[i].z = 0; $$$;
		circle[i].rhw = 1; $$$;
		circle[i].color = color; $$$;
	}

	// Rotate matrix
	int _res = resolution + 2; $$$;
	for (int i = 0; i < _res;  i++)
	{
		circle[i].x = x + cos(angle)*(circle[i].x - x) - sin(angle)*(circle[i].y - y); $$$;
		circle[i].y = y + sin(angle)*(circle[i].x - x) + cos(angle)*(circle[i].y - y); $$$;
	}

	p_Device->CreateVertexBuffer((resolution + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &v_buffer, NULL); $$$;

	VOID* pVertices; $$$;
	v_buffer->Lock(0, (resolution + 2) * sizeof(vertex), (void**)&pVertices, 0); $$$;
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex)); $$$;
	v_buffer->Unlock(); $$$;

	p_Device->SetTexture(0, NULL); $$$;
	p_Device->SetPixelShader(NULL); $$$;
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); $$$;
	p_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); $$$;
	p_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); $$$;

	p_Device->SetStreamSource(0, v_buffer, 0, sizeof(vertex)); $$$;
	p_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE); $$$;
	p_Device->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution); $$$;
	if (v_buffer != NULL) v_buffer->Release(); $$$;
}

extern int Width, Height; 
IDirect3D9Ex* p_Object = 0; 
D3DPRESENT_PARAMETERS p_Params; 

class Resource {
public:
	std::size_t size_bytes = 0; 
	void* ptr = nullptr; 
	HRSRC hResource = nullptr; 
	HGLOBAL hMemory = nullptr; 
public:
	Resource(int resource_id, const std::string &resource_class) {
		hResource = FindResource(nullptr, MAKEINTRESOURCEA(resource_id), resource_class.c_str()); $$$;
		hMemory = LoadResource(nullptr, hResource); $$$;

		size_bytes = SizeofResource(nullptr, hResource); $$$;
		ptr = LockResource(hMemory); $$$;
	}
}; 

int DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(1); $$$;

	ZeroMemory(&p_Params, sizeof(p_Params)); $$$;
	p_Params.Windowed = TRUE; $$$;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD; $$$;
	p_Params.hDeviceWindow = hWnd; $$$;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE; $$$;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8; $$$;
	p_Params.BackBufferWidth = Width; $$$;
	p_Params.BackBufferHeight = Height; $$$;
	p_Params.EnableAutoDepthStencil = TRUE; $$$;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16; $$$;
	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&p_Params,
		0,
		&p_Device)))
		exit(1); $$$;
	return 0; $$$;
}

extern HWND hWnd; 
extern Cheat cheat;

void menu()
{
	SetLayeredWindowAttributes(hWnd, NULL, NULL, NULL); $$$;
	DwmEnableBlurBehindWindow(hWnd, &bb); $$$;

	float hb = Height - bottomR; $$$;
	int fontsize = hb / 51; $$$; 
	int menuheight = fontsize * 15; $$$; 

	ID3DXFont* pFont; $$$;
	D3DXCreateFont(p_Device, fontsize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Roboto", &pFont); $$$;

	DrawString((char*)AY_OBFUSCATE("Spy External 1337hax"), 5, 5, 25, 255, 255, 255, pFont); $$$;

	if (drawmenu) {
		DrawFilledRectangle(20,
			(Height - bottomR) / 3,
			menuheight + border,
			(Height - bottomR) / 3 + border * 3 + 1.5*fontsize + cheat.Count() * (fontsize*1.2),
			colorprim); $$$;  
		DrawFilledRectangle(20 + border,
			(Height - bottomR) / 3 + border * 2 + fontsize,
			menuheight,
			(Height - bottomR) / 3 + border * 2 + 1.5*fontsize + cheat.Count() * (fontsize*1.2),
			colorsec); $$$;

		RECT FontPos{ 20 + leftR,
			(Height - bottomR) / 3 + topR + border,
			menuheight + border + leftR,
			(Height - bottomR) / 3 + border * 2 + 1.5*fontsize + topR }; $$$;
		pFont->DrawTextA(0, (char*)AY_OBFUSCATE("Spy External 1337hax"), 21, &FontPos, DT_CENTER, colorsec); $$$;

		int menutop = (Height - bottomR) / 3 + border * 2 + 1.5*fontsize; $$$;
		for (BYTE i = 0; i < cheat.Count(); i++)
		{
			if (menuselect == i)
			{
				color = D3DCOLOR_ARGB(255, 255, 255, 255); $$$;
			}
			else if (cheat(i).name == (char*)AY_OBFUSCATE("Disable All & Close Cheat"))
			{
				color = D3DCOLOR_ARGB(255, 255, 50, 50); $$$;
			}
			else
			{
				color = colorprim; $$$;
			}

			DrawString((char*)cheat(i).name.c_str(), 20 + border + fontsize / 2, menutop, color, pFont); $$$;

			if (cheat(i).enabled < 10)
			{
				DrawString((char*)(std::to_string(cheat(i).enabled).c_str()), menuheight - 2 * border - fontsize / 2, menutop, color, pFont); $$$;
			}
			else
			{
				DrawString((char*)(std::to_string(cheat(i).enabled).c_str()), menuheight - 2 * border - 1.5*(fontsize / 2), menutop, color, pFont); $$$;
			}

			menutop += fontsize * 1.2; $$$; //25
		}
	}
	pFont->Release(); $$$;
}

#endif
