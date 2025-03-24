SIZE	?= 10
WIDTH	?= 800
HEIGHT	?= 600
GHEIGHT	= $$(expr $(HEIGHT) / $(SIZE))
GWIDTH	= $$(expr $(WIDTH) / $(SIZE))

FILES := algorithms.c functions.c functions.h main.c priorityqueue.c shared.h ui.c ui.h
EXEC := maze

CC	= gcc
CFLAGS	= -Wall -Wextra -std=c99 -DHEIGHT=$(GHEIGHT) -DWIDTH=$(GWIDTH) -DSIZE=$(SIZE)
LDFLAGS	= -lSDL2 -lm

maze: $(FILES)
	$(CC) main.c -o $(EXEC) $(LDFLAGS) $(CFLAGS)
	@echo "Code compiled"
	clear -x
	@./maze

clean:
	rm -f $(EXEC)
