SOURCE = main.c src/hash_table.c src/utils.c
OUTPUT = hash_table
CFLAGS = -o $(OUTPUT) -lm

all:
	$(CC) $(SOURCE) $(CFLAGS)
	./$(OUTPUT)