#pragma once

#include <stdint.h>

#include "cpu.h"
#include "instruction.h"

/**
 * 8-bit Load Operations
 */


/**
 * 16-bit Load Operations
 */
void cpu_op_ld_n_nn(cpu_state_t *cpu, instruction_t instruction);


/**
 * 8-bit ALU Operations
 */
void cpu_op_xor_n(cpu_state_t *cpu, instruction_t instruction);

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

/**
 * Call Operations
 */ 

/**
 * Restart and Return Operations
 */
