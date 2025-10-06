#include "ops.h"

/**
 * 8-bit Load Operations
 */
void cpu_op_ld_nn_n(cpu_state_t *cpu, instruction_t instruction) {
    *(instruction.byte_register_r1) = instruction.byte_operand;
}

void cpu_op_ld_a_n(cpu_state_t *cpu, instruction_t instruction) {
    switch(instruction.opcode) {
        case 0x3E:
            cpu->registers.a = instruction.byte_operand;
            break;
        case 0x0A:
        case 0x1A:
        case 0x7E:
        case 0xFA:
            cpu->registers.a = *(instruction.word_register_r1);
            break;
        default:
            cpu->registers.a = *(instruction.byte_register_r1);
            break;
    }
}

void cpu_op_ldd_hl_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction) {
    uint16_t address = *(instruction.word_register_r1);
    // Write value of A to address in HL
    mmu_write_byte(mmu, address, *(instruction.byte_register_r2));
    // Decrement HL
    *(instruction.word_register_r1) = address - 1;
}

void cpu_op_ldh_n_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction) {
    uint16_t address = 0xFF00 + instruction.byte_operand;
    mmu_write_byte(mmu, address, cpu->registers.a);
}

void cpu_op_ldh_a_n(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction) {
    uint16_t address = 0xFF00 + instruction.byte_operand;
    cpu->registers.a = mmu_read_byte(mmu, address);
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

void cpu_op_cp_n(cpu_state_t *cpu, instruction_t instruction) {
    uint16_t value;
    if (instruction.opcode == 0xFE) {
        value = instruction.byte_operand;
    } else if (instruction.opcode == 0xBE) {
        value = cpu->registers.hl;
    } else {
        value = *(instruction.byte_register_r1);
    }
    uint16_t result = cpu->registers.a - value;

    // Set flags
    cpu->registers.f = 0; // Clear all flags
    if (result == 0) {
        cpu->registers.f |= 0x80; // Set zero flag
    }
    cpu->registers.f |= 0x40; // Set N flag
    if (cpu->registers.a < value) {
        cpu->registers.f |= 0x10; // Set C flag
    }
    if ((cpu->registers.a & 0x0F) < (value & 0x0F)) {
        cpu->registers.f |= 0x20; // Set H flag
    }
}

void cpu_op_inc_n(cpu_state_t *cpu, instruction_t instruction) {
    uint16_t value = 0;

    if (instruction.opcode == 0x35) {
        *(instruction.word_register_r1) += 1;
        value = *(instruction.word_register_r1);
    } else {
        *(instruction.byte_register_r1) += 1;
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
 * Miscellaneous Operations
 */
void cpu_op_di(cpu_state_t *cpu) {
    cpu->clock.disable_ime_timer = 2;
}

void cpu_op_ei(cpu_state_t *cpu) {
    cpu->clock.enable_ime_timer = 2;
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
        int8_t offset = (int8_t)instruction.byte_operand; // Sign-extend the operand
        cpu->registers.pc += offset;
    }
}