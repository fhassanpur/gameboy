#include <SDL3/SDL.h>

#include "cpu.h"
#include "decode.h"

void cpu_init(cpu_state_t *cpu) {
    cpu->registers.af = 0x01B0;
    cpu->registers.bc = 0x0013;
    cpu->registers.de = 0x00D8;
    cpu->registers.hl = 0x014D;
    cpu->registers.sp = 0xFFFE;
    cpu->registers.pc = 0x0100;
}

bool cpu_step(cpu_state_t *cpu, mmu_state_t *mmu) {
    // Fetch
    uint8_t opcode = mmu->rom[cpu->registers.pc++];

    // Decode
    instruction_t instruction = cpu_decode_instruction(cpu, mmu, opcode);

    // Execute
    bool result = cpu_execute_instruction(cpu, mmu, instruction);

    // Handle IME timers
    if (cpu->clock.disable_ime_timer > 0) {
        if (cpu->clock.disable_ime_timer-- == 0) {
            cpu->registers.ime = false;
        }
    }
    if (cpu->clock.enable_ime_timer > 0) {
        if (cpu->clock.enable_ime_timer-- == 0) {
            cpu->registers.ime = true;
        }
    }

    return result;
}

bool cpu_execute_instruction(cpu_state_t *cpu, mmu_state_t *mmu, instruction_t instruction) {
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
        case LD_A_n:
            cpu_op_ld_a_n(cpu, instruction);
            break;
        case LDD_HL_A:
            cpu_op_ldd_hl_a(cpu, instruction);
            break;
        case LDH_n_A:
            cpu_op_ldh_n_a(cpu, mmu, instruction);
            break;
        case LDH_A_n:
            cpu_op_ldh_a_n(cpu, mmu, instruction);
            break;
            
        /**
         * 8-bit ALU
         */
        case XOR_n:
            cpu_op_xor_n(cpu, instruction);
            break;
        case CP_n:
            cpu_op_cp_n(cpu, instruction);
            break;
        case INC_n:
            cpu_op_inc_n(cpu, instruction);
            break;
        case DEC_n:
            cpu_op_dec_n(cpu, instruction);
            break;
        
        case NOP:
            // Do nothing
            break;
        case DI:
            cpu_op_di(cpu);
            break;
        case EI:
            cpu_op_ei(cpu);
            break;
        case JP_nn:
            cpu->registers.pc = instruction.word_operand;
            break;
        case JR_cc_n:
            cpu_op_jr_cc_n(cpu, instruction);
            break;

        // Handle other instructions here
        default:
            SDL_Log("Unhandled instruction type: %02X", instruction.type);
            return false;
    }
    SDL_Log("%02X: %s", instruction.opcode, instruction.mnemonic);

    cpu->clock.machine_cycles += instruction.cycles;

    return true;
}