byte pad;

byte score;

byte fall_count_down;
byte FALL_FRAMES = 30;

byte nextShape;
byte currShape;
sbyte shapeX = 5;
byte shapeY;

byte rotation;

void get_next_shape(void)
{
  rotation = 0;
  currShape = nextShape;
  nextShape = rand() % SHAPES_COUNT;
}

void move_down(void)
{
  fall_count_down = 0;
  
  if(shapeY + SHAPE_MARGIN_BELOW(currShape) + 2 < BOARD_SIZE_Y
     && !is_shape_colliding(currShape, shapeX, shapeY + 1))
  {
    ++shapeY;
  }
  else
  {
    place_shape(currShape, shapeX, shapeY);
    get_next_shape();
    
    --FALL_FRAMES;
    
    shapeX = BLOCK_START;
    shapeY = 0;
  }
}

void start(void)
{
  shapeX = BLOCK_START;
  get_next_shape();
}

void draw(void)
{
  draw_shape(currShape, shapeX, shapeY);
  draw_shape(nextShape, BOARD_SIZE_X + 3, 5);
}

void update(void)
{
  pad = pad_trigger(0);
  
  if(pad&PAD_A)
  {
    if(rotation < 1)
    {
      ++rotation;
      currShape += SHAPES_COUNT;
    }
    else
    {
      rotation = 0;
      currShape -= SHAPES_COUNT;
    }
  }
  
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
  
  checkForBoardLines(&score);
}

