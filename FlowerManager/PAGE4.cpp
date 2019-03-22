/*
PAGE4.cpp: ���ļ������ҳ
���ߣ�1120151782 ����ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<����ޱ>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE4.h"
#include "PAGE4_ATTR.h"
#include "PAGE4_COPY.h"
#include "afxdialogex.h"


// PAGE4 �Ի���

IMPLEMENT_DYNAMIC(PAGE4, CDialogEx)

PAGE4::PAGE4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE4, pParent)
	, m_Dest(_T("������·��"))
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
	DDX_Text(pDX, IDC_EDIT_Dest, m_Dest);    //�����ļ�·��
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


// PAGE4 ��Ϣ�������

BOOL PAGE4::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    //GetDlgItem(IDC_EDIT_Dest)->SetWindowText("������·��");
	m_ImageList.Create(32, 32, ILC_COLOR32, 10, 30);     
	m_ListDir.SetImageList(&m_ImageList, LVSIL_NORMAL);    
	m_TreeDir.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	m_hRoot = m_TreeDir.InsertItem("�˵���");          
	GetDrives(m_hRoot);                                //��ȡ�̷��� 
	WalkDir(m_hRoot);                               //���������ļ���
	m_TreeDir.Expand(m_hRoot, TVE_EXPAND);          //չ�����۵������б� TVE_EXPANDչ���б�   
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void PAGE4::GetDrives(HTREEITEM hParent)
{
	//��ȡϵͳ�����������ַ�����Ϣ 
	/*
	DWORD WINAPI GetLogicalDriveStringsA(
	_In_ DWORD nBufferLength,
	_Out_writes_to_opt_(nBufferLength, return + 1) LPSTR lpBuffer
	);
	*/
	size_t szAllDriveStrings = GetLogicalDriveStrings(0, NULL); 
	char *pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];  //��������  
   
    //C:\'\0'D:\'\0'E:\'\0'F:\'\0'I:\'\0'  ÿ���̷�֮������'\0'�������������Ҫ�ֱ��ȡ
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
	//��ȡ�����̷������������ļ���
	HTREEITEM hChild = m_TreeDir.GetChildItem(hParent);   //��ȡָ��λ���е�����  
	while (hChild)
	{
		CString strText = m_TreeDir.GetItemText(hChild);  //�����б�����Ŀ����  
		if (strText.Right(1) != "\\")                   
			strText += _T("\\");
		strText += "*.*";

		//�߲��ұ߽���InsertItem  
		CFileFind file;                                        
		BOOL bContinue = file.FindFile(strText);              //����child·�����ļ�  
		while (bContinue)
		{
			bContinue = file.FindNextFile();                  
			if (file.IsDirectory() && !file.IsDots())           
				m_TreeDir.InsertItem(file.GetFileName(), hChild); //���  
		}
		WalkDir(hChild);                                  //�ݹ����  
		hChild = m_TreeDir.GetNextItem(hChild, TVGN_NEXT);         
	}
}

CString PAGE4::GetCurrentDir(HTREEITEM hCurrent)
{
	CString strTemp;
	CString strReturn = "";
	while (hCurrent != m_hRoot)
	{
		strTemp = m_TreeDir.GetItemText(hCurrent);    //�����б�����Ŀ����  
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";
		strReturn = strTemp + strReturn;
		hCurrent = m_TreeDir.GetParentItem(hCurrent); //���ظ���Ŀ���  
	}
	return strReturn;
}

void PAGE4::AddSubDir(HTREEITEM hParent)
{
	CString strPath = GetCurrentDir(hParent);     //��ȡ��ǰ����·�� 
	if (strPath.Right(1) != "\\")
		strPath += "\\";
	strPath += "*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(strPath);    //���Ұ����ַ������ļ�  
	while (bContinue)
	{
		bContinue = file.FindNextFile();        //������һ���ļ�  
		if (file.IsDirectory() && !file.IsDots())
			m_TreeDir.InsertItem(file.GetFileName(), hParent);
	}
}

void PAGE4::OnItemexpandedTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TVITEM item = pNMTreeView->itemNew;                  //����\���ܹ���������ͼ��Ŀ��Ϣ  
	if (item.hItem == m_hRoot)
		return;
	HTREEITEM hChild = m_TreeDir.GetChildItem(item.hItem);  //��ȡָ��λ���е�����  
	while (hChild)
	{
		AddSubDir(hChild);                               //�����Ŀ¼  
		hChild = m_TreeDir.GetNextItem(hChild, TVGN_NEXT);   //��ȡ���οؼ�TVGN_NEXT���ֵ���  
	}
	*pResult = 0;
}

//ѡ�к�չʾ��List
void PAGE4::OnSelchangedTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListDir.DeleteAllItems();
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	TVITEM item = pNMTreeView->itemNew;
	if (item.hItem == m_hRoot)
		return;
	CString str = GetCurrentDir(item.hItem);
	if (str.Right(1) != "\\")
		str += "\\";
	//�浱ǰĿ¼
	SetDirStr(str);

	ShowFileList(str);
	*pResult = 0;
}

void PAGE4::OnRclickListDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu* pMenuDir = new CMenu;
	pMenuDir->LoadMenu(IDR_MENU2);

	CMenu* pSubThread = pMenuDir->GetSubMenu(0);
	//MENU2 ��Ŀ¼0���ļ�����

	//!��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSubThread->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
	*pResult = 0;
}

//Set & Get
void PAGE4::SetDirStr(CString str)
{
	//��DirPath
	DirPath = str;
}
CString PAGE4::GetDirStr()
{
	//��DirPath
	return DirPath;
}

//Set & Get
void PAGE4::SetPackStr(CString pstr)
{
	//��DirPath
	PackPath = pstr;
}
CString PAGE4::GetPackStr()
{
	//��DirPath
	return PackPath;
}

void PAGE4::OnDirAttr()
{
	// TODO: �ڴ���������������
	int nSel = m_ListDir.GetSelectionMark();
	//MessageBox((LPTSTR)nSel);

	if (nSel >= 0)
	{
		//MessageBox("SUCCESS");
		CString Path = GetDirStr() + m_ListDir.GetItemText(nSel, 0);
		//ƴ��·�����ļ���

		if ((Path[0] >= 'a'&&Path[0] <= 'z') ||
			(Path[0] >= 'A'&&Path[0] <= 'Z'))
		{
			//��������ҳ
			PAGE4_ATTR DlgATTR(Path);
			DlgATTR.DoModal();
		}
		else
		{
			MessageBox("��ѡ����Ȩ�޷��ʵ�·��");
		}
	}
	else
	{
		MessageBox("��ѡ������");
	}
}

void PAGE4::OnDirDele()  //�ļ�ɾ��
{
	// TODO: �ڴ���������������
	int nSel = m_ListDir.GetSelectionMark();
	if (nSel >= 0)
	{
		CString FileName = m_ListDir.GetItemText(nSel, 0);
		CString Sure = "ȷ��ɾ��" + FileName;
		MessageBox((LPCTSTR)Sure);
		FileName = GetDirStr() + FileName;

		DeleteFile(FileName);
		m_ListDir.DeleteAllItems();

		ShowFileList(GetDirStr());
	}
}

void PAGE4::OnDirCreate()
{
	// TODO: �ڴ���������������
}

void PAGE4::OnDirUpdate()   //List Controlˢ��
{
	// TODO: �ڴ���������������

	m_ListDir.DeleteAllItems();

	CString str = GetDirStr();
	ShowFileList(str);

}

void PAGE4::OnTreeUpdate()
{
	// TODO: �ڴ���������������
	//���List Control��Tree Control 
	m_TreeDir.DeleteAllItems();
	m_ListDir.DeleteAllItems();

	//����Tree Control
	m_TreeDir.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	m_hRoot = m_TreeDir.InsertItem("�˵���");
	GetDrives(m_hRoot);                                //��ȡ�̷��� 
	WalkDir(m_hRoot);                                  //�ݹ����
	m_TreeDir.Expand(m_hRoot, TVE_EXPAND);          //չ�����۵������б� TVE_EXPANDչ���б�  

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
			/*���Լ���ICON��*/
			int i = m_ImageList.Add(info.hIcon);
			m_ListDir.InsertItem(i, info.szDisplayName, i);
		}
	}
}
//�ļ��и���
void PAGE4::OnDirCopy()
{
	int nSel = m_ListDir.GetSelectionMark();
	//MessageBox((LPTSTR)nSel);

	if (nSel >= 0)
	{
		//MessageBox("SUCCESS");
		CString Path = m_ListDir.GetItemText(nSel, 0);
		//ֻ���ļ���

		//���ø��ƶԻ���
		PAGE4_COPY DlgCOPY(GetDirStr(), Path); //·�����ļ�
		DlgCOPY.DoModal();
	}
	else
	{
		MessageBox("δѡ������");
	}
}
//�ļ��и���
void PAGE4::OnPackCopy()   
{
	if (PackPath)
	{
		//���ÿ���ҳ
		//���ع��캯��
		PAGE4_COPY DlgCOPY(PackPath); //·��
		DlgCOPY.DoModal();
	}
	else
	{
		MessageBox("δѡ��·��");
	}

}

void PAGE4::OnPackDele()
{
	// TODO: �ڴ���������������
	DeleteFolder(PackPath);
	OnTreeUpdate();
}

void PAGE4::OnClickedListOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString mDest;
	GetDlgItemText(IDC_EDIT_Dest, mDest);
	if (mDest.Right(1) != "\\")
		mDest += "\\";
	SetDirStr(mDest);
	ShowFileList(mDest);
}

void PAGE4::OnSetfocusEditDest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_Dest, __T(""));
}

void PAGE4::OnEnChangeEditDest()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_Dest, __T(""));
}

void PAGE4::OnRclickTreeDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu* pMenuDir = new CMenu;
	pMenuDir->LoadMenu(IDR_MENU2);
	CMenu* pSubThread = pMenuDir->GetSubMenu(2);
	//MENU2 ��Ŀ¼0���ļ�����

	CPoint point;	//�һ�����CTreeCtrl������ [��������ϵ]
	CPoint ptSc;	//�һ��˵�����[��Ļ����ϵ]  

	UINT  flag;
	GetCursorPos(&point);	
	ptSc = point;	
	ScreenToClient(&point);

	MapWindowPoints(&m_TreeDir, &point, 1);
	//MapWindowPoint  Ϊ���ࣨCDialog���ĳ�Ա����,  ������ϵӳ��ΪCTreeCtrl������ϵ



	HTREEITEM hChild = m_TreeDir.HitTest(point,&flag);  //��ȡָ��λ���е����� 
	if (hChild != NULL)
	{
		m_TreeDir.Select(hChild, TVGN_CARET);
		//MessageBox(GetCurrentDir(hChild));
		//����;[��������ϵ] -- ptSc
		pSubThread->TrackPopupMenu(TPM_LEFTALIGN, ptSc.x, ptSc.y, this, NULL);
		//����ѡȡ����ľ���·����Public����PackPath
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
				bTemp = DeleteFolder(path);     // �ݹ�  
				bRes = bTemp && bRes ? TRUE : FALSE;
			}
			else
			{
				bTemp = DeleteFile(path);       // ɾ���ļ�  
				bRes = bTemp && bRes ? TRUE : FALSE;
			}
		}
	}

	bTemp = RemoveDirectory(strPath);   // ɾ�����ļ���  
	bRes = bTemp && bRes ? TRUE : FALSE;

	return bRes;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</����ޱ>