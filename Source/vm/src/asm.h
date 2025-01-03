#ifndef WCVM_INSTRUCTIONS_H
#define WCVM_INSTRUCTIONS_H

// Arithmetic and data movement instructions
#define nop 0x00
#define mov 0x01,
#define add 0x02,
#define sub 0x03,
#define mul 0x04,
#define div 0x05,
#define mod 0x06,

// Jump instructions
#define jmp 0x07
#define je  0x08
#define jne 0x09
#define jl  0x0A
#define jg  0x0B
#define jle 0x0C
#define jge 0x0D

// Call and return instructions
#define call 0x0E,
#define ret  0x0F

// Comparison instructions
#define cmp  0x10,

// Load and stack instructions
#define lea   0x11,
#define pushq 0x12,
#define popq  0x13,

// Word instructions
#define movw 0x14,
#define addw 0x15,
#define subw 0x16,
#define mulw 0x17,
#define divw 0x18,
#define modw 0x19,

// Dword instructions
#define movd 0x1A,
#define addd 0x1B,
#define subd 0x1C,
#define muld 0x1D,
#define divd 0x1E,
#define modd 0x1F,

// System call
#define syscall 0x20,

// Qword instructions
#define movq 0x21,
#define addq 0x22,
#define subq 0x23,
#define mulq 0x24,
#define divq 0x25,
#define modq 0x26,

// Comparison by size
#define cmpw 0x27,
#define cmpd 0x28,
#define cmpq 0x29,

// Halt instruction
#define halt 0xFF

#endif // WCVM_INSTRUCTIONS_H
