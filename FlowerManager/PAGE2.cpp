/*
PAGE2.cpp: �����ܡ�ҳ
���ߣ�1120151769 ��˼��
*/
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������<��˼��>

#include "stdafx.h"
#include "FlowerManager.h"
#include "PAGE2.h"
#include "afxdialogex.h"


// PAGE2 �Ի���


IMPLEMENT_DYNAMIC(PAGE2, CDialogEx)

PAGE2::PAGE2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE2, pParent)
{

}

PAGE2::~PAGE2()
{
}

void PAGE2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTPER, m_ListPer);
	DDX_Control(pDX, IDC_LISTPOWER, m_ListPower);
}


BEGIN_MESSAGE_MAP(PAGE2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONPER1, &PAGE2::OnBnClickedButtonper1)						//ˢ��
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTPER, &PAGE2::OnLvnColumnclickListper)			//��ϵͳ
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTPOWER, &PAGE2::OnLvnColumnclickListpower)		//�ŵ�Դ
END_MESSAGE_MAP()


// PAGE2 ��Ϣ�������


BOOL PAGE2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	method1 = FALSE;
	method2 = FALSE;

	//ϵͳ��Ϣ
	m_ListPer.InsertColumn(0, "����", NULL, 250, 50);
	m_ListPer.InsertColumn(1, "ֵ", NULL, 250, 50);

	//��Դ��Ϣ
	m_ListPower.InsertColumn(0, "����", NULL, 250, 50);
	m_ListPower.InsertColumn(1, "ֵ", NULL, 280, 50);

	ListProc();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

/*��ȡϵͳ�͵�ص�������Ϣ*/
void PAGE2::ListProc() 
{

	//ϵͳ������Ϣ
	PERFORMANCE_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	pi.cb = sizeof(pi);
	GetPerformanceInfo(&pi, sizeof(pi));

	//���ڹ淶�ַ���ʽ
	TCHAR* sz = new TCHAR[MAX_PATH];

	StrFormatByteSize(pi.cb, sz, MAX_PATH);
	AddItem(0, "PERFORMANCE_INFORMATION��С", sz);

	//�ύҳ��
	sprintf(sz, "%d ҳ", pi.CommitTotal);
	AddItem(0, "��ǰ�ύ��ҳ������", sz);
	sprintf(sz, "%d ҳ", pi.CommitLimit);
	AddItem(0, "��ǰ���ύ�����ҳ����", sz);
	sprintf(sz, "%d ҳ", pi.CommitPeak);
	AddItem(0, "��ʷ�ύҳ���ֵ", sz);

	//�����ڴ�
	sprintf(sz, "%d ҳ", pi.PhysicalTotal);
	AddItem(0, "��ҳ������������ڴ�", sz);
	sprintf(sz, "%d ҳ", pi.PhysicalAvailable);
	AddItem(0, "��ǰ���õ������ڴ�", sz);

	//Cache
	sprintf(sz, "%d ҳ", pi.SystemCache);
	AddItem(0, "Cache������", sz);

	//Kernel
	sprintf(sz, "%d ҳ", pi.KernelTotal);
	AddItem(0, "�ڴ�����", sz);
	sprintf(sz, "%d ҳ", pi.KernelPaged);
	AddItem(0, "��ҳ�ش�С", sz);
	sprintf(sz, "%d ҳ", pi.KernelNonpaged);
	AddItem(0, "�Ƿ�ҳ�ش�С", sz);

	//ҳ�Ĵ�С
	StrFormatByteSize(pi.PageSize, sz, MAX_PATH);
	AddItem(0, "ҳ�Ĵ�С", sz);

	//���
	sprintf(sz, "%d", pi.HandleCount);
	AddItem(0, "�򿪵ľ������", sz);

	//����
	sprintf(sz, "%d", pi.ProcessCount);
	AddItem(0, "���̸���", sz);

	//�߳�
	sprintf(sz, "%d", pi.ThreadCount);
	AddItem(0, "�̸߳���", sz);

	//��Դ������Ϣ
	//�����й�ϵͳ��Դ״̬����Ϣ
	SYSTEM_POWER_STATUS power;					
	ZeroMemory(&pi, sizeof(power));

	if (GetSystemPowerStatus(&power)) 
	{
		//������Դ״̬
		switch (power.ACLineStatus) 
		{
		case 0:
			sprintf(sz, "����");
			break;
		case 1:
			sprintf(sz, "����");
			break;
		case 255:
			sprintf(sz, "δ֪״̬");
			break;
		}
		AddItem(1, "��������Դ״̬", sz);

		//��س��״̬
		switch (power.BatteryFlag) 
		{
		case 1:
			sprintf(sz, "�ߣ���������66%");
			break;
		case 2:
			sprintf(sz, "�ͣ���������33%");
			break;
		case 4:
			sprintf(sz, "�������أ���������5%");
			break;
		case 8:
			sprintf(sz, "�����");
			break;
		case 125:
			sprintf(sz, "��ϵͳ���");
			break;
		case 255:
			sprintf(sz, "δ֪״̬���޷���ȡ���״̬");
			break;
		}
		AddItem(1, "��س��״̬", sz);

		//ʣ���������İٷֱȣ��ó�Ա������0��100֮���һ��ֵ��������״̬δ֪��ֵ
		sprintf(sz, "%d%%", power.BatteryLifePercent);
		AddItem(1, "ʣ������ٷֱ�", sz);

		//ʣ�������������������ʣ������δ֪���豸���ӵ�������Դ����Ϊ-1
		if (power.BatteryLifeTime == -1)
			sprintf(sz, "ʣ������δ֪/�豸���ӵ�������Դ");
		else
			sprintf(sz, "%d ��", power.BatteryLifeTime);
		AddItem(1, "ʣ��������", sz);

		//��ȫ���ʱ�ĵ��������������������������δ֪���豸���ӵ�������Դ����Ϊ-1
		if (power.BatteryFullLifeTime = -1)
			sprintf(sz, "�����������δ֪/�豸���ӵ�������Դ");
		else
			sprintf(sz, "%d ��", power.BatteryFullLifeTime);
		AddItem(1, "��ȫ���ʱ�ĵ������", sz);
	}
	else 
	{
		GetLastError();
	}
}

/*��List��д������ֵ*/
void PAGE2::AddItem(bool flag, TCHAR* name, TCHAR* value) 
{
	int nItemNum;
	switch (flag) 
	{
		//дϵͳ����
	case 0:
		nItemNum = m_ListPer.GetItemCount();
		m_ListPer.InsertItem(nItemNum, name);
		m_ListPer.SetItemText(nItemNum, 1, value);
		break;
		//д�������
	case 1:
		nItemNum = m_ListPower.GetItemCount();
		m_ListPower.InsertItem(nItemNum, name);
		m_ListPower.SetItemText(nItemNum, 1, value);
		break;
	}
}

//ˢ��
void PAGE2::OnBnClickedButtonper1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListPer.DeleteAllItems();		//���ϵͳ����List����
	m_ListPower.DeleteAllItems();	//��յ������List����
	ListProc();						//����д������
}

//�ȽϺ���������ϵͳlist����ĳһ������
int CALLBACK PAGE2::MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// �Ӳ�������ȡ����Ƚ�lc����������
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column1);
	CString lp2 = lc->GetItemText(row2, sort_column1);

	//������������(�е㲻�淶����Ϊδ���ǵ�λ���Ҿ������⹦��)
	if (sort_column1 == 1)
	{
		if (method1)
			return atoi(lp1) - atoi(lp2);
		else
			return atoi(lp2) - atoi(lp1);
	}
	//�������ַ�������
	else
	{
		if (method1)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//�ȽϺ��������ڵ�Դҳlist����ĳһ������
int CALLBACK PAGE2::MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	// �Ӳ�������ȡ����Ƚ�lc����������
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column2);
	CString lp2 = lc->GetItemText(row2, sort_column2);

	//�����ַ�������
	{
		if (method2)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	return 0;
}

//��Ӧϵͳlist����
void PAGE2::OnLvnColumnclickListper(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sort_column1 = pNMLV->iSubItem;				//�����������
	int count = m_ListPer.GetItemCount();		//list������
	for (int i = 0; i < count; i++)
	{
		//ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ����ȽϺ����ĵ�һ��������
		m_ListPer.SetItemData(i, i);
	}
	method1 = !method1;						//��һ�ε���ı�����˳��
	//��list����
	m_ListPer.SortItems(
		MyCompareProc1,						//�ȽϺ���
		(LPARAM)&m_ListPer);				//�ȽϺ����ĵ���������

	*pResult = 0;
}

//��Ӧ��Դ����list����
void PAGE2::OnLvnColumnclickListpower(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sort_column2 = pNMLV->iSubItem;				//�������
	int count = m_ListPower.GetItemCount();		//list������
	for (int i = 0; i < count; i++)
	{
		//ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ����ȽϺ����ĵ�һ��������
		m_ListPower.SetItemData(i, i);
	}
	method2 = !method2;						//��һ�ε���ı�����˳��
	//��list����
	m_ListPower.SortItems(
		MyCompareProc2,						//�ȽϺ���
		(LPARAM)&m_ListPower);				//�ȽϺ����ĵ���������

	*pResult = 0;
}
//����������������������������������������������������������������������������������������������������������������������������������������������������������������������������</��˼��>