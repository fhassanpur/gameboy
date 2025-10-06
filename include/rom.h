#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>

#define MAX_ROM_SIZE 4194304 // 4MB

bool load_rom(uint8_t *result, char const *filename) {
    // Open the file
    FILE *fptr = fopen(filename, "rb");

    // Check if file exists / have permissions
    if (fptr == NULL) {
        SDL_Log("Error opening file: %s", filename);
        return false;
    }

    // Load ROM into memory
    int i = 0;
    int buffer;
    while ((buffer = fgetc(fptr)) != EOF) {
        // Prevent buffer overflow
        if (i >= MAX_ROM_SIZE) {
            SDL_Log("Error: ROM size exceeeds max supported size");
            fclose(fptr);
            return false;
        }

        result[i] = (uint8_t)buffer;
        i++;
    }

    fclose(fptr);

    return true;
}