#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <stack>
#include <windows.h>

using namespace std;
using namespace std::chrono;

// ֱ�Ӳ�������
void insertionSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 1; i < n; ++i) 
	{
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
		{
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ϣ������
void shellSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) 
	{
        for (int i = gap; i < n; ++i) 
		{
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
			{
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// ð������
void bubbleSort(vector<int>& arr) 
{
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) 
	{
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) 
		{
            if (arr[j] > arr[j + 1]) 
			{
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) 
		{
            break;
        }
    }
}

// �������������� 
int partition(vector<int>& arr, int low, int high) 
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) 
	{
        if (arr[j] <= pivot) 
		{
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

//��������
void quickSort(vector<int>& arr, int low, int high) 
{
    stack<pair<int, int>> stk;
    stk.push({low, high});

    while (!stk.empty()) 
	{
        pair<int, int> top = stk.top();
        int start = top.first;
        int end = top.second;

        stk.pop();

        if (start < end) 
		{
            int pivot = partition(arr, start, end);
            stk.push({start, pivot - 1});
            stk.push({pivot + 1, end});
        }
    }
}

// ѡ������
void selectionSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) 
	{
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) 
		{
            if (arr[j] < arr[minIndex]) 
			{
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// ������������ 
void heapify(vector<int>& arr, int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) 
	{
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) 
	{
        largest = right;
    }
    if (largest != i) 
	{
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

//������ 
void heapSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) 
	{
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) 
	{
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// �鲢���������� 
void merge(vector<int>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) 
	{
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) 
	{
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
	{
        if (L[i] <= R[j]) 
		{
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) 
	{
        arr[k++] = L[i++];
    }
    while (j < n2) 
	{
        arr[k++] = R[j++];
    }
}

//�鲢���� 
void mergeSort(vector<int>& arr, int left, int right) 
{
    if (left < right) 
	{
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// �������������� 
int getMax(vector<int>& arr) 
{
    int maxNum = arr[0];
    int n = arr.size();
    for (int i = 1; i < n; ++i) 
	{
        if (arr[i] > maxNum) 
		{
            maxNum = arr[i];
        }
    }
    return maxNum;
}

//�������������� 
void countSort(vector<int>& arr, int exp) 
{
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    for (int i = 0; i < n; ++i) 
	{
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) 
	{
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) 
	{
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; ++i) 
	{
        arr[i] = output[i];
    }
}

//�������� 
void radixSort(vector<int>& arr) 
{
    int maxNum = getMax(arr);
    for (int exp = 1; maxNum / exp > 0; exp *= 10) 
	{
        countSort(arr, exp);
    }
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

//�����Ļ 
void Sleep_Cls(int time)
{
	Sleep(time);
	system("cls");
	//�ӳ� time ms�������Ļ
}

int main() 
{
    srand(time(NULL));
    Set_Color(11);
	cout << "���ڽ��������㷨�Ƚ�ϵͳ��" << endl;
	Set_Color(7);
	cout << "һ���ʼ�����������������samples.txt����..." << endl;
	Sleep(1000);
	// �����������ݲ����浽�ļ���
    ofstream file("samples.txt");
    if (!file) 
	{
        cout << "�޷����ļ���" << endl;
        return 1;
    }
    
    for (int i = 0; i < 10; ++i) 
	{
        vector<int> sample(50000);
        for (int j = 0; j < 50000; ++j) 
		{
            sample[j] = rand();
        }
        if (i == 0) 
		{
			Set_Color(6);
            cout << "���ڲ�����1�����ݣ���������..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "��1�����ݴ洢�ɹ���" << endl;
            cout<<endl; 
        } 
        
		else if (i == 1) 
		{
			Set_Color(6);
            cout << "���ڲ�����2�����ݣ���������..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "��2�����ݴ洢�ɹ���" << endl;
            cout<<endl; 
            sort(sample.begin(), sample.end(), greater<int>());
        }
        
        else
		{
			Set_Color(6);
            cout << "���ڲ�����"<<i+1<<"�����ݣ��������..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "��"<<i<<"�����ݴ洢�ɹ���" << endl;
            cout<<endl; 
            sort(sample.begin(), sample.end(), greater<int>());
		 } 
		 
        for (int j = 0; j < 50000; ++j) 
		{
            file << sample[j] << " ";
        }
        file << endl;
    }
    cout << "ʮ������������Ѿ�������ϣ�һ���ʼ����" << endl;
    file.close();
    Sleep_Cls(1000);

    // ���ļ��ж�ȡ�������ݲ��������򣬲�ͳ��ʱ��
    ifstream inputFile("samples.txt");
    if (!inputFile) 
	{
        cout << "�޷����ļ���" << endl;
        return 1;
    }

    string line;
    int sampleIndex = 1;
    while (getline(inputFile, line)) 
	{
        vector<int> arr;
        int num;
        istringstream iss(line);
        while (iss >> num) 
		{
            arr.push_back(num);
        }
        Set_Color(15);
        cout << "���� " << sampleIndex++ << ":" << endl;

        // ֱ�Ӳ�������
        vector<int> arr_insertion(arr);
        auto start = high_resolution_clock::now();
        insertionSort(arr_insertion);
        auto end = high_resolution_clock::now();
        duration<double, milli> duration_insertion = end - start;
        
        if (duration_insertion.count()> 4000)
		{
			Set_Color(4);
			cout << "ֱ�Ӳ�������ʱ��: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count()> 2500&&duration_insertion.count()<=4000)
		{
			Set_Color(6);
			cout << "ֱ�Ӳ�������ʱ��: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count() > 500&&duration_insertion.count()<=2500)
		{
			Set_Color(14);
			cout << "ֱ�Ӳ�������ʱ��: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count()> 20&&duration_insertion.count()<=500)
		{
			Set_Color(3);
			cout << "ֱ�Ӳ�������ʱ��: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "ֱ�Ӳ�������ʱ��: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // ϣ������
        vector<int> arr_shell(arr);
        start = high_resolution_clock::now();
        shellSort(arr_shell);
        end = high_resolution_clock::now();
        duration<double, milli> duration_shell = end - start;
        if (duration_shell.count()> 4000)
		{
			Set_Color(4);
		    cout << "ϣ������ʱ��: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count()> 2500&&duration_shell.count()<=4000)
		{
			Set_Color(6);
			cout << "ϣ������ʱ��: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count() > 500&&duration_shell.count()<=2500)
		{
			Set_Color(14);
			cout << "ϣ������ʱ��: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count()> 20&&duration_shell.count()<=500)
		{
			Set_Color(3);
			cout << "ϣ������ʱ��: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "ϣ������ʱ��: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // ð������
        vector<int> arr_bubble(arr);
        start = high_resolution_clock::now();
        bubbleSort(arr_bubble);
        end = high_resolution_clock::now();
        duration<double, milli> duration_bubble = end - start;
        if (duration_bubble.count()> 4000)
		{
			Set_Color(4);
		    cout << "ð������ʱ��: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count()> 2500&&duration_bubble.count()<=4000)
		{
			Set_Color(6);
			cout << "ð������ʱ��: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count() > 500&&duration_bubble.count()<=2500)
		{
			Set_Color(14);
			cout << "ð������ʱ��: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count()> 20&&duration_bubble.count()<=500)
		{
			Set_Color(3);
			cout << "ð������ʱ��: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "ð������ʱ��: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // ѡ������
        vector<int> arr_selection(arr);
        start = high_resolution_clock::now();
        selectionSort(arr_selection);
        end = high_resolution_clock::now();
        duration<double, milli> duration_selection = end - start;
        if (duration_selection.count()> 4000)
		{
			Set_Color(4);
		    cout << "ѡ������ʱ��: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count()> 2500&&duration_selection.count()<=4000)
		{
			Set_Color(6);
			cout << "ѡ������ʱ��: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count() > 500&&duration_selection.count()<=2500)
		{
			Set_Color(14);
			cout << "ѡ������ʱ��: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count()> 20&&duration_selection.count()<=500)
		{
			Set_Color(3);
			cout << "ѡ������ʱ��: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "ѡ������ʱ��: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // ������
        vector<int> arr_heap(arr);
        start = high_resolution_clock::now();
        heapSort(arr_heap);
        end = high_resolution_clock::now();
        duration<double, milli> duration_heap = end - start;
        if (duration_heap.count()> 4000)
		{
			Set_Color(4);
		    cout << "������ʱ��: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count()> 2500&&duration_heap.count()<=4000)
		{
			Set_Color(6);
			cout << "������ʱ��: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count() > 500&&duration_heap.count()<=2500)
		{
			Set_Color(14);
			cout << "������ʱ��: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count()> 20&&duration_heap.count()<=500)
		{
			Set_Color(3);
			cout << "������ʱ��: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "������ʱ��: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // �鲢����
        vector<int> arr_merge(arr);
        start = high_resolution_clock::now();
        mergeSort(arr_merge, 0, arr_merge.size() - 1);
        end = high_resolution_clock::now();
        duration<double, milli> duration_merge = end - start;
        if (duration_merge.count()> 4000)
		{
			Set_Color(4);
		    cout << "�鲢����ʱ��: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count()> 2500&&duration_merge.count()<=4000)
		{
			Set_Color(6);
			cout << "�鲢����ʱ��: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count() > 500&&duration_merge.count()<=2500)
		{
			Set_Color(14);
			cout << "�鲢����ʱ��: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count()> 20&&duration_merge.count()<=500)
		{
			Set_Color(3);
			cout << "�鲢����ʱ��: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "�鲢����ʱ��: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // ��������
        vector<int> arr_radix(arr);
        start = high_resolution_clock::now();
        radixSort(arr_radix);
        end = high_resolution_clock::now();
        duration<double, milli> duration_radix = end - start;
        if (duration_radix.count()> 4000)
		{
			Set_Color(4);
		    cout << "��������ʱ��: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count()> 2500&&duration_radix.count()<=4000)
		{
			Set_Color(6);
			cout << "��������ʱ��: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count() > 500&&duration_radix.count()<=2500)
		{
			Set_Color(14);
			cout << "��������ʱ��: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count()> 20&&duration_radix.count()<=500)
		{
			Set_Color(3);
			cout << "��������ʱ��: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "��������ʱ��: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);
        
         // ��������
        vector<int> arr_quick(arr);
        start = high_resolution_clock::now();
        quickSort(arr_quick, 0, arr_quick.size() - 1);
        end = high_resolution_clock::now();
        duration<double, milli> duration_quick = end - start;
        if (duration_quick.count()> 4000)
		{
			Set_Color(4);
		    cout << "��������ʱ��: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count()> 2500&&duration_quick.count()<=4000)
		{
			Set_Color(6);
			cout << "��������ʱ��: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count() > 500&&duration_quick.count()<=2500)
		{
			Set_Color(14);
			cout << "��������ʱ��: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count()> 20&&duration_quick.count()<=500)
		{
			Set_Color(3);
		    cout << "��������ʱ��: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "��������ʱ��: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);
        cout << endl;
    }

    inputFile.close();

    return 0;
}
