/*
PAGE3.cpp: �����硱ҳ
���ߣ�1120151769 ��˼��
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE3.h"
#include "afxdialogex.h"


// PAGE3 �Ի���

IMPLEMENT_DYNAMIC(PAGE3, CDialogEx)

PAGE3::PAGE3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE3, pParent)
{

}

PAGE3::~PAGE3()
{

}

void PAGE3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREENET, m_TreeNet);
	DDX_Control(pDX, IDC_LISTNET, m_ListNet);
}


BEGIN_MESSAGE_MAP(PAGE3, CDialogEx)
	ON_NOTIFY(TVN_GETINFOTIP, IDC_TREENET, &PAGE3::OnTvnGetInfoTipTreenet)			//��껬���ڵ㣬��ʾ���ӽڵ���
	ON_BN_CLICKED(IDC_BUTTONNet, &PAGE3::OnBnClickedButtonnet)						//ˢ��ҳ��
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREENET, &PAGE3::OnTvnSelchangedTreenet)			//��ʾ��ѡ�еĽڵ�
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTNET, &PAGE3::OnLvnColumnclickListnet)		//����
END_MESSAGE_MAP()


// PAGE3 ��Ϣ�������


BOOL PAGE3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HTREEITEM hRoot;										//���ĸ�
	hRoot = m_TreeNet.InsertItem(_T("��������"), 0, 0);		//���ڵ���

	LPNETRESOURCE Ipnr = NULL;								//������Դ

	//Listд�ϸ���������
	//m_ListNet.InsertColumn(0, "���", NULL, 50, 50);		//û������壬�Ҳ�����
	m_ListNet.InsertColumn(0, "Զ����������", NULL, 150, 50);
	m_ListNet.InsertColumn(1, "��Դ����", NULL, 100, 50);
	m_ListNet.InsertColumn(2, "��������û�����������������ʾѡ��", NULL, 180, 50);
	m_ListNet.InsertColumn(3, "���ʹ�õ�һ��λ��־", NULL, 80, 50);
	m_ListNet.InsertColumn(4, "�����豸����", NULL, 150, 50);
	m_ListNet.InsertColumn(5, "ö�ٷ�Χ", NULL, 150, 50);
	m_ListNet.InsertColumn(6, "����", NULL, 100, 50);
	m_ListNet.InsertColumn(7, "�ṩ��", NULL, 100, 50);

	//�ݹ���������
	TreeProc(hRoot, Ipnr, 1);

	//չ����һ��ڵ㡪���ÿ�һ�����������
	m_TreeNet.Expand(hRoot, TVE_EXPAND);					

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void PAGE3::TreeProc(HTREEITEM hRoot, LPNETRESOURCE lpnr, int depth) 
{
	DWORD dwResult, dwResultEnum;
	HANDLE hEnum;
	DWORD cbBuffer = 16384;			// 16K �Ǹ����ʵĴ�С
	DWORD cEntries = -1;			// ö�����п��ܵ���Ŀ
	LPNETRESOURCE lpnrLocal;		// ָ��ö�ٵĽṹ��
	DWORD i;
	HTREEITEM hsubRoot;				//�½ڵ�Ҳ�����������ӵġ�����Ŷ

	//����WNetOpenEnum��������ʼö��
	dwResult = WNetOpenEnum(
		RESOURCE_GLOBALNET,			// ���е�������Դ
		RESOURCETYPE_ANY,			// ���е���Դ
		0,							// ö��������Դ
		lpnr,						// ��һ����NULL
		&hEnum);					// ��Դ�ľ��

	//�Ͻ����Ҹ�΢��ѧ��
	if (dwResult != NO_ERROR)
	{
		return;
	}

	// ����GlobalAlloc������������Դ
	lpnrLocal = (LPNETRESOURCE)GlobalAlloc(GPTR, cbBuffer);
	if (lpnrLocal == NULL) 
	{
		// NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
		//MessageBox("��Դ����ʧ�ܣ�");
		return;
	}

	//����һ��ö�ٵ�ѭ��
	do {
		// ��ʼ��������
		ZeroMemory(lpnrLocal, cbBuffer);

		// ����WNetEnumResource����������ö��
		dwResultEnum = WNetEnumResource(
			hEnum,				// ��Դ�ľ��
			&cEntries,			// -1
			lpnrLocal,			// LPNETRESOURCE
			&cbBuffer);			// ��������С

		// ������óɹ���ѭ��
		if (dwResultEnum == NO_ERROR) 
		{
			m_TreeNet.SetItemData(hRoot, cEntries);						//���ڵ�д�����м������ӣ�һ���Է����û�Ϊ�أ�����ʦ˵�û���ɵ��
			for (i = 0; i < cEntries; i++) 
			{
				// �����ǵ�����������
				hsubRoot = IntsertNode(hRoot, &lpnrLocal[i], depth);

				//Listͬ������һ����Դ��¼
				DisplayStruct(i, &lpnrLocal[i]);

				// ���NETRESOURCE�ṹ�����һ���������ݹ�ص��ô˺�������Ϊ���ж���ѽ
				if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage& RESOURCEUSAGE_CONTAINER)) 
				{
					//����һ��ݹ鰡
					TreeProc(hsubRoot, &lpnrLocal[i], ++depth);
					depth--;		//�ص���һ��
				}
			}//for�������ǲ��������ǣ��������ܿ��������������˭����
		}//if
		 // ����
		else if (dwResultEnum != ERROR_NO_MORE_ITEMS) 
		{
			//      NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
			break;
		}
	} while (dwResultEnum != ERROR_NO_MORE_ITEMS);

	// ����GlobalFree�����ͷ��ڴ�
	GlobalFree((HGLOBAL)lpnrLocal);

	// ����WNetCloseEnum��������ö��
	dwResult = WNetCloseEnum(hEnum);

	if (dwResult != NO_ERROR) 
	{
		// ����
		//    NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
		return;
	}
}

/*�����в���һ���ڵ㣬�����µĽڵ�Ŷ������������Ҳ�Ǹ��ְ�*/
HTREEITEM PAGE3::IntsertNode(HTREEITEM hRoot, LPNETRESOURCE lpnrLocal, int depth)
{
	HTREEITEM hSubRoot;
	hSubRoot= m_TreeNet.InsertItem(lpnrLocal->lpRemoteName, depth, depth, hRoot);
	return hSubRoot;
}

/*���ڽ��������ϸ��Ϣд��List�г��ָ��û�*/
void PAGE3::DisplayStruct(int i, LPNETRESOURCE lpnrLocal) 
{
	//������������
	TCHAR* Num = new TCHAR[MAX_PATH];
	TCHAR* Scope = new TCHAR[MAX_PATH];
	TCHAR* Type = new TCHAR[MAX_PATH];
	TCHAR* DisplayType = new TCHAR[MAX_PATH];
	TCHAR* Usage = new TCHAR[MAX_PATH];
	TCHAR* Localname = new TCHAR[MAX_PATH];
	TCHAR* Remotename = new TCHAR[MAX_PATH];
	TCHAR* Comment = new TCHAR[MAX_PATH];
	TCHAR* Provider = new TCHAR[MAX_PATH];

	//���
	sprintf(Num, "%d", i);

	//ö�ٷ�Χ
	switch (lpnrLocal->dwScope)
	{
	case(RESOURCE_CONNECTED):
		sprintf(Scope, "ö�ٵ�ǰ���ӵ���Դ");
		break;
	case(RESOURCE_GLOBALNET):
		sprintf(Scope, "ö�������ϵ�������Դ");
		break;
	case(RESOURCE_REMEMBERED):
		sprintf(Scope, "ö�ټ��䣨���ã�����");
		break;
	default:
		sprintf(Scope, "δ֪ %d", lpnrLocal->dwScope);
		break;
	}

	//��Դ����
	switch (lpnrLocal->dwType) 
	{
	case(RESOURCETYPE_ANY):
		sprintf(Type, "������Դ");
		break;
	case(RESOURCETYPE_DISK):
		sprintf(Type, "������Դ");
	case(RESOURCETYPE_PRINT):
		sprintf(Type, "��ӡ��Դ");
		break;
	default:
		sprintf(Type, "δ֪ %d", lpnrLocal->dwType);
		break;
	}

	//��������û�����������������ʾѡ��
	switch (lpnrLocal->dwDisplayType) 
	{
	case (RESOURCEDISPLAYTYPE_GENERIC):
		sprintf(DisplayType, "������ʾ����ķ���������Ҫ");
		break;
	case (RESOURCEDISPLAYTYPE_DOMAIN):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪһ����");
		break;
	case (RESOURCEDISPLAYTYPE_SERVER):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪ������");
		break;
	case (RESOURCEDISPLAYTYPE_SHARE):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪ����");
		break;
	case (RESOURCEDISPLAYTYPE_FILE):
		sprintf(DisplayType, "�ö���Ӧ����ʾΪһ���ļ�");
		break;
	case (RESOURCEDISPLAYTYPE_GROUP):
		sprintf(DisplayType, "�ö���Ӧ����Ϊһ������ʾ");
		break;
	case (RESOURCEDISPLAYTYPE_NETWORK):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪ����");
		break;
	case(RESOURCEDISPLAYTYPE_ROOT):
		sprintf(DisplayType, "�ö���Ӧ����ʾΪ����������߼���");
		break;
	case(RESOURCEDISPLAYTYPE_SHAREADMIN):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪ������");
		break;
	case(RESOURCEDISPLAYTYPE_DIRECTORY):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪһ��Ŀ¼");
		break;
	case(RESOURCEDISPLAYTYPE_TREE):
		sprintf(DisplayType, "�ö���Ӧ����ʾΪһ����");
		break;
	case(RESOURCEDISPLAYTYPE_NDSCONTAINER):
		sprintf(DisplayType, "�ö���Ӧ��ʾΪNetwareĿ¼��������");
		break;
	default:
		sprintf(DisplayType, "δ֪ %d", lpnrLocal->dwDisplayType);
		break;
	}

	//������Դ���ʹ�õ�һ��λ��־
	switch (lpnrLocal->dwUsage)
	{
	case(RESOURCEUSAGE_CONNECTABLE):
		sprintf(Usage, "�����ӵ���Դ");
		break;
	case(RESOURCEUSAGE_CONTAINER):
		sprintf(Usage, "������Դ");
		break;
	case(RESOURCEUSAGE_NOLOCALDEVICE):
		sprintf(Usage, "�Ǳ����豸");
		break;
	case(RESOURCEUSAGE_SIBLING):
		sprintf(Usage, "�ֵܽ���");//windows��ʹ�����ֵ
		break;
	case(RESOURCEUSAGE_ATTACHED):
		sprintf(Usage, "��������");
		break;
	default:
		sprintf(Usage, "δ֪ %d", lpnrLocal->dwUsage);
		break;
	}
	//����һ�α������Ĵ��룬�˴�����΢������ṩ�������߲�ѯ��΢���dwUsage�ĸ�ȫ��Ľ��ͣ���ʹ������Ĵ���
	//if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE) {
	//	sprintf(Usage, "0x%x = connectable",lpnrLocal->dwUsage);
	//}
	//else {
	//	sprintf(Usage, "0x%x = container", lpnrLocal->dwUsage);
	//}

	//�����豸����
	/*���dwScope��Ա����RESOURCE_CONNECTED��RESOURCE_REMEMBERED��
	��˳�Ա��ָ��ָ�������豸���ƵĿ���ֹ�ַ�����ָ�롣
	������Ӳ�ʹ���豸����ó�ԱΪNULL��*/
	sprintf(Localname, "%s", lpnrLocal->lpLocalName);

	//Զ���豸����
	/*�����Ŀ��������Դ����ó�Ա��ָ��ָ��Զ���������ƵĿ���ֹ�ַ�����ָ�롣
	������ǵ�ǰ���������ӣ�lpRemoteName��Աָ����������ص���������ָ���lpLocalName��Ա��
	���ַ����ĳ��ȿ�����MAX_PATH���ַ������ұ�����ѭ�����ṩ�ߵ�����Լ����*/
	sprintf(Remotename, "%s", lpnrLocal->lpRemoteName);

	//ָ������������ṩ���ṩ��ע�͵�NULL��ֹ�ַ�����ָ�롣
	sprintf(Comment, "%s", lpnrLocal->lpComment);

	//�ṩ��
	/*ָ�����ӵ����Դ���ṩ�������Ƶ�NULL��ֹ�ַ�����ָ�롣����ṩ������δ֪���˳�Ա����ΪNULL*/
	sprintf(Provider, "%s", lpnrLocal->lpProvider);

	//����һ����¼
	AddItem(Num, Remotename, Type, DisplayType, Usage, Localname, Scope, Comment, Provider);
}

/*��List�����һ����Դ�ļ�¼*/
void PAGE3::AddItem(TCHAR* num, TCHAR* remotename, TCHAR* type, TCHAR* displaytype, TCHAR* usage, TCHAR* localname, TCHAR* scope, TCHAR* comment, TCHAR* provider)
{
	int nItemNum;
	nItemNum = m_ListNet.GetItemCount();
	//�����ҾͲ�д�ˣ�������ĺ�����д����˵�
	m_ListNet.InsertItem(nItemNum, remotename);
	m_ListNet.SetItemText(nItemNum, 1, type);
	m_ListNet.SetItemText(nItemNum, 2, displaytype);
	m_ListNet.SetItemText(nItemNum, 3, usage);
	m_ListNet.SetItemText(nItemNum, 4, localname);
	m_ListNet.SetItemText(nItemNum, 5, scope);
	m_ListNet.SetItemText(nItemNum, 6, comment);
	m_ListNet.SetItemText(nItemNum, 7, provider);
	//m_ListNet.SetItemText(nItemNum, 8, provider);
}

/*��껮�����ڵ����ĳ�����ڵ�ʱ����ʾ�ڵ���ӽڵ��м����������ǲ���������*/
void PAGE3::OnTvnGetInfoTipTreenet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NMTVGETINFOTIP* pTVTipInfo = (NMTVGETINFOTIP*)pNMHDR;   // �������pNMHDRת��ΪNMTVGETINFOTIPָ������   
	HTREEITEM hRoot = m_TreeNet.GetRootItem();				// ��ȡ���ĸ��ڵ�   
	CString strText;										// ÿ�����ڵ����ʾ��Ϣ   

	if (pTVTipInfo->hItem == hRoot) {
		// �����껮���Ľڵ��Ǹ��ڵ㣬����ʾ��ϢΪ���������ǲ������⻯�ˣ���ʾ��
		//strText = _T("");
		strText.Format(_T("%d"), pTVTipInfo->lParam);
	}
	else {
		// �����껮���Ľڵ㲻�Ǹ��ڵ㣬�򽫸ýڵ�ĸ���32λ���ݸ�ʽ��Ϊ�ַ���,�ǲ��Ǻ�����һ�������װ׼������д���
		strText.Format(_T("%d"), pTVTipInfo->lParam);
	}

	// ��strText�ַ���������pTVTipInfo�ṹ�������pszText��Ա�У�����������ʾ����ΪstrText����ʾ��Ϣ   
	strcpy(pTVTipInfo->pszText, strText);
	*pResult = 0;
}

/*��ʾѡ�еĽڵ㡪����˵���Һ�������*/
void PAGE3::OnTvnSelchangedTreenet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString strText; // ���ڵ�ı�ǩ�ı��ַ���   

	// ��ȡ��ǰѡ�нڵ�ľ��   
	HTREEITEM hItem = m_TreeNet.GetSelectedItem();

	// ��ȡѡ�нڵ�ı�ǩ�ı��ַ���   
	strText = m_TreeNet.GetItemText(hItem);

	// ���ַ�����ʾ���༭����   
	SetDlgItemText(IDC_EDITNET, strText);
}

/*ˢ�°�ť*/
void PAGE3::OnBnClickedButtonnet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_TreeNet.DeleteAllItems();							//�������ǰ���нڵ�
	HTREEITEM hRoot;									//��������һ����
	hRoot = m_TreeNet.InsertItem(_T("��������"), 0, 0);//����������

	LPNETRESOURCE Ipnr = NULL;

	m_ListNet.DeleteAllItems();

	TreeProc(hRoot, Ipnr, 1);

	//չ���ҵĸ�~~~
	m_TreeNet.Expand(hRoot, TVE_EXPAND);
}

//�ȽϺ���������list����ĳһ�����򡪡���Ǹ��ʵ���̲�ס����
int CALLBACK PAGE3::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// �Ӳ�������ȡ����Ƚ�lc����������
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column);
	CString lp2 = lc->GetItemText(row2, sort_column);

	//������������
	//if (sort_column == 0)
	//{
	//	if (method)
	//		return atoi(lp1) - atoi(lp2);
	//	else
	//		return atoi(lp2) - atoi(lp1);
	//}
	//�����ַ�������
	//else
	{
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}


void PAGE3::OnLvnColumnclickListnet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sort_column = pNMLV->iSubItem;	//�������
	int count = m_ListNet.GetItemCount();	//list������
	for (int i = 0; i < count; i++)
	{
		//ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ����ȽϺ����ĵ�һ��������
		m_ListNet.SetItemData(i, i);
	}
	method = !method;		//��һ�ε���ı�����˳��
							//��list����
	m_ListNet.SortItems(
		MyCompareProc,			//�ȽϺ���
		(LPARAM)&m_ListNet);	//�ȽϺ����ĵ���������
	*pResult = 0;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>