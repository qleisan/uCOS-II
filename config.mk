CC = gcc

LD = ld

DIR=$(shell pwd)/../arduino

INCS = -I.\
       -I$(DIR)/sample \

CFLAGS = -Wall -Werror -g -I$(TOPDIR)/ -I$(TOPDIR)/ucos/ -I$(TOPDIR)/ucos/port/
LDFLAGS = -lpthread

$(BUILDDIR)/%.o : %.c
	@$(CC) $(CFLAGS) $(INCS) -c -o   $@ $^
	@echo "  [CC] $@"
