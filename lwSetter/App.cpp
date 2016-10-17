// App.cpp: файл реализации
//

#include "stdafx.h"
#include "App.h"
#include "MainDialog.h"


// CApp

IMPLEMENT_DYNCREATE(CApp, CWinApp)

CApp::CApp()
{
	app = this;
}

CApp::~CApp()
{
}

static CApp _app;
CApp *app;

BOOL CApp::InitInstance()
{
	// TODO:  выполните здесь индивидуальную инициализацию потоков
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES | ICC_LINK_CLASS;
	SetRegistryKey(_T("disba1ancer"));
	InitCommonControlsEx(&icc);
	_tcslwr(m_lpCmdLine);
	if (!_tcscmp(m_lpCmdLine, _T("/s"))) {
		ReinitWallpaper();
	} else {
		m_pMainWnd = new CMainDialog();
		m_pMainWnd->ShowWindow(SW_NORMAL);
		m_pMainWnd->UpdateWindow();
	}
	return TRUE;
}

int CApp::ExitInstance()
{
	// TODO:  выполните здесь любую индивидуальную очистку потоков
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(CApp, CWinApp)
END_MESSAGE_MAP()


// обработчики сообщений CApp


bool CApp::ReinitWallpaper()
{
	bool enable;
	TCHAR defWlp[] = _T("%systemroot%\\Web\\Wallpaper\\Windows\\img0.jpg");
	enable = GetProfileInt(_T("Settings"), _T("Enable"), 0) != 0;
	if (enable){
		CString path;
		TCHAR args[320];
		HWND hwWorker = GetWorker();
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		path = GetProfileString(_T("Settings"), _T("Path"));
		if (path.IsEmpty())
			return false;
		SendMessage(GetProgman(), 0x52c, 0, 0);
		if (!hwWorker) {
			for (int i = 0; i < 300 && !hwWorker; ++i) {
				Sleep(1000);
				hwWorker = GetWorker();
			}
			if (!hwWorker)
				return false;
		}
		wsprintf(args, _T("%u"), hwWorker);
		path += _T(" /p ");
		path += args;
		_tcscpy(args, path.GetString()); //Stack overflow
		SendMessage(FindWindowEx(hwWorker, NULL, NULL, NULL), WM_CLOSE, 0, 0);
		SystemParametersInfo(SPI_SETDESKWALLPAPER, sizeof(defWlp), defWlp, 0);
		ZeroMemory(&si, sizeof(si));
		if (!CreateProcess(NULL, args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			int n = GetLastError();
			return false;
		}
	} else {
		SendMessage(FindWindowEx(GetWorker(), NULL, NULL, NULL), WM_CLOSE, 0, 0);
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, defWlp, 0);
	}
	return true;
}


HWND CApp::GetProgman()
{
	return FindWindowEx(NULL, NULL, _T("Progman"), NULL);
}


HWND CApp::GetWorker()
{
	HWND hwWorker = NULL;
	while (hwWorker = FindWindowEx(NULL, hwWorker, _T("WorkerW"), NULL))
	{
		if (IsWindowVisible(hwWorker)) {
			if (!FindWindowEx(NULL, hwWorker, _T("WorkerW"), NULL))
				break;
		}
	}
	return hwWorker;
}
