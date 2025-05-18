```
 _____               __                 
/ _  / ___ _ __ ___ / _\ ___ __ _ _ __  
\// / / _ \ '__/ _ \\ \ / __/ _` | '_ \ 
 / //\  __/ | | (_) |\ \ (_| (_| | | | |
/____/\___|_|  \___/\__/\___\__,_|_| |_|

```

C based single threaded port scanner using raw sockets

## Features
- IP validation using regex
- Host pinging before scannning
- Shows opened ports in real-time

## Usage

```console
./zeroscan <ip_address> <start_port> <end_port>
```

### Example

```console
./zeroscan 192.168.1.1 20-500
```

### Print help menu

```console
./zeroscan -h
```

## Compiling

Use `Makefile` for compilation
```console
make
```

To remove .o files:

```console
make clean
```

## Notes
- This port scanner is single threaded
- Scans only TCP ports, no UDP
- Made specifically for linux (POSIX API)
- Good enough for basic scanning, for more larger scans threaded or asynchronous features would be better





