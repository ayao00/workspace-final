#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#include "networking.h"
#include "board.h"
#include "play.h"

void process(char *s, struct Minesweeper *currentboard);
void subserver(int from_client, struct Minesweeper *currentboard);

int main() {
  char diff[10];
  struct Minesweeper *currentgame;

  printf("Enter a difficulty (easy, medium, hard, or other):\n");
  fgets(diff,sizeof(diff),stdin);
  if(!strncmp(diff, "easy", 4)){
    currentgame = makeBoard(1);
  }
  else if(!strncmp(diff, "medium", 6)){
    currentgame = makeBoard(2);
  }
  else if(!strncmp(diff, "hard", 4)){
    currentgame = makeBoard(3);
  }
  //else if (!strncmp(diff, "other", 1)){
  else{
    currentgame = makeBoard(4);
  }

  placeMines(currentgame);
  findMineCounts(currentgame);
  showAns(currentgame);
  printBoard(currentgame);

  int listen_socket;
  int f;
  listen_socket = server_setup();
  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket, currentgame);
      if (checkDone(currentgame) == 1){
        break;
      }
    else
      close(client_socket);
  }
}

void subserver(int client_socket, struct Minesweeper *currentboard) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer, currentboard);
    write(client_socket, "switched", sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s, struct Minesweeper *currentgame) {
  int x,y,j,i;
  int turns = 0;
  char ** coord = parse_args(s, ",");
  sscanf(coord[0],"%d", &x);
  sscanf(coord[1],"%d", &y);
  j = x - 1;
  i = currentgame->rows - y;
  printf("%d\n",i);
  printf("%d\n",j);
  if(!strncmp(coord[2],"u",1)){
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
}
