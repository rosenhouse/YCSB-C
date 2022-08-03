CC=g++
CFLAGS=-std=c++17 -g -Wall -pthread -I./
LDFLAGS= -lpthread -ltbb -lhiredis -lsplinterdb -lrocksdb -lprotobuf -lgrpc
SUBDIRS=core db
GRPC_GENERATED=db/kvs.pb.cc db/kvs.grpc.pb.cc
SUBCPPSRCS=$(wildcard core/*.cc) $(wildcard db/*.cc) $(GRPC_GENERATED)
SUBCSRCS=$(wildcard core/*.c) $(wildcard db/*.c)
OBJECTS=$(SUBCPPSRCS:.cc=.o) $(SUBCSRCS:.c=.o)
EXEC=ycsbc

# for gRPC
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl


all: $(SUBDIRS) $(EXEC)

$(SUBDIRS):
	$(MAKE) -C $@

$(EXEC): $(wildcard *.cc) $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	$(RM) $(EXEC)
	rm -f *.o *.pb.cc *.pb.h

.PHONY: $(SUBDIRS) $(EXEC)

.PHONY: compile_flags.txt
compile_flags.txt:
	$(MAKE) -C db compile_flags.txt; \
	cp -p db/compile_flags.txt .
