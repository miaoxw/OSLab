/*************************************************************************
** 文件名:   FlopyImageTool.cpp
×× 主要类:   CFlopyImageToolApp
**  
** Copyright (c) 
** 创建人:   liu_sir  (E-Mail:milo2002@sohu.com)
** 日  期:   2006-03
** 修改人:  
** 日  期:
** 描  述:   软盘镜像工具工程类
××          
**
** 版  本:   1.0.0
** 备  注:   

 * ***********************************************************************/
// FlopyImageTool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FlopyImageTool.h"
#include "FlopyImageToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolApp

BEGIN_MESSAGE_MAP(CFlopyImageToolApp, CWinApp)
	//{{AFX_MSG_MAP(CFlopyImageToolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolApp construction

CFlopyImageToolApp::CFlopyImageToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFlopyImageToolApp object

CFlopyImageToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolApp initialization

BOOL CFlopyImageToolApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFlopyImageToolDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
