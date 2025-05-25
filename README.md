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
- Support multi-threading with partial asynchronous features (`-t`, `--threads` flag to set number of threads)
- Supports rescanning failed ports up to 3 times (`--long` flag)
- Allows to scan target multiple times, depends on user's input (`--long` flag)

## ⌨️ Usage

```console
zeroscan <ip_address> -p <start_port> <end_port> -t <num_threads> --long
zeroscan <ip_address> -p <port> -- retries 3
```

### Example

```console
zeroscan 127.0.0.1 -p 1 1000
zeroscan 127.0.0.1 -p 3306 --retries 2
zeroscan 127.0.0.1 -p 5000 --long --threads 200
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
- Scans only TCP ports, no UDP
- Made specifically for linux (POSIX API)
- Default number of threads is set to 500, however if you wish to change, either change it in code and compile
or run scan with -t NUM, --threads NUM flag
- It is recommended to use `--retries` flag during default scanning (without `--long` flag) to reduce chance of failed ports.
Default scanning scans only 1 time, it may skip some ports. Scanning with `--long NUM` increases reliability 
