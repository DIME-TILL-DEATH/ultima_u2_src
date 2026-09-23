uint32_t Arsys_sym(const uint8_t col , const uint8_t pag , const uint16_t sym , const uint8_t curs);
uint32_t Arsys_sym_up(uint8_t col , uint8_t pag , uint16_t sym , uint8_t curs);
uint32_t Arsys_sym_down(uint8_t col , uint8_t pag , uint16_t sym , uint8_t curs);
void Arsys_line(const uint8_t col , const  uint8_t pag , const  uint8_t* adr , const uint8_t curs);
void Arsys_clean(const uint8_t col , const uint8_t pag , const uint8_t* adr);
void Arsys_clean_(uint8_t col , uint8_t pag , uint8_t size );
void Arsys_num(uint8_t col , uint8_t pag , uint8_t val , uint8_t curs);

extern uint8_t font_buf[];
extern volatile uint8_t dma_complete_fl;
extern const uint8_t SystemFont5x7[];
//void spi3_dma_init_transfer(uint8_t length , uint32_t* adr);
