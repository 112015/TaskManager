/*
PAGE4_ATTR.h: “文件浏览”属性页头文件
作者：1120151782 王紫薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<王紫薇>
#pragma once


// PAGE4_ATTR 对话框

class PAGE4_ATTR : public CDialogEx
{
	DECLARE_DYNAMIC(PAGE4_ATTR)

public:
	//需要传参
	PAGE4_ATTR(CWnd* pParent = NULL);   // 标准构造函数 
	PAGE4_ATTR(CString  Path);  //重载构造函数
	virtual ~PAGE4_ATTR();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE4_ATTR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CString m_StrFileName;		//文件名;
	CString m_StrType;			//类型;
	CString m_StrPath;			//路径;
	CString m_StrSize;			//大小;
	CString m_StrCreatTime;		//创建时间;
	CString m_StrViewTime;		//访问时间;
	CString m_StrModifyTime;	//修改时间;
	CString m_StrRead;			//文件属性

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
//——————————————————————————————————————————————————————————————————————————————————————</王紫薇>