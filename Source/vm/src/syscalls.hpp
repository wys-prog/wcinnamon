#pragma once

#include <stdio.h>
#include <wchar.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "vm.hpp"

namespace wcvm {
  void vm::init_syscalls() {
    // int print(const char *_ptr);
    syscalls[0x0000] = [this]() {
      qword ptr = read_qword();
      std::string buff;

      while (memory[ptr]) buff += (char)memory[ptr++]; 

      std::cout << buff << std::flush;
      st.push(0x0000000000000000);
    };
  }

}
