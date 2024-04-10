#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h> 

#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 100

using namespace std;

/*以下是栈的结构定义*/
template<class T>
class Stack
{
private:
	T* data;                   // 存储栈元素的数组指针
	T* base;                   // 指向栈底的指针
	T* top;                    // 指向栈顶的指针
	int stacksize;             // 栈的当前容量
public:
	Stack(void)
	{
		data = new T[STACK_INIT_SIZE];               // 创建存储栈元素的数组
		top = base = data;                           // 初始化栈顶和栈底指针为数组首地址
		stacksize = STACK_INIT_SIZE;                 // 初始化栈的容量
	}
	void ClearStack()
	{
		top = base;                                  // 清空栈，将栈顶指针指向栈底指针
	}
	bool StackEmpty()
	{
		if (top == base)
		{
			return true;                             // 栈为空
		}
		
		else
		{
			return false;                            // 栈不为空
		}
	}
	
	int StackLength()
	{
		return top - base;                          // 返回栈的长度（栈顶指针减去栈底指针）
	}
	
	T GetTop()
	{
		return *(top - 1);                          // 获取栈顶元素的值
	}
	
	T* GetBaseLoca()
	{
		return base;                                // 返回栈底指针
	}
	
	void Push(T num)		                          // 进栈 
	{
		if (top - base != stacksize)
		{
			*(top) = num;                           // 将元素添加到栈顶
			top++;                                  // 更新栈顶指针
		}
		
		else
		{
			int i;
			T* tmp;
			tmp = new T[stacksize + STACKINCREMENT]; // 创建新的更大的临时数组
			for (i = 0; i < stacksize; i++)
			{
				tmp[i] = data[i];                    // 将原数组中的元素复制到临时数组中
			}
			delete[]data;                            // 释放原数组内存
			data = tmp;                              // 将临时数组指针赋值给原数组指针

			stacksize += STACKINCREMENT;             // 更新栈的容量

			*(top) = num;                            // 将元素添加到栈顶
			top++;                                   // 更新栈顶指针
		}
	}
	
	T Pop()	                                      // 出栈 
	{
		if (top != base)
		{
			top--;                                   // 更新栈顶指针
			return *(top);                           // 返回栈顶元素的值
		}
		else
		{
			return '\0';                             // 栈为空，返回空字符
		}
	}
	
	void ShowStack()
	{
		int i;
		if (top - base == 0)
		{
			cout << "空栈" << endl;                  // 栈为空，打印空栈提示
		}
		else
		{
			cout << "栈底到栈顶：";
			for (i = 0; i < top - base; i++)
			{
				cout << data[i] << " ";              // 从栈底到栈顶依次打印栈元素的值
			}
			cout << endl;
		}
	}
};

/*以下为队列的结构定义*/
template <class T>
struct QNode
{
	T data;           // 数据成员
	QNode* next;      // 指向下一个节点的指针
};

template <class T>
class Queue
{
public:
	QNode<T>* front;	// 队头指针（链表头）	
	QNode<T>* rear;	    // 队尾指针（链表尾） 

	Queue()
	{
		front = rear = new QNode<T>;   // 创建一个空节点作为头节点
		front->next = NULL;            // 头节点的next指针初始化为NULL
	}

	~Queue()
	{
		QNode<T>* p, * q;
		p = q = front;
		while (p != NULL)
		{
			p = p->next;
			delete q;                   // 释放节点内存
			q = p;
		}
		front = rear = NULL;             // 清空队列
	}

	void ClearQueue()
	{
		QNode<T>* p, * q;
		p = q = front->next;
		while (p != NULL)
		{
			p = p->next;
			delete q;                   // 释放节点内存
			q = p;
		}
		rear = front;                    // 将队尾指针指向头节点，表示队列被清空
	}

	bool QueueEmpty()
	{
		if (front == rear)
		{
			return true;                  // 队列为空
		}
		else
		{
			return false;                 // 队列不为空
		}
	}

	int QueueLength()
	{
		int count = 0;
		QNode<T>* p;
		p = front->next;
		while (p != NULL)
		{
			count++;                     // 统计节点数量
			p = p->next;
		}
		return count;                     // 返回队列长度
	}

	QNode<T>* GetHead()
	{
		if (front == rear)
		{
			cout << "队空" << endl;      // 队列为空，无法获取队头元素
			return NULL;
		}
		else
		{
			return front->next;           // 返回队头指针指向的节点
		}
	}

	void EnQueue(T d)
	{
		QNode<T>* p;
		p = new QNode<T>;                  // 创建新节点
		p->data = d;                       // 将数据赋值给节点的data成员
		p->next = NULL;                    // 新节点的next指针初始化为NULL
		rear->next = p;                    // 将新节点连接到队尾
		rear = rear->next;                 // 更新队尾指针
	}

	T DeQueue()
	{
		if (front == rear)
		{
			cout << "队空" << endl;       // 队列为空，无法出队
		}
		else
		{
			T ans;
			QNode<T>* p;
			p = front->next;
			ans = p->data;                // 获取队头元素的值
			front->next = p->next;        // 移除队头节点
			if (rear == p)
			{
				rear = front;             // 若队列中只有一个节点，更新队尾指针
			}
			delete p;                     // 释放节点内存
			return ans;                   // 返回队头元素的值
		}
	}
};

//求最小值 
float min(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

//邻接表 
struct ArcNode
{
	int adjvex;			//该弧所指向的顶点的位置vertices[adjvex]
	int road;			//表示这一条弧是第几路车，方便构建车与车之间的图
	ArcNode* nextarc;	//指向下一条弧的指针
};

//表头节点 
struct VNode
{
	char name[50];		//站点名
	ArcNode* firstarc;	//指向第一条依附于该顶点的弧的指针
};

//图 
class ALGraph 
{
private:
	VNode vertices[6000];					//顶点向量,每一站之间都有一个顶点
	int vexnum, arcnum;						//图的当前顶点数和弧数
	int* visited;							//用于深度优先搜索和广度优先搜索
public:


	void AddArcNode(int v1, int v2, int road)
		//为vertices[v1]和vertices[v2]两个站之间添加一条无向边，并且记录这一条无向边第road路上的
	{
		ArcNode* Ap;
		Ap = vertices[v1].firstarc;
		if (Ap == NULL)
		{
			vertices[v1].firstarc = new ArcNode;
			vertices[v1].firstarc->adjvex = v2;
			vertices[v1].firstarc->road = road;
			vertices[v1].firstarc->nextarc = NULL;
		}
		else
		{
			while (Ap->nextarc != NULL)
			{
				Ap = Ap->nextarc;
			}
			Ap->nextarc = new ArcNode;
			Ap = Ap->nextarc;
			Ap->adjvex = v2;
			Ap->road = road;
			Ap->nextarc = NULL;
		}

		Ap = vertices[v2].firstarc;
		if (Ap == NULL)
		{
			vertices[v2].firstarc = new ArcNode;
			vertices[v2].firstarc->adjvex = v1;
			vertices[v2].firstarc->road = road;
			vertices[v2].firstarc->nextarc = NULL;
		}
		else
		{
			while (Ap->nextarc != NULL)
			{
				Ap = Ap->nextarc;
			}
			Ap->nextarc = new ArcNode;
			Ap = Ap->nextarc;
			Ap->adjvex = v1;
			Ap->road = road;
			Ap->nextarc = NULL;
		}

		arcnum++;//边数++
	}

	ALGraph()
	{
		arcnum = 0;
		int i, j, count;
		int road;
		int pre_p;
		fstream rf;
		ArcNode* Ap;
		char str[3000];
		rf.open("南京公交线路.txt", ios::in);
		if (rf.fail())
		{
			cout << "南京公交线路.txt打开失败" << endl;
			exit(0);
		}

		vexnum = 0;
		road = 0;
		count = 0;

		while (!rf.eof())
		{
			rf >> road;
			if (rf.eof())
			{
				break;
			}
			rf.getline(str, 3000, '\n');
			i = 0;
			while (str[i] != ' ') i++;
			while (str[i] == ' ') i++;

			while (1)
			{
				for (j = 0; str[i] != ',' && str[i] != '\0'; i++, j++)
				{
					vertices[vexnum].name[j] = str[i];
				}
				vertices[vexnum].name[j] = '\0';
				for (j = 0; j < vexnum; j++)
				{
					if (strcmp(vertices[j].name, vertices[vexnum].name) == 0)
					{
						if (count > 0)
						{
							AddArcNode(j, pre_p, road);
						}
						pre_p = j;
						count++;
						break;
					}
				}
				if (j == vexnum)
				{
					vertices[vexnum].firstarc = NULL;
					if (count > 0)
					{
						AddArcNode(pre_p, vexnum, road);
					}

					pre_p = vexnum;
					vexnum++;
					count++;
				}
				if (str[i] != '\0')
				{
					i++;
				}
				else
				{
					break;
				}
			}
			pre_p = 0;
			count = 0;
		}
		rf.close();
		visited = new int[vexnum];
	}

	~ALGraph()
	{
		ArcNode* Ap, * pre_Ap;
		for (int i = 0; i < vexnum; i++)
		{
			Ap = vertices[i].firstarc;
			if (Ap == NULL);
			else
			{
				pre_Ap = Ap;
				while (1)
				{
					Ap = Ap->nextarc;
					if (Ap == NULL)
					{
						break;
					}
					delete pre_Ap;
					pre_Ap = Ap;
				}
			}
		}
	}

	ArcNode* AdjVex(int i)
	{
		ArcNode* Ap;
		Ap = vertices[i].firstarc;
		if (Ap == NULL)
		{
			return NULL;
		}
		else
		{
			return Ap;
		}
	}

	int GetVexNum()
	{
		return vexnum;
	}

	int FindRoad(char* n)
	{
		for (int i = 0; i < vexnum; i++)
		{
			if (strcmp(vertices[i].name, n) == 0)
			{
				return i;
			}
		}
		return -1;
	}

	VNode* GetVNode()
	{
		return vertices;
	}

	bool IsAdj(int i, int j)//判断vertices[i]与vertices[j]是否相邻
	{
		ArcNode* Ap;
		Ap = vertices[i].firstarc;
		if (Ap == NULL);
		else
		{
			while (Ap != NULL)
			{
				if (Ap->adjvex == j)
				{
					return true;
				}
				Ap = Ap->nextarc;
			}
		}

		Ap = vertices[j].firstarc;
		if (Ap == NULL);
		else
		{
			while (Ap != NULL)
			{
				if (Ap->adjvex == i)
				{
					return true;
				}
				Ap = Ap->nextarc;
			}
		}

		return false;
	}

	void MiniRoad(char* start, char* end)			//用广度优先搜索求最短路径
		//start是起始站点的名字，end的是结束站点的名字
	{
		for (int i = 0; i < vexnum; i++)
		{
			visited[i] = 0;
		}

		int v, u;
		int s, e;
		ArcNode* w = NULL;
		int i, j;
		int flag = 0;

		Queue<int> Q;
		for (i = 0; i < vexnum; i++)
		{
			if (strcmp(start, vertices[i].name) == 0)
			{
				s = i;
			}
			if (strcmp(end, vertices[i].name) == 0)
			{
				e = i;
			}
		}

		v = s;
		visited[v] = 1;
		Q.EnQueue(v);
		while (!Q.QueueEmpty())//广度优先搜索
		{
			if (flag == 1)
			{
				break;
			}
			u = Q.DeQueue();
			for (w = vertices[u].firstarc; w != NULL; w = w->nextarc)
			{
				if (visited[w->adjvex] == 0)
				{
					visited[w->adjvex] = visited[u] + 1;//往深一层搜索
					if (w->adjvex == e)
					{
						flag = 1;//已经走到了终点
						break;
					}
					Q.EnQueue(w->adjvex);
				}
			}
		}

		ArcNode* Ap;
		Stack<int> S_sta;
		Stack<int> S_road;
		S_sta.Push(w->adjvex);
		i = w->adjvex;

		cout << "经过站最少的路线为：" << endl;
		cout << "共：" << visited[w->adjvex] << "站" << endl;
		for (int deep = visited[w->adjvex] - 1; deep > 1; deep--)//i是层数
		{
			for (j = 0; j < vexnum; j++)//j为下标
			{
				if (visited[j] == deep && IsAdj(i, j))//如果是上一层并且两站点相邻
				{
					S_sta.Push(j);//j可以在路线上，进栈
					i = j;//i成为上一层
					break;//结束循环并且往更上一层寻找
				}
			}
		}


		cout << vertices[s].name;
		i = s;

		while (!S_sta.StackEmpty())//输出路线
		{
			cout << "——>";
			j = S_sta.Pop();
			Ap = vertices[j].firstarc;
			while (Ap->adjvex != i)
			{
				Ap = Ap->nextarc;
			}
			if (S_road.StackEmpty() || (S_road.GetTop() != Ap->road))//于此同时记录路线上的站点的乘车路线，并记录
			{
				S_road.Push(Ap->road);
			}
			cout << vertices[j].name;
			i = j;
		}
		cout << endl << endl;

		cout << "乘车路线为：" << endl;
		cout << "共：" << S_road.StackLength() << "路车" << endl;
		cout << S_road.Pop() << "路";
		while (!S_road.StackEmpty())
		{
			cout << "——>";
			cout << S_road.Pop() << "路";
		}

		cout << endl << endl;
	}


};



struct Arc
{
	int adjvex;			//该弧所指向的顶点的位置vertices[adjvex]
	Arc* nextarc;	//指向下一条弧的指针
};

struct BusNode
{
	Arc* firstarc;	//指向第一条依附于该顶点的弧的指针
};


class LGraph//这个类是车与车之间的图
{
private:
	BusNode vertices[1000];							//顶点向量，从1开始
	int vexnum, arcnum;						//图的当前顶点数和弧数
	int* visited;
public:

	void AddArc(int v1, int v2)
	{
		int flag;
		Arc* Ap;
		Ap = vertices[v1].firstarc;
		if (Ap == NULL)
		{
			vertices[v1].firstarc = new Arc;
			vertices[v1].firstarc->adjvex = v2;
			vertices[v1].firstarc->nextarc = NULL;
		}
		else
		{
			flag = 0;
			while (Ap->nextarc != NULL)
			{
				if (Ap->adjvex == v2) flag = 1;//说明两辆车可以换乘的信息已经记录了
				Ap = Ap->nextarc;
				if (Ap->adjvex == v1) flag = 1;//说明两辆车可以换乘的信息已经记录了	
			}
			
			if (!flag)
			{
				Ap->nextarc = new Arc;
				Ap = Ap->nextarc;
				Ap->adjvex = v2;
				Ap->nextarc = NULL;
			}
		}

		Ap = vertices[v2].firstarc;
		if (Ap == NULL)
		{
			vertices[v2].firstarc = new Arc;
			vertices[v2].firstarc->adjvex = v1;
			vertices[v2].firstarc->nextarc = NULL;
		}
		else
		{
			flag = 0;
			while (Ap->nextarc != NULL)
			{
				if (Ap->adjvex == v1) flag = 1;//说明两辆车可以换乘的信息已经记录了	
				Ap = Ap->nextarc;
				if (Ap->adjvex == v1) flag = 1;//说明两辆车可以换乘的信息已经记录了			
			}
			if (!flag)
			{
				Ap->nextarc = new Arc;
				Ap = Ap->nextarc;
				Ap->adjvex = v1;
				Ap->nextarc = NULL;
			}
		}

		arcnum++;
	}

	LGraph(ALGraph* G)//用站与站之间的图来构建
	{
		vexnum = 0;
		ArcNode* Ap;
		Arc* Bp;
		int i, j, k;
		int count;
		int Bus[500];

		for (i = 0; i < G->GetVexNum(); i++)
		{
			Ap = G->GetVNode()[i].firstarc;
			for (j = 0; j < 500; j++)
			{
				Bus[j] = 0;
			}
			if (Ap == NULL)
			{
				continue;
			}
			else
			{
				count = 0;
				while (Ap != NULL)
				{
					for (k = 0; k < count; k++)
					{
						if (Ap->road == Bus[k])
						{
							break;
						}
					}
					if (k == count)
					{
						Bus[count++] = Ap->road;
						if (Ap->road > vexnum)
						{
							vexnum = Ap->road;
						}
					}
					Ap = Ap->nextarc;
				}
				for (k = 0; k < count - 1; k++)
				{
					for (j = k + 1; j < count; j++)
					{
						if (Bus[j] != Bus[k])
						{
							AddArc(Bus[j], Bus[k]);
						}
					}
				}
			}
		}

		visited = new int[vexnum + 1];
	}

	~LGraph()
	{
		Arc* Ap, * pre_Ap;
		for (int i = 1; i < vexnum + 1; i++)
		{
			Ap = vertices[i].firstarc;
			if (Ap == NULL);
			else
			{
				pre_Ap = Ap;
				while (1)
				{
					Ap = Ap->nextarc;
					if (Ap == NULL)
					{
						break;
					}
					delete pre_Ap;
					pre_Ap = Ap;
				}
			}
		}
	}

	bool IsAdj(int i, int j)//判断vertices[i]与vertices[j]是否相邻
	{
		Arc* Ap;
		Ap = vertices[i].firstarc;
		if (Ap == NULL);
		else
		{
			while (Ap != NULL)
			{
				if (Ap->adjvex == j)
				{
					return true;
				}
				Ap = Ap->nextarc;
			}
		}

		Ap = vertices[j].firstarc;
		if (Ap == NULL);
		else
		{
			while (Ap != NULL)
			{
				if (Ap->adjvex == i)
				{
					return true;
				}
				Ap = Ap->nextarc;
			}
		}

		return false;
	}

	int FindMinTime(int start, int end)			//从v开始进行广度优先搜索
	{
		if (start == end)
		{
			return 0;
		}

		for (int i = 1; i < vexnum + 1; i++)
		{
			visited[i] = 0;
		}

		int v, u;
		Arc* w = NULL;
		int i, j;
		int flag = 0;

		Queue<int> Q;

		v = start;
		visited[v] = 1;
		Q.EnQueue(v);
		while (!Q.QueueEmpty())
		{
			if (flag == 1)
			{
				break;
			}
			u = Q.DeQueue();
			for (w = vertices[u].firstarc; w != NULL; w = w->nextarc)
			{
				if (visited[w->adjvex] == 0)
				{
					visited[w->adjvex] = visited[u] + 1;
					if (w->adjvex == end)
					{
						flag = 1;//已经走到了终点
						break;
					}
					Q.EnQueue(w->adjvex);
				}
			}
		}
		return  visited[w->adjvex];
	}

	void PrintMinTransform(int start, int end)
	{
		if (start == end)
		{
			cout << "两站位于" << start << "路车路线上" << endl;
			return;
		}

		for (int i = 1; i < vexnum + 1; i++)
		{
			visited[i] = 0;
		}

		int v, u;
		Arc* w = NULL;
		int i, j;
		int flag = 0;

		Queue<int> Q;

		v = start;
		visited[v] = 1;
		Q.EnQueue(v);
		while (!Q.QueueEmpty())
		{
			if (flag == 1)
			{
				break;
			}
			u = Q.DeQueue();
			for (w = vertices[u].firstarc; w != NULL; w = w->nextarc)
			{
				if (visited[w->adjvex] == 0)
				{
					visited[w->adjvex] = visited[u] + 1;
					if (w->adjvex == end)
					{
						flag = 1;//已经走到了终点
						break;
					}
					Q.EnQueue(w->adjvex);
				}
			}
		}

		Arc* Ap;
		Stack<int> S;
		S.Push(w->adjvex);
		i = w->adjvex;

		cout << "换乘最少的路线为：" << endl;
		if (visited[w->adjvex] <= 2)
		{
			cout << "不用换乘" << endl;
		}
		
		else
		{
			cout << "共换乘坐：" << visited[w->adjvex] - 1 << "次" << endl;
		}
		
		for (int deep = visited[w->adjvex] - 1; deep > 1; deep--)//i是层数
		{
			for (j = 0; j < vexnum; j++)//j为下标
			{
				if (visited[j] == deep && IsAdj(i, j))
				{
					S.Push(j);
					i = j;
					break;
				}
			}
		}


		cout << start;
		i = start;

		while (!S.StackEmpty())
		{
			cout << "——>";
			cout << S.Pop();
		}
		cout << endl << endl;
	}

	void MiniTransform(ALGraph* G, int start, int end)		//对G中每一个点都进行广度优先搜索
	{
		int i, j;
		for (i = 1; i < vexnum + 1; i++)
		{
			visited[i] = 0;
		}

		ArcNode* Ap;

		int s_road[100];
		int e_road[100];
		int s_count = 0;
		int e_count = 0;
		char s[50];
		char e[50];

		Ap = G->GetVNode()[start].firstarc;
		while (Ap != NULL)
		{
			s_road[s_count++] = Ap->road;
			Ap = Ap->nextarc;
		}

		Ap = G->GetVNode()[end].firstarc;
		while (Ap != NULL)
		{
			e_road[e_count++] = Ap->road;
			Ap = Ap->nextarc;
		}

		int min = 99999;
		int tmp = 0;
		int min_s = 0;
		int min_e = 0;
		for (i = 0; i < s_count; i++)
		{
			for (j = 0; j < e_count; j++)
			{
				tmp = FindMinTime(s_road[i], e_road[j]);
				if (tmp <= min)
				{
					min = tmp;
					min_s = s_road[i];
					min_e = e_road[j];
				}
			}
		}
		PrintMinTransform(min_s, min_e);
	}
};

int main()
{
	int start, end;
	char s[50];
	char e[50];
	cout << "请输入起点：";
	cin >> s;
	cout << "请输入终点：";
	cin >> e;

	ALGraph A;
	LGraph B(&A);
	start = A.FindRoad(s);
	end = A.FindRoad(e);
	if (start == -1 || end == -1)
	{
		cout << "输入站点有误！" << endl;
		return 0;
	}
if(start==end)
{
	cout << "\n不需要乘坐公交车，起点，终点位置相同！" <<endl;
	return 0;
}
	A.MiniRoad(s, e);

	cout << endl << endl << "最少换乘" << endl;
	B.MiniTransform(&A, start, end);
}

