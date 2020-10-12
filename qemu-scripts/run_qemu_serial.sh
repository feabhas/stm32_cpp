# $1 machine to use
# $2 elf image to use
if [ $# -lt 2 ]
  then
    echo "Not enough arguments supplied, two arguments require: machine and .elf image"
    exit 1
fi
# QEMU Invocation
# see https://www.qemu.org/docs/master/system/invocation.html
# -M <name>       : Select the emulated machine by name
#    feabhas      : feabhas qemu target with LED pin output naming
#    feabhas-wms  : feabhas qemu target with WMS pin output naming
# -d <list>       : To make QEMU inform the user about problems [various options]
#    unimp        :
# -semihosting    : Enable semihosting mode
# -kernel <file>  : executable image to load 
# -nographic      : disable graphical output so that QEMU is a simple command line application.
# -serial <dev>   : Redirect the virtual serial port to host character device dev
# tcp:[host]:port[,server][,nowait][,nodelay][,reconnect=seconds]
# tcp::7777,server,nodelay
qemu-system-arm -M $1 -d unimp -semihosting -kernel  $2 -serial tcp::7777,server,nodelay

