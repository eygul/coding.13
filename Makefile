CC = gcc
CFLAGS = -Wall -O2
TARGET = tlb
all: $(TARGET)
$(TARGET): tlb.c
	$(CC) $(CFLAGS) -o $(TARGET) tlb.c
clean:
	rm -f $(TARGET)