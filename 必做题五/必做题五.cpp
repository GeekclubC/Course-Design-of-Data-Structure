#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <Windows.h>

using namespace std;

//����������ṹ�� 
struct TreeNode 
{
    int val;
    TreeNode* childs[100];
    int child_num;//�ӽڵ������ 
    
    TreeNode(int value) : val(value), child_num(0) //���캯�� 
	{
        for (int i = 0; i < 100; i++) 
		{
            childs[i] = NULL;
        }
    }
};

// ��ӡ·��
void printPaths(TreeNode* root, int path_arr[], int path_len);

// �����������
void count_tree_depth(TreeNode* node, int deep);

// ��ӡ���νṹ
void printtree(TreeNode* root);

//����������ɫ 
void Set_Color(int x);

int main() 
{
    int n;
    cout<<"������ڵ�����"<<endl;
    cin >> n;
    TreeNode* nodes[100];
    for (int i = 0; i < 100; i++) 
	{
        nodes[i] = NULL;
    }
    cout<<"�����븸�ڵ���:"<<endl;
    for (int i = 1; i <= n; i++) 
	{
        int parent;
        cin >> parent;
        if (nodes[i] == NULL) 
		{
            nodes[i] = new TreeNode(i);
        }
        if (parent == 0) 
		{
            nodes[0] = nodes[i];
        } else {
            if (nodes[parent] == NULL) 
			{
                nodes[parent] = new TreeNode(parent);
            }
            nodes[parent]->childs[nodes[parent]->child_num] = nodes[i];
            nodes[parent]->child_num++;
        }
    }
    int path_arr[100];
    cout<<"�����Ķ��������£�"<<endl;
    printtree(nodes[0]);
    cout << endl;
    cout<<"���дӸ���㵽����Ҷ����·�����£�"<<endl;
    printPaths(nodes[0], path_arr, 0);
    return 0;
}


// ��ӡ·��
void printPaths(TreeNode* root, int path_arr[], int path_len) 
{
    if (root == NULL) 
	{
        return;
    }
    path_arr[path_len] = root->val;
    path_len++;
    if (root->child_num == 0) {
        for (int i = 0; i < path_len; i++)
		 {
            if (i > 0) 
			{
                cout << "-";
            }
            cout << path_arr[i];
        }
        cout << "��";
    } else 
	{
        for (int i = 0; i < root->child_num; i++) 
		{
            printPaths(root->childs[i], path_arr, path_len);
        }
    }
}

int tree_depth;
// �����������
void count_tree_depth(TreeNode* node, int deep) 
{
    tree_depth = deep > tree_depth ? deep : tree_depth;
    if (node->childs[0] != NULL)
        count_tree_depth(node->childs[0], deep + 1);
    if (node->childs[1] != NULL)
        count_tree_depth(node->childs[1], deep + 1);
}

// ��ӡ���νṹ
void printtree(TreeNode* root) 
{
    tree_depth = -1;
    if (root != NULL)
        count_tree_depth(root, tree_depth + 1);
    else 
	{
        cout << "****" << endl << "NULL" << endl << "****" << endl;
        return;
    }
    vector<vector<pair<int, int>>> node;
    node.resize(tree_depth + 1);
    queue<pair<TreeNode*, int>> lque;
    TreeNode* Nuptr = NULL;
    lque.push(make_pair(root, 0));
    while (1) 
	{
        TreeNode* cur = lque.front().first;
        int floor = lque.front().second;
        if (floor == tree_depth + 1)
            break;
        lque.pop();
        if (cur == NULL) 
		{
            lque.push(make_pair(Nuptr, floor + 1));
            lque.push(make_pair(Nuptr, floor + 1));
            node[floor].emplace_back(make_pair(NULL, 0));
            continue;
        }
        if (cur->childs[0] != NULL)
            lque.push(make_pair(cur->childs[0], floor + 1));
        else
            lque.push(make_pair(Nuptr, floor + 1));
        if (cur->childs[1] != NULL)
            lque.push(make_pair(cur->childs[1], floor + 1));
        else
            lque.push(make_pair(Nuptr, floor + 1));
        node[floor].emplace_back(make_pair(cur->val, 0));
    }
    unordered_map<int, vector<pair<int, int>>> hash_map;
    vector<pair<int, int>>::iterator it1;
    for (it1 = node[tree_depth].begin(); it1 != node[tree_depth].end(); it1++)
    {
        int num1 = it1 - node[tree_depth].begin() + 1;
        if (num1 % 2 == 1) {
            hash_map[(3 * num1 - 1) / 2].emplace_back(make_pair((*it1).first, tree_depth));
            (*it1).second = (3 * num1 - 1) / 2;
        }
        else {
            hash_map[(3 * num1) / 2].emplace_back(make_pair((*it1).first, tree_depth));
            (*it1).second = (3 * num1) / 2;
        }
    }
    it1--;
    int maxline = (*it1).second;

    vector<pair<int, int>>::iterator it2;
    for (int i = tree_depth - 1; i >= 0; i--) 
	{
        it1 = node[i + 1].begin();
        it2 = node[i].begin();
        while (it1 != node[i + 1].end()) 
		{
            int line1 = (*it1).second;
            it1++;
            int line2 = (*it1).second;
            it1++;
            if (it2 - node[i].begin() < node[i].size() / 2)
                (*it2).second = (line1 + line2 + 1) / 2;
            else
                (*it2).second = (line1 + line2) / 2;
            hash_map[(*it2).second].emplace_back(make_pair((*it2).first, i));
            it2++;
        }
    }
    Set_Color(2);
    cout << "*********************************************" << endl;
    for (int i = maxline; i >= 1; i--) 
	{
        vector<pair<int, int>> vec_pair = hash_map[i];
        int col = 0;
        int vec_size = vec_pair.size();
        for (int k = vec_size - 1; k >= 0; k--) 
		{
            for (; col < vec_pair[k].second; col++)
                cout << "\t";
            if (vec_pair[k].first != 0)
            {
            	Set_Color(2); 
                cout << vec_pair[k].first;
            }
            else
            {
            	Set_Color(4); 
                cout << "NULL";
            }
        }
        cout << endl;
    }
    cout << "*********************************************" << endl;
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
