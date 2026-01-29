# console
single-header console logger (with timestamps, and optional log levels) for C++

# example
```cpp
	console::init("Console Title");
	console::log("Hello world!"); // no level, just timestamp is displayed here
    console::log("Hello world!", console::level::INFO);
```
