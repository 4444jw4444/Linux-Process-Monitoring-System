.phony all:
all: sample inf args PMS

sample: sample.c
	gcc sample.c -lreadline -lhistory -ltermcap -o sample

inf: inf.c
	gcc inf.c -o inf

args: args.c
	gcc args.c -o args

PMS: PMS.c
	gcc PMS.c -lreadline -lhistory -ltermcap -o PMS

.PHONY clean:
clean:
	-rm -rf *.o *.exe
