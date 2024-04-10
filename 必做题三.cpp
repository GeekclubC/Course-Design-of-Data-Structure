#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <stdlib.h> 
using namespace std;

typedef struct Stack 
{
	// ջ��ָ��
    int top; 
    
    // ջ������
    int capacity;
    
    // �洢���ݵ�����
    double* data;
}Stack;

// ����ջ
Stack* createStack(int capacity);

// �ж�ջ�Ƿ�����
bool isFull(Stack* stack);

// �ж�ջ�Ƿ�Ϊ��
bool isEmpty(Stack* stack);

// ��ջ
void push(Stack* stack, double item);

//��ջ 
double pop(Stack* stack);

// �鿴ջ��Ԫ��
double peek(Stack* stack);

// ����������֮��Ĳ������
void calc(Stack* nums, Stack* ops);

// ��ȡ����������ȼ�
int precedence(char op);

// ������ʽ��ֵ
double calculate(string s, Stack* nums, Stack* ops);


//����������ɫ 
void Set_Color(int x);

int main() {
    string input;
    cout << "�������������ʽ��ע����#��Ϊ��ʼ�ͽ�����" << endl;
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
        cout << "����������ʽ�г����˷�������������֣�������֮��Ĵ�������" << endl;
		}
	}
    if (start != '#' || end != '#') {
    	Set_Color(4);
        cout << "������ʹ��#��Ϊ��ʼ�ͽ�����" << endl;
        return 0;
    } else {
        Stack* nums = createStack(100);
        Stack* ops = createStack(100);
        string expression = input.substr(1, len - 2);
        double result = calculate(expression, nums, ops);
        cout << "�������ʽ�Ľ��Ϊ��" << result << endl;
        delete[] nums->data;
        delete[] ops->data;
        delete nums;
        delete ops;
    }
    return 0;
}
//����������ɫ 
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

// ����ջ
Stack* createStack(int capacity) 
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = 0;
    stack->data = new double[capacity];
    return stack;
}

// �ж�ջ�Ƿ�����
bool isFull(Stack* stack) 
{
    return stack->top == stack->capacity;
}

// �ж�ջ�Ƿ�Ϊ��
bool isEmpty(Stack* stack) 
{
    return stack->top == 0;
}

// ��ջ
void push(Stack* stack, double item) 
{
    if (isFull(stack)) 
	{
        return;
    }
    stack->data[stack->top++] = item;
}

//��ջ 
double pop(Stack* stack) 
{
    if (isEmpty(stack)) 
	{
        return -1;
    }
    return stack->data[--stack->top];
}

// �鿴ջ��Ԫ��
double peek(Stack* stack) 
{
    if (isEmpty(stack)) 
	{
    	// ����ջΪ��
        return -1;
    }
    return stack->data[stack->top - 1];
}

// ����������֮��Ĳ������
void calc(Stack* nums, Stack* ops) 
{
    double b = pop(nums);
    double a = pop(nums);
    Set_Color(4);
    cout<<"����:"<<"	"<<b<<"	"<<"��ջ"<<endl;
    cout<<"����:"<<"	"<<a<<"	"<<"��ջ"<<endl;
    char op = pop(ops);
    Set_Color(4);
    cout<<"�����:"<<"	"<<op<<"       "<<"��ջ"<<endl;
    double result;
    if(b==0&&op=='/')
	{
		Set_Color(4);
		cout<<"���󣡳�������Ϊ0��"<<endl;
		//��ֹ���� 
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
            result = fmod(a, b);//ȡ�� 
            break;
        case '^':
            result = pow(a, b);
            break;
    }
    Set_Color(2);
    cout<<"����:"<<"	"<<result<<"	"<<"��ջ"<<endl;
    push(nums, result);
}

// ��ȡ����������ȼ�
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

// ������ʽ��ֵ
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
                double num = stod(numStr);//���ַ���ת��Ϊ������ 
                Set_Color(2);
                cout<<"����:"<<"	"<<num<<"	"<<"��ջ"<<endl;
                push(nums, num);
                numStr = "";
            }
            // ���������ţ�ֱ����ջ
            if (c == '(') 
			{
				Set_Color(2);
                cout<<"������  ("<<"       "<<"��ջ"<<endl;
                push(ops, c);
            } 
            // ���������ţ�ִ����Ӧ�ļ��㣬���������ջ
			else if (c == ')') 
			{
				cout<<"������  )"<<"       "<<"����"<<endl;
                while (!isEmpty(ops) && peek(ops) != '(') 
				{
                    calc(nums, ops);
                }
                // ����ջ
                Set_Color(4);
                pop(ops);
            } 
            // �����������ִ����Ӧ�ļ��㣬���������ջ
			else 
			{
				
                while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(c)) 
				{
                    calc(nums, ops);
                }
                push(ops, c);
                Set_Color(2);
                cout<<"�����:"<<"	"<<c<<"	"<<"��ջ"<<endl; 
            }
        }
    }
    if (!numStr.empty()) 
	{
        double num = stod(numStr);
        Set_Color(2);
        cout<<"����:"<<"	"<<num<<"	"<<"��ջ"<<endl;
        push(nums, num);
    }
    // ��ʣ�����������м���
    while (!isEmpty(ops)) 
	{
        calc(nums, ops);
    }
    // �������յļ�����
    return peek(nums);
}

