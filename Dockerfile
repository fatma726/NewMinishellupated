FROM ubuntu:22.04

# Install necessary packages
RUN apt-get update && apt-get install -y \
    valgrind \
    gcc \
    make \
    libreadline-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Copy project files
COPY . .

# Don't pre-build - will compile fresh for correct architecture

# Default command
CMD ["bash"]
