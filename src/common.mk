SRCS = *.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

$(OBJS): $(SRCS)
	gcc -c $(FLAGS) $(SRCS) $(LIBS)

clean:
	rm -f *.o 
