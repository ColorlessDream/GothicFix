#include "PreCompiled.h"

HMODULE hDDraw = NULL;

static bool	Prepared = false;	
static uChar Bak[5] = {};

typedef HRESULT (WINAPI* DirectDrawEnumerateExAPtr)(LPVOID lpCallback, LPVOID lpContext, DWORD dwFlags);

HRESULT WINAPI MyDirectDrawEnumerateExA(LPVOID lpCallback, LPVOID lpContext, DWORD dwFlags)
{
	uChar* codeBase = (uChar*)GetModuleHandle(NULL);
	PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
	if(importDesc)
	{
		FARPROC* Res = GetImportFunctionAddress(codeBase, importDesc, false, "DirectDrawCreateEx");
		uChar* Raw = (uChar*)*Res;

		if(memcmp(Raw, Bak, 5))
			MessageBoxA(NULL, "Diff", "Info", MB_ICONINFORMATION);
		else
			MessageBoxA(NULL, "Equal", "Info", MB_ICONINFORMATION);

		for(uInt i = 0; i < 5; i++)
			PatchAddress<uChar>(&Raw[i], Bak[i]);
	}

	if(hDDraw = LoadLibraryA("ddraw.dll"))
	{
		DirectDrawEnumerateExAPtr Func = (DirectDrawEnumerateExAPtr)GetProcAddress(hDDraw, "DirectDrawEnumerateExA");
		if(Func)
			return Func(lpCallback, lpContext, dwFlags);
	}

	return S_OK;
}

bool PrepareSteamOverlayFix(void)
{
	char SteamOverlayFix[256];
	GothicReadIniString("DEBUG", "SteamOverlayFix", "1", SteamOverlayFix, 256, "SystemPack.ini");

	if(atoi(SteamOverlayFix))
	{
		uChar* codeBase = (uChar*)GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
		if(importDesc)
		{
			FARPROC* Res = GetImportFunctionAddress(codeBase, importDesc, false, "DirectDrawCreateEx");
			if(Res && *Res)
			{
				uChar* Raw = (uChar*)*Res;
				memcpy(Bak, Raw, 5);

				uChar* codeBase = (uChar*)GetModuleHandle(NULL);
				PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
				if(importDesc)
					PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "DirectDrawEnumerateExA", (FARPROC)MyDirectDrawEnumerateExA);

			}
		}
	}
	return true;
}

bool InstallSteamOverlayFix(void)
{
	if(Prepared)
	{
		uChar* codeBase = (uChar*)GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
		if(importDesc)
		{
			FARPROC* Res = GetImportFunctionAddress(codeBase, importDesc, false, "DirectDrawCreateEx");
			uChar* Raw = (uChar*)*Res;

			if(memcmp(Raw, Bak, 5))
				MessageBoxA(NULL, "Diff", "Info", MB_ICONINFORMATION);
			else
				MessageBoxA(NULL, "Equal", "Info", MB_ICONINFORMATION);

			for(uInt i = 0; i < 5; i++)
				PatchAddress<uChar>(&Raw[i], Bak[i]);
		}
	}
	return true;
}