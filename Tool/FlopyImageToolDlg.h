// FlopyImageToolDlg.h : header file
//
/*************************************************************************
** 文件名:   FlopyImageTool.h
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
#if !defined(AFX_FLOPYIMAGETOOLDLG_H__87A65E6F_704B_4FC3_B36F_A47A03E1C424__INCLUDED_)
#define AFX_FLOPYIMAGETOOLDLG_H__87A65E6F_704B_4FC3_B36F_A47A03E1C424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolDlg dialog

class CFlopyImageToolDlg : public CDialog
{
// Construction
public:
	CString m_ImgFileName;//镜像文件名称
	CFlopyImageToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlopyImageToolDlg)
	enum { IDD = IDD_FLOPYIMAGETOOL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlopyImageToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlopyImageToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAbout();
	afx_msg void OnBtnAdd();
	afx_msg void OnButGenImg();
	afx_msg void OnBtnWriteFlopy();
	afx_msg void OnBtndel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtntrip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//CBitmapButton m_btn;
public:
	afx_msg void OnLbnSelchangeListfile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPYIMAGETOOLDLG_H__87A65E6F_704B_4FC3_B36F_A47A03E1C424__INCLUDED_)
