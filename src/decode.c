#include "decode.h"

uint8_t cpu_read_byte(cpu_state_t *cpu, mmu_state_t *mmu) {
    return mmu_read_byte(mmu, cpu->registers.pc++);
}

uint16_t cpu_read_word(cpu_state_t *cpu, mmu_state_t *mmu) {
    uint16_t address = cpu->registers.pc;
    uint16_t result = mmu_read_word(mmu, address);
    cpu->registers.pc += 2;
    return result;
}

instruction_t cpu_decode_instruction(cpu_state_t *cpu, mmu_state_t *mmu, uint8_t opcode) {
    instruction_t instruction = { 
        opcode, 
        UNIMPLEMENTED, 
        "UNIMPLEMENTED INSTRUCTION", 
        0, 
        0, 0, 0, 0,
        0, 0
    };

    switch (opcode) {
        case 0x00:
            instruction.type = NOP;
            instruction.mnemonic = "NOP";
            instruction.cycles = 4;
            break;

        /**
         * 8-bit loads
         */

         // LD nn,n
        case 0x06:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD B, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x0E:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD C, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x16:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD D, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.d;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x1E:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD E, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.e;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x26:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD H, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.h;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x2E:
            instruction.type = LD_nn_n;
            instruction.mnemonic = "LD L, n";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.l;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;
        case 0x21:
            instruction.type = LD_n_nn;
            instruction.mnemonic = "LD HL, nn";
            instruction.cycles = 12;
            instruction.word_register_r1 = &cpu->registers.hl;
            instruction.word_operand = cpu_read_word(cpu, mmu);
            break;

        // LD r1,r2
        case 0x7F:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, A";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.a;
            break;
        case 0x78:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, B";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.b;
            break;
        case 0x79:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, C";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.c;
            break;
        case 0x7A:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, D";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.d;
            break;
        case 0x7B:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, E";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.e;
            break;
        case 0x7C:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, H";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.h;
            break;
        case 0x7D:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, L";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.byte_register_r2 = &cpu->registers.l;
            break;
        case 0x7E:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD A, HL";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.a;
            instruction.word_register_r2 = &cpu->registers.hl;
            break;
        case 0x40:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, B";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.b;
            break;
        case 0x41:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, C";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.c;
            break;
        case 0x42:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, D";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.d;
            break;
        case 0x43:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, E";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.e;
            break;
        case 0x44:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, H";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.h;
            break;
        case 0x45:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, L";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.byte_register_r2 = &cpu->registers.l;
            break;
        case 0x46:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD B, HL";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.b;
            instruction.word_register_r2 = &cpu->registers.hl;
            break;
        case 0x48:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, B";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.b;
            break;
        case 0x49:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, C";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.c;
            break;
        case 0x4A:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, D";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.d;
            break;
        case 0x4B:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, E";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.e;
            break;
        case 0x4C:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, H";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.h;
            break;
        case 0x4D:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, L";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.byte_register_r2 = &cpu->registers.l;
            break;
        case 0x4E:
            instruction.type = LD_r1_r2;
            instruction.mnemonic = "LD C, HL";
            instruction.cycles = 8;
            instruction.byte_register_r1 = &cpu->registers.c;
            instruction.word_register_r2 = &cpu->registers.hl;
            break;
        case 0x50:
            break;
        case 0x51:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
        case 0x54:
            break;
        case 0x55:
            break;
        case 0x56:
            break;
        case 0x58:
            break;
        case 0x59:
            break;
        case 0x5A:
            break;
        case 0x5B:
            break;
        case 0x5C:
            break;
        case 0x5D:
            break;
        case 0x5E:
            break;
        case 0x60:
            break;
        case 0x61:
            break;
        case 0x62:
            break;
        case 0x63:
            break;
        case 0x64:
            break;
        case 0x65:
            break;
        case 0x66:
            break;
        case 0x68:
            break;
        case 0x69:
            break;
        case 0x6A:
            break;
        case 0x6B:
            break;
        case 0x6C:
            break;
        case 0x6D:
            break;
        case 0x6E:
            break;
        case 0x70:
            break;
        case 0x71:
            break;
        case 0x72:
            break;
        case 0x73:
            break;
        case 0x74:
            break;
        case 0x75:
            break;
        case 0x36:
            break;

        // LD A, n
        // TODO

        // LD n, A
        // TODO

        // LD A, C
        // TODO

        // LD C, A
        // TODO

        // LDD A, HL
        // TODO

        // LDD HL, A
        case 0x32:
            instruction.type = LDD_HL_A;
            instruction.mnemonic = "LDD (HL), A";
            instruction.cycles = 8;
            instruction.word_register_r1 = &cpu->registers.hl;
            instruction.byte_register_r2 = &cpu->registers.a;
            break;

        /**
         * 16-bit loads
         */

        /**
         * 8-bit ALU
         */

        // XOR n
        case 0xAF:
            instruction.type = XOR_n;
            instruction.mnemonic = "XOR A";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.a;
            break;
        
        // CP n

        // INC n
        
        // DEC n
        case 0x3D:
            break;
        case 0x05:
            instruction.type = DEC_n;
            instruction.mnemonic = "DEC B";
            instruction.cycles = 4;
            instruction.byte_register_r1 = &cpu->registers.b;
            break;
        case 0x0D:
            break;
        case 0x15:
            break;
        case 0x1D:
            break;
        case 0x25:
            break;
        case 0x2D:
            break;
        case 0x35:
            break;

        /**
         * 16-bit Arithmetic
         */

        /**
         * Miscellaneous
         */

        /**
         * Rotates & Shifts
         */

        /**
         * Bit Opcodes
         */

        /**
         * Jumps
         */

         // JP nn
        case 0xC3:
            instruction.type = JP_nn;
            instruction.mnemonic = "JP nn";
            instruction.cycles = 12;
            instruction.word_operand = cpu_read_word(cpu, mmu);
            break;

        // JR cc, n
        case 0x20:
            instruction.type = JR_cc_n;
            instruction.mnemonic = "JR NZ, n";
            instruction.cycles = 8;
            instruction.byte_operand = cpu_read_byte(cpu, mmu);
            break;

        /**
         * Calls
         */

        /**
         * Restarts
         */

         /**
          * Returns
          */
        // Add more opcodes here
        default:
            break;
    }

    return instruction;
}