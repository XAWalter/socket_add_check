#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char * argv[]){
	if(argc != 4){
		printf("Incorrect Input\n");
		exit(1);
	}

	char *num_1 = argv[1];
	char *num_2 = argv[2];
	char *num_3 = argv[3];
	char response[256];

	printf("Guess: %s + %s = %s\n", num_1, num_2, num_3);

	int s = 0;
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
		exit(1);
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if( connect(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		perror("connect error");
	}

	
	send(s, num_1, 256, 0);
	send(s, num_2, 256, 0);
	send(s, num_3, 256, 0);


	recv(s, &response, 256, 0);
	printf("%s\n", response);

	recv(s, &response, 256, 0);
	int correct = atoi(response);
	printf("%d\n", correct);

	
	close(s);

	return 0;
}
