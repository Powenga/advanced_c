# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Папки
SRC = src
OBJ = obj
BIN = bin
INCLUDE = include

# Имя исполняемого файла
TARGET = $(BIN)/app

# Список исходников
SRCS = $(SRC)/main.c $(SRC)/utils.c $(SRC)/temp_functions.c $(SRC)/cli.c $(SRC)/file_reader.c
OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

# Определяем ОС
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(1) mkdir $(1)
    RM = if exist $(1) rmdir /s /q $(1)
else
    MKDIR = mkdir -p $(1)
    RM = rm -rf $(1)
endif

# Правило по умолчанию
all: $(TARGET)

# Создание папок
$(OBJ):
	$(call MKDIR,$@)

$(BIN):
	$(call MKDIR,$@)

# Сборка приложения
$(TARGET): $(OBJS) | $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Компиляция объектов
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	$(call RM,$(OBJ))
	$(call RM,$(BIN))
