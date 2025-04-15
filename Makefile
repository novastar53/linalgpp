build:
	clang++  -framework Accelerate src/main.cpp  -DACCELERATE_NEW_LAPACK 

.PHONY: build