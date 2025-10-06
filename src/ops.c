#include "ops.h"

/**
 * 8-bit Load Operations
 */
void cpu_op_ld_nn_n(cpu_state_t *cpu, instruction_t instruction) {
    *(instruction.byte_register_r1) = instruction.byte_operand;
}

void cpu_op_ldd_hl_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction) {
    uint16_t address = *(instruction.word_register_r1);
    // Write value of A to address in HL
    mmu_write_byte(mmu, address, *(instruction.byte_register_r2));
    // Decrement HL
    *(instruction.word_register_r1) = address - 1;
}

/**
 * 16-bit Load Operations
 */
void cpu_op_ld_n_nn(cpu_state_t *cpu, instruction_t instruction) {
    *(instruction.word_register_r1) = instruction.word_operand;
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

void cpu_op_dec_n(cpu_state_t *cpu, instruction_t instruction) {
    uint16_t value = 0;

    if (instruction.opcode == 0x35) {
        *(instruction.word_register_r1) -= 1;
        value = *(instruction.word_register_r1);
    } else {
        *(instruction.byte_register_r1) -= 1;
        value = *(instruction.byte_register_r1);
    }

    cpu->registers.f &= 0x10; // Preserve C flag, clear others
    if (value == 0) {
        cpu->registers.f |= 0x80; // Set zero flag
    }
    cpu->registers.f |= 0x40; // Set N flag
    if ((value & 0x0F) == 0x0F) {
        cpu->registers.f |= 0x20; // Set H flag
    }
}

/**
 * Jump Operations
 */
void cpu_op_jr_cc_n(cpu_state_t *cpu, instruction_t instruction) {
    bool condition_met = false;

    // Check condition based on opcode
    switch (instruction.opcode) {
        case 0x20: // JR NZ, n
            condition_met = (cpu->registers.f & 0x80) == 0; // Zero flag not set
            break;
    }

    if (condition_met) {
        cpu->registers.pc += instruction.byte_operand;
    }
}