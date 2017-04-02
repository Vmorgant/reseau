all : client serveur

client : client.c
	gcc -g client.c -o client
serveur : Serveur.c
	gcc -g Serveur.c -o serveur

clean : 
	rm *.o