import requests

def test_request():
    url = "https://hacker-news.firebaseio.com/v0/topstories.json"
    r = requests.get(url)
    print("status_code:", r.status_code)
    print(r.json())

def output_fun(text, my_age):
    text = "new text"
    out_msg = "output:" + text + " age:" + str(my_age)
    print(out_msg)
    return out_msg


def fun_array(*arr):
    print("count:" + str(len(arr)) + str(arr))


def fun_map(**my_map):
    print("count:" + str(len(my_map.items())) + str(my_map))


print("Hello, world!")

msg = " hello, kitty "
print(msg.title())

msg = msg.strip()
print(msg)

print(msg.upper() + str(123))

cars = ['honda', 'audi', 'bmw']
sorted_cars = sorted(cars)
print(str(cars) + " " + str(sorted_cars) + str(len(sorted_cars)))
cars.sort(reverse=True)
print(cars)

cars.append('toyota')
print(cars)

car = cars.pop(0)
print(cars)

del cars[-1]
for one_car in cars:
    print(one_car)

for num in range(1, 10):
    print(num)

ls = list(range(1, 11, 2))
print(str(ls) + " min:" + str(min(ls)) + " sum:" + str(sum(ls)))

print(ls[1:3])

# 复制列表
copy_list = ls[:]

# 元组 不可修改
dim = ("honda", "bwm", "audi")
for d in dim:
    print(d)

age = 19
if age >= 18:
    print("ok")
elif age > 12:
    print("young")
else:
    print("failed")

dic = {"name": "kitty", "age": 20}
print(dic["name"] + " age:" + str(dic["age"]))

dic["name"] = "tom"
print(dic['name'])
del dic["age"]
dic['birthday'] = 1900

for key, value in dic.items():
    print("key:" + str(key) + " value:" + str(value))

if dic.get("name1") is None:
    print("is none")
else:
    print("not null")
print("keys:" + str(dic.keys()) + " value:" + str(dic.values()))

# new_age = input("input age:")
# dic["age"] = int(new_age)
print(dic)

input_text = "kitty"
my_text = output_fun(input_text, 123)
print(my_text + " input_text:" + input_text)
fun_array("honda", "bwm")
fun_map(first_name="tom", age=20)
test_request()
