#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <format>

void DisassembleOpCode(const std::vector<std::byte> &codebuffer, int &pc)
{
    const std::byte *code = &codebuffer[pc];
    int opbytes = 1;

    std::cout << std::format("{:04x} ", pc);

    switch (static_cast<unsigned char>(code[0]))
    {
    case 0x00:
        std::cout << "NOP";
        break;
    case 0x01:
        std::cout << std::format("LXI    B,#{:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0x02:
        std::cout << "STAX   B";
        break;
    case 0x03:
        std::cout << "INX    B";
        break;
    case 0x04:
        std::cout << "INR    B";
        break;
    case 0x05:
        std::cout << "DCR    B";
        break;
    case 0x06:
        std::cout << std::format("MVI    B,#{:02x}", static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x07:
        std::cout << "RLC";
        break;
    case 0x08:
        std::cout << "NOP";
        break;
    case 0x09:
        std::cout << "DAD    B";
        break;
    case 0x0a:
        std::cout << "LDAX   B";
        break;
    case 0x0b:
        std::cout << "DCX    B";
        break;
    case 0x0c:
        std::cout << "INR    C";
        break;
    case 0x0d:
        std::cout << "DCR    C";
        break;
    case 0x0e:
        std::cout << std::format("MVI    C,#{:02x}", static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x0f:
        std::cout << "RRC";
        break;
    case 0x10:
        std::cout << "NOP";
        break;
    case 0x11:
        std::cout << std::format("LXI    D,#{:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0x12:
        std::cout << "STAX   D";
        break;
    case 0x13:
        std::cout << "INX    D";
        break;
    case 0x14:
        std::cout << "INR    D";
        break;
    case 0x15:
        std::cout << "DCR    D";
        break;
    case 0x16:
        std::cout << std::format("MVI    D,#{:02x}",
                                 static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x17:
        std::cout << "RAL";
        break;
    case 0x18:
        std::cout << "NOP";
        break;
    case 0x19:
        std::cout << "DAD    D";
        break;
    case 0x1a:
        std::cout << "LDAX   D";
        break;
    case 0x1b:
        std::cout << "DCX    D";
        break;
    case 0x1c:
        std::cout << "INR    D";
        break;
    case 0x1d:
        std::cout << "DCR    E";
        break;
    case 0x1e:
        std::cout << std::format("MVI    E,#{:02x}",
                                 static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x1f:
        std::cout << "RAR";
        break;
    case 0x20:
        std::cout << "RIM";
        break;
    case 0x21:
        std::cout << std::format("LXI    H,#{:02x}{:02x}",
                                 static_cast<unsigned char>(code[1]),
                                 static_cast<unsigned char>(code[2]));
        opbytes = 3;
        break;
    case 0x22:
        std::cout << std::format("SHLD   ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[1]),
                                 static_cast<unsigned char>(code[2]));
        opbytes = 3;
        break;
    case 0x23:
        std::cout << "INX    H";
        break;
    case 0x24:
        std::cout << "INR    H";
        break;
    case 0x25:
        std::cout << "DCR    H";
        break;
    case 0x26:
        std::cout << std::format("MVI    H,#{:02x}",
                                 static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x27:
        std::cout << "DAA";
        break;
    case 0x28:
        std::cout << "NOP";
        break;
    case 0x29:
        std::cout << "DAD    H";
        break;
    case 0x2a:
        std::cout << std::format("LHLD   ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[1]),
                                 static_cast<unsigned char>(code[2]));
        opbytes = 3;
        break;
    case 0x2b:
        std::cout << "DCX    H";
        break;
    case 0x2c:
        std::cout << "INR    L";
        break;
    case 0x2d:
        std::cout << "DCR    L";
        break;
    case 0x2e:
        std::cout << std::format("MVI    L,${:02x}", static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x2f:
        std::cout << "CMA";
        break;
    case 0x30:
        std::cout << "SIM";
        break;
    case 0x31:
        std::cout << std::format("LXI    SP,${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0x32:
        std::cout << std::format("STA    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0x33:
        std::cout << "INX    SP";
        break;
    case 0x34:
        std::cout << "INR    M";
        break;
    case 0x35:
        std::cout << "DCR    M";
        break;
    case 0x36:
        std::cout << std::format("MVI    M,#{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0x37:
        std::cout << "STC";
        break;
    case 0x38:
        std::cout << "NOP";
        break;
    case 0x39:
        std::cout << "DAD    SP";
        break;
    case 0x3a:
        std::cout << std::format("LDA    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0x3b:
        std::cout << "DCX    SP";
        break;
    case 0x3c:
        std::cout << "INR    A";
        break;
    case 0x3d:
        std::cout << "DCR    A";
        break;
    case 0x3e:
        std::cout << std::format("MVI    A,#{:02x}", static_cast<unsigned char>(code[1]));
        opbytes = 2;
        break;
    case 0x3f:
        std::cout << "CMC";
        break;
    case 0x40:
        std::cout << "MOV    B,B";
        break;
    case 0x41:
        std::cout << "MOV    B,C";
        break;
    case 0x42:
        std::cout << "MOV    B,D";
        break;
    case 0x43:
        std::cout << "MOV    B,E";
        break;
    case 0x44:
        std::cout << "MOV    B,H";
        break;
    case 0x45:
        std::cout << "MOV    B,L";
        break;
    case 0x46:
        std::cout << "MOV    B,M";
        break;
    case 0x47:
        std::cout << "MOV    B,A";
        break;
    case 0x48:
        std::cout << "MOV    C,B";
        break;
    case 0x49:
        std::cout << "MOV    C,C";
        break;
    case 0x4a:
        std::cout << "MOV    C,D";
        break;
    case 0x4b:
        std::cout << "MOV    C,E";
        break;
    case 0x4c:
        std::cout << "MOV    C,H";
        break;
    case 0x4d:
        std::cout << "MOV    C,L";
        break;
    case 0x4e:
        std::cout << "MOV    C,M";
        break;
    case 0x4f:
        std::cout << "MOV    C,A";
        break;
    case 0x50:
        std::cout << "MOV    D,B";
        break;
    case 0x51:
        std::cout << "MOV    D,C";
        break;
    case 0x52:
        std::cout << "MOV    D,D";
        break;
    case 0x53:
        std::cout << "MOV    D,E";
        break;
    case 0x54:
        std::cout << "MOV    D,H";
        break;
    case 0x55:
        std::cout << "MOV    D,L";
        break;
    case 0x56:
        std::cout << "MOV    D,M";
        break;
    case 0x57:
        std::cout << "MOV    D,A";
        break;
    case 0x58:
        std::cout << "MOV    E,B";
        break;
    case 0x59:
        std::cout << "MOV    E,C";
        break;
    case 0x5a:
        std::cout << "MOV    E,D";
        break;
    case 0x5b:
        std::cout << "MOV    E,E";
        break;
    case 0x5c:
        std::cout << "MOV    E,H";
        break;
    case 0x5d:
        std::cout << "MOV    E,L";
        break;
    case 0x5e:
        std::cout << "MOV    E,M";
        break;
    case 0x5f:
        std::cout << "MOV    E,A";
        break;
    case 0x60:
        std::cout << "MOV    H,B";
        break;
    case 0x61:
        std::cout << "MOV    H,C";
        break;
    case 0x62:
        std::cout << "MOV    H,D";
        break;
    case 0x63:
        std::cout << "MOV    H,E";
        break;
    case 0x64:
        std::cout << "MOV    H,H";
        break;
    case 0x65:
        std::cout << "MOV    H,L";
        break;
    case 0x66:
        std::cout << "MOV    H,M";
        break;
    case 0x67:
        std::cout << "MOV    H,A";
        break;
    case 0x68:
        std::cout << "MOV    L,B";
        break;
    case 0x69:
        std::cout << "MOV    L,C";
        break;
    case 0x6a:
        std::cout << "MOV    L,D";
        break;
    case 0x6b:
        std::cout << "MOV    L,E";
        break;
    case 0x6c:
        std::cout << "MOV    L,H";
        break;
    case 0x6d:
        std::cout << "MOV    L,L";
        break;
    case 0x6e:
        std::cout << "MOV    L,M";
        break;
    case 0x6f:
        std::cout << "MOV    L,A";
        break;
    case 0x70:
        std::cout << "MOV    M,B";
        break;
    case 0x71:
        std::cout << "MOV    M,C";
        break;
    case 0x72:
        std::cout << "MOV    M,D";
        break;
    case 0x73:
        std::cout << "MOV    M,E";
        break;
    case 0x74:
        std::cout << "MOV    M,H";
        break;
    case 0x75:
        std::cout << "MOV    M,L";
        break;
    case 0x76:
        std::cout << "HLT";
        break;
    case 0x77:
        std::cout << "MOV    M,A";
        break;
    case 0x78:
        std::cout << "MOV    A,B";
        break;
    case 0x79:
        std::cout << "MOV    A,C";
        break;
    case 0x7a:
        std::cout << "MOV    A,D";
        break;
    case 0x7b:
        std::cout << "MOV    A,E";
        break;
    case 0x7c:
        std::cout << "MOV    A,H";
        break;
    case 0x7d:
        std::cout << "MOV    A,L";
        break;
    case 0x7e:
        std::cout << "MOV    A,M";
        break;
    case 0x7f:
        std::cout << "MOV    A,A";
        break;
    case 0x80:
        std::cout << "ADD    B";
        break;
    case 0x81:
        std::cout << "ADD    C";
        break;
    case 0x82:
        std::cout << "ADD    D";
        break;
    case 0x83:
        std::cout << "ADD    E";
        break;
    case 0x84:
        std::cout << "ADD    H";
        break;
    case 0x85:
        std::cout << "ADD    L";
        break;
    case 0x86:
        std::cout << "ADD    M";
        break;
    case 0x87:
        std::cout << "ADD    A";
        break;
    case 0x88:
        std::cout << "ADC    B";
        break;
    case 0x89:
        std::cout << "ADC    C";
        break;
    case 0x8a:
        std::cout << "ADC    D";
        break;
    case 0x8b:
        std::cout << "ADC    E";
        break;
    case 0x8c:
        std::cout << "ADC    H";
        break;
    case 0x8d:
        std::cout << "ADC    L";
        break;
    case 0x8e:
        std::cout << "ADC    M";
        break;
    case 0x8f:
        std::cout << "ADC    A";
        break;
    case 0x90:
        std::cout << "SUB    B";
        break;
    case 0x91:
        std::cout << "SUB    C";
        break;
    case 0x92:
        std::cout << "SUB    D";
        break;
    case 0x93:
        std::cout << "SUB    E";
        break;
    case 0x94:
        std::cout << "SUB    H";
        break;
    case 0x95:
        std::cout << "SUB    L";
        break;
    case 0x96:
        std::cout << "SUB    M";
        break;
    case 0x97:
        std::cout << "SUB    A";
        break;
    case 0x98:
        std::cout << "SBB    B";
        break;
    case 0x99:
        std::cout << "SBB    C";
        break;
    case 0x9a:
        std::cout << "SBB    D";
        break;
    case 0x9b:
        std::cout << "SBB    E";
        break;
    case 0x9c:
        std::cout << "SBB    H";
        break;
    case 0x9d:
        std::cout << "SBB    L";
        break;
    case 0x9e:
        std::cout << "SBB    M";
        break;
    case 0x9f:
        std::cout << "SBB    A";
        break;
    case 0xa0:
        std::cout << "ANA    B";
        break;
    case 0xa1:
        std::cout << "ANA    C";
        break;
    case 0xa2:
        std::cout << "ANA    D";
        break;
    case 0xa3:
        std::cout << "ANA    E";
        break;
    case 0xa4:
        std::cout << "ANA    H";
        break;
    case 0xa5:
        std::cout << "ANA    L";
        break;
    case 0xa6:
        std::cout << "ANA    M";
        break;
    case 0xa7:
        std::cout << "ANA    A";
        break;
    case 0xa8:
        std::cout << "XRA    B";
        break;
    case 0xa9:
        std::cout << "XRA    C";
        break;
    case 0xaa:
        std::cout << "XRA    D";
        break;
    case 0xab:
        std::cout << "XRA    E";
        break;
    case 0xac:
        std::cout << "XRA    H";
        break;
    case 0xad:
        std::cout << "XRA    L";
        break;
    case 0xae:
        std::cout << "XRA    M";
        break;
    case 0xaf:
        std::cout << "XRA    A";
        break;
    case 0xb0:
        std::cout << "ORA    B";
        break;
    case 0xb1:
        std::cout << "ORA    C";
        break;
    case 0xb2:
        std::cout << "ORA    D";
        break;
    case 0xb3:
        std::cout << "ORA    E";
        break;
    case 0xb4:
        std::cout << "ORA    H";
        break;
    case 0xb5:
        std::cout << "ORA    L";
        break;
    case 0xb6:
        std::cout << "ORA    M";
        break;
    case 0xb7:
        std::cout << "ORA    A";
        break;
    case 0xb8:
        std::cout << "CMP    B";
        break;
    case 0xb9:
        std::cout << "CMP    C";
        break;
    case 0xba:
        std::cout << "CMP    D";
        break;
    case 0xbb:
        std::cout << "CMP    E";
        break;
    case 0xbc:
        std::cout << "CMP    H";
        break;
    case 0xbd:
        std::cout << "CMP    L";
        break;
    case 0xbe:
        std::cout << "CMP    M";
        break;
    case 0xbf:
        std::cout << "CMP    A";
        break;
    case 0xc0:
        std::cout << "RNZ";
        break;
    case 0xc1:
        std::cout << "POP    B";
        break;
    case 0xc2:
        std::cout << std::format("JNZ    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xc3:
        std::cout << std::format("JMP    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xc4:
        std::cout << std::format("CNZ    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xc5:
        std::cout << "PUSH   B";
        break;
    case 0xc6:
        std::cout << std::format("ADI    #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xc7:
        std::cout << "RST    0";
        break;
    case 0xc8:
        std::cout << "RZ";
        break;
    case 0xc9:
        std::cout << "RET";
        break;
    case 0xca:
        std::cout << std::format("JZ     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xcb:
        std::cout << "NOP";
        break;
    case 0xcc:
        std::cout << std::format("CZ     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xcd:
        std::cout << std::format("CALL   ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xce:
        std::cout << std::format("ACI    #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xcf:
        std::cout << "RST    1";
        break;
    case 0xd0:
        std::cout << "RNC";
        break;
    case 0xd1:
        std::cout << "POP    D";
        break;
    case 0xd2:
        std::cout << std::format("JNC    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xd3:
        std::cout << std::format("OUT    #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xd4:
        std::cout << std::format("CNC    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xd5:
        std::cout << "PUSH   D";
        break;
    case 0xd6:
        std::cout << std::format("SUI    #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xd7:
        std::cout << "RST    2";
        break;
    case 0xd8:
        std::cout << "RC";
        break;
    case 0xd9:
        std::cout << "NOP";
        break;
    case 0xda:
        std::cout << std::format("JC     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xdb:
        std::cout << std::format("IN     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xdc:
        std::cout << std::format("CC     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xdd:
        std::cout << "NOP";
        break;
    case 0xde:
        std::cout << std::format("SBI     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xdf:
        std::cout << "RST    3";
        break;
    case 0xe0:
        std::cout << "RPO";
        break;
    case 0xe1:
        std::cout << "POP    H";
        break;
    case 0xe2:
        std::cout << std::format("JPO    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xe3:
        std::cout << "XTHL";
        break;
    case 0xe4:
        std::cout << std::format("CPO    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xe5:
        std::cout << "PUSH   H";
        break;
    case 0xe6:
        std::cout << std::format("ANI     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xe7:
        std::cout << "RST    4";
        break;
    case 0xe8:
        std::cout << "RPE";
        break;
    case 0xe9:
        std::cout << "PCHL";
        break;
    case 0xea:
        std::cout << std::format("JPE    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xeb:
        std::cout << "XCHG";
        break;
    case 0xec:
        std::cout << std::format("CPE    ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xed:
        std::cout << "NOP";
        break;
    case 0xee:
        std::cout << std::format("XRI     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xef:
        std::cout << "RST    5";
        break;
    case 0xf0:
        std::cout << "RP";
        break;
    case 0xf1:
        std::cout << "POP    PSW";
        break;
    case 0xf2:
        std::cout << std::format("JP     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xf3:
        std::cout << "DI";
        break;
    case 0xf4:
        std::cout << std::format("CP     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xf5:
        std::cout << "PUSH   PSW";
        break;
    case 0xf6:
        std::cout << std::format("ORI     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xf7:
        std::cout << "RST    6";
        break;
    case 0xf8:
        std::cout << "RM";
        break;
    case 0xf9:
        std::cout << "SPHL";
        break;
    case 0xfa:
        std::cout << std::format("JM     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xfb:
        std::cout << "EI";
        break;
    case 0xfc:
        std::cout << std::format("CM     ${:02x}{:02x}",
                                 static_cast<unsigned char>(code[2]),
                                 static_cast<unsigned char>(code[1]));
        opbytes = 3;
        break;
    case 0xfd:
        std::cout << "NOP";
        break;
    case 0xfe:
        std::cout << std::format("CPI     #{:02x}", static_cast<unsigned char>(code[1]));
        break;
    case 0xff:
        std::cout << "RST    7";

    std::cout << std::endl;
    pc += opbytes;
}
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "error: Program requires exactly one command line argument." << std::endl;
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

    int pc = 0;
    while (pc < fsize)
    {
        DisassembleOpCode(buffer, pc);
    }

    return 0;
}