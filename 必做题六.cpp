#include<iostream>
#include <windows.h>
using namespace std;

#define MAX 15000
#define INFINITY 200001

typedef struct Gnode 
{
    int n;  // 顶点数
    int e;  // 边数
    int weigh[MAX][MAX];
} Gnode;

//设置字体颜色 
void Set_Color(int x);

//创建有向图 
Gnode* CreateGraph();

// 输出最短路径
void PrintPath(int path[], int v,int x);

// Dijkstra算法
void Dijkstra(Gnode* Graph, int v); 

int main() 
{
    Gnode* Graph = CreateGraph();
    int startVertex;
    Dijkstra(Graph, 0);
    delete Graph;
    return 0;
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

//创建有向图 
Gnode* CreateGraph() 
{
    int v1, v2, w;
    Gnode* Graph = new Gnode;
    Set_Color(15);
    cout << "请输入图的顶点数和边数:";
    cin >> Graph->n >> Graph->e;
    if(Graph->n>MAX)
    {
    	Set_Color(4);
    	cout<<"错误！输入的顶点数超过了最大值15000"<<endl;
		exit(0); 
	}
	if(Graph->e>1000)
    {
    	Set_Color(4);
    	cout<<"错误！输入的边数超过了最大值1000"<<endl;
		exit(0); 
	}
    for (int i = 0; i < Graph->n; i++) 
	{
        for (int j = 0; j < Graph->n; j++) 
		{
            Graph->weigh[i][j] = INFINITY;  // 初始化边权值为无穷大
        }
    }
    cout << "请输入边的起点，终点和权值，以空格分隔" << endl;
    for (int i = 0; i < Graph->e; i++) 
	{
        cin >> v1 >> v2 >> w;
        if(v1>=Graph->n||v1<0)
        {
        	Set_Color(4);
        	cout<<"错误！起点的值输入有误"<<endl;
        	exit(0);
		}
		if(v2>=Graph->n||v2<0)
        {
        	Set_Color(4);
        	cout<<"错误！终点的值输入有误"<<endl;
        	exit(0);
		}
        if(w<=0)
        {
        	Set_Color(4);
        	cout<<"错误！正权有向图权值不能为非正数"<<endl;
        	exit(0);
		}
		 
        Graph->weigh[v1][v2] = w;
    }
    return Graph;
}

// 输出最短路径
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

// Dijkstra算法
void Dijkstra(Gnode* Graph, int v) 
{
    int dis[MAX];  // 记录起点到各顶点的最短距离
    int path[MAX];  // 记录最短路径的前驱节点
    bool visited[MAX];  // 记录顶点是否已经访问
    for (int i = 0; i < Graph->n; i++) 
	{
        dis[i] = Graph->weigh[v][i];  // 初始化dis数组
        visited[i] = false;  // 初始化visited数组
        if (Graph->weigh[v][i] < INFINITY) 
		{
            path[i] = v;  // 如果起点v与顶点i之间有边，则将i的前驱节点设为v
        } 
		else 
		{
            path[i] = -1;  // 否则将i的前驱节点设为-1
        }
    }
    dis[v] = 0;  // 起点到自身的距离为0
    visited[v] = true;  // 将起点标记为已访问

    for (int i = 1; i < Graph->n; i++) 
	{
        int min_dis = INFINITY;
        int min_v = -1;
        // 找到当前未访问的距离最小的顶点
        for (int j = 0; j < Graph->n; j++) 
		{
            if (!visited[j] && dis[j] < min_dis) 
			{
                min_dis = dis[j];
                min_v = j;
            }
        }
        if (min_v == -1) break;  // 如果没有找到顶点，则退出循环
        visited[min_v] = true;  // 将顶点标记为已访问

        // 更新与当前顶点相邻的顶点的最短距离和路径
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
                    // 如果发现一条与当前最短路径长度相同但经过的顶点更少的路径，则更新路径
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

    // 输出最短路径
    for (int i = 1; i < Graph->n; i++) 
	{
        cout << "起点" << v << "到达顶点" << i << "的最短距离为: " << dis[i] << endl;
        cout << "最短路径为: ";
        PrintPath(path, i,i);
        cout << endl << endl;
    }
}
