CXX=g++
ifeq ($(USE_CCACHE), y)
ifeq (, $(shell which ccache))
$(error "ccache is not installed, please do apt-get install ccache")
else 
CXX=ccache g++
endif
endif

GTEST_DIR = googletest/googletest

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -O3 -g -Wall -Wextra -pthread 

LDFLAGS = -lpthread

ifeq ($(USE_GMP), y)
ifeq (, $(shell locate gmp))
$(error "gmp is not installed, please do apt-get install libgmp3-dev")
else 
LDFLAGS+=-lgmp
endif
endif

ifeq ($(USE_OPEN_MP), y)
ifeq (, $(shell locate gomp))
$(error "OPEN_MP is not installed, please do apt-get install gcc-multilib")
else 
LDFLAGS+=-lgomp
CXXFLAGS+= -fopenmp
endif
endif

TESTS = main

SOURCE_DIR = src

SRCS= $(SOURCE_DIR)/bigintarithmetic.cpp \
	  $(SOURCE_DIR)/biginteger.cpp\
	  $(SOURCE_DIR)/main.cpp

OBJS=$(SRCS:.cpp=.o)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

ifeq ($(DEBUG), y)
CPPFLAGS += -DDEBUG
endif

all : $(TESTS)
	./$(TESTS)

clean :
	rm -rf $(TESTS) gtest.a gtest_main.a src/*.o src/*.gch test/*.o

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

.cpp.o: $(SOURCE_DIR)/bigintarithmetic.h $(SOURCE_DIR)/biginteger.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TESTS): $(OBJS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
