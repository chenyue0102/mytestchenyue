from django import template

register = template.Library()
@register.filter
def my_showbig(value):
    return str(value).upper()