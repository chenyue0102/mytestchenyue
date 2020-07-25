CC=gcc
CFLAGS=`gnustep-config --objc-flags` -Wl,--no-as-needed
LDFLAGS=-lgnustep-base -lobjc -fconstant-string-class=NSConstantString
INCLUDE=-I/usr/include/GNUstep
test:libanimal.a libcat.a libperson.a TestObjectC.m
	$(CC) $(CFLAGS) $(INCLUDE) -I./ -L./ $(LDFLAGS) -lanimal -lcat -lperson TestObjectC.m -o test
	rm -rf *.a
	rm -rf *.o
	rm -rf *.d

libanimal.a:Animal.m
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -c Animal.m -o libanimal.a	

libcat.a:Cat.m
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -c Cat.m -o libcat.a	

libperson.a:Person.m
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -c Person.m -o libperson.a	
	
clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf *.d
	rm -f test
