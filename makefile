files = home.c structures.h functions.h input.h

run: $(files)
	gcc home.c
	./a.out
	
clean:
	rm -f a
	clear