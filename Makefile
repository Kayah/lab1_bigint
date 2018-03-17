CC=gcc
CXX=g++
SRCS= biginteger.c
SRCXXS = main.cpp bigintarithmetic.cpp
OBJS=$(SRCS:.c=.o)
OBJS+=$(SRCXXS:.cpp=.o)
MAIN=lab1
# CFLAGS= -O3 -Werror -fcolor-diagnostics -fsanitize=memory -fsanitize=undefined
# CFLAGS=
LFLAGS=
LIBS=

ifeq ($(DEBUG), y)
CFLAGS += -DDEBUG
endif

build: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm *.o $(MAIN)

