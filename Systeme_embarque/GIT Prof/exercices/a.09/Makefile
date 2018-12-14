DIRS=$(filter-out Makefile, $(wildcard *))

all clean:
	for dir in $(DIRS); do $(MAKE) -C $$dir $@; done

