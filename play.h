struct player{
  char name[100];
  int pastgames;
  int victories;
  int losses;
};

struct player makePlayer(char * name);
struct player findPlayer(char * name);
void printPlayer(struct player user);
void addPlayer(struct player user);
