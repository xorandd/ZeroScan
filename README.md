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
- Scans top 1000 ports if no ports are included (list of top ports is in the [top_1000_ports.h](src/top_1000_ports.h))
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

- Nmap if you want to use `--nmap` option, or install using ZeroScan when it prompts so, supported linux distributions:
  - Arch Linux / Manjaro
  - Debian / Ubuntu / Mint
  - Fedora  

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

To install run `dpkg -i <downloaded file>`

```
dpkg -i ./zeroscan.deb
```
