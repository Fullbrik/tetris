#define BOARD_TOP_MARGIN 0
#define BOARD_RIGHT_MARGIN 1

#define BOARD_SIZE_X 10
#define BOARD_SIZE_Y 20

#define BLOCK_START 4

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
  t_board[y][x] = val;
}

byte readBoard(byte x, byte y)
{
  return t_board[y][x];
}

void flickerRow(byte row)
{
  oam_clear();
  
  for(j = 0; j < 5; ++j)
  {
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     vram_adr(NTADR_A(BOARD_RIGHT_MARGIN + 1, BOARD_TOP_MARGIN + 1 + row));
     vram_write(t_board[row], BOARD_SIZE_X);
     vram_adr(NTADR_A(0,0));
     
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     ppu_wait_frame();
     vram_adr(NTADR_A(BOARD_RIGHT_MARGIN + 1, BOARD_TOP_MARGIN + 1 + row));
     vram_write("                           ", BOARD_SIZE_X);
     vram_adr(NTADR_A(0,0));
   }
  
  for(j = 0; j < BOARD_SIZE_X; ++j)
  {
    writeToBoard(j, row, 0);
  }
  
  for(k = row; k > 0; --k)
  {
    for(j = 0; j < BOARD_SIZE_X; ++j)
    {
      writeToBoard(j,  k, readBoard(j, k - 1));
      writeToBoard(j,  k - 1, readBoard(j, 0));
    }
  }
  
  drawBoardToPPU();
}

void checkForBoardLines(byte* score)
{
  for(i = BOARD_SIZE_Y - 1; i != 255; --i)
  {
    byte placedBlocks = 0;
    
    for(j = 0; j < BOARD_SIZE_X; ++j)
    {
      if(readBoard(j, i))
        ++placedBlocks;
    }
    
    if(placedBlocks == BOARD_SIZE_X)
    {
      flickerRow(i);
      ++*score;
      --i;
    }
  }
}
