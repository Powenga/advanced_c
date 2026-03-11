# Компилятор и флаги
CC = gcc
CFLAGS = -fdiagnostics-color=always -Wall -Wextra -g -Iinclude 
LDFLAGS = -lncursesw 

# Папки
SRC = src
OBJ = obj
BIN = bin
INCLUDE = include

# Имя исполняемого файла
TARGET = $(BIN)/app

# Список исходников
SRCS = $(SRC)/main.c $(SRC)/roots.c $(SRC)/integrals.c $(SRC)/cli.c
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
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET) 

# Компиляция объектов
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	$(call RM,$(OBJ))
	$(call RM,$(BIN))
