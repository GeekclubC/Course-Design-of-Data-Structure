#include <iostream>
#include <algorithm>

using namespace std;

int main() 
{
    int N, M;
    cin >> N; // �����Ż�ȯ����ֵ����
    int ans[N];
    for (int i = 0; i < N; i++) 
	{
        cin >> ans[i]; // ��������ÿ���Ż�ȯ����ֵ
    }
    cin >> M; // ������Ʒ�۸�����
    int products[M];
    for (int i = 0; i < M; i++) 
	{
        cin >> products[i]; // ��������ÿ����Ʒ�ļ۸�
    }

    // ���Ż�ȯ����Ʒ�������򣬴�С��������
    sort(ans, ans + N);
    sort(products, products + M);
    
    long long max_profit = 0;

    // ������������
    int i = N - 1, j = M - 1; // ���Ż�ȯ����Ʒ��������ʼ����
    while (i >= 0 && j >= 0) 
	{
        if (ans[i] > 0 && products[j] > 0) // ����Ż�ȯ����Ʒ��Ϊ����
		{
            max_profit += (long long)ans[i] * products[j]; // �����������Ż�ȯ��ֵ����Ʒ�۸�
            i--; // �ƶ�����һ���Ż�ȯ��ֵ
            j--; // �ƶ�����һ����Ʒ�۸�
        } 
		else 
		{ // ����Ż�ȯ����Ʒ����Ϊ����������һ��Ϊ�㣬���˳�ѭ��
            break;
        }
    }

    // ������������
    i = 0, j = 0; // ���Ż�ȯ����Ʒ����Ŀ�ͷ��ʼ����
    while (i < N && j < M) 
	{
        if (ans[i] < 0 && products[j] < 0) // ����Ż�ȯ����Ʒ��Ϊ����
		{
            max_profit += (long long)ans[i] * products[j]; // �����������Ż�ȯ��ֵ����Ʒ�۸�
            i++; // �ƶ�����һ���Ż�ȯ��ֵ
            j++; // �ƶ�����һ����Ʒ�۸�
        } 
		else 
		{ // ����Ż�ȯ����Ʒ����Ϊ����������һ��Ϊ�㣬���˳�ѭ��
            break;
        }
    }
    // ����������
    cout << max_profit << endl; 

    return 0;
}

