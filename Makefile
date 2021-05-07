SOURCE = main.c src/hash_table.c
OUTPUT = hash_table
ADDITIONAL_CFLAGS = -o $(OUTPUT) -lm

all:
	$(CC) $(SOURCE) $(ADDITIONAL_CFLAGS)
	./$(OUTPUT)