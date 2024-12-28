#pragma once

#include <string>
#include <functional>
#include <unordered_map>

namespace wcvm {

  /* List of all instructions 
   * mov  [dst] [src]     -- Will move « src » into « dst »
   * add  [dst] [src]     -- Will add « src » to « dst » 
   * sub  [dst] [src]     -- Will subtract « dst » by « src »
   * mul  [dst] [src]     -- Will multiply « dst » by « src »
   * div  [dst] [src]     -- Will divide « dst » by « src »
   * jmp  [lbl]           -- Will jump
   * je   [lbl]           -- Will jump if it's equal
   * jne  [lbl]           -- Will jump if it's not equal
   * jl   [lbl]           -- Will jump if it's lesser
   * jg   [lbl]           -- Will jump if it's grather
   * jle  [lbl]           -- Will jump if it's lesser or equal 
   * jge  [lbl]           -- Will jump if it's grather or equal 
   * call [addr]          -- Will push the current address, jump at « addr », execute the code, and recome back to the last address
   * ret                  -- Will return the current memory address (and place it at the top of the stack)
   * cmp  [a] [b] [addr]  -- Will compare « a » to « b ». Results in « addr »
   * halt                 -- Will stop the CPU
   */

}