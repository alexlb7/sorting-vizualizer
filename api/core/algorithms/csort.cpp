#include <functional>

extern "C" {

    typedef void (*Callback)(int arr[], int size);
    typedef void (*MergeCallback)(int array[], int left, int mid, int right);

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void bubble_sort(int arr[], int size, Callback callback) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    callback(arr, size);
                }
            }
        }
    }

    void selection_sort(int arr[], int size, Callback callback) {
        for (int i = 0; i < size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                swap(arr[min_idx], arr[i]);
                callback(arr, size);
            }
        }
    }
    void insertion_sort(int arr[], int size, Callback callback) {
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }

            if (j + 1 != i) {
                arr[j + 1] = key;
                callback(arr, size);
            }
        }
    }
    void heapify(int arr[], int size, int i, Callback callback) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] > arr[largest])
            largest = left;

        if (right < size && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            callback(arr, size);
            heapify(arr, size, largest, callback);
        }
    }

    void heapsort(int arr[], int size, Callback callback) {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(arr, size, i, callback);

        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            callback(arr, size);
            heapify(arr, i, 0, callback);
        }
    }

    void merge(int arr[], int left, int middle, int right, Callback callback) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        int leftArray[n1];
        int rightArray[n2];

        for (int i = 0; i < n1; i++)
            leftArray[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArray[j] = arr[middle + 1 + j];

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                arr[k] = leftArray[i];
                i++;
            } else {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
            callback(arr, k);  // Callback when the array is modified
        }

        while (i < n1) {
            arr[k] = leftArray[i];
            i++;
            k++;
            callback(arr, k);  // Callback when the array is modified
        }

        while (j < n2) {
            arr[k] = rightArray[j];
            j++;
            k++;
            callback(arr, k);  // Callback when the array is modified
        }
    }

    void mergeSort(int arr[], int left, int right, Callback callback) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            mergeSort(arr, left, middle, callback);
            mergeSort(arr, middle + 1, right, callback);

            merge(arr, left, middle, right, callback);
        }
    }

    void mergeSortCallback(int arr[], int size, Callback callback) {
        mergeSort(arr, 0, size - 1, callback);
    }
    // ... (other functions)

}
