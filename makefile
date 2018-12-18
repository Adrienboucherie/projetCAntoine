%: %.c
	gcc -Wall -o $@ $@.c -g

treetest: treetest.c
	gcc -Wall -o $@ $@.c -Llib/recherche -lrecherche