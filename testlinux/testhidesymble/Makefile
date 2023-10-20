CXX=gcc

CURDIR=$(shell pwd)
#Bsymbolic 优先使用自己的符号

test:lib1 lib2 $(CURDIR)/test.c
	$(CXX) $(CURDIR)/test.c -o test -Wl,-rpath=$(CURDIR)/ -L$(CURDIR)/ -lso1 -lso2 

lib1:$(CURDIR)/lib1/call1.c $(CURDIR)/lib1/hello1.c
	#$(CXX) -fPIC -shared -fvisibility=hidden -o $(CURDIR)/libso1.so $^
	$(CXX) -fPIC -shared -Wl,-Bsymbolic -o $(CURDIR)/libso1.so $^
	
lib2:$(CURDIR)/lib2/call2.c $(CURDIR)/lib2/hello2.c
	#$(CXX) -fPIC -shared -fvisibility=hidden -o $(CURDIR)/libso2.so $^
	$(CXX) -fPIC -shared -Wl,-Bsymbolic -o $(CURDIR)/libso2.so $^
	
	
clean:
	-rm -rf *.so test