// -----------------------------------------------------------------------------
// Peripherals.h
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

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

namespace STM32F407
{
  enum class AHB1_device {
    gpio_A = 0,
    gpio_B = 1,
    gpio_C = 2,
    gpio_D = 3,
    gpio_E = 4,
    gpio_F = 5,
    gpio_G = 6,
    gpio_H = 7,
    gpio_I = 8
  };

  enum class APB1_device {
    timer_2  = 0,
    timer_3  = 1,
    timer_4  = 2,
    timer_5  = 3,
    timer_6  = 4,
    timer_7  = 5,
    timer_12 = 6,
    timer_13 = 7,
    timer_14 = 8,
    spi_2    = 14,
    spi_3    = 15,
    usart_2  = 17,
    usart_3  = 18,
    usart_4  = 19,
    usart_5  = 20,
    i2c_1    = 21,
    i2c_2    = 22,
    i2c_3    = 23,
  };

  enum class APB2_device {
    timer_1  = 0,
    timer_8  = 1,
    usart_1  = 4,
    usart_6  = 5,
    adc_1    = 8,
    adc_2    = 9,
    adc_3    = 10,
    timer_9  = 16,
    timer_10 = 17,
    timer_11 = 18,
  };

  // Enable a particular device
  //
  void enable(AHB1_device device);
  void enable(APB1_device device);
  void enable(APB2_device device);

} // namespace STM32F407

#endif // PERIPHERALS_H_
