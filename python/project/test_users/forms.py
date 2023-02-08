from django import forms
from test_users.models import UserBaseInfo

class UserBaseInfoForm(forms.ModelForm):
    class Meta:
        model = UserBaseInfo
        #fields = '__all__'
        fields = ['user_name','password','status','create_date']
    user_name = forms.CharField(label='用户名称', min_length=6, max_length=30,
    error_messages={'required':'用户名称不能为空', 'min_length':'长度', 'invalid':'输入正确的用户名'})
    password=forms.CharField(label='密码', min_length=6, max_length=32,
    widget=forms.widgets.PasswordInput(attrs={"class":"password"}, render_value=True))

class UserBaseInfoModifyForm(forms.ModelForm):
    class Meta:
        model = UserBaseInfo
        fields = '__all__'
        exclude = ()
    id = forms.CharField(label="用户id")
    user_name = forms.CharField(label='用户名称', min_length=6, max_length=30,
    error_messages={'required':'用户名称不能为空', 'min_length':'长度', 'invalid':'输入正确的用户名'})
    password=forms.CharField(label='密码', min_length=6, max_length=32,
    widget=forms.widgets.PasswordInput(attrs={"class":"password"}, render_value=True))

    def __init__(self, *args, **kwargs):
        super(forms.ModelForm, self).__init__(*args, **kwargs)
        #self.fields['user_name'].widget.attrs['readonly'] = True
        self.fields['id'].widget = forms.HiddenInput()
        self.fields['create_date'].widget = forms.HiddenInput()
    
    