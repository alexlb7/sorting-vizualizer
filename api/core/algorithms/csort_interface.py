# csort_interface.py
from ctypes import CDLL, c_int, POINTER, CFUNCTYPE

# Load the shared library (.so) or DLL
csort_lib = CDLL('core/algorithms/lib/csort.so')  # Update with the correct path and library name

# Define the function signature
bubble_sort = csort_lib.bubble_sort
selection_sort = csort_lib.selection_sort
insertion_sort = csort_lib.insertion_sort
bubble_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]
selection_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]
insertion_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

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
