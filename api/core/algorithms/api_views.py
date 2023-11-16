import json
from django.http import JsonResponse
from django.http import HttpResponse
from core.algorithms.csort_interface import csort
from django.views.decorators.csrf import csrf_exempt

@csrf_exempt
def sort_api(request):
    if request.method == 'POST':
        arr = json.loads(request.POST.get('arr'))
        method = request.POST.get('method')
        sorted_arr = csort(arr,method)
        return JsonResponse(sorted_arr, safe=False)
    return JsonResponse({'error': 'Invalid request method'})
