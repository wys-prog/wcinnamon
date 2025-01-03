#include <bits/stdc++.h>
#include "asm.h"

int main(int argc, const char** argv) {
  std::vector<uint8_t> ins = {  
    syscall, 0x00, 0x00,                                          // puts syscall
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C,               // uint64_t _len = 12;
    'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\n',  // char *_msg = "Hello world\n"
    0xFF,
  };

  std::ofstream out("boot");

  for (const auto i : ins) {
    char buff[1] = {(char)i};
    out.write(buff, 1);
  }

  out.close();

  return 0;
}