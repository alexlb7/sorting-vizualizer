import json
import random

from django.shortcuts import render
from django.http import HttpResponse, JsonResponse

def sorting_view(request):

    arr = [random.randint(5, 100) for _ in range(100)]

    context = {'initial_arr': arr}
    return render(request, 'sorting_template.html', context)
