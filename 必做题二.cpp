#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <windows.h>
#define MAX 26  
using namespace std;

// �ڵ����ݽṹ���洢�ڵ�
typedef struct Node
{
    int x; // ������
    int y; // ������
} Node;

// ջ���ݽṹ���洢ջ
typedef struct stack
{
    int size;  // ջ������
    Node* top; // ջ��
    Node* base; // ջ��
} stack;

bool map[MAX][MAX];//�洢��ͼ 
bool vis[MAX][MAX];	//�洢��ͼ�������
bool die[MAX][MAX];	//�洢��·
bool is_find=false;//�ж������ҵ�·�߳��Թ�
const int dx[] = {1, 0, -1, 0};  // �ҡ��¡�����
const int dy[] = {0, 1, 0, -1}; 

// ����ջ
stack* createstack(); 

//��ջ 
void stackpush(stack* k, int x, int y);

// ��ȡջ��
Node stacktop(stack* k);

// ��ջ
void stackpop(stack* k);

// �ж�ջ�Ƿ�Ϊ��
bool empty(stack* k);

// ��ӡ��ջ
void Print(stack* k);

//�����Թ� 
void createPuzzle(int x,int y,bool map[MAX][MAX],bool vis[MAX][MAX],bool die[MAX][MAX]);

//Ѱ·����
void DFS(int x, int y, int tx, int ty,stack* k);

//����������ɫ 
void Set_Color(int x);

//�Թ��޽����� 
void NO_find(bool is_find);

int main()
{
    stack* k = createstack(); //����ջ 
	cout << "���ڴ��ļ��ж�ȡ��Ϣ" << endl;
	ifstream file;
	file.open("T2.txt");
	int x, y;
	file >> x >> y;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
			file >> map[i][j];
			vis[i][j]=false ;
		}
	}
	cout<<"��ȡ�����Թ����£�(0��ʾ�ϰ�)"<<endl;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
		 cout<<map[i][j]<<" ";
	    }
	    cout<<endl;
	}
	createPuzzle(x,y,map,vis,die);
	cout << "��Ϣ��ȡ��ɡ�"<<endl;
	cout<<"�������������:";
	int startx, starty, endx, endy;
	cin >> startx >> starty;
	stackpush(k,startx,starty);
	cout << "�������յ�����:";
	cin >> endx >> endy;
	DFS(startx,starty,endx,endy,k);	
	NO_find(is_find);
	file.close();//�ر��ļ� 
    return 0;
}

// ����ջ
stack* createstack() 
{
    stack* p = (stack*)malloc(sizeof(stack)); // �����¿ռ�
    if (p == NULL) // ����ʧ��
    {
        cout << "����ջʧ��" << endl;
        return nullptr;
    }
    p->size = 0;
    p->base = p->top = (Node*)malloc(sizeof(Node)); // Ϊtop�����ڴ�ռ�
    return p;
}

// ��ջ
void stackpush(stack* k, int x, int y)
{
    k->top->x = x;
    k->top->y = y;
    k->top++;
    k->size++;
}

// ��ȡջ��
Node stacktop(stack* k)
{
    if (k->size != 0) // ջ�ǿ�
    {
        return *(k->top - 1);
    }
    else
    {
        cout << "���棬ջ��ʱΪ��" << endl;
        return Node{-1, -1}; // ����һ����Ч�ڵ�
    }
}

// ��ջ
void stackpop(stack* k)
{
    if (k->size != 0) // ջ�ǿ�
    {
        k->top--;
        k->size--;
    }
    else
    {
        cout << "���棬ջ��ʱΪ��" << endl;
    }
}

// �ж�ջ�Ƿ�Ϊ��
bool empty(stack* k)
{
    return k->top == k->base;
}

// ��ӡ��ջ
void Print(stack* k)
{
    Node* pCur = k->base;
    while (pCur < k->top)
    {
    	Set_Color(10);//��ɫ 
        cout << "( " << pCur->x << ", " << pCur->y << " )";
        Set_Color(15);//��ɫ 
        if (pCur < k->top - 1)
            cout << " --> ";
        pCur++;
    }
    cout << endl;
}

//�����Թ� 
void createPuzzle(int x,int y,bool map[MAX][MAX],bool vis[MAX][MAX],bool die[MAX][MAX])
{
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(map[i][j]==1)//���������
			{
			vis[i][j]==true;	
			}
			else if(map[i][j]==0)//������ϰ�
			{
			die[i][j]==true; 
			} 
		}
	 } 
}

//Ѱ·����
void DFS(int x, int y, int tx, int ty,stack* k)			//����ΪĿǰ�������꼰�յ�����
{
	vis[x][y] = true;
	if (x == tx && y == ty)
	{
		cout << "�Ѿ��ҵ��߳����Թ���·����������ʾ��" << endl;
		Print(k);
		is_find = true;
		return;
	}
	for (int i = 0; i <= 3; i++)
	{
		if (!vis[x + dx[i]][y + dy[i]] && map[x + dx[i]][y + dy[i]] && y + dy[i] >= 1 && y + dy[i] <= 25 && x + dx[i] >= 1 && x + dx[i] <= 25)
		{
			vis[x + dx[i]][y + dy[i]] = true;
			stackpush(k,x + dx[i], y + dy[i]);
			DFS(x + dx[i], y + dy[i], tx, ty,k);
			if (is_find)
				return;
			stackpop(k);
			die[y + dy[i]][x + dx[i]]= true;
		}
	}
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

//�Թ��޽����� 
void NO_find(bool is_find)
{
	if (is_find == false)
	{
		Set_Color(4);
		cout << "������ϣ����Թ��޽⣡" << endl;
		Set_Color(7);
	}
}
