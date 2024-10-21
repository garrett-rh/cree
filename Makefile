default: build

build:
	gcc -std=c17 -Wpedantic -pedantic-errors -Wconversion -Werror -Wall -Wextra tree.c -o tree