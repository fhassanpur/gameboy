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
// Todo: LD A, n
// Todo: LD n, A
// Todo: LC A, C
// Todo: LD C, A
// Todo: LDD A, HL
void cpu_op_ldd_hl_a(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction);
// Todo: LDI A, HL
// Todo: LDI HL, A
// Todo: LDH n, A
// Todo: LDH A, n


/**
 * 16-bit Load Operations
 */
void cpu_op_ld_n_nn(cpu_state_t *cpu, instruction_t instruction);


/**
 * 8-bit ALU Operations
 */
void cpu_op_xor_n(cpu_state_t *cpu, instruction_t instruction);
// Todo: CP n
// Todo: INC n
void cpu_op_dec_n(cpu_state_t *cpu, instruction_t instruction);

/**
 * 16-bit ALU Operations
 */

/**
 * Miscellaneous Operations
 */

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
