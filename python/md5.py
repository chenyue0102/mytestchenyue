#-*- coding:UTF-8 -*-
import sys
import hashlib
import os

def getMd5(filePath):
	f = open(filePath, 'rb')
	md5Obj = hashlib.md5()
	while True:
		d = f.read(1024)
		if not d:
			break
		md5Obj.update(d)
	hashcode = md5Obj.hexdigest()
	f.close()
	md5=str(hashcode).lower()
	return md5
	

#for i in range(1,len(sys.argv)):
	#print(u"参数" + str(i)+sys.argv[i])

if __name__ == "__main__":
	if len(sys.argv) > 0:
		print(getMd5(sys.argv[1]))