#include<iostream>
#include<fstream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;
typedef struct node
{
	bool is_word;//��¼�Ƿ��ǵ��ʵ�β��ĸ
	char data;//��ǰ�ڵ�����
	string translation;//����
	node* next[26];//�ӽڵ�ָ��
	int num;//�ӽ�����
	node()//���캯��
	{
	    memset(next, NULL, sizeof(next));
		num = 0;
		is_word = false;
	}
}node;
node* root = new node;//���ڵ�����
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

void add(string tran, string s, node* t, int d)
{
	if (t->next[int(s[d] - 'a')] == NULL)//�ýڵ��ӽڵ��ַ�û��������ӵ�����һ��ĸ��ͬ��
	{
		t->next[int(s[d] - 'a')] = new node;//�½��ڵ�
		t->next[int(s[d] - 'a')]->data = s[d];
		if (d == s.length() - 1)//���ʴ洢���
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
	else//����ͬ��
	{
		if (d == s.length() - 1)//���ʴ洢���
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
		if (t->num == 0)//�ýڵ����ӽڵ�
		{
			return true;
		}
		return false;
	}
	else
	{
		if (delete_(s, t->next[int(s[d] - 'a')], d + 1))//��ĩ�ڵ�ɾ������ɾ��������һ�ڵ��Ӧ����Ϣ
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
		else//�����Ͻڵ��ޱ仯
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
		cout << "dictionary.txt��ʧ�ܣ�����" << endl;
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
		cout <<"--------------------��ӭ��������ֵ�ϵͳ--------------------"<<endl; 
		cout << "--------------------1.��ӵ���------------------------------" << endl;
		cout << "--------------------2.���ҵ���------------------------------" << endl;
		cout << "--------------------3.ɾ������------------------------------" << endl;
		cout << "--------------------4.�޸ĵ���------------------------------" << endl;
		cout << "--------------------5.����չʾ------------------------------" << endl;
		cout << "--------------------6.�˳�����------------------------------" << endl;
		cout <<"--------------------������ϲ����н���ѡ��";
		int choice;
		cin >> choice;
		switch (choice) 
		{
		case 1: {
			string s;
			string tran;
			cout << "�����뵥�ʣ�";
			cin >> s;
			cout << "���������ģ�";
			cin >> tran;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "���벻�Ϸ�������" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (search(s, root, 0, false))
			{
				Set_Color(4); 
				cout << "�����Ѵ��ڣ�����" << endl;
				system("pause");
				system("cls");
				break;
			}
			fstream file("dictionary.txt", ios::app);
			if (file.fail())
			{
				Set_Color(4); 
				cout << "dictionary.txt��ʧ�ܣ�����" << endl;
				exit(0);
			}
			file << s << ' ' << tran << '\n';
			file.close();
			add(tran, s, root, 0);
			cout << "��ӳɹ�������" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			cout << "������Ҫ���ҵĵ��ʣ�";
			string s;
			cin >> s;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "���벻�Ϸ�������" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (search(s, root, 0, true))
			{
				Set_Color(2); 
				cout << "���ʴ��ڡ�" << endl;
			}
			else
			{
				Set_Color(4); 
				cout << "δ�ҵ�������" << endl;
			}
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			string s;
			cout << "������Ҫɾ���ĵ��ʣ�";
			cin >> s;
			if (!is_lawful(s))
			{
				Set_Color(4); 
				cout << "���벻�Ϸ�������" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (!search(s, root, 0, false))
			{
				Set_Color(4); 
				cout << "���ʲ����ڣ�����" << endl;
				system("pause");
				system("cls");
				break;
			}
			delete_(s,root,0);
			fstream file("word.txt", ios::trunc | ios::out);
			sort(root, -1);
			file.close();
			Set_Color(2); 
			cout << "ɾ���ɹ�������" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4: {
			string s1, s2;
			while (1)
			{
				cout << "������Ҫ�޸ĵĵ��ʣ�";
				cin >> s1;
				if (!is_lawful(s1))
				{
					Set_Color(4); 
					cout << "���벻�Ϸ�������" << endl;
					system("pause");
					system("cls");
					continue;
				}
				if (!search(s1, root, 0, false))
				{
					Set_Color(4); 
					cout << "���ʲ����ڣ�����" << endl;
					system("pause");
					system("cls");
					continue;
				}
				break;
			}
			string tran;
			while (1)
			{
				cout << "������д�ĳ�ʲô���ʣ�";
				cin >> s2;
				cout << "���ģ�";
				cin >> tran;
				if (!is_lawful(s2))
				{
					Set_Color(4); 
					cout << "���벻�Ϸ�������" << endl;
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
			cout << "�޸ĳɹ�������" << endl;
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
