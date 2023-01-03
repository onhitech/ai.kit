#=======================================
# Makefile
#=======================================
CC = gcc
CFLAGS = -c
LDFLAGS = -lwiringPi #-lm
LDLIBS =

%: %.c
	$(CC) -o $@ $< $(LDFLAGS)

default:
	@echo "Type \"make filename\" to compile..."

clean:
	rm -f *.o
