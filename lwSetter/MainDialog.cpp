// MainDialog.cpp: ���� ����������
//

#include "stdafx.h"
#include "MainDialog.h"
#include "App.h"


// ���������� ���� CMainDialog

IMPLEMENT_DYNAMIC(CMainDialog, CDialog)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAINDIALOG, pParent)
{
	Create(IDD_MAINDIALOG, pParent);
	LoadSettings();
}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OKBUTTON, okButton);
	DDX_Control(pDX, IDC_CANCELBUTTON, cancelButton);
	DDX_Control(pDX, IDC_PATHEDIT, pathEdit);
	DDX_Control(pDX, IDC_LWENABLE, lwEnableCheck);
	DDX_Control(pDX, IDC_BROWSEBUTTON, browseButton);
	DDX_Control(pDX, IDC_APPLYBUTTON, applyButton);
	DDX_Control(pDX, IDC_SETTINGSBUTTON, settingsButton);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CANCELBUTTON, &CMainDialog::OnBnClickedCancelbutton)
	ON_BN_CLICKED(IDC_LWENABLE, &CMainDialog::OnBnClickedLwenable)
	ON_BN_CLICKED(IDC_OKBUTTON, &CMainDialog::OnBnClickedOkbutton)
	ON_BN_CLICKED(IDC_APPLYBUTTON, &CMainDialog::OnBnClickedApplybutton)
	ON_BN_CLICKED(IDC_BROWSEBUTTON, &CMainDialog::OnBnClickedBrowsebutton)
	ON_BN_CLICKED(IDC_SETTINGSBUTTON, &CMainDialog::OnBnClickedSettingsbutton)
END_MESSAGE_MAP()


// ����������� ��������� CMainDialog


void CMainDialog::OnClose()
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	DestroyWindow();
	CDialog::OnClose();
}


void CMainDialog::OnBnClickedCancelbutton()
{
	// TODO: �������� ���� ��� ����������� �����������
	SendMessage(WM_CLOSE);
}


bool CMainDialog::LoadSettings()
{
	lwEnableCheck.SetCheck(app->GetProfileInt(_T("Settings"), _T("Enable"), 0));
	OnBnClickedLwenable();
	pathEdit.SetWindowText(app->GetProfileString(_T("Settings"), _T("Path")));
	return true;
}


bool CMainDialog::StoreSettings()
{
	CString path;
	CRegKey runReg;
	bool enable = lwEnableCheck.GetCheck() != 0;
	app->WriteProfileInt(_T("Settings"), _T("Enable"), enable);
	pathEdit.GetWindowText(path);
	app->WriteProfileString(_T("Settings"), _T("Path"), path);
	runReg.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if (enable) {
		GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);
		path.ReleaseBuffer();
		path += _T(" /s");
		runReg.SetStringValue(app->m_pszAppName, path);
	} else {
		runReg.DeleteValue(app->m_pszAppName);
	}
	return true;
}


void CMainDialog::OnBnClickedLwenable()
{
	// TODO: �������� ���� ��� ����������� �����������
	bool enable = lwEnableCheck.GetCheck() != 0;
	if (enable) {
		pathEdit.EnableWindow();
		browseButton.EnableWindow();
		settingsButton.EnableWindow();
	} else {
		pathEdit.EnableWindow(0);
		browseButton.EnableWindow(0);
		settingsButton.EnableWindow(0);
	}
}


void CMainDialog::OnBnClickedOkbutton()
{
	// TODO: �������� ���� ��� ����������� �����������
	StoreSettings();
	app->ReinitWallpaper();
	OnBnClickedCancelbutton();
}


void CMainDialog::OnBnClickedApplybutton()
{
	// TODO: �������� ���� ��� ����������� �����������
	StoreSettings();
	app->ReinitWallpaper();
}


void CMainDialog::OnBnClickedBrowsebutton()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString path;
	CString filter;
	pathEdit.GetWindowText(path);
	filter.LoadString(IDS_OPENFILETYPES);
	CFileDialog openDialog(TRUE, NULL, path, 0, filter, this);
	if (openDialog.DoModal() == IDOK) {
		pathEdit.SetWindowText(openDialog.GetPathName());
	}
}


void CMainDialog::OnBnClickedSettingsbutton()
{
	// TODO: �������� ���� ��� ����������� �����������
	CString path;
	TCHAR args[320];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	pathEdit.GetWindowText(path);
	_tcscpy(args, path.GetString()); //Stack overflow
	ZeroMemory(&si, sizeof(si));
	CreateProcess(NULL, args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
