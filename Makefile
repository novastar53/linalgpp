# === Choose backend: cpu, cuda, macos ===
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    BACKEND := macos
else ifeq ($(UNAME), Linux)
    BACKEND := cuda
endif

# === Compiler options ===
CXX := g++
NVCC := nvcc
CLANG := clang++

CXXFLAGS := -O3 -std=c++17
LDFLAGS :=
SRC := src/main.cpp
EXE := dot_product

# === Backend-specific settings ===
ifeq ($(BACKEND),cuda)
    COMPILER := $(NVCC)
    LDFLAGS += -lcublas
else ifeq ($(BACKEND),macos)
    COMPILER := $(CLANG)
    LDFLAGS += -framework Accelerate
else
    COMPILER := $(CXX)
endif

# === Build rule ===
all:
	$(COMPILER) $(CXXFLAGS) $(SRC) -o $(EXE) $(LDFLAGS)

# === Clean rule ===
clean:
	rm -f dot_product_* *.o *.out