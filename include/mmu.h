#pragma once

#include <stdint.h>
#include <stdio.h>
#include <SDL3/SDL.h>

typedef struct mmu_state {
    uint8_t rom[32768]; // 32kb ROM cartridge memory
    uint8_t vram[8192]; // 8kb GPU memory
    uint8_t eram[8192]; // 8kb external cartridge RAM
    uint8_t ram[8192];  // 8kb internal working RAM
    uint8_t zram[128];  // 128b zero-page RAM
    uint8_t oam[160];   // 160b GPU object attribute memory
} mmu_state_t;

void mmu_init(mmu_state_t *mmu, uint8_t *rom_data);
uint8_t mmu_read_byte(mmu_state_t *mmu, uint16_t address);
uint16_t mmu_read_word(mmu_state_t *mmu, uint16_t address);