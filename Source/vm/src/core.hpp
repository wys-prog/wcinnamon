#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "vm.hpp"
#include "list.hpp"

namespace wcvm {
  /* List of all instructions 
   * mov    [dst] [src]       -- Will move « src » into « dst »
   * add    [dst] [src]       -- Will add « src » to « dst » 
   * sub    [dst] [src]       -- Will subtract « dst » by « src »
   * mul    [dst] [src]       -- Will multiply « dst » by « src »
   * div    [dst] [src]       -- Will divide « dst » by « src »
   * jmp    [lbl]             -- Will jump
   * je     [lbl]             -- Will jump if it's equal
   * jne    [lbl]             -- Will jump if it's not equal
   * jl     [lbl]             -- Will jump if it's lesser
   * jg     [lbl]             -- Will jump if it's grather
   * jle    [lbl]             -- Will jump if it's lesser or equal 
   * jge    [lbl]             -- Will jump if it's grather or equal 
   * call   [addr]            -- Will push the current address, jump at « addr », execute the code, and recome back to the last address
   * ret                      -- Will return the current memory address (and place it at the top of the stack)
   * cmp    [a] [b] [addr]    -- Will compare « a » to « b ». Results in « addr »
   * lea    [dst], [addr]     -- Will load « addr » at « dst »
   * push   [src]             -- Will push « src » to the stack
   * pop    [dst]             -- Will pop the top of the stack into « dst »
   * movw   [dst] [src]       -- Will move « src » into « dst ». Operands are words.
   * addw   [dst] [src]       -- Will add « src » to « dst ». Operands are words.
   * subw   [dst] [src]       -- Will subtract « dst » by « src ». Operands are words.
   * mulw   [dst] [src]       -- Will multiply « dst » by « src ». Operands are words.
   * divw   [dst] [src]       -- Will divide « dst » by « src ». Operands are words.
   * movd   [dst] [src]       -- Will move « src » into « dst ». Operands are dword.
   * addd   [dst] [src]       -- Will add « src » to « dst ». Operands are dwords.
   * subd   [dst] [src]       -- Will subtract « dst » by « src ». Operands are dwords.
   * muld   [dst] [src]       -- Will multiply « dst » by « src ». Operands are dwords.
   * divd   [dst] [src]       -- Will divide « dst » by « src ». Operands are dwords.
   * syscall [n°]             -- Will call a system componant.
   * halt                     -- Will stop the CPU
   */

  byte vm::read_byte() { return memory[ip++]; }

  word vm::read_word() {
    word w = (memory[ip] << 8) | memory[ip+1];
    ip += 2;
  }

  dword vm::read_dword() {
    dword d = (memory[ip] << 24) | (memory[ip+1] << 16) | (memory[ip+2] << 8) | memory[ip+3];
    ip += 4;
  }

  void vm::init_table() {

    ftable[0x00] = [this]() { return; }; // « nop » instruction.

    // mov 
    ftable[0x01] = [this]() { memory[read_byte()] = read_byte(); }; 

    // add
    ftable[0x02] = [this]() { memory[read_byte()] += read_byte(); };

    // sub
    ftable[0x03] = [this]() { memory[read_byte()] -= read_byte(); };

    // mul
    ftable[0x04] = [this]() { memory[read_byte()] *= read_byte(); };

    // div
    ftable[0x05] = [this]() { memory[read_byte()] /= read_byte(); };

    // mod
    ftable[0x06] = [this]() {
      memory[ip+1] = memory[ip+1] % memory[ip+2];
      ip += 2;
    };

    // jmp
    ftable[0x07] = [this]() { ip = memory[read_dword()]; };

    ftable[0x08] = [this]() {
      ip = (cf == 0) ? memory[read_dword()] : ip; // don't use « ++ip ». If cf is not 0, this will increments ip, so in 
      ip += 1;                                    // each case the ip will be memory[ip+1]. And we dont wont that.
    };

    ftable[0x09] = [this]() {
      ip = (cf == 0) ? ip : memory[read_dword()];
      ip += 1;
    };

    ftable[0x0A] = [this]() {
      ip = (cf == 1) ? memory[read_dword()] : ip;
      ip += 1;
    };

    ftable[0x0B] = [this]() {
      ip = (cf == 2) ? memory[read_dword()] : ip;
      ip += 1;
    };

    ftable[0x0C] = [this]() {
      ip = (cf == 0) ? ip : memory[read_dword()];
      ip = (cf == 1) ? memory[read_dword()] : ip;
      ip += 1;
    };

    ftable[0x0D] = [this]() {
      ip = (cf == 0) ? ip : memory[read_dword()];
      ip = (cf == 2) ? memory[read_dword()] : ip;
      ip += 1;
    };

    ftable[0x0E] = [this]() {
      st.push(ip);
      ip = read_dword();
    };

    ftable[0x0F] = [this]() {
      if (st.empty()) {
        ip = 0x00000000;
      } else {
        ip = st.top();
        st.pop();
      }
    };

    ftable[0x10] = [this]() {
      byte a = read_byte(), b = read_byte();
      dword addr = read_dword();

      if (a == b) cf = 0;
      else if (a > b) cf = 2;
      else cf = 1;
    };

    // lea, push, pop, halt

    ftable[0x11] = [this]() {
      dword src = read_dword();
      dword dst = read_dword();

      memory[dst] = memory[src];
    };

    ftable[0x12] = [this]() { st.push(read_dword()); };

    ftable[0x13] = [this]() {
      dword dst = read_dword();

      if (!st.empty()) {
        dst = st.top();
        st.pop();
      } else {
        dst = 0x00000000;
      }
    };

    ftable[0x14] = [this]() { memory[read_word()] = read_word(); };

    ftable[0x15] = [this]() { memory[read_word()] += read_word(); };

    ftable[0x16] = [this]() { memory[read_word()] -= read_word(); };

    ftable[0x17] = [this]() { memory[read_word()] *= read_word(); };

    ftable[0x18] = [this]() { memory[read_word()] /= read_word(); };

    ftable[0x19] = [this]() { 
      word a = read_word(), b = read_word();
      memory[a] = a % b;
    };

    ftable[0x1A] = [this]() { memory[read_dword()] = read_dword(); };

    ftable[0x1B] = [this]() { memory[read_dword()] += read_dword(); };

    ftable[0x1C] = [this]() { memory[read_dword()] -= read_dword(); };

    ftable[0x1D] = [this]() { memory[read_dword()] *= read_dword(); };

    ftable[0x1E] = [this]() { memory[read_dword()] /= read_dword(); };

    ftable[0x1F] = [this]() {
      dword a = read_dword(), b = read_dword();
      memory[a] = a % b;
    };

    // syscall /args... 0x21
    ftable[0x20] = [this]() {
      list<byte> mylist(8);
      byte b = read_byte();
      
      while (!b == 0x21) {
        mylist.push(b);
      }
    };

    ftable[0x21] = [this](){};

    ftable[0xFF] = [this]() { halt = false; };
  }

}