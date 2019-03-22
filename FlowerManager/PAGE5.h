/*
PAGE5.h: ＾猟周賠尖￣匈遊猟周
恬宀��1120151764 蛎珍杷
	 1120151775 袋浣
*/
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<蛎珍杷>
#pragma once

// PAGE5 斤三崇

class PAGE5 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE5)

public:
	PAGE5(CWnd* pParent = NULL);   // 炎彈更夛痕方
	virtual ~PAGE5();

	// 斤三崇方象
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 屶隔

	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_page5;
	CEdit m_edit_fileroute;
	afx_msg void OnBnClickedButtonFileroute();
	void searchFile(char * sourceFile);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnLvnColumnclickListPage5(NMHDR *pNMHDR, LRESULT *pResult);
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</蛎珍杷>
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<袋浣>
	CEdit m_edit_filetype;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFiletype();
	afx_msg void OnBnClickedCheckChooseallPage5();
	afx_msg void OnBnClickedButtonClean();
};
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</袋浣>
