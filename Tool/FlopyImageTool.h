// FlopyImageTool.h : main header file for the FLOPYIMAGETOOL application
//
/*************************************************************************
** �ļ���:   FlopyImageTool.h
���� ��Ҫ��:   CFlopyImageToolApp
**  
** Copyright (c) 
** ������:   liu_sir  (E-Mail:milo2002@sohu.com)
** ��  ��:   2006-03
** �޸���:  
** ��  ��:
** ��  ��:   ���̾��񹤾߹�����
����          
**
** ��  ��:   1.0.0
** ��  ע:   

 * ***********************************************************************/

#if !defined(AFX_FLOPYIMAGETOOL_H__4E1B28FF_858C_4CD4_ACF2_DE652B7C44DE__INCLUDED_)
#define AFX_FLOPYIMAGETOOL_H__4E1B28FF_858C_4CD4_ACF2_DE652B7C44DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolApp:
// See FlopyImageTool.cpp for the implementation of this class
//

class CFlopyImageToolApp : public CWinApp
{
public:
	CFlopyImageToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlopyImageToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlopyImageToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPYIMAGETOOL_H__4E1B28FF_858C_4CD4_ACF2_DE652B7C44DE__INCLUDED_)
