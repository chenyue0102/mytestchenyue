CXX = gcc
OBJSDIR = /root/projects/testlinuxdll
MACRODEFINE = -D"BUILDING_DLL"
#
testlinuxdll:$(OBJSDIR) export.h $(OBJSDIR) export.c
	$(CXX) -shared -Wl,-soname,libtestlinuxdll.so -o libtestlinuxdll.so.1 export.c $(MACRODEFINE)
	