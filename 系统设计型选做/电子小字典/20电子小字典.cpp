#include<iostream>
#include<fstream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;
typedef struct node
{
	bool is_word;//记录是否是单词的尾字母
	char data;//当前节点数据
	string translation;//汉译
	node* next[26];//子节点指针
	int num;//子结点个数
	node()//构造函数
	{
	    memset(next, NULL, sizeof(next));
		num = 0;
		is_word = false;
	}
}node;
node* root = new node;//根节点声明
bool is_lawful(string s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] > 'z' || s[i] < 'a')
			return false;
		i++;
	}
	return true;
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

void add(string tran, string s, node* t, int d)
{
	if (t->next[int(s[d] - 'a')] == NULL)//该节点子节点字符没有与所添加单词下一字母相同的
	{
		t->next[int(s[d] - 'a')] = new node;//新建节点
		t->next[int(s[d] - 'a')]->data = s[d];
		if (d == s.length() - 1)//单词存储完成
		{
			t->next[int(s[d] - 'a')]->is_word = true;
			t->next[int(s[d] - 'a')]->translation = tran;
			//cout << tran << endl;
			t->num++;
			return;
		}
		t->num++;
		add(tran, s, t->next[int(s[d] - 'a')], d + 1);
	}
	else//有相同的
	{
		if (d == s.length() - 1)//单词存储完成
		{
			t->next[int(s[d] - 'a')]->is_word = true;
			t->next[int(s[d] - 'a')]->translation = tran;
			//cout << tran << endl;
			return;
		}
		add(tran, s, t->next[int(s[d] - 'a')], d + 1);
	}
}
bool delete_(string s, node* t, int d) 
{
	if (d == s.length())
	{
		t->is_word = false;
		if (t->num == 0)//该节点无子节点
		{
			return true;
		}
		return false;
	}
	else
	{
		if (delete_(s, t->next[int(s[d] - 'a')], d + 1))//若末节点删除，则删除其在上一节点对应的信息
		{
			free(t->next[int(s[d] - 'a')]);
			t->next[int(s[d] - 'a')] = NULL;
			if (t->is_word)
				return false;
			t->num--;
			if (t->num == 0)
				return true;
			else
				return false;
		}
		else//否则上节点无变化
		{
			return false;
		}
	}
}
void File()
{
	fstream file("dictionary.txt", ios::in);
	if (file.fail())
	{
		Set_Color(4); 
		cout << "dictionary.txt打开失败！！！" << endl;
		exit(0);
	}
	while (!file.eof())
	{
		string s;
		string tran;
		file >> s;
		file >> tran;
		if (s != "")
			add(tran, s, root, 0);
	}
}
bool search(string s,node *t,int d,bool flag)
{
	static char out[100] = { '\0' };
	if (d == s.length())
	{
		if (t->is_word == true)
		{
			if (flag)
			{
				for (int i = 0; i <= d; i++)
					cout << out[i];
				cout << ' ' << t->translation;
				cout << endl;
			}
			return true;
		}
		else
			return false;
	}
	if (t->next[int(s[d] - 'a')] == NULL)
	{
		return false;
	}
	else
	{
		return search(s, t->next[int(s[d] - 'a')], d + 1, flag);
	}
}
void show(node *t,int d)
{
	static char s[32] = { 0 };
	if (d != -1)
		s[d] = t->data;
	if (t->is_word)
	{
		for (int i = 0; i <= d; i++)
			cout << s[i];
		cout << ' ' << t->translation << endl;
	}
	for (int i = 0; i < 26; i++)
	{
		if (t->next[i] != NULL)
			show(t->next[i], d + 1);
	}
	return;
}
void sort(node* t, int d)
{
	fstream file("dictionary.txt", ios::app);
	static char s[100] = { '\0' };
	if (d != -1)
		s[d] = t->data;
	else
	{
		fill(s, s + 100, '\0');
	}
	if (t->is_word)
	{
		for (int i = 0; i <= d; i++)
			file << s[i];
		file << ' ';
		file << t->translation;
		file << '\n';
		file.flush();
	}
	for (int i = 0; i < 26; i++)
	{
		if (t->next[i] != NULL)
			sort(t->next[i], d + 1);
	}
	file.flush();
}
void menu()
{
	while (1)
	{
		Set_Color(15); 
		cout <<"--------------------欢迎进入电子字典系统--------------------"<<endl; 
		cout << "--------------------1.添加单词------------------------------" << endl;
		cout << "--------------------2.查找单词------------------------------" << endl;
		cout << "--------------------3.删除单词------------------------------" << endl;
		cout << "--------------------4.修改单词------------------------------" << endl;
		cout << "--------------------5.单词展示------------------------------" << endl;
		cout << "--------------------6.退出程序------------------------------" << endl;
		cout <<"--------------------请从以上操作中进行选择：";
		int choice;
		cin >> choice;
		switch (choice) 
		{
		case 1: {
			string s;
			string tran;
			cout << "请输入单词：";
			cin >> s;
			cout << "请输入中文：";
			cin >> tran;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "输入不合法！！！" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (search(s, root, 0, false))
			{
				Set_Color(4); 
				cout << "单词已存在！！！" << endl;
				system("pause");
				system("cls");
				break;
			}
			fstream file("dictionary.txt", ios::app);
			if (file.fail())
			{
				Set_Color(4); 
				cout << "dictionary.txt打开失败！！！" << endl;
				exit(0);
			}
			file << s << ' ' << tran << '\n';
			file.close();
			add(tran, s, root, 0);
			cout << "添加成功！！！" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			cout << "请输入要查找的单词：";
			string s;
			cin >> s;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "输入不合法！！！" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (search(s, root, 0, true))
			{
				Set_Color(2); 
				cout << "单词存在。" << endl;
			}
			else
			{
				Set_Color(4); 
				cout << "未找到！！！" << endl;
			}
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			string s;
			cout << "请输入要删除的单词：";
			cin >> s;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "输入不合法！！！" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (!search(s, root, 0, false))
			{
				Set_Color(4); 
				cout << "单词不存在！！！" << endl;
				system("pause");
				system("cls");
				break;
			}
			delete_(s,root,0);
			fstream file("word.txt", ios::trunc | ios::out);
			sort(root, -1);
			file.close();
			Set_Color(2); 
			cout << "删除成功！！！" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4: {
			string s1, s2;
			while (1)
			{
				cout << "请输入要修改的单词：";
				cin >> s1;
				if (!is_lawful(s1))
				{
					Set_Color(4); 
					cout << "输入不合法！！！" << endl;
					system("pause");
					system("cls");
					continue;
				}
				if (!search(s1, root, 0, false))
				{
					Set_Color(4); 
					cout << "单词不存在！！！" << endl;
					system("pause");
					system("cls");
					continue;
				}
				break;
			}
			string tran;
			while (1)
			{
				cout << "请输入写改成什么单词：";
				cin >> s2;
				cout << "中文：";
				cin >> tran;
				if (!is_lawful(s2))
				{
					Set_Color(4); 
					cout << "输入不合法！！！" << endl;
					system("pause");
					system("cls");
					continue;
				}
				break;
			}
			delete_(s1, root, 0);
			add(tran, s2, root, 0);
			fstream file("dictionary.txt", ios::trunc | ios::out);
			sort(root, -1);
			file.close();
			Set_Color(2); 
			cout << "修改成功！！！" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 5: {
			show(root, -1);
			system("pause");
			system("cls");
			break;
		}
		case 6: {
			return;
		}
		}
	}
}
int main()
{
	File();
	menu();
	return 0;
}
