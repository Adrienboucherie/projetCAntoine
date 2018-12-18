%.o: %.c recherche.h
	gcc -c $< -g

librecherche.a: config.o directory_list.o
	ar -rs $@ $^