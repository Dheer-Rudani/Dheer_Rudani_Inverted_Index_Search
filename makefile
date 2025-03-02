OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
inverted_search.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe

