
SUBDIRS = port

TARGET = $(BUILDDIR)/ucos.o
OBJS = $(BUILDDIR)/ucos_ii.o \
       $(BUILDDIR)/os_dbg_r.o \
       $(BUILDDIR)/port.o

all: subdirs $(TARGET)

subdirs:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1; done

$(TARGET): $(OBJS)
	@$(LD) -r $^ -o $@ 
	@echo "  [LD] $@"

clean:
	find . -name "*.o" -o -name "*.exe" | xargs rm -rf  

include $(TOPDIR)/config.mk
