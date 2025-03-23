#include "shared.h"
#include "functions.c"
#include "ui.c"

void DFS(SDL_Renderer* renderer) {
    // Event loop
    SDL_Event e;
    int quit = 0;
    int found = 0;

    int pX = 0;
    int pY = 0;

    Coordinate* stack = NULL;
    size_t stackSize = 0;

    Coordinate* visited = NULL;
    size_t visitedSize = 0;

    ParentEntry* parent = NULL;
    size_t parentSize = 0;

    push(&stack, &stackSize, (Coordinate){0,0});
    add_parent(&parent, &parentSize, (Coordinate){0,0}, (Coordinate){0,0});

    while (stackSize>0 && !quit && !found) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Coordinate coord = pop(&stack, &stackSize);
        pX = coord.x;
        pY = coord.y;

        push(&visited, &visitedSize, (Coordinate){pX, pY});

        if (endReached(renderer, pX, pY)) {
            found = 1;
        }

        remove_sprite(renderer, pX, pY);


        for (int i = 0; i < 4; i++) {
            int nX = pX + DIRECTIONS[i].x * SIZE;
            int nY = pY + DIRECTIONS[i].y * SIZE;

            if (isCellOk(renderer, nX, nY) && !find((Coordinate){nX,nY}, visited, visitedSize)) {
                push(&stack, &stackSize, (Coordinate){nX, nY});
                add_parent(&parent, &parentSize, (Coordinate){nX,nY}, (Coordinate){pX,pY});
                draw_sprite(renderer, nX, nY);
            }

        }

        SDL_RenderPresent(renderer);
    }

    // Show final path
    int i = 0;
    Coordinate* path = NULL;
    size_t pathSize = 0;
    Coordinate current = {pX, pY};
    while (!quit) {
        for (size_t i = 0; i < stackSize; i++) {
            remove_sprite(renderer, stack[i].x, stack[i].y);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        while (!(current.x == 0 && current.y == 0) && i < parentSize) {
            push(&path, &pathSize, current);
            SDL_RenderDrawLine(renderer, current.x + SIZE / 2, current.y + SIZE / 2, find_parent(parent, parentSize, current).x + SIZE / 2, find_parent(parent, parentSize, current).y + SIZE / 2);
            SDL_RenderPresent(renderer);
            current = find_parent(parent, parentSize, current);
            i++;
        }
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    free(stack);
    free(visited);
    free(parent);
    free(path);
}

void A_star(SDL_Renderer* renderer) {
    SDL_Event e;
    int quit = 0;
    int found = 0;

    // Coordinate S = {0,0};
    // Coordinate G = {(int)(WIDTH / SIZE), (int)(HEIGHT / SIZE)};
    //
    // Coordinate* openlist = {{0,0}};
    // int openListSize = 1;
    //
    // Coordinate* closedList = {{0,0}};
    // int closedListSize = 0;
}
