/*
PAGE1.h: ＾序殻￣匈遊猟周
恬宀��1120151782 藍從浣
*/
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<藍從浣>
#pragma once
//序殻

// PAGE1 斤三崇

class PAGE1 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE1)

public:
	PAGE1(CWnd* pParent = NULL);   // 炎彈更夛痕方
	virtual ~PAGE1();

	// 斤三崇方象
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 屶隔
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListProcess;
	virtual BOOL OnInitDialog();
	void ListProc();
	void AddItem(TCHAR* name, TCHAR* pid, TCHAR* fpid, TCHAR* cntThreads, TCHAR* PriClassBase);
	afx_msg void OnRclickListProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnProUpdate();
};
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</藍從浣>