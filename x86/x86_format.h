#pragma once

#include <stdint.h>
#include <functional>
#include <string>

struct x86_instruction;
struct x86_format
{
    struct Format
    {
        struct Operand
        {
            enum Type { NOP, ADR, IMM, REG };
            Type type = NOP;

            int scale;
            int index;
            int base;
            int32_t displacement;

            uint64_t address;
            uint8_t* memory;
        };
        int size = 0;
        int length = 1;
        const char* instruction = "";
        Operand operand[3];

        void (*operation)(x86_instruction&, const Format&, void*, const void*) = nullptr;
    };
};
