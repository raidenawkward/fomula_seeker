NAME := 24

CFLAGS += -g
SRC := $(shell ls ./*.c)
OBJS := $(SRC:.c=.o)

EXLIBS := -L./lib -ltree

TAR_EXEC := b

default:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TAR_EXEC) $(EXLIBS)
clean:
	rm -f $(OBJS) $(TAR_EXEC) $(TAR_LIB) $(TAR_ALIB)
