FROM gcc:12.2.0

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    make \
    astyle \
    cmake \
    libgtest-dev && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /LabWork2

# Copy only what's needed for building
COPY Makefile .
COPY src/ src/
COPY include/ include/

# Build and verify the executable exists
RUN make && \
    ls -la && \
    test -f run_game || (echo "run_game not found!" && exit 1)

# Copy remaining files
COPY . .

# Set the entrypoint
CMD ["./run_game"]
