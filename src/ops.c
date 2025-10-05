#include "ops.h"

/**
 * 8-bit Load Operations
 */
void cpu_op_ld_nn_n(cpu_state_t *cpu, instruction_t instruction) {
    *(instruction.byte_register_r1) = instruction.byte_operand;
}

/**
 * 8-bit ALU Operations
 */
void cpu_op_xor_n(cpu_state_t *cpu, instruction_t instruction) {
    *instruction.byte_register_r1 ^= *(instruction.byte_register_r1);

    // Set flags
    cpu->registers.f = 0; // Clear all flags
    if (*instruction.byte_register_r1 == 0) {
        cpu->registers.f |= 0x80; // Set zero flag
    }
    cpu->registers.f |= 0x20; // Set H flag
}

/**
 * 16-bit Load Operations
 */
void cpu_op_ld_n_nn(cpu_state_t *cpu, instruction_t instruction) {
    *(instruction.word_register_r1) = instruction.word_operand;
}