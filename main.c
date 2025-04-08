#include "algorithms.c"

int main() {
    srand(time(NULL));

    // Init SDL
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("Error while initialisation");
        return 1;
    }

    // Init SDL_ttf
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Create window
    SDL_Window* window= SDL_CreateWindow(
        "Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * SIZE,
        HEIGHT * SIZE,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
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

    TTF_Font *fontS = TTF_OpenFont(FONT, 20);
    TTF_Font *fontL = TTF_OpenFont(FONT, 40);

    if (!fontS && !fontL){
        printf("Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }


    int quit = 0;

    SDL_Rect dfsButton = {100, 100, 100, 20};
    SDL_Rect astarButton = {100, 130, 100, 20};

    drawText(renderer, fontL, (SDL_Rect){WIDTH*SIZE/2-200, 50, 400, 40}, "Which algorithm?", (SDL_Color){255, 255, 255, 255});
    drawButton(renderer, fontS, dfsButton, "DFS");
    drawButton(renderer, fontS, astarButton, "A*");
    SDL_Event e;

    while (!nAlgo && !quit) {
        isClick = 0;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    clickStart.x = e.motion.x;
                    clickStart.y = e.motion.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    clickEnd.x = e.motion.x;
                    clickEnd.y = e.motion.y;
                    isClick = 1;
                    break;
            }
        }

        if (isClick) {
            buttonClicked(dfsButton, 1);
            buttonClicked(astarButton, 2);
        }

        SDL_RenderPresent(renderer);
    }

    if (nAlgo == 1) {
        SDL_SetWindowTitle(window, "Maze | DFS");
    } else if (nAlgo == 2) {
        SDL_SetWindowTitle(window, "Maze | A*");
    }

    maze(renderer,DIRECTIONS);


    /* nAlgo
     *
     * 1- DFS
     * 2- A*
     *
    */
    printf("%d\n", nAlgo);
    if (nAlgo == 1) DFS(renderer);
    else if (nAlgo == 2) A_star(renderer);
    else {
        printf("Erreur: entrée non valide\n");
        return 1;
    }

    // Quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
