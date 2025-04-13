#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <format>
#include <unordered_map>
#include <utility>
#include <ranges>

#include <bw_util.h>

std::unordered_map<unsigned int, std::string> RP = {
    {0b000, "BC"},
    {0b001, "DE"},
    {0b010, "HL"},
    {0b011, "PSW"}
};

std::unordered_map<unsigned int, std::string> DDD = {
    {0b000, "B"},
    {0b001, "C"},
    {0b010, "D"},
    {0b011, "E"},
    {0b100, "H"},
    {0b101, "L"},
    {0b110, "M"},
    {0b111, "A"}
};

std::unordered_map<unsigned int, std::string> CC = {
    {0b000, "NZ"},
    {0b001, "Z"},
    {0b010, "NC"},
    {0b011, "C"},
    {0b100, "PO"},
    {0b101, "PE"},
    {0b110, "P"},
    {0b111, "N"}
};

std::unordered_map<unsigned int, std::string> ALU = {
    {0b000, "ADD"},
    {0b001, "ADC"},
    {0b010, "SUB"},
    {0b011, "SBB"},
    {0b100, "ANA"},
    {0b101, "XRA"},
    {0b110, "ORA"},
    {0b111, "CMP"}
};

std::unordered_map<unsigned int, std::pair<std::string, int>> Set1 = {
    {0b00000000, {"NOP", 0}},
    {0b00000111, {"RLC", 0}},
    {0b00001111, {"RRC", 0}},
    {0b00010111, {"RAL", 0}},
    {0b00011111, {"RAR", 0}},
    {0b00100010, {"SHLD", 2}},
    {0b00100111, {"DAA", 0}},
    {0b00101010, {"LHLD", 2}},
    {0b00101111, {"CMA", 0}},
    {0b00110010, {"STA", 2}},
    {0b00110111, {"STC", 0}},
    {0b00111010, {"LDA", 2}},
    {0b00111111, {"CMC", 0}},
    {0b01110110, {"HLT", 0}},
    {0b11000011, {"JMP", 2}},
    {0b11001001, {"RET", 0}},
    {0b11001101, {"CALL", 2}},
    {0b11010011, {"OUT", 1}},
    {0b11011011, {"IN", 1}},
    {0b11100011, {"XTHL", 0}},
    {0b11101001, {"PCHL", 0}},
    {0b11101011, {"XCHG", 0}},
    {0b11110011, {"DI", 0}},
    {0b11111001, {"SPHL", 0}},
    {0b11111011, {"EI", 0}}
};

std::unordered_map<unsigned int, std::pair<std::string, int>> Set2 = {
    {0b000001, {"LXI", 2}},
    {0b000010, {"STAX", 0}},
    {0b000011, {"INX", 0}},
    {0b001001, {"DAD", 0}},
    {0b001010, {"LDAX", 0}},
    {0b001011, {"DCX", 0}},
    {0b110001, {"POP", 0}},
    {0b110101, {"PUSH", 0}}
};

std::unordered_map<unsigned int, std::pair<std::string, int>> Set3 = {
    {0b00100, {"INR", 0}},
    {0b00101, {"DCR", 0}},
    {0b00110, {"MVI", 1}}
};

std::unordered_map<unsigned int, std::pair<std::string, int>> Set4 = {
    {0b11000, {"RCC", 0}},
    {0b11010, {"JCC", 2}},
    {0b11100, {"CCC", 2}}
};



void print_pair(std::ofstream& output, std::pair<std::string, int> pair, std::string further_data, const std::byte *code, std::string extra_character) {
    output << std::format("{: <8}",pair.first);
    output << further_data;
    if (pair.second == 1) {
        output << extra_character << std::format("{:02x}", static_cast<unsigned int>(code[1]));
    }
    else if (pair.second == 2) {
        output << extra_character << std::format("{:02x}{:02x}", static_cast<unsigned int>(code[2]), static_cast<unsigned int>(code[1]));
    }
}


void DisassembleOpCode(const std::vector<std::byte> &codebuffer, int &pc, std::ofstream& output)
{
    const std::byte *code = &codebuffer[pc]; // Pointer to the current byte
    int opbytes = 1;

    output << std::format("{:04x} ", pc); // Print the PC in hexadecimal format

    unsigned int opcode = static_cast<unsigned int>(code[0]);

    // Set 1

    if (Set1.find(opcode)!= Set1.end()) {
        auto pair = Set1[opcode];
        print_pair(output, pair, "", code,"");
        opbytes += pair.second;
    }
    else{

        bwu::bitvector new_opcode = bwu::bitvector(opcode);

        // Set 2
        if (Set2.find(new_opcode.poprange(4,6))!= Set2.end()){
            auto pair = Set2[new_opcode.poprange(4,6)];
            print_pair(output, pair,RP[new_opcode.getrange(4,6)], code, ",");
            opbytes += pair.second;
        }
        // Set 3
        else if(Set3.find(new_opcode.poprange(3,6))!= Set3.end()) {
            auto pair = Set3[new_opcode.poprange(3,6)];
            print_pair(output, pair,DDD[new_opcode.getrange(3,6)], code, ",");
            opbytes += pair.second;
        }
        // MOV Command
        else if(new_opcode.poprange(0,6) == 0b01) {
            print_pair(output, {"MOV",0},DDD[new_opcode.getrange(3,6)]+","+DDD[new_opcode.getrange(0,3)],code, "");
        }
        // Set 4
        else if(Set4.find(new_opcode.poprange(3,6))!= Set4.end()) {
            auto pair = Set4[new_opcode.poprange(3,6)];
            print_pair(output, pair, CC[new_opcode.getrange(3,6)]+",", code, "");
            opbytes += pair.second;
        }
        // RST Command
        else if(new_opcode.poprange(3,6) == 0b11111) {
            print_pair(output, {"RST", 0},std::format("{:04x}", new_opcode.getrange(3,6)),code, "");
        }
        // ALU Data Command
        else if(new_opcode.poprange(3,6) == 0b11110) {
            print_pair(output, {ALU[new_opcode.getrange(3,6)], 1}, "", code, "");
            opbytes += 1;
        }
        // ALU Register Command
        else if(new_opcode.poprange(0,6) == 0b10) {
            print_pair(output, {ALU[new_opcode.getrange(3,6)], 0}, DDD[new_opcode.getrange(0,3)], code, "");
        }

    }
    output << std::endl;
    pc += opbytes;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "error: Program requires exactly two command line arguments." << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::cerr << "error: Couldn't open " << filename << std::endl;
        return 1;
    }

    std::streamsize fsize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<std::byte> buffer(fsize);
    if (!file.read(reinterpret_cast<char *>(buffer.data()), fsize))
    {
        std::cerr << "error: Failed to read the file." << std::endl;
        return 1;
    }

    std::string o_filename = argv[2];

    std::ofstream output;
    output.open(o_filename);


    int pc = 0;
    while (pc < fsize)
    {
        DisassembleOpCode(buffer, pc, output);
    }

    output.close();

    return 0;
}