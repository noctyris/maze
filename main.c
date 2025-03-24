#include "algorithms.c"

int main() {
    srand(time(NULL));

    char nAlgo[1];
    printf("Quel algorithme exectuer ? \n1-\tDFS\n2-\tA*\n> ");
    scanf("%1s", nAlgo);

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
        WIDTH * SIZE,
        HEIGHT * SIZE,
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

    if (nAlgo[0] == '1') DFS(renderer);
    else if (nAlgo[0] == '2') A_star(renderer);
    else {
        printf("Erreur: entrée non valide");
        return 1;
    }

    // Quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
