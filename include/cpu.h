#pragma once

#include <stdint.h>

#include "instruction.h"

typedef struct cpu_registers {
    struct {
		union {
			struct {
				uint8_t f;
				uint8_t a;
			};
			uint16_t af;
		};
	};
	struct {
		union {
			struct {
				uint8_t c;
				uint8_t b;
			};
			uint16_t bc;
		};
	};
	struct {
		union {
			struct {
				uint8_t e;
				uint8_t d;
			};
			uint16_t de;
		};
	};
	struct {
		union {
			struct {
				uint8_t l;
				uint8_t h;
			};
			uint16_t hl; 
		};
	};
	
	uint16_t sp; // Stack Pointer
	uint16_t pc; // Program Counter

    uint8_t ime; // Interrupt Master Enable
} cpu_registers_t;

typedef struct cpu_state {
    cpu_registers_t registers;
} cpu_state_t;

void cpu_init(cpu_state_t *cpu);
bool cpu_step(cpu_state_t *cpu, uint8_t *rom_memory);
instruction_t cpu_decode_instruction(cpu_state_t *cpu, uint8_t opcode);
bool cpu_execute_instruction(cpu_state_t *cpu, instruction_t instruction);