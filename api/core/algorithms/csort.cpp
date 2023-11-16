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

    // ... (other functions)

}
