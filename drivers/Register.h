// -----------------------------------------------------------------------------
// Register.h
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

#ifndef REGISTER_H_
#define REGISTER_H_

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace STM32F407
{
  // ------------------------------------------------------------------------
  // Dispatch tags
  //
  struct read_only
  {
  };
  struct write_only
  {
  };
  struct read_write : public read_only, public write_only
  {
  };

  // SFINAE aliases
  // We can define the type returned by std::enable_if as bool; then we can
  // write code as follows: template <typename T, is_some_trait<T> = true> void
  // func() { }
  //
  // The aliases give the following results for our tag types:
  //
  //                 read_only  write_only  read_write
  //               ---------------------------------------
  // is_read_only  |     T          F           T
  // is_write_only |     F          T           T
  // is_read_write |     F          F           T
  //
  template<typename U>
  using is_read_only =
    typename std::enable_if<std::is_base_of<read_only, U>::value, bool>::type;

  template<typename U>
  using is_write_only =
    typename std::enable_if<std::is_base_of<write_only, U>::value, bool>::type;

  template<typename U>
  using is_read_write =
    typename std::enable_if<std::is_base_of<read_write, U>::value, bool>::type;

  // ------------------------------------------------------------------------
  // Traits
  // These traits are used to select an appropriately-sized underlying type
  // for accessing the hardware.  The pointer size cannot be fixed, and must
  // exactly match the actual hardware register size, otherwise we could end
  // up with over-writing issues, or reads inadvertantly clearing bits in
  // other registers.
  //
  template<unsigned int sz>
  struct Register_traits
  {
  };

  template<>
  struct Register_traits<8>
  {
    using internal_type = std::uint8_t;
  };

  template<>
  struct Register_traits<16>
  {
    using internal_type = std::uint16_t;
  };

  template<>
  struct Register_traits<24>
  {
    using internal_type = std::uint32_t;
  };

  template<>
  struct Register_traits<32>
  {
    using internal_type = std::uint32_t;
  };

  template<>
  struct Register_traits<64>
  {
    using internal_type = std::uint64_t;
  };

  // ------------------------------------------------------------------------
  //
  template<std::size_t sz, typename Register_Ty = read_write>
  class Register {
  public:
    using reg_type = typename Register_traits<sz>::internal_type;

  private:
    // bit_proxy represents one of the
    // individual bits in the hardware
    // register.
    //
    class bit_proxy {
    public:
      // Returns the current value of the
      // associated bit
      //
      // returns    1 if the bit is set
      // returns    0 is the bit is not set
      //
      template<typename T = Register_Ty, is_read_only<T> = true>
      operator Register::reg_type() const
      {
        return (*(owner->raw_ptr) & (static_cast<reg_type>(1U) << bit_num)) ?
                 1 :
                 0;
      }

      // Sets / clears the associated bit in the
      // parent register.
      // 0   Clears the bit
      // >0  Sets the bit
      //
      template<typename T = Register_Ty, is_write_only<T> = true>
      bit_proxy& operator=(Register::reg_type val)
      {
        if (val == 0) {
          *(owner->raw_ptr) &= ~(static_cast<reg_type>(1U) << bit_num);
        }
        else {
          *(owner->raw_ptr) |= (static_cast<reg_type>(1U) << bit_num);
        }
        return *this;
      }

      // Assigning one bit_proxy to another doesn't
      // copy the state of the bit_proxy, it copies
      // the value of the actual bit in the register.
      // So:
      // reg[0] = 1;
      // reg[0] = reg[1];
      // will copy the value of reg[0] (1) to reg[1]
      //
      bit_proxy& operator=(const bit_proxy& rhs)
      {
        *this = static_cast<Register::reg_type>(rhs);
        return *this;
      }

    protected:
      // Constructor
      //
      bit_proxy(Register<sz, Register_Ty>* reg, unsigned int num) :
        owner{ reg }, bit_num{ num }
      {
      }

    private:
      friend class Register<sz, Register_Ty>; // The parent must be able to
                                              // construct.
      Register<sz, Register_Ty>*
                   owner;   // The Register object that created this proxy.
      unsigned int bit_num; // The bit in the actual Register.
    };

  public:
    explicit Register(std::uint32_t address) :
      raw_ptr{ reinterpret_cast<reg_type*>(address) }
    {
    }

    template<typename T = Register_Ty, is_write_only<T> = true>
    void operator=(reg_type bit_mask)
    {
      *raw_ptr = bit_mask;
    }

    // Convert to unsigned integer.
    //
    // returns    The value held in the register
    //             as an unsigned integer the size
    //             of the register
    //
    template<typename T = Register_Ty, is_read_only<T> = true>
    operator reg_type() const
    {
      return *raw_ptr;
    }

    // Or-assignment operator
    //
    // Any bits set to one in bit_mask will be set to 1 on
    // the actual hardware.
    //
    template<typename T = Register_Ty, is_read_write<T> = true>
    void operator|=(std::uint32_t bit_mask)
    {
      *raw_ptr |= bit_mask;
    }

    // And-assignment operator
    //
    // Any bits set to one in bit_mask will be bitwise AND-ed
    // with the bits in the actual hardware.
    //
    template<typename T = Register_Ty, is_read_write<T> = true>
    void operator&=(reg_type bit_mask)
    {
      *raw_ptr &= bit_mask;
    }

    // C++ doesn't support a 'bit' type for accessing a single
    // bit in a word, so we simulate it with a 'proxy' for each
    // bit.  The []operator is used to create a bit_proxy.
    //
    // returns    A bit_proxy that represents the selected bit
    //             in the register.
    //
    bit_proxy operator[](unsigned int index)
    {
      return bit_proxy{ this, index };
    }

    // For const, or read_only Registers the value of the Register
    // cannot be modified through a proxy; so cut out the middle-
    // man and simply return the value of the selected bit (as if
    // via a bit_proxy)
    //
    // returns    The value of the selected bit.
    //
    template<typename T = Register_Ty, is_read_only<T> = true>
    unsigned int operator[](unsigned int index) const
    {
      return ((*raw_ptr & (1 << index)) != 0 ? 1 : 0);
    }

  private:
    volatile reg_type* raw_ptr;
  };

} // namespace STM32F407

#endif // REGISTER_H_
