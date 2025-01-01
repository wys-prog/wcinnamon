#pragma once

#include <stdio.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "vm.hpp"

namespace wcvm {
  void vm::init_syscalls() {
    syscalls[0x0000] = [this]() {
      qword string_beg = st.top(); st.pop();
      qword i = 0;
      std::string str;

      while (memory[string_beg+i]) {
        str += memory[string_beg+i++];
      }

      puts(str.c_str());
    };
  }

}