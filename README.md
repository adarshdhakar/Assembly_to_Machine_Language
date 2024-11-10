# RISC-V Assembler

This project is a simple RISC-V assembler that converts RISC-V assembly instructions into their corresponding machine code. The assembler supports various instruction types including R-type, I-type, S-type, B-type, U-type, and J-type.

## Features

- **RISC-V instruction support:** Includes a wide range of RISC-V instructions (e.g., `add`, `sub`, `lw`, `sw`, `beq`, `jal`).
- **Binary Conversion:** Converts assembly instructions into 32-bit machine code.
- **Label handling:** Allows the use of labels in the assembly code.
- **Two's complement handling:** Provides support for negative numbers using two's complement representation.

## Supported Instructions

- **R-Type:** `add`, `sub`, `sll`, `slt`, `sltu`, `xor`, `srl`, `sra`, `or`, `and`
- **I-Type:** `jalr`, `addi`, `slti`, `sltiu`, `xori`, `ori`, `andi`, `lb`, `lh`, `lw`, `lbu`, `lhu`
- **S-Type:** `sb`, `sh`, `sw`
- **B-Type:** `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`
- **U-Type:** `lui`, `auipc`
- **J-Type:** `jal`

## Getting Started

To run the project, follow these instructions:

### Prerequisites

You need to have the following tools installed on your system:

- **C++ compiler:** (e.g., `g++`)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/adarshdhakar/Assembly_to_Machine_Language.git
    cd Assembly_to_Machine_Language
    ```

2. Compile the project:

    If you are using `g++`, you can compile the code using:

    ```bash
    g++ Assembly_to_Machine_Language.cpp
    ```

3. Run the assembler:

    ```bash
    ./a.out
    ```

### Example Usage

You can input RISC-V instructions, and the assembler will convert them into their respective machine code.

Example input:

    "addi x5, x5, 10",      // int n = 10;
    "addi x1, x1, 0",       // int i = 0; (x1 = 0)
    "addi x2, x2, 0",       // int sum = 0;

    "addi x5, x5, 1",       // n = n + 1;

    "sum_loop:",            
    "beq x1, x5, done",     // if(i == n) goto done;
    "add x2, x2, x1",       // sum = sum + i;
    "addi x1, x1, 1",       // i = i + 1;
    "jal x3, sum_loop",     

    "done:",    
    "sw x2, 0(x31)"         // DM[x31+0] = x2;

Output:

    00000000101000101000001010010011
    00000000000000001000000010010011
    00000000000000010000000100010011
    00000000000100101000001010010011
    00000000010100001000001001100011
    00000000000100010000000100110011
    00000000000100001000000010010011
    11111111111111111101000111101111
    00000000001011111010000000100011

### Instruction Reference

For a detailed list of RISC-V instructions and their encodings, refer to the [RISC-V CARD.pdf](https://github.com/adarshdhakar/Assembly_to_Machine_Language/blob/main/RISCV_CARD.pdf).



