#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "vm.hpp"
#include "trim.hpp"
#include "dylibs.hpp"

namespace wcvm {
  std::pair<int, std::string> compile_line(const std::string &line) {
    size_t del = line.find(':');
    if (del == std::string::npos) 
        throw std::runtime_error("Bad config file. Missing ':' delimiter.\nLine: " + line);

    // Extract and trim the key and value
    std::string first = line.substr(0, del);
    std::string second = line.substr(del + 1);

    // Trim whitespace (implement or use std::trim if available)
    first = trim(first);
    second = trim(second);

    // Convert the first part to an integer
    int key = 0;
    try {
      key = std::stoi(first);
    } catch (const std::invalid_argument &) {
      throw std::runtime_error("Invalid key (not an integer): " + first);
    } catch (const std::out_of_range &) {
      throw std::runtime_error("Key out of range: " + first);
    }

    return {key, second};
  }



  void vm::_syscalls_check_files() {
    if (!std::filesystem::exists(config.env + "/libs/")) throw std::runtime_error(config.env + "/libs/: No such directory.\n");
    if (!std::filesystem::exists(config.env + "/libs/cfg")) throw std::runtime_error(config.env + "/libs/cfg: No such file.\n");
    if (!std::filesystem::exists(config.env + "/libs/" + get_lib_name("lib"))) throw std::runtime_error(config.env + "/libs/lib.??: No such file.\n");
  }



  void vm::_syscalls_load_functions() {
    std::string lib_path = config.env + "/libs/";
    std::ifstream cfg(config.env + get_lib_name("libs/lib"));
    if (!cfg) throw std::runtime_error(config.env + "/libs/cfg: Unable to open file");

    std::string line;
    while (std::getline(cfg, line, ';')) {
      auto out = compile_line(line);
      syscalls[out.first] = load_external_function(lib_path, out.second);
    }

    cfg.close();
  }



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
    
    _syscalls_check_files();
    _syscalls_load_functions();
  }

}
