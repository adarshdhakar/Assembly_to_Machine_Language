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

string hexDigitToBinary(char hexDigit) {
    switch (toupper(hexDigit)) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "";
    }
}

string hexToBin(string hex) {
    string binary = "";
    for (char hexDigit : hex) {
        string bin = hexDigitToBinary(hexDigit);
        if (!bin.empty()) {
            binary += bin;
        } else {
            cerr << "Invalid hexadecimal digit: " << hexDigit << std::endl;
            return "";
        }
    }
    
    if (binary.length() > 32) {
        binary = binary.substr(binary.length() - 32);
    } else if (binary.length() < 32) {
        binary = string(32 - binary.length(), '0') + binary;
    }

    return binary;
}

string decimalToBinary(const string& decimalStr) {
    int decimal = stoi(decimalStr);
    string binaryStr = bitset<32>(decimal).to_string();

    // binaryStr.erase(0, binaryStr.find_first_not_of('0'));

    if (binaryStr.empty()) {
        binaryStr = "0";
    }

    return binaryStr;
}

string tolowerString(const string& func){
    string str = "";
    for(const char &it : func){
        str.push_back(tolower(it));
    }
    return str;
}

void makeStrLenBin(string &s, int n){
    if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        s.erase(0,2);
        s = hexToBin(s);
    }
    else {
        s = decimalToBinary(s);           
    }
    s.erase(0, 32-n);
}

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

        rd = tolowerString(rd.substr(0, rd.find(',')));
        rs1 = tolowerString(rs1.substr(0, rs1.find(',')));

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

class I{
private:
    string opcode = "0010011", rd, func3, rs1, imm;
    string machineCode;

    string findRegister(string s){
        if(registers.find(s) != registers.end()){
            return registers[s];
        }
        return "-1";
    }
    void joinCodes(){
        cout << imm << " " << rs1 << " " << func3 << " " << rd << " " << opcode << endl;
        machineCode = imm + rs1 + func3 + rd + opcode;
    }

public:
    I (vector<string> inst_break, vector<string> modeAndFunc) {
        this->rd = inst_break[1];
        this->rs1 = inst_break[2];
        this->imm = inst_break[3];

        rd = tolowerString(rd.substr(0, rd.find(',')));
        rs1 = tolowerString(rs1.substr(0, rs1.find(',')));

        if(tolower(inst_break[0][0]) == 'l'){
            swap(rs1, imm);
            opcode = "0000011";
        }

        rd = findRegister(rd);
        rs1 = findRegister(rs1);

        makeStrLenBin(imm, 12);

        this->func3 = modeAndFunc[1];
        joinCodes();
    }

    string getMachineCode(){
        return machineCode;
    }
};

class S{
private:
    string opcode = "0100011", imm1, func3, rs1, rs2, imm2;
    string machineCode;

    string findRegister(string s){
        if(registers.find(s) != registers.end()){
            return registers[s];
        }
        return "-1";
    }
    void joinCodes(){
        cout << imm2 << " " << rs2 << " " << rs1 << " " << func3 << " " << imm1 << " " << opcode << endl;
        machineCode = imm2 + rs2 + rs1 + func3 + imm1 + opcode;
    }

public:
    S (vector<string> inst_break, vector<string> modeAndFunc) {
        this->rs2 = inst_break[1];
        string str = inst_break[2];

        makeStrLenBin(str, 12);

        this->imm2 = str.substr(0, 7);
        this->imm1 = str.substr(7, 12);
        this->rs1 = inst_break[3];
        rs2 = rs2.substr(0, rs2.find(','));

        rs2 = findRegister(rs2);
        rs1 = findRegister(rs1);

        this->func3 = modeAndFunc[1];
        joinCodes();
    }

    string getMachineCode(){
        return machineCode;
    }
};

class U{
private:
    string opcode = "0110111", rd, imm;
    string machineCode;

    string findRegister(string s){
        if(registers.find(s) != registers.end()){
            return registers[s];
        }
        return "-1";
    }
    void joinCodes(){
        cout << imm << " " << rd << " " << opcode << endl;
        machineCode = imm + rd + opcode;
    }

public:
    U (vector<string> inst_break, vector<string> modeAndFunc) {
        this->rd = inst_break[1];
        this->imm = inst_break[2];

        rd = tolowerString(rd.substr(0, rd.find(',')));
        rd = findRegister(rd);

        makeStrLenBin(imm, 20);

        joinCodes();
    }

    string getMachineCode(){
        return machineCode;
    }
};

class B{
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
    B (vector<string> inst_break, vector<string> modeAndFunc) {
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

class J{
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
    J (vector<string> inst_break, vector<string> modeAndFunc) {
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


class Assembler {
private:
    unordered_map<string, vector<string>> functions; //{func, {addMode, func3, func7}};
    
    vector<string> getInfo(string func){
        func = tolowerString(func);
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
    functions["addi"] = {"I", "000", ""};  // Add Immediate
    functions["slti"] = {"I", "010", ""};  // Set Less Than Immediate
    functions["sltiu"] = {"I", "011", ""}; // Set Less Than Immediate Unsigned
    functions["xori"] = {"I", "100", ""};  // XOR Immediate
    functions["ori"] = {"I", "110", ""};   // OR Immediate
    functions["andi"] = {"I", "111", ""};  // AND Immediate

    // I-type Load instructions
    functions["lb"] = {"I", "000", ""};    // Load Byte
    functions["lh"] = {"I", "001", ""};    // Load Halfword
    functions["lw"] = {"I", "010", ""};    // Load Word
    functions["lbu"] = {"I", "100", ""};   // Load Byte Unsigned
    functions["lhu"] = {"I", "101", ""};   // Load Halfword Unsigned

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

    void removeBrackets(string& instruction){
        int n = instruction.size();
        for(int i = 0; i < n; i ++){
            if(instruction[i] == '(' || instruction[i] == ')'){
                instruction[i] = ' ';
            }
        }
    }

    string assemble(string& instruction){
        removeBrackets(instruction);

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
        else if(addMode == "I"){
            I iMode = I(inst_break, modeAndFunc);
            machineCode = iMode.getMachineCode();
        }
        else if(addMode == "S"){
            S sMode = S(inst_break, modeAndFunc);
            machineCode = sMode.getMachineCode();
        }
        else if(addMode == "B"){
            B bMode = B(inst_break, modeAndFunc);
            machineCode = bMode.getMachineCode();
        }
        else if(addMode == "U"){
            U uMode = U(inst_break, modeAndFunc);
            machineCode = uMode.getMachineCode();
        }
        else if(addMode == "J"){
            J jMode = J(inst_break, modeAndFunc);
            machineCode = jMode.getMachineCode();
        }

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