#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

int num[1005]; // ���ڴ洢Կ�׺��е�Կ��������±��ʾԿ��λ�ã�ֵ��ʾԿ�ױ��

struct Node
{
    int key; // Կ�ױ��
    int time; // ʱ��
    int sign; // �軹��ʶ����Ϊ0����Ϊ1
} node[20002]; // �洢�軹Կ�׵���Ϣ

// �Զ���ȽϺ�������������
bool cmp(Node a, Node b)
{
    if(a.time != b.time)
        return a.time < b.time; // ʱ���������
    else{
        if(a.sign != b.sign) 
            return a.sign > b.sign; // ������
        else 
            return a.key < b.key; // ���С����
    }
}

int main()
{
	ifstream a;
	a.open("data.txt",ios::in);
	if(a.eof())
	{
		cout<<"���ļ�ʧ��!"<<endl;
		a.close();
		exit(0);
	}
    int N, K;
    a>> N >> K; // ����Կ�׺д�С�Ͳ�������
    for(int i = 1; i <= N; i++) 
        num[i] = i; // ��ʼ��Կ�׺�

    int n = 0;
    while(K--)
	{
        int w,s,c;
        //cin >> w >> s >> c; // ����軹Կ�׵���Ϣ
        a>>w>>s>>c;
        // �洢��Կ�׵���Ϣ
        node[n].key = w;
        node[n].time = s;
        node[n++].sign = 0;//0����� 
        // �洢��Կ�׵���Ϣ
        node[n].key = w;
        node[n].time = s + c;
        node[n++].sign = 1;//1���� 
    }
    sort(node, node + n, cmp); // �Խ軹Կ�׵���Ϣ��������

    for(int i = 0; i < n; i++)
	{
        if(node[i].sign)
		{ // ��Կ��
            for(int j = 1; j <= N; j++)
			{
                if(!num[j])
				{
                    num[j] = node[i].key; // �ҵ���λ�����뻹��Կ��
                    break;
                }    
            }   
        }
        else
		{ // ��Կ��
            for(int j = 1; j <= N; j++)
			{
                if(num[j] == node[i].key)
                    num[j] = 0; // �ҵ���Ӧ��Կ�ף���Ϊ��λ
            }   
        } 
    }
    
    for(int i = 1; i <= N; i++)
        cout << num[i] << " "; // ������յ�Կ�׺����
    a.close();
    return 0;
}
