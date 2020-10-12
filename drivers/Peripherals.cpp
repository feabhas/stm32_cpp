// -----------------------------------------------------------------------------
// Peripherals.cpp
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------

#include "Peripherals.h"
#include "Memory_map.h"
#include "Register.h"

#include <cstdint>
using std::uint32_t;

namespace STM32F407
{
  void enable(AHB1_device device)
  {
    Register<32> RCC_AHB1_enable{ AHB1_base + 0x3830 };
    RCC_AHB1_enable[static_cast<unsigned int>(device)] = 1;
  }

  void enable(APB1_device device)
  {
    Register<32> RCC_APB1_enable{ AHB1_base + 0x3840 };
    RCC_APB1_enable[static_cast<unsigned int>(device)] = 1;
  }

  void enable(APB2_device device)
  {
    Register<32> RCC_APB2_enable{ AHB1_base + 0x3844 };
    RCC_APB2_enable[static_cast<unsigned int>(device)] = 1;
  }

} // namespace STM32F407
