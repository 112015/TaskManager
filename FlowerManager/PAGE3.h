/*
PAGE3.h: “网络”页头文件
作者：1120151769 侯思凡
*/
//——————————————————————————————————————————————————————————————————————————————————————<侯思凡>
#pragma once
#include "afxcmn.h"

#include<Winnetwk.h>
#pragma comment(lib,"Mpr.lib")


// PAGE3 对话框

class PAGE3 : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE3)

public:
	PAGE3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PAGE3();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeNet;
	CListCtrl m_ListNet;

	//递归整个网络，枚举所有资源
	void  TreeProc(HTREEITEM hRoot, LPNETRESOURCE lpnr, int depth);
	//向Tree中插入一个新节点
	HTREEITEM IntsertNode(HTREEITEM hRoot, LPNETRESOURCE lpnrLocal, int depth);
	//显示每一资源——获取各属性值
	void DisplayStruct(int i, LPNETRESOURCE lpnrLocal);
	//添加一条记录
	void AddItem(TCHAR* num, TCHAR* scope, TCHAR* type, TCHAR* displaytype, TCHAR* usage, TCHAR* localname, TCHAR* remotename, TCHAR* comment, TCHAR* provider);

	//初始化
	virtual BOOL OnInitDialog();
	//鼠标滑过该节点，显示该节点的子节点数——汇报容器内资源数量
	afx_msg void OnTvnGetInfoTipTreenet(NMHDR *pNMHDR, LRESULT *pResult);
	//舒心按钮的响应事件
	afx_msg void OnBnClickedButtonnet();
	//提示选中的节点
	afx_msg void OnTvnSelchangedTreenet(NMHDR *pNMHDR, LRESULT *pResult);
	//对列表控件的排序
	afx_msg void OnLvnColumnclickListnet(NMHDR *pNMHDR, LRESULT *pResult);
};

//用于列表排序
static int sort_column;			// 记录点击的列
static bool method;				// 记录比较方法
//——————————————————————————————————————————————————————————————————————————————————————</侯思凡>