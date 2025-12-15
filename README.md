# Blackjack
A basic game of blackjack using Qt and QML

## Build & Run

### Prerequisites
## Build & Run

### Prerequisites
- Qt 6.5 or later
- CMake 3.16+
- A C++17 compatible compiler
  - Windows: MSVC
  - macOS: Clang
  - Linux: GCC or Clang

### Option 1: Qt Creator (Recommended)
1. Open Qt Creator
2. Select **Open Project**
3. Open `CMakeLists.txt`
4. Configure with a Qt 6 kit
5. Build and run

### Option 2: Command Line
```bash
mkdir build
cd build
cmake ..
cmake --build .
./blackjack   # or blackjack.exe on Windows


