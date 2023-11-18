from ctypes import CDLL, c_int, POINTER, CFUNCTYPE

# Load the shared library (.so) or DLL
csort_lib = CDLL('core/algorithms/lib/csort.so')  # Update with the correct path and library name

# Define the function signature
bubble_sort = csort_lib.bubble_sort
bubble_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

selection_sort = csort_lib.selection_sort
selection_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

insertion_sort = csort_lib.insertion_sort
insertion_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

heapsort = csort_lib.heapsort
heapsort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

mergesort = csort_lib.mergeSortCallback
mergesort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

quicksort = csort_lib.quicksortfirstcall
quicksort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

bucketsort = csort_lib.bucketsort
quicksort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

radixsort = csort_lib.radixsort
radixsort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

countingsort = csort_lib.countingsort
countingsort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

def csort(arr, method, result_queue):
    size = len(arr)
    c_arr = (c_int * size)(*arr)

    def c_callback(arr_ptr):
        updated_arr = [arr_ptr[i] for i in range(size)]
        result_queue.put(updated_arr)

    match method:
        case 'b':
            bubble_sort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 's':
            selection_sort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'i':
            insertion_sort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'h':
            heapsort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'm':
            mergesort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'q':
            quicksort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'k':
            bucketsort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 'r':
            radixsort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
        case 't':
            countingsort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
