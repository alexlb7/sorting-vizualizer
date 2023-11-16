# csort_interface.py
from ctypes import CDLL, c_int, POINTER, CFUNCTYPE

# Load the shared library (.so) or DLL
csort_lib = CDLL('core/algorithms/lib/csort.so')  # Update with the correct path and library name

# Define the function signature
bubble_sort = csort_lib.bubble_sort
selection_sort = csort_lib.selection_sort
bubble_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]
selection_sort.argtypes = [POINTER(c_int), c_int, CFUNCTYPE(None, POINTER(c_int))]

def csort(arr, method):
    size = len(arr)
    c_arr = (c_int * size)(*arr)

    def c_callback(arr_ptr):
        updated_arr =  [arr_ptr[i] for i in range(size)]
        yield f"data: {updated_arr}\n\n"

    if method == 'b':
        bubble_sort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))
    elif method == 's':
        selection_sort(c_arr, size, CFUNCTYPE(None, POINTER(c_int))(c_callback))

    yield f"data: {list(c_arr)}\n\n"
