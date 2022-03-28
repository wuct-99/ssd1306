#ifndef __SSD1306_H
#define __SSD1306_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "main.h"
#include "ssd1306_fonts.h"


#define SSD1306_INCLUDE_FONT_6x8

#define spi_port hspi1

#define OLED_CS GPIOC, GPIO_PIN_5
#define OLED_DC GPIOC, GPIO_PIN_4
#define OLED_RES GPIOA, GPIO_PIN_6

void ssd1306_init();
void spi_sendbyte(uint8_t data);
void oled_writecmd(uint8_t data);
void oled_writedata(uint8_t data);
void clean_screen();
void fill_white();
void fill_screen(uint8_t data);
void oled_print(uint8_t x, uint8_t y);
void test();

#endif 