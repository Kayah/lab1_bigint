CC=clang-3.8
SRCS=main.c biginteger.c
OBJS=$(SRCS:.c=.o)
MAIN=lab1
# CFLAGS= -O3 -Werror -fcolor-diagnostics -fsanitize=memory -fsanitize=undefined
CFLAGS=
LFLAGS=
LIBS=
build: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm *.o $(MAIN)

