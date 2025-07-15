```
 _____               __                 
/ _  / ___ _ __ ___ / _\ ___ __ _ _ __  
\// / / _ \ '__/ _ \\ \ / __/ _` | '_ \ 
 / //\  __/ | | (_) |\ \ (_| (_| | | | |
/____/\___|_|  \___/\__/\___\__,_|_| |_|

```

Port scanner written in C

## ✨ Features
- Shows opened ports in real-time
- Host pinging before scannning
- Scans top 1000 ports if no ports are included (top_1000_ports.h)
- Doesn't ping target if not needed (`--no-ping`)
- Support multi-threading with partial asynchronous feature (`-t`, `--threads` option to set number of threads)
- Supports rescanning failed ports up to 3 times (`--long` option)
- Allows to scan target multiple times, depends on user's input (`--retries` option)
- Allows to run nmap with following options (`--nmap <OPTIONS>`):
  - sS
  - sC
  - sV
  - A
  - T<0-5> 

## ❗ Requirements

If you want to use `--nmap` option you need to install [nmap](https://nmap.org/)

## 📥 Installation

### 1. Compiling from source

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
$ echo '6e25efebc8257fd0efa9e166b1fe9992d3e1d848fa592b8ed577898e441aaa46' ./zeroscan_1.5.1.deb | sha256sum -c
./zeroscan_1.5.1.deb: OK
```

To install run `dpkg -i <downloaded file>`

```
dpkg -i ./zeroscan_1.4.0.deb
```

## 📝 Notes
- Scans only TCP ports, no UDP
- Default number of threads is set to 200, however if you wish to change use `--threads`/`-t` option
- It is recommended to use `--retries` option during default scanning (without `--long` option) to reduce chance of false failed ports which may be open.
Scans target 1 time by default but it may skip some ports. Scanning with `--long NUM` increases reliability 
