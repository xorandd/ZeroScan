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

## ⌨️ Usage

```console
zeroscan <ip_address> -p <start_port> <end_port> -t <num_threads> --long
zeroscan <ip_address> -p <port> -- retries 3
```

### Example

```console
zeroscan 127.0.0.1 -p 1 1000
zeroscan 127.0.0.1 -p 1 1000  --long --no-ping
zeroscan 127.0.0.1 -p 3306 --retries 2
zeroscan 127.0.0.1 -p 5000 --threads 200
```

### Print help menu

```console
./zeroscan -h
./zeroscan --help
```

## 📥 Installation

### 1. Compiling from source

Use `Makefile` for compilation
```
git clone https://github.com/xorandd/ZeroScan
cd ZeroScan
make
```
### 2. Debian / Kali

Download `.deb` package from  [releases](https://github.com/xorandd/ZeroScan/releases)

Integrity Checksum example

```
$ echo '68ef6f1afc0e29b90981f983b006e587e63ecf6bedacd338cdc66e6c000dc246' ./zeroscan_1.4.0.deb | sha256sum -c
./zeroscan_1.3.1.deb: OK
```

To install run `dpkg -i <downloaded file>` eg
```
dpkg -i ./zeroscan_1.4.0.deb
```

## 📝 Notes
- Scans only TCP ports, no UDP
- Made specifically for linux (POSIX API)
- Default number of threads is set to 200, however if you wish to change use `--threads` option
or run scan with -t NUM, --threads NUM flag
- It is recommended to use `--retries` option during default scanning (without `--long` option) to reduce chance of failed ports.
Default scanning scans only 1 time, it may skip some ports. Scanning with `--long NUM` increases reliability 
