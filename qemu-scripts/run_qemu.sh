# $1 machine to use
# $2 elf image to use
if [ $# -lt 2 ]
  then
    echo "Not enough arguments supplied, two arguments require: machine and .elf image"
    exit 1
fi
# -M feabhas     : Select the emulated machine by name
# -d             : To make QEMU inform the user about problems [various options]
# -semihosting   : Enable semihosting mode
# -kernel        : executable image to load 
qemu-system-arm -M $1 -d unimp,guest_errors -semihosting -kernel $2
