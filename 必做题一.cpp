#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdio>
#include<windows.h>
#include<TLHELP32.h>
#include<iomanip>
#include<string>
#include"Psapi.h"
#pragma comment(lib,"Psapi.lib")
using namespace std;

//��������
typedef struct SLNode {
	//������
	char name[100];

	//������ʱ��
	int duration;

	//������ʱ��
	int endTime;

	//�ڴ�ʹ�õ����
	int memory;

	//PID
	int PID;

	SLNode* next;
}SLNode, * SLinkList;

//˫������
typedef struct DLNode {
	//������
	char name[100];

	//������ʱ��
	int duration;

	//������ʱ��
	int endTime;

	//�ڴ��ʹ�����
	int memory;

	//PID
	int PID;

	DLNode* pre, * next;
}DLNode, * DLinkList;
//ͳ���ѽ�������
int UpdateTime(DLinkList&, DLinkList&, SLinkList&);

//ˢ�º���½���
int UpdateProgarm(DLinkList&, DLinkList, SLinkList&);

//����PID���ڴ������ʱ��������в��Ҹý���
SLinkList LocateOverList(SLinkList&, const int);

//��ʾ��ǰ����
void ShowArray_D(DLinkList, SLinkList);
//��ȡ�ڴ�
int PrintMemoryInfo(DWORD);

//������ǰ��������
int CreateList(DLinkList&);

//�����ѽ�����������
int CreateEndedList(SLinkList&, DLinkList);

//���ڴ��С����������
int SortDList(DLinkList&);

//���ս���ʱ������
int SortSList(SLinkList&);
//����������ɫ
void Set_Color(int x);
int main() {
	//LΪ�ܽ��̱�cuttentLΪ��ǰ���̱�
	DLinkList L;
	DLinkList currentL;

	//S�д洢�ѽ�������
	SLinkList S;

	//�����ó���ִ��ʱ�õ�������Ľ��̱������뵱ǰ���̱ȶԣ�����ȡ�ѽ�������
	CreateList(L);

	//�����������̱�
	CreateEndedList(S, L);

	//����
	SortDList(L);
	Set_Color(2);
	//��ӡ
	ShowArray_D(L, S);

	while (1) {
		//ÿ��1s��ȡһ�ε�ǰ����
		Sleep(1000);

		//����
		system("cls");

		//��ȡ��ǰ���̱�
		CreateList(currentL);

		//����
		SortDList(currentL);

		//��������ʱ�估����ʱ��
		UpdateTime(L, currentL, S);

		//�������µ��õĳ����µ��õĳ���
		UpdateProgarm(L, currentL, S);

		//����
		SortSList(S);

		//��ӡ
		ShowArray_D(currentL, S);
	}

	system("pause");
	return 0;
}
//��ȡ�ڴ�
int PrintMemoryInfo(DWORD processID)
{
	//API
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (hProcess == NULL)
		return 0;

	//GetProcessMemoryInfo()���ڻ�ȡ�ڴ��ʹ�����
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		CloseHandle(hProcess);

		//pmc.WorkingSetSize���ǳ����ڵ�ǰ���봦���ڴ�ʹ����
		return pmc.WorkingSetSize;
	}
}
//��������
int CreateList(DLinkList& D) {
	//ͷ���
	D = (DLinkList)malloc(sizeof(DLNode));
	D->pre = NULL;
	D->next = NULL;

	//p��ѭ����������ʱ��ָ�������
	//qΪ�½��
	DLinkList p = D, q;

	//��Ž�����Ϣ�Ľṹ��
	PROCESSENTRY32 temp;
	temp.dwSize = sizeof(temp);

	//��ȡϵͳ�ڵ����н���
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnapshot)
	{
		printf("δ��ý��̣�\n");
		return 0;
	}

	//��ȡ����
	BOOL bMore = Process32First(hProcessSnapshot, &temp);
	while (bMore) {
		//��õ�ǰ���̵��ڴ���
		int judge = PrintMemoryInfo(temp.th32ProcessID);
		if (judge > 0) {
			// Convert WCHAR to char
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, temp.szExeFile, -1, NULL, 0, NULL, NULL);
			char* tempName = new char[size_needed];
			WideCharToMultiByte(CP_UTF8, 0, temp.szExeFile, -1, tempName, size_needed, NULL, NULL);

			//�½��̵����ݸ����½�㣬����˫���������
			q = (DLinkList)malloc(sizeof(DLNode));
			q->memory = judge / 1024;
			strcpy_s(q->name, sizeof(q->name), tempName);
			q->PID = temp.th32ProcessID;
			q->duration = 0;
			p->next = q;
			q->pre = p;
			q->next = NULL;
			p = q;

			delete[] tempName;
		}
		bMore = Process32Next(hProcessSnapshot, &temp);
	}

	//���hProcess���
	CloseHandle(hProcessSnapshot);
	return 1;
}
//������������
int CreateEndedList(SLinkList& S, DLinkList D)
{
	//���ܽ��������������ݸ�����¼�ѽ�����������
	S = (SLinkList)malloc(sizeof(SLNode));
	S->duration = 0;//��ʱ��
	S->endTime = 0;//����ʱ��
	DLinkList  p_D = D->next;
	SLinkList p_S = S, q_S = (SLinkList)malloc(sizeof(SLNode));
	while (p_D) {
		q_S = (SLinkList)malloc(sizeof(SLNode));
		strcpy_s(q_S->name, strlen(p_D->name) + 1, p_D->name);
		q_S->PID = p_D->PID;
		q_S->duration = 0;
		q_S->endTime = 0;
		p_S->next = q_S;
		p_S = p_S->next;
		p_D = p_D->next;
	}
	q_S->next = NULL;
	return 1;
}
//�����ڴ��С����
int SortDList(DLinkList& D) {
	//ͳ�ƽ����Ŀ
	int statisticNum = 0;
	DLinkList statistic = D->next;
	while (statistic) {
		statisticNum++;
		statistic = statistic->next;
	}

	//ð������
	DLinkList q = D->next;
	DLinkList t = (DLinkList)malloc(sizeof(DLNode));
	//��������Ƿ�������
	//������������
	//���������
	int flag = 1;

	while (flag == 1 && statisticNum - 1 > 0)
	{
		q = D->next;
		//��û�з�������
		//flagΪ0���򲻻ᷢ����һ������
		flag = 0;
		for (int i = 1; i < statisticNum; i++)
		{
			if (q->memory < q->next->memory)
			{
				flag = 1;
				strcpy_s(t->name, strlen(q->name) + 1, q->name);
				t->memory = q->memory;
				t->PID = q->PID;
				t->duration = q->duration;
				strcpy_s(q->name, strlen(q->next->name) + 1, q->next->name);
				q->memory = q->next->memory;
				q->PID = q->next->PID;
				q->duration = q->next->duration;
				strcpy_s(q->next->name, strlen(t->name) + 1, t->name);
				q->next->memory = t->memory;
				q->next->PID = t->PID;
				q->next->duration = t->duration;
			}
			q = q->next;
		}
		statisticNum--;
	}
	return 1;
}
//���ս���ʱ������
int SortSList(SLinkList& S) {
	//��¼�����Ŀ
	int statisticNum = 0;
	SLinkList statistic = S->next;
	while (statistic) {
		statisticNum++;
		statistic = statistic->next;
	}

	//ð������
	SLinkList q = S->next;
	SLinkList t = (SLinkList)malloc(sizeof(SLNode));
	//��������Ƿ�������
	//������������
	//���������
	int flag = 1;

	while (flag == 1 && statisticNum - 1 > 0)
	{
		q = S->next;
		//��û�з�������
		//flagΪ0���򲻻ᷢ����һ������
		flag = 0;
		for (int i = 1; i < statisticNum; i++)
		{
			if (q->endTime < q->next->endTime)
			{
				flag = 1;
				strcpy_s(t->name, strlen(q->name) + 1, q->name);
				t->endTime = q->endTime;
				t->PID = q->PID;
				t->duration = q->duration;
				strcpy_s(q->name, strlen(q->next->name) + 1, q->next->name);
				q->endTime = q->next->endTime;
				q->PID = q->next->PID;
				q->duration = q->next->duration;
				strcpy_s(q->next->name, strlen(t->name) + 1, t->name);
				q->next->endTime = t->endTime;
				q->next->PID = t->PID;
				q->next->duration = t->duration;
			}
			q = q->next;
		}
		statisticNum--;
	}
	return 1;
}
//��ʾ��ǰ����
void ShowArray_D(DLinkList D, SLinkList S) {
	Set_Color(2);
	cout.setf(ios::left);
	cout << setw(20) << "��ǰϵͳ������" << '	' << "PID";
	cout.setf(ios::right, ios::left);
	cout << '	' << setw(17) << "�ڴ�ʹ�����" << '	' << "����ʱ��" << '	' << setw(20) << endl;
	cout << "----------------------------------------------------------------" << endl;

	DLinkList  p = D->next;
	SLinkList s = S->next;

	//��ӡ��ǰ�������������
	while (p) {
		char* nameSave = p->name;
		for (int i = 0; i < 20; i++) {
			cout << nameSave[i];
			if (nameSave[i] == '\0') {
				for (int j = i; j < 20; j++) {
					cout << " ";
				}
				break;
			}
		}

		cout.setf(ios::left);
		cout << '	' << p->PID;

		cout.setf(ios::right, ios::left);
		cout << '	' << setw(15) << p->memory << "KB";
		if (p->duration < 60)
			cout << '	' << p->duration << "s" << endl;
		if (p->duration >= 60)
			cout << '	' << p->duration / 60 << "m  " << p->duration % 60 << "s" << endl;

		p = p->next;
	}
	cout << endl;

	if (s) {
		Set_Color(4);
		cout.setf(ios::left);
		cout << setw(20) << "�ѽ���������" << '	' << "PID";
		cout.setf(ios::right, ios::left);
		cout << '	' << setw(17) << "����ʱ��" << '	' << "����ʱ��" << '	' << setw(20) << endl;
		cout << "----------------------------------------------------------------" << endl;
	}

	//������δ����
	//�ѽ�����������Ľ���endTimeֵ��Ϊ0����ӡ
	while (s && s->endTime != 0) {
		char* nameSave1 = s->name;
		for (int i = 0; i < 20; i++) {
			cout << nameSave1[i];
			if (nameSave1[i] == '\0') {
				for (int j = i; j < 20; j++) {
					cout << " ";
				}
				break;
			}
		}

		cout.setf(ios::left);
		cout << '\t' << s->PID;

		cout.setf(ios::right, ios::left);
		if (s->duration < 60)
			cout << '	' << setw(15) << s->duration << "s";
		if (s->duration >= 60)
			cout << '	' << setw(12) << s->duration / 60 << "m  " << s->duration % 60 << "s";


		cout.setf(ios::left, ios::right);

		if (s->endTime < 60)
			cout << '	' << s->endTime << "s" << endl;
		if (s->endTime >= 60)
			cout << '	' << s->endTime / 60 << "m  " << s->endTime % 60 << "s" << endl;
		s = s->next;

	}
}
//����PID���ҽ���
SLinkList LocateOverList(SLinkList& S, const int PID)
{
	//���ѽ��������в��ҽ��̱��ΪPID�Ľ���
	SLinkList p = S->next;
	while (p)
	{
		if (PID == p->PID)
			return p;
		p = p->next;
	}
	return NULL;
}
//ͳ���ѽ�������
int UpdateTime(DLinkList& L, DLinkList& currentL, SLinkList& S) {
	//�ж������ҵ�δ��������
	int judge;

	SLinkList p_S = S->next;
	DLinkList p_L = L->next, p_currentL;

	//ͷ���������¼����ʱ��
	S->duration += 1;

	while (p_L) {
		//����Ϊ1
		judge = 1;

		//Ѱ������δ��������
		p_currentL = currentL->next;
		while (p_currentL) {
			//�ý���δ����
			if (p_currentL->PID == p_L->PID)
			{
				//�ҵ�����Ϊ0
				judge = 0;
				break;
			}
			p_currentL = p_currentL->next;
		}

		//�����ѽ���
		if (judge)
		{
			//��ȡ�ý����������ѽ������������λ��
			//���½���ʱ��
			p_S = LocateOverList(S, p_L->PID);

			//�������ʱ��Ϊ0�����½���ʱ��
			//�������ʱ�䲻Ϊ0�����½����ĳ���ʱ��
			if (p_S->endTime == 0) {
				p_S->endTime = S->duration;
			}
			else {
				p_S->duration += 1;
			}
		}

		//����δ����
		//���µ�ǰ���̵����еĳ���ʱ��
		else {
			p_L->duration += 1;
			p_currentL->duration = p_L->duration;
		}

		p_L = p_L->next;
	}
	return 1;
}
//ˢ�º���½���
int UpdateProgarm(DLinkList& L, DLinkList currentL, SLinkList& S)
{
	//�ж������ҵ��½���
	int judge;

	//p_SΪ
	//q_S���ڽ��½��̽��(�ѽ�����������)
	//temp_SΪ�½��̵Ľ��(�ѽ�����������)
	SLinkList p_S = S->next, q_S = S->next, temp_S = (SLinkList)malloc(sizeof(SLNode));

	//p_L���ڶԱȵ�ǰ�����Ƿ�Ϊ�½���
	//p_currentLΪ��ǰ���̱��ָ��
	//q_L���ڽ��½��̽��(�ܽ�������)
	//temp_LΪ�½��̵Ľ��(�ܽ�������)
	DLinkList p_L = L->next, p_currentL = currentL->next, q_L = L->next, temp_L = (DLinkList)malloc(sizeof(DLNode));

	//������ǰ���̱�
	while (p_currentL) {
		judge = 1;

		p_L = L->next;
		while (p_L) {
			//�ý������ڽ��̱�L��
			if (p_currentL->PID == p_L->PID)
			{
				judge = 0;
				break;
			}
			p_L = p_L->next;
		}

		//������̲���L��,������ӵ�L,S����
		if (judge)
		{
			do {
				q_L = q_L->next;
			} while (q_L->next);
			temp_L = (DLinkList)malloc(sizeof(DLNode));
			temp_L->PID = p_currentL->PID;
			temp_L->memory = p_currentL->memory;
			temp_L->duration = 0;
			strcpy_s(temp_L->name, p_currentL->name);
			q_L->next = temp_L;
			temp_L->next = NULL;
			temp_L->pre = q_L;


			do {
				q_S = q_S->next;
			} while (q_S->next);
			temp_S = (SLinkList)malloc(sizeof(SLNode));
			temp_S->PID = p_currentL->PID;
			temp_S->duration = 0;
			temp_S->endTime = 0;
			strcpy_s(temp_S->name, p_currentL->name);
			q_S->next = temp_S;
			temp_S->next = NULL;
		}

		else {
			p_S = S->next;
			while (p_S)
			{
				if (p_currentL->PID == p_S->PID && p_S->endTime != 0)
				{
					//�������ý���
					p_S->endTime = 0;

					p_currentL->duration = p_L->duration = 0;
					break;
				}
				p_S = p_S->next;
			}
		}

		p_currentL = p_currentL->next;
	}
	return 1;
}
//����������ɫ
void Set_Color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	//�˺����ɿ���������ɫ����ɫ��Ӧ�б�������ʾ
	/*
	color(0);
	printf(����ɫ\n��);
	color(1);
	printf(����ɫ\n��);
	color(2);
	printf(����ɫ\n��);
	color(3);
	printf(������ɫ\n��);
	color(4);
	printf(����ɫ\n��);
	color(5);
	printf(����ɫ\n��);
	color(6);
	printf(����ɫ\n��);
	color(7);
	printf(����ɫ\n��);
	color(8);
	printf(����ɫ\n��);
	color(9);
	printf(������ɫ\n��);
	color(10);
	printf(������ɫ\n��);
	color(11);
	printf(����ǳ��ɫ\n��);
	color(12);
	printf(������ɫ\n��);
	color(13);
	printf(������ɫ\n��);
	color(14);
	printf(������ɫ\n��);
	color(15);
	printf(������ɫ\n��);
	��0-15��Χ�޸ĵ����������ɫ����15�ı�����ı�����ɫ
	*/
}