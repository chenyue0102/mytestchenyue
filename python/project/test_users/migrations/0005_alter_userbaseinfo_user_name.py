# Generated by Django 4.1.5 on 2023-02-05 11:18

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('test_users', '0004_alter_userbaseinfo_status'),
    ]

    operations = [
        migrations.AlterField(
            model_name='userbaseinfo',
            name='user_name',
            field=models.CharField(max_length=30, unique=True, verbose_name='用户名称'),
        ),
    ]
