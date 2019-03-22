/*
PAGE5.cpp: ���ļ�����ҳ
���ߣ�1120151764 ������
	 1120151775 ��ޱ
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE5.h"
#include "afxdialogex.h"
#include "ChooseExtension.h"
#include <regex>  
#include <string>  
#include <vector>  
#include <iostream>  

int sort_column_p5; // ��¼�������
bool method_p5 = false; // ��¼�ȽϷ���

const int BUFSIZE = 4096;

//Ҫƥ���ļ����͵�������ʽ
char* reg[33] = {
	".*\\.syd", ".*\\.~.*", "~.*\\..*", ".*\\.---", ".*\\.\\^.*",
	".*\\.\\?\\?~",  ".*\\.\\?\\?\\$", ".*\\.tmp", ".*\\._mp", ".*\\.spc",
	".*\\.cdr_", ".*\\.#Res", ".*\\.%%%", ".*\\.@@@", ".*\\.\\$\\$\\$",
	"mscreate\\.dir", ".*\\.chk", "chklist\\..*", ".*\\.gid", ".*\\.fts",
	".*\\.ftg", ".*\\.ms", ".*\\.old", ".*\\.bak", ".*\\.prv",
	".*\\.wpk", ".*\\.xlk", ".*\\.pch", ".*\\.dmp", ".*\\.diz",
	"Thumbs\\.db", ".*\\.err", ".*log\\.txt"
};
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
struct ext
{
	string name;
	string description;
	BOOL state;
};
ext extend[33];
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
// PAGE5 �Ի���

IMPLEMENT_DYNAMIC(PAGE5, CDialogEx)

PAGE5::PAGE5(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE5, pParent)
{

}

PAGE5::~PAGE5()
{
}

void PAGE5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEROUTE, m_edit_fileroute);
	DDX_Control(pDX, IDC_LIST_PAGE5, m_list_page5);
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
	DDX_Control(pDX, IDC_EDIT_FILETYPE, m_edit_filetype);
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
BEGIN_MESSAGE_MAP(PAGE5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILEROUTE, &PAGE5::OnBnClickedButtonFileroute)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &PAGE5::OnBnClickedButtonSearch)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_PAGE5, &PAGE5::OnLvnColumnclickListPage5)
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
	ON_BN_CLICKED(IDC_BUTTON_FILETYPE, &PAGE5::OnBnClickedButtonFiletype)
	ON_BN_CLICKED(IDC_CHECK_CHOOSEALL_PAGE5, &PAGE5::OnBnClickedCheckChooseallPage5)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &PAGE5::OnBnClickedButtonClean)
END_MESSAGE_MAP()
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>

// PAGE5 ��Ϣ�������
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
//ͨ��CFolderPickerDialog����ļ�·��
void PAGE5::OnBnClickedButtonFileroute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog fd(
		NULL,	//��ʼ�ļ���
		0,		//�������Զ���Ի����е�һ��������־�����
		this,	//ָ��Ի������ĸ����ڻ������ߴ��ڵ�ָ��
		0);		//OPENFILENAME �ṹ�Ĵ�С

	if (fd.DoModal() == IDOK)
	{
		CString des;	//���ص�·���ַ���
		des = fd.GetPathName();
		SetDlgItemText(IDC_EDIT_FILEROUTE, des);	//���ַ�������edit��
													//MessageBox(des);
	}
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
void insertExtend(int number, string name, string description, BOOL state)
{
	extend[number].name = name;
	extend[number].description = description;
	extend[number].state = state;
}

void initExtend()
{
	insertExtend(0, "*.syd", "��ʱ�ļ�", false);
	insertExtend(1, "*.~*", "��ʱ�ļ�", false);
	insertExtend(2, "~*.*", "��ʱ�ļ�", false);
	insertExtend(3, "*.---", "��ʱ�ļ�", false);
	insertExtend(4, "*.^*", "��ʱ�ļ�", false);
	insertExtend(5, "*.??~", "��ʱ�ļ�", false);
	insertExtend(6, "*.??$", "��ʱ�ļ�", false);
	insertExtend(7, "*.tmp", "��ʱ�ļ�", false);
	insertExtend(8, "*._mp", "��ʱ�ļ�", false);
	insertExtend(9, "*.spc", "WordPerfect��ʱ�ļ�", false);
	insertExtend(10, "*.cdr_", "Corel DRAW��ʱ�ļ�", false);
	insertExtend(11, "*.#Res", "Mac Photoshop��ʱ�ļ�", false);
	insertExtend(12, "*.%%%", "��װ����ʱ�ļ�", false);
	insertExtend(13, "*.@@@", "��װ����ʱ�ļ�", false);
	insertExtend(14, "*.$$$", "��װ����ʱ�ļ�", false);
	insertExtend(15, "mscreate.dir", "��װ����ʱ�ļ�", false);
	insertExtend(16, "*.chk", "��ʧ�صĻָ��ļ�", false);
	insertExtend(17, "chklist.*", "��ʧ�صĻָ��ļ�", false);
	insertExtend(18, "*.gid", "������֧�ֵ���ʱ�ļ�", false);
	insertExtend(19, "*.fts", "������֧�ֵ���ʱ�ļ�", false);
	insertExtend(20, "*.ftg", "������֧�ֵ���ʱ�ļ�", false);
	insertExtend(21, "*.ms", "΢���Ʒ�����ļ�", false);
	insertExtend(22, "*.old", "�����ļ�", false);
	insertExtend(23, "*.bak", "�����ļ�", false);
	insertExtend(24, "*.prv", "�����ļ�", false);
	insertExtend(25, "*.wbk", "Word�ı����ļ�", false);
	insertExtend(26, "*.xlk", "Excel�ı����ļ�", false);
	insertExtend(27, "*.pch", "Ԥ����ͷ�ļ�", false);
	insertExtend(28, "*.dmp", "�ڴ�ת���ļ�", false);
	insertExtend(29, "*.diz", "zip�ĵ�˵���ļ�", false);
	insertExtend(30, "Thumbs.db", "ͼƬԤ������ͼ�ļ�", false);
	insertExtend(31, "*.err", "������־�ļ�", false);
	insertExtend(32, "*.log.txt", "������־�ļ�", false);
}


BOOL PAGE5::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	initExtend();

	m_list_page5.SetExtendedStyle(
		LVS_EX_GRIDLINES |			//���Ʊ��
		LVS_EX_FULLROWSELECT |		//ѡ��Ϊһ����
		LVS_EX_CHECKBOXES);			//ÿ��ǰ����checkbox
	m_list_page5.InsertColumn(0, "�ļ�·��", NULL, 250, 50);
	m_list_page5.InsertColumn(1, "�ļ�����", NULL, 100, 50);
	m_list_page5.InsertColumn(2, "�ļ�����", NULL, 150, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void PAGE5::OnBnClickedButtonFiletype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ChooseExtension* CXdlg;
	CXdlg = new ChooseExtension(this);

	for (int i = 0; i < 33; i++)
	{
		CXdlg->extState[i] = extend[i].state;
	}

	CXdlg->DoModal();

	string str = "";
	for (int i = 0; i < 33; i++)
	{
		extend[i].state = CXdlg->extState[i];
		if (extend[i].state)
		{
			str += "\"";
			str += extend[i].name;
			str += "\" ";
		}
	}

	TCHAR *extstring = new TCHAR[500];
	_stprintf_s(extstring, 500, "%s", str.c_str());
	SetDlgItemText(IDC_EDIT_FILETYPE, extstring);	//���ַ�������edit��
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
//�ж��Ƿ�Ϊ��Ҫ�����͵��ļ�
int isWantedFileType(char* filename)
{
	for (int i = 0; i < 33; i++)
	{
		//����ÿ���û�ѡ���Ҫ������ļ�����
		if (extend[i].state)
		{
			std::string pattern{ reg[i] };
			std::regex re(pattern);		//������ʽ
			std::string str = filename;	//��ƥ����ļ���
			bool ret = std::regex_match(str, re);	//����ƥ����
			if (ret)	//���ƥ�䵽��ǰ�ļ�����
			{
				return i;
			}
		}
	}
	return -1;
}

//�ж��Ƿ�ΪĿ¼
static BOOL IsChildDir(WIN32_FIND_DATA *lpFindData)
{
	return (
		((lpFindData->dwFileAttributes &
			FILE_ATTRIBUTE_DIRECTORY) != 0) &&	//�ļ����Բ�ΪĿ¼
			(lstrcmp(lpFindData->cFileName, __TEXT(".")) != 0) &&	//���ļ�������ǰĿ¼
		(lstrcmp(lpFindData->cFileName, __TEXT("..")) != 0));	//���ļ���������һĿ¼
}

//����·��ָ���ļ���
void PAGE5::searchFile(char * sourceFile)
{
	WIN32_FIND_DATA FindFileData;
	char src[BUFSIZE];	//����Դ�ļ���ַ
	lstrcpy(src, sourceFile);	//����ǰԴ�ļ�����ַ���Ƶ�Դ�ļ���ַ��
	lstrcat(src, "\\*");	//Դ��ַ׷��\*������Ŀ¼�������ļ�
	HANDLE hFind = FindFirstFile(src,	//���ҵ�һ���ļ�
		&FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)	//�ҵ����ļ�
	{
		//ѭ��������һ�ļ���ֱ������
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			//��Դ��ַ�е�\*ȥ�������˵���һ�ļ���
			memset(src, 0, sizeof(src));	//Դ��ַ����
			lstrcpy(src, sourceFile);
			lstrcat(src, "\\");
			//��Դ��ַ��Ŀ���ַ����׷���ҵ����ļ���
			lstrcat(src, FindFileData.cFileName);
			if (IsChildDir(&FindFileData))	//����ҵ���Ŀ¼
			{
				searchFile(src);	//������Ŀ¼�ݹ���Ҹ���
			}
			else	//����ҵ������ļ�
			{
				//�ж��Ƿ�ΪҪ������ļ����ͣ��������ͱ��
				int num = isWantedFileType(FindFileData.cFileName);
				if (num != -1)
				{
					//����б��������
					int nItemNum = m_list_page5.GetItemCount();

					//�����ļ����ͺ��ļ������ַ����������и�ʽת��
					TCHAR *type = new TCHAR[MAX_PATH];
					_stprintf_s(type, MAX_PATH, "%s", extend[num].name.c_str());
					TCHAR *description = new TCHAR[MAX_PATH];
					_stprintf_s(description, MAX_PATH, "%s", extend[num].description.c_str());

					//�б��������
					m_list_page5.InsertItem(nItemNum, src);
					m_list_page5.SetItemText(nItemNum, 1, type);
					m_list_page5.SetItemText(nItemNum, 2, description);
				}
			}
			//Դ��ַ��Ŀ���ַ�����˵���һ�ļ���
			lstrcpy(src, sourceFile);
			lstrcat(src, "\\");
		}
	}
}

//ɨ�谴ť
void PAGE5::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list_page5.DeleteAllItems();	//����б�
	CString csX;
	m_edit_fileroute.GetWindowText(csX);	//����ļ�·��
	char* sourceFile = (char*)csX.GetBuffer(0);	//��ʽת��
												//�����ļ�ɨ��
	searchFile(sourceFile);

	MessageBox(		//������ʾ��
		_T("ɨ����ɣ�"),	//��������
		_T("��ʾ"),		//��������
		MB_ICONASTERISK);	//��ʾͼ��
	return;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��ޱ>
//ȫѡcheckbox�Ĳ���
void PAGE5::OnBnClickedCheckChooseallPage5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_CHOOSEALL_PAGE5);
	int state = pBtn->GetCheck();
	if (state == 0)
	{
		for (int i = 0; i<m_list_page5.GetItemCount(); i++)
		{
			m_list_page5.SetCheck(i, false);
		}
	}
	else
	{
		for (int i = 0; i<m_list_page5.GetItemCount(); i++)
		{
			m_list_page5.SetCheck(i, true);
		}
	}
}

//�����ļ���ť
void PAGE5::OnBnClickedButtonClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_list_page5.GetItemCount() == 0)
	{
		MessageBox(		//������ʾ��
			_T("û�п������ļ���"),	//��������
			_T("��ʾ"),		//��������
			MB_ICONASTERISK);	//��ʾͼ��
		return;
	}

	int cnt = 0;	//ѡ�������ļ���

	for (int i = m_list_page5.GetItemCount() - 1; i >= 0; i--)
	{
		if (m_list_page5.GetCheck(i) == TRUE)
		{
			cnt++;
			char FileName[260];
			memset(FileName, 0, 260);
			m_list_page5.GetItemText(i, 0, FileName, 259);
			DeleteFile(FileName);
			m_list_page5.DeleteItem(i);
		}
	}

	if (cnt == 0)	//δ��ѡ������
	{
		MessageBox(		//������ʾ��
			_T("��ѡ�������"),	//��������
			_T("��ʾ"),		//��������
			MB_ICONASTERISK);	//��ʾͼ��
		return;
	}

	string str = "������ɣ�\n������ ";
	str += to_string(cnt);
	str += " ���ļ�";

	MessageBox(		//������ʾ��
		_T(str.c_str()),	//��������
		_T("��ʾ"),		//��������
		MB_ICONASTERISK);	//��ʾͼ��
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��ޱ>
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<������>
//�ȽϺ���������list����ĳһ������
int CALLBACK PAGE5::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// �Ӳ�������ȡ����Ƚ�lc����������
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column_p5);
	CString lp2 = lc->GetItemText(row2, sort_column_p5);

	//�����ַ�������
	//�����������
	if (method_p5)
		return lp1.CompareNoCase(lp2);
	else
		return lp2.CompareNoCase(lp1);
	return 0;
}

//���list��ĳ����ͷ��������������
void PAGE5::OnLvnColumnclickListPage5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sort_column_p5 = pNMLV->iSubItem;	//�������
	int count = m_list_page5.GetItemCount();	//list������
	for (int i = 0; i < count; i++)
	{
		//ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ����ȽϺ����ĵ�һ��������
		m_list_page5.SetItemData(i, i);
	}
	method_p5 = !method_p5;		//��һ�ε���ı�����˳��
								//��list����
	m_list_page5.SortItems(
		MyCompareProc,			//�ȽϺ���
		(LPARAM)&m_list_page5);	//�ȽϺ����ĵ���������
	*pResult = 0;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</������>