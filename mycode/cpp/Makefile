SRCS:=$(wildcard *.cc)
ELFS:=$(SRCS:%.cc=%)
CC:=g++
all:$(ELFS)

%:%.cc
	$(CC) $< -o $@
clean:
	rm -rf $(ELFS)
