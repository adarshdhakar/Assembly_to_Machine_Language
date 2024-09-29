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

add x2, x1, x2
damn:
addi x5, x6, 10
hello:
lui x3, 50
sw x4, 10(x3)
jal x7, hello
beq x8, x9, damn

Output:

00000000001000001000000100110011
00000000000100110000001010010011
00000000000000110010000110110111
00000000010000011010010100100011
11111111111111111110001111101111
11111110100101000000110111100011

### Instruction Reference

For a detailed list of RISC-V instructions and their encodings, refer to the [RISC-V CARD.pdf](https://github.com/adarshdhakar/Assembly_to_Machine_Language/blob/main/RISCV_CARD.pdf).



