# compiler attributes
CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra -pedantic

# directory attributes
TARGET = program
CPPFILES = main.cpp enum_to_str.cpp zoo_classes.cpp zoo_manager.cpp
HEADERS = enum_to_str.h input_validation.h zoo_classes.h

$(TARGET): $(CPPFILES) $(HEADERS)
	$(CC) $(CCFLAGS) $(CPPFILES) -o $(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)
