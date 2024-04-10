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

//���������㷨 
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
    cout << "���·������" << endl;
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
    cout<<"���Ķ�����Ϊ��"<<ans<<" "<<"��С��·��Ϊ��"<<minn; 
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
        Graph->weigh[v2][v1] = w;
    }
    return Graph;
}

//���������㷨 
void Floyd(Gnode* Graph,int a[MAX][MAX],int path[MAX][MAX])
{
  //��ʼ������a,path
 
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
  //����ѭ������a[i][j]
   
  //����ת��ı��
  for(int k=0;k<Graph->n;k++)
  { 
    //����� 
    for(int i=0;i<Graph->n;i++)
    {
    	//��ֹ����
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
