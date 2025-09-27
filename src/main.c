#include <SDL3/SDL.h>

#include "window.h"
#include "rom.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
    if (!initialize()) {
        return SDL_APP_FAILURE;
    }

    if (argc < 2) {
        SDL_Log("Usage: %s <rom file>", argv[0]);
        cleanup();
        return SDL_APP_FAILURE;
    }

    bool running = true;
    SDL_Event event;

    uint8_t rom_data[32768];
    load_rom(rom_data, argv[1]);

    cpu_state_t cpu = {0};
    cpu_init(&cpu);
    
    while (running) {
        // Check if program should quit
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        if (!cpu_step(&cpu, rom_data)) {
            running = false;
        }
    }

    cleanup();
    return 0;
}