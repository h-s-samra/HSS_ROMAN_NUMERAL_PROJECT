# --------------- Makefile Log --------------------
#
# 02/09/2017	HSamra	Initial Commit
#
# -------------------------------------------------

# compiler type (gcc=c / g++=c++)
CC = gcc

# compiler flags
CFLAGS = -c

exec_all: all run clean

all: roman_numeral_project increment

roman_numeral_project: main.o
	$(CC) main.o -o test_exe

main.o: main.c
	$(CC) $(CFLAGS) main.c

run:
	./test_exe

clean:
	rm -rf *o test_exe

increment:
	./increment_build.sh
open:
	./open_files.sh
	