# Use an official C++ image for building
FROM gcc:latest AS builder

# Set the working directory
WORKDIR /app

# Copy the source code
COPY . .

# Build the C++ library using CMake
RUN apt-get update && apt-get install -y cmake \
    && rm -rf build \ 
    && mkdir build \ 
    && cd build \
    && cmake .. \
    && make

# Final image
FROM alpine:latest

# Copy the built library from the builder stage
COPY --from=builder /app/build/libmaze-factory.so /usr/local/lib/libmaze-factory.so
COPY --from=builder /app/include/ /usr/local/include/

# Set environment variables (if needed)
ENV LD_LIBRARY_PATH=/usr/local/lib

# This container runs as a service for the backend
CMD ["sleep", "infinity"]
