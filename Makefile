default: build

build:
	gcc -std=c17 -Wpedantic -pedantic-errors -Werror -Wall tree.c -o tree
