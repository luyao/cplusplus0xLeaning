#!/usr/bin/perl
# Program:
# 		generate the make file
# History:
# Author: luyao(yaolu1103@gmail.com)
# Date:  2012/07/05 10:02:23

use strict;

my $head = "CC=~/bin/g++
SHELL=/bin/sh

INCLUDES=-I./ -I./include -I~/include/
LIB_PATH=-L./lib -L~/lib -L~/lib64

CPPFLAGS=-O0 -g -static -fPIC -finline-functions -Wall -Werror -pipe \\
        -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith \\
        -D_XOPEN_SOURE=500 -D_GNU_SOURCE\\
		-std=c++0x

LDFLAGS=-lpthread
";

print $head;

print "all:";
my @files = `ls *.cpp`;
foreach(@files){
    chomp;
    if (s/\.cpp//) {
        print "$_\t";
    }
}
print "\n%.o: %.cpp  
	\$(CC) \$(CPPFLAGS) -c \$< -o \$@ \$(INCLUDES) \$(LIB_PATH)
";

foreach(@files){
    print "$_:$_.o\n\t\$(CC) -o \$@ \$^ \$(LIB_PATH) \$(LDFLAGS)\n";    
}

print "clean:\n\trm -rf `ls | grep -v cpp | grep -v \.pl | grep -v make`";
