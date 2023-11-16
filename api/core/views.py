import json
import random

from django.shortcuts import render
from django.http import HttpResponse

def sorting_view(request):

    arr = [random.randint(5, 1000) for _ in range(100)]

    context = {'initial_arr': arr}
    return render(request, 'sorting_template.html', context)
