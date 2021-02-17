from qiling import *

def my_sandbox(path, rootfs):
    ql = Qiling(path, rootfs)
    ql.run()

if __name__ == "__main__":
    my_sandbox(["rootfs/arm64_linux/bin/arm64_hello"], "rootfs/arm64_linux")
