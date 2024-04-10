#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <stdlib.h> 
using namespace std;

typedef struct Stack 
{
	// 栈顶指针
    int top; 
    
    // 栈的容量
    int capacity;
    
    // 存储数据的数组
    double* data;
}Stack;

// 创建栈
Stack* createStack(int capacity);

// 判断栈是否已满
bool isFull(Stack* stack);

// 判断栈是否为空
bool isEmpty(Stack* stack);

// 入栈
void push(Stack* stack, double item);

//出栈 
double pop(Stack* stack);

// 查看栈顶元素
double peek(Stack* stack);

// 计算两个数之间的操作结果
void calc(Stack* nums, Stack* ops);

// 获取运算符的优先级
int precedence(char op);

// 计算表达式的值
double calculate(string s, Stack* nums, Stack* ops);


//设置字体颜色 
void Set_Color(int x);

int main() {
    string input;
    cout << "请输入算数表达式，注意以#作为起始和结束符" << endl;
    cin >> input;
    char start, end;
    int len = input.length();
    start = input[0];
    end = input[len - 1];
    for(int i=1;i<len-1;i++)
    {
    	if((input[i]>='0'&&input[i]<='9')||input[i]=='+'||input[i]=='-'||input[i]=='*'||input[i]=='/'||input[i]=='^'||input[i]=='('||input[i]==')'||input[i]=='.')
    	{
    		continue;
		}
		else
		{
		Set_Color(4);
        cout << "错误！运算表达式中出现了非运算符，非数字，非括号之外的错误输入" << endl;
		}
	}
    if (start != '#' || end != '#') {
    	Set_Color(4);
        cout << "错误！请使用#作为起始和结束符" << endl;
        return 0;
    } else {
        Stack* nums = createStack(100);
        Stack* ops = createStack(100);
        string expression = input.substr(1, len - 2);
        double result = calculate(expression, nums, ops);
        cout << "算术表达式的结果为：" << result << endl;
        delete[] nums->data;
        delete[] ops->data;
        delete nums;
        delete ops;
    }
    return 0;
}
//设置字体颜色 
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

// 创建栈
Stack* createStack(int capacity) 
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = 0;
    stack->data = new double[capacity];
    return stack;
}

// 判断栈是否已满
bool isFull(Stack* stack) 
{
    return stack->top == stack->capacity;
}

// 判断栈是否为空
bool isEmpty(Stack* stack) 
{
    return stack->top == 0;
}

// 入栈
void push(Stack* stack, double item) 
{
    if (isFull(stack)) 
	{
        return;
    }
    stack->data[stack->top++] = item;
}

//出栈 
double pop(Stack* stack) 
{
    if (isEmpty(stack)) 
	{
        return -1;
    }
    return stack->data[--stack->top];
}

// 查看栈顶元素
double peek(Stack* stack) 
{
    if (isEmpty(stack)) 
	{
    	// 错误：栈为空
        return -1;
    }
    return stack->data[stack->top - 1];
}

// 计算两个数之间的操作结果
void calc(Stack* nums, Stack* ops) 
{
    double b = pop(nums);
    double a = pop(nums);
    Set_Color(4);
    cout<<"数字:"<<"	"<<b<<"	"<<"出栈"<<endl;
    cout<<"数字:"<<"	"<<a<<"	"<<"出栈"<<endl;
    char op = pop(ops);
    Set_Color(4);
    cout<<"运算符:"<<"	"<<op<<"       "<<"出栈"<<endl;
    double result;
    if(b==0&&op=='/')
	{
		Set_Color(4);
		cout<<"错误！除数不能为0！"<<endl;
		//终止程序 
		exit(1); 
	} 
    switch (op) 
	{
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = fmod(a, b);//取余 
            break;
        case '^':
            result = pow(a, b);
            break;
    }
    Set_Color(2);
    cout<<"数字:"<<"	"<<result<<"	"<<"入栈"<<endl;
    push(nums, result);
}

// 获取运算符的优先级
int precedence(char op) 
{
    if (op == '+' || op == '-') 
	{
        return 1;
    } else if (op == '*' || op == '/' || op == '%') 
	{
        return 2;
    } else if (op == '^') 
	{
        return 3;
    }
    return 0;
}

// 计算表达式的值
double calculate(string s, Stack* nums, Stack* ops) 
{
    int flag=0;
    int n = s.length();
    double sum=0;
    string numStr = "";
    for (int i = 0; i < n; i++) 
	{
        char c = s[i];
        if (c == ' ') 
		{
            continue;
        } else if (c >= '0' && c <= '9' || c == '.') 
		{
            numStr += c;
        } 
		else 
		{
            if (!numStr.empty()) 
			{
                double num = stod(numStr);//将字符串转化为浮点型 
                Set_Color(2);
                cout<<"数字:"<<"	"<<num<<"	"<<"入栈"<<endl;
                push(nums, num);
                numStr = "";
            }
            // 遇到左括号，直接入栈
            if (c == '(') 
			{
				Set_Color(2);
                cout<<"左括号  ("<<"       "<<"入栈"<<endl;
                push(ops, c);
            } 
            // 遇到右括号，执行相应的计算，并将结果入栈
			else if (c == ')') 
			{
				cout<<"右括号  )"<<"       "<<"出现"<<endl;
                while (!isEmpty(ops) && peek(ops) != '(') 
				{
                    calc(nums, ops);
                }
                // 弹出栈
                Set_Color(4);
                pop(ops);
            } 
            // 遇到运算符，执行相应的计算，并将结果入栈
			else 
			{
				
                while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(c)) 
				{
                    calc(nums, ops);
                }
                push(ops, c);
                Set_Color(2);
                cout<<"运算符:"<<"	"<<c<<"	"<<"入栈"<<endl; 
            }
        }
    }
    if (!numStr.empty()) 
	{
        double num = stod(numStr);
        Set_Color(2);
        cout<<"数字:"<<"	"<<num<<"	"<<"入栈"<<endl;
        push(nums, num);
    }
    // 对剩余的运算符进行计算
    while (!isEmpty(ops)) 
	{
        calc(nums, ops);
    }
    // 返回最终的计算结果
    return peek(nums);
}

