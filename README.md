```
 _____               __                 
/ _  / ___ _ __ ___ / _\ ___ __ _ _ __  
\// / / _ \ '__/ _ \\ \ / __/ _` | '_ \ 
 / //\  __/ | | (_) |\ \ (_| (_| | | | |
/____/\___|_|  \___/\__/\___\__,_|_| |_|

```

C based port scanner

## ✨ Features
- Host pinging before scannning
- Scans top 1000 ports if no need to ping before scan (top_1000_ports.h)
- Shows opened ports in real-time
- Support multi-threading with partial asynchronous feature (`-t`, `--threads` option to set number of threads)
- Supports rescanning failed ports up to 3 times (`--long` option)
- Allows to scan target multiple times, depends on user's input (`--long` option)
- Doesn't ping machine you scanning if not needed
- Allows to run nmap with following options:
  - sS
  - sC
  - sV
  - A
  - T<0-5> 

## ❗ Requirements

If you want to use `--nmap` option you need to install [nmap](https://nmap.org/)

## 📥 Installation

### 1. Compiling from source

Use `Makefile` for compilation
```
git clone https://github.com/xorandd/ZeroScan
cd ZeroScan
make
```
Move compiled binary to `/usr/local/bin` if you want it to run anywhere in terminal. 

### 2. Debian / Kali

Download `.deb` package from  [releases](https://github.com/xorandd/ZeroScan/releases)

Integrity Checksum example

```
$ echo 'e8c7737b070a071caf0092ec0cb261f29d299dbe4992d83d99ac5b62e0a2d850' ./zeroscan_1.5.0.deb | sha256sum -c
./zeroscan_1.5.0.deb: OK
```

To install run `dpkg -i <downloaded file>` eg
```
dpkg -i ./zeroscan_1.4.0.deb
```

## 📝 Notes
- Scans only TCP ports, no UDP
- Made specifically for linux (POSIX API)
- Default number of threads is set to 200, however if you wish to change use `--threads`/`-t` option
- It is recommended to use `--retries` option during default scanning (without `--long` option) to reduce chance of failed ports.
Default scanning scans only 1 time, it may skip some ports. Scanning with `--long NUM` increases reliability 
