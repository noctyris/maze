#include "utils.h"

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

    Coordinate DIRECTIONS[] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };

    maze(renderer,DIRECTIONS);

    // Event loop
    SDL_Event e;
    int quit = 0;

    Coordinate* stack = NULL;
    size_t stackSize = 0;

    Coordinate* visited = NULL;
    size_t visitedSize = 0;

    push(&stack, &stackSize, (Coordinate){0,0});

    while (stackSize!=0 && !quit) {
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
