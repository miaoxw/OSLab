// FlopyImageToolDlg.cpp : implementation file
//
/*************************************************************************
** 文件名:   FlopyImageToolDlg.cpp
×× 主要类:   CFlopyImageToolDlg
**  
** Copyright (c) 
** 创建人:   liu_sir  (E-Mail:milo2002@sohu.com)
** 日  期:   2006-03
** 修改人:  
** 日  期:
** 描  述:   软盘镜像工具对话框类
××          
**
** 版  本:   1.0.0
** 备  注:   

 * ***********************************************************************/

#include "stdafx.h"
#include "FlopyImageTool.h"
#include "FlopyImageToolDlg.h"
#include "shlwapi.h"
#include ".\flopyimagetooldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FLOPYBYTESIZE 1474560 //软盘字节数
#define BlOCKSIZE 512   //块大小
#define ADISKMODE 1 //对软盘空间进行补充
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolDlg dialog

CFlopyImageToolDlg::CFlopyImageToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlopyImageToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlopyImageToolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlopyImageToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlopyImageToolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlopyImageToolDlg, CDialog)
	//{{AFX_MSG_MAP(CFlopyImageToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BUTGEN, OnButGenImg)
	ON_BN_CLICKED(IDC_BUTGEN2, OnBtnWriteFlopy)
	ON_BN_CLICKED(IDC_BTNDEL, OnBtndel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNSTRIP, OnBtntrip)
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LISTFILE, OnLbnSelchangeListfile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlopyImageToolDlg message handlers

BOOL CFlopyImageToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CProgressCtrl* pProgCtrl = (CProgressCtrl* )this->GetDlgItem(IDC_PROGRESS1);
	pProgCtrl->ShowWindow(SW_HIDE);
	pProgCtrl->SetRange(0,100);
	CStatic* pStatus = (CStatic*)this->GetDlgItem(IDC_STATIC_STATUS);
	//pStatus->sette
	//this->m_btn.
	//this->m_btn.AutoLoad(IDC_BTNSTRIP,this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlopyImageToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlopyImageToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFlopyImageToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlopyImageToolDlg::OnBtnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();

}

void CFlopyImageToolDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter = "*.bin*.exe|*.exe;*.bin|*.com|*.com|*.*|*.*||";
	CFileDialog flDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	flDlg.m_ofn.Flags |=OFN_ALLOWMULTISELECT;
	if(flDlg.DoModal()==IDOK)
	{
		CString sFileName = flDlg.GetPathName();
	    POSITION p;
		CListBox* plist = (CListBox*)this->GetDlgItem(IDC_LISTFILE); 
		p = flDlg.GetStartPosition();
		while(p)
		{
			sFileName = flDlg.GetNextPathName(p);
			plist->AddString(sFileName);
		}

	}
}


//写镜像文件到软驱
UINT FuncWriteFlopy(LPVOID pDialog)
{
	//begin显示设置
	CFlopyImageToolDlg* pCurDlg =  (CFlopyImageToolDlg*) pDialog;
	CProgressCtrl* pProgCtrl = (CProgressCtrl* )pCurDlg->GetDlgItem(IDC_PROGRESS1);
	CListBox* pList = (CListBox*)pCurDlg->GetDlgItem(IDC_LISTFILE);
	CStatic* pStatus = (CStatic*)pCurDlg->GetDlgItem(IDC_STATIC_STATUS);
	pProgCtrl->ShowWindow(SW_SHOW);
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	pProgCtrl->SetPos(0);
	CString sOut = "开始写入镜像文件...";
	pStatus->SetWindowText(sOut);
	int nTotalBlocks = 80*18*2;
  
	//1.打开A驱动器
	 HANDLE    hFile = CreateFile(_T("\\\\.\\A:"),
                       GENERIC_WRITE,
                       FILE_SHARE_WRITE,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if(hFile==NULL)
	{
		sOut = _T("不能打开驱动器A");
		AfxMessageBox(sOut);
		pStatus->SetWindowText(sOut);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return -1;
	}

    PBYTE pBuffer = (PBYTE)malloc(BlOCKSIZE);
	if(pBuffer==NULL)
	{
		sOut = _T("开辟内存空间失败!");
		AfxMessageBox(sOut);
		pStatus->SetWindowText(sOut);
		CloseHandle(hFile);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return -1;
	}
	memset(pBuffer,0,BlOCKSIZE);
	//2.打开镜像文件
    CFile fInFile;
    BOOL b = fInFile.Open(pCurDlg->m_ImgFileName, CFile::modeRead);
    if(!b)
	{
		sOut.Format(_T("不能打开镜像文件%s!"),pCurDlg->m_ImgFileName);
		AfxMessageBox(sOut);
		pStatus->SetWindowText(sOut);
		CloseHandle(hFile);
		pProgCtrl->ShowWindow(SW_HIDE);
		free(pBuffer);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return -1;
	}

	//3.分块写入镜像文件
	DWORD dwImgLen = fInFile.GetLength();
	for(int i=0;i<nTotalBlocks;i++)
	{
	    DWORD dwLen=0;
		fInFile.Read(pBuffer, BlOCKSIZE);
		WriteFile(hFile, pBuffer, BlOCKSIZE, &dwLen, NULL);

#ifndef ADISKMODE
		if((DWORD)((i+1)*BlOCKSIZE)>=dwImgLen) break;//镜像文件写入完毕
#endif
		if(dwLen!=BlOCKSIZE)
		{
			sOut.Format(_T("写入镜像文件%s失败,请检查软驱!"),pCurDlg->m_ImgFileName);
			AfxMessageBox(sOut);
			pStatus->SetWindowText(sOut);
			CloseHandle(hFile);
			pProgCtrl->ShowWindow(SW_HIDE);
			fInFile.Close();
			free(pBuffer);
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return -1;
			
		}
		pProgCtrl->SetPos((int)(i*100/nTotalBlocks));
	}




	//4.关闭文件
    fInFile.Close();
	CloseHandle(hFile);
    free(pBuffer);
	

	//end 显示设置
	pProgCtrl->SetPos(100);
	sOut.Format(_T("镜像文件%s写入软驱成功!"),pCurDlg->m_ImgFileName);
	MessageBox(pCurDlg->m_hWnd,sOut,_T("提示"),MB_OK | MB_ICONINFORMATION);
	pProgCtrl->ShowWindow(SW_HIDE);
	pStatus->SetWindowText(sOut);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return 0;
}

//生成镜像文件函数
UINT FuncGenImageFile(LPVOID pDialog)
{
	//Begin 显示设置
	CFlopyImageToolDlg* pCurDlg =  (CFlopyImageToolDlg*) pDialog;
	CProgressCtrl* pProgCtrl = (CProgressCtrl* )pCurDlg->GetDlgItem(IDC_PROGRESS1);
	CListBox* pList = (CListBox*)pCurDlg->GetDlgItem(IDC_LISTFILE);
	CStatic* pStatus = (CStatic*)pCurDlg->GetDlgItem(IDC_STATIC_STATUS);
	pProgCtrl->ShowWindow(SW_SHOW);
	pProgCtrl->SetPos(0);
	CString sOut = _T("开始生成镜像文件");
	pStatus->SetWindowText(sOut);
    
	//1.创建输出镜像文件
	byte* pBuf = NULL;
    DWORD count = 0,dwFileLength=0;
	CFile outfile;
	if(!outfile.Open(pCurDlg->m_ImgFileName,CFile::modeCreate | CFile::modeWrite))
	{
		sOut.Format(_T("不能打开文件%S"),pCurDlg->m_ImgFileName);
		AfxMessageBox(sOut);
		pStatus->SetWindowText(sOut);
		pProgCtrl->ShowWindow(SW_HIDE);
		return -1;
	}
	
	//2.依次对输入文件读取,写入输出镜像文件
    for( int i = 0 ; i < pList->GetCount(); ++i ){
      CString sInFileName; 
	  pList->GetText(i,sInFileName);
      CFile infile;

	  if(!infile.Open(sInFileName,CFile::modeRead))
	  {
		sOut.Format(_T("不能打开文件%S"),sInFileName);
		AfxMessageBox(sOut);
		outfile.Close();
		pStatus->SetWindowText(sOut);
		pProgCtrl->ShowWindow(SW_HIDE);
		return -1;
	  }
	  dwFileLength = infile.GetLength();
	  if(i==0)
	  {
		  if(dwFileLength>512)
		  {
			  sOut.Format(_T("文件%S不是一个有效的引导区文件,请使用[功能3]裁减该文件!"),sInFileName);
			  AfxMessageBox(sOut);
			  outfile.Close();
			  infile.Close();

			  pStatus->SetWindowText(sOut);
			  pProgCtrl->ShowWindow(SW_HIDE);
			  return -1;
		  }
	  }
      if(i==0)//对0扇区文件进行特殊处理
	  {
	  	  pBuf = new byte[BlOCKSIZE]; 
		  ::memset(pBuf,0,BlOCKSIZE);
		  infile.Read(pBuf,dwFileLength);
		  if(pBuf[510]!=0x55) pBuf[510]=0x55;
		  if(pBuf[511]!=0xAA) pBuf[510]=0xAA;
		  outfile.Write(pBuf,BlOCKSIZE);
		  dwFileLength = BlOCKSIZE;
	  }
	  else
	  {
		  pBuf = new byte[dwFileLength]; 
		  infile.Read(pBuf,dwFileLength);
		  outfile.Write(pBuf,dwFileLength);
	  }
      infile.Close() ;

	  delete[] pBuf;
	  count += dwFileLength;
	  pProgCtrl->SetPos((int)(count*100/FLOPYBYTESIZE));
    }

	/*不对软盘剩余进行补充*/
#ifdef ADISKMODE
    //3.补充剩余的软盘字节为0
	DWORD dwRet = FLOPYBYTESIZE-count;
	pBuf = new byte[dwRet];
	memset(pBuf,0,dwRet);
	outfile.Write(pBuf,dwRet);
	delete[] pBuf;
#endif
    outfile.Close() ;


    //end 显示设置
	pProgCtrl->SetPos(100);
	sOut.Format(_T("生成镜像文件%s成功!"),pCurDlg->m_ImgFileName);
	MessageBox(pCurDlg->m_hWnd,sOut,_T("提示"),MB_OK | MB_ICONINFORMATION);
	pProgCtrl->ShowWindow(SW_HIDE);
	pStatus->SetWindowText(sOut);
	return 0;
}

void CFlopyImageToolDlg::OnButGenImg() 
{
	// TODO: Add your control notification handler code here
	CListBox* plist = (CListBox*)this->GetDlgItem(IDC_LISTFILE); 
	if(plist->GetCount()<1)
	{
		AfxMessageBox(_T("至少应该添加一个源文件!"));
		plist->SetFocus();
		return;
	}
	CString strFilter;
	strFilter = _T("*.img|*.img||");
	CFileDialog flDlg(FALSE, _T("*.img"), NULL, OFN_OVERWRITEPROMPT, strFilter);
	if(flDlg.DoModal()==IDOK)
	{
		this->m_ImgFileName = flDlg.GetPathName();
		::AfxBeginThread(FuncGenImageFile,(LPVOID)this);
	}
}

void CFlopyImageToolDlg::OnBtnWriteFlopy() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter = _T("*.img|*.img||");
	CFileDialog flDlg(TRUE, _T("*.img"), NULL, OFN_FILEMUSTEXIST, strFilter);
	if(flDlg.DoModal()==IDOK)
	{
		this->m_ImgFileName = flDlg.GetPathName();
		::AfxBeginThread(FuncWriteFlopy,(LPVOID)this);
	}

}

void CFlopyImageToolDlg::OnBtndel() 
{
	// TODO: Add your control notification handler code here
	CListBox* plist = (CListBox*)this->GetDlgItem(IDC_LISTFILE); 	
	int index = plist->GetCurSel();
	if(index!=-1)
	{
		plist->DeleteString(index);
	}
}

HBRUSH CFlopyImageToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_STATUS)//
	{
		// Set the text color to red.
		pDC->SetTextColor(RGB(0, 0, 255));
		
		// Set the background mode for text to transparent 
		// so background will show thru.
		pDC->SetBkMode(TRANSPARENT);
		
	}
	else if(pWnd->GetDlgCtrlID()==IDC_LISTFILE)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkColor(RGB(0,222,0));
		
		// Set the background mode for text to transparent 
		// so background will show thru.
		pDC->SetBkMode(TRANSPARENT);		
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFlopyImageToolDlg::OnBtntrip() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter = _T("*.exe|*.exe|*.*|*.*||");
	CFileDialog flDlg(TRUE, _T("*.exe"), NULL, OFN_FILEMUSTEXIST, strFilter);
	if(flDlg.DoModal()==IDOK)
	{
		CString sFileName = flDlg.GetPathName();


		CFile fInfile;
		if(!fInfile.Open(sFileName,CFile::modeRead))
		{
			AfxMessageBox(_T("不能打开文件！"));
			return;
		}
		long size = fInfile.GetLength();
		if(size<=512)
		{
			CString s;
			s.Format(_T("%s不是一个有效的DOS文件!"),sFileName);
			AfxMessageBox(s);
			fInfile.Close();
			return;
		}

		PBYTE pBuf = (PBYTE)new byte[512];
		fInfile.Read(pBuf,512);
		delete[] pBuf;

		long nRetSize = size-512;
		pBuf = new BYTE[nRetSize];

		fInfile.Read(pBuf,nRetSize);
		CString sOutFile = sFileName;
		sOutFile.Replace(fInfile.GetFileName(),_T("A-out.bin"));
		//sOutFile +=_T("\\out.bin");
		if(PathFileExists(sOutFile))
		{
			::DeleteFile(sOutFile);
		}

		CFile fOutFile;
		fOutFile.Open(sOutFile,CFile::modeCreate|CFile::modeWrite);
		fOutFile.Write(pBuf,nRetSize);

		fOutFile.Close();
		delete[] pBuf;
		CString sOut;
		sOut.Format(_T("生成%s成功!"),sOutFile);
		MessageBox(sOut,_T("提示"),MB_OK | MB_ICONINFORMATION);

	}
}

void CFlopyImageToolDlg::OnLbnSelchangeListfile()
{
	// TODO: 在此添加控件通知处理程序代码
	//::SetCursor();
}
