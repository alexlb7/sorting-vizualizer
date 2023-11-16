from django.urls import path

from core.views import sorting_view
from core.algorithms.api_views import sort_api

urlpatterns = [
    path('', sorting_view, name='sorting_view'),
    path('sort_api', sort_api, name='sort_api'),
]