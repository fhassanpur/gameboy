#include <SDL3/SDL.h>

#include "cpu.h"

void cpu_init(cpu_state_t *cpu) {
    cpu->registers.af = 0x01B0;
    cpu->registers.bc = 0x0013;
    cpu->registers.de = 0x00D8;
    cpu->registers.hl = 0x014D;
    cpu->registers.sp = 0xFFFE;
    cpu->registers.pc = 0x0100;
}

bool cpu_step(cpu_state_t *cpu, uint8_t *rom_memory) {
    // Fetch
    uint8_t opcode = rom_memory[cpu->registers.pc++];

    // Decode
    instruction_t instruction = cpu_decode_instruction(cpu, opcode);

    // Execute
    return cpu_execute_instruction(cpu, instruction);
}

instruction_t cpu_decode_instruction(cpu_state_t *cpu, uint8_t opcode) {
    instruction_t instruction = {0};
    instruction.opcode = opcode;
    instruction.byte_operand = NULL;
    instruction.word_operand = NULL;

    switch (opcode) {
        case 0x00:
            instruction.type = NOP;
            instruction.mnemonic = "NOP";
            break;
        // Add more opcodes here
        default:
            instruction.type = UNIMPLEMENTED;
            instruction.mnemonic = "UNIMPLEMENTED INSTRUCTION";
            break;
    }

    return instruction;
}

bool cpu_execute_instruction(cpu_state_t *cpu, instruction_t instruction) {
    switch (instruction.type) {
        case UNIMPLEMENTED:
            SDL_Log("Attempted to execute unimplemented instruction with opcode: %02X", instruction.opcode);
            return false;
        case NOP:
            // Do nothing
            break;
        // Handle other instructions here
        default:
            SDL_Log("Unhandled instruction type: %d", instruction.type);
            return false;
    }
    SDL_Log("%02X: %s", instruction.opcode, instruction.mnemonic);

    return true;
}