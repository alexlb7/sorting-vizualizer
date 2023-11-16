import json
from django.http import JsonResponse, StreamingHttpResponse
from core.algorithms.csort_interface import csort
from django.views.decorators.csrf import csrf_exempt
from urllib.parse import unquote
import time

@csrf_exempt
def sort_api(request):
    array_string = request.GET.get('array', '')
    method = request.GET.get('method', '')
    decoded_array_string = unquote(array_string)
    array = json.loads(decoded_array_string)

    response = StreamingHttpResponse(csort(array, method), content_type='text/event-stream')
    response['Cache-Control'] = 'no-cache'
    return response