#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel
    {
        for (int i = 0; i < n - 1; ++i) {
            #pragma omp for
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// Merge two sorted subarrays into a single sorted subarray
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 10; // Length of the array
    vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; // Input array
    
    // Measure sequential bubble sort performance
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> sequentialTime = end - start;
    cout << "Sequential Bubble Sort Time: " << sequentialTime.count() << " seconds\n";
    cout << "Sequential Bubble Sort Result: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // Measure parallel bubble sort performance
    start = chrono::high_resolution_clock::now();
    parallelBubbleSort(arr);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> parallelTime = end - start;
    cout << "Parallel Bubble Sort Time: " << parallelTime.count() << " seconds\n";
    cout << "Parallel Bubble Sort Result: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // Reset the array
    arr = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    
    // Measure sequential merge sort performance
    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    sequentialTime = end - start;
    cout << "Sequential Merge Sort Time: " << sequentialTime.count() << " seconds\n";
    cout << "Sequential Merge Sort Result: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // Measure parallel merge sort performance
    start = chrono::high_resolution_clock::now();
    parallelMergeSort(arr, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    parallelTime = end - start;
    cout << "Parallel Merge Sort Time: " << parallelTime.count() << " seconds\n";
    cout << "Parallel Merge Sort Result: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
