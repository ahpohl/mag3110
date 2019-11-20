# define the C compiler to use
CPP = g++

# define any compile-time flags
CPPFLAGS = -Wall -g -std=c++11 -pthread -c

# define any directories containing header files other than /usr/include
INCLUDES = -I../include

# define build directory
BUILD = ../build

# define library paths in addition to /usr/lib
LFLAGS = -L$(BUILD)

# define any libraries to link into executable:
LIBS = -Wl,-Bstatic -lmag3110 -Wl,-Bdynamic -lwiringPi

# define source files
SRCS = $(wildcard *.cpp)

# define object files
OBJS = $(SRCS:.cpp=.o)

# define executables
EXECS = $(OBJS:%.o=%)

.PHONY: all clean

all: $(OBJS)

.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< -o $@

.o.:
	$(CPP) $< $(LFLAGS) $(LIBS) -o $@

clean:
	-@ $(RM) *.o
	-@ $(RM) $(EXECS)
