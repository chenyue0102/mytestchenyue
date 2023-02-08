from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.contrib.auth import logout, login, authenticate
from django.contrib.auth.forms import UserCreationForm
from django.http import Http404, HttpResponse
from test_users.forms import UserBaseInfoForm, UserBaseInfoModifyForm
from test_users.models import UserBaseInfo
import json


# Create your views here.
def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse('index'))

def register(request):
    if (request.method == "GET"):
        myform = UserBaseInfoForm()
        return render(request, "register.html", {'form_obj': myform})
    elif (request.method == 'POST'):
        print("post")
        f = UserBaseInfoForm(request.POST)
        if (f.is_valid()):
            print("valid")
            k = f.save(commit=True)
            print("type:" + type(k).__name__)
            return render(request, "register_success.html", {'user':f})
        else:
            print("not valid")
            errors = f.errors
            print(errors)
            return render(request, "register.html", {'form_obj': f, 'errors':errors})

def user_list(request):
    userinfos = UserBaseInfo.objects.filter()
    return render(request, "user_list.html", {"users":userinfos})

def user_delete(request):
    if request.method != 'POST':
        raise Http404("must post")
    
    token = request.META.get("X-CSRFToken")
    json_data = json.loads(request.body)
    #print("delete body:" + str(request.body))
    user_name = json_data.get("user_name")
    user_id = json_data.get("user_id")
    #print("delete user_name:" + str(user_name) + " id:" + str(user_id))
    info = UserBaseInfo.objects.get(id=user_id)
    if info == None:
        print("not find user")
    else:
        info.delete()
        #print("delete user success")
        resp = HttpResponse()
        resp.content = 'delete success'
        resp.status_code = 200
    return resp

def user_modify(request):
    if request.method == 'GET':
        #print("user_modify GET")
        token = request.META.get("X-CSRFToken")
        user_name = request.GET.get("user_name")
        user_id = request.GET.get("user_id")
        #print("user_modify user_name:" + str(user_name) + " id:" + str(user_id))
        info = UserBaseInfo.objects.get(id=user_id)
        #print("UserBaseInfo:" + str(type(info)))
        if info == None:
            print("not find user")
        else:
            f = UserBaseInfoModifyForm(instance=info)
            context = {'form_obj':f}
            #print("modify form:" + str(type(f)))
            return render(request, "user_modify.html", context)
            #return HttpResponseRedirect(reverse('index'))
    elif request.method == 'POST':
        json_data = json.loads(request.body)
        #print("body:" + str(request.body))
        user_id = json_data.get("id")
       
        info = UserBaseInfo.objects.get(id=user_id)
        if info == None:
            print("user none")
            return Http404()
        
        info.user_name = json_data.get("user_name")
        info.status = json_data.get("status")
        info.save()
        resp = HttpResponse()
        resp.content = 'modify success'
        resp.status_code = 200
        return resp

           
def register2(request):
    if request.method != 'POST':
        form = UserCreationForm()
    else:
        form = UserCreationForm(data=request.POST)

    if form.is_valid():
        new_user = form.save()
        authenticated_user = authenticate(username=new_user.username,
            password=request.POST['password1'])
        login(request, authenticated_user)
        return HttpResponseRedirect(reverse('index'))

    context = {'form': form}
    return render(request, 'register.html', context)
