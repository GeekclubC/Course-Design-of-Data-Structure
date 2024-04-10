#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <windows.h>
#define MAX 26  
using namespace std;

// 节点数据结构，存储节点
typedef struct Node
{
    int x; // 横坐标
    int y; // 纵坐标
} Node;

// 栈数据结构，存储栈
typedef struct stack
{
    int size;  // 栈的容量
    Node* top; // 栈顶
    Node* base; // 栈底
} stack;

bool map[MAX][MAX];//存储地图 
bool vis[MAX][MAX];	//存储地图访问情况
bool die[MAX][MAX];	//存储死路
bool is_find=false;//判断是能找到路走出迷宫
const int dx[] = {1, 0, -1, 0};  // 右、下、左、上
const int dy[] = {0, 1, 0, -1}; 

// 创建栈
stack* createstack(); 

//进栈 
void stackpush(stack* k, int x, int y);

// 获取栈顶
Node stacktop(stack* k);

// 弹栈
void stackpop(stack* k);

// 判断栈是否为空
bool empty(stack* k);

// 打印该栈
void Print(stack* k);

//创建迷宫 
void createPuzzle(int x,int y,bool map[MAX][MAX],bool vis[MAX][MAX],bool die[MAX][MAX]);

//寻路函数
void DFS(int x, int y, int tx, int ty,stack* k);

//设置字体颜色 
void Set_Color(int x);

//迷宫无解的输出 
void NO_find(bool is_find);

int main()
{
    stack* k = createstack(); //创建栈 
	cout << "正在从文件中读取信息" << endl;
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
	cout<<"读取到的迷宫如下：(0表示障碍)"<<endl;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
		 cout<<map[i][j]<<" ";
	    }
	    cout<<endl;
	}
	createPuzzle(x,y,map,vis,die);
	cout << "信息读取完成。"<<endl;
	cout<<"请输入起点坐标:";
	int startx, starty, endx, endy;
	cin >> startx >> starty;
	stackpush(k,startx,starty);
	cout << "请输入终点坐标:";
	cin >> endx >> endy;
	DFS(startx,starty,endx,endy,k);	
	NO_find(is_find);
	file.close();//关闭文件 
    return 0;
}

// 创建栈
stack* createstack() 
{
    stack* p = (stack*)malloc(sizeof(stack)); // 分配新空间
    if (p == NULL) // 分配失败
    {
        cout << "创建栈失败" << endl;
        return nullptr;
    }
    p->size = 0;
    p->base = p->top = (Node*)malloc(sizeof(Node)); // 为top分配内存空间
    return p;
}

// 进栈
void stackpush(stack* k, int x, int y)
{
    k->top->x = x;
    k->top->y = y;
    k->top++;
    k->size++;
}

// 获取栈顶
Node stacktop(stack* k)
{
    if (k->size != 0) // 栈非空
    {
        return *(k->top - 1);
    }
    else
    {
        cout << "警告，栈此时为空" << endl;
        return Node{-1, -1}; // 返回一个无效节点
    }
}

// 弹栈
void stackpop(stack* k)
{
    if (k->size != 0) // 栈非空
    {
        k->top--;
        k->size--;
    }
    else
    {
        cout << "警告，栈此时为空" << endl;
    }
}

// 判断栈是否为空
bool empty(stack* k)
{
    return k->top == k->base;
}

// 打印该栈
void Print(stack* k)
{
    Node* pCur = k->base;
    while (pCur < k->top)
    {
    	Set_Color(10);//绿色 
        cout << "( " << pCur->x << ", " << pCur->y << " )";
        Set_Color(15);//白色 
        if (pCur < k->top - 1)
            cout << " --> ";
        pCur++;
    }
    cout << endl;
}

//创建迷宫 
void createPuzzle(int x,int y,bool map[MAX][MAX],bool vis[MAX][MAX],bool die[MAX][MAX])
{
	for(int i=1;i<=x;i++)
	{
		for(int j=1;j<=y;j++)
		{
			if(map[i][j]==1)//如果可以走
			{
			vis[i][j]==true;	
			}
			else if(map[i][j]==0)//如果有障碍
			{
			die[i][j]==true; 
			} 
		}
	 } 
}

//寻路函数
void DFS(int x, int y, int tx, int ty,stack* k)			//参数为目前所在坐标及终点坐标
{
	vis[x][y] = true;
	if (x == tx && y == ty)
	{
		cout << "已经找到走出该迷宫的路径，如下所示：" << endl;
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

//迷宫无解的输出 
void NO_find(bool is_find)
{
	if (is_find == false)
	{
		Set_Color(4);
		cout << "搜索完毕，此迷宫无解！" << endl;
		Set_Color(7);
	}
}
