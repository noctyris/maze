files := algorithms.c functions.c functions.h main.c priorityqueue.c shared.h ui.c ui.h

maze: $(files)
	gcc -o maze main.c -lSDL2 -lm
	@echo "Code compiled"
	clear -x
	@./maze

clean:
	rm -f maze
