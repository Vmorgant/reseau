#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 1500
#define MAX_MSG 100

int main(int argc, char *argv[]){
        
        char chr;
        FILE * file;
	int sd,rc,i;
	struct sockaddr_in localAddr,servAddr;
	struct hostent *h;
	if(argc <3){
		printf("%s <server> <file>\n",argv[0]);
		exit(1);
	}
	h=gethostbyname(argv[1]);
	if(h==NULL){
		printf("%s : unknow host '%s' \n",argv[0],argv[1]);
		exit(1);
	}
	servAddr.sin_family=h->h_addrtype;
	memcpy((char *) &servAddr.sin_addr.s_addr,h->h_addr_list[0],h->h_length);
	servAddr.sin_port =htons(SERVER_PORT);
	
	/*create socket*/
	sd=socket(AF_INET, SOCK_STREAM,0);
	if(sd<0){
		perror("cannot open socket ");
		exit(1);
	}
	
	/*bind any port number*/
	
	localAddr.sin_family =AF_INET;
	localAddr.sin_addr.s_addr =htonl(INADDR_ANY);
	localAddr.sin_port =htons(0);
	rc=bind(sd,(struct sockaddr *) &localAddr,sizeof(localAddr));
	if(rc<0){
		printf("%s : cannot bind port TCP %u \n",argv[0],SERVER_PORT);
		perror("error ");
		exit(1);
	}
	
	/*Connect to server*/
	
	rc=connect(sd,(struct sockaddr *) &servAddr,sizeof(servAddr));
	if(rc<0){
		perror("cannot connect ");
		exit(1);
	}
	
        file=fopen(argv[2],"r");
        while(!feof(file)){
                fscanf(file,"%c",&chr);
                rc=send( sd,&chr,sizeof(char) + 1, 0);
                if(rc<0){
                    perror("cannot send data");
                    close(sd);
                    exit(1);
                }
        
	}
	printf("%s : data%u sent (%s) \n",argv[0],2,argv[2]);
	fclose(file);
	close(sd);
	return(0);
}
	
