#pragma once

#include <stack>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "list.hpp"

namespace wcvm {
  typedef u_int8_t      byte;
  typedef u_int16_t     word;
  typedef u_int32_t     dword;

  class vm {
  private:
    u_int32_t             ip;
    byte                  cf; // Compare Flag
    std::stack<u_int32_t> st;
    bool                  halt = false;
    std::ifstream         disk;

    byte memory[std::numeric_limits<u_int32_t>::max()];
    std::unordered_map<byte, std::function<void()>> ftable;
    std::unordered_map<word, std::function<void(byte *, word)>> syscalls;

    void    init_table();
    void    init_syscalls();
    byte    read_byte();
    word    read_word();
    dword   read_dword();

  public:

    void init() {
      std::cout << "Wide Cinnamon Virtual Machine (WCVM)\n"
                   "------------------------------------\n";
      
      init_table();
      init_syscalls();
    }
  };
}
