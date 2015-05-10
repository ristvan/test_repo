LIBNAME=AVLTree
LIBNAMES=

#INCLUDES := $(pathsubst %,./../%/inc, $(LIBNAMES))
#INCDIRS:=../inc $(INCLUDES)
INCDIRS:=./include
SRCDIR:=./src
SRCS:=$(wildcard $(SRCDIR)/*.cc)

GCC:=g++
AR:=ar
RANLIB:=ranlib

ARCH:=$(shell echo `uname -m | tr "[:upper:]" "[:lower:][_*]"`-`uname -s | tr "[:upper:]" "[:lower:][_*]"`)

OUTDIR:=./lib/$(ARCH)
INTDIR:=./release/$(ARCH)/$(LIBNAME).dir
CFLAGS:=-I. $(patsubst %,-I%,$(INCDIRS)) -O3
LDFLAGS:=
LIB=lib$(LIBNAME).a

OBJS:=$(patsubst %.cc,$(INTDIR)/%.o,$(notdir $(SRCS)))

.PHONY: all

all: $(OUTDIR)/. $(INTDIR)/. $(OUTDIR)/$(LIB)

$(OUTDIR)/.:
	mkdir -p $(OUTDIR)
	chmod -R 750 $(OUTDIR)
		
$(INTDIR)/.:
	echo $@
	mkdir -p $(INTDIR)
	chmod -R 750 $(INTDIR)

$(OBJS): $(INTDIR)/%.o: $(SRCDIR)/%.cc
	$(GCC) -c $(CFLAGS) -o $@ $<


$(OUTDIR)/$(LIB): $(OBJS)
	rm -f $@
	$(AR) rc $@ $^
	$(RANLIB) $@

clean:
	rm -rf $(OUTDIR) $(INTDIR)

clean-all: clean

