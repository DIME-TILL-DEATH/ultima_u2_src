#define SH1106_COMMAND 0
#define SH1106_DATA    1
#define SH1106_ROWS    8
#define SH1106_X_PIXELS     128
#define SH1106_Y_PIXELS     64

void sh1106_gotoXY(uint8_t x, uint8_t y);
void sh1106_write_byte(uint8_t comm,uint8_t data);
void writeLcd(uint8_t data);
void sh1106_clear();
void spi3_dma_init_transfer(uint8_t length , uint32_t* adr);
