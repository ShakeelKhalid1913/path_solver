# Path Solver

A C++ implementation of a path-finding algorithm that finds the optimal path through a 2D grid environment with obstacles.

## 🚀 Features

- Grid-based pathfinding using forward search algorithm
- Backtracking to find optimal path
- Support for 20x20 grid environments
- Handles obstacles, start points, and goal points
- Memory-efficient node exploration

## 🛠 Technical Details

### Environment Symbols
- `S`: Start position
- `G`: Goal position
- `=`: Wall/Obstacle
- `.`: Empty space

### Core Components

1. **Node System**
   - Position tracking (x,y coordinates)
   - Distance calculations
   - Parent-child relationships for path reconstruction

2. **NodeList Management**
   - Dynamic node storage
   - Explored nodes tracking
   - Path reconstruction capabilities

3. **PathSolver Algorithm**
   - Forward search implementation
   - Optimal path backtracking
   - Environment analysis

## 🔧 Build Requirements

- C++17 or higher
- CMake 3.28 or higher
- A C++ compiler (gcc, clang, or MSVC)

## 📋 Building the Project

```bash
# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .
```

## 🏃‍♂️ Running the Program

```bash
./path_solver
```

## 📁 Project Structure

```
path_solver/
├── CMakeLists.txt        # CMake build configuration
├── Types.h              # Common type definitions
├── Node.h/cpp           # Node class implementation
├── NodeList.h/cpp       # Node list management
├── PathSolver.h/cpp     # Core pathfinding algorithm
├── main.cpp            # Program entry point
└── sampleTest/         # Test cases and examples
```

## 💡 Algorithm Overview

1. **Forward Search**
   - Explores the grid from start position
   - Identifies possible paths
   - Tracks explored nodes

2. **Backtracking**
   - Reconstructs optimal path
   - Uses parent-child relationships
   - Returns shortest path from start to goal

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 👤 Author

**Shakeel Khalid**
- GitHub: [@shakeelkhalid1913](https://github.com/shakeelkhalid1913)

## 📝 License

This project is open source and available under the [MIT License](LICENSE).
