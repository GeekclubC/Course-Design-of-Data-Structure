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

//弗洛伊德算法 
void Floyd(Gnode* Graph,int a[MAX][MAX],int path[MAX][MAX]);

int a[MAX][MAX]; 
int path[MAX][MAX];

int main() 
{
	int minn=INFINITY;
	int sum=0;
	int ans=-1;
    Gnode* Graph = CreateGraph();
    Floyd(Graph,a,path);
    Set_Color(11);
    cout << "最短路径矩阵：" << endl;
    for (int i = 0; i < Graph->n; i++) 
    {
        for (int j = 0; j < Graph->n; j++) 
        {
            cout << a[i][j] << " ";
            if(i!=j)
            sum+=a[i][j];
        }
         if(sum<minn)
        {
        	minn=sum;
        	ans=i;
		}
		sum=0;
        cout << endl;
    }
    Set_Color(14);
    cout<<"中心顶点编号为："<<ans<<" "<<"最小总路径为："<<minn; 
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

//创建无向图 
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
        Graph->weigh[v2][v1] = w;
    }
    return Graph;
}

//弗洛伊德算法 
void Floyd(Gnode* Graph,int a[MAX][MAX],int path[MAX][MAX])
{
  //初始化数组a,path
 
  for(int i=0;i<Graph->n;i++)
  {
    for(int j=0;j<Graph->n;j++)
    {
        a[i][j]=Graph->weigh[i][j];
        if(a[i][j]<INFINITY)
        {
            path[i][j]=i;
        }
        else
        {
            path[i][j]=-1;
        }
       } 
  }
  //三重循环计算a[i][j]
   
  //做中转点的编号
  for(int k=0;k<Graph->n;k++)
  { 
    //起点编号 
    for(int i=0;i<Graph->n;i++)
    {
    	//终止点编号
        for(int j=0;j<Graph->n;j++)
        { 
            if(a[i][j]>a[i][k]+a[k][j])
              {
                a[i][j]=a[i][k]+a[k][j];
                path[i][j]=k;
              } 
          }
      }
   }
}
