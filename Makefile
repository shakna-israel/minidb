all:
	$(CC) -o minidb src/minidb.c -Isrc

.PHONY: test
test:
	sh ./test
