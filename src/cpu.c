#include <SDL3/SDL.h>

#include "cpu.h"
#include "decode.h"
#include "ops.h"

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
    instruction_t instruction = cpu_decode_instruction(cpu, rom_memory, opcode);

    // Execute
    return cpu_execute_instruction(cpu, instruction);
}

bool cpu_execute_instruction(cpu_state_t *cpu, instruction_t instruction) {
    switch (instruction.type) {
        case UNIMPLEMENTED:
            SDL_Log("Attempted to execute unimplemented instruction with opcode: %02X", instruction.opcode);
            return false;
        case LD_nn_n:
            cpu_op_ld_nn_n(cpu, instruction);
            break;
        case LD_n_nn:
            cpu_op_ld_n_nn(cpu, instruction);
            break;
        case XOR_n:
            cpu_op_xor_n(cpu, instruction);
            break;
        case NOP:
            // Do nothing
            break;
        case JP_nn:
            cpu->registers.pc = instruction.word_operand;
            break;

        // Handle other instructions here
        default:
            SDL_Log("Unhandled instruction type: %d", instruction.type);
            return false;
    }
    SDL_Log("%02X: %s", instruction.opcode, instruction.mnemonic);

    cpu->clock.machine_cycles += instruction.cycles;

    return true;
}