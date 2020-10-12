# $1 elf image to use
if [ $# -lt 1 ]
  then
    echo ".elf image file not supplied"
    exit 1
fi
qemu-system-arm -S -M feabhas-wms -s -d unimp,guest_errors -semihosting -kernel  $1 --trace events=trace-event-list