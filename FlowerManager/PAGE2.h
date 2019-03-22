/*
PAGE2.cpp: “性能”页头文件
作者：1120151769 侯思凡
*/
//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>
#pragma once
//性能
#include<Psapi.h>	
#include<Shlwapi.h>
#include<TlHelp32.h>
#include<winbase.h>

#pragma comment(lib,"Shlwapi.lib")  
#pragma comment(lib,"Kernel32.lib")  

// PAGE2 对话框

class PAGE2 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE2)

public:
	PAGE2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PAGE2();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	static int CALLBACK MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListPer;
	CListCtrl m_ListPower;

	//由OnInitDialog调用，获取系统和电池性能
	void ListProc();
	//写入一条获得的性能值
	void AddItem(bool flag, TCHAR* name, TCHAR* value);

	//初始化函数
	virtual BOOL OnInitDialog();
	//刷新按钮的响应事件
	afx_msg void OnBnClickedButtonper1();
	//对系统性能列表的排序
	afx_msg void OnLvnColumnclickListper(NMHDR *pNMHDR, LRESULT *pResult);
	//对电源性能列表的排序
	afx_msg void OnLvnColumnclickListpower(NMHDR *pNMHDR, LRESULT *pResult);
};

//系统性能排序用
static int sort_column1;		// 记录点击的列
static bool method1;			// 记录比较方法
//电源性能排序用
static int sort_column2;		// 记录点击的列
static bool method2;			// 记录比较方法
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>