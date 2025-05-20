```
 _____               __                 
/ _  / ___ _ __ ___ / _\ ___ __ _ _ __  
\// / / _ \ '__/ _ \\ \ / __/ _` | '_ \ 
 / //\  __/ | | (_) |\ \ (_| (_| | | | |
/____/\___|_|  \___/\__/\___\__,_|_| |_|

```

C based port scanner

## ✨ Features
- IP validation using regex
- Host pinging before scannning
- Shows opened ports in real-time
- Support multi-threading

## ⌨️ Usage

```console
./zeroscan <ip_address> <start_port> <end_port>
```

### Example

```console
./zeroscan 192.168.1.1 20 500
```

### Print help menu

```console
./zeroscan -h
```

## ✨ Installation

### 1. Compiling from source

Use `Makefile` for compilation
```
git clone https://github.com/xorandd/ZeroScan
cd ZeroScan
make
```
### 2. Debian / Kali

Download `.deb` package from  [releases](https://github.com/xorandd/ZeroScan/releases)

To install package run `dpkg -i <downloaded_file>`

To uninstall run `dpkg -r zeroscan`

## 📝 Notes
- This port scanner is single threaded
- Scans only TCP ports, no UDP
- Made specifically for linux (POSIX API)
- Good enough for basic scanning, for more larger scans threaded or asynchronous features would be better





