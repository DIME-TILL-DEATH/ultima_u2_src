#ifndef __SH1106_H__
#define __SH1106_H__

#include "apptypes.h"


class sh1106_t
{

  // экранчик представляет собой матрицу 8x128 элементов ( 8 row x 128 col )
  // каждый элемент представляет собой 8 пикселей
  // элемент адресуется и пиксели выставляются 8 битами записанного по адрусу [ row, col ] байта

  enum command_t : uint8_t
  {
    cmd_set_low_col        = 0x00,
    cmd_set_high_col       = 0x10,
    cmd_set_row            = 0xb0,
    cmd_off                = 0xAE,
    cmd_on                 = 0xAF,
    cmd_multiplex_ratio    = 0xA8,
    cmd_contrast           = 0x81,
    cmd_com_scan_direction = 0xC8,
    cmd_offset             = 0xD3,
    cmd_clock_div          = 0xD5,
    cmd_com_pins           = 0xDA,
    cmd_precharge_period   = 0xD9,
    cmd_vcom_detect        = 0xDB,
    cmd_color_normal       = 0xA6,
    cmd_color_invert       = 0xA7,
  };


  typedef void (*reset_state_active_t)();
  typedef void (*reset_state_deactive_t)();
  typedef void (*init_t)();
  typedef void (*write_t)(const uint8_t val);
  typedef void (*cs_t)();
  typedef void (*delay_ms_t)(uint32_t val);
  typedef void (*mode_t)();

   public:

  constexpr static uint8_t rows = 8 ;
  constexpr static uint8_t cols = 128 ;

     struct font_t
      {
        const uint8_t  offset ; // индекс первого символа в ANSCI
        const uint8_t  hsize   ; // размер в пикселах
        const uint8_t  vsize   ; // размер в 8 пиксельных блоках  (vsize - 1) / 8 + 1
        const uint8_t  default_intersymbol_space ; // растояние между bound-box символов при отрисовке по умолчанию
        const uint8_t* bitmap ;
      } ;

     struct io_t
      {
        reset_state_active_t reset_state_active;
        reset_state_deactive_t reset_state_deactive;
        init_t init;
	write_t write;
	cs_t select ;
	cs_t deselect ;
	delay_ms_t delay_ms ;
	mode_t command_mode ;
	mode_t data_mode ;
      };



      inline sh1106_t (const io_t& io, const font_t* fonts) : io(io) , fonts(fonts)
        {
	  // инициализация SPI io
	  io.init();

	  io.reset_state_active();
	  io.delay_ms(0xffff);
	  io.reset_state_deactive();
	  io.delay_ms(0xffff);

	  command( cmd_off);           /*display off*/
	  command( 0x02);           /*set lower column address*/
	  command( 0x10);           /*set higher column address*/
	  command( 0x40);           /*set display start line*/
	  command( 0xB0);           /*set page address*/
	  command( cmd_contrast);           /*contract control*/
	  command( 0x80);           /*128*/
	  command( 0xA1);           /*set segment remap*/
	  command( cmd_color_normal);           /*normal / reverse*/
	  command( cmd_multiplex_ratio);           /*multiplex ratio*/
	  command( 0x3F);           /*duty = 1/32*/
	  command( 0xAD);           /*set charge pump enable*/
	  command( 0x8B);           /*external VCC   */
	  command( 0x30 | 2);       /*0X30---0X33  set VPP   9V liangdu!!!!*/
	  command( cmd_com_scan_direction);           /*Com scan direction*/
	  command( cmd_offset);           /*set display offset*/
	  command( 0x00);           /*   0x20  */
	  command( cmd_clock_div);           /*set osc division*/
	  command( 0x80);
	  command( cmd_precharge_period);           /*set pre-charge period*/
	  command( 0x1F);           /*0x22*/
	  command( cmd_com_pins);           /*set COM pins*/
	  command( 0x12);
	  command( cmd_vcom_detect);           /*set vcomh*/
	  command( 0x40);
	  command( cmd_on);
	  clear();

	  font_index = 0 ;

        } ;
      inline ~sh1106_t () {} ;

      inline void col(const uint8_t val)
      {
	if ( val >= cols )
	  //std::__throw_out_of_range("invalid sh1106 col index");
	  return ;
	const uint8_t tmp = val + 2;          // Panel is 128 pixels wide, controller RAM has space for 132,
	io.command_mode();
	io.select();
	io.write(cmd_set_low_col  | (tmp & 0xF));
	io.write(cmd_set_high_col | (tmp >> 4));
	io.deselect();
      }

      inline void row(const uint8_t val)
      {
	if ( val >= rows )
	  //std::__throw_out_of_range("invalid sh1106 row index");
	  return ;
	command( cmd_set_row + val);
      }

      inline void move(const uint8_t col, const uint8_t row)
      {
	  if ( (row >= rows) || (col >= cols))
	    return ;
	  const uint8_t tmp = col + 2;
	  io.command_mode();
	  io.select();
	  io.write(cmd_set_low_col  | (tmp & 0xF));
	  io.write(cmd_set_high_col | (tmp >> 4));
	  io.write(cmd_set_row + row);
	  io.deselect();
      }

      inline void clear()
      {
	for (uint8_t row = 0 ; row < rows ; row++)
         {
            move(0, row);
            io.data_mode();
            io.select();
            for (uint8_t col = 0;  col < cols ; col++)
      	       io.write(0x00);
            io.deselect();
         }
      }

      inline void clear_rows( const uint8_t row_start , const uint8_t row_count , const uint8_t col_start,  const uint8_t col_count)
            {
      	for (uint8_t row = row_start ; row < row_start + row_count ; row++)
               {
                  move(col_start, row);
                  io.data_mode();
                  io.select();
                  for (uint8_t col = 0;  col < col_count ; col++)
            	       io.write(0x00);
                  io.deselect();
               }
            }

     // возвращает значение текущего col после отрисовки
     inline uint32_t string(const uint8_t col , const uint8_t row , const char* str)
     {
         uint32_t current_col = col ;
         for ( uint8_t stage = 0 ; stage < fonts[font_index].vsize; stage++)
         {
           move (col,row+stage);
           uint8_t i = 0 ;
           while(str[i])
             current_col += symbol(stage,str[i++] );
         }
         return current_col ;
     }

   inline void font(const  uint8_t val, const uint8_t intersymbol_space=255)
     {
       font_index = val ;
       intersymbol_space == 255 ? this->intersymbol_space = fonts[font_index].default_intersymbol_space : this->intersymbol_space = intersymbol_space ;
     }

   inline void fomst_inter_letter_space(const  uint8_t val=255)
     {
       val == 255 ? intersymbol_space = fonts[font_index].default_intersymbol_space : intersymbol_space = val ;
     }

   inline void color_invert ()
     {
       command(cmd_color_invert);
     }

   inline void color_normal ()
     {
       command(cmd_color_normal);
     }

   protected:


      inline void command (const uint8_t val)
         {
	  io.command_mode();

	  io.select();
	  io.write(val);

	  io.deselect();
         }

      void data(uint8_t val)
        {
	  io.data_mode();

          io.select();
          io.write(val);
          io.deselect();
        }

      // возвращает ширину символа + intersymbol_space
      inline uint32_t symbol(const uint8_t stage , const uint8_t sym)
      {
	  const uint8_t* font_symbol = &(fonts[font_index].bitmap[(sym - fonts[font_index].offset ) * (fonts[font_index].vsize * fonts[font_index].hsize+1)]) ;

	  uint8_t font_symbol_size = *font_symbol++ ;

	  for(uint32_t i = 0; i < font_symbol_size ; i++)
                {
	           data( font_symbol[i*fonts[font_index].vsize + stage] );
                }
              for(uint32_t i = 0; i < intersymbol_space ; i++)
                {
                   data(0);
                }
          return font_symbol_size + intersymbol_space ;
      }




   private:
      const io_t&   io    ;
      const font_t* fonts ;
      uint8_t font_index  ;
      uint8_t intersymbol_space ;


};

#endif /* __SH1106_H__ */
