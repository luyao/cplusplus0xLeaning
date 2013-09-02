CC=~/bin/g++
SHELL=/bin/sh

INCLUDES=-I./ -I./include -I~/include/
LIB_PATH=-L./lib -L~/lib -L~/lib64

CPPFLAGS=-O0 -g -static -fPIC -finline-functions -Wall -Werror -pipe \
        -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith \
        -D_XOPEN_SOURE=500 -D_GNU_SOURCE\
		-std=c++0x

LDFLAGS=-lpthread
all:autoTest	lambda	rvalues	staticAssert	thread	
%.o: %.cpp  
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDES) $(LIB_PATH)
autoTest:autoTest.o
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
lambda:lambda.o
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
rvalues:rvalues.o
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
staticAssert:staticAssert.o
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
thread:thread.o
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
clean:
	rm -rf `ls | grep -v cpp | grep -v .pl | grep -v make`