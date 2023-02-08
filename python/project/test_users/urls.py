from django.urls.conf import include
from django.urls import path, re_path
from django.contrib.auth.views import LoginView, LogoutView
from test_users.views import register, user_list, user_delete, user_modify

# users
urlpatterns = [
    re_path(r'^login/$', LoginView.as_view(template_name='login.html'), name='login'),
    re_path(r"^logout/$", LogoutView.as_view(), name='logout'),
    re_path(r"^register/$", register, name='register'),
    re_path(r"^user_list/$", user_list, name='user_list'),
    re_path(r"^user_delete/$", user_delete, name='user_delete'),
    re_path(r"^user_modify/", user_modify, name='user_modify'),
]
