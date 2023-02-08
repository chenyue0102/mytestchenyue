from django.urls.conf import include
from django.urls import path, re_path
from test_model.views import index, new_topic, topic, topics, new_entry, edit_entry, showid

urlpatterns = [
    path(r'show/<int:id>/', showid, name='showid'),
    path(r'index.html', index, name='index'),
    path(r'new_topic.html', new_topic, name='new_topic'),
    re_path(r'^topics/$', topics, name='topics'),
    re_path(r'topics/(?P<topic_id>\d+)/', topic, name='topic'),
    re_path(r'^new_entry/(?P<topic_id>\d+)/$', new_entry, name='new_entry'),
    re_path(r'^edit_entry/(?P<entry_id>\d+)/$', edit_entry, name='edit_entry'),
]
