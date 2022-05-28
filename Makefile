all: Convert Concate

Convert:
	gcc -fcommon convert.c  --static -o bin2txt
Concate:
	gcc -fcommon concate.c  --static -o binpbin
