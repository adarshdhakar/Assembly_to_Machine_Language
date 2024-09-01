#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> registers = {
    {"x0", "00000"},
    {"x1", "00001"},
    {"x2", "00010"},
    {"x3", "00011"},
    {"x4", "00100"},
    {"x5", "00101"},
    {"x6", "00110"},
    {"x7", "00111"},
    {"x8", "01000"},
    {"x9", "01001"},
    {"x10","01010"},
    {"x11","01011"},
    {"x12","01100"},
    {"x13","01101"},
    {"x14","01110"},
    {"x15","01111"},
    {"x16","10000"},
    {"x17","10001"},
    {"x18","10010"},
    {"x19","10011"},
    {"x20","10100"},
    {"x21","10101"},
    {"x22","10110"},
    {"x23","10111"},
    {"x24","11000"},
    {"x25","11001"},
    {"x26","11010"},
    {"x27","11011"},
    {"x28","11100"},
    {"x29","11101"},
    {"x30","11110"},
    {"x31","11111"}
};


class R{
private:
    string opcode = "0110011", rd, func3, rs1, rs2, func7;
    string machineCode;

    string findRegister(string s){
        if(registers.find(s) != registers.end()){
            return registers[s];
        }
        return "-1";
    }
    void joinCodes(){
        cout << func7 << " " << rs2 << " " << rs1 << " " << func3 << " " << rd << " " << opcode << endl;
        machineCode = func7 + rs2 + rs1 + func3 + rd + opcode;
    }

public:
    R (vector<string> inst_break, vector<string> modeAndFunc) {
        this->rd = inst_break[1];
        this->rs1 = inst_break[2];
        this->rs2 = inst_break[3];
        rd = rd.substr(0, rd.find(','));
        rs1 = rs1.substr(0, rs1.find(','));
        rs2 = rs2.substr(0, rs2.find(','));

        rd = findRegister(rd);
        rs1 = findRegister(rs1);
        rs2 = findRegister(rs2);

        this->func3 = modeAndFunc[1];
        this->func7 = modeAndFunc[2];
        joinCodes();
    }

    string getMachineCode(){
        return machineCode;
    }
};

class S {
    
}

class Assembler {
private:
    unordered_map<string, vector<string>> functions; //{func, {addMode, func3, func7}}

    vector<string> getInfo(const string& func){
        if(functions.find(func) != functions.end()){
            return functions[func];
        }
        return {""};
    }
public:
   Assembler() {
    // R-type instructions
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
    
    // I-type instructions
    functions["jalr"] = {"I", "000", ""};  // Jump and Link Register
    functions["lb"] = {"I", "000", ""};    // Load Byte
    functions["lh"] = {"I", "001", ""};    // Load Halfword
    functions["lw"] = {"I", "010", ""};    // Load Word
    functions["lbu"] = {"I", "100", ""};   // Load Byte Unsigned
    functions["lhu"] = {"I", "101", ""};   // Load Halfword Unsigned
    functions["addi"] = {"I", "000", ""};  // Add Immediate
    functions["slti"] = {"I", "010", ""};  // Set Less Than Immediate
    functions["sltiu"] = {"I", "011", ""}; // Set Less Than Immediate Unsigned
    functions["xori"] = {"I", "100", ""};  // XOR Immediate
    functions["ori"] = {"I", "110", ""};   // OR Immediate
    functions["andi"] = {"I", "111", ""};  // AND Immediate
    
    // S-type instructions
    functions["sb"] = {"S", "000", ""};    // Store Byte
    functions["sh"] = {"S", "001", ""};    // Store Halfword
    functions["sw"] = {"S", "010", ""};    // Store Word
    
    // B-type instructions
    functions["beq"] = {"B", "000", ""};   // Branch Equal
    functions["bne"] = {"B", "001", ""};   // Branch Not Equal
    functions["blt"] = {"B", "010", ""};   // Branch Less Than
    functions["bge"] = {"B", "011", ""};   // Branch Greater or Equal
    functions["bltu"] = {"B", "100", ""};  // Branch Less Than Unsigned
    functions["bgeu"] = {"B", "101", ""};  // Branch Greater or Equal Unsigned
    
    // U-type instructions
    functions["lui"] = {"U", "", ""};      // Load Upper Immediate
    functions["auipc"] = {"U", "", ""};    // Add Upper Immediate to PC
    
    // J-type instructions
    functions["jal"] = {"J", "", ""};      // Jump and Link
}


    string assemble(const string& instruction){
        vector<string> inst_break;
        stringstream s(instruction);
        string word;

        while (getline(s, word, ' ')) {
            inst_break.push_back(word);
        }
        
        vector<string> modeAndFunc = getInfo(inst_break[0]);
        string addMode = modeAndFunc[0];

        string machineCode = "";
        if(addMode == "R"){
            R rMode = R(inst_break, modeAndFunc);
            machineCode = rMode.getMachineCode();
        }
        // else if(addMode == "I"){
        //     I iMode = I(inst_break, modeAndFunc);
        //     machineCode = iMode.getMachineCode();
        // }
        // else if(addMode == "S"){
        //     S sMode = S(inst_break, modeAndFunc);
        //     machineCode = sMode.getMachineCode();
        // }
        // else if(addMode == "B"){
        //     B bMode = B(inst_break, modeAndFunc);
        //     machineCode = bMode.getMachineCode();
        // }
        // else if(addMode == "U"){
        //     U uMode = U(inst_break, modeAndFunc);
        //     machineCode = uMode.getMachineCode();
        // }
        // else if(addMode == "J"){
        //     J jMode = J(inst_break, modeAndFunc);
        //     machineCode = jMode.getMachineCode();
        // }

        return machineCode;
    }
};

int main(){
    string s;
    Assembler assembler;
    while(1){
        getline(cin, s, '\n');

        if (s.empty()) {
            break; 
        }

        string str = assembler.assemble(s);
        cout << str << endl;
    }
}