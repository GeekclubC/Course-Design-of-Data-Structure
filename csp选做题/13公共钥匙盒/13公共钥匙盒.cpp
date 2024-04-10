#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

int num[1005]; // 用于存储钥匙盒中的钥匙情况，下标表示钥匙位置，值表示钥匙编号

struct Node
{
    int key; // 钥匙编号
    int time; // 时间
    int sign; // 借还标识，借为0，还为1
} node[20002]; // 存储借还钥匙的信息

// 自定义比较函数，用于排序
bool cmp(Node a, Node b)
{
    if(a.time != b.time)
        return a.time < b.time; // 时间早的优先
    else{
        if(a.sign != b.sign) 
            return a.sign > b.sign; // 还优先
        else 
            return a.key < b.key; // 编号小优先
    }
}

int main()
{
	ifstream a;
	a.open("data.txt",ios::in);
	if(a.eof())
	{
		cout<<"打开文件失败!"<<endl;
		a.close();
		exit(0);
	}
    int N, K;
    a>> N >> K; // 输入钥匙盒大小和操作次数
    for(int i = 1; i <= N; i++) 
        num[i] = i; // 初始化钥匙盒

    int n = 0;
    while(K--)
	{
        int w,s,c;
        //cin >> w >> s >> c; // 输入借还钥匙的信息
        a>>w>>s>>c;
        // 存储借钥匙的信息
        node[n].key = w;
        node[n].time = s;
        node[n++].sign = 0;//0代表借 
        // 存储还钥匙的信息
        node[n].key = w;
        node[n].time = s + c;
        node[n++].sign = 1;//1代表还 
    }
    sort(node, node + n, cmp); // 对借还钥匙的信息进行排序

    for(int i = 0; i < n; i++)
	{
        if(node[i].sign)
		{ // 还钥匙
            for(int j = 1; j <= N; j++)
			{
                if(!num[j])
				{
                    num[j] = node[i].key; // 找到空位，放入还的钥匙
                    break;
                }    
            }   
        }
        else
		{ // 借钥匙
            for(int j = 1; j <= N; j++)
			{
                if(num[j] == node[i].key)
                    num[j] = 0; // 找到对应的钥匙，置为空位
            }   
        } 
    }
    
    for(int i = 1; i <= N; i++)
        cout << num[i] << " "; // 输出最终的钥匙盒情况
    a.close();
    return 0;
}
