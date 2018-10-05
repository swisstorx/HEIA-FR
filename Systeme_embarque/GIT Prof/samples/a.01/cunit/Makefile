SUBDIRS=$(filter-out Makefile, $(wildcard *))
	
all clean:
	for dir in $(SUBDIRS); do $(MAKE) --no-print-directory -C $$dir $@; done

