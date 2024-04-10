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

//单向链表
typedef struct SLNode {
	//进程名
	char name[100];

	//持续的时间
	int duration;

	//结束的时间
	int endTime;

	//内存使用的情况
	int memory;

	//PID
	int PID;

	SLNode* next;
}SLNode, * SLinkList;

//双向链表
typedef struct DLNode {
	//进程名
	char name[100];

	//持续的时间
	int duration;

	//结束的时间
	int endTime;

	//内存的使用情况
	int memory;

	//PID
	int PID;

	DLNode* pre, * next;
}DLNode, * DLinkList;
//统计已结束进程
int UpdateTime(DLinkList&, DLinkList&, SLinkList&);

//刷新后更新进程
int UpdateProgarm(DLinkList&, DLinkList, SLinkList&);

//根据PID，在储存结束时间的链表中查找该进程
SLinkList LocateOverList(SLinkList&, const int);

//显示当前进程
void ShowArray_D(DLinkList, SLinkList);
//获取内存
int PrintMemoryInfo(DWORD);

//创建当前进程链表
int CreateList(DLinkList&);

//创建已结束进程链表
int CreateEndedList(SLinkList&, DLinkList);

//按内存大小给进程排序
int SortDList(DLinkList&);

//按照结束时间排序
int SortSList(SLinkList&);
//设置字体颜色
void Set_Color(int x);
int main() {
	//L为总进程表，cuttentL为当前进程表
	DLinkList L;
	DLinkList currentL;

	//S中存储已结束进程
	SLinkList S;

	//创建该程序执行时得到的最初的进程表，用于与当前进程比对，来获取已结束进程
	CreateList(L);

	//创建结束进程表
	CreateEndedList(S, L);

	//排序
	SortDList(L);
	Set_Color(2);
	//打印
	ShowArray_D(L, S);

	while (1) {
		//每过1s获取一次当前进程
		Sleep(1000);

		//清屏
		system("cls");

		//获取当前进程表
		CreateList(currentL);

		//排序
		SortDList(currentL);

		//调整结束时间及持续时间
		UpdateTime(L, currentL, S);

		//调整重新调用的程序及新调用的程序
		UpdateProgarm(L, currentL, S);

		//排序
		SortSList(S);

		//打印
		ShowArray_D(currentL, S);
	}

	system("pause");
	return 0;
}
//获取内存
int PrintMemoryInfo(DWORD processID)
{
	//API
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (hProcess == NULL)
		return 0;

	//GetProcessMemoryInfo()用于获取内存的使用情况
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		CloseHandle(hProcess);

		//pmc.WorkingSetSize就是程序在当前代码处的内存使用量
		return pmc.WorkingSetSize;
	}
}
//创建链表
int CreateList(DLinkList& D) {
	//头结点
	D = (DLinkList)malloc(sizeof(DLNode));
	D->pre = NULL;
	D->next = NULL;

	//p在循环建立链表时，指向最后结点
	//q为新结点
	DLinkList p = D, q;

	//存放进程信息的结构体
	PROCESSENTRY32 temp;
	temp.dwSize = sizeof(temp);

	//获取系统内的所有进程
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnapshot)
	{
		printf("未获得进程！\n");
		return 0;
	}

	//获取进程
	BOOL bMore = Process32First(hProcessSnapshot, &temp);
	while (bMore) {
		//获得当前进程的内存量
		int judge = PrintMemoryInfo(temp.th32ProcessID);
		if (judge > 0) {
			// Convert WCHAR to char
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, temp.szExeFile, -1, NULL, 0, NULL, NULL);
			char* tempName = new char[size_needed];
			WideCharToMultiByte(CP_UTF8, 0, temp.szExeFile, -1, tempName, size_needed, NULL, NULL);

			//新进程的内容赋给新结点，接在双向链表最后
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

	//清除hProcess句柄
	CloseHandle(hProcessSnapshot);
	return 1;
}
//创建结束链表
int CreateEndedList(SLinkList& S, DLinkList D)
{
	//把总进程链表所有内容赋给记录已结束进程链表
	S = (SLinkList)malloc(sizeof(SLNode));
	S->duration = 0;//总时间
	S->endTime = 0;//结束时间
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
//按照内存大小排序
int SortDList(DLinkList& D) {
	//统计结点数目
	int statisticNum = 0;
	DLinkList statistic = D->next;
	while (statistic) {
		statisticNum++;
		statistic = statistic->next;
	}

	//冒泡排序
	DLinkList q = D->next;
	DLinkList t = (DLinkList)malloc(sizeof(DLNode));
	//标记排序是否发生交换
	//若不发生交换
	//则排序完成
	int flag = 1;

	while (flag == 1 && statisticNum - 1 > 0)
	{
		q = D->next;
		//若没有发生交换
		//flag为0，则不会发生下一趟排序
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
//按照结束时间排序
int SortSList(SLinkList& S) {
	//记录结点数目
	int statisticNum = 0;
	SLinkList statistic = S->next;
	while (statistic) {
		statisticNum++;
		statistic = statistic->next;
	}

	//冒泡排序
	SLinkList q = S->next;
	SLinkList t = (SLinkList)malloc(sizeof(SLNode));
	//标记排序是否发生交换
	//若不发生交换
	//则排序完成
	int flag = 1;

	while (flag == 1 && statisticNum - 1 > 0)
	{
		q = S->next;
		//若没有发生交换
		//flag为0，则不会发生下一趟排序
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
//显示当前进程
void ShowArray_D(DLinkList D, SLinkList S) {
	Set_Color(2);
	cout.setf(ios::left);
	cout << setw(20) << "当前系统进程名" << '	' << "PID";
	cout.setf(ios::right, ios::left);
	cout << '	' << setw(17) << "内存使用情况" << '	' << "持续时间" << '	' << setw(20) << endl;
	cout << "----------------------------------------------------------------" << endl;

	DLinkList  p = D->next;
	SLinkList s = S->next;

	//打印当前进程链表的内容
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
		cout << setw(20) << "已结束进程名" << '	' << "PID";
		cout.setf(ios::right, ios::left);
		cout << '	' << setw(17) << "持续时间" << '	' << "结束时间" << '	' << setw(20) << endl;
		cout << "----------------------------------------------------------------" << endl;
	}

	//当链表未结束
	//已结束进程链表的结点的endTime值不为0，打印
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
//根据PID查找进程
SLinkList LocateOverList(SLinkList& S, const int PID)
{
	//在已结束进程中查找进程编号为PID的进程
	SLinkList p = S->next;
	while (p)
	{
		if (PID == p->PID)
			return p;
		p = p->next;
	}
	return NULL;
}
//统计已结束进程
int UpdateTime(DLinkList& L, DLinkList& currentL, SLinkList& S) {
	//判断有无找到未结束进程
	int judge;

	SLinkList p_S = S->next;
	DLinkList p_L = L->next, p_currentL;

	//头结点用来记录调试时间
	S->duration += 1;

	while (p_L) {
		//重置为1
		judge = 1;

		//寻找有无未结束进程
		p_currentL = currentL->next;
		while (p_currentL) {
			//该进程未结束
			if (p_currentL->PID == p_L->PID)
			{
				//找到，置为0
				judge = 0;
				break;
			}
			p_currentL = p_currentL->next;
		}

		//进程已结束
		if (judge)
		{
			//获取该结束进程在已结束进程链表的位置
			//更新结束时间
			p_S = LocateOverList(S, p_L->PID);

			//如果结束时间为0，更新结束时间
			//如果结束时间不为0，更新结束的持续时间
			if (p_S->endTime == 0) {
				p_S->endTime = S->duration;
			}
			else {
				p_S->duration += 1;
			}
		}

		//进程未结束
		//更新当前进程的运行的持续时间
		else {
			p_L->duration += 1;
			p_currentL->duration = p_L->duration;
		}

		p_L = p_L->next;
	}
	return 1;
}
//刷新后更新进程
int UpdateProgarm(DLinkList& L, DLinkList currentL, SLinkList& S)
{
	//判断有无找到新进程
	int judge;

	//p_S为
	//q_S用于接新进程结点(已结束进程链表)
	//temp_S为新进程的结点(已结束进程链表)
	SLinkList p_S = S->next, q_S = S->next, temp_S = (SLinkList)malloc(sizeof(SLNode));

	//p_L用于对比当前进程是否为新进程
	//p_currentL为当前进程表的指针
	//q_L用于接新进程结点(总进程链表)
	//temp_L为新进程的结点(总进程链表)
	DLinkList p_L = L->next, p_currentL = currentL->next, q_L = L->next, temp_L = (DLinkList)malloc(sizeof(DLNode));

	//遍历当前进程表
	while (p_currentL) {
		judge = 1;

		p_L = L->next;
		while (p_L) {
			//该进程已在进程表L中
			if (p_currentL->PID == p_L->PID)
			{
				judge = 0;
				break;
			}
			p_L = p_L->next;
		}

		//如果进程不在L中,将其添加到L,S表中
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
					//重新启用进程
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
//设置字体颜色
void Set_Color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	//此函数可控制字体颜色，颜色对应列表如下所示
	/*
	color(0);
	printf(“黑色\n”);
	color(1);
	printf(“蓝色\n”);
	color(2);
	printf(“绿色\n”);
	color(3);
	printf(“湖蓝色\n”);
	color(4);
	printf(“红色\n”);
	color(5);
	printf(“紫色\n”);
	color(6);
	printf(“黄色\n”);
	color(7);
	printf(“白色\n”);
	color(8);
	printf(“灰色\n”);
	color(9);
	printf(“淡蓝色\n”);
	color(10);
	printf(“淡绿色\n”);
	color(11);
	printf(“淡浅绿色\n”);
	color(12);
	printf(“淡红色\n”);
	color(13);
	printf(“淡紫色\n”);
	color(14);
	printf(“淡黄色\n”);
	color(15);
	printf(“亮白色\n”);
	在0-15范围修改的是字体的颜色超过15改变的是文本背景色
	*/
}