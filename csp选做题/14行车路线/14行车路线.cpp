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
{//���ߵ���Ϣ������ͼ���ڽӱ�洢
    int to;//�ߵ���һ���˵�
    int length;//�ߵĳ���
    int type;//�ߵ�����  1��С·  0����·
    //���캯��,�����ǳ�ʼ���߶���ĳ�Ա�������Ա��ڴ����ߵ�ʵ��ʱ������и�ֵ��
    Edge(int t,int l,int _type):to(t),length(l),type(_type){}
};

ll fatigue[MAXN];//��¼���������С��ƣ�Ͷ�
int little[MAXN];//��¼ƣ�Ͷ���С������£��Ըõ�Ϊ�յ��С·�ĳ���
bool visit[MAXN];//��Ǹ������Ƿ񱻷��ʹ�
vector<Edge> graph[MAXN];//ͼ���ڽӱ�洢

struct Point
{//�����Ϣ������Dijkstra�����ȶ���
    int number;//����ı��
    ll tired;//��С��ƣ�Ͷ�
    //���캯��,�����ǳ�ʼ�������ĳ�Ա�������Ա��ڴ������ʵ��ʱ������и�ֵ��
    Point(int n,int t):number(n),tired(t){}
    bool operator < (const Point& point) const
	{//С�ں�����
        return tired > point.tired;//ƣ�Ͷ�С�����ȼ���
    }
};

void Dijkstra(int start,int n)
{
    fill(fatigue,fatigue+n+1,INF);//�Ƚ����е��ƣ�Ͷȶ�����Ϊ�����
    fill(little,little+n+1,0);//�����е�ǰ��������С·��������Ϊ0
    fill(visit,visit+n+1,false);//�����е㶼���Ϊδ���ʹ�
    fatigue[start] = 0;//��ʼ����ƣ�Ͷ�Ϊ0
    priority_queue<Point>que;
    que.push(Point(1,0));//����ʼ�����뵽���ȶ�����
    while(!que.empty())
	{//���в�Ϊ��ʱ����ѭ��
        int current = que.top().number;
        que.pop();
        if(!visit[current])
		{//����Ԫ��δ������ʱ
            visit[current] = true;//������
            for(int i=0;i<graph[current].size();i++)
			{//����õ���ڽӵ�
                int now = graph[current][i].to;//�ڽӵ���Ϊnow
                if(visit[now])
				{
                    continue;
                }
                ll cost = 0;//��¼now����С��ƣ��ֵ
                if(graph[current][i].type)
				{//��ΪС·
                    //temp��¼��now��Ϊ�յ��С·�ĳ���
                    //��current��Ϊ�յ��С·�ĳ��ȣ���������֮��ľ���
                    ll temp = little[current] + graph[current][i].length;
                    //����current��ƣ�Ͷȼ�ȥcurrentС·���ĵ�ƣ�Ͷ�
                    //�ڼ���now֮ǰС·����temp��ƽ��
                    cost = fatigue[current] - little[current] * little[current] + temp * temp;
                }
				else
				{
                    //��Ϊ��·��ֱ�Ӽ��ϴ�·�ĳ��ȼ�Ϊƣ�Ͷ�
                    cost = fatigue[current] + graph[current][i].length;
                }
                if(cost < fatigue[now])
				{//�ɳڲ���
                    fatigue[now] = cost;//����ƣ�Ͷȵ�ֵ
                    //����С·����
                    if(graph[current][i].type)
					{
                        little[now] = little[current] + graph[current][i].length;
                    }else{
                        little[now] = 0;
                    }
                    //�����µĵ���뵽������
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
        //����ͼ��������·�ڣ��㣩Ҫ���ӵ��Է����ڽӵ���
        graph[from].push_back(Edge(to,length,type));
        graph[to].push_back(Edge(from,length,type));
    }
    Dijkstra(1,n);//��㣬·��������ĸ�����
    cout<<fatigue[n];
    return 0;
}
