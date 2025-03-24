SIZE ?= 10
HEIGHT	?= $$(expr 600 / $(SIZE))
WIDTH	?= $$(expr 800 / $(SIZE))

FILES := algorithms.c functions.c functions.h main.c priorityqueue.c shared.h ui.c ui.h
EXEC := maze

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -DHEIGHT=$(HEIGHT) -DWIDTH=$(WIDTH) -DSIZE=$(SIZE)
LDFLAGS = -lSDL2 -lm

maze: $(FILES)
	$(CC) main.c -o $(EXEC) $(LDFLAGS) $(CFLAGS)
	@echo "Code compiled"
	clear -x
	@./maze

clean:
	rm -f maze
