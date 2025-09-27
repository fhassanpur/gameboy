#pragma once

#include <stdint.h>

typedef enum instruction_type {
    UNIMPLEMENTED,

    // 8-bit loads
    LD_nn_n,
    LD_r1_r2,
    LD_A_n,
    LD_n_A,
    LD_A_C,
    LD_C_A,
    LDD_A_HL,
    LDD_HL_A,
    LDI_A_HL,
    LDI_HL_A,
    LDH_n_A,
    LDH_A_n,

    // 16-bit loads
    LD_n_nn,
    LD_SP_HL,
    LDHL_SP_n,
    LD_nn_SP,
    PUSH_nn,
    POP_nn,

    // 8-bit ALU
    ADD_A_n,
    ADC_A_n,
    SUB_n,
    SBC_A_n,
    AND_n,
    OR_n,
    XOR_n,
    CP_n,
    INC_n,
    DEC_n,

    // 16-bit ALU
    ADD_HL_n,
    ADD_SP_n,
    INC_nn,
    DEC_nn,

    // Misc
    SWAP_n,
    DAA,
    CPL,
    CCF,
    SCF,
    NOP,
    HALT,
    STOP,
    DI,
    EI,

    // Rotates and shifts
    RLCA,
    RLA,
    RRCA,
    RRA,
    RLC_n,
    RL_n,
    RRC_n,
    RR_n,
    SLA_n,
    SRA_n,
    SRL_n,

    // Bit operations
    BIT_b_r,
    SET_b_r,
    RES_b_r,

    // Jumps
    JP_nn,
    JP_cc_nn,
    JP_HL,
    JR_n,
    JR_cc_n,

    // Calls
    CALL_nn,
    CALL_cc_nn,

    // Restart & returns
    RST_n,
    RET,
    RET_cc,
    RETI
    
} instruction_type_t;

typedef struct instruction {
    uint8_t opcode;
    instruction_type_t type;
    char *mnemonic;
    uint8_t *byte_operand;
    uint16_t *word_operand;
} instruction_t;