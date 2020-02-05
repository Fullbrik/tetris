byte pad;

byte score;

byte fall_count_down;
#define FALL_FRAMES 5

byte currShape;
sbyte shapeX = 5;
byte shapeY;

void move_down(void)
{
  fall_count_down = 0;
  
  if(shapeY + SHAPE_MARGIN_BELOW(currShape) + 1 < BOARD_SIZE_Y 
     && !is_shape_colliding(currShape, shapeX, shapeY + 1))
  {
    ++shapeY;
  }
  else
  {
    place_shape(currShape, shapeX, shapeY);
    
    shapeY = 0;
  }
  
  
}

void start(void)
{
  
}

void draw(void)
{
  draw_shape(currShape, shapeX, shapeY);
}

void update(void)
{
  pad = pad_trigger(0);
  
  if(pad&PAD_LEFT)
  {
    if(shapeX + SHAPE_MARGIN_LEFT(currShape) > 0)
    {
      if(!is_shape_colliding(currShape, shapeX - 1, shapeY))
        --shapeX;
    }
  }
  
  if(pad&PAD_RIGHT)
  {
    if(shapeX + SHAPE_MARGIN_RIGHT(currShape) < BOARD_SIZE_X - 1)
    {
      if(!is_shape_colliding(currShape, shapeX + 1, shapeY))
        ++shapeX;
    }
  }
  
  if(pad&PAD_DOWN)
  {
    move_down();
  }
  
  ++fall_count_down;
  
  if(fall_count_down > FALL_FRAMES)
  {
    move_down();
  }
  
  checkForBoardLines();
}

