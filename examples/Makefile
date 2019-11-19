# define the C compiler to use
CPP := g++

# define any compile-time flags
CPPFLAGS := -Wall -g -std=c++11 -pthread

# define any directories containing header files other than /usr/include
INCLUDES := -I../include

# define build directory
BUILD := ../build

# define library paths in addition to /usr/lib
LFLAGS := -L$(BUILD)

# define any libraries to link into executable:
LIBS := -Wl,-Bstatic -lmag3110 -Wl,-Bdynamic -lwiringPi

# define examples
BASIC := $(BUILD)/basic

.PHONY: clean

all: $(BASIC)

$(BASIC):
	$(CPP) mag3110_basic.cpp $(CPPFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(BASIC)

clean:
	$(RM) $(BASIC) *~
