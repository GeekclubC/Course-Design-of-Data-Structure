#include <iostream>
#include <algorithm>

using namespace std;
int a[1010], b[1010] = {0};
int main()
{
    int n, index;
    cin >> n;
    // ����n������
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n); // �����������������

    // ͳ��ÿ���������ֵĴ���
    for (int i = 0; i < n; ++i)
    {
        index = a[i];
        b[index] = 1; // ��Ǹ��������ֹ�
    }

    // ����ÿ�������ĳ��ִ���
    for (int i = 0; i < n - 1; ++i)
    {
        index = a[i];
        if (a[i] == a[i + 1])
        {
            ++b[index];
        }
    }

    int max = b[1], tag = 0;
    // ���ճ��ִ����Ӷൽ��������
    for (int k = 0; k <= a[n - 1]; ++k)
    {
        for (int i = 1; i <= a[n - 1]; ++i)
        {
            if (max < b[i])
            {
                max = b[i];
                tag = i;
            }
        }
        if (max != 0 && tag != 0)
            cout << tag << " " << max << endl;
        b[tag] = 0;
        max = 0;
    }
    return 0;
}
