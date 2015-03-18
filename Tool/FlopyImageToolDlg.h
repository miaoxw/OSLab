// FlopyImageToolDlg.h : header file
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
	CString m_ImgFileName;//�����ļ�����
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
