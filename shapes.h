#define SHAPES_COUNT 1

const byte shapes[SHAPES_COUNT][3][3] =
{
  {
    {0, 0, 1},
    {0, 1, 1},
    {0, 1, 1}
  }
};

#define SHAPE_MARGIN_LEFT(shape)  shape_margins[shape][0]
#define SHAPE_MARGIN_RIGHT(shape) shape_margins[shape][1]
#define SHAPE_MARGIN_BELOW(shape) shape_margins[shape][1]
const byte shape_margins[SHAPES_COUNT][3] =
{
  {1,2,3}
};

void draw_shape(byte shape, byte x, byte y)
{
  #define BOARD_TO_SCREEN_X(x)(((x) + BOARD_RIGHT_MARGIN + 1)*8)
  #define BOARD_TO_SCREEN_Y(y)(((y) + BOARD_TOP_MARGIN + 1)*8)
  
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(shapes[shape][j][i])
        oam_off = oam_spr(BOARD_TO_SCREEN_X(x + i), BOARD_TO_SCREEN_Y(y + j) - 1, 0x01, shapes[shape][j][i], oam_off);
    }
  }
}

void place_shape(byte shape, byte x, byte y)
{
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(shapes[shape][j][i])
        writeToBoard(x + i, y + j, shapes[shape][j][i]);
    }
  }
  
  drawBoardToPPU();
}

byte is_shape_colliding(byte shape, byte x, byte y)
{
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(shapes[shape][j][i])
      {
        if(readBoard(x + i, y + j))
          return 1;
      }
    }
  }
  
  return 0;
}
