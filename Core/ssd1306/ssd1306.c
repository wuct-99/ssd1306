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
    HAL_Delay(1);
    HAL_GPIO_WritePin(OLED_RES, 1);

	//set mux ration		
    oled_writecmd(0xA8);
    oled_writecmd(0x3F);

	//set display offest
    oled_writecmd(0xD3);
    oled_writecmd(0x00);

	//set display start line
    oled_writecmd(0x40);

	//set segment re-map
    oled_writecmd(0xA1);

	//set com output scan direction
    oled_writecmd(0xC8);

	//set com pins hardware configuration
    oled_writecmd(0xDA);
    oled_writecmd(0x02);

	//set contrast control
    oled_writecmd(0x81);
    oled_writecmd(0x7F);

	//diable entire diasplay on
    oled_writecmd(0xA4);

	//set normal display 
    oled_writecmd(0xA6);

	//set osc frequency
    oled_writecmd(0xD5);
    oled_writecmd(0x80);

	//enable charge pump regulator
    oled_writecmd(0x8D);
    oled_writecmd(0x14);

	//display
    oled_writecmd(0xAF);
}

void spi_sendbyte(uint8_t data)
{
    HAL_SPI_Transmit(&spi_port, (uint8_t*)&data, 1, 10);
}

void oled_writecmd(uint8_t data)
{
    HAL_GPIO_WritePin(OLED_DC, 0);
    HAL_GPIO_WritePin(OLED_CS, 0);
    spi_sendbyte(data);
    HAL_GPIO_WritePin(OLED_CS, 1);
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
	oled_writecmd(0xAE);
    //set memory addressing mode
	oled_writecmd(0x20);
	oled_writecmd(0x00);

    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 127; j++){
            oled_writedata(data);
        }
    }
	oled_writecmd(0xAF);
}

void oled_print(){
    uint8_t data[] = {0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x2000, 0x0000};

    oled_writecmd(0xAE);
	oled_writecmd(0x20);
	oled_writecmd(0x00);

    oled_writedata(data[0][1]);

    oled_writecmd(0xAF);
}