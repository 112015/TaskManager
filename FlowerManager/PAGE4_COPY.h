/*
PAGE4_COPY.h: ＾猟周箝誓￣鹸崙匈遊猟周
恬宀��1120151782 藍從浣
*/
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<藍從浣>
#pragma once


// PAGE4_COPY 斤三崇

class PAGE4_COPY : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE4_COPY)

public:

	PAGE4_COPY(CWnd* pParent = NULL);   	// 炎彈更夛痕方 
	PAGE4_COPY(CString Dir, CString FileName);  	// 猟周鹸崙更夛痕方
	PAGE4_COPY(CString Pack);	//猟周斜鹸崙更夛痕方
	
	virtual ~PAGE4_COPY();

	// 斤三崇方象
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE4_COPY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 屶隔
	CString m_Source;
	CString m_Dest;   //喇Edit資誼議朕炎揃抄
	CString m_FileName;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void CopySingleFile(CString DestStr);
	void CopyDirectory(CString DestStr);
	virtual BOOL OnInitDialog();
	BOOL IsDirectory(LPCTSTR pstrPath);
	BOOL CopyFolder(CString strSrcFolder, CString strDstFolder);
};
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</藍從浣>