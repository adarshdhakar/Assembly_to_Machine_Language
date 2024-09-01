#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> functions; // {func, {addMode, func3, func7}}

// Function to add R-type instructions
void addRTypeInstructions() {
    functions["add"] = {"R", "000", "0000000"};   // Addition
    functions["sub"] = {"R", "000", "0100000"};   // Subtraction
    functions["sll"] = {"R", "001", "0000000"};   // Shift Left Logical
    functions["slt"] = {"R", "010", "0000000"};   // Set Less Than
    functions["sltu"] = {"R", "011", "0000000"};  // Set Less Than Unsigned
    functions["xor"] = {"R", "100", "0000000"};   // XOR
    functions["srl"] = {"R", "101", "0000000"};   // Shift Right Logical
    functions["sra"] = {"R", "101", "0100000"};   // Shift Right Arithmetic
    functions["or"] = {"R", "110", "0000000"};    // OR
    functions["and"] = {"R", "111", "0000000"};   // AND
}

// Function to add I-type instructions
void addITypeInstructions() {
    functions["jalr"] = {"I", "000"};  // Jump and Link Register
    functions["addi"] = {"I", "000"};  // Add Immediate
    functions["slti"] = {"I", "010"};  // Set Less Than Immediate
    functions["sltiu"] = {"I", "011"}; // Set Less Than Immediate Unsigned
    functions["xori"] = {"I", "100"};  // XOR Immediate
    functions["ori"] = {"I", "110"};   // OR Immediate
    functions["andi"] = {"I", "111"};  // AND Immediate

    // I-type Load instructions
    functions["lb"] = {"I", "000"};    // Load Byte
    functions["lh"] = {"I", "001"};    // Load Halfword
    functions["lw"] = {"I", "010"};    // Load Word
    functions["lbu"] = {"I", "100"};   // Load Byte Unsigned
    functions["lhu"] = {"I", "101"};   // Load Halfword Unsigned
}

// Function to add S-type instructions
void addSTypeInstructions() {
    functions["sb"] = {"S", "000"};    // Store Byte
    functions["sh"] = {"S", "001"};    // Store Halfword
    functions["sw"] = {"S", "010"};    // Store Word
}

// Function to add B-type instructions
void addBTypeInstructions() {
    functions["beq"] = {"B", "000"};   // Branch Equal
    functions["bne"] = {"B", "001"};   // Branch Not Equal
    functions["blt"] = {"B", "100"};   // Branch Less Than
    functions["bge"] = {"B", "101"};   // Branch Greater or Equal
    functions["bltu"] = {"B", "110"};  // Branch Less Than Unsigned
    functions["bgeu"] = {"B", "111"};  // Branch Greater or Equal Unsigned
}

// Function to add U-type instructions
void addUTypeInstructions() {
    functions["lui"] = {"U"};      // Load Upper Immediate
    functions["auipc"] = {"U"};    // Add Upper Immediate to PC
}

// Function to add J-type instructions
void addJTypeInstructions() {
    functions["jal"] = {"J"};      // Jump and Link
}

// Main function to initialize all instruction types
void initializeFunctions() {
    addRTypeInstructions();
    addITypeInstructions();
    addSTypeInstructions();
    addBTypeInstructions();
    addUTypeInstructions();
    addJTypeInstructions();
}