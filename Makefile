# --------------- Makefile log ---------------
#
#		Date			Initials		Comments
#		----			--------		--------
#		02/09/2017		HSamra			Initial Commit
#										Added roman_numeral_calc.c and test_roman_numeral_calc.c
#
# ------------------------------------------------------

# compiler type (gcc=c / g++=c++)
CC = gcc

# compiler flags
CFLAGS = -c

exec_all: all run clean

all: roman_numeral_project increment

roman_numeral_project: main.o roman_numeral_calc.o test_roman_numeral_calc.o
	$(CC) main.o roman_numeral_calc.o test_roman_numeral_calc.o -o test_exe

main.o: main.c
	$(CC) $(CFLAGS) main.c

roman_numeral_calc.o:
	$(CC) $(CFLAGS) roman_numeral_calc.c
	
test_roman_numeral_calc.o:
	$(CC) $(CFLAGS) test_roman_numeral_calc.c
	
run:
	./test_exe

clean:
	rm -rf *o test_exe

increment:
	./increment_build.sh
open:
	./open_files.sh
	