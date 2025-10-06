#pragma once

#include <stdint.h>

#include "cpu.h"
#include "mmu.h"
#include "instruction.h"

/**
 * 8-bit Load Operations
 */
void cpu_op_ld_nn_n(cpu_state_t *cpu, instruction_t instruction);
// Todo: LD r1, r2
void cpu_op_ld_a_n(cpu_state_t *cpu, instruction_t instruction);
// Todo: LD n, A
// Todo: LC A, C
// Todo: LD C, A
// Todo: LDD A, HL
void cpu_op_ldd_hl_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction);
// Todo: LDI A, HL
// Todo: LDI HL, A
void cpu_op_ldh_n_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction);
void cpu_op_ldh_a_n(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction);


/**
 * 16-bit Load Operations
 */
void cpu_op_ld_n_nn(cpu_state_t *cpu, instruction_t instruction);


/**
 * 8-bit ALU Operations
 */
void cpu_op_xor_n(cpu_state_t *cpu, instruction_t instruction);
void cpu_op_cp_n(cpu_state_t *cpu, instruction_t instruction);
void cpu_op_inc_n(cpu_state_t *cpu, instruction_t instruction);
void cpu_op_dec_n(cpu_state_t *cpu, instruction_t instruction);

/**
 * 16-bit ALU Operations
 */

/**
 * Miscellaneous Operations
 */
void cpu_op_di(cpu_state_t *cpu);
void cpu_op_ei(cpu_state_t *cpu);

/**
 * Rotate and Shift Operations
 */

/**
 * Bit Operations
 */ 

/**
 * Jump Operations
 */
void cpu_op_jr_cc_n(cpu_state_t *cpu, instruction_t instruction);

/**
 * Call Operations
 */ 

/**
 * Restart and Return Operations
 */
