// 
//  Font data for Verdana 8pt
// 

#include <avr/pgmspace.h>

const uint8_t daftOrder[] = {2,1,3,7,0,6,8,5,4};
const uint8_t daftWidths[] = {7,6,5,7,2,5,6,6,6}; 

// 50 + 18 = 68 bits = 9 bytes

// Character bitmaps for Verdana 8pt
const uint8_t PROGMEM daftLetters[] = 
{
  // 1@0 'A' (6 pixels wide)
  0x30, //   ##  
  0x30, //   ##  
  0x48, //  #  # 
  0x48, //  #  # 
  0x48, //  #  # 
  0xFC, // ######
  0x84, // #    #
  0x84, // #    #

  // 2@8 'D' (7 pixels wide)
  0xF8, // #####  
  0x84, // #    # 
  0x82, // #     #
  0x82, // #     #
  0x82, // #     #
  0x82, // #     #
  0x84, // #    # 
  0xF8, // #####  

  // 3@16 'F' (5 pixels wide)
  0xF8, // #####
  0x80, // #    
  0x80, // #    
  0xF0, // #### 
  0x80, // #    
  0x80, // #    
  0x80, // #    
  0x80, // #    

  // 4@24 'K' (6 pixels wide)
  0x84, // #    #
  0x88, // #   # 
  0x90, // #  #  
  0xA0, // # #   
  0xE0, // ###   
  0x90, // #  #  
  0x88, // #   # 
  0x84, // #    #

  // 5@32 'N' (6 pixels wide)
  0xC4, // ##   #
  0xC4, // ##   #
  0xA4, // # #  #
  0xA4, // # #  #
  0x94, // #  # #
  0x94, // #  # #
  0x8C, // #   ##
  0x8C, // #   ##

  // 6@40 'P' (5 pixels wide)
  0xF0, // #### 
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0xF0, // #### 
  0x80, // #    
  0x80, // #    
  0x80, // #    

  // 7@48 'T' (7 pixels wide)
  0xFE, // #######
  0x10, //    #   
  0x10, //    #   
  0x10, //    #   
  0x10, //    #   
  0x10, //    #   
  0x10, //    #   
  0x10, //    #   

  // 8@56 'U' (6 pixels wide)
  0x84, // #    #
  0x84, // #    #
  0x84, // #    #
  0x84, // #    #
  0x84, // #    #
  0x84, // #    #
  0x84, // #    #
  0x78, //  #### 
};