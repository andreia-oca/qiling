from qiling import *

def my_sandbox(path, rootfs):
    ql = Qiling(path, rootfs)
    ql.run()

if __name__ == "__main__":
    my_sandbox(["rootfs/x86_windows/bin/x86_hello.exe"], "rootfs/x86_windows")
