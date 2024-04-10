#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#define maxx 10000
using namespace std;
typedef struct arc  //�ڽӱ�Ľڵ� 
{
	int index;    //��� 
	float weight;   //Ȩ�� 
	struct arc *next;   //ָ����һ���ڵ� 
}AR;

typedef struct MyGraph//�����ڽӾ�����ڽӱ����ַ�ʽ����ߣ�prim�㷨���ڽӱ�kruscal�㷨���ڽӾ��� 
{
	int type;//0��ʾ��������1��ʾ������
	int arcnum; //��ĸ��� 
	int vexnum; //�ߵĸ��� 
	char **vexname;  //������� 
	AR *N;  //�ڽӱ� 
	float **A;//�ڽӾ���̬����
}GH;

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

void DFS(GH *G,int *visit,int index)//����������� 
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

int connect(GH *G)//�ж��Ƿ���ͨ 
{
	int i;
	int ans;//��ͨ��֧
	ans=0; 
	int *visit=(int *)malloc(sizeof(int)*G->vexnum);//����Ƿ��Ѿ���������ڵ� 
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
		return 1;  //��ͨ 
	else
		return 0;  //����ͨ
}

int findvex(GH *G,char *s)//�ҵ��Ӧ�ı�� 
{
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		if(strcmp(s,G->vexname[i])==0)
			return i;
	}
	printf("����!\n");
	exit(0);
}

void creatgraph(GH *G)//����ͼ 
{
	FILE *fp;
	int i,j,mg,n,k;
	char s1[20],s2[20];
	AR *p;
	fp=fopen("data.txt","rb");//ֻ���ļ� 
	if(!fp)
	{
		printf("data.txt�ļ���ʧ��!\n");
		exit(0);
	}
	fscanf(fp,"%d",&n);//�����ĸ��� 
	G->vexnum=n; 
	Set_Color(6);
	printf("ͼΪ����ͼ--1��������ͼ--0��"); //�ֶ�����ͼ������ͼ��������ͼ 
	scanf("%d",&k);
	G->type=k;   
	G->N=(AR *)malloc(n*sizeof(AR));
	G->A=(float **)malloc(n*sizeof(int *));//Ϊ�ڽӾ������n����ָ��
	G->vexname=(char **)malloc(n*sizeof(char *));//Ϊ�����������n����ָ��
	G->arcnum=0;  //�ߵĸ�����ʼ��Ϊ0 
	for(i=0;i<n;i++) //��ʼ�� 
	{
		fscanf(fp,"%s",s1); //����ڵ����� 
		G->vexname[i]=(char *)malloc(strlen(s1)*sizeof(char));
		strcpy(G->vexname[i],s1); 
		G->N[i].next=NULL;	//�ڽӱ�ָ���ʼ��ָ���ָ�� 
		G->A[i]=(float *)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			G->A[i][j]=0;//�Ե�i�е�Ԫ�س�ʼ������ʼֵΪ0
	}
	while(fscanf(fp,"%s%s%d",s1,s2,&mg)!=EOF)//����� 
	{
		i=findvex(G,s1);   //�ߵ���������֮һ 
		j=findvex(G,s2);   //�ߵ���������֮һ 
		(G->arcnum)++;     //�ߵ�������һ 
		p=(AR *)malloc(sizeof(AR));
		p->index=j; //i��Ϊ���,j��Ϊ�յ�    
		p->weight=mg;//j��Ȩ��Ϊi��j��Ȩ�� 
		p->next=G->N[i].next;//�ѽڵ�p���뵽�ڽӱ�������i�� 
		G->N[i].next=p;
		G->A[i][j]=mg;        //���ڽӾ���Ķ�ӦԪ�ظ�ֵ
		if(G->type==0)        //GΪ����ͼ����Ҫ��������һ��,������һ�� 
		{
			p=(AR *)malloc(sizeof(AR));
			p->index=i;
			G->A[j][i]=mg;  
			p->weight=mg;
			p->next=G->N[j].next;
			G->N[j].next=p;
		}
	}
	fclose(fp);//�ر��ļ�	
}

void showgraph(GH *G)//���ڽӱ���ʾͼ 
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
			printf("--%s(%.2f) ",G->vexname[p->index],p->weight);//���������λ������������ 
			p=p->next;
		}		
	}
	Set_Color(2);
	printf("\nͼ��ȨֵΪ��%f\n\n",sum);
}

int findmin(float *a,int n)//�ҵ���������С����ֵ��Ӧ�ı�� 
{
	int min,i,j;
	min=maxx;
	j=0;
	for(i=0;i<n;i++)//�Ƚ������˼·,���ǲ��ܼ����һ��Ϊmin����ֹ��һ��Ϊ0 
	{
		if((a[i]!=0)&&a[i]<min)
		{
			min=a[i];
			j=i;
		}
	}
	return j;
}

void prim(GH *G)   //prim�㷨 
{
	GH *prim;    //�������ͼG����С������ 
	AR *a;
	int i,mmin,nex[G->vexnum];      //mminΪͼ������ĵ��е����������С��ı�ţ�nex��ʾ��ÿ���������ĵ�ı�� 
	float min[G->vexnum];           //ÿ���㵽��ǰ���ľ��� 
	
	prim=(GH *)malloc(sizeof(GH));  //��ʼ��ͼprim---��ʼ 
	prim->vexnum=G->vexnum;         //��ĸ�����ԭ��һ�� 
	prim->arcnum=prim->vexnum-1;    //��С�������ߵĸ���Ϊ�������-1 
	prim->type=0;       //����ͼ 
	prim->N=(AR *)malloc(prim->vexnum*sizeof(AR));
	prim->vexname=(char **)malloc(prim->vexnum*sizeof(char *));
	memset(nex,0,prim->vexnum*sizeof(int)); 
	for(i=0;i<prim->vexnum;i++)
	{
		prim->vexname[i]=(char *)malloc(strlen(G->vexname[i])*sizeof(char));
		strcpy(prim->vexname[i],G->vexname[i]);
		prim->N[i].next=NULL;
	}   //��ʼ��ͼprim---���� 
	
	min[0]=0;                               //�Ȱѵ�һ����Ž����� 
	for(i=1;i<prim->vexnum;i++) //��ʼ��min������ֵΪһ���ϴ�ֵ 
		min[i]=maxx;
	for(a=G->N[0].next;a;a=a->next)  //����������ֻ�нڵ�0������Щ���뵽0�����ĵ���һ�θ��£���ԭ���ľ��뻻λ��v0�ľ��� 
		min[a->index]=a->weight;
	for(i=1;i<prim->vexnum;i++)      //ÿ���ҵ�����������С�ĵ㲢�ŵ����� 
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
		for(a=G->N[mmin].next;a;a=a->next)//��min���и��� 
		{
			if(min[a->index]>a->weight)
			{
				nex[a->index]=mmin;
				min[a->index]=a->weight;
			}
		}
	}
	showgraph(prim);//չʾprim���ɵ���С������ 
}

void findmmin(GH *G,float *mmin)//Ѱ�Ҿ�������С����ֵ�������ڵ�λ�� 
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
				mmin[0]=i;  //min[0]�洢������ 
				mmin[1]=j;  //min[1]�洢������ 
				mmin[2]=min;//min[2]�洢��Ӧ��ֵ 
			}
		}
	}
	G->A[(int)(mmin[0])][(int)(mmin[1])]=0.;//float���� 
}

int get(int *pre,int k)//�õ��õ���ԭʼ������ 
{
	int a;
	a=k; 
	while(pre[a]!=a)
		a=pre[a];
	return a;
}

void show(GH *G)//���ڽӾ���չʾͼ 
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
	printf("\nͼ��ȨֵΪ��%f\n\n",sum);
}

void kruscal(GH *G)//kruscal�㷨 
{
	GH *kruscal;//pΪ�µ�ͼ����p����������������� 
	int i,j,pre[G->vexnum];//preָ����ǰ׺ 
	float mmins[3];  //min[0],min[1]��ʾȨֵ��С�ıߵ���������,min[3]��ʾȨ�� 
	
	kruscal=(GH *)malloc(sizeof(GH));//��ʼ�� 
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
	} //��ʼ������ 
	
	for(i=1;i<kruscal->vexnum;)//��ÿһ��������ȥ 
	{
		findmmin(G,mmins);
		if(get(pre,(int)(mmins[0]))!=get(pre,(int)(mmins[1])))   //�������������Ȳ�ͬ���������������� 
		{
			if(get(pre,(int)(mmins[0]))<get(pre,(int)(mmins[1])))
				pre[get(pre,(int)(mmins[1]))]=get(pre,(int)(mmins[0]));
			else
				pre[get(pre,(int)(mmins[0]))]=get(pre,(int)(mmins[1]));
			kruscal->A[(int)(mmins[0])][(int)(mmins[1])]=mmins[2];//�޸���Ӧ���ڽӾ��� 
			kruscal->A[(int)(mmins[1])][(int)(mmins[0])]=mmins[2];//�޸���Ӧ���ڽӾ��� 
			i++;
		}
	} 
	show(kruscal);//չʾkruscal���ɵ���С������ 
}

int main()
{
	GH G;
	Set_Color(15);
	printf("\n------------------------------��С������------------------------------\n\n");
	creatgraph(&G);//����ͼ
	printf("\n------------------------------ԭͼ------------------------------\n\n");
	showgraph(&G);//��ʾͼ
	Set_Color(15);
	printf("\n------------------------------ԭͼ��ʾ���------------------------------\n");
	if(connect(&G))//��ͨͼ������С������ 
	{
		Set_Color(3);
		printf("\n------------------------------prim�㷨�õ�����С������------------------------------\n");
		prim(&G);
		Set_Color(3);
		printf("\n------------------------------prim��ʾ���------------------------------\n");
		Set_Color(9);
		printf("\n------------------------------kruscal�㷨�õ�����С������------------------------------\n");
		kruscal(&G);
		Set_Color(9);
		printf("\n------------------------------kruscal��ʾ���------------------------------\n");
	}
	else
	{
		Set_Color(4);
		printf("\n������ͨͼ��û����С������!!!\n");
	}
	return 0;
}

