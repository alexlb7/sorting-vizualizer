# csort_interface.py
from ctypes import CDLL, c_int, POINTER

# Load the shared library (.so) or DLL
csort_lib = CDLL('core/algorithms/lib/csort.so')  # Update with the correct path and library name

# Define the function signature
bubble_sort = csort_lib.bubble_sort
selection_sort = csort_lib.selection_sort
bubble_sort.argtypes = [POINTER(c_int), c_int]
selection_sort.argtypes = [POINTER(c_int), c_int]

def csort(arr,method):
    size = len(arr)
    c_arr = (c_int * size)(*arr)

    match method:
        case 'b':
            bubble_sort(c_arr, size)
        case 's':
            selection_sort(c_arr, size)
    return list(c_arr)
