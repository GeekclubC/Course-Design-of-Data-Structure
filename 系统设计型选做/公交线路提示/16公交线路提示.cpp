#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h> 

#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 100

using namespace std;

/*������ջ�Ľṹ����*/
template<class T>
class Stack
{
private:
	T* data;                   // �洢ջԪ�ص�����ָ��
	T* base;                   // ָ��ջ�׵�ָ��
	T* top;                    // ָ��ջ����ָ��
	int stacksize;             // ջ�ĵ�ǰ����
public:
	Stack(void)
	{
		data = new T[STACK_INIT_SIZE];               // �����洢ջԪ�ص�����
		top = base = data;                           // ��ʼ��ջ����ջ��ָ��Ϊ�����׵�ַ
		stacksize = STACK_INIT_SIZE;                 // ��ʼ��ջ������
	}
	void ClearStack()
	{
		top = base;                                  // ���ջ����ջ��ָ��ָ��ջ��ָ��
	}
	bool StackEmpty()
	{
		if (top == base)
		{
			return true;                             // ջΪ��
		}
		
		else
		{
			return false;                            // ջ��Ϊ��
		}
	}
	
	int StackLength()
	{
		return top - base;                          // ����ջ�ĳ��ȣ�ջ��ָ���ȥջ��ָ�룩
	}
	
	T GetTop()
	{
		return *(top - 1);                          // ��ȡջ��Ԫ�ص�ֵ
	}
	
	T* GetBaseLoca()
	{
		return base;                                // ����ջ��ָ��
	}
	
	void Push(T num)		                          // ��ջ 
	{
		if (top - base != stacksize)
		{
			*(top) = num;                           // ��Ԫ����ӵ�ջ��
			top++;                                  // ����ջ��ָ��
		}
		
		else
		{
			int i;
			T* tmp;
			tmp = new T[stacksize + STACKINCREMENT]; // �����µĸ������ʱ����
			for (i = 0; i < stacksize; i++)
			{
				tmp[i] = data[i];                    // ��ԭ�����е�Ԫ�ظ��Ƶ���ʱ������
			}
			delete[]data;                            // �ͷ�ԭ�����ڴ�
			data = tmp;                              // ����ʱ����ָ�븳ֵ��ԭ����ָ��

			stacksize += STACKINCREMENT;             // ����ջ������

			*(top) = num;                            // ��Ԫ����ӵ�ջ��
			top++;                                   // ����ջ��ָ��
		}
	}
	
	T Pop()	                                      // ��ջ 
	{
		if (top != base)
		{
			top--;                                   // ����ջ��ָ��
			return *(top);                           // ����ջ��Ԫ�ص�ֵ
		}
		else
		{
			return '\0';                             // ջΪ�գ����ؿ��ַ�
		}
	}
	
	void ShowStack()
	{
		int i;
		if (top - base == 0)
		{
			cout << "��ջ" << endl;                  // ջΪ�գ���ӡ��ջ��ʾ
		}
		else
		{
			cout << "ջ�׵�ջ����";
			for (i = 0; i < top - base; i++)
			{
				cout << data[i] << " ";              // ��ջ�׵�ջ�����δ�ӡջԪ�ص�ֵ
			}
			cout << endl;
		}
	}
};

/*����Ϊ���еĽṹ����*/
template <class T>
struct QNode
{
	T data;           // ���ݳ�Ա
	QNode* next;      // ָ����һ���ڵ��ָ��
};

template <class T>
class Queue
{
public:
	QNode<T>* front;	// ��ͷָ�루����ͷ��	
	QNode<T>* rear;	    // ��βָ�루����β�� 

	Queue()
	{
		front = rear = new QNode<T>;   // ����һ���սڵ���Ϊͷ�ڵ�
		front->next = NULL;            // ͷ�ڵ��nextָ���ʼ��ΪNULL
	}

	~Queue()
	{
		QNode<T>* p, * q;
		p = q = front;
		while (p != NULL)
		{
			p = p->next;
			delete q;                   // �ͷŽڵ��ڴ�
			q = p;
		}
		front = rear = NULL;             // ��ն���
	}

	void ClearQueue()
	{
		QNode<T>* p, * q;
		p = q = front->next;
		while (p != NULL)
		{
			p = p->next;
			delete q;                   // �ͷŽڵ��ڴ�
			q = p;
		}
		rear = front;                    // ����βָ��ָ��ͷ�ڵ㣬��ʾ���б����
	}

	bool QueueEmpty()
	{
		if (front == rear)
		{
			return true;                  // ����Ϊ��
		}
		else
		{
			return false;                 // ���в�Ϊ��
		}
	}

	int QueueLength()
	{
		int count = 0;
		QNode<T>* p;
		p = front->next;
		while (p != NULL)
		{
			count++;                     // ͳ�ƽڵ�����
			p = p->next;
		}
		return count;                     // ���ض��г���
	}

	QNode<T>* GetHead()
	{
		if (front == rear)
		{
			cout << "�ӿ�" << endl;      // ����Ϊ�գ��޷���ȡ��ͷԪ��
			return NULL;
		}
		else
		{
			return front->next;           // ���ض�ͷָ��ָ��Ľڵ�
		}
	}

	void EnQueue(T d)
	{
		QNode<T>* p;
		p = new QNode<T>;                  // �����½ڵ�
		p->data = d;                       // �����ݸ�ֵ���ڵ��data��Ա
		p->next = NULL;                    // �½ڵ��nextָ���ʼ��ΪNULL
		rear->next = p;                    // ���½ڵ����ӵ���β
		rear = rear->next;                 // ���¶�βָ��
	}

	T DeQueue()
	{
		if (front == rear)
		{
			cout << "�ӿ�" << endl;       // ����Ϊ�գ��޷�����
		}
		else
		{
			T ans;
			QNode<T>* p;
			p = front->next;
			ans = p->data;                // ��ȡ��ͷԪ�ص�ֵ
			front->next = p->next;        // �Ƴ���ͷ�ڵ�
			if (rear == p)
			{
				rear = front;             // ��������ֻ��һ���ڵ㣬���¶�βָ��
			}
			delete p;                     // �ͷŽڵ��ڴ�
			return ans;                   // ���ض�ͷԪ�ص�ֵ
		}
	}
};

//����Сֵ 
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

//�ڽӱ� 
struct ArcNode
{
	int adjvex;			//�û���ָ��Ķ����λ��vertices[adjvex]
	int road;			//��ʾ��һ�����ǵڼ�·�������㹹�����복֮���ͼ
	ArcNode* nextarc;	//ָ����һ������ָ��
};

//��ͷ�ڵ� 
struct VNode
{
	char name[50];		//վ����
	ArcNode* firstarc;	//ָ���һ�������ڸö���Ļ���ָ��
};

//ͼ 
class ALGraph 
{
private:
	VNode vertices[6000];					//��������,ÿһվ֮�䶼��һ������
	int vexnum, arcnum;						//ͼ�ĵ�ǰ�������ͻ���
	int* visited;							//����������������͹����������
public:


	void AddArcNode(int v1, int v2, int road)
		//Ϊvertices[v1]��vertices[v2]����վ֮�����һ������ߣ����Ҽ�¼��һ������ߵ�road·�ϵ�
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

		arcnum++;//����++
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
		rf.open("�Ͼ�������·.txt", ios::in);
		if (rf.fail())
		{
			cout << "�Ͼ�������·.txt��ʧ��" << endl;
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

	bool IsAdj(int i, int j)//�ж�vertices[i]��vertices[j]�Ƿ�����
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

	void MiniRoad(char* start, char* end)			//�ù���������������·��
		//start����ʼվ������֣�end���ǽ���վ�������
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
		while (!Q.QueueEmpty())//�����������
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
					visited[w->adjvex] = visited[u] + 1;//����һ������
					if (w->adjvex == e)
					{
						flag = 1;//�Ѿ��ߵ����յ�
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

		cout << "����վ���ٵ�·��Ϊ��" << endl;
		cout << "����" << visited[w->adjvex] << "վ" << endl;
		for (int deep = visited[w->adjvex] - 1; deep > 1; deep--)//i�ǲ���
		{
			for (j = 0; j < vexnum; j++)//jΪ�±�
			{
				if (visited[j] == deep && IsAdj(i, j))//�������һ�㲢����վ������
				{
					S_sta.Push(j);//j������·���ϣ���ջ
					i = j;//i��Ϊ��һ��
					break;//����ѭ������������һ��Ѱ��
				}
			}
		}


		cout << vertices[s].name;
		i = s;

		while (!S_sta.StackEmpty())//���·��
		{
			cout << "����>";
			j = S_sta.Pop();
			Ap = vertices[j].firstarc;
			while (Ap->adjvex != i)
			{
				Ap = Ap->nextarc;
			}
			if (S_road.StackEmpty() || (S_road.GetTop() != Ap->road))//�ڴ�ͬʱ��¼·���ϵ�վ��ĳ˳�·�ߣ�����¼
			{
				S_road.Push(Ap->road);
			}
			cout << vertices[j].name;
			i = j;
		}
		cout << endl << endl;

		cout << "�˳�·��Ϊ��" << endl;
		cout << "����" << S_road.StackLength() << "·��" << endl;
		cout << S_road.Pop() << "·";
		while (!S_road.StackEmpty())
		{
			cout << "����>";
			cout << S_road.Pop() << "·";
		}

		cout << endl << endl;
	}


};



struct Arc
{
	int adjvex;			//�û���ָ��Ķ����λ��vertices[adjvex]
	Arc* nextarc;	//ָ����һ������ָ��
};

struct BusNode
{
	Arc* firstarc;	//ָ���һ�������ڸö���Ļ���ָ��
};


class LGraph//������ǳ��복֮���ͼ
{
private:
	BusNode vertices[1000];							//������������1��ʼ
	int vexnum, arcnum;						//ͼ�ĵ�ǰ�������ͻ���
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
				if (Ap->adjvex == v2) flag = 1;//˵�����������Ի��˵���Ϣ�Ѿ���¼��
				Ap = Ap->nextarc;
				if (Ap->adjvex == v1) flag = 1;//˵�����������Ի��˵���Ϣ�Ѿ���¼��	
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
				if (Ap->adjvex == v1) flag = 1;//˵�����������Ի��˵���Ϣ�Ѿ���¼��	
				Ap = Ap->nextarc;
				if (Ap->adjvex == v1) flag = 1;//˵�����������Ի��˵���Ϣ�Ѿ���¼��			
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

	LGraph(ALGraph* G)//��վ��վ֮���ͼ������
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

	bool IsAdj(int i, int j)//�ж�vertices[i]��vertices[j]�Ƿ�����
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

	int FindMinTime(int start, int end)			//��v��ʼ���й����������
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
						flag = 1;//�Ѿ��ߵ����յ�
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
			cout << "��վλ��" << start << "·��·����" << endl;
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
						flag = 1;//�Ѿ��ߵ����յ�
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

		cout << "�������ٵ�·��Ϊ��" << endl;
		if (visited[w->adjvex] <= 2)
		{
			cout << "���û���" << endl;
		}
		
		else
		{
			cout << "����������" << visited[w->adjvex] - 1 << "��" << endl;
		}
		
		for (int deep = visited[w->adjvex] - 1; deep > 1; deep--)//i�ǲ���
		{
			for (j = 0; j < vexnum; j++)//jΪ�±�
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
			cout << "����>";
			cout << S.Pop();
		}
		cout << endl << endl;
	}

	void MiniTransform(ALGraph* G, int start, int end)		//��G��ÿһ���㶼���й����������
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
	cout << "��������㣺";
	cin >> s;
	cout << "�������յ㣺";
	cin >> e;

	ALGraph A;
	LGraph B(&A);
	start = A.FindRoad(s);
	end = A.FindRoad(e);
	if (start == -1 || end == -1)
	{
		cout << "����վ������" << endl;
		return 0;
	}
if(start==end)
{
	cout << "\n����Ҫ��������������㣬�յ�λ����ͬ��" <<endl;
	return 0;
}
	A.MiniRoad(s, e);

	cout << endl << endl << "���ٻ���" << endl;
	B.MiniTransform(&A, start, end);
}

