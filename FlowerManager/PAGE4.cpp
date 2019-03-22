/*
PAGE4.cpp: “文件浏览”页
作者：1120151782 王紫薇
*/
//——————————————————————————————————————————————————————————————————————————————————————<王紫薇>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4.h"
#include "PAGE4_ATTR.h"
#include "PAGE4_COPY.h"
#include "afxdialogex.h"


// PAGE4 对话框

IMPLEMENT_DYNAMIC(PAGE4, CDialogEx)

PAGE4::PAGE4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE4, pParent)
	, m_Dest(_T("请输入路径"))
{

}

PAGE4::~PAGE4()
{
}

void PAGE4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_Dir, m_TreeDir);
	DDX_Control(pDX, IDC_LIST_Dir, m_ListDir);
	DDX_Text(pDX, IDC_EDIT_Dest, m_Dest);    //输入文件路径
}


BEGIN_MESSAGE_MAP(PAGE4, CDialogEx)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_Dir, &PAGE4::OnItemexpandedTreeDir)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_Dir, &PAGE4::OnSelchangedTreeDir)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_Dir, &PAGE4::OnRclickListDir)
	ON_COMMAND(ID_Dir_Attr, &PAGE4::OnDirAttr)
	ON_COMMAND(ID_Dir_Update, &PAGE4::OnDirUpdate)
	ON_COMMAND(ID_Dir_Copy, &PAGE4::OnDirCopy)
	ON_COMMAND(ID_Dir_Dele, &PAGE4::OnDirDele)
	ON_EN_SETFOCUS(IDC_EDIT_Dest, &PAGE4::OnSetfocusEditDest)
	ON_BN_CLICKED(IDC_LIST_OK, &PAGE4::OnClickedListOk)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_Dir, &PAGE4::OnRclickTreeDir)
	ON_COMMAND(ID_Pack_Copy, &PAGE4::OnPackCopy)
	ON_COMMAND(ID_Tree_Update, &PAGE4::OnTreeUpdate)
	ON_COMMAND(ID_Pack_Dele, &PAGE4::OnPackDele)
END_MESSAGE_MAP()


// PAGE4 消息处理程序

BOOL PAGE4::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
    //GetDlgItem(IDC_EDIT_Dest)->SetWindowText("请输入路径");
	m_ImageList.Create(32, 32, ILC_COLOR32, 10, 30);     
	m_ListDir.SetImageList(&m_ImageList, LVSIL_NORMAL);    
	m_TreeDir.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	m_hRoot = m_TreeDir.InsertItem("此电脑");          
	GetDrives(m_hRoot);                                //获取盘符串 
	WalkDir(m_hRoot);                               //驱动盘下文件夹
	m_TreeDir.Expand(m_hRoot, TVE_EXPAND);          //展开或折叠子项列表 TVE_EXPAND展开列表   
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void PAGE4::GetDrives(HTREEITEM hParent)
{
	//获取系统分区驱动盘字符串信息 
	/*
	DWORD WINAPI GetLogicalDriveStringsA(
	_In_ DWORD nBufferLength,
	_Out_writes_to_opt_(nBufferLength, return + 1) LPSTR lpBuffer
	);
	*/
	size_t szAllDriveStrings = GetLogicalDriveStrings(0, NULL); 
	char *pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];  //建立数组  
   
    //C:\'\0'D:\'\0'E:\'\0'F:\'\0'I:\'\0'  每个盘符之间用了'\0'做间隔，所以需要分别获取
	GetLogicalDriveStrings(szAllDriveStrings, pDriveStrings);
	size_t szDriveString = strlen(pDriveStrings);                      
	while (szDriveString > 0)
	{
		m_TreeDir.InsertItem(pDriveStrings, hParent);    
		pDriveStrings += szDriveString + 1;            
		szDriveString = strlen(pDriveStrings);
	}
}

void PAGE4::WalkDir(HTREEITEM hParent)
{
	//获取驱动盘符下所有子项文件夹
	HTREEITEM hChild = m_TreeDir.GetChildItem(hParent);   //获取指定位置中的子项  
	while (hChild)
	{
		CString strText = m_TreeDir.GetItemText(hChild);  //检索列表中项目文字  
		if (strText.Right(1) != "\\")                   
			strText += _T("\\");
		strText += "*.*";

		//边查找边建树InsertItem  
		CFileFind file;                                        
		BOOL bContinue = file.FindFile(strText);              //查找child路径下文件  
		while (bContinue)
		{
			bContinue = file.FindNextFile();                  
			if (file.IsDirectory() && !file.IsDots())           
				m_TreeDir.InsertItem(file.GetFileName(), hChild); //添加  
		}
		WalkDir(hChild);                                  //递归调用  
		hChild = m_TreeDir.GetNextItem(hChild, TVGN_NEXT);         
	}
}

CString PAGE4::GetCurrentDir(HTREEITEM hCurrent)
{
	CString strTemp;
	CString strReturn = "";
	while (hCurrent != m_hRoot)
	{
		strTemp = m_TreeDir.GetItemText(hCurrent);    //检索列表中项目文字  
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";
		strReturn = strTemp + strReturn;
		hCurrent = m_TreeDir.GetParentItem(hCurrent); //返回父项目句柄  
	}
	return strReturn;
}

void PAGE4::AddSubDir(HTREEITEM hParent)
{
	CString strPath = GetCurrentDir(hParent);     //获取当前绝对路径 
	if (strPath.Right(1) != "\\")
		strPath += "\\";
	strPath += "*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(strPath);    //查找包含字符串的文件  
	while (bContinue)
	{
		bContinue = file.FindNextFile();        //查找下一个文件  
		if (file.IsDirectory() && !file.IsDots())
			m_TreeDir.InsertItem(file.GetFileName(), hParent);
	}
}

void PAGE4::OnItemexpandedTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	TVITEM item = pNMTreeView->itemNew;                  //发送\接受关于树形视图项目信息  
	if (item.hItem == m_hRoot)
		return;
	HTREEITEM hChild = m_TreeDir.GetChildItem(item.hItem);  //获取指定位置中的子项  
	while (hChild)
	{
		AddSubDir(hChild);                               //添加子目录  
		hChild = m_TreeDir.GetNextItem(hChild, TVGN_NEXT);   //获取树形控件TVGN_NEXT下兄弟项  
	}
	*pResult = 0;
}

//选中后展示在List
void PAGE4::OnSelchangedTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_ListDir.DeleteAllItems();
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	TVITEM item = pNMTreeView->itemNew;
	if (item.hItem == m_hRoot)
		return;
	CString str = GetCurrentDir(item.hItem);
	if (str.Right(1) != "\\")
		str += "\\";
	//存当前目录
	SetDirStr(str);

	ShowFileList(str);
	*pResult = 0;
}

void PAGE4::OnRclickListDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu* pMenuDir = new CMenu;
	pMenuDir->LoadMenu(IDR_MENU2);

	CMenu* pSubThread = pMenuDir->GetSubMenu(0);
	//MENU2 子目录0：文件操作

	//!获取鼠标位置;
	CPoint point;
	GetCursorPos(&point);

	//弹出;
	pSubThread->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	*pResult = 0;
}

//Set & Get
void PAGE4::SetDirStr(CString str)
{
	//存DirPath
	DirPath = str;
}
CString PAGE4::GetDirStr()
{
	//读DirPath
	return DirPath;
}

//Set & Get
void PAGE4::SetPackStr(CString pstr)
{
	//存DirPath
	PackPath = pstr;
}
CString PAGE4::GetPackStr()
{
	//读DirPath
	return PackPath;
}

void PAGE4::OnDirAttr()
{
	// TODO: 在此添加命令处理程序代码
	int nSel = m_ListDir.GetSelectionMark();
	//MessageBox((LPTSTR)nSel);

	if (nSel >= 0)
	{
		//MessageBox("SUCCESS");
		CString Path = GetDirStr() + m_ListDir.GetItemText(nSel, 0);
		//拼接路径和文件名

		if ((Path[0] >= 'a'&&Path[0] <= 'z') ||
			(Path[0] >= 'A'&&Path[0] <= 'Z'))
		{
			//调用属性页
			PAGE4_ATTR DlgATTR(Path);
			DlgATTR.DoModal();
		}
		else
		{
			MessageBox("请选择有权限访问的路径");
		}
	}
	else
	{
		MessageBox("请选中数据");
	}
}

void PAGE4::OnDirDele()  //文件删除
{
	// TODO: 在此添加命令处理程序代码
	int nSel = m_ListDir.GetSelectionMark();
	if (nSel >= 0)
	{
		CString FileName = m_ListDir.GetItemText(nSel, 0);
		CString Sure = "确认删除" + FileName;
		MessageBox((LPCTSTR)Sure);
		FileName = GetDirStr() + FileName;

		DeleteFile(FileName);
		m_ListDir.DeleteAllItems();

		ShowFileList(GetDirStr());
	}
}

void PAGE4::OnDirCreate()
{
	// TODO: 在此添加命令处理程序代码
}

void PAGE4::OnDirUpdate()   //List Control刷新
{
	// TODO: 在此添加命令处理程序代码

	m_ListDir.DeleteAllItems();

	CString str = GetDirStr();
	ShowFileList(str);

}

void PAGE4::OnTreeUpdate()
{
	// TODO: 在此添加命令处理程序代码
	//清空List Control、Tree Control 
	m_TreeDir.DeleteAllItems();
	m_ListDir.DeleteAllItems();

	//重载Tree Control
	m_TreeDir.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	m_hRoot = m_TreeDir.InsertItem("此电脑");
	GetDrives(m_hRoot);                                //获取盘符串 
	WalkDir(m_hRoot);                                  //递归遍历
	m_TreeDir.Expand(m_hRoot, TVE_EXPAND);          //展开或折叠子项列表 TVE_EXPAND展开列表  

}

void PAGE4::ShowFileList(CString str)
{
	m_ListDir.DeleteAllItems();
	str += "*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(str);
	while (bContinue)
	{
		bContinue = file.FindNextFile();

		if (!file.IsDirectory() && !file.IsDots())
		{
			SHFILEINFO info;
			CString temp = str;
			int index = temp.Find("*.*");
			temp.Delete(index, 3);
			SHGetFileInfo(temp + file.GetFileName(), 0, &info, sizeof(&info), SHGFI_DISPLAYNAME | SHGFI_ICON);
			/*加自己的ICON？*/
			int i = m_ImageList.Add(info.hIcon);
			m_ListDir.InsertItem(i, info.szDisplayName, i);
		}
	}
}
//文件夹复制
void PAGE4::OnDirCopy()
{
	int nSel = m_ListDir.GetSelectionMark();
	//MessageBox((LPTSTR)nSel);

	if (nSel >= 0)
	{
		//MessageBox("SUCCESS");
		CString Path = m_ListDir.GetItemText(nSel, 0);
		//只有文件名

		//调用复制对话框
		PAGE4_COPY DlgCOPY(GetDirStr(), Path); //路径、文件
		DlgCOPY.DoModal();
	}
	else
	{
		MessageBox("未选中数据");
	}
}
//文件夹复制
void PAGE4::OnPackCopy()   
{
	if (PackPath)
	{
		//调用拷贝页
		//重载构造函数
		PAGE4_COPY DlgCOPY(PackPath); //路径
		DlgCOPY.DoModal();
	}
	else
	{
		MessageBox("未选择路径");
	}

}

void PAGE4::OnPackDele()
{
	// TODO: 在此添加命令处理程序代码
	DeleteFolder(PackPath);
	OnTreeUpdate();
}

void PAGE4::OnClickedListOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString mDest;
	GetDlgItemText(IDC_EDIT_Dest, mDest);
	if (mDest.Right(1) != "\\")
		mDest += "\\";
	SetDirStr(mDest);
	ShowFileList(mDest);
}

void PAGE4::OnSetfocusEditDest()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_Dest, __T(""));
}

void PAGE4::OnEnChangeEditDest()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_Dest, __T(""));
}

void PAGE4::OnRclickTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu* pMenuDir = new CMenu;
	pMenuDir->LoadMenu(IDR_MENU2);
	CMenu* pSubThread = pMenuDir->GetSubMenu(2);
	//MENU2 子目录0：文件操作

	CPoint point;	//右击点在CTreeCtrl的坐标 [自身坐标系]
	CPoint ptSc;	//右击菜单基于[屏幕坐标系]  

	UINT  flag;
	GetCursorPos(&point);	
	ptSc = point;	
	ScreenToClient(&point);

	MapWindowPoints(&m_TreeDir, &point, 1);
	//MapWindowPoint  为父类（CDialog）的成员函数,  将坐标系映射为CTreeCtrl的坐标系



	HTREEITEM hChild = m_TreeDir.HitTest(point,&flag);  //获取指定位置中的子项 
	if (hChild != NULL)
	{
		m_TreeDir.Select(hChild, TVGN_CARET);
		//MessageBox(GetCurrentDir(hChild));
		//弹出;[自身坐标系] -- ptSc
		pSubThread->TrackPopupMenu(TPM_LEFTALIGN, ptSc.x, ptSc.y, this, NULL);
		//保存选取子项的绝对路径至Public变量PackPath
		CString Source = GetCurrentDir(hChild);
		if (Source.Right(1) != "\\")
			Source += "\\";

		SetPackStr(Source); 
	}
}

BOOL PAGE4::DeleteFolder(CString strPath)
{
	BOOL bRes = TRUE;
	BOOL bTemp;
	CFileFind finder;
	CString path = strPath + _T("\\*.*");
	BOOL bfind = finder.FindFile(path);
	while (bfind)
	{
		bfind = finder.FindNextFile();
		path = finder.GetFilePath();
		if (!finder.IsDots())
		{
			if (finder.IsDirectory())
			{
				bTemp = DeleteFolder(path);     // 递归  
				bRes = bTemp && bRes ? TRUE : FALSE;
			}
			else
			{
				bTemp = DeleteFile(path);       // 删除文件  
				bRes = bTemp && bRes ? TRUE : FALSE;
			}
		}
	}

	bTemp = RemoveDirectory(strPath);   // 删除空文件夹  
	bRes = bTemp && bRes ? TRUE : FALSE;

	return bRes;
}
//——————————————————————————————————————————————————————————————————————————————————————</王紫薇>