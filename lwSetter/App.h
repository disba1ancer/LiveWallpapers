#pragma once

#include "resource.h"

// CApp

class CApp : public CWinApp
{
	DECLARE_DYNCREATE(CApp)

public:
	CApp();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	bool ReinitWallpaper();
private:
	HWND GetProgman();
	HWND GetWorker();
};


extern CApp *app;