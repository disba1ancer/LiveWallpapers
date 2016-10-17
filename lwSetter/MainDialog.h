#pragma once
#include "afxwin.h"


// диалоговое окно CMainDialog

class CMainDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CMainDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CButton okButton;
	CButton cancelButton;
	CEdit pathEdit;
	CButton lwEnableCheck;
	CButton browseButton;
	CButton applyButton;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancelbutton();
	bool LoadSettings();
	bool StoreSettings();
	afx_msg void OnBnClickedLwenable();
	afx_msg void OnBnClickedOkbutton();
	afx_msg void OnBnClickedApplybutton();
	afx_msg void OnBnClickedBrowsebutton();
	afx_msg void OnBnClickedSettingsbutton();
private:
	CButton settingsButton;
};
