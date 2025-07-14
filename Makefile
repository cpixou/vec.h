CC := gcc
CFLAGS := -O3 -fPIC -shared

OUT ?= vec
TARGET := vec.c
HEADER := vec.h

PREFIX ?= /usr
LIBDIR := $(PREFIX)/lib
INCDIR := $(PREFIX)/include

build: $(TARGET)
	$(CC) $(CFLAGS) -o lib$(OUT).so $(TARGET)

install: lib$(OUT).so $(HEADER)
	install -d $(LIBDIR)
	install -m 755 lib$(OUT).so $(LIBDIR)/
	install -d $(INCDIR)
	install -m 644 $(HEADER) $(INCDIR)/
	ldconfig

uninstall:
	rm -f $(LIBDIR)/lib$(OUT).so
	rm -f $(INCDIR)/$(HEADER)
	ldconfig

clean:
	rm -f lib$(OUT).so

.PHONY: build install uninstall clean