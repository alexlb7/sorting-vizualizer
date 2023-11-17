import json
from django.http import JsonResponse, StreamingHttpResponse
from core.algorithms.csort_interface import csort
from django.views.decorators.csrf import csrf_exempt
from urllib.parse import unquote
import time
import random
import threading
from queue import Queue

@csrf_exempt
def sort_api(request):
    array_string = request.GET.get('array', '')
    method = request.GET.get('method', '')
    delay = int(request.GET.get('delay', 10))
    decoded_array_string = unquote(array_string)
    array = json.loads(decoded_array_string)
    def event_stream():
        result_queue = Queue()

        # Create a thread for sorting
        sort_thread = threading.Thread(target=csort, args=(array.copy(), method, result_queue))
        sort_thread.start()

        # Wait for the sorting thread to finish
        sort_thread.join()

        # Retrieve results from the queue and yield to the client
        while not result_queue.empty():
            time.sleep(delay/1000)
            yield f"data: {result_queue.get()}\n\n"

    response = StreamingHttpResponse(event_stream(), content_type='text/event-stream')
    response['Cache-Control'] = 'no-cache'
    return response

@csrf_exempt
def rebuild_array(request):
    size = int(request.GET.get('size', 100))
    max = int(request.GET.get('size', 1000))

    arr = [random.randint(0, max) for _ in range(size)]
    return JsonResponse(arr, safe=False)