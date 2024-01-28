Original repository [here](https://github.com/jcdubois/uCOS-II)

## original README.md ##

µCOS for Linux

This is a µCOS port for Linux.

There is a project example in EvalBoards/linux/linux32/GNU/OS/

To build it:

	cd EvalBoards/linux/linux32/GNU/OS/
	make

This produces an OS.elf file that you can run.

## my notes

(these notes need to be reviewed and updated)

virtualbox Ubuntu (also tested OK on WSL2 Ubuntu 20.04)
```
sudo apt update
sudo apt-get install build-essential libc6-dev-i386

cd uCOS-II/EvalBoards/linux/linux32/GNU/OS/
make && ./OS.elf	
```

Application now implements a simple traffic light simulation. Output is printed to console.
