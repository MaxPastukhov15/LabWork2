# ===== Базовый образ с GCC и Make =====
FROM gcc:12.2.0

# Установка зависимостей (gtest для тестов)
RUN apt-get update && \
    apt-get install -y \
    make \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Сборка Google Test
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# Копирование всего проекта
WORKDIR /app
COPY . .

# Сборка проекта через Makefile
RUN make && make test

# Запуск (можно переопределить командой `docker run`)
CMD ["./run_game"]
