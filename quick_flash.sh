#! /bin/bash


if [ "$#" -ne 3 ]; then
  echo "usage: ./quick_flash.sh <port> <proj_path> <proj_name>"
  exit 1
fi

# activate virt env first!
source .venv/bin/activate

# e.g. /dev/cu.usbserial-1110
PORT=$1
PROJ_PATH=$2
PROJ_NAME=$3

# run flash 
python3 ./components/esptool_py/esptool/esptool.py --chip esp8266 --port $PORT --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 $PROJ_PATH/build/bootloader/bootloader.bin 0x10000 $PROJ_PATH/build/$PROJ_NAME.bin 0x8000 $PROJ_PATH/build/partitions_singleapp.bin
