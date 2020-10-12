# $1 elf image to use
if [ $# -lt 1 ]
  then
    echo ".elf image file not supplied"
    exit 1
fi
# -M feabhas-wms : Select the emulated machine by name
# -d             : To make QEMU inform the user about problems [various options]
# -semihosting   : Enable semihosting mode
# -kernel        : executable image to load 
# ~/qemu/arm-softmmu/qemu-system-arm -M feabhas -d unimp,guest_errors -semihosting -kernel $1
qemu-system-arm -M feabhas -d unimp,guest_errors -semihosting -kernel $1
