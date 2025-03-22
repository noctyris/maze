#include "main.h"
#include "ui.c"

void maze(SDL_Renderer* renderer, Coordinate* directions) {
    SDL_SetRenderDrawColor(renderer, WALLC, WALLC, WALLC, 255);
    for (int x = SIZE; x < WIDTH; x += SIZE * 2) {
        for (int y = SIZE; y < HEIGHT; y += SIZE * 2) {
            SDL_Rect rect = {x, y, SIZE, SIZE};
            SDL_RenderFillRect(renderer, &rect);

            Coordinate randomCoord = chooseRandomCoordinate(directions);
            SDL_Rect adjacentRect = {x + randomCoord.x * SIZE, y + randomCoord.y * SIZE, SIZE, SIZE};
            SDL_RenderFillRect(renderer, &adjacentRect);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 200, 50, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){0, 0, SIZE, SIZE});

    SDL_SetRenderDrawColor(renderer, 200, 50, 0, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){WIDTH - SIZE, HEIGHT - SIZE, SIZE, SIZE});
}

int main(int argc, char* argv[]) {
    // Init SDL
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("Error while initialisation");
        return 1;
    }

    // Create window
    SDL_Window* window= SDL_CreateWindow(
        "Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Error while creating window");
        SDL_Quit();
        return 1;
    }

    // Create renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        printf("Error while creating renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    maze(renderer,DIRECTIONS);

    // Event loop
    SDL_Event e;
    int quit = 0;

    Coordinate* stack = NULL;
    size_t stackSize = 0;

    Coordinate* visited = NULL;
    size_t visitedSize = 0;

    push(&stack, &stackSize, (Coordinate){0,0});

    while (stackSize>0 && !quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Coordinate coord = pop(&stack, &stackSize);
        int pX = coord.x;
        int pY = coord.y;

        push(&visited, &visitedSize, (Coordinate){pX, pY});

        for (int i = 0; i < 4; i++) {
            int nX = pX + DIRECTIONS[i].x * SIZE;
            int nY = pY + DIRECTIONS[i].y * SIZE;

            if (isCellOk(renderer, nX, nY)) {
                push(&stack, &stackSize, (Coordinate){pX, pY});
            }

            remove_sprite(renderer, pX, pY);
            draw_sprite(renderer, nX, nY);

            // TODO: Continue the pathfinder

        }

        SDL_RenderPresent(renderer);
    }

    if (!quit) {
        SDL_Delay(2000);
    }

    // Quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
