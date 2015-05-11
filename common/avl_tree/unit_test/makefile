PROGNAME=AVLTreeTest
LIBNAMES=AVLTree

GTEST_DIR=/home/ristvan/appl/gtest-1.7.0
GTEST_INCLUDE_DIR=$(GTEST_DIR)/include

#INCLUDES:=$(patsubst %,./../%/include, $(LIBNAMES))
INCLUDES:=./../include $(GTEST_INCLUDE_DIR)
INCDIRS:=./include $(INCLUDES)
SRCDIR:=./src
SRCS:=$(wildcard $(SRCDIR)/*.cc)

GCC:=g++
AR:=ar
RANLIB:=ranlib

ARCH:=$(shell echo `uname -m | tr "[:upper:]" "[:lower:][_*]"`-`uname -s | tr "[:upper:]" "[:lower:][_*]"`)
LIBDIR:=../lib/$(ARCH)

OUTDIR:=./release/$(ARCH)
INTDIR:=./release/$(ARCH)/$(PROGNAME).dir
CFLAGS:=-I. $(patsubst %,-I%,$(INCDIRS)) -O3
LDFLAGS:=-L$(LIBDIR) -L$(GTEST_DIR)
LIBS:=$(LIBNAMES)

OBJS:=$(patsubst %.cc,$(INTDIR)/%.o,$(notdir $(SRCS)))

all: run

all-libs:
	$(MAKE) -C ../

all-prog: $(OUTDIR)/. $(INTDIR)/. $(OUTDIR)/$(PROGNAME)

$(OUTDIR)/.:
	mkdir -p $(OUTDIR)
	chmod -R 750 $(OUTDIR)

$(INTDIR)/.:
	mkdir -p $(INTDIR)
	chmod -R 750 $(INTDIR)

$(OBJS): $(INTDIR)/%.o: $(SRCDIR)/%.cc
	$(GCC) -c $(CFLAGS) -o $@ $<

$(OUTDIR)/$(PROGNAME): $(OBJS) $(patsubst %,$(LIBDIR)/lib%.a,$(LIBS))
	$(GCC) $(LDFLAGS) -o $@ $^ $(patsubst %,-l%,$(LIBS)) -lgtest -lpthread

run: all-libs all-prog
	$(OUTDIR)/$(PROGNAME)

clean:
	rm -f $(OUTDIR)/$(PROGNAME) $(INTDIR)/*.o core

clean-all: clean
	for X in $(LIBNAMES); do $(MAKE) -C ../$$X $@; done

