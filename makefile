# compiler
CC = g++

# files
SRC_FILES = $(wildcard /*.cpp)

compile: ${SRC_FILES}
	 ${CC} {SRC_FILES} -o program