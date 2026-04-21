# The name of your final program
TARGET = sentinel

# The compiler to use (MinGW)
CC = gcc

# Compiler flags (Wall shows all warnings, g is for debugging)
CFLAGS = -Wall -g -I"C:/TDM-GCC-64/include"

# Add -static at the beginning of the libraries
LIBS = -static -L"C:/TDM-GCC-64/lib" -lpdcurses -mconsole

# The default 'make' command
all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LIBS)

# Command to clean up the folder (type 'mingw32-make clean')
clean:
	del $(TARGET).exe