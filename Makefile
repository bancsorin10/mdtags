

all:
	gcc -O3 mdtags.c -o mdtags

clean:
	rm mdtags || true

install:
	cp -f mdtags ~/.local/bin/

re: clean all
