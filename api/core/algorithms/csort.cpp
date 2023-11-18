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

    int partition(int arr[], int low, int high, Callback callback) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
                callback(arr, high + 1);
            }
        }

        swap(arr[i + 1], arr[high]);
        callback(arr, high + 1);
        return i + 1;
    }

    void quicksort(int arr[], int low, int high, Callback callback) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high, callback);

            quicksort(arr, low, pivotIndex - 1, callback);
            quicksort(arr, pivotIndex + 1, high, callback);
        }
    }
    void quicksortfirstcall(int arr[], int size, Callback callback) {
        quicksort(arr, 0, size - 1, callback);
    }

    int getMax(int* arr, int size) {
        int max = arr[0];
        for (int i = 1; i < size; i++)
            if (arr[i] > max)
                max = arr[i];
        return max;
    }

    void bucketsort(int arr[], int size, Callback callback) {
        int maxVal = getMax(arr, size);
        int* bucketSizes = new int[maxVal + 1]();

        for (int i = 0; i < size; ++i) {
            bucketSizes[arr[i]]++;
            callback(arr, size);
        }

        int index = 0;
        for (int i = 0; i <= maxVal; ++i) {
            for (int j = 0; j < bucketSizes[i]; ++j) {
                arr[index++] = i;
                callback(arr, size);
            }
        }
        delete[] bucketSizes;
    }

    void countingSortToRadix(int* arr, int size, int exp, Callback callback) {
        const int BASE = 10;
        int* output = new int[size];
        int* count = new int[BASE]{0};

        for (int i = 0; i < size; i++)
            count[(arr[i] / exp) % BASE]++;

        for (int i = 1; i < BASE; i++)
            count[i] += count[i - 1];

        for (int i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % BASE] - 1] = arr[i];
            callback(arr, size);
            count[(arr[i] / exp) % BASE]--;
        }

        for (int i = 0; i < size; i++)
            arr[i] = output[i];

        callback(arr, size);

        delete[] output;
        delete[] count;
    }

    void radixsort(int* arr, int size, Callback callback) {
        int max = getMax(arr, size);

        for (int exp = 1; max / exp > 0; exp *= 10)
            countingSortToRadix(arr, size, exp, callback);
    }

    void countingsort(int arr[], int size, Callback callback) {
        // Find the maximum value in the array
        int max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        // Create a count array to store the count of each element
        int count[max + 1] = {0};

        // Populate the count array
        for (int i = 0; i < size; i++) {
            count[arr[i]]++;
        }

        // Update the original array based on the count array
        int index = 0;
        for (int i = 0; i <= max; i++) {
            while (count[i] > 0) {
                arr[index++] = i;
                count[i]--;
                // Callback to monitor changes in the array
                callback(arr, size);
            }
        }
    }
}

