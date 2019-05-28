CC=arm-none-linux-gnueabi-gcc
CFLAGS=-static -Wall

MAIN_OBJS = main.o

all: app

app: $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(MAIN_OBJS) app

