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

// 直接插入排序
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

// 希尔排序
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

// 冒泡排序
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

// 快速排序辅助函数 
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

//快速排序
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

// 选择排序
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

// 堆排序辅助函数 
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

//堆排序 
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

// 归并排序辅助函数 
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

//归并排序 
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

// 基数排序辅助函数 
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

//基数排序辅助函数 
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

//基数排序 
void radixSort(vector<int>& arr) 
{
    int maxNum = getMax(arr);
    for (int exp = 1; maxNum / exp > 0; exp *= 10) 
	{
        countSort(arr, exp);
    }
}

//调节字体颜色 
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

//清空屏幕 
void Sleep_Cls(int time)
{
	Sleep(time);
	system("cls");
	//延迟 time ms后清空屏幕
}

int main() 
{
    srand(time(NULL));
    Set_Color(11);
	cout << "正在进入排序算法比较系统！" << endl;
	Set_Color(7);
	cout << "一秒后开始生成随机数，并存入samples.txt备用..." << endl;
	Sleep(1000);
	// 生成样本数据并保存到文件中
    ofstream file("samples.txt");
    if (!file) 
	{
        cout << "无法打开文件！" << endl;
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
            cout << "正在产生第1套数据：正序样本..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "第1套数据存储成功！" << endl;
            cout<<endl; 
        } 
        
		else if (i == 1) 
		{
			Set_Color(6);
            cout << "正在产生第2套数据：逆序样本..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "第2套数据存储成功！" << endl;
            cout<<endl; 
            sort(sample.begin(), sample.end(), greater<int>());
        }
        
        else
		{
			Set_Color(6);
            cout << "正在产生第"<<i+1<<"套数据：随机样本..." << endl;
	        Sleep(300);
			Set_Color(7);
			Set_Color(11);
            sort(sample.begin(), sample.end());
            Sleep(300);
            cout << "第"<<i<<"套数据存储成功！" << endl;
            cout<<endl; 
            sort(sample.begin(), sample.end(), greater<int>());
		 } 
		 
        for (int j = 0; j < 50000; ++j) 
		{
            file << sample[j] << " ";
        }
        file << endl;
    }
    cout << "十套随机数样本已经保存完毕，一秒后开始排序。" << endl;
    file.close();
    Sleep_Cls(1000);

    // 从文件中读取样本数据并进行排序，并统计时间
    ifstream inputFile("samples.txt");
    if (!inputFile) 
	{
        cout << "无法打开文件！" << endl;
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
        cout << "样本 " << sampleIndex++ << ":" << endl;

        // 直接插入排序
        vector<int> arr_insertion(arr);
        auto start = high_resolution_clock::now();
        insertionSort(arr_insertion);
        auto end = high_resolution_clock::now();
        duration<double, milli> duration_insertion = end - start;
        
        if (duration_insertion.count()> 4000)
		{
			Set_Color(4);
			cout << "直接插入排序时间: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count()> 2500&&duration_insertion.count()<=4000)
		{
			Set_Color(6);
			cout << "直接插入排序时间: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count() > 500&&duration_insertion.count()<=2500)
		{
			Set_Color(14);
			cout << "直接插入排序时间: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_insertion.count()> 20&&duration_insertion.count()<=500)
		{
			Set_Color(3);
			cout << "直接插入排序时间: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "直接插入排序时间: " << duration_insertion.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 希尔排序
        vector<int> arr_shell(arr);
        start = high_resolution_clock::now();
        shellSort(arr_shell);
        end = high_resolution_clock::now();
        duration<double, milli> duration_shell = end - start;
        if (duration_shell.count()> 4000)
		{
			Set_Color(4);
		    cout << "希尔排序时间: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count()> 2500&&duration_shell.count()<=4000)
		{
			Set_Color(6);
			cout << "希尔排序时间: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count() > 500&&duration_shell.count()<=2500)
		{
			Set_Color(14);
			cout << "希尔排序时间: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_shell.count()> 20&&duration_shell.count()<=500)
		{
			Set_Color(3);
			cout << "希尔排序时间: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "希尔排序时间: " << duration_shell.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 冒泡排序
        vector<int> arr_bubble(arr);
        start = high_resolution_clock::now();
        bubbleSort(arr_bubble);
        end = high_resolution_clock::now();
        duration<double, milli> duration_bubble = end - start;
        if (duration_bubble.count()> 4000)
		{
			Set_Color(4);
		    cout << "冒泡排序时间: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count()> 2500&&duration_bubble.count()<=4000)
		{
			Set_Color(6);
			cout << "冒泡排序时间: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count() > 500&&duration_bubble.count()<=2500)
		{
			Set_Color(14);
			cout << "冒泡排序时间: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_bubble.count()> 20&&duration_bubble.count()<=500)
		{
			Set_Color(3);
			cout << "冒泡排序时间: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "冒泡排序时间: " << duration_bubble.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 选择排序
        vector<int> arr_selection(arr);
        start = high_resolution_clock::now();
        selectionSort(arr_selection);
        end = high_resolution_clock::now();
        duration<double, milli> duration_selection = end - start;
        if (duration_selection.count()> 4000)
		{
			Set_Color(4);
		    cout << "选择排序时间: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count()> 2500&&duration_selection.count()<=4000)
		{
			Set_Color(6);
			cout << "选择排序时间: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count() > 500&&duration_selection.count()<=2500)
		{
			Set_Color(14);
			cout << "选择排序时间: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_selection.count()> 20&&duration_selection.count()<=500)
		{
			Set_Color(3);
			cout << "选择排序时间: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "选择排序时间: " << duration_selection.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 堆排序
        vector<int> arr_heap(arr);
        start = high_resolution_clock::now();
        heapSort(arr_heap);
        end = high_resolution_clock::now();
        duration<double, milli> duration_heap = end - start;
        if (duration_heap.count()> 4000)
		{
			Set_Color(4);
		    cout << "堆排序时间: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count()> 2500&&duration_heap.count()<=4000)
		{
			Set_Color(6);
			cout << "堆排序时间: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count() > 500&&duration_heap.count()<=2500)
		{
			Set_Color(14);
			cout << "堆排序时间: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_heap.count()> 20&&duration_heap.count()<=500)
		{
			Set_Color(3);
			cout << "堆排序时间: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "堆排序时间: " << duration_heap.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 归并排序
        vector<int> arr_merge(arr);
        start = high_resolution_clock::now();
        mergeSort(arr_merge, 0, arr_merge.size() - 1);
        end = high_resolution_clock::now();
        duration<double, milli> duration_merge = end - start;
        if (duration_merge.count()> 4000)
		{
			Set_Color(4);
		    cout << "归并排序时间: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count()> 2500&&duration_merge.count()<=4000)
		{
			Set_Color(6);
			cout << "归并排序时间: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count() > 500&&duration_merge.count()<=2500)
		{
			Set_Color(14);
			cout << "归并排序时间: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_merge.count()> 20&&duration_merge.count()<=500)
		{
			Set_Color(3);
			cout << "归并排序时间: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "归并排序时间: " << duration_merge.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);

        // 基数排序
        vector<int> arr_radix(arr);
        start = high_resolution_clock::now();
        radixSort(arr_radix);
        end = high_resolution_clock::now();
        duration<double, milli> duration_radix = end - start;
        if (duration_radix.count()> 4000)
		{
			Set_Color(4);
		    cout << "基数排序时间: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count()> 2500&&duration_radix.count()<=4000)
		{
			Set_Color(6);
			cout << "基数排序时间: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count() > 500&&duration_radix.count()<=2500)
		{
			Set_Color(14);
			cout << "基数排序时间: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_radix.count()> 20&&duration_radix.count()<=500)
		{
			Set_Color(3);
			cout << "基数排序时间: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "基数排序时间: " << duration_radix.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);
        
         // 快速排序
        vector<int> arr_quick(arr);
        start = high_resolution_clock::now();
        quickSort(arr_quick, 0, arr_quick.size() - 1);
        end = high_resolution_clock::now();
        duration<double, milli> duration_quick = end - start;
        if (duration_quick.count()> 4000)
		{
			Set_Color(4);
		    cout << "快速排序时间: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count()> 2500&&duration_quick.count()<=4000)
		{
			Set_Color(6);
			cout << "快速排序时间: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count() > 500&&duration_quick.count()<=2500)
		{
			Set_Color(14);
			cout << "快速排序时间: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else if (duration_quick.count()> 20&&duration_quick.count()<=500)
		{
			Set_Color(3);
		    cout << "快速排序时间: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		
		else
		{
			Set_Color(11);
			cout << "快速排序时间: " << duration_quick.count() << " ms" << endl;
			Set_Color(7);
		}
		Set_Color(7);
        cout << endl;
    }

    inputFile.close();

    return 0;
}
