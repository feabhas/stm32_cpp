# $1 machine to use
# $2 elf image to use
if [ $# -lt 2 ]
  then
    echo "Not enough arguments supplied, two arguments require: machine and .elf image"
    exit 1
fi
# QEMU Invocation
# see https://www.qemu.org/docs/master/system/invocation.html
# -S              : Do not start CPU at startup (you must type ‘c’ in the monitor).
# -M <name>       : Select the emulated machine by name
#    feabhas-wms  : feabhas qemu target with WMS pin output naming
# -s              : Shorthand for -gdb tcp::1234, i.e. open a gdbserver on TCP port 1234
# -d <list>       : To make QEMU inform the user about problems [various options]
#    unimp        :
# -semihosting    : Enable semihosting mode
# -kernel <file>  : executable image to load 
# -nographic      : disable graphical output so that QEMU is a simple command line application.
# -serial <dev>   : Redirect the virtual serial port to host character device dev
# tcp:[host]:port[,server][,nowait][,nodelay][,reconnect=seconds]
# tcp::7777,server,nowait,nodelay
qemu-system-arm -S -M S1 -s -d unimp -semihosting -kernel $2 -serial tcp::7777,server,nowait,nodelay

