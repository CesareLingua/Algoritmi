CFLAGS = -std=gnu99 -Wall -pedantic

Start: hash_table.o hash_table_test.o unit_test.o
	gcc $(CFLAGS) hash_table.o hash_table_test.o unit_test.o -o Start

hash_table.o: hash_table.h unit_test.h hash_table_test.c
	gcc $(CFLAGS) -c hash_table.c -O2

hash_table_test.o: hash_table.h unit_test.h hash_table_test.c unit_test.c
	gcc $(CFLAGS) -c hash_table_test.c -O2

unit_test.o: unit_test.h hash_table.h unit_test.c
	gcc $(CFLAGS) -c unit_test.c -O2

clean:
	rm -f *.o
	rm -f Start
