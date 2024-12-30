#pragma once

#include <stack>
#include <limits>
#include <string>
#include <functional>
#include <unordered_map>

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

    byte memory[std::numeric_limits<u_int32_t>::max()];
    std::unordered_map<byte, std::function<void()>> ftable;
    std::unordered_map<std::string, u_int32_t> extfunctions;

    void    init_table();
    byte    read_byte();
    word    read_word();
    dword   read_dword();
    void    init(); // Will parse the memory to find external functions.

  public:
  };
}

/*
  byte op;
  op = read_byte();

  if (op == 0x00) {
    ..
  } else if (op == 0x01)
  {
    ...
  }

  op 0x56

*/