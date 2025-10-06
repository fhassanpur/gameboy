#include "mmu.h"

void mmu_init(mmu_state_t *mmu, uint8_t *rom_data) {
    // Load first 32kb of ROM data into memory
    for (int i = 0; i < 32768; i++) {
        mmu->rom[i] = rom_data[i];
    }

    // Clear other memory regions
    for (int i = 0; i < 8192; i++) {
        mmu->vram[i] = 0;
        mmu->eram[i] = 0;
        mmu->ram[i] = 0;
    }
    for (int i = 0; i < 128; i++) {
        mmu->zram[i] = 0;
    }
    for (int i = 0; i < 160; i++) {
        mmu->oam[i] = 0;
    }
}

uint8_t mmu_read_byte(mmu_state_t *mmu, uint16_t address) {
    switch (address & 0xF000) {
        // ROM
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return mmu->rom[address];

        // GPU VRAM
        case 0x8000:
        case 0x9000:
            return mmu->vram[address & 0x1FFF];

        // External RAM
        case 0xA000:
        case 0xB000:
            return mmu->eram[address & 0x1FFF];

        // Working RAM
        case 0xC000:
        case 0xD000:
        case 0xE000:
            return mmu->ram[address & 0x1FFF];

        case 0xF000:
            // Working RAM (shadow)
            if (address & 0x0F00 < 0xD00) {
                return mmu->ram[address & 0x1FFF];
            }

            // GPU OAM: after 160b, remaining bytes are 0
            if (address & 0x0F00 < 0xF00) {
                if (address < 0xFEA0) {
                    return mmu->oam[address & 0xFF];
                } else {
                    return 0;
                }
            }

            // Zero-page RAM
            if (address >= 0xFF80) {
                return mmu->zram[address & 0x7F];
            } else {
                // Instruction error
                return 0;
            }

    }
}

uint16_t mmu_read_word(mmu_state_t *mmu, uint16_t address) {
    return mmu_read_byte(mmu, address) | (mmu_read_byte(mmu, address + 1) << 8);
}

void mmu_write_byte(mmu_state_t *mmu, uint16_t address, uint8_t value) {
    switch (address & 0xF000) {
        // ROM - typically not writable, ignore writes
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            break;

        // GPU VRAM
        case 0x8000:
        case 0x9000:
            mmu->vram[address & 0x1FFF] = value;
            break;

        // External RAM
        case 0xA000:
        case 0xB000:
            mmu->eram[address & 0x1FFF] = value;
            break;

        // Working RAM
        case 0xC000:
        case 0xD000:
        case 0xE000:
            mmu->ram[address & 0x1FFF] = value;
            break;

        case 0xF000:
            // Working RAM (shadow)
            if (address & 0x0F00 < 0xD00) {
                mmu->ram[address & 0x1FFF] = value;
                break;
            }

            // GPU OAM: after 160b, remaining bytes are ignored
            if (address & 0x0F00 < 0xF00) {
                if (address < 0xFEA0) {
                    mmu->oam[address & 0xFF] = value;
                }
                break;
            }

            // Zero-page RAM
            if (address >= 0xFF80) {
                mmu->zram[address & 0x7F] = value;
                break;
            } else {
                // Instruction error
                break;
            }
    }
}

void mmu_write_word(mmu_state_t *mmu, uint16_t address, uint16_t value) {
    mmu_write_byte(mmu, address, value & 0xFF);
    mmu_write_byte(mmu, address + 1, (value >> 8) & 0xFF);
}