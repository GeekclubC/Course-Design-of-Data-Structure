#include <iostream>
#include <algorithm>

using namespace std;

int main() 
{
    int N, M;
    cin >> N; // 输入优惠券的面值数量
    int ans[N];
    for (int i = 0; i < N; i++) 
	{
        cin >> ans[i]; // 依次输入每种优惠券的面值
    }
    cin >> M; // 输入商品价格数量
    int products[M];
    for (int i = 0; i < M; i++) 
	{
        cin >> products[i]; // 依次输入每种商品的价格
    }

    // 对优惠券和商品进行排序，从小到大排列
    sort(ans, ans + N);
    sort(products, products + M);
    
    long long max_profit = 0;

    // 遍历正数部分
    int i = N - 1, j = M - 1; // 从优惠券和商品数组的最后开始遍历
    while (i >= 0 && j >= 0) 
	{
        if (ans[i] > 0 && products[j] > 0) // 如果优惠券和商品均为正数
		{
            max_profit += (long long)ans[i] * products[j]; // 最大利润加上优惠券面值乘商品价格
            i--; // 移动到下一个优惠券面值
            j--; // 移动到下一个商品价格
        } 
		else 
		{ // 如果优惠券和商品均不为正数，或者一方为零，则退出循环
            break;
        }
    }

    // 遍历负数部分
    i = 0, j = 0; // 从优惠券和商品数组的开头开始遍历
    while (i < N && j < M) 
	{
        if (ans[i] < 0 && products[j] < 0) // 如果优惠券和商品均为负数
		{
            max_profit += (long long)ans[i] * products[j]; // 最大利润加上优惠券面值乘商品价格
            i++; // 移动到下一个优惠券面值
            j++; // 移动到下一个商品价格
        } 
		else 
		{ // 如果优惠券和商品均不为负数，或者一方为零，则退出循环
            break;
        }
    }
    // 输出最大利润
    cout << max_profit << endl; 

    return 0;
}

