
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"


byte i, j, k;


#include "t_board.h"

#include "shapes.h"


#include "game.h"



/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,   // background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
};

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void game(void)
{
  ppu_off();
  for(i = 0; i < BOARD_SIZE_Y; i++)
  {
    vram_adr(NTADR_A(BOARD_RIGHT_MARGIN, 1 + i));
    vram_put(5);
    vram_adr(NTADR_A(BOARD_RIGHT_MARGIN + BOARD_SIZE_X + 1, 1 + i));
    vram_put(5);
  }
  
  vram_adr(NTADR_A(BOARD_RIGHT_MARGIN, BOARD_SIZE_Y + 1));
  
  for(i = 0; i < BOARD_SIZE_X + 2; i++)
  {
    vram_put(5);
  }
  
  vram_adr(NTADR_A(0,0));
  ppu_on_all();
  
  start();
  
  // infinite loop
  while(1) {
    ppu_wait_frame();
    
    oam_off = 0;
    draw();
    if(oam_off != 0) oam_hide_rest(oam_off);
    
    update();
  }
}

void main(void)
{
  setup_graphics();
  ppu_on_all();
  
  game();
}
