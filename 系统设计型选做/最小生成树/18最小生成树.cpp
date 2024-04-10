#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#define maxx 10000
using namespace std;
typedef struct arc  //邻接表的节点 
{
	int index;    //编号 
	float weight;   //权重 
	struct arc *next;   //指向下一个节点 
}AR;

typedef struct MyGraph//用了邻接矩阵和邻接表两种方式来存边：prim算法用邻接表，kruscal算法用邻接矩阵 
{
	int type;//0表示无向网，1表示有向网
	int arcnum; //点的个数 
	int vexnum; //边的个数 
	char **vexname;  //点的名字 
	AR *N;  //邻接表 
	float **A;//邻接矩阵动态数组
}GH;

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

void DFS(GH *G,int *visit,int index)//深度优先搜索 
{
	AR *p;
	visit[index]=1;
	p=G->N[index].next;
	while(p)
	{
		if(visit[p->index]==0)
			DFS(G,visit,p->index);
		p=p->next;
	}
}

int connect(GH *G)//判断是否连通 
{
	int i;
	int ans;//连通分支
	ans=0; 
	int *visit=(int *)malloc(sizeof(int)*G->vexnum);//标记是否已经经过这个节点 
	memset(visit,0,sizeof(int)*G->vexnum);
	for(i=1;i<G->vexnum;i++)
	{
		if(!visit[i])
		{
			DFS(G,visit,i);
			ans++;
		}
	}
	free(visit);
	if(ans==1)
		return 1;  //连通 
	else
		return 0;  //不联通
}

int findvex(GH *G,char *s)//找点对应的编号 
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		if(strcmp(s,G->vexname[i])==0)
			return i;
	}
	printf("错误!\n");
	exit(0);
}

void creatgraph(GH *G)//创建图 
{
	FILE *fp;
	int i,j,mg,n,k;
	char s1[20],s2[20];
	AR *p;
	fp=fopen("data.txt","rb");//只读文件 
	if(!fp)
	{
		printf("data.txt文件打开失败!\n");
		exit(0);
	}
	fscanf(fp,"%d",&n);//读入点的个数 
	G->vexnum=n; 
	Set_Color(6);
	printf("图为有向图--1还是无向图--0："); //手动输入图是有向图还是无向图 
	scanf("%d",&k);
	G->type=k;   
	G->N=(AR *)malloc(n*sizeof(AR));
	G->A=(float **)malloc(n*sizeof(int *));//为邻接矩阵分配n个行指针
	G->vexname=(char **)malloc(n*sizeof(char *));//为姓名矩阵分配n个行指针
	G->arcnum=0;  //边的个数初始化为0 
	for(i=0;i<n;i++) //初始化 
	{
		fscanf(fp,"%s",s1); //读入节点名字 
		G->vexname[i]=(char *)malloc(strlen(s1)*sizeof(char));
		strcpy(G->vexname[i],s1); 
		G->N[i].next=NULL;	//邻接表指针初始化指向空指针 
		G->A[i]=(float *)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			G->A[i][j]=0;//对第i行的元素初始化，初始值为0
	}
	while(fscanf(fp,"%s%s%d",s1,s2,&mg)!=EOF)//读入边 
	{
		i=findvex(G,s1);   //边的两个顶点之一 
		j=findvex(G,s2);   //边的两个顶点之一 
		(G->arcnum)++;     //边的数量加一 
		p=(AR *)malloc(sizeof(AR));
		p->index=j; //i作为起点,j作为终点    
		p->weight=mg;//j的权重为i到j的权重 
		p->next=G->N[i].next;//把节点p插入到邻接表里（起点是i） 
		G->N[i].next=p;
		G->A[i][j]=mg;        //对邻接矩阵的对应元素赋值
		if(G->type==0)        //G为无向图，则要反着再来一次,和上面一样 
		{
			p=(AR *)malloc(sizeof(AR));
			p->index=i;
			G->A[j][i]=mg;  
			p->weight=mg;
			p->next=G->N[j].next;
			G->N[j].next=p;
		}
	}
	fclose(fp);//关闭文件	
}

void showgraph(GH *G)//用邻接表显示图 
{
	int i;
	float sum=0.;
	AR *p;
	for(i=0;i<G->vexnum;i++)
	{
		printf("\n%s",G->vexname[i]);
		p=G->N[i].next;
		while(p)
		{
			sum=sum+p->weight;			
			printf("--%s(%.2f) ",G->vexname[p->index],p->weight);//控制输出的位数，保持美观 
			p=p->next;
		}		
	}
	Set_Color(2);
	printf("\n图的权值为：%f\n\n",sum);
}

int findmin(float *a,int n)//找到数组中最小的正值对应的编号 
{
	int min,i,j;
	min=maxx;
	j=0;
	for(i=0;i<n;i++)//比较排序的思路,但是不能假设第一个为min，防止第一个为0 
	{
		if((a[i]!=0)&&a[i]<min)
		{
			min=a[i];
			j=i;
		}
	}
	return j;
}

void prim(GH *G)   //prim算法 
{
	GH *prim;    //用来存放图G的最小生成树 
	AR *a;
	int i,mmin,nex[G->vexnum];      //mmin为图中树外的点中到树里距离最小点的编号，nex表示与每个点相连的点的编号 
	float min[G->vexnum];           //每个点到当前树的距离 
	
	prim=(GH *)malloc(sizeof(GH));  //初始化图prim---开始 
	prim->vexnum=G->vexnum;         //点的个数和原来一样 
	prim->arcnum=prim->vexnum-1;    //最小生成树边的个数为顶点个数-1 
	prim->type=0;       //无向图 
	prim->N=(AR *)malloc(prim->vexnum*sizeof(AR));
	prim->vexname=(char **)malloc(prim->vexnum*sizeof(char *));
	memset(nex,0,prim->vexnum*sizeof(int)); 
	for(i=0;i<prim->vexnum;i++)
	{
		prim->vexname[i]=(char *)malloc(strlen(G->vexname[i])*sizeof(char));
		strcpy(prim->vexname[i],G->vexname[i]);
		prim->N[i].next=NULL;
	}   //初始化图prim---结束 
	
	min[0]=0;                               //先把第一个点放进树中 
	for(i=1;i<prim->vexnum;i++) //初始化min，都赋值为一个较大值 
		min[i]=maxx;
	for(a=G->N[0].next;a;a=a->next)  //现在树里面只有节点0，对那些距离到0更近的点做一次更新，把原来的距离换位到v0的距离 
		min[a->index]=a->weight;
	for(i=1;i<prim->vexnum;i++)      //每次找到离树距离最小的点并放到树中 
	{
		a=(AR *)malloc(sizeof(AR));
		mmin=findmin(min,prim->vexnum);
		a->index=mmin;
		a->weight=min[mmin];
		a->next=prim->N[nex[mmin]].next;
		prim->N[nex[mmin]].next=a;
		a=(AR *)malloc(sizeof(AR));
		a->index=nex[mmin];
		a->weight=min[mmin];
		a->next=prim->N[mmin].next;
		prim->N[mmin].next=a;
		min[mmin]=0;
		for(a=G->N[mmin].next;a;a=a->next)//对min进行更新 
		{
			if(min[a->index]>a->weight)
			{
				nex[a->index]=mmin;
				min[a->index]=a->weight;
			}
		}
	}
	showgraph(prim);//展示prim生成的最小生成树 
}

void findmmin(GH *G,float *mmin)//寻找矩阵中最小的正值及其所在的位置 
{
	int i,j;
	float min=9999;
	for(i=0;i<G->vexnum;i++)
	{
		for(j=0;j<G->vexnum;j++)
		{
			if(G->A[i][j]!=0&&G->A[i][j]<min)
			{
				min=G->A[i][j];
				mmin[0]=i;  //min[0]存储横坐标 
				mmin[1]=j;  //min[1]存储纵坐标 
				mmin[2]=min;//min[2]存储相应的值 
			}
		}
	}
	G->A[(int)(mmin[0])][(int)(mmin[1])]=0.;//float类型 
}

int get(int *pre,int k)//得到该点最原始的祖先 
{
	int a;
	a=k; 
	while(pre[a]!=a)
		a=pre[a];
	return a;
}

void show(GH *G)//用邻接矩阵展示图 
{
	int i,j;
	float sum=0.;
	for(i=0;i<G->vexnum;i++)
	{
		printf("\n%s",G->vexname[i]);
		for(j=0;j<G->vexnum;j++)
		{
			if(G->A[i][j])
			{
				printf("--%s(%.2f)",G->vexname[j],G->A[i][j]);
				sum=sum+G->A[i][j];
			}
		}
	}
	Set_Color(2);
	printf("\n图的权值为：%f\n\n",sum);
}

void kruscal(GH *G)//kruscal算法 
{
	GH *kruscal;//p为新的图，由p来存放生成树的数据 
	int i,j,pre[G->vexnum];//pre指向点的前缀 
	float mmins[3];  //min[0],min[1]表示权值最小的边的两个顶点,min[3]表示权重 
	
	kruscal=(GH *)malloc(sizeof(GH));//初始化 
	kruscal->vexnum=G->vexnum; 
	kruscal->arcnum=kruscal->vexnum-1;
	kruscal->type=0;
	kruscal->A=(float **)malloc(kruscal->vexnum*sizeof(float *));
	kruscal->vexname=(char **)malloc(kruscal->vexnum*sizeof(char *));
	for(i=0;i<kruscal->vexnum;i++)
	{
		pre[i]=i;
		kruscal->vexname[i]=(char *)malloc(strlen(G->vexname[i])*sizeof(char));
		strcpy(kruscal->vexname[i],G->vexname[i]);
		kruscal->A[i]=(float *)malloc(kruscal->vexnum*sizeof(float));
		for(j=0;j<kruscal->vexnum;j++)
			kruscal->A[i][j]=0;
	} //初始化结束 
	
	for(i=1;i<kruscal->vexnum;)//把每一个点连进去 
	{
		findmmin(G,mmins);
		if(get(pre,(int)(mmins[0]))!=get(pre,(int)(mmins[1])))   //如果两个点的祖先不同，则将两个点连起来 
		{
			if(get(pre,(int)(mmins[0]))<get(pre,(int)(mmins[1])))
				pre[get(pre,(int)(mmins[1]))]=get(pre,(int)(mmins[0]));
			else
				pre[get(pre,(int)(mmins[0]))]=get(pre,(int)(mmins[1]));
			kruscal->A[(int)(mmins[0])][(int)(mmins[1])]=mmins[2];//修改相应的邻接矩阵 
			kruscal->A[(int)(mmins[1])][(int)(mmins[0])]=mmins[2];//修改相应的邻接矩阵 
			i++;
		}
	} 
	show(kruscal);//展示kruscal生成的最小生成树 
}

int main()
{
	GH G;
	Set_Color(15);
	printf("\n------------------------------最小生成树------------------------------\n\n");
	creatgraph(&G);//创建图
	printf("\n------------------------------原图------------------------------\n\n");
	showgraph(&G);//显示图
	Set_Color(15);
	printf("\n------------------------------原图显示完毕------------------------------\n");
	if(connect(&G))//连通图才有最小生成树 
	{
		Set_Color(3);
		printf("\n------------------------------prim算法得到的最小生成树------------------------------\n");
		prim(&G);
		Set_Color(3);
		printf("\n------------------------------prim显示完毕------------------------------\n");
		Set_Color(9);
		printf("\n------------------------------kruscal算法得到的最小生成树------------------------------\n");
		kruscal(&G);
		Set_Color(9);
		printf("\n------------------------------kruscal显示完毕------------------------------\n");
	}
	else
	{
		Set_Color(4);
		printf("\n不是连通图，没有最小生成树!!!\n");
	}
	return 0;
}

