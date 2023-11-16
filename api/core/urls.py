from django.urls import path

from core.views import index, HomePage, sorting_view
from core.algorithms.api_views import sort_api

urlpatterns = [
    path("home", HomePage, name="home"),
    path("", index, name="index"),
    path('sorting/', sorting_view, name='sorting_view'),
    path('sorting/sort_api', sort_api, name='sort_api'),
]