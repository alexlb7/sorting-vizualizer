#include <functional>

extern "C" {

    typedef void (*Callback)(int arr[], int size);

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
    // ... (other functions)

}
