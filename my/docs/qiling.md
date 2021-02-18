# Qiling notes
## Install Prerequisites
```
sudo apt-get update
sudo apt-get upgrade
sudo apt install python3-pip git cmake build-essential libtool-bin python3-dev automake flex bison libglib2.0-dev libpixman-1-dev clang python3-setuptools llvm
pip3 install qiling
```

To try out fuzzing on Qiling, install AFLplusplus:
```
git clone https://github.com/AFLplusplus/AFLplusplus.git AFLplusplus
cd ./AFLplusplus
make
cd unicorn_mode
./build_unicorn_support.sh
```

## Tutorials
[VIRTUAL LAB: Qiling Framework: Build a Fuzzer Based on a 1day Bug - Lau Kai Jern](https://youtu.be/e3_T3KLh2NU)

Use QEMu and try to modify it? 
No, QEMU is emulating to many things that an IoT device does not need (device drivers, keyboard, mouse, display card, sound card).

Unicorn only emulates only the CPU (it stripped down the bloatware from QEMU). Unicorn is only emulating CPU instructions.

Qiling framework is based on Unicorn. 
It can emulates OS and firmware binary(MIPS, ARM).
Allows fine-grained instrumentation (at instruction level, basic block, syscall)
Can replace an entire syscall with a handler.


## Demos

**Note** Test on Ubuntu 20.10.

### Emulate ARM binary

Script `my_hello_windows.py`:

```
from qiling import *

def my_sandbox(path, rootfs):
    ql = Qiling(path, rootfs)
    ql.run()

if __name__ == "__main__":
    my_sandbox(["rootfs/arm64_linux/bin/arm64_hello"], "rootfs/arm64_linux")

```

Command:

```
python3 my_hello_arm_linux.py
```

### Emulate Windows EXE

Script `my_hello_windows.py`:

```
from qiling import *

def my_sandbox(path, rootfs):
    ql = Qiling(path, rootfs)
    ql.run()

if __name__ == "__main__":
    my_sandbox(["rootfs/x86_windows/bin/x86_hello.exe"], "rootfs/x86_windows")

```

Command:

```
python3 my_hello_windows.py
```

[SOLVED] For now this is raising an error. I have submitted an [issue](https://github.com/qilingframework/qiling/issues/699)

**Note:** Use the script `examples/scripts/dllscollector.bat` on Windows to collect the dlls and registry files.

Details on Windows examples:
- `crackme_x86_windows_auto.py` is hijacking `stdin` and feeds the correct password without user intervention.
- `crackme_x86_windows.py` is brute-forcing the password.
- `crackme_x86_windows_unpatch.py` simulates the program unpatched (i.e. awaits for a password from the user and verifies it).
- `my_patched_windows.py` always display *Congratulations* no matter the password typed (patches the binary with no-ops over the password verification instructions).

### Emulate Linux x86 ELF



### Fuzzing with Qiling Unicornafl

Fuzzing a dummy linux_x86 binary.

```
git clone https://github.com/AFLplusplus/AFLplusplus.git
cd ./AFLplusplus
make binary-only
```

Run these commands as **root** on the host machine, otherwcdise AFL will get mad:
```
echo core >/proc/sys/kernel/core_pattern
cd /sys/devices/system/cpu
echo performance | tee cpu*/cpufreq/scaling_governor
```

To test open a `python3` console and type the following commands:
```
import qiling
import unicornafl
```

Finally, to start the fuzzing process run:
```
AFL_AUTORESUME=1 AFL_PATH="$(realpath ./AFLplusplus)" PATH="$AFL_PATH:$PATH" afl-fuzz -i afl_inputs -o afl_outputs -U -- python3 ./fuzz_x8664_linux.py @@
```
The inputs that generated crashes can be found at `afl_outputs/default/crashes/`

To DEBUG the binary one can run the script **only once** with a specific input:
```
python3 fuzz_x8664_linux.py ./afl_outputs/default/crashes/id\:000001\,sig\:06\,src\:000000\,time\:8822\,op\:havoc\,rep\:4 
```
