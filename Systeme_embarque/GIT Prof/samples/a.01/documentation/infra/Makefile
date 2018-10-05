SUBDIRS=$(filter-out Makefile doc, $(wildcard *))
	
all clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done

