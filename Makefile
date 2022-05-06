all: Convert

Convert:
	gcc -fcommon convert.c  --static -o bin2txt
