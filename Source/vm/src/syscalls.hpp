#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "vm.hpp"

namespace wcvm {
  void vm::init_syscalls() {
    // int print(const char *_ptr);
    syscalls[0x0000] = [this]() {
      qword len = read_qword();
      std::string buff;
      
      for (qword i = 0; i < len; i++) {
        buff += read_byte();
      }

      std::cout << buff << std::flush;
    };

    // int load(uint64_t _count, const void *_beg)
    syscalls[0x0001] = [this]() {
      qword _count = read_qword();
      qword _beg   = read_qword(); 

      std::ifstream file(config.env + "boot");

      int add = 0;
      for (qword i = 0; i < _count; i++) {
        char buff[512] = {0};
        file.read(buff, 512);

        write((const byte*)buff, 512, _beg+add);

        add += 512;
      }

      file.close();
    };
  }

}
