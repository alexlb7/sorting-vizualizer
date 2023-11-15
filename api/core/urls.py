from django.urls import path

from core.views import index, HomePage

urlpatterns = [
    path("home", HomePage, name="home"),
    path("", index, name="index"),
]