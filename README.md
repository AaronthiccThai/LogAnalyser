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

### Error Severity Analysis
- Categorises errors by severity (e.g. WARN, ERROR, CRITICAL)
- Tracks frequency of each severity level
- Calculates percentage distribution
- Identifies the most severe error and its line number

---

## Project Structure

- `src/`: Contains the core implementation (main entry, server logic, and normalisers).
- `include/`: Header files for the application's ADTs and logic.
- `models/`: Defines the log entry interfaces and specific implementations (Access/Error).
- `utils/`: Utility classes for common tasks like date/time manipulation.

---

## Getting Started

### Prerequisites

- **C++ Compiler**: A C++17 compatible compiler (e.g., GCC 7+, Clang 5+, or MSVC 2017+).
- **CMake**: Version 3.10 or higher.

### Installation & Building

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

### Usage

To analyse a log file, run the compiled binary and pass the path to your log file as an argument:

```bash
./analyser path/to/your/access.log
```

## Extending the Project 
The Log Analyser is designed with an interface-driven architecture, making it easy to add new functionality. 

### Adding a New Log Format 
1. Define the Model: Create a new class in src/models/ that inherits from ILogEntry. If you are adding a variation of an access or error log, inherit from AccessLogEntry or ErrorLogEntry. 

2. Implement the Parser: Create a new parser class in src/parsers/ that implements the ILogParser interface. You must provide logic for:
   -  ```supports(const std::string& line)```: To detect if a line matches your format.
   -  ```parse(const std::string& line)```: To extract data into your model. 

3. Register the Parser: Add your new parser to the ParserEngine registry so it can be utilised during the file processing loop.

### Adding a New Analyser 
1. Create the Analyser Class: Define a new class in src/analysers/ that implements the ILogAnalyser interface. Each analyser should follow the Single Responsibility Principle, meaning it focuses on one specific type of analysis (e.g. request counting, error severity tracking, or anomaly detection) and maintains its own internal state independently. You must provide logic for:
   -  ```supports(const std::string& line)```: To detect if a line matches your format.
   -  ```parse(const std::string& line)```: To extract data into your model. 

2. Implement Logic: Use dynamic_cast within your process method (as seen in ErrorSeverityAnalyser) to safely access specific fields if you are targeting a particular log type (like AccessLogEntry).

3. Register the Analyser: Add your new analyser to the AnalyserEngine registry so it can be utilised during the file processing loop.

