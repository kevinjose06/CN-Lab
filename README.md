# CN Lab - Computer Networks Programs

This repository contains a collection of C-based socket programming exercises developed for the Computer Networks laboratory course PCCSL507 under the KTU 2024 scheme. The programs demonstrate core networking concepts such as TCP communication, UDP messaging, concurrent server design, file transfer, matrix analysis, abbreviation translation, and packet capture.

The projects are designed for Linux or Unix-like environments and are intended to be compiled with GCC.

## Project Overview

The repository includes the following client-server applications and networking utilities:

| File(s) | Description | Protocol | Port |
| --- | --- | --- | --- |
| `chat-server.c`, `chat-client.c` | Multi-user TCP chat application | TCP | 5000 |
| `concurrent-server.c`, `concurrent-client.c` | Concurrent UDP time server/client | UDP | 5000 |
| `Connection-server.c`, `Connection-client.c` | Basic TCP message exchange | TCP | 8080 |
| `file-server.c`, `file-client.c` | Concurrent file server and client | TCP | 5000 |
| `Matrix-server.c`, `Matrix-client.c` | Matrix type classification over TCP | TCP | 8080 |
| `String-server.c`, `String-client.c` | Informal-to-formal English translation using UDP | UDP | 8080 |
| `packet.c` | Raw socket TCP packet sniffer | Raw IP/TCP | N/A |

## Features Covered

- TCP stream sockets for reliable client-server communication
- UDP datagram-based communication for lightweight request/response models
- Concurrent server handling through `fork()` and `pthread`
- File transfer from server to client
- Matrix classification logic for triangular and diagonal matrices
- Text processing using abbreviation replacement
- Packet capture using raw sockets

## Program Details

### 1. Chat Application

- `chat-server.c` accepts multiple client connections and broadcasts messages to all connected clients.
- `chat-client.c` connects to the chat server, receives incoming messages, and allows users to send text over the terminal.
- The application uses `pthread` for receiving messages asynchronously.

### 2. Concurrent Time Server

- `concurrent-server.c` listens for UDP requests and spawns a thread for each incoming request.
- `concurrent-client.c` sends a request to the server and prints the returned system time.
- This demonstrates UDP communication and multi-threaded service handling.

### 3. Basic Connection Program

- `Connection-server.c` waits for a client connection and prints the message it receives.
- `Connection-client.c` sends a message string to the server.
- This is a simple introductory TCP example.

### 4. File Transfer Server

- `file-server.c` accepts a requested filename from the client.
- If the file exists, the server reads and sends contents to the client.
- If not, it sends a not-found message.
- The server also sends its process ID (PID) to the client for display.

### 5. Matrix Classification

- `Matrix-client.c` reads the order of a square matrix and its elements from the user.
- The client sends the matrix to the server.
- `Matrix-server.c` checks whether the matrix is diagonal, upper triangular, lower triangular, or none.
- The result is returned to the client and displayed.

### 6. Informal English Translator

- `String-client.c` sends a sentence containing abbreviations such as `idc`, `atm`, or `tbh`.
- `String-server.c` replaces known abbreviations with formal English equivalents.
- The translated text is sent back and displayed.

### 7. Packet Sniffer

- `packet.c` creates a raw TCP socket and captures packets from the network interface.
- It extracts the source and destination IP addresses and port numbers.
- This is a low-level networking example and requires elevated privileges on most Linux systems.

## Compilation

Compile each program individually using GCC. Example commands:

```bash
gcc -o chat-server chat-server.c -pthread
gcc -o chat-client chat-client.c -pthread

gcc -o concurrent-server concurrent-server.c -pthread
gcc -o concurrent-client concurrent-client.c

gcc -o Connection-server Connection-server.c
gcc -o Connection-client Connection-client.c

gcc -o file-server file-server.c
gcc -o file-client file-client.c

gcc -o Matrix-server Matrix-server.c
gcc -o Matrix-client Matrix-client.c

gcc -o String-server String-server.c
gcc -o String-client String-client.c

gcc -o packet packet.c
```

## Running the Programs

### TCP Chat

```bash
./chat-server
./chat-client
```

Then type messages in the client terminal. Use `exit` to close the connection.

### UDP Time Server

```bash
./concurrent-server
./concurrent-client
```

The client sends a `TIME` request and receives the server's system time.

### Basic TCP Message Exchange

```bash
./Connection-server
./Connection-client
```

The client sends a message and the server displays it.

### File Transfer

```bash
./file-server
./file-client
```

When prompted, enter a filename that exists in the server environment.

### Matrix Analysis

```bash
./Matrix-server
./Matrix-client
```

Enter the matrix order and matrix values, then view the classification result.

### Informal Text Translator

```bash
./String-server
./String-client
```

Enter a sentence using common shorthand abbreviations to see it converted into formal English.

### Packet Capture

```bash
sudo ./packet
```

This may require root privileges because raw sockets are used.

## Notes

- These programs are intended for educational and laboratory use.
- Port numbers are hardcoded in the source files and must match between client and server.
- Some programs use raw sockets and therefore require Linux privileges.
- The code is intentionally simple and demonstrates networking fundamentals rather than production-grade application design.

## Suggested Learning Order

1. Start with the basic TCP connection programs.
2. Move to UDP time and chat communication.
3. Study the file transfer and matrix classification examples.
4. Explore the abbreviation translator and raw packet sniffer for advanced socket concepts.

## License

This project is provided for academic study and learning purposes.

## Author

This repository is part of a Computer Networks laboratory collection for a university-level networking course.
