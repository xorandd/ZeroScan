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
- Scans top 1000 ports if no ports are included
- Support multi-threading with partial asynchronous feature
- Supports rescanning failed ports up to 3 times
- Allows to run nmap with following options
  - sS
  - sC
  - sV
  - A
  - T<0-5> 

## ❗ Requirements

- Nmap if you want to use `--nmap` option, or install using ZeroScan when it prompts so, supported linux distributions:
  - Arch
  - Debian
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
