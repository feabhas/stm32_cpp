# $1 elf image to use
if [ $# -lt 1 ]
  then
    echo ".elf image file not supplied"
    exit 1
fi
# -S             : Do not start CPU at startup (you must type ‘c’ in the monitor).
# -M feabhas     : Select the emulated machine by name
# -s             : Shorthand for -gdb tcp::1234, i.e. open a gdbserver on TCP port 1234
# -d             : To make QEMU inform the user about problems [various options]
# -semihosting   : Enable semihosting mode
# -kernel        : executable image to load 
qemu-system-arm -S -M feabhas -s -d unimp,guest_errors -semihosting -kernel $1
