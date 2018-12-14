
/**
 * Copyright 2018 University of Applied Sciences Western Switzerland / Fribourg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project:	HEIA-FR / Embedded Systems 2 Laboratory
 *
 * Abstract: SEPS114A-C Click Board (SPEPS114A - LCD)
 *
 * Purpose:	This module provides a basic driver for the SEPS114A-C click board.
 *			This driver is customized to run with the HEIA-FR Beaglebone 
 *			Black in cape 1.
 *
 * Origin:	This driver has been largely inspired from the mikroElektronika
 *			device driver released for the STM32F10VC MCU.
 *
 * Author: 	Daniel Gachet
 * Date: 	24.10.2018
 */

#include <am335x_gpio.h>
#include "am335x_spi.h"


#include "oled.h"

static enum oled_devices {SSD1351, SEPS114A} oled_device = 
	SEPS114A;
//	SSD1351;


/** EN pin */
#define EN_PIN		9
#define EN_GPIO 	AM335X_GPIO0

/* R/W pin */
#define RW_PIN		8	
#define RW_GPIO 	AM335X_GPIO0

/* RST pin */
#define RST_PIN		10
#define RST_GPIO	AM335X_GPIO0

/* DC pin */
#define DC_PIN		18
#define DC_GPIO		AM335X_GPIO1

// ----------------------------------------------------------------------------

static int delay_ms(unsigned ms)
{
	for (int i=ms; i>0; i--)
		for (int j=0; j<1000; j++);
	return 0;
}

// ----------------------------------------------------------------------------

static inline void spi_init(uint32_t freq)
{
	am335x_spi_init (AM335X_SPI1, AM335X_CHAN0, freq, 8);
}

static inline void send_data (uint32_t* val, int nb)
{
	am335x_spi_write(AM335X_SPI1, AM335X_CHAN0, val, nb);
}

static inline void send_cmd (uint32_t cmd)
{
	// select command
	am335x_gpio_change_state(DC_GPIO, DC_PIN, false);
	send_data(&cmd, 1);
	am335x_gpio_change_state(DC_GPIO, DC_PIN, true);
}

static inline void send_cmd_val (uint32_t cmd, uint32_t value)
{
	send_cmd (cmd);
	send_data(&value, 1);
}

static inline void send_cmd_val2 (uint32_t cmd, uint32_t val1, uint32_t val2)
{
	send_cmd (cmd);
	uint32_t value[2] = {val1, val2};
	send_data(value, 1);
}

// ----------------------------------------------------------------------------

// SEPS114A commands, for details please read SPES114A datasheet
enum SEPS114A_vals {
	SEPS114A_SOFT_RESET				=0x01,
	SEPS114A_DISPLAY_ON_OFF			=0x02,
	SEPS114A_ANALOG_CONTROL			=0x0F,
	SEPS114A_STANDBY_ON_OFF			=0x14,
	SEPS114A_OSC_ADJUST				=0x1A,
	SEPS114A_ROW_SCAN_DIRECTION		=0x09,
	SEPS114A_DISPLAY_X1				=0x30,
	SEPS114A_DISPLAY_X2				=0x31,
	SEPS114A_DISPLAY_Y1				=0x32,
	SEPS114A_DISPLAY_Y2				=0x33,
	SEPS114A_DISPLAYSTART_X			=0x38,
	SEPS114A_DISPLAYSTART_Y			=0x39,
	SEPS114A_CPU_IF					=0x0D,
	SEPS114A_MEM_X1					=0x34,
	SEPS114A_MEM_X2					=0x35,
	SEPS114A_MEM_Y1					=0x36,
	SEPS114A_MEM_Y2					=0x37,
	SEPS114A_MEMORY_WRITE_READ		=0x1D,
	SEPS114A_DDRAM_DATA_ACCESS_PORT	=0x08,
	SEPS114A_DISCHARGE_TIME			=0x18,
	SEPS114A_PEAK_PULSE_DELAY		=0x16,
	SEPS114A_PEAK_PULSE_WIDTH_R		=0x3A,
	SEPS114A_PEAK_PULSE_WIDTH_G		=0x3B,
	SEPS114A_PEAK_PULSE_WIDTH_B		=0x3C,
	SEPS114A_PRECHARGE_CURRENT_R	=0x3D,
	SEPS114A_PRECHARGE_CURRENT_G	=0x3E,
	SEPS114A_PRECHARGE_CURRENT_B	=0x3F,
	SEPS114A_COLUMN_CURRENT_R		=0x40,
	SEPS114A_COLUMN_CURRENT_G		=0x41,
	SEPS114A_COLUMN_CURRENT_B		=0x42,
	SEPS114A_ROW_OVERLAP			=0x48,
	SEPS114A_SCAN_OFF_LEVEL			=0x49,
	SEPS114A_ROW_SCAN_ON_OFF		=0x17,
	SEPS114A_ROW_SCAN_MODE			=0x13,
	SEPS114A_SCREEN_SAVER_CONTROL	=0xD0,
	SEPS114A_SS_SLEEP_TIMER			=0xD1,
	SEPS114A_SCREEN_SAVER_MODE		=0xD2,
	SEPS114A_SS_UPDATE_TIMER		=0xD3,
	SEPS114A_RGB_IF					=0xE0,
	SEPS114A_RGB_POL				=0xE1,
	SEPS114A_DISPLAY_MODE_CONTROL	=0xE5,
};

// set memory area(address) to write a display data
void seps114a_set_area (uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2)
{
	send_cmd_val (SEPS114A_MEM_X1, x1);
	send_cmd_val (SEPS114A_MEM_X2, x2);
	send_cmd_val (SEPS114A_MEM_Y1, y1);
	send_cmd_val (SEPS114A_MEM_Y2, y2);

	//set DDRAM access port
	uint32_t data[1] = {0x08};
	am335x_gpio_change_state (DC_GPIO, DC_PIN, false);
	send_data (data, 1);

	// switch to data mode
	am335x_gpio_change_state (DC_GPIO, DC_PIN, true);
}

static void seps114a_init()
{
	// soft reset
	send_cmd_val (SEPS114A_SOFT_RESET, 0x00);    

	// standby ON/OFF (wait for 5ms between on/off (min delay 1ms)
	send_cmd_val (SEPS114A_STANDBY_ON_OFF, 0x01); // on
	delay_ms(5); 
	send_cmd_val (SEPS114A_STANDBY_ON_OFF, 0x00); //�off
	delay_ms(5);

	// display turn off
	send_cmd_val (SEPS114A_DISPLAY_ON_OFF, 0x00);

	// Set Oscillator operation (using external resistor and internal OSC)
	send_cmd_val (SEPS114A_ANALOG_CONTROL, 0x00);

	// set frame rate (95Hz)
	send_cmd_val (SEPS114A_OSC_ADJUST,0x03);

	// set active display area of panel
	send_cmd_val (SEPS114A_DISPLAY_X1, 0x00);
	send_cmd_val (SEPS114A_DISPLAY_X2, 0x5F);
	send_cmd_val (SEPS114A_DISPLAY_Y1, 0x00);
	send_cmd_val (SEPS114A_DISPLAY_Y2, 0x5F);

	// Select the RGB data format and set the initial state of RGB 
	// interface port (RGB 8bit interface)
	send_cmd_val (SEPS114A_RGB_IF, 0x00);           

	// set RGB polarity
	send_cmd_val (SEPS114A_RGB_POL, 0x00);

	// set display mode control (SWAP:BGR, Reduce current : Normal, DC[1:0] : Normal)
	send_cmd_val (SEPS114A_DISPLAY_MODE_CONTROL, 0x80);

	// set MCU Interface (MPU External interface mode, 8bits)
	send_cmd_val (SEPS114A_CPU_IF, 0x00);

	// set Memory Read/Write mode
	send_cmd_val (SEPS114A_MEMORY_WRITE_READ, 0x02);

	// set row scan direction (column: 0 --> max, row : 0 --> max)
	send_cmd_val (SEPS114A_ROW_SCAN_DIRECTION, 0x00);

	// Set row scan mode (alternate scan mode)
	send_cmd_val (SEPS114A_ROW_SCAN_MODE, 0x00); 

	// set column current
	send_cmd_val (SEPS114A_COLUMN_CURRENT_R, 0x6E);
	send_cmd_val (SEPS114A_COLUMN_CURRENT_G, 0x4F);
	send_cmd_val (SEPS114A_COLUMN_CURRENT_B, 0x77);

	// set row overlap (band gap only)
	send_cmd_val (SEPS114A_ROW_OVERLAP, 0x00);  

	// set discharge time (normal discharge time)
	send_cmd_val (SEPS114A_DISCHARGE_TIME, 0x01);

	// set peak pulse delay
	send_cmd_val (SEPS114A_PEAK_PULSE_DELAY, 0x00);

	// set peak pulse width
	send_cmd_val (SEPS114A_PEAK_PULSE_WIDTH_R, 0x02);
	send_cmd_val (SEPS114A_PEAK_PULSE_WIDTH_G, 0x02);
	send_cmd_val (SEPS114A_PEAK_PULSE_WIDTH_B, 0x02);

	// set precharge current
	send_cmd_val (SEPS114A_PRECHARGE_CURRENT_R, 0x14);
	send_cmd_val (SEPS114A_PRECHARGE_CURRENT_G, 0x50);
	send_cmd_val (SEPS114A_PRECHARGE_CURRENT_B, 0x19);
	
	// Set row scan on/off (normal row scan)
	send_cmd_val (SEPS114A_ROW_SCAN_ON_OFF, 0x00);

	// set scan off level (VCC_C*0.75)
	send_cmd_val (SEPS114A_SCAN_OFF_LEVEL, 0x04);

	// set memory access point
	send_cmd_val (SEPS114A_DISPLAYSTART_X, 0x00);
	send_cmd_val (SEPS114A_DISPLAYSTART_Y, 0x00);

  	// Clear screen
	oled_memory_size(0,95,0,95);
	for (int i=0;i<96*96; i++)
		oled_color(0x0000);

	// display turn on
	send_cmd_val (SEPS114A_DISPLAY_ON_OFF, 0x01);
}

// -----------------------------------------------------------------------------

// SSD1351 Commands
enum ssd1351 {
  SSD1351_SETCOLUMNADDRESS          = 0x15,
  SSD1351_SETROWADDRESS             = 0x75,
  SSD1351_WRITERAM                  = 0x5C, 
  SSD1351_READRAM                   = 0x5D, 
  SSD1351_COLORDEPTH                = 0xA0, 
  SSD1351_SETDISPLAYSTARTLINE       = 0xA1,
  SSD1351_SETDISPLAYOFFSET          = 0xA2, 
  SSD1351_SETDISPLAYMODE_ALLOFF     = 0xA4,
  SSD1351_SETDISPLAYMODE_ALLON      = 0xA5,
  SSD1351_SETDISPLAYMODE_RESET      = 0xA6,
  SSD1351_SETDISPLAYMODE_INVERT     = 0xA7,
  SSD1351_FUNCTIONSELECTION         = 0xAB,
  SSD1351_SLEEPMODE_DISPLAYOFF      = 0xAE,
  SSD1351_SLEEPMODE_DISPLAYON       = 0xAF,
  SSD1351_SETPHASELENGTH            = 0xB1,
  SSD1351_ENHANCEDDRIVINGSCHEME     = 0xB2, 
  SSD1351_SETFRONTCLOCKDIV          = 0xB3,
  SSD1351_SETSEGMENTLOWVOLTAGE      = 0xB4,
  SSD1351_SETGPIO                   = 0xB5,
  SSD1351_SETSECONDPRECHARGEPERIOD  = 0xB6,
  SSD1351_GRAYSCALELOOKUP           = 0xB8,
  SSD1351_LINEARLUT                 = 0xB9,
  SSD1351_SETPRECHARGEVOLTAGE       = 0xBB,
  SSD1351_SETVCOMHVOLTAGE           = 0xBE,
  SSD1351_SETCONTRAST               = 0xC1,
  SSD1351_MASTERCONTRAST            = 0xC7,
  SSD1351_SETMUXRRATIO              = 0xCA,
  SSD1351_NOP3                      = 0xD1,
  SSD1351_NOP4                      = 0xE3,
  SSD1351_SETCOMMANDLOCK            = 0xFD,
  SSD1351_HORIZONTALSCROLL          = 0x96,
  SSD1351_STOPMOVING                = 0x9E,
  SSD1351_STARTMOVING               = 0x9F  
};

static inline void ssd1351_dat (uint32_t value)
{
	send_data(&value, 1);
}

static void ssd1351_set_area(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2)
{
  send_cmd(SSD1351_WRITERAM);
  send_cmd(SSD1351_SETCOLUMNADDRESS);
  uint32_t x[2] = {x1+16, x2+16};
  send_data(x,2);

  send_cmd(SSD1351_SETROWADDRESS);
  uint32_t y[2] = {y1, y2};
  send_data(y,2);

  send_cmd(SSD1351_WRITERAM);
}

static void ssd1351_init()
{
	send_cmd(SSD1351_SETCOMMANDLOCK);
	ssd1351_dat(0x12);                               // Unlocked to enter commands
	send_cmd(SSD1351_SETCOMMANDLOCK);
	ssd1351_dat(0xB1);                               // Make all commands accessible 
	send_cmd(SSD1351_SLEEPMODE_DISPLAYOFF);
	send_cmd(SSD1351_SETFRONTCLOCKDIV);
	ssd1351_dat(0xF1);//was F1
	send_cmd(SSD1351_SETMUXRRATIO);
	ssd1351_dat(0x7f);//7f
	send_cmd(SSD1351_COLORDEPTH);
	ssd1351_dat(0x70);                               // Bit 7:6 = 65,536 Colors, Bit 3 = BGR or RGB
	send_cmd(SSD1351_SETCOLUMNADDRESS);
	ssd1351_dat(0x00);
	ssd1351_dat(0x7F); //7f
	send_cmd(SSD1351_SETROWADDRESS);
	ssd1351_dat(0x00);
	ssd1351_dat(0x7F);  // 7f
	send_cmd(SSD1351_SETDISPLAYSTARTLINE);
	ssd1351_dat(0x00);
	send_cmd(SSD1351_SETDISPLAYOFFSET);
	ssd1351_dat(0x00);
	send_cmd(SSD1351_SETGPIO);
	ssd1351_dat(0x00);                               // Disable GPIO pins
	send_cmd(SSD1351_FUNCTIONSELECTION);
	ssd1351_dat(0x01);                               // External VDD (0 = External, 1 = Internal)
	send_cmd(SSD1351_SETPHASELENGTH);
	ssd1351_dat(0x32);
	send_cmd(SSD1351_SETSEGMENTLOWVOLTAGE);
	ssd1351_dat(0xA0);                               // Enable External VSL
	ssd1351_dat(0xB5);
	ssd1351_dat(0x55);
	send_cmd(SSD1351_SETPRECHARGEVOLTAGE);
	ssd1351_dat(0x17);
	send_cmd(SSD1351_SETVCOMHVOLTAGE);
	ssd1351_dat(0x05);
	send_cmd(SSD1351_SETCONTRAST);
	ssd1351_dat(0xC8);
	ssd1351_dat(0x80);
	ssd1351_dat(0xC8);
	send_cmd(SSD1351_MASTERCONTRAST);
	ssd1351_dat(0x0F);                               // Maximum contrast
	send_cmd(SSD1351_SETSECONDPRECHARGEPERIOD);
	ssd1351_dat(0x01);
	send_cmd(SSD1351_SETDISPLAYMODE_RESET);

  	// Clear screen
	oled_memory_size(0,127,0,127);
	for (int i=0;i<128*128; i++)
		oled_color(0x0000);

	// Turn the display on
	send_cmd(SSD1351_SLEEPMODE_DISPLAYON);  

}

// --- public methods ----

// init sequence for 96x96 SEPS114A color module
void oled_init(enum oled_versions version)
{
	// init gpio interface
	am335x_gpio_init (AM335X_GPIO0);
	am335x_gpio_init (AM335X_GPIO1);
/*
	am335x_gpio_setup_pin_in (EN_GPIO,  EN_PIN,  AM335X_GPIO_PULL_NONE, false);
	am335x_gpio_setup_pin_in (RW_GPIO,  RW_PIN,  AM335X_GPIO_PULL_NONE, false);
	am335x_gpio_setup_pin_in (RST_GPIO, RST_PIN, AM335X_GPIO_PULL_NONE, false);
	am335x_gpio_setup_pin_in (DC_GPIO,  DC_PIN,  AM335X_GPIO_PULL_NONE, false);
	bool en  = am335x_gpio_get_state (EN_GPIO,   EN_PIN);
	bool rw  = am335x_gpio_get_state (RW_GPIO,   RW_PIN);
	bool rst = am335x_gpio_get_state (RST_GPIO,  RST_PIN);
	bool dc  = am335x_gpio_get_state (DC_GPIO,   DC_PIN);

	printf ("\n\nen=%d, rw=%d, rst=%d, dc=%d\n\n", en, rw, rst, dc);
*/
	am335x_gpio_setup_pin_out (EN_GPIO,  EN_PIN,  true);
	delay_ms(100);
	am335x_gpio_setup_pin_out (RW_GPIO,  RW_PIN,  false);
	am335x_gpio_setup_pin_out (RST_GPIO, RST_PIN, true);
	am335x_gpio_setup_pin_out (DC_GPIO,  DC_PIN,  false);


	// SEPS114A hard reset
	delay_ms(40);
	am335x_gpio_change_state (RST_GPIO, RST_PIN, false);
	delay_ms(40);
	am335x_gpio_change_state (RST_GPIO, RST_PIN, true);
	delay_ms(300);

	if (version == OLED_V101) {
		oled_device = SSD1351;
		spi_init (2000000);
		ssd1351_init();
	} else {
		oled_device = SEPS114A;
		spi_init (20000000);
		seps114a_init();
	}
}


// set memory area(address) to write a display data
void oled_memory_size(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2)
{
	if (oled_device == SSD1351) {
		ssd1351_set_area  (x1, x2, y1, y2);
	} else {
		seps114a_set_area (x1, x2, y1, y2);
	}
}

// send color for 1 pixel
void oled_color(uint32_t color)
{
	uint32_t data[2] = {color>>8, color&0xff};
	send_data(data, 2);
}

// send image
void oled_send_image(struct pixel* image, uint32_t nb_pixels)
{
	send_data (&image[0].hword, nb_pixels*2);
}

// test
void oled_test (int(*delay)(unsigned))
{
	if (delay==0) delay = delay_ms;

	for(int i=0;i<8;i++) {
		send_cmd_val (SEPS114A_SCREEN_SAVER_MODE, i);
		send_cmd_val (SEPS114A_SCREEN_SAVER_CONTROL, 0x88);
		delay(500);
		send_cmd_val (SEPS114A_SCREEN_SAVER_CONTROL, 0x00);
	}
}


