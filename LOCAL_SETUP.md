## local setup notes

- activate py env with `source espenv/bin/activate`
- set $IDF_PATH = this directory

- if for some reason the docker image is lost, reinstall these on an x64 ubtuntu
container:

```bash
apt update && apt upgrade -y

apt install -y \
    git \
    make \
    gcc \
    g++ \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    python3-venv \
    wget \
    curl \
    flex \
    bison \
    gperf \
    ncurses-dev \
    libncurses5-dev \
    libncursesw5-dev \
    libssl-dev \
    libffi-dev \
    libtool \
    pkg-config \
    gettext \
    unzip
```

- install requirements.txt in the venv, but make sure to downgrade setup tools with
```bash
python -m pip install setuptools==80.0.0
```
since there are some deprecation issues.

### cleaning notes

if encountering compile issues, always first check that artifacts from other build environments
have been cleaned. (`.o` and `.d` files). delete them with

```bash
find . -name '*.d' -delete
```

### env vars

```bash
export IDF_PATH=/home/dev/ESP8266_RTOS_SDK
export PYTHON=$(pwd)/espenv/bin/python
export PATH=$PATH:/opt/xtensa-lx106-elf/bin
```


### flash command example

```
To flash all build output, run 'make flash' or:
python /home/dev/ESP8266_RTOS_SDK/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/cu.usbserial-1110 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 /home/dev/ESP8266_RTOS_SDK/examples/get-started/hello_world/build/bootloader/bootloader.bin 0x10000 /home/dev/ESP8266_RTOS_SDK/examples/get-started/hello_world/build/hello-world.bin 0x8000 /home/dev/ESP8266_RTOS_SDK/examples/get-started/hello_world/build/partitions_singleapp.bin
```

### reading serial output

the *lower* baud rate of 74880 applies for this MCU, e.g. use
```bash
picocom -b 74880 /dev/cu.usbserial-1110
```
