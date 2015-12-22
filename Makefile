.phony all:
all: PMS

PMS: PMS.c
	gcc PMS.c -lreadline -lhistory -ltermcap -o PMS

.PHONY clean:
clean:
	-rm -rf *.o *.exe
