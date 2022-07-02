.PHONY: all clean

all: build

clean:
	rm lib/*.so
	rm lib/*.o

build: my_string.so
	g++ -L./lib/ -Wall -Wextra -Werror -o my_string --std=c++17 src/main.cc -lstring
	export LD_LIBRARY_PATH=./lib/:$LD_LIBRARY_PATH

my_string.so: lib/search_trie.o lib/my_string.o
	g++ -shared -Wall -Wextra -Werror --std=c++17 -o lib/libstring.so lib/search_trie.o lib/my_string.o

lib/my_string.o: lib/search_trie.o src/my_string.h src/search_trie.h src/my_string.cc
	g++ -c -Wall -fPIC -Wextra -Werror --std=c++17 -o lib/my_string.o src/my_string.cc

lib/search_trie.o: src/search_trie.h src/my_string.h src/search_trie.cc
	g++ -c -Wall -fPIC -Wextra -Werror --std=c++17 -o lib/search_trie.o src/search_trie.cc
