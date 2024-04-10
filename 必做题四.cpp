#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <fstream>
#include <windows.h>
using namespace std;

// ������������ڵ�
typedef struct HuffmanNode 
{
    char data;          // �洢�ַ�����
    int frequency;      // �洢�ַ����ֵ�Ƶ��
    string code;        // �洢����������
    HuffmanNode* left;  // ����ָ��
    HuffmanNode* right; // �Һ���ָ��
}HuffmanNode;

// �Զ���ȽϺ������������ȶ���
struct Compare 
{
    bool operator()(HuffmanNode* a, HuffmanNode* b) const 
	{
        return a->frequency > b->frequency;
    }
};

// �Զ������ȶ���
class PriorityQueue 
{
private:
    vector<HuffmanNode*> data;

public:
    void push(HuffmanNode* node) 
	{
        data.push_back(node);
        push_heap(data.begin(), data.end(), Compare());
    }

    HuffmanNode* top() 
	{
        make_heap(data.begin(), data.end(), Compare());
        return data.front();
    }

    void pop() 
	{
        pop_heap(data.begin(), data.end(), Compare());
        data.pop_back();
    }

    bool empty() const 
	{
        return data.empty();
    }
};

// ����������ͽ�����
class Coding {
public:
    // �����������
    HuffmanNode* buildHuffmanTree(const string& input) 
	{
        // ͳһת�������ַ���ΪСд��ʽ
        string lowerCaseInput;
        for (char c : input) 
		{
            if (isalpha(c)) 
			{
                lowerCaseInput += tolower(c);
            }
        }

        // ͳ���ַ����ִ���
        map<char, int> frequencyMap;
        for (char c : lowerCaseInput) 
		{
            frequencyMap[c]++;
        }

        // �������ȶ���
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (const auto& pair : frequencyMap) 
		{
            HuffmanNode* node = new HuffmanNode{pair.first, pair.second, "", nullptr, nullptr};
            pq.push(node);
        }

        // ������������
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            HuffmanNode* parent = new HuffmanNode{'\0', left->frequency + right->frequency, "", left, right};
            pq.push(parent);
        }

        return pq.top();
    }

    // ���ɹ���������
    void generateHuffmanCode(HuffmanNode* root, string code, map<char, string>& codeMap) 
	{
        if (root->left) 
		{
            generateHuffmanCode(root->left, code + "0", codeMap);
        }
        if (root->right) 
		{
            generateHuffmanCode(root->right, code + "1", codeMap);
        }
        if (root->data != '\0')
		 {
            root->code = code;
            codeMap[root->data] = code;
        }
    }

    // ����
    string encode(const string& input, const map<char, string>& codeMap)
	 {
        string encodedText;
        for (char c : input) 
		{
            char lowercaseChar = tolower(c); // ���ַ�ת��ΪСд��ʽ
            if (codeMap.find(lowercaseChar) != codeMap.end())
			 {
                encodedText += codeMap.at(lowercaseChar);
            } else {
                // �����޷�������ַ�����ԭ��
                encodedText += c;
            }
        }
        return encodedText;
    }

    // ����
    string decode(const string& encodedText, HuffmanNode* root,string input) 
	{
        string decodedText;
        int i=0;
        HuffmanNode* current = root;
        for (char c : encodedText) 
		{
            if (c == '0') 
			{
                current = current->left;
            } 
			else 
			{
                current = current->right;
            }
            if (current->data != '\0') 
			{
                // ����ԭʼ�����ַ��Ĵ�Сд�������ӵ���������
                if (islower(current->data)&&input[i]<='z'&&input[i]>='a') 
				{
                    decodedText += current->data;
                } 
				else 
				{
                    decodedText += toupper(current->data);
                }
                current = root;
                i++;
            }
        }
        return decodedText;
    }

    // �ͷŹ��������ڴ�
    void releaseHuffmanTree(HuffmanNode* root) 
	{
        if (root) 
		{
            releaseHuffmanTree(root->left);
            releaseHuffmanTree(root->right);
            delete root;
        }
    }
};

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

int main() 
{
	int flag=0;//Ϊ1ʱ��ʾ�зǷ��ַ� 
	Set_Color(15);//��ɫ
	int i=1;
    string input;
    // �����ļ�����������
    ifstream infile("T4.txt");
    // ����ļ��Ƿ�ɹ���
    if (!infile.is_open()) 
	{
    	Set_Color(4);//��ɫ 
        cout << "�޷����ļ�" << endl;
        return 0;
    }
    cout<<"�ļ��ѳɹ���"<<endl;
    cout<<"���ڴ�T4.txt�ļ��ж�ȡ����"<<endl; 
	while (getline(infile, input)) 
	{
		Set_Color(15);//��ɫ
		cout<<"��"<<i<<"�ζ�ȡ�ļ�"<<endl; 
		cout << "���ļ��ж�ȡ���ַ���Ϊ��" << input << endl;
		i++;
		for(char ch:input)
		{
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
			{
				continue;
			}
			else
			{
				Set_Color(4);//��ɫ 
				cout<<"���棡�����ַ������зǷ��ַ����޷������������"<<endl;
				Set_Color(15);//��ɫ
				cout<<"----------------------------------------"<<endl; 
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
		flag=0;	
		continue;
		} 
		Coding huffman;
        HuffmanNode* root = huffman.buildHuffmanTree(input);
        map<char, string> codeMap;
        huffman.generateHuffmanCode(root, "", codeMap);
        string encodedText = huffman.encode(input, codeMap);
        string decodedText = huffman.decode(encodedText, root,input);
        Set_Color(6);//��ɫ 
        cout << "��������" << encodedText << endl;
        Set_Color(2);//��ɫ 
        cout << "��������" << decodedText << endl;
        Set_Color(15);//��ɫ 
        // �ͷŶ�̬������ڴ�
        cout<<"----------------------------------------"<<endl; 
        huffman.releaseHuffmanTree(root);
	}
	Set_Color(2);//��ɫ 
	cout<<"�ļ���ȡ���"<<endl;
	 // �ر��ļ�
    infile.close();
    return 0;
}
