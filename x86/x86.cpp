//==============================================================================
// miCPU : x86 Source
//
// Copyright (c) 2025 TAiGA
// https://github.com/metarutaiga/miCPU
//==============================================================================
#include "x86.h"

//------------------------------------------------------------------------------
#define o &x86::
#define x , o
//------------------------------------------------------------------------------
// One-Byte Opcode Map
//------------------------------------------------------------------------------
const x86::instruction_pointer x86::one[256] =
{      // 0        1       2      3      4       5       6       7       8       9       A       B       C        D       E       F
/* 0 */ o ADD    x ADD   x ADD  x ADD  x ADD   x ADD   x PUSH  x POP   x OR    x OR    x OR    x OR    x OR     x OR    x PUSH  x TWO
/* 1 */ x ADC    x ADC   x ADC  x ADC  x ADC   x ADC   x PUSH  x POP   x SBB   x SBB   x SBB   x SBB   x SBB    x SBB   x PUSH  x POP
/* 2 */ x AND    x AND   x AND  x AND  x AND   x AND   x ___   x ___   x SUB   x SUB   x SUB   x SUB   x SUB    x SUB   x ___   x ___
/* 3 */ x XOR    x XOR   x XOR  x XOR  x XOR   x XOR   x ___   x ___   x CMP   x CMP   x CMP   x CMP   x CMP    x CMP   x ___   x ___
/* 4 */ x INC    x INC   x INC  x INC  x INC   x INC   x INC   x INC   x DEC   x DEC   x DEC   x DEC   x DEC    x DEC   x DEC   x DEC
/* 5 */ x PUSH   x PUSH  x PUSH x PUSH x PUSH  x PUSH  x PUSH  x PUSH  x POP   x POP   x POP   x POP   x POP    x POP   x POP   x POP
/* 6 */ x PUSHAD x POPAD x ___  x ___  x ___   x ___   x OS    x ___   x PUSH  x IMUL  x PUSH  x IMUL  x ___    x ___   x ___   x ___
/* 7 */ x Jcc    x Jcc   x Jcc  x Jcc  x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc    x Jcc   x Jcc   x Jcc
/* 8 */ x grp1   x grp1  x ___  x grp1 x TEST  x TEST  x XCHG  x XCHG  x MOV   x MOV   x MOV   x MOV   x MOV    x LEA   x MOV   x POP
/* 9 */ x XCHG   x XCHG  x XCHG x XCHG x XCHG  x XCHG  x XCHG  x XCHG  x CWDE  x CDQ   x ___   x ___   x PUSHFD x POPFD x SAHF  x LAHF
/* A */ x ___    x ___   x ___  x ___  x MOVSx x MOVSx x CMPSx x CMPSx x TEST  x TEST  x STOSx x STOSx x LODSx  x LODSx x SCASx x SCASx
/* B */ x MOV    x MOV   x MOV  x MOV  x MOV   x MOV   x MOV   x MOV   x MOV   x MOV   x MOV   x MOV   x MOV    x MOV   x MOV   x MOV
/* C */ x grp2   x grp2  x RET  x RET  x ___   x ___   x MOV   x MOV   x ENTER x LEAVE x ___   x ___   x ___    x ___   x ___   x ___
/* D */ x grp2   x grp2  x grp2 x grp2 x ___   x ___   x ___   x XLAT  x ESC   x ESC   x ESC   x ESC   x ESC    x ESC   x ESC   x ESC
/* E */ x LOOP   x LOOP  x LOOP x Jcc  x ___   x ___   x ___   x ___   x CALL  x Jcc   x ___   x Jcc   x ___    x ___   x ___   x ___
/* F */ x ___    x ___   x REP  x REP  x ___   x CMC   x grp3  x grp3  x CLC   x STC   x ___   x ___   x CLD    x STD   x grp4  x grp5
};
//------------------------------------------------------------------------------
// Two-Byte Opcode Map
//------------------------------------------------------------------------------
const x86::instruction_pointer x86::two[256] =
{      // 0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F
/* 0 */ o grp6  x grp7  x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 1 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 2 */ x MOV   x MOV   x MOV   x MOV   x MOV   x ___   x MOV   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 3 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 4 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 5 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 6 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 7 */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* 8 */ x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc   x Jcc
/* 9 */ x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc x SETcc
/* A */ x ___   x ___   x ___   x BT    x SHxD  x SHxD  x ___   x ___   x ___   x ___   x ___   x BTS   x SHxD  x SHxD  x ___   x IMUL
/* B */ x ___   x ___   x ___   x BTR   x ___   x ___   x MOVZX x MOVZX x ___   x ___   x grp8  x BTC   x BSF   x BSR   x MOVSX x MOVSX
/* C */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* D */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* E */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
/* F */ x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___   x ___
};
//------------------------------------------------------------------------------
// Opcodes determined by bits 5,4,3 of modR/M byte
//------------------------------------------------------------------------------
const x86::instruction_pointer x86::group[16][8] =
{        // 0      1     2      3     4     5      6      7
/* 0 */ { o ___  x ___ x ___  x ___ x ___ x ___  x ___  x ___  },
/* 1 */ { o ADD  x OR  x ADC  x SBB x AND x SUB  x XOR  x CMP  },
/* 2 */ { o Rxx  x Rxx x Rxx  x Rxx x Sxx x Sxx  x ___  x Sxx  },
/* 3 */ { o TEST x ___ x NOT  x NEG x MUL x IMUL x DIV  x IDIV },
/* 4 */ { o INC  x DEC x ___  x ___ x ___ x ___  x ___  x ___  },
/* 5 */ { o INC  x DEC x CALL x ___ x JMP x ___  x PUSH x ___  },
/* 6 */ { o ___  x ___ x ___  x ___ x ___ x ___  x ___  x ___  },
/* 7 */ { o ___  x ___ x ___  x ___ x ___ x ___  x ___  x ___  },
/* 8 */ { o ___  x ___ x ___  x ___ x BT  x BTS  x BTR  x BTC  },
};
//------------------------------------------------------------------------------
#undef o
#undef x
//------------------------------------------------------------------------------
x86::~x86()
{
#if defined(_UCRT)
    _aligned_free(memory);
#else
    free(memory);
#endif
}
//------------------------------------------------------------------------------
bool x86::Initialize(size_t space, const void* program, size_t size)
{
    if (space & (1024 - 1)) {
        printf("space %zd is not aligned 1024\n", space);
        return false;
    }
    if (space < (1024 + size + 65536)) {
        printf("space %zd is less than %zd\n", space, 1024 + size + 65536);
        return false;
    }
#if defined(_UCRT)
    memory = (uint8_t*)_aligned_malloc(1024, space);
#else
    memory = (uint8_t*)aligned_alloc(1024, space);
#endif
    if (memory == nullptr) {
        printf("memory allocation is failed\n");
        return false;
    }
    memset(memory, 0, space);
    stack = memory + space - 16;

    eip = 1024;
    memcpy(memory + eip, program, size);

    return true;
}
//------------------------------------------------------------------------------
bool x86::Step()
{
    for (;;) {
        opcode = memory + eip;
        (this->*one[opcode[0]])();

        switch (opcode[0]) {
        case 0x26:
        case 0x2E:
        case 0x36:
        case 0x3E:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0xF0:
        case 0xF2:
        case 0xF3:
            continue;
            break;
        default:
            operand_size_override = false;
            repeat_string_operation = false;
            break;
        }
        break;
    }

    return true;
}
//------------------------------------------------------------------------------
std::string x86::Disassemble(int count)
{
    std::string output;

    x86 backup;
    for (int i = 0; i < 8; ++i)
        backup.regs[i] = regs[i];
    backup.eflags = eflags;
    backup.eip = eip;

    disasm = &output;

    for (int i = 0; i < count; ++i) {
        char temp[64];

        uint32_t address = eip;
        snprintf(temp, 64, "%08X", address);
        output += temp;
        output += ' ';
        output += ':';
        output += ' ';
        size_t insert = output.size();

        Step();

        for (uint32_t i = 0; i < 16; ++i) {
            if (address + i >= eip) {
                output.insert(insert, 2, ' ');
                continue;;
            }
            snprintf(temp, 64, "%02X", memory[address + i]);
            output.insert(insert, temp);
            insert += 2;
        }
    }

    disasm = nullptr;

    for (int i = 0; i < 8; ++i)
        regs[i] = backup.regs[i];
    eflags = backup.eflags;
    eip = backup.eip;

    return output;
}
//------------------------------------------------------------------------------
#define AL              regs[0].l
#define AH              regs[0].h
#define AX              regs[0].w
#define EAX             regs[0].d
#define CL              regs[1].l
#define CH              regs[1].h
#define CX              regs[1].w
#define ECX             regs[1].d
#define DL              regs[2].l
#define DH              regs[2].h
#define DX              regs[2].w
#define EDX             regs[2].d
#define BL              regs[3].l
#define BH              regs[3].h
#define BX              regs[3].w
#define EBX             regs[3].d
#define BP              regs[4].w
#define EBP             regs[4].d
#define SI              regs[5].w
#define ESI             regs[5].d
#define DI              regs[6].w
#define EDI             regs[6].d
#define SP              regs[7].w
#define ESP             regs[7].d
#define EIP             eip
#define EFLAGS          eflags.d
#define FLAGS           eflags.w
#define CF              eflags._c
#define PF              eflags._p
#define AF              eflags._a
#define ZF              eflags._z
#define SF              eflags._s
#define DF              eflags._d
#define OF              eflags._o
#define REG(reg)        ((int)((&reg - &EAX) / (&ECX - &EAX)))
#define IMM8(m,i)       (*(int8_t*)(m+i))
#define IMM16(m,i)      (*(int16_t*)(m+i))
#define IMM32(m,i)      (*(int32_t*)(m+i))
#define Push(reg)       { stack -= sizeof(uint32_t); *(uint32_t*)stack = reg; }
#define Pop()           (*(uint32_t*)((stack += sizeof(uint32_t)) - sizeof(uint32_t)))
//------------------------------------------------------------------------------
#define BEGIN_OPERATION(line) ; \
    EIP += format.length; \
    if (disasm) { \
        (*disasm) += line; \
        (*disasm) += '\n'; \
        return; \
    } \
    auto operation = [=, this](auto& DEST, auto SRC)
#define END_OPERATION ; \
    switch (format.size) { \
    case 8:     operation(*(uint8_t*)format.operand[0].memory, *(uint8_t*)format.operand[1].memory);    break; \
    case 16:    operation(*(uint16_t*)format.operand[0].memory, *(uint16_t*)format.operand[1].memory);  break; \
    case 32:    operation(*(uint32_t*)format.operand[0].memory, *(uint32_t*)format.operand[1].memory);  break; \
    }
//------------------------------------------------------------------------------
static const char* const REG8[8] = { "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH" };
static const char* const REG16[8] = { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI" };
static const char* const REG32[8] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
x86::Format x86::Decode(int offset, const char* instruction, int direction, int operand_size, int immediate_size)
{
    int OPREG = (direction == 0) ? 1 : 0;
    int MODRM = (direction == 0) ? 0 : 1;

    x86::Format format;
    format.size = (operand_size == 0) ? 8 : operand_size_override ? 16 : 32;
    format.length = offset + 1;
    format.instruction = instruction;
    if (offset) {
        int MOD = (opcode[offset] >> 6) & 0b11;
        int REG = (opcode[offset] >> 3) & 0b111;
        int RM = (opcode[offset] >> 0) & 0b111;

        int SS = (opcode[offset + 1] >> 6) & 0b11;
        int INDEX = (opcode[offset + 1] >> 3) & 0b111;
        int BASE = (opcode[offset + 1] >> 0) & 0b111;

        switch (opcode[offset] & 0b11111000) {
        case 0b00100000:
            format.length += 1;
            format.operand[MODRM].scale = (INDEX == 0b100) ? 0 : (1 << SS);
            format.operand[MODRM].index = (INDEX == 0b100) ? -1 : INDEX;
            format.operand[MODRM].base = (BASE == 0b101) ? -1 : BASE;
            break;
        case 0b01100000:
            format.length += 2;
            format.operand[MODRM].scale = (INDEX == 0b100) ? 0 : (1 << SS);
            format.operand[MODRM].index = (INDEX == 0b100) ? -1 : INDEX;
            format.operand[MODRM].base = BASE;
            format.operand[MODRM].displacement = IMM8(opcode, format.length - 1);
            break;
        case 0b10100000:
            format.length += 5;
            format.operand[MODRM].scale = (INDEX == 0b100) ? 0 : (1 << SS);
            format.operand[MODRM].index = (INDEX == 0b100) ? -1 : INDEX;
            format.operand[MODRM].base = BASE;
            format.operand[MODRM].displacement = IMM32(opcode, format.length - 4);
            break;
        default:
            switch (MOD) {
            case 0b00:
                format.operand[MODRM].base = RM;
                break;
            case 0b01:
                format.length += 1;
                format.operand[MODRM].base = RM;
                format.operand[MODRM].displacement = IMM8(opcode, format.length - 1);
                break;
            case 0b10:
                format.length += 4;
                format.operand[MODRM].base = RM;
                format.operand[MODRM].displacement = IMM32(opcode, format.length - 4);
                break;
            case 0b11:
                format.operand[MODRM].reg = true;
                format.operand[MODRM].base = RM;
                break;
            }
            break;
        }
        format.operand[OPREG].reg = true;
        format.operand[OPREG].base = REG;
    }
    else {
        format.operand[MODRM].reg = true;
        format.operand[MODRM].base = 0;
        format.operand[OPREG].reg = true;
        format.operand[OPREG].base = 0;
    }

    if (immediate_size) {
        if (immediate_size < 0)
            immediate_size = format.size;
        switch (immediate_size) {
        case 8:
            format.length += 1;
            format.operand[OPREG].imm = true;
            format.operand[OPREG].displacement = IMM8(opcode, format.length - 1);
            break;
        case 16:
            format.length += 2;
            format.operand[OPREG].imm = true;
            format.operand[OPREG].displacement = IMM16(opcode, format.length - 2);
            break;
        case 32:
            format.length += 4;
            format.operand[OPREG].imm = true;
            format.operand[OPREG].displacement = IMM32(opcode, format.length - 4);
            break;
        }
    }

    return format;
}
//------------------------------------------------------------------------------
std::string x86::Disasm(const Format& format, int operand)
{
    auto hex = [](auto imm) {
        char temp[64];
        unsigned long long value = std::abs((int64_t)imm);
        if (value > 0xFFFF) snprintf(temp, 64, "%s%08llX", imm < 0 ? "-" : "", value);
        else if (value > 0xFF) snprintf(temp, 64, "%s%04llX", imm < 0 ? "-" : "", value);
        else snprintf(temp, 64, "%s%02llX", imm < 0 ? "-" : "", value);
        return std::string(temp);
    };

    std::string disasm;
    disasm += format.instruction;
    for (int i = 0; i < operand; ++i) {
        if (i) disasm += ',';
        disasm += ' ';
        if (format.operand[i].imm) {
            disasm += hex(format.operand[i].displacement);
        }
        else if (format.operand[i].reg) {
            switch (format.size) {
            case 8:     disasm += REG8[format.operand[i].base];   break;
            case 16:    disasm += REG16[format.operand[i].base];  break;
            case 32:    disasm += REG32[format.operand[i].base];  break;
            }
        }
        else {
            switch (format.size) {
            case 8:     disasm += "BYTE PTR"; break;
            case 16:    disasm += "WORD PTR"; break;
            case 32:    disasm += "DWORD PTR"; break;
            }
            disasm += ' ';
            disasm += '[';
            if (format.operand[i].scale > 0) {
                disasm += REG32[format.operand[i].index];
                disasm += '*';
                disasm += std::to_string(format.operand[i].scale);
            }
            if (format.operand[i].base >= 0) {
                if (disasm.back() != '[')
                    disasm += '+';
                disasm += REG32[format.operand[i].base];
            }
            if (format.operand[i].displacement) {
                if (disasm.back() != '[')
                    disasm += '+';
                disasm += hex(format.operand[i].displacement);
            }
            if (disasm.back() == '[')
                disasm += '0';
            disasm += ']';
        }
    }

    return disasm;
}
//------------------------------------------------------------------------------
void x86::Fixup(Format& format)
{
    for (int i = 0; i < 2; ++i) {
        if (format.operand[i].imm) {
            format.operand[i].memory = nullptr;
            format.operand[i].memory += format.operand[i].displacement;
        }
        else if (format.operand[i].reg) {
            if (format.size != 8 || format.operand[i].base < 4) {
                format.operand[i].memory = &regs[format.operand[i].base].l;
            }
            else {
                format.operand[i].memory = &regs[format.operand[i].base - 4].h;
            }
        }
        else {
            format.operand[i].address = 0;
            format.operand[i].address += regs[format.operand[i].index].d * format.operand[i].scale;
            format.operand[i].address += regs[format.operand[i].base].d;
            format.operand[i].address += format.operand[i].displacement;
            format.operand[i].memory = memory + format.operand[i].address;
        }
    }
}
//------------------------------------------------------------------------------
template<typename A, typename B>
void x86::UpdateEFlags(A& DEST, B TEMP)
{
    int bits = sizeof(A) * 8;
    CF = ((DEST ^ TEMP) &  (1 << (bits - 1))) ? 1 : 0;
    PF = ((       TEMP) &  (1              )) ? 1 : 0;
    AF = ((DEST ^ TEMP) &  (1              )) ? 1 : 0;
    ZF = ((       TEMP) == (0              )) ? 1 : 0;
    SF = ((       TEMP) &  (1 << (bits - 1))) ? 1 : 0;
    OF = ((DEST ^ TEMP) &  (1 << (bits - 2))) ? 1 : 0;
    DEST = TEMP;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void x86::ESC()
{
}
//------------------------------------------------------------------------------
void x86::TWO()
{
    (this->*two[opcode[1]])();
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void x86::grp1()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[1][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp2()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[2][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp3()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[3][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp4()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[4][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp5()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[5][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp6()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[6][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp7()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[7][nnn])();
}
//------------------------------------------------------------------------------
void x86::grp8()
{
    int nnn = (opcode[1] >> 3) & 0b111;
    (this->*group[8][nnn])();
}
//------------------------------------------------------------------------------
void x86::___()
{
    Format format;

    BEGIN_OPERATION("UNKNOWN") {
    } END_OPERATION;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void x86::OS()
{
    EIP += 1;

    operand_size_override = true;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void x86::ADC()
{
    Format format;
    switch (opcode[0]) {
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:  format = Decode(1, "ADC", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x14:
    case 0x15:  format = Decode(0, "ADC",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "ADC",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "ADC",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST + SRC + CF);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::ADD()
{
    Format format;
    switch (opcode[0]) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:  format = Decode(1, "ADD", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x04:
    case 0x05:  format = Decode(0, "ADD",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "ADD",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "ADD",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST + SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::AND()
{
    Format format;
    switch (opcode[0]) {
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:  format = Decode(1, "AND", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x24:
    case 0x25:  format = Decode(0, "AND",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "AND",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "AND",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST & SRC);
        CF = 0;
        OF = 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BSF()
{
    Format format = Decode(2, "BSF", 0, 1, 0);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        ZF = 1;
        if (SRC) {
            ZF = 0;
            DEST = __builtin_ctz(SRC);
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BSR()
{
    Format format = Decode(2, "BSR", 0, 1, 0);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        ZF = 1;
        if (SRC) {
            ZF = 0;
            DEST = __builtin_clz(SRC) ^ (sizeof(SRC) * 8 - 1);
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BT()
{
    Format format;
    switch (opcode[1]) {
    case 0xA3:  format = Decode(2, "BT", 0, 1, 0);  break;
    case 0xBA:  format = Decode(2, "BT", 0, 1, -1); break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        CF = (DEST & (1 << SRC)) ? 1 : 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BTC()
{
    Format format;
    switch (opcode[1]) {
    case 0xBA:  format = Decode(2, "BTC", 0, 1, -1);    break;
    case 0xBB:  format = Decode(2, "BTC", 0, 1, 0);     break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        CF = (DEST & (1 << SRC)) ? 1 : 0;
        DEST = (DEST ^ (1 << SRC));
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BTR()
{
    Format format;
    switch (opcode[1]) {
    case 0xB3:  format = Decode(2, "BTR", 0, 1, 0);     break;
    case 0xBA:  format = Decode(2, "BTR", 0, 1, -1);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        CF = (DEST & (1 << SRC)) ? 1 : 0;
        DEST = (DEST & ~(1 << SRC));
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::BTS()
{
    Format format;
    switch (opcode[1]) {
    case 0xAB:  format = Decode(2, "BTS", 0, 1, 0);     break;
    case 0xBA:  format = Decode(2, "BTS", 0, 1, -1);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        CF = (DEST & (1 << SRC)) ? 1 : 0;
        DEST = (DEST | (1 << SRC));
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CALL()
{
    Format format;
    switch (opcode[0]) {
    case 0xE8:  format = Decode(0, "CALL", 0, 1, -1);   break;
    case 0xFF:  format = Decode(1, "CALL", 0, 1, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        Push(EIP);
        if (format.operand[0].imm)
            EIP += format.operand[0].displacement;
        else
            EIP = *(uint32_t*)format.operand[0].memory;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CDQ()
{
    Format format;
    format.size = operand_size_override ? 16 : 32;
    format.length = 1;
    format.instruction = operand_size_override ? "CWD" : "CDQ";

    BEGIN_OPERATION(format.instruction) {
        if (format.size == 16)
            DX = (int16_t)AX < 0 ? 0xFFFF : 0x0000;
        else
            EDX = (int32_t)EAX < 0 ? 0xFFFFFFFF : 0x00000000;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CLC()
{
    Format format;

    BEGIN_OPERATION("CLC") {
        CF = 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CLD()
{
    Format format;

    BEGIN_OPERATION("CLD") {
        DF = 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CMC()
{
    Format format;

    BEGIN_OPERATION("CMC") {
        CF = !CF;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CMP()
{
    Format format;
    switch (opcode[0]) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:  format = Decode(1, "CMP", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x3C:
    case 0x3D:  format = Decode(0, "CMP",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "CMP",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "CMP",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        auto TEMP = DEST;
        UpdateEFlags(TEMP, TEMP - SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CMPSx()
{
    Format format;
    switch (opcode[0]) {
    case 0xA6:  format = Decode(0, "CMPSB", 0, 0, 0);                                   break;
    case 0xA7:  format = Decode(0, operand_size_override ? "CMPSW" : "CMPSD", 0, 1, 0); break;
    }
    format.operand[0].base = REG(EDI);
    format.operand[1].base = REG(ESI);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        auto TEMP = DEST;
        UpdateEFlags(TEMP, TEMP - SRC);
        ESI = DF == 0 ? ESI + sizeof(SRC) : ESI + sizeof(SRC);
        EDI = DF == 0 ? EDI + sizeof(DEST) : EDI + sizeof(DEST);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::CWDE()
{
    Format format;
    format.size = operand_size_override ? 16 : 32;
    format.length = 1;
    format.instruction = operand_size_override ? "CBW" : "CWDE";

    BEGIN_OPERATION(format.instruction) {
        if (format.size == 16)
            AX = (int8_t)AL;
        else
            EAX = (int16_t)AX;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::DEC()
{
    Format format;
    switch (opcode[0]) {
    case 0x48:  format = Decode(0, "DEC", 0,             0b01, 0);  break;
    case 0xFE:
    case 0xFF:  format = Decode(1, "DEC", 0, opcode[0] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST - 1);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::DIV()
{
    Format format;
    switch (opcode[0]) {
    case 0xF6:
    case 0xF7:  format = Decode(1, "DIV", 0, opcode[0] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = DEST / SRC;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::ENTER()
{
    Format format = Decode(0, "ENTER", 0, 0, 16);
    format.length += 1;
    format.operand[1].displacement = IMM8(opcode, 2);

    BEGIN_OPERATION(Disasm(format)) {
        int level = format.operand[1].displacement % 32;
        Push(ESP);
        if (level > 0) {
            uint32_t frame_ptr = ESP;
            for (int i = 1; i < level; ++i) {
                EBP = EBP - 4;
                Push(EBP);
            }
            Push(frame_ptr);
        }
        ESP -= (uint16_t)format.operand[1].displacement;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::IDIV()
{
    Format format;
    switch (opcode[0]) {
    case 0xF6:
    case 0xF7:  format = Decode(1, "IDIV", 0, opcode[0] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        typename std::make_signed_t<std::remove_reference_t<decltype(DEST)>> dest = DEST;
        typename std::make_signed_t<std::remove_reference_t<decltype(SRC)>> src = SRC;
        DEST = dest / src;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::IMUL()
{
    Format format;
    switch (opcode[0]) {
    case 0x0F:  format = Decode(2, "IMUL", 0,             0b01, 0);     break;
    case 0x69:  format = Decode(1, "IMUL", 0,             0b01, -1);    break;
    case 0x6B:  format = Decode(1, "IMUL", 0,             0b01, 8);     break;
    case 0xF6:
    case 0xF7:  format = Decode(1, "IMUL", 0, opcode[0] & 0b01, 0);     break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        typename std::make_signed_t<std::remove_reference_t<decltype(DEST)>> dest = DEST;
        typename std::make_signed_t<std::remove_reference_t<decltype(SRC)>> src = SRC;
        DEST = dest * src;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::INC()
{
    Format format;
    switch (opcode[0]) {
    case 0x40:  format = Decode(0, "INC", 0,             0b01, 0);  break;
    case 0xFE:
    case 0xFF:  format = Decode(1, "INC", 0, opcode[0] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST + 1);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::Jcc()
{
    Format format;
    switch (opcode[0]) {
    case 0x70:  format = Decode(0, "JO", 0, 0, 8);      break;
    case 0x71:  format = Decode(0, "JNO", 0, 0, 8);     break;
    case 0x72:  format = Decode(0, "JC", 0, 0, 8);      break;
    case 0x73:  format = Decode(0, "JNC", 0, 0, 8);     break;
    case 0x74:  format = Decode(0, "JZ", 0, 0, 8);      break;
    case 0x75:  format = Decode(0, "JNZ", 0, 0, 8);     break;
    case 0x76:  format = Decode(0, "JBE", 0, 0, 8);     break;
    case 0x77:  format = Decode(0, "JA", 0, 0, 8);      break;
    case 0x78:  format = Decode(0, "JS", 0, 0, 8);      break;
    case 0x79:  format = Decode(0, "JNS", 0, 0, 8);     break;
    case 0x7A:  format = Decode(0, "JPE", 0, 0, 8);     break;
    case 0x7B:  format = Decode(0, "JPO", 0, 0, 8);     break;
    case 0x7C:  format = Decode(0, "JL", 0, 0, 8);      break;
    case 0x7D:  format = Decode(0, "JGE", 0, 0, 8);     break;
    case 0x7E:  format = Decode(0, "JLE", 0, 0, 8);     break;
    case 0x7F:  format = Decode(0, "JG", 0, 0, 8);      break;
    case 0xE3:  format = Decode(0, operand_size_override ? "JCXZ" : "JECXZ", 0, 0, 8);  break;
    case 0x0F:
        switch (opcode[1]) {
        case 0x80:  format = Decode(0, "JO", 0, 1, -1);     break;
        case 0x81:  format = Decode(0, "JNO", 0, 1, -1);    break;
        case 0x82:  format = Decode(0, "JC", 0, 1, -1);     break;
        case 0x83:  format = Decode(0, "JNC", 0, 1, -1);    break;
        case 0x84:  format = Decode(0, "JZ", 0, 1, -1);     break;
        case 0x85:  format = Decode(0, "JNZ", 0, 1, -1);    break;
        case 0x86:  format = Decode(0, "JBE", 0, 1, -1);    break;
        case 0x87:  format = Decode(0, "JA", 0, 1, -1);     break;
        case 0x88:  format = Decode(0, "JS", 0, 1, -1);     break;
        case 0x89:  format = Decode(0, "JNS", 0, 1, -1);    break;
        case 0x8A:  format = Decode(0, "JPE", 0, 1, -1);    break;
        case 0x8B:  format = Decode(0, "JPO", 0, 1, -1);    break;
        case 0x8C:  format = Decode(0, "JL", 0, 1, -1);     break;
        case 0x8D:  format = Decode(0, "JGE", 0, 1, -1);    break;
        case 0x8E:  format = Decode(0, "JLE", 0, 1, -1);    break;
        case 0x8F:  format = Decode(0, "JG", 0, 1, -1);     break;
        }
        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        // TODO
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::JMP()
{
    Format format;
    switch (opcode[0]) {
    case 0xE9:  format = Decode(0, "JMP", 0, 1, -1);   break;
    case 0xEB:  format = Decode(0, "JMP", 0, 0, 8);    break;
    case 0xFF:  format = Decode(1, "JMP", 0, 1, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        if (format.operand[0].imm)
            EIP += format.operand[0].displacement;
        else
            EIP = *(uint32_t*)format.operand[0].memory;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::LAHF()
{
    Format format;

    BEGIN_OPERATION("LAHF") {
        AH = FLAGS;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::LEA()
{
    Format format = Decode(1, "LEA", 0, 0, 0);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = format.operand[0].address;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::LEAVE()
{
    Format format;

    BEGIN_OPERATION("LEAVE") {
        ESP = EBP;
        EBP = Pop();
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::LODSx()
{
    Format format;
    switch (opcode[0]) {
    case 0xAC:  format = Decode(0, "LODSB", 0, 0, 0);                                   break;
    case 0xAD:  format = Decode(0, operand_size_override ? "LODSW" : "LODSD", 0, 1, 0); break;
    }
    format.operand[0].reg = true;
    format.operand[0].base = REG(EAX);
    format.operand[1].base = REG(ESI);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = SRC;
        ESI = DF == 0 ? ESI + sizeof(SRC) : ESI + sizeof(SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::LOOP()
{
    Format format;
    switch (opcode[0]) {
    case 0xE0:  format = Decode(0, "LOOPNZ", 0, 1, 8);  break;
    case 0xE1:  format = Decode(0, "LOOPZ", 0, 1, 8);   break;
    case 0xE2:  format = Decode(0, "LOOP", 0, 1, 8);    break;
    }

    BEGIN_OPERATION(Disasm(format)) {
        uint32_t CountReg = (format.size == 16) ? CX : ECX;
        if (CountReg) {
            ECX = ECX - 1;
            bool BranchCond = true;
            switch (opcode[0]) {
                case 0xE0:  BranchCond = (ZF == 0); break;
                case 0xE1:  BranchCond = (ZF != 0); break;
            }
            if (BranchCond) {
                EIP += format.operand[1].displacement;
            }
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::MOV()
{
    Format format;
    switch (opcode[0]) {
    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:  format = Decode(1, "MOV", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0xB0:
    case 0xB1:
    case 0xB2:
    case 0xB3:
    case 0xB4:
    case 0xB5:
    case 0xB6:
    case 0xB7:  format = Decode(0, "MOV", 0, 0, -1);
                format.operand[0].reg = true;
                format.operand[0].base = opcode[0] & 0b111; break;
    case 0xB8:
    case 0xB9:
    case 0xBA:
    case 0xBB:
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:  format = Decode(0, "MOV", 0, 1, -1);
                format.operand[0].reg = true;
                format.operand[0].base = opcode[0] & 0b111; break;
    case 0xC6:  format = Decode(1, "MOV", 0, 0, -1);        break;
    case 0xC7:  format = Decode(1, "MOV", 0, 1, -1);        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = SRC;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::MOVSx()
{
    Format format;
    switch (opcode[0]) {
    case 0xA4:  format = Decode(0, "MOVSB", 0, 0, 0);                                   break;
    case 0xA5:  format = Decode(0, operand_size_override ? "MOVSW" : "MOVSD", 0, 1, 0); break;
    }
    format.operand[0].base = REG(EDI);
    format.operand[1].base = REG(ESI);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = SRC;
        ESI = DF == 0 ? ESI + sizeof(SRC) : ESI + sizeof(SRC);
        EDI = DF == 0 ? EDI + sizeof(DEST) : EDI + sizeof(DEST);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::MOVSX()
{
    Format format;
    switch (opcode[1]) {
    case 0xBE:
    case 0xBF:  format = Decode(2, "MOVSX", 0, opcode[1] & 0b01, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        switch (format.size) {
        case 8:
            (uint16_t&)DEST = SRC;
            break;
        case 16:
            (uint32_t&)DEST = SRC;
            break;
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::MOVZX()
{
    Format format;
    switch (opcode[1]) {
    case 0xB6:
    case 0xB7:  format = Decode(2, "MOVZX", 0, opcode[1] & 0b01, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        switch (format.size) {
        case 8:
            (uint16_t&)DEST = SRC;
            break;
        case 16:
            (uint32_t&)DEST = SRC;
            break;
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::MUL()
{
    Format format;
    switch (opcode[0]) {
    case 0xF6:
    case 0xF7:  format = Decode(1, "MUL", 0, opcode[0] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = DEST / SRC;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::NEG()
{
    Format format;
    switch (opcode[1]) {
    case 0xF6:
    case 0xF7:  format = Decode(1, "NEG", 0, opcode[1] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        CF = (DEST == 0) ? 0 : 1;
        DEST = -DEST;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::NOP()
{
    Format format;

    BEGIN_OPERATION("NOP") {
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::NOT()
{
    Format format;
    switch (opcode[1]) {
    case 0xF6:
    case 0xF7:  format = Decode(1, "NOT", 0, opcode[1] & 0b01, 0);  break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = !DEST;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::OR()
{
    Format format;
    switch (opcode[0]) {
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:  format = Decode(1, "OR", opcode[0] & 0b10, opcode[0] & 0b01, 0);    break;
    case 0x0C:
    case 0x0D:  format = Decode(0, "OR",             0b00, opcode[0] & 0b01, -1);   break;
    case 0x80:
    case 0x81:  format = Decode(1, "OR",             0b00, opcode[0] & 0b01, -1);   break;
    case 0x83:  format = Decode(1, "OR",             0b00, opcode[0] & 0b01, 8);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST | SRC);
        CF = 0;
        OF = 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::POP()
{
    Format format;
    switch (opcode[0]) {
    case 0x58:  format = Decode(1, "POP", 0, 1, 0); break;
    case 0x8F:  format = Decode(1, "POP", 0, 1, 0); break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = Pop();
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::POPAD()
{
    Format format = Decode(0, "POPAD", 0, 1, 0);

    BEGIN_OPERATION(Disasm(format)) {
        EDI = Pop();
        ESI = Pop();
        EBP = Pop();
        Pop();
        EBX = Pop();
        EDX = Pop();
        ECX = Pop();
        EAX = Pop();
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::POPFD()
{
    Format format = Decode(0, "POPFD", 0, 1, 0);

    BEGIN_OPERATION(Disasm(format)) {
        EFLAGS = Pop();
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::PUSH()
{
    Format format;
    switch (opcode[0]) {
    case 0x50:  format = Decode(1, "PUSH", 0, 1, 0);    break;
    case 0x68:  format = Decode(0, "PUSH", 0, 1, -1);   break;
    case 0x6A:  format = Decode(0, "PUSH", 0, 1, 8);    break;
    case 0xFF:  format = Decode(1, "PUSH", 0, 1, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        Push(DEST);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::PUSHAD()
{
    Format format = Decode(0, "PUSHAD", 0, 1, 0);

    BEGIN_OPERATION(Disasm(format)) {
        auto Temp = ESP;
        Push(EAX);
        Push(ECX);
        Push(EDX);
        Push(EBX);
        Push(Temp);
        Push(EBP);
        Push(ESI);
        Push(EDI);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::PUSHFD()
{
    Format format = Decode(0, "PUSHFD", 0, 1, 0);

    BEGIN_OPERATION(Disasm(format)) {
        Push(EFLAGS);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::Rxx()
{
    Format format;
    switch (opcode[0]) {
    case 0xC0:
    case 0xC1:
        switch (opcode[1] >> 3 & 7) {
        case 0: format = Decode(1, "ROL", 0, opcode[0] & 0b01, 8);  break;
        case 1: format = Decode(1, "ROR", 0, opcode[0] & 0b01, 8);  break;
        case 2: format = Decode(1, "RCL", 0, opcode[0] & 0b01, 8);  break;
        case 3: format = Decode(1, "RCR", 0, opcode[0] & 0b01, 8);  break;
        }
        break;
    case 0xD0:
    case 0xD1:
        switch (opcode[1] >> 3 & 7) {
        case 0: format = Decode(1, "ROL", 0, opcode[0] & 0b01, 0);  break;
        case 1: format = Decode(1, "ROR", 0, opcode[0] & 0b01, 0);  break;
        case 2: format = Decode(1, "RCL", 0, opcode[0] & 0b01, 0);  break;
        case 3: format = Decode(1, "RCR", 0, opcode[0] & 0b01, 0);  break;
        }
        format.operand[1].imm = true;
        format.operand[1].displacement = 1;
        break;
    case 0xD2:
    case 0xD3:
        switch (opcode[1] >> 3 & 7) {
        case 0: format = Decode(1, "ROL", 0, opcode[0] & 0b01, 0);  break;
        case 1: format = Decode(1, "ROR", 0, opcode[0] & 0b01, 0);  break;
        case 2: format = Decode(1, "RCL", 0, opcode[0] & 0b01, 0);  break;
        case 3: format = Decode(1, "RCR", 0, opcode[0] & 0b01, 0);  break;
        }
        format.operand[1].reg = true;
        format.operand[1].base = REG(ECX);
        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        switch (opcode[1] >> 3 & 7) {
        case 0:
            if (sizeof(DEST) == 1)  DEST = __builtin_rotateleft8(DEST, SRC);
            if (sizeof(DEST) == 2)  DEST = __builtin_rotateleft16(DEST, SRC);
            if (sizeof(DEST) == 4)  DEST = __builtin_rotateleft32(DEST, SRC);
            break;
        case 1:
            if (sizeof(DEST) == 1)  DEST = __builtin_rotateright8(DEST, SRC);
            if (sizeof(DEST) == 2)  DEST = __builtin_rotateright16(DEST, SRC);
            if (sizeof(DEST) == 4)  DEST = __builtin_rotateright32(DEST, SRC);
            break;
        case 2: // TODO
            if (sizeof(DEST) == 1)  DEST = __builtin_rotateleft8(DEST, SRC);
            if (sizeof(DEST) == 2)  DEST = __builtin_rotateleft16(DEST, SRC);
            if (sizeof(DEST) == 4)  DEST = __builtin_rotateleft32(DEST, SRC);
            break;
        case 3: // TODO
            if (sizeof(DEST) == 1)  DEST = __builtin_rotateright8(DEST, SRC);
            if (sizeof(DEST) == 2)  DEST = __builtin_rotateright16(DEST, SRC);
            if (sizeof(DEST) == 4)  DEST = __builtin_rotateright32(DEST, SRC);
            break;
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::REP()
{
    EIP += 1;

    repeat_string_operation = true;
}
//------------------------------------------------------------------------------
void x86::RET()
{
    Format format;
    switch (opcode[0]) {
    case 0xC2:  format = Decode(0, "RET", 0, 0, 16);    break;
    case 0xC3:  format = Decode(0, "RET", 0, 0, 0);     break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        EIP = Pop();
        ESP = ESP + format.operand[0].displacement;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SAHF()
{
    Format format;

    BEGIN_OPERATION("SAHF") {
        FLAGS = AH;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::Sxx()
{
    Format format;
    switch (opcode[0]) {
    case 0xC0:
    case 0xC1:
        switch (opcode[1] >> 3 & 7) {
        case 4: format = Decode(1, "SHL", 0, opcode[0] & 0b01, 8);  break;
        case 5: format = Decode(1, "SHR", 0, opcode[0] & 0b01, 8);  break;
        case 6: format = Decode(1, "SAL", 0, opcode[0] & 0b01, 8);  break;
        case 7: format = Decode(1, "SAR", 0, opcode[0] & 0b01, 8);  break;
        }
        break;
    case 0xD0:
    case 0xD1:
        switch (opcode[1] >> 3 & 7) {
        case 4: format = Decode(1, "SHL", 0, opcode[0] & 0b01, 0);  break;
        case 5: format = Decode(1, "SHR", 0, opcode[0] & 0b01, 0);  break;
        case 6: format = Decode(1, "SAL", 0, opcode[0] & 0b01, 0);  break;
        case 7: format = Decode(1, "SAR", 0, opcode[0] & 0b01, 0);  break;
        }
        format.operand[1].imm = true;
        format.operand[1].displacement = 1;
        break;
    case 0xD2:
    case 0xD3:
        switch (opcode[1] >> 3 & 7) {
        case 4: format = Decode(1, "SHL", 0, opcode[0] & 0b01, 0);  break;
        case 5: format = Decode(1, "SHR", 0, opcode[0] & 0b01, 0);  break;
        case 6: format = Decode(1, "SAL", 0, opcode[0] & 0b01, 0);  break;
        case 7: format = Decode(1, "SAR", 0, opcode[0] & 0b01, 0);  break;
        }
        format.operand[1].reg = true;
        format.operand[1].base = REG(ECX);
        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        typename std::make_signed_t<std::remove_reference_t<decltype(DEST)>> dest = DEST;
        switch (opcode[1] >> 3 & 7) {
        case 4: DEST = DEST << SRC; break;
        case 5: DEST = DEST >> SRC; break;
        case 6: DEST = dest << SRC; break;
        case 7: DEST = dest >> SRC; break;
        }
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SBB()
{
    Format format;
    switch (opcode[0]) {
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:  format = Decode(1, "SBB", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x1C:
    case 0x1D:  format = Decode(0, "SBB",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "SBB",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "SBB",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST - (SRC + CF));
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SCASx()
{
    Format format;
    switch (opcode[0]) {
    case 0xAE:  format = Decode(0, "SCASB", 0, 0, 0);                                   break;
    case 0xAF:  format = Decode(0, operand_size_override ? "SCASW" : "SCASD", 0, 1, 0); break;
    }
    format.operand[0].base = REG(EDI);
    format.operand[1].base = REG(EAX);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        auto TEMP = DEST;
        UpdateEFlags(TEMP, SRC - TEMP);
        EDI = DF == 0 ? EDI + sizeof(DEST) : EDI + sizeof(DEST);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SETcc()
{
    Format format;
    switch (opcode[1]) {
    case 0x90:  format = Decode(2, "SETO", 0, 0, 0);    break;
    case 0x91:  format = Decode(2, "SETNO", 0, 0, 0);   break;
    case 0x92:  format = Decode(2, "SETC", 0, 0, 0);    break;
    case 0x93:  format = Decode(2, "SETNC", 0, 0, 0);   break;
    case 0x94:  format = Decode(2, "SETZ", 0, 0, 0);    break;
    case 0x95:  format = Decode(2, "SETNZ", 0, 0, 0);   break;
    case 0x96:  format = Decode(2, "SETBE", 0, 0, 0);   break;
    case 0x97:  format = Decode(2, "SETA", 0, 0, 0);    break;
    case 0x98:  format = Decode(2, "SETS", 0, 0, 0);    break;
    case 0x99:  format = Decode(2, "SETNS", 0, 0, 0);   break;
    case 0x9A:  format = Decode(2, "SETPE", 0, 0, 0);   break;
    case 0x9B:  format = Decode(2, "SETPO", 0, 0, 0);   break;
    case 0x9C:  format = Decode(2, "SETL", 0, 0, 0);    break;
    case 0x9D:  format = Decode(2, "SETGE", 0, 0, 0);   break;
    case 0x9E:  format = Decode(2, "SETLE", 0, 0, 0);   break;
    case 0x9F:  format = Decode(2, "SETG", 0, 0, 0);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        // TODO
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SHxD()
{
    Format format;
    switch (opcode[1]) {
    case 0xA4:
        format = Decode(2, "SHLD", 0, 1, 0);
        format.length += 1;
        format.operand[2].imm = true;
        format.operand[2].displacement = IMM8(opcode, 3);
        break;
    case 0xA5:
        format = Decode(2, "SHLD", 0, 1, 0);
        format.operand[2].reg = true;
        format.operand[2].base = REG(ECX);
        break;
    case 0xAC:
        format = Decode(2, "SHRD", 0, 1, 0);
        format.length += 1;
        format.operand[2].imm = true;
        format.operand[2].displacement = IMM8(opcode, 3);
        break;
    case 0xAD:
        format = Decode(2, "SHRD", 0, 1, 0);
        format.operand[2].reg = true;
        format.operand[2].base = REG(ECX);
        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format, 3)) {
        // TODO
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::STC()
{
    Format format;

    BEGIN_OPERATION("STC") {
        CF = 1;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::STD()
{
    Format format;

    BEGIN_OPERATION("STD") {
        DF = 1;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::STOSx()
{
    Format format;
    switch (opcode[0]) {
    case 0xAA:  format = Decode(0, "STOSB", 0, 0, 0);                                   break;
    case 0xAB:  format = Decode(0, operand_size_override ? "STOSW" : "STOSD", 0, 1, 0); break;
    }
    format.operand[0].reg = true;
    format.operand[0].base = REG(EDI);
    format.operand[1].base = REG(EAX);
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        DEST = SRC;
        EDI = DF == 0 ? EDI + sizeof(SRC) : EDI + sizeof(SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::SUB()
{
    Format format;
    switch (opcode[0]) {
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:  format = Decode(1, "SUB", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x2C:
    case 0x2D:  format = Decode(0, "SUB",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "SUB",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "SUB",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST - SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::TEST()
{
    Format format;
    switch (opcode[0]) {
    case 0x84:
    case 0x85:  format = Decode(1, "TEST", 0, opcode[0] & 0b01, 0);     break;
    case 0xA8:
    case 0xA9:  format = Decode(0, "TEST", 0, opcode[0] & 0b01, -1);    break;
    case 0xF6:
    case 0xF7:  format = Decode(1, "TEST", 0, opcode[0] & 0b01, -1);    break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        auto TEMP = DEST;
        UpdateEFlags(TEMP, TEMP & SRC);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::XCHG()
{
    Format format;
    switch (opcode[0]) {
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
        format = Decode(0, "XCHG", 0, 1, 0);
        format.operand[0].reg = true;
        format.operand[0].base = REG(EAX);
        format.operand[1].reg = true;
        format.operand[1].base = (opcode[0] & 0b111);
        break;
    case 0x86:
    case 0x87:
        format = Decode(1, "XCHG", 0, opcode[0] & 0b01, 0);
        break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        auto TEMP = DEST;
        DEST = SRC;
        SRC = TEMP;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::XLAT()
{
    Format format;

    BEGIN_OPERATION("XLAT") {
        AL = *(memory + EBX + AL);
    } END_OPERATION;
}
//------------------------------------------------------------------------------
void x86::XOR()
{
    Format format;
    switch (opcode[0]) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:  format = Decode(1, "XOR", opcode[0] & 0b10, opcode[0] & 0b01, 0);   break;
    case 0x34:
    case 0x35:  format = Decode(0, "XOR",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x80:
    case 0x81:  format = Decode(1, "XOR",             0b00, opcode[0] & 0b01, -1);  break;
    case 0x83:  format = Decode(1, "XOR",             0b00, opcode[0] & 0b01, 8);   break;
    }
    Fixup(format);

    BEGIN_OPERATION(Disasm(format)) {
        UpdateEFlags(DEST, DEST ^ SRC);
        CF = 0;
        OF = 0;
    } END_OPERATION;
}
//------------------------------------------------------------------------------
