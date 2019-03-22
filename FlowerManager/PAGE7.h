/*
PAGE7.h: ＾坪贋￣匈遊猟周
恬宀��1120151775 袋浣
*/
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<袋浣>
#pragma once
#include "afxcmn.h"


// PAGE7 斤三崇

class PAGE7 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE7)

public:
	PAGE7(CWnd* pParent = NULL);   // 炎彈更夛痕方
	virtual ~PAGE7();

	// 斤三崇方象
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 屶隔

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListSystemInfo;
	virtual BOOL OnInitDialog();
	void ListProc();
	//void AddItem(TCHAR* name, TCHAR* data);
	afx_msg void OnBnClickedButtonRefresh();
};
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</袋浣>