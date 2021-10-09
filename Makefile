PROYECTO = NMEA
DESTDIR = /usr/local/bin
CFLAGS = -Wall
LDFLAGS = -pthread
CC = gcc

objects := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(objects)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) %(DESTDIR)

unistall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)
