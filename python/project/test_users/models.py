from django.db import models

# Create your models here.
class UserBaseInfo(models.Model):
    class StatusChoice(models.IntegerChoices):
        NORMAL = 0x00, "normal"
        DISABLE = 0x01, "disable"

    id = models.AutoField(verbose_name='用户ID', primary_key=True)
    #user_name = models.CharField(verbose_name='用户名称', max_length=30, unique=True)
    user_name = models.CharField(verbose_name='用户名称', max_length=30)
    password = models.CharField(verbose_name='密码', max_length=32)
    status = models.IntegerField(verbose_name='状态', choices = StatusChoice.choices)
    create_date = models.DateTimeField(verbose_name='创建日期', db_column='createDate')
    
    def __str__(self) -> str:
        return str(self.id)

    class Meta:
        #managed = True
        ordering = ["-create_date", "-id"]
        verbose_name = '用户信息表'
        db_table = 'user_base_info'
