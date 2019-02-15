#testlinux.o
CXX = g++
OBJSDIR = /root/projects/TestLinux
CXXFLAGS = -std=c++11 -Wall -Wextra
VPATH=OBJSDIR

#testlinux
testlinux:$(OBJSDIR) main.o $(OBJSDIR) testlinux.o
	$(CXX) -o testlinux $(OBJSDIR)/main.o $(OBJSDIR)/testlinux.o -lpthread 

#testlinux.o
testlinux.o:$(OBJSDIR) TestLinux.h $(OBJSDIR) TestLinux.cpp
	$(CXX) -c $(OBJSDIR)/TestLinux.cpp -o $(OBJSDIR)/testlinux.o $(CXXFLAGS)

#main.o
main.o:${OBJSDIR} main.cpp $(OBJSDIR) TestLinux.h
	$(CXX) -c $(OBJSDIR)/main.cpp -o $(OBJSDIR)/main.o $(CXXFLAGS)

#clean
clean:
	-rm -rf $(OBJSDIR)/*.o
	-rm -rf $(OBJSDIR)/testlinux