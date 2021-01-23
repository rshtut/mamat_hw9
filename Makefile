CC = g++
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c++11
OBJS=field.o ip.o port.o string.o main.o
EXEC=firewall.exe
RM=rm -rf libfirewall.so *.o *.exe

firewall.exe: $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -L. -lfirewall -L. -linput

main.o: field.h ip.h port.h string.h input.h
	$(CC) $(CFLAGS) -c -fpic main.cpp

libfirewall.so: field.o port.o ip.o string.o
	$(CCLINK) -shared field.o ip.o port.o string.o -o libfirewall.so

port.o: port.cpp port.h field.h string.h
	$(CC) $(CFLAGS) -c -fpic port.cpp

ip.o: ip.cpp ip.h field.h string.h
	$(CC) $(CFLAGS) -c -fpic ip.cpp

field.o: field.cpp field.h string.h
	$(CC) $(CFLAGS) -c -fpic field.cpp

string.o: string.cpp string.h
	$(CC) $(CFLAGS) -c -fpic string.cpp

clean:
	$(RM)