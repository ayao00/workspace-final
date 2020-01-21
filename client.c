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

struct input{
  char x[BUFFER_SIZE];
  char y[BUFFER_SIZE];
  char choice[BUFFER_SIZE];
};

int main(int argc, char **argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];

  struct input current;
  if (argc == 2)
  server_socket = client_setup( argv[1]);
  else
  server_socket = client_setup( TEST_IP );

  srand(time(NULL));
  printf("Have you played before (y/n)? ");
  char ans[5];
  fgets(ans,sizeof(ans), stdin);

  struct player playerOne;
  char username[20];
  if(!strncmp(ans,"y",1)){
    printf("What is your username? ");
    fgets(username, 256, stdin);
    username[strlen(username) - 1] = '\0';
    printf("%s\n", username);
    playerOne = findPlayer(username);
  }else{
    printf("What would you like your username to be? ");
    fgets(username, 256, stdin);
    username[strlen(username) - 1] = '\0';
    playerOne = makePlayer(username);
  }
  printPlayer(playerOne);

  // char diff[10];
  // struct Minesweeper *currentgame;
  //
  // printf("Enter a difficulty (easy, medium, hard, or other):\n");
  // fgets(diff,sizeof(diff),stdin);
  // if(!strncmp(diff, "easy", 4)){
  //   currentgame = makeBoard(1);
  // }
  // else if(!strncmp(diff, "medium", 6)){
  //   currentgame = makeBoard(2);
  // }
  // else if(!strncmp(diff, "hard", 4)){
  //   currentgame = makeBoard(3);
  // }
  // //else if (!strncmp(diff, "other", 1)){
  // else{
  //   currentgame = makeBoard(4);
  // }
  //
  // placeMines(currentgame);
  // findMineCounts(currentgame);
  // showAns(currentgame);
  // printBoard(currentgame);


  while (1) {

    printf("Enter an x-coor: ");
    fgets(current.x, sizeof(buffer), stdin);
    *strchr(current.x, '\n') = 0;

    printf("Enter a y-coor: ");
    fgets(current.y, sizeof(buffer), stdin);
     *strchr(current.y, '\n') = 0;

    printf("Uncover or flag? (f/u): ");
    fgets(current.choice, sizeof(buffer), stdin);
     *strchr(current.choice, '\n') = 0;

    strcpy(buffer, current.x);
    strcat(buffer, current.y);
    strcat(buffer, current.choice);
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
