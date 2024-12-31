#pragma once

#define MEMORY_MAX 4294967295

#include <stack>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>

namespace wcvm {
  typedef uint8_t      byte;
  typedef uint16_t     word;
  typedef uint32_t     dword;

  class vm {
  private:
    u_int32_t ip;
    byte cf; // Compare Flag
    std::stack<uint32_t> st; // Stack
    bool halt = false;
    std::string env;
    byte memory[MEMORY_MAX];
    std::unordered_map<byte, std::function<void()>> ftable;
    std::unordered_map<word, std::function<void(byte *, word)>> syscalls;
  
    void  init_table();
    void  init_syscalls();
    void  init_disk();
    byte  read_byte();
    word  read_word();
    dword read_dword();

  public:

    void init() {
      std::cout << "------------------------------------\n"
                   "Wide Cinnamon Virtual Machine (WCVM)\n"
                   "Memory:  " << sizeof(memory) << " bytes\n"   
                   "Runtime: Wys - WCVM:RT\n"
                   "Runtime Environnement: " << env <<
                   "------------------------------------\n";
      
      init_table();
      init_syscalls();
      init_disk();
    }
  };
}
