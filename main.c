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
        800, 600,
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
    TTF_Font *fontL = TTF_OpenFont(FONT, 30);

    if (!fontS && !fontL){
        printf("Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    int quit = 0;
    int nAlgo = 0;

    SDL_Rect dfsButton = {100, 100, 100, 20};
    SDL_Rect astarButton = {100, 130, 100, 20};
    SDL_Rect dijkstraButton = {100, 160, 100, 20};

    int sizeWriting = 0;
    char sizeEntry[3] = "";
    int sizeEntryLength = 0;
    SDL_Rect sizeInputField = {600, 100, 100, 20};

    int widthWriting = 0;
    char widthEntry[3] = "";
    int widthEntryLength = 0;
    SDL_Rect widthInputField = {600, 300, 100, 20};

    int heightWriting = 0;
    char heightEntry[3] = "";
    int heightEntryLength = 0;
    SDL_Rect heightInputField = {600, 500, 100, 20};

    drawText(renderer, fontL, (SDL_Rect){0, 50, 300, 40}, "Algorithms", (SDL_Color){255, 255, 255, 255});
    drawText(renderer, fontL, (SDL_Rect){650, 50, 0, 40}, "Cell size", (SDL_Color){255, 255, 255, 255});
    drawText(renderer, fontL, (SDL_Rect){650, 250, 0, 40}, "Grid width", (SDL_Color){255, 255, 255, 255});
    drawText(renderer, fontL, (SDL_Rect){650, 450, 0, 40}, "Grid height", (SDL_Color){255, 255, 255, 255});
    SDL_Event e;

    while (!nAlgo && !quit) {
        isClick = 0;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = 1;
                    return 0;
                case SDL_MOUSEBUTTONDOWN:
                    clickStart.x = e.motion.x;
                    clickStart.y = e.motion.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    clickEnd.x = e.motion.x;
                    clickEnd.y = e.motion.y;
                    isClick = 1;
                    break;
                case SDL_MOUSEMOTION:
                    mousePos.x = e.motion.x;
                    mousePos.y = e.motion.y;
                    break;
                case SDL_KEYDOWN:
                    if (sizeWriting) {
                        if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                            // Ajouter le chiffre à sizeEntry si la limite n'est pas atteinte
                            if (sizeEntryLength < 2) { // Taille maximale : 3 caractères
                                sizeEntry[sizeEntryLength] = '0' + (e.key.keysym.sym - SDLK_0);
                                sizeEntryLength++;
                                sizeEntry[sizeEntryLength] = '\0'; // Terminateur de chaîne
                            }
                        } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
                            // Supprimer le dernier caractère avec Backspace
                            if (sizeEntryLength > 0) {
                                sizeEntryLength--;
                                sizeEntry[sizeEntryLength] = '\0';
                            }
                        }
                        SIZE = atoi(sizeEntry);
                    }
                    if (widthWriting) {
                        if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                            // Ajouter le chiffre à widthEntry si la limite n'est pas atteinte
                            if (widthEntryLength < 4) { // Taille maximale : 3 caractères
                                widthEntry[widthEntryLength] = '0' + (e.key.keysym.sym - SDLK_0);
                                widthEntryLength++;
                                widthEntry[widthEntryLength] = '\0'; // Terminateur de chaîne
                            }
                        } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
                            // Supprimer le dernier caractère avec Backspace
                            if (widthEntryLength > 0) {
                                widthEntryLength--;
                                widthEntry[widthEntryLength] = '\0';
                            }
                        }
                        WIDTH = atoi(widthEntry);
                    }
                    if (heightWriting) {
                        if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                            // Ajouter le chiffre à heightEntry si la limite n'est pas atteinte
                            if (heightEntryLength < 4) { // Taille maximale : 3 caractères
                                heightEntry[heightEntryLength] = '0' + (e.key.keysym.sym - SDLK_0);
                                heightEntryLength++;
                                heightEntry[heightEntryLength] = '\0'; // Terminateur de chaîne
                            }
                        } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
                            // Supprimer le dernier caractère avec Backspace
                            if (heightEntryLength > 0) {
                                heightEntryLength--;
                                heightEntry[heightEntryLength] = '\0';
                            }
                        }
                        HEIGHT = atoi(heightEntry);
                    }
                    break;
            }
        }

        if (isClick) {
            buttonClicked(dfsButton, &nAlgo, 1);
            buttonClicked(astarButton, &nAlgo, 2);
            buttonClicked(dijkstraButton, &nAlgo, 3);
            buttonClicked(sizeInputField, &sizeWriting, 1);
            buttonClicked(widthInputField, &widthWriting, 1);
            buttonClicked(heightInputField, &heightWriting, 1);
            if (!posIn(clickStart, sizeInputField) && !posIn(clickEnd, sizeInputField)) sizeWriting = 0;
            if (!posIn(clickStart, widthInputField) && !posIn(clickEnd, widthInputField)) widthWriting = 0;
            if (!posIn(clickStart, heightInputField) && !posIn(clickEnd, heightInputField)) heightWriting = 0;
        }

        drawButton(renderer, fontS, dfsButton, "DFS", posIn(mousePos, dfsButton) ? hoverColor : normalColor);
        drawButton(renderer, fontS, astarButton, "A*", posIn(mousePos, astarButton) ? hoverColor : normalColor);
        drawButton(renderer, fontS, dijkstraButton, "Dijkstra", posIn(mousePos, dijkstraButton) ? hoverColor : normalColor);
        drawButton(renderer, fontS, sizeInputField, strlen(sizeEntry)!=0 ? sizeEntry : " ", sizeWriting ? (SDL_Color){255, 220, 220, 255} : (posIn(mousePos, sizeInputField) ? hoverColor : normalColor));
        drawButton(renderer, fontS, widthInputField, strlen(widthEntry)!=0 ? widthEntry : " ", widthWriting ? (SDL_Color){255, 220, 220, 255} : (posIn(mousePos, widthInputField) ? hoverColor : normalColor));
        drawButton(renderer, fontS, heightInputField, strlen(heightEntry)!=0 ? heightEntry : " ", heightWriting ? (SDL_Color){255, 220, 220, 255} : (posIn(mousePos, heightInputField) ? hoverColor : normalColor));

        SDL_RenderPresent(renderer);
    }

    if (!SIZE) SIZE = 10;
    if (!WIDTH) WIDTH = 80;
    if (!HEIGHT) HEIGHT = 60;
    SDL_SetWindowSize(window, WIDTH*SIZE, HEIGHT*SIZE);

    maze(renderer,DIRECTIONS);

    switch (nAlgo) {
        case 1:
            SDL_SetWindowTitle(window, "Maze | DFS");
            DFS(renderer);
            break;
        case 2:
            SDL_SetWindowTitle(window, "Maze | A*");
            A_star(renderer);
            break;
        case 3:
            SDL_SetWindowTitle(window, "Maze | Dijkstra");
            Dijkstra(renderer);
            break;
        printf("Erreur: entrée non valide\n");
        return 1;
    }

    // Quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
