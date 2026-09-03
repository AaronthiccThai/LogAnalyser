# Log Analyser

## Overview

The Log Analyser is a C++ application designed to parse and analyse server log files. It currently supports Apache-style access and error logs and generates structured reports such as request counts, error rates, and error severity distributions.

The system is modular and extensible, allowing additional server logs and analysers to be easily integrated.

## Features

### Log Parsing
- Parses Apache access and error logs
- Automatically identifies log types
- Extracts structured log entries from raw text
- Handles invalid or malformed lines safely

### Request Analysis
- Counts total requests
- Counts total errors
- Calculates success and error rates
- Provides overall traffic summary
- Future work would involve showcasing request method and its path

### Error Severity Analysis
- Categorises errors by severity (e.g. WARN, ERROR, CRITICAL)
- Tracks frequency of each severity level
- Calculates percentage distribution
- Future work would involve identifying the most severe error and its line number

---

## Project Structure

```text
.
├── Dockerfile
├── README.md
├── notes.txt
├── src
│   ├── analysers
│   │   ├── AnalyserEngine.cpp
│   │   ├── AnalyserEngine.h
│   │   ├── ErrorSeverityAnalyser.cpp
│   │   ├── ErrorSeverityAnalyser.h
│   │   ├── ILogAnalyser.h
│   │   ├── RequestCountAnalyser.cpp
│   │   └── RequestCountAnalyser.h
│   ├── main.cpp
│   ├── models
│   │   ├── AccessLogEntry.h
│   │   ├── ErrorLogEntry.h
│   │   ├── ILogEntry.h
│   │   ├── ILogParser.h
│   │   ├── apache
│   │   │   ├── ApacheAccessLogEntry.h
│   │   │   └── ApacheErrorLogEntry.h
│   │   └── nginx
│   │       ├── NginxAccessLogEntry.h
│   │       └── NginxErrorLogEntry.h
│   ├── parsers
│   │   ├── ParserEngine.cpp
│   │   ├── ParserEngine.h
│   │   ├── apache
│   │   │   ├── ApacheAccessLogParser.cpp
│   │   │   ├── ApacheAccessLogParser.h
│   │   │   ├── ApacheErrorLogParser.cpp
│   │   │   └── ApacheErrorLogParser.h
│   │   └── nginx
│   │       ├── NginxAccessLogParser.cpp
│   │       ├── NginxAccessLogParser.h
│   │       ├── NginxErrorLogParser.cpp
│   │       └── NginxErrorLogParser.h
│   └── utils
│       ├── DateTime.h
│       └── printHelp.h
└── testfiles
    ├── apache
    │   ├── 1.log
    │   ├── 2.log
    │   ├── 3.log
    │   ├── 4.log
    │   ├── 5.log
    │   └── 6.log
    └── nginx
        ├── 1.log
        ├── 2.log
        └── 3.log
```
---

## Getting Started

### Prerequisites

- **C++ Compiler**: A C++17 compatible compiler (e.g., GCC 7+, Clang 5+, or MSVC 2017+).
- **CMake**: Version 3.10 or higher.
- **Docker** (optional): For containerised execution.

## Installation & Building


### Option 1: Build Natively (CMake)
1. **Clone the repository**:
   ```bash
   git clone https://github.com/AaronthiccThai/LogAnalyser.git
   cd LogAnalyser
   ```

2. **Build the project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Option 2: Running Via Docker
Ensure Docker is running in the background

1. **Clone the repository**:
   ```bash
   git clone https://github.com/AaronthiccThai/LogAnalyser.git
   cd LogAnalyser
2. **Build the Docker image**:
```docker build -t log-analyser .```


---

## Local Usage
First compile the codebase by running cmake -B build, then running ```bash ./build/make ```
Run the analyser by passing a log file followed by optional command-line flags:

```bash
./build/analyser <log_file> [options]
```

### Examples

Analyse all logs:
```bash
./build/analyser testfiles/4.log
```

Run only severity analysis:
```bash
./build/analyser testfiles/4.log --severity
```

Run only request analysis:
```bash
./build/analyser testfiles/4.log --requests
```

Save report:
```bash
./build/analyser testfiles/4.log --save
```

Show help:
```bash
./build/analyser --help
```

---

## Docker Usage

Run using Docker instead of local build:

### Build image
```bash
docker build -t log-analyser .
```

### Run analyser
```bash
docker run --rm log-analyser <log_file> [options]
```

### Examples

Analyse logs:
```bash
docker run --rm log-analyser testfiles/4.log
```

Run severity analysis:
```bash
docker run --rm log-analyser testfiles/4.log --severity
```

Save report (with volume mount):
```bash
docker run --rm -v $(pwd)/output:/app/output log-analyser testfiles/4.log --save
```

Show help:
```bash
docker run --rm log-analyser --help
```

---
## Extending the Project

The Log Analyser is built using an interface-driven and modular architecture.  
Analysers are now **command-driven**, meaning they are only executed if enabled via command-line flags (e.g. `--severity`, `--requests`, `--all`).

---

## Adding a New Log Format

### 1. Define the Model
Create a new class in `src/models/` that inherits from `ILogEntry`.

If extending an existing type:
- Use `AccessLogEntry` for access logs
- Use `ErrorLogEntry` for error logs

---

### 2. Implement the Parser
Create a new parser in `src/parsers/` that implements `ILogParser`.

You must implement:

- `supports(const std::string& line)`  
  → Determines whether this parser can handle the log line

- `parse(const std::string& line)`  
  → Converts the raw log line into a structured `ILogEntry`

---

### 3. Register the Parser
Add your parser to `ParserEngine`, so it is considered during parsing.

---

## Adding a New Analyser (Command-Driven)

Analysers are **no longer automatically executed**.  
They must be explicitly enabled through the CLI.

---

### 1. Create the Analyser Class
Create a new class in `src/analysers/` that implements `ILogAnalyser`.

Each analyser should:
- Follow the **Single Responsibility Principle**
- Maintain its own internal state
- Focus on one type of analysis (e.g. severity, requests, anomalies)

---

### 2. Implement Logic
Implement:

- `process(const ILogEntry& entry, int lineNumber)`
- `printReport()`
- `saveReport()`

Use `dynamic_cast` where necessary to access specific log types safely.

---

### 3. Register the Analyser (IMPORTANT CHANGE)

Unlike the previous version, analysers are **not registered in the constructor by default**.

Instead, they are enabled via `AnalyserEngine` methods:

```cpp
--severity   → analyserEngine.enableSeverityAnalyser()
--requests   → analyserEngine.enableRequestAnalyser()
--all        → analyserEngine.enableAll()
```

So your analyser must be added inside the appropriate enable function in `AnalyserEngine`, not automatically at startup.

---

### 4. CLI Control Flow

The analyser will only run if:

- It is enabled via command-line flags
- OR `--all` is specified

