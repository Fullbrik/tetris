#define BOARD_TOP_MARGIN 0
#define BOARD_RIGHT_MARGIN 0

#define BOARD_SIZE_X 5
#define BOARD_SIZE_Y 7

byte t_board[BOARD_SIZE_Y][BOARD_SIZE_X] = {};

void drawBoardToPPU()
{
  ppu_off();
  
  for(i = 0; i < BOARD_SIZE_Y; i++)
  {
    vram_adr(NTADR_A(BOARD_RIGHT_MARGIN + 1, BOARD_TOP_MARGIN + 1 + i));
    vram_write(t_board[i], BOARD_SIZE_X);
  }
  
  vram_adr(NTADR_A(0,0));
  
  ppu_on_all();
}

void writeToBoard(byte x, byte y, byte val)
{
  t_board[x][y] = val;
}

byte readBoard(byte x, byte y)
{
  return t_board[x][y];
}
