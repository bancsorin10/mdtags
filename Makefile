

all:
	gcc -O3 mdtags.c -o mdtags

clean:
	rm mdtags || true

re: clean all
