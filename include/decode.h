#pragma once

#include "cpu.h"
#include "mmu.h"

uint8_t cpu_read_byte(cpu_state_t *cpu, mmu_state_t *mmu);
uint16_t cpu_read_word(cpu_state_t *cpu, mmu_state_t *mmu);
instruction_t cpu_decode_instruction(cpu_state_t *cpu, mmu_state_t *mmu, uint8_t opcode);