
CC := arm-linux-gnueabi-gcc

ALL_FLAGS := -static $(CFLAGS)

EXECUTABLES := screenTest


.PHONY: clean

screenTest: screenTest.c
	$(CC) screenTest.c -o screenTest $(ALL_FLAGS)

clean:
	-rm $(EXECUTABLES)
