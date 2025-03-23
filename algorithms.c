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

    int GRID_HEIGHT = (int)(HEIGHT / SIZE);
    int GRID_WIDTH = (int)(WIDTH / SIZE);

    int startX = 0, startY = 0; // Point de départ
    int goalX = GRID_WIDTH - 1, goalY = GRID_HEIGHT - 1; // Point d'arrivée

    PriorityQueue openList = { .size = 0 };
    pushPQ(&openList, startX, startY, heuristic(startX, startY, goalX, goalY));

    int g[GRID_WIDTH][GRID_HEIGHT];
    int visited[GRID_WIDTH][GRID_HEIGHT];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            g[i][j] = INT_MAX; // Initialiser tous les coûts à l'infini
        }
    }
    g[startX][startY] = 0;

    int pX, pY;

    ParentEntry* parent = NULL;
    size_t parentSize = 0;

    add_parent(&parent, &parentSize, (Coordinate){startX, startY}, (Coordinate){startX, startY});

    while (!isEmpty(&openList) && !quit && !found) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Node current = popPQ(&openList);
        pX = current.x;
        pY = current.y;

        if (visited[pX][pY]) {
            continue;
        }

        visited[pX][pY] = 1;
        remove_sprite(renderer, pX * SIZE, pY * SIZE);

        if (pX == goalX && pY == goalY) {
            found = 1;
            break;
        };

        for (int i = 0; i < 4; i++) {
            int nX = (pX + DIRECTIONS[i].x) * SIZE;
            int nY = (pY + DIRECTIONS[i].y) * SIZE;
            int gridX = nX / SIZE;
            int gridY = nY / SIZE;


            if (!isCellOk(renderer, nX, nY) || visited[gridX][gridY]) {
                continue;
            }

            float tentative_g = g[pX][pY] + 1; // Coût uniforme ici

            if (tentative_g < g[gridX][gridY]) {
                g[gridX][gridY] = tentative_g;
                float f = tentative_g + heuristic(gridX, gridY, goalX, goalY);
                pushPQ(&openList, gridX, gridY, f);

                add_parent(&parent, &parentSize, (Coordinate){gridX, gridY}, (Coordinate){pX, pY});
                draw_sprite(renderer, nX, nY);
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Afficher le chemin final
    if (found) {
        for (size_t i = 0; i < openList.size; i++) {
            remove_sprite(renderer, openList.heap[i].x * SIZE, openList.heap[i].y * SIZE);
        }

        int i = 0;
        Coordinate current = {goalX, goalY};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        while (!(current.x == startX && current.y == startY)) {
            if (i > parentSize) {
                printf("Infinite loop: path can't be determined\n");
                return;
            }
            i++;

            Coordinate parentCoord = find_parent(parent, parentSize, current);

            SDL_RenderDrawLine(renderer, current.x * SIZE + SIZE / 2, current.y * SIZE + SIZE / 2,
                               find_parent(parent, parentSize, current).x * SIZE + SIZE / 2,
                               find_parent(parent, parentSize, current).y * SIZE + SIZE / 2);
            SDL_RenderPresent(renderer);
            current = parentCoord;
        }
    }

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_RenderPresent(renderer);
    }

    // free(visited);
    free(parent);
}
