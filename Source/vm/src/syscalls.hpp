#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "vm.hpp"

namespace wcvm {
  void vm::init_syscalls() {
    syscalls[0x0000] = [this]() {
      // write HANDLE STRING
      word handle = read_word();
      std::string string;
      byte b = read_byte();
      
      while (b) {
        string.push_back(b);
        b = read_byte();
      }

      io.handles[handle].write(string);
    };

    syscalls[0x0001] = [this]() {
      // read HANDLE LEN ADDRESS
      word handle = read_word();
      qword len = read_qword();
      qword add = read_dword();

      byte *buff = new byte[len];
      io.handles[handle].read(buff, len);

      for (qword i = 0; i < len; ++i) {
        memory[add+i] = buff[i];
      }

      delete[] buff;
    };

    syscalls[0x0002] = [this]() {};

  }

}