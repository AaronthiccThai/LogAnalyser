FROM gcc:13

WORKDIR /app

COPY . .

RUN find src -name "*.cpp" | xargs g++ -std=c++17 -Isrc -o log_analyser

ENTRYPOINT ["./log_analyser"]