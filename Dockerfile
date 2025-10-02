FROM debian:bullseye

# Install dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    libreadline-dev \
    file \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /minishell

# Copy only source files, not binaries
COPY include ./include
COPY src ./src
COPY bonus ./bonus
COPY libs/Libft/*.c libs/Libft/
COPY libs/Libft/libft.h libs/Libft/
COPY Makefile .
COPY *.supp .

# Remove any existing binaries to ensure clean compilation
RUN rm -f minishell minishell_bonus

# Clean all binaries and compile fresh inside container
RUN cd libs/Libft && rm -f *.o *.a && \
    gcc -Wall -Wextra -Werror -c *.c && \
    ar rcs libft.a *.o && \
    cd /minishell && \
    rm -f minishell minishell_bonus && \
    make fclean && make clean && make && make bonus

RUN file ./minishell && echo "Binary type:" && file ./minishell
RUN file ./minishell_bonus && echo "Bonus binary type:" && file ./minishell_bonus
