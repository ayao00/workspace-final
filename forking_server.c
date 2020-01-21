#include "networking.h"
#include "board.h"
#include "play.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();

  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, "switched", sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  int x,y,j,i;
  int turns = 0;
  sscanf(s[0],"%d", &x);
  scanf(s[1],"%d", &y);
  j = x - 1;
  i = currentgame->rows - y;
  if(!strncmp(s[2],"u",1)){
    if (currentgame->board[i][j].revealed){
      //bruh
      printf("uncover the damn thing");
      uncoverCheat(currentgame, i, j);
    }else{
      uncoverSpace(currentgame, i, j);
    }
  }
  else{
    flagSpace(currentgame, i, j);
  }
  turns ++;
  printBoard(currentgame);
  if (checkDone(currentgame) == 1){
    break;
  }
}
