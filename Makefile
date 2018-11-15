all:
	$(CC) -std=c99 -o minidb src/minidb.c -Isrc

.PHONY: test
test:
	sh ./test
