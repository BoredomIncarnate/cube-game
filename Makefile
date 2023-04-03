all:
	clang -v src/*.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o game