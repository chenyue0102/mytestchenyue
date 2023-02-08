# Generated by Django 4.1.5 on 2023-02-04 07:04

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='UserBaseInfo',
            fields=[
                ('id', models.AutoField(primary_key=True, serialize=False, verbose_name='用户ID')),
                ('user_name', models.CharField(max_length=30, verbose_name='用户名称')),
                ('password', models.CharField(max_length=32, verbose_name='密码')),
                ('status', models.IntegerField(verbose_name='状态')),
                ('create_date', models.DateTimeField(db_column='createDate', verbose_name='创建日期')),
            ],
        ),
    ]
