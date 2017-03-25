all : client serveur

client : client.c
	gcc client.c -o client
serveur : Serveur.c
	gcc Serveur.c -o serveur

clean : 
	rm *.o