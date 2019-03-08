names=['zhangsan','lisi','houqi','maba']
print(names[0:2])
print(names[1:])
print(names[-2:])

squares=[value**2 for value in range(1,11)]
print(squares)

digits=[1,3,6,0]
print('max' + str(max(digits)) + " min" + str(min(digits)) + " sum" + str(sum(digits)))

even_number = list(range(2,11,2))
print(even_number)

print(3**4)

for value in range(1,6):
	print(value)
numbers = list(range(1,6))
print(numbers)


for name in names:
	print(name)

print(len(names))
names.sort(reverse = True)
print(names)
names.remove('lisi')
print(names)

message = "  hello world "
print(message)
print(message.title())
print(message.upper())
print(message.lower())

print(message.rstrip())
print(message.lstrip())
print(message.strip())

message = "I'm python"
print(message)

names=['zhangsan','lisi','houqi','maba']
print(names)
print(names[0].title())
print(names[-1].title())
names.append('zhujiu')
print(names)
names.insert(0, 'first')
print(names)
del names[0]
print(names)
lastname=names.pop(-1)
print('lastname ' + lastname)

color="blue"
if color=="blue" or color=="red":
	print("")
else:
	print("")
	
ids=[1,2,3]
num=2
if 	num in ids:
	print("find")
else:
	print("not find")


