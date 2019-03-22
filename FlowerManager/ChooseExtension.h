/*
ChooseExtension.h: ＾猟周賠尖￣僉夲猟周窃侏匈遊猟周
恬宀��1120151775 袋浣
*/
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！<袋浣>
#include<string>
using namespace std;

#pragma once


// ChooseExtension 斤三崇

class ChooseExtension : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseExtension)

public:
	ChooseExtension(CWnd* pParent = nullptr);   // 炎彈更夛痕方
	virtual ~ChooseExtension();



	// 斤三崇方象
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSE_EXTENDED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 屶隔

	DECLARE_MESSAGE_MAP()
public:
	BOOL extState[34];
	void AddItem(TCHAR* FileType, TCHAR* FileDescription);
	virtual BOOL OnInitDialog();
	CListCtrl m_list_extension;
	afx_msg void OnLvnItemchangedListExtension(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonExtensionOk();
	afx_msg void OnBnClickedCheckChooseAllExt();
};
//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！</袋浣>