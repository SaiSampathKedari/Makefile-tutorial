all: make_dir create_files

make_dir: 
	mkdir -p d1 d2 d3

create_files: 
	touch f1.c f2.c f3.c

clean:
	rm -f f1.c f2.c f3.c 
	rm -rf d1 d2 d3

# .DEFAULT_GOAL = create_files