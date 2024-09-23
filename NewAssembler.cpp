#include <bits/stdc++.h>
using namespace std;

map<string, int> labels;
unordered_map<string, vector<string>> functions;

void addRTypeInstructions() {
    functions["add"] = {"R", "000", "0000000"};
    functions["sub"] = {"R", "000", "0100000"};
    functions["sll"] = {"R", "001", "0000000"};
    functions["slt"] = {"R", "010", "0000000"};
    functions["sltu"] = {"R", "011", "0000000"};
    functions["xor"] = {"R", "100", "0000000"};
    functions["srl"] = {"R", "101", "0000000"};
    functions["sra"] = {"R", "101", "0100000"};
    functions["or"] = {"R", "110", "0000000"};
    functions["and"] = {"R", "111", "0000000"};
}

void addITypeInstructions() {
    functions["jalr"] = {"I", "000"};
    functions["addi"] = {"I", "000"};
    functions["slti"] = {"I", "010"};
    functions["sltiu"] = {"I", "011"};
    functions["xori"] = {"I", "100"};
    functions["ori"] = {"I", "110"};
    functions["andi"] = {"I", "111"};
    
    functions["lb"] = {"I", "000"};
    functions["lh"] = {"I", "001"};
    functions["lw"] = {"I", "010"};
    functions["lbu"] = {"I", "100"};
    functions["lhu"] = {"I", "101"};
}

void addSTypeInstructions() {
    functions["sb"] = {"S", "000"};
    functions["sh"] = {"S", "001"};
    functions["sw"] = {"S", "010"};
}

void addBTypeInstructions() {
    functions["beq"] = {"B", "000"};
    functions["bne"] = {"B", "001"};
    functions["blt"] = {"B", "100"};
    functions["bge"] = {"B", "101"};
    functions["bltu"] = {"B", "110"};
    functions["bgeu"] = {"B", "111"};
}

void addUTypeInstructions() {
    functions["lui"] = {"U"};
    functions["auipc"] = {"U"};
}

void addJTypeInstructions() {
    functions["jal"] = {"J"};
}

void initializeFunctions() {
    addRTypeInstructions();
    addITypeInstructions();
    addSTypeInstructions();
    addBTypeInstructions();
    addUTypeInstructions();
    addJTypeInstructions();
}

unordered_map<string, string> registers = {
    {"zero","x0"},
    {"ra","x1"},
    {"sp","x2"},
    {"gp","x3"},
    {"tp","x4"},
    {"t0","x5"},
    {"t1","x6"},
    {"t2","x7"},
    {"s0","x8"},
    {"fp","x8"},
    {"s1","x9"},
    {"a0","x10"},
    {"a1","x11"},
    {"a2","x12"},
    {"a3","x13"},
    {"a4","x14"},
    {"a5","x15"},
    {"a6","x16"},
    {"a7","x17"},
    {"s2","x18"},
    {"s3","x19"},
    {"s4","x20"},
    {"s5","x21"},
    {"s6","x22"},
    {"s7","x23"},
    {"s8","x24"},
    {"s9","x25"},
    {"s10","x26"},
    {"s11","x27"},
    {"t3","x28"},
    {"t4","x29"},
    {"t5","x30"},
    {"t6","x31"},
};

string hexDigitToBinary(char hexDigit) {
    switch(toupper(hexDigit)){
        case '0': return "0000";
        case '1': return "0000";
        case '2': return "0000";
        case '3': return "0000";
        case '4': return "0000";
        case '5': return "0000";
        case '6': return "0000";
        case '7': return "0000";
        case '8': return "0000";
        case '9': return "0000";
        case 'A': return "0000";
        case 'B': return "0000";
        case 'C': return "0000";
        case 'D': return "0000";
        case 'E': return "0000";
        case 'F': return "0000";
        default: return "";
    }
}

class Instruction {
public:
    string machineCode;
    
    string hexToBin(string hex){
        string binary = "";
        for(char hexDigit : hex){
            string bin = hexDigitToBinary(hexDigit);
            if(!bin.empty()){
                binary += bin;
            }
        }
        
        if(binary.length() > 32) {
            binary = binary.substr(binary.length() - 32);
        }
        else if(binary.length() < 32){
            binary = string(32 - binary.length(), '0') + binary;
        }
        
        return binary;
    }
    
    string decimalToBinary(const string& decimalStr){
        int decimal = stoi(decimalStr);
        string binaryStr = bitset<32>(decimal).to_string();
        
        if(binaryStr.empty()){
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
    
    string findRegister(string s){
        if(s[0] != 'x' && s[0] != 'X'){
            if(registers.find(s) != registers.end()){
                s = registers[s];
            }
        }
        
        s.erase(0, 1);
        makeStrLenBin(s, 5);
        return s;
    }
    
    void labelToImme(string &str, int n, int lineNum){
        int labelIdx = -1;
        if(labels.find(str) != labels.end()){
            labelIdx = labels[str];
        }

        int offset = lineNum - labelIdx;
        str = to_string(offset);
        
        makeStrLenBin(str, n-1);
        if(offset > 0){
            str = "0" + str;
            str = twosComplementor(str);
        }
        else {
            str = "0" + str;
        }
    }
    
    string getMachineCode() {
        return machineCode;
    }
};

class R : public Instruction {
private:
    string opcode = "0110011", rd, func3, rs1, rs2, func7;
    
    void joinCodes() {
        machineCode = func7 + rs2 + rs1 + func3 + rd + opcode;
    }
    
public:
    R(vector<string> inst_break, vector<string> modeAndFunc) {
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
};

class I : public Instruction {
private:
    string opcode = "0010011", rd, func3, rs1, imm;
    
    void joinCodes() {
        machineCode = imm + rs1 + func3 + rd + opcode;
    }

public: 
    I (vector<string> inst_break, vector<string> modeAndFunc){
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
};

class S : public Instruction {
private: 
    string opcode = "0100011", imm1, func3, rs1, rs2, imm2;
     
    void joinCodes() {
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
};


class B : public Instruction {
private:
    string opcode = "1100011", imm1, func3, rs1, rs2, imm2;
    
    void joinCodes() {
        machineCode = imm2 + rs2 + rs1 + func3 + imm1 + opcode;
    }
    
public:
    B (vector<string> inst_break, vector<string> modeAndFunc, int lineNum){
        this->rs2 = inst_break[1];
        this->rs1 = inst_break[2];
        
        rs2 = rs2.substr(0, rs2.find(','));
        rs1 = rs1.substr(0, rs1.find(','));
        
        rs2 = findRegister(rs2);
        rs1 = findRegister(rs1);
        
        string str = inst_break[3];
        
        // labelToImme(str, 12, lineNum);
        // this->imm2 = str.substr(0, 7);
        // this->imm1 = str.substr(7, 12);
        
        labelToImme(str,  13, lineNum);
        str.erase(str.size() - 1);
        this->imm2 = str[0] + str.substr(2, 6);
        this->imm1 = str.substr(8, 4) + str[1];
        
        this->func3 = modeAndFunc[1];
        joinCodes();
    }
};

class U : public Instruction {
private:
    string opcode = "0110111", rd, imm;
    
    void joinCodes() {
        machineCode = imm + rd + opcode;
    }

public:
    U (vector<string> inst_break){
        this->rd = inst_break[1];
        this->imm = inst_break[2];
        
        rd = tolowerString(rd.substr(0, rd.find(',')));
        rd = findRegister(rd);
        
        makeStrLenBin(imm, 20);
        
        joinCodes();
    }
};

class J : public Instruction {
private:
    string opcode = "1101111", rd, imm;
    
    void joinCodes() {
        machineCode = imm + rd + opcode;
    }

public:
    J (vector<string> inst_break, int lineNum){
        this->rd = inst_break[1];
        rd = tolowerString(rd.substr(0, rd.find(',')));
        rd = findRegister(rd);
        
        // this->imm = inst_break[2];
        // labelToImme(imm, 20, lineNum);
        
        labelToImme(imm, 21, lineNum);
        imm.erase(imm.size() - 1);
        string str = imm;
        imm = str[0] + str.substr(10, 10) + str[9] + str.substr(1,8);
        
        joinCodes();
    }
};

char flip(char c) {
    return (c == '0')? '1': '0';
} 
  
string twosComplementor(string bin) 
{ 
    int n = bin.length(); 
    int i; 
  
    string ones, twos; 
    ones = twos = ""; 
  
    for (i = 0; i < n; i++) 
        ones += flip(bin[i]); 
  
    twos = ones; 
    for (i = n - 1; i >= 0; i--) 
    { 
        if (ones[i] == '1') 
            twos[i] = '0'; 
        else
        { 
            twos[i] = '1'; 
            break; 
        } 
    } 

    if (i == -1) 
        twos = '1' + twos; 
  
    return twos;
} 

class Assembler {
private:
    string tolowerString(const string& func){
        string str = "";
        for(const char &it : func){
            str.push_back(tolower(it));
        }
        return str;
    }
    
    vector<string> getInfo(string func){
        func = tolowerString(func);
        if(functions.find(func) != functions.end()){
            return functions[func];
        }
        return {""};
    }
    
    void removeBrackets(string& instruction){
        int n = instruction.size();
        for(int i = 0; i < n; i++){
            if(instruction[i] == '(' || instruction[i] == ')'){
                instruction[i] = ' ';
            }
        }
    }
    
    string help_assembler(vector<string>& inst_break, vector<string>& modeAndFunc, int lineNum, string addMode){
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
            B bMode = B(inst_break, modeAndFunc, lineNum);
            machineCode = bMode.getMachineCode();
        }
        else if(addMode == "U"){
            U uMode = U(inst_break);
            machineCode = uMode.getMachineCode();
        }
        else if(addMode == "J"){
            J jMode = J(inst_break, lineNum);
            machineCode = jMode.getMachineCode();
        }
        
        return machineCode;
    }
    
public:
    Assembler() {
        initializeFunctions();
    }
    
    string assemble(string& instruction, int lineNum){
        removeBrackets(instruction);
        
        vector<string> inst_break;
        stringstream s(instruction);
        string word;
        
        while(getline(s, word, ' ')){
            inst_break.push_back(word);
        }
        
        vector<string> modeAndFunc = getInfo(inst_break[0]);
        string addMode = modeAndFunc[0];
        
        string machineCode = help_assembler(inst_break, modeAndFunc, lineNum, addMode);
        
        return machineCode;
    }
};

void readCodeAndFindLabel(vector<string>& assemblyCode){
    ifstream fin;
    fin.open("Assembly.txt");
    
    string line;
    int count = 1;
    
    while(getline(fin, line)){
        if(line.find(" ") == string::npos){
            line.pop_back();
            labels[line] = count;
        }
        assemblyCode.push_back(line);
        // cout << line << endl;
        count ++;
    }
    
    fin.close();
}

vector<string> convertToMachineCode(Assembler assembler, vector<string>& assemblyCode){
    vector<string> machineCode;
    ofstream fout;
    fout.open("MachineCode.txt");
    
    int count = 0;
    string line;
    for(int i = 1; i <= assemblyCode.size(); i++){
        line = assemblyCode[i-1];
        if(line.find(" ") != string::npos){
            string str = assembler.assemble(line, i);
            machineCode.push_back(str);
            fout << str << endl;
        }
        count ++;
    }
    
    fout.close();
    return machineCode;
}

void printCodes(vector<string>& code){
    cout << endl;
    for(auto &it: code){
        cout << it << endl;
    }
}

int main() {
    vector<string> assemblyCode;
    
    readCodeAndFindLabel(assemblyCode);
    Assembler assembler;
    vector<string> machineCode = convertToMachineCode(assembler, assemblyCode);
    
    printCodes(machineCode);
}