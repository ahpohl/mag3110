# define the C compiler to use
CPP := g++

# define any compile-time flags
CPPFLAGS := -Wall -g -std=c++11 -pthread

# define any directories containing header files other than /usr/include
INCLUDES := -I../include

# define library paths in addition to /usr/lib
LFLAGS := -L../build

# define any libraries to link into executable:
LIBS := -Wl,-Bstatic -lmag3110 -Wl,-Bdynamic -lwiringPi

BASIC := mag3110_basic

.PHONY: clean

all: $(BASIC)

$(BASIC):
	$(CPP) $(BASIC).cpp $(CPPFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(BASIC)

clean:
	$(RM) $(BASIC) *~
