
all: crack_me_argv crack_me

crack_me: crack_me.c
	gcc crack_me.c -Wall -g -o ../rootfs/x8664_linux/bin/crack_me

crack_me_argv: crack_me_argv.c
	gcc crack_me_argv.c -Wall -g -o ../rootfs/x8664_linux/bin/crack_me_argv

clean:
	rm -rf *.o crack_me crack_me_argv