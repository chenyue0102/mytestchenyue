CC=gcc
CFLAGS=`gnustep-config --objc-flags` -Wl,--no-as-needed
LDFLAGS=-lgnustep-base -lobjc -fconstant-string-class=NSConstantString
INCLUDE=-I/usr/include/GNUstep
test:libanimal.a TestObjectC.m
	$(CC) $(CFLAGS) $(INCLUDE) -I./ -L./ $(LDFLAGS) -lanimal TestObjectC.m -o test
	rm -rf *.a
	rm -rf *.o
	rm -rf *.d

libanimal.a:Animal.m
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -c Animal.m -o libanimal.a	
	
	
clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.d
	rm -f test
