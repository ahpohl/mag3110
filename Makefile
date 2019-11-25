# define the C compiler to use
CPP = g++

# define any compile-time flags
CPPFLAGS = -Wall -Wextra -g -std=c++11 -pthread -fPIC -shared

# define any directories containing header files other than /usr/include
INCLUDES = -I./include

# define library paths in addition to /usr/lib
LFLAGS =

# define any libraries to link into executable:
LIBS =

# define src directory
SRC_DIR = src

# define the output directory
OBJ_DIR = build

# define the C source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# define the objects
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# define the file names 
STATIC_LIB = libmag3110.a
SHARED_LIB = libmag3110.so

# get version info from git and compile into the program
# https://embeddedartistry.com/blog/2016/10/27/giving-you-build-a-version
version := $(subst -, ,$(shell git describe --long --dirty --tags))
COMMIT := $(strip $(word 3, $(version)))
COMMITS_PAST := $(strip $(word 2, $(version)))
DIRTY := $(strip $(word 4, $(version)))
ifneq ($(COMMITS_PAST), 0)
    BUILD_INFO_COMMITS := "."$(COMMITS_PAST)
endif
ifneq ($(DIRTY),)
    BUILD_INFO_DIRTY :="+"
endif

export BUILD_TAG :=$(strip $(word 1, $(version)))
export BUILD_INFO := $(COMMIT)$(BUILD_INFO_COMMITS)$(BUILD_INFO_DIRTY)

CPPFLAGS += -DVERSION_BUILD_DATE=\""$(shell date "+%F %T")"\" \
            -DVERSION_BUILD_MACHINE=\""$(shell echo `whoami`@`hostname`)"\" \
            -DVERSION_TAG=\"$(BUILD_TAG)\" \
            -DVERSION_BUILD=\"$(BUILD_INFO)\"

LIB_VERSION := $(BUILD_TAG:v%=%)

# define examples directory
EXAMPLE := examples

.PHONY: build clean install docs examples

all: shared static

build:
	mkdir -p $(OBJ_DIR)

shared: build $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -o $(OBJ_DIR)/$(SHARED_LIB) $(OBJS) $(LFLAGS) $(LIBS)

static: build $(OBJS)
	$(AR) rcs $(OBJ_DIR)/$(STATIC_LIB) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(OBJ_DIR)/$(SHARED_LIB) $(OBJ_DIR)/$(STATIC_LIB) *~
	$(MAKE) -C $(EXAMPLE) clean

# define install directories
ifeq ($(PREFIX),)
  PREFIX = /usr/local
endif

install: all
	install -d $(DESTDIR)$(PREFIX)/lib
	install -d $(DESTDIR)$(PREFIX)/include
	install -m 644 $(OBJ_DIR)/$(STATIC_LIB) $(DESTDIR)$(PREFIX)/lib/$(STATIC_LIB)
	install -m 755 $(OBJ_DIR)/$(SHARED_LIB) $(DESTDIR)$(PREFIX)/lib/$(SHARED_LIB).$(LIB_VERSION)
	install -m 644 include/mag3110.hpp $(DESTDIR)$(PREFIX)/include/libmag3110.hpp

docs:
	doxygen Doxyfile

examples: all
	$(MAKE) -C $(EXAMPLE)
