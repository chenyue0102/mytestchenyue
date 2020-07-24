CC=gcc
target:TestObjectC.m
	$(CC) `gnustep-config --objc-flags` -Wl,--no-as-needed -I/usr/include/GNUstep -lgnustep-base -lobjc -fconstant-string-class=NSConstantString TestObjectC.m -o test

clean:
	rm -rf test.*
	rm -rf test
