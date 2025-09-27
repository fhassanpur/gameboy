#include <SDL3/SDL.h>

#include "window.c"

int main(int argc, char *argv[]) {
    if (!initialize()) {
        return SDL_APP_FAILURE;
    }

    bool running = true;
    SDL_Event event;
    
    while (running) {
        // Check if program should quit
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }

    cleanup();
    return 0;
}