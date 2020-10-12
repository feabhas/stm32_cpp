# $1 machine to use
# $2 elf image to use
if [ $# -lt 2 ]
  then
    echo "Not enough arguments supplied, two arguments require: machine and .elf image"
    exit 1
fi
qemu-system-arm -S -M $1 -s -d unimp,guest_errors -semihosting -kernel  $2 -monitor tcp::55555,server --trace events=trace-event-list
