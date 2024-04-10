#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const int MAXN = 510;
const int INF = INT_MAX;
typedef long long ll;

struct Edge
{//各边的信息，用于图的邻接表存储
    int to;//边的另一个端点
    int length;//边的长度
    int type;//边的类型  1：小路  0：大路
    //构造函数,作用是初始化边对象的成员变量，以便在创建边的实例时对其进行赋值。
    Edge(int t,int l,int _type):to(t),length(l),type(_type){}
};

ll fatigue[MAXN];//记录到达个点最小的疲劳度
int little[MAXN];//记录疲劳度最小的情况下，以该点为终点的小路的长度
bool visit[MAXN];//标记各个点是否被访问过
vector<Edge> graph[MAXN];//图的邻接表存储

struct Point
{//点的信息，用于Dijkstra的优先队列
    int number;//各点的编号
    ll tired;//最小的疲劳度
    //构造函数,作用是初始化点对象的成员变量，以便在创建点的实例时对其进行赋值。
    Point(int n,int t):number(n),tired(t){}
    bool operator < (const Point& point) const
	{//小于号重载
        return tired > point.tired;//疲劳度小的优先级大
    }
};

void Dijkstra(int start,int n)
{
    fill(fatigue,fatigue+n+1,INF);//先将所有点的疲劳度都设置为无穷大
    fill(little,little+n+1,0);//将所有点前边连续的小路长度设置为0
    fill(visit,visit+n+1,false);//将所有点都标记为未访问过
    fatigue[start] = 0;//开始结点的疲劳度为0
    priority_queue<Point>que;
    que.push(Point(1,0));//将开始结点加入到优先队列中
    while(!que.empty())
	{//队列不为空时进行循环
        int current = que.top().number;
        que.pop();
        if(!visit[current])
		{//队首元素未被访问时
            visit[current] = true;//访问它
            for(int i=0;i<graph[current].size();i++)
			{//处理该点的邻接点
                int now = graph[current][i].to;//邻接点编号为now
                if(visit[now])
				{
                    continue;
                }
                ll cost = 0;//记录now的最小的疲劳值
                if(graph[current][i].type)
				{//若为小路
                    //temp记录以now作为终点的小路的长度
                    //以current作为终点的小路的长度，加上两点之间的距离
                    ll temp = little[current] + graph[current][i].length;
                    //先用current的疲劳度减去current小路消耗的疲劳度
                    //在加上now之前小路长度temp的平方
                    cost = fatigue[current] - little[current] * little[current] + temp * temp;
                }
				else
				{
                    //若为大路，直接加上大路的长度即为疲劳度
                    cost = fatigue[current] + graph[current][i].length;
                }
                if(cost < fatigue[now])
				{//松弛操作
                    fatigue[now] = cost;//更新疲劳度的值
                    //更新小路长度
                    if(graph[current][i].type)
					{
                        little[now] = little[current] + graph[current][i].length;
                    }else{
                        little[now] = 0;
                    }
                    //将更新的点加入到队列中
                    que.push(Point(now,fatigue[now]));
                }
            }
        }
    }
}

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
	{
        int type,from,to,length;
        cin>>type>>from>>to>>length;
        //无向图，故两个路口（点）要互加到对方的邻接点中
        graph[from].push_back(Edge(to,length,type));
        graph[to].push_back(Edge(from,length,type));
    }
    Dijkstra(1,n);//起点，路口数（点的个数）
    cout<<fatigue[n];
    return 0;
}
