#include<iostream>
#include <windows.h>
using namespace std;

#define MAX 15000
#define INFINITY 200001

typedef struct Gnode 
{
    int n;  // ������
    int e;  // ����
    int weigh[MAX][MAX];
} Gnode;

//����������ɫ 
void Set_Color(int x);

//��������ͼ 
Gnode* CreateGraph();

// ������·��
void PrintPath(int path[], int v,int x);

// Dijkstra�㷨
void Dijkstra(Gnode* Graph, int v); 

int main() 
{
    Gnode* Graph = CreateGraph();
    int startVertex;
    Dijkstra(Graph, 0);
    delete Graph;
    return 0;
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

//��������ͼ 
Gnode* CreateGraph() 
{
    int v1, v2, w;
    Gnode* Graph = new Gnode;
    Set_Color(15);
    cout << "������ͼ�Ķ������ͱ���:";
    cin >> Graph->n >> Graph->e;
    if(Graph->n>MAX)
    {
    	Set_Color(4);
    	cout<<"��������Ķ��������������ֵ15000"<<endl;
		exit(0); 
	}
	if(Graph->e>1000)
    {
    	Set_Color(4);
    	cout<<"��������ı������������ֵ1000"<<endl;
		exit(0); 
	}
    for (int i = 0; i < Graph->n; i++) 
	{
        for (int j = 0; j < Graph->n; j++) 
		{
            Graph->weigh[i][j] = INFINITY;  // ��ʼ����ȨֵΪ�����
        }
    }
    cout << "������ߵ���㣬�յ��Ȩֵ���Կո�ָ�" << endl;
    for (int i = 0; i < Graph->e; i++) 
	{
        cin >> v1 >> v2 >> w;
        if(v1>=Graph->n||v1<0)
        {
        	Set_Color(4);
        	cout<<"��������ֵ��������"<<endl;
        	exit(0);
		}
		if(v2>=Graph->n||v2<0)
        {
        	Set_Color(4);
        	cout<<"�����յ��ֵ��������"<<endl;
        	exit(0);
		}
        if(w<=0)
        {
        	Set_Color(4);
        	cout<<"������Ȩ����ͼȨֵ����Ϊ������"<<endl;
        	exit(0);
		}
		 
        Graph->weigh[v1][v2] = w;
    }
    return Graph;
}

// ������·��
void PrintPath(int path[], int v,int x) 
{
	
    if (path[v] == -1) 
	{
        cout << v << "->";
        return;
    }
    PrintPath(path, path[v],x);
    if(x!=v)
    cout << v << "->";
    else if(x==v)
    cout<<v;
}

// Dijkstra�㷨
void Dijkstra(Gnode* Graph, int v) 
{
    int dis[MAX];  // ��¼��㵽���������̾���
    int path[MAX];  // ��¼���·����ǰ���ڵ�
    bool visited[MAX];  // ��¼�����Ƿ��Ѿ�����
    for (int i = 0; i < Graph->n; i++) 
	{
        dis[i] = Graph->weigh[v][i];  // ��ʼ��dis����
        visited[i] = false;  // ��ʼ��visited����
        if (Graph->weigh[v][i] < INFINITY) 
		{
            path[i] = v;  // ������v�붥��i֮���бߣ���i��ǰ���ڵ���Ϊv
        } 
		else 
		{
            path[i] = -1;  // ����i��ǰ���ڵ���Ϊ-1
        }
    }
    dis[v] = 0;  // ��㵽����ľ���Ϊ0
    visited[v] = true;  // �������Ϊ�ѷ���

    for (int i = 1; i < Graph->n; i++) 
	{
        int min_dis = INFINITY;
        int min_v = -1;
        // �ҵ���ǰδ���ʵľ�����С�Ķ���
        for (int j = 0; j < Graph->n; j++) 
		{
            if (!visited[j] && dis[j] < min_dis) 
			{
                min_dis = dis[j];
                min_v = j;
            }
        }
        if (min_v == -1) break;  // ���û���ҵ����㣬���˳�ѭ��
        visited[min_v] = true;  // ��������Ϊ�ѷ���

        // �����뵱ǰ�������ڵĶ������̾����·��
        for (int w = 0; w < Graph->n; w++) 
		{
            if (!visited[w] && Graph->weigh[min_v][w] < INFINITY) 
			{
                if (dis[w] > dis[min_v] + Graph->weigh[min_v][w]) 
				{
                    dis[w] = dis[min_v] + Graph->weigh[min_v][w];
                    path[w] = min_v;
                } 
				else if (dis[w] == dis[min_v] + Graph->weigh[min_v][w]) 
				{
                    // �������һ���뵱ǰ���·��������ͬ�������Ķ�����ٵ�·���������·��
                    int temp_path[Graph->n];
                    for (int k = 0; k < Graph->n; k++) 
					{
                        temp_path[k] = path[k];
                    }
                    temp_path[w] = min_v;
                    int min_vertex_count = 0;
                    int curr_vertex = w;
                    while (curr_vertex != v) 
					{
                        curr_vertex = temp_path[curr_vertex];
                        min_vertex_count++;
                    }
                    int original_vertex_count = 0;
                    curr_vertex = w;
                    while (curr_vertex != v) 
					{
                        curr_vertex = path[curr_vertex];
                        original_vertex_count++;
                    }
                    if (min_vertex_count < original_vertex_count) 
					{
                        for (int k = 0; k < Graph->n; k++) 
						{
                            path[k] = temp_path[k];
                        }
                    }
                }
            }
        }
    }

    // ������·��
    for (int i = 1; i < Graph->n; i++) 
	{
        cout << "���" << v << "���ﶥ��" << i << "����̾���Ϊ: " << dis[i] << endl;
        cout << "���·��Ϊ: ";
        PrintPath(path, i,i);
        cout << endl << endl;
    }
}
