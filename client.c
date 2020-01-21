#include "networking.h"

struct input{
  char x[BUFFER_SIZE];
  char y[BUFFER_SIZE];
  char choice[BUFFER_SIZE];
};
int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];
  // char x[BUFFER_SIZE];
  // char y[BUFFER_SIZE];
  // char choice[BUFFER_SIZE];
  // char buffer[BUFFER_SIZE * 3];

  struct input current;
  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

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
