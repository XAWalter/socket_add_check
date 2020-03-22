#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include <string.h>

int main(){
	int s = 0;

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
	}

	struct sockaddr_in s_addr;

	int opt = 1;

	setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	s_addr.sin_addr.s_addr = INADDR_ANY;

	if( bind(s, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
		perror("bind error");
		exit(1);
	}
while(1){
	if(listen(s, 3) < 0){
		perror("listen error");
	}

	int c_sock = 0;
	int addrlen = sizeof(s_addr);

	if((c_sock = accept(s, (struct sockaddr *)&s_addr, (socklen_t*)&addrlen)) < 0 ){
		perror("accept error");
		exit(-1);
	}

	char temp[256];

	recv(c_sock, &temp, 256, 0);
	int num_1 = atoi(temp);

	recv(c_sock, &temp, 256, 0);
	int num_2 = atoi(temp);

	recv(c_sock, &temp, 256, 0);
	int num_3 = atoi(temp);

	char *response;

	if((num_1+num_2) == num_3){
		response = "correct";
	}
	else{
		response = "incorrect";
		num_3 = num_1+num_2;
		sprintf(temp, "%d", num_3);
	}

	send(c_sock, response, 256, 0);
	send(c_sock, temp, 256, 0);
}

	close(s);

	return 0;
}
