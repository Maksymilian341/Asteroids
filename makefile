CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

all:
	$(CC) main.c asteroidy.c bullety.c player.c game_states.c -o game $(CFLAGS) $(LDFLAGS)
	./game