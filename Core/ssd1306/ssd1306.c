/*
By Samosn Wu
*/
#include "ssd1306.h"

void ssd1306_init()
{
    HAL_GPIO_WritePin(OLED_DC, 1);
    HAL_GPIO_WritePin(OLED_CS, 1);
    HAL_GPIO_WritePin(OLED_RES, 1);
    HAL_Delay(1);
    HAL_GPIO_WritePin(OLED_RES, 0);
    HAL_Delay(3);
    HAL_GPIO_WritePin(OLED_RES, 1);

    HAL_Delay(100);

    oled_writecmd(0xAE);

	//set osc frequency
    oled_writecmd(0xD5);
    oled_writecmd(0x80);

	// set mux ratio	
    oled_writecmd(0xA8);
    oled_writecmd(0x3F);

	//set display offest
    oled_writecmd(0xD3);
    oled_writecmd(0x00);

	//enable charge pump regulator
    oled_writecmd(0x8D);
    oled_writecmd(0x14);
    
    //set the memory mode
	oled_writecmd(0x20);
	oled_writecmd(0x00);

	//set segment re-map
    oled_writecmd(0xA1);

	//set com output scan direction
    oled_writecmd(0xC8);
	
	//set com pins hardware configuration
    oled_writecmd(0xDA);
    oled_writecmd(0x12);

	//set contrast control
    oled_writecmd(0x81);
    oled_writecmd(0xCF);

    oled_writedata(0xD9);
    oled_writedata(0xF1);

    oled_writedata(0xDb);
    oled_writedata(0x40);

	//diable entire diasplay on
    oled_writecmd(0xA4);

	//set normal display 
    oled_writecmd(0xA6);

	//display on
    oled_writecmd(0xAF);

    clean_screen();
}

void spi_sendbyte(uint8_t data)
{
    // HAL_SPI_Transmit(&spi_port, (uint8_t*)&data, 1, 10);
    HAL_SPI_Transmit_DMA(&spi_port, (uint8_t*)&data, 1);
}

void oled_writecmd(uint8_t data)
{
    HAL_GPIO_WritePin(OLED_DC, 0);
    HAL_GPIO_WritePin(OLED_CS, 0);
    spi_sendbyte(data);
    HAL_GPIO_WritePin(OLED_CS, 1);
    HAL_Delay(1);
}

void oled_writedata(uint8_t data)
{
    HAL_GPIO_WritePin(OLED_DC, 1);
    HAL_GPIO_WritePin(OLED_CS, 0);
    spi_sendbyte(data);
    HAL_GPIO_WritePin(OLED_CS, 1);
}

void clean_screen(){
    fill_screen(0x00);
}

void fill_white(){
    fill_screen(0xFF);
}

void fill_screen(uint8_t data){
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 127; j++){
            oled_writedata(data);
        }
    }
}

void oled_print(uint8_t x, uint8_t y){
    uint8_t page = x / 8;
    uint8_t curr_x = page * 8;
    uint8_t shift = x - curr_x;
	
	oled_writecmd(0x20);
	oled_writecmd(0x00);

    oled_writecmd(0x22);
    oled_writecmd(page);
    oled_writecmd(7);

    oled_writecmd(0x21);
    oled_writecmd(y);
    oled_writecmd(127);

    // uint8_t t[] = {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31};
    //write data
    for(uint8_t i = 0; i < font_width; i++){
        // oled_writedata(t[i] << shift);
        oled_writedata(font_array[10+i] << shift);
    }

    if(shift != 0){
        oled_writecmd(0x22);
        oled_writecmd(page + 1);
        oled_writecmd(7);

        oled_writecmd(0x21);
        oled_writecmd(y);
        oled_writecmd(127);
        
        for(uint8_t i = 0; i < font_width; i++){
            oled_writedata(font_array[10+i] >> (8 - shift));
        }
    }
}

void oled_print_ch(uint8_t x, uint8_t y, char ch){
    uint16_t index = ((ch - 32) * font_width)+ 4;

    uint8_t page = x / 8;
    uint8_t curr_x = page * 8;
    uint8_t shift = x - curr_x;
	
	oled_writecmd(0x20);
	oled_writecmd(0x00);

    oled_writecmd(0x22);
    oled_writecmd(page);
    oled_writecmd(7);

    oled_writecmd(0x21);
    oled_writecmd(y);
    oled_writecmd(127);

    //write data
    for(uint8_t i = 0; i <= font_width; i++){
        oled_writedata(font_array[index+i] << shift);
    }

    if(shift != 0){
        oled_writecmd(0x22);
        oled_writecmd(page + 1);
        oled_writecmd(7);

        oled_writecmd(0x21);
        oled_writecmd(y);
        oled_writecmd(127);
        
        for(uint8_t i = 0; i <= font_width; i++){
            oled_writedata(font_array[index+i] >> (8 - shift));
        }
    }
}

void oled_print_str(uint8_t x, uint8_t y, char* text){
    uint16_t num_word = strlen(text);
    for(int i = 0; i <= num_word; i++){
        oled_print_ch(x , y + (i * font_width), text[i]);
    }
}