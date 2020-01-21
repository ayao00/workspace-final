struct Minesweeper{
  struct space **board;
  int rows;
  int columns;
  int size;
  int mines;
};

struct space{
  int revealed;
  int mine;
  int neighborcount;
  int flagged; //corresponds to the player number who found it
};

void placeMines(struct Minesweeper *gameboard);
int getMineCount(struct Minesweeper *gameboard, int y, int x);
void findMineCounts(struct Minesweeper *gameboard);
void uncoverCheat(struct Minesweeper *gameboard, int y, int x);
void uncoverSpace(struct Minesweeper *gameboard, int y, int x);
void flagSpace(struct Minesweeper *gameboard, int y, int x);
struct Minesweeper *makeBoard(int difficulty);
void printBoard(struct Minesweeper *gameboard);
void showAns(struct Minesweeper * gameboard);
int checkDone(struct Minesweeper *gameboard);
struct space createSpace();
void freeBoard(struct Minesweeper *gameboard);
char * wordBoard(struct Minesweeper *gameboard);
