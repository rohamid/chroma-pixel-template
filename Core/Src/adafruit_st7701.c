/*
 * adafruit_st7701.c
 *
 *  Created on: Jul 4, 2024
 *      Author: user
 */

#include "st7701.h"
#include "spi.h"


//static bool st7701WriteCmd(uint8_t data);
//static bool st7701WriteData(uint8_t data);
//static bool st7701InitRegs(void);

static bool SPI_WriteData(uint8_t data);
static bool SPI_WriteComm(uint8_t data);
static bool st7701_init_regs(void);

bool st7701_init(void)
{
	st7701_init_regs();
	return true;
}

bool st7701_init_regs(void)
{

	SPI_WriteData(0x08);
	SPI_WriteData(0x08);
	SPI_WriteData(0x22);
	SPI_WriteData(0x04);
	SPI_WriteData(0x11);
	SPI_WriteData(0x11);
	SPI_WriteData(0xA9);
	SPI_WriteData(0x32);
	SPI_WriteData(0x18);

	//PAGE1
	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x11);


	SPI_WriteComm(0xB0);    SPI_WriteData(0x60); //Vop=4.7375v

	SPI_WriteComm(0xB1);    SPI_WriteData(0x32); //VCOM=32

	SPI_WriteComm(0xB2);    SPI_WriteData(0x07); //VGH=15v

	SPI_WriteComm(0xB3);    SPI_WriteData(0x80);

	SPI_WriteComm(0xB5);    SPI_WriteData(0x49); //VGL=-10.17v

	SPI_WriteComm(0xB7);    SPI_WriteData(0x85);

	SPI_WriteComm(0xB8);    SPI_WriteData(0x21); //AVDD=6.6 & AVCL=-4.6

	SPI_WriteComm(0xC1);    SPI_WriteData(0x78);

	SPI_WriteComm(0xC2);    SPI_WriteData(0x78);

	SPI_WriteComm(0xE0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x1B);
	SPI_WriteData(0x02);

	SPI_WriteComm(0xE1);
	SPI_WriteData(0x08);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x07);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x44);
	SPI_WriteData(0x44);



	SPI_WriteComm(0xE2);
	SPI_WriteData(0x11);
	SPI_WriteData(0x11);
	SPI_WriteData(0x44);
	SPI_WriteData(0x44);
	SPI_WriteData(0xED);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0xEC);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);


	SPI_WriteComm(0xE3);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x11);
	SPI_WriteData(0x11);


	SPI_WriteComm(0xE4);
	SPI_WriteData(0x44);
	SPI_WriteData(0x44);

	SPI_WriteComm(0xE5);
	SPI_WriteData(0x0A);
	SPI_WriteData(0xE9);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x0C);
	SPI_WriteData(0xEB);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x0E);
	SPI_WriteData(0xED);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x10);
	SPI_WriteData(0xEF);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);




	SPI_WriteComm(0xE6);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x11);
	SPI_WriteData(0x11);

	SPI_WriteComm(0xE7);
	SPI_WriteData(0x44);
	SPI_WriteData(0x44);


	SPI_WriteComm(0xE8);
	SPI_WriteData(0x09);
	SPI_WriteData(0xE8);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x0B);
	SPI_WriteData(0xEA);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x0D);
	SPI_WriteData(0xEC);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x0F);
	SPI_WriteData(0xEE);
	SPI_WriteData(0xD8);
	SPI_WriteData(0xA0);


	SPI_WriteComm(0xEB);
	SPI_WriteData(0x02);
	SPI_WriteData(0x00);
	SPI_WriteData(0xE4);
	SPI_WriteData(0xE4);
	SPI_WriteData(0x88);
	SPI_WriteData(0x00);
	SPI_WriteData(0x40);


	SPI_WriteComm(0xEC);
	SPI_WriteData(0x3C);
	SPI_WriteData(0x00);


	SPI_WriteComm(0xED);
	SPI_WriteData(0xAB);
	SPI_WriteData(0x89);
	SPI_WriteData(0x76);
	SPI_WriteData(0x54);
	SPI_WriteData(0x02);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0x20);
	SPI_WriteData(0x45);
	SPI_WriteData(0x67);
	SPI_WriteData(0x98);
	SPI_WriteData(0xBA);

	SPI_WriteComm(0x36);
	SPI_WriteData(0x00);


	//-----------VAP & VAN---------------
	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x13);

	SPI_WriteComm(0xE5);
	SPI_WriteData(0xE4);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0x50);	// 0x3a
	SPI_WriteData(0x66);
	SPI_WriteComm(0x21);
	HAL_Delay(1);
	SPI_WriteComm(0x11);
	HAL_Delay(120);
	SPI_WriteComm(0x29);

	bool ret;

	ret = SPI_WriteComm(0x29);   //Display On
	HAL_Delay(50);

	return ret;

//	//PAGE1
//  st7701WriteCmd(0xFF);
//  st7701WriteData(0x77);
//  st7701WriteData(0x01);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x10);
//
//  st7701WriteCmd(0xC0);
//  st7701WriteData(0x3B);
//  st7701WriteData(0x00);
//
//  st7701WriteCmd(0xC1);
//  st7701WriteData(0x0D);
//  st7701WriteData(0x02);
//
//  st7701WriteCmd(0xC2);
//  st7701WriteData(0x31);
//  st7701WriteData(0x05);
//
//  st7701WriteCmd(0xCD);
//  st7701WriteData(0x08);
//
//  st7701WriteCmd(0xB0);
//  st7701WriteData(0x00); //Positive Voltage Gamma Control
//  st7701WriteData(0x11);
//  st7701WriteData(0x18);
//  st7701WriteData(0x0E);
//  st7701WriteData(0x11);
//  st7701WriteData(0x06);
//  st7701WriteData(0x07);
//  st7701WriteData(0x08);
//  st7701WriteData(0x07);
//  st7701WriteData(0x22);
//  st7701WriteData(0x04);
//  st7701WriteData(0x12);
//  st7701WriteData(0x0F);
//  st7701WriteData(0xAA);
//  st7701WriteData(0x31);
//  st7701WriteData(0x18);
//
//  st7701WriteCmd(0xB1);
//  st7701WriteData(0x00); //Negative Voltage Gamma Control
//  st7701WriteData(0x11);
//  st7701WriteData(0x19);
//  st7701WriteData(0x0E);
//  st7701WriteData(0x12);
//  st7701WriteData(0x07);
//  st7701WriteData(0x08);
//  st7701WriteData(0x08);
//  st7701WriteData(0x08);
//  st7701WriteData(0x22);
//  st7701WriteData(0x04);
//  st7701WriteData(0x11);
//  st7701WriteData(0x11);
//  st7701WriteData(0xA9);
//  st7701WriteData(0x32);
//  st7701WriteData(0x18);
//
//  //PAGE1
//  st7701WriteCmd(0xFF);
//  st7701WriteData(0x77);
//  st7701WriteData(0x01);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x11);
//
//  st7701WriteCmd(0xB0);    st7701WriteData(0x60); //Vop=4.7375v
//  st7701WriteCmd(0xB1);    st7701WriteData(0x32); //VCOM=32
//  st7701WriteCmd(0xB2);    st7701WriteData(0x07); //VGH=15v
//  st7701WriteCmd(0xB3);    st7701WriteData(0x80);
//  st7701WriteCmd(0xB5);    st7701WriteData(0x49); //VGL=-10.17v
//  st7701WriteCmd(0xB7);    st7701WriteData(0x85);
//  st7701WriteCmd(0xB8);    st7701WriteData(0x21); //AVDD=6.6 & AVCL=-4.6
//  st7701WriteCmd(0xC1);    st7701WriteData(0x78);
//  st7701WriteCmd(0xC2);    st7701WriteData(0x78);
//
//  st7701WriteCmd(0xE0);
//  st7701WriteData(0x00);
//  st7701WriteData(0x1B);
//  st7701WriteData(0x02);
//
//  st7701WriteCmd(0xE1);
//  st7701WriteData(0x08);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x07);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x44);
//  st7701WriteData(0x44);
//
//  st7701WriteCmd(0xE2);
//  st7701WriteData(0x11);
//  st7701WriteData(0x11);
//  st7701WriteData(0x44);
//  st7701WriteData(0x44);
//  st7701WriteData(0xED);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0xEC);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//
//  st7701WriteCmd(0xE3);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x11);
//  st7701WriteData(0x11);
//
//  st7701WriteCmd(0xE4);
//  st7701WriteData(0x44);
//  st7701WriteData(0x44);
//
//  st7701WriteCmd(0xE5);
//  st7701WriteData(0x0A);
//  st7701WriteData(0xE9);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x0C);
//  st7701WriteData(0xEB);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x0E);
//  st7701WriteData(0xED);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x10);
//  st7701WriteData(0xEF);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//
//  st7701WriteCmd(0xE6);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x11);
//  st7701WriteData(0x11);
//
//  st7701WriteCmd(0xE7);
//  st7701WriteData(0x44);
//  st7701WriteData(0x44);
//
//  st7701WriteCmd(0xE8);
//  st7701WriteData(0x09);
//  st7701WriteData(0xE8);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x0B);
//  st7701WriteData(0xEA);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x0D);
//  st7701WriteData(0xEC);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//  st7701WriteData(0x0F);
//  st7701WriteData(0xEE);
//  st7701WriteData(0xD8);
//  st7701WriteData(0xA0);
//
//  st7701WriteCmd(0xEB);
//  st7701WriteData(0x02);
//  st7701WriteData(0x00);
//  st7701WriteData(0xE4);
//  st7701WriteData(0xE4);
//  st7701WriteData(0x88);
//  st7701WriteData(0x00);
//  st7701WriteData(0x40);
//
//  st7701WriteCmd(0xEC);
//  st7701WriteData(0x3C);
//  st7701WriteData(0x00);
//
//  st7701WriteCmd(0xED);
//  st7701WriteData(0xAB);
//  st7701WriteData(0x89);
//  st7701WriteData(0x76);
//  st7701WriteData(0x54);
//  st7701WriteData(0x02);
//  st7701WriteData(0xFF);
//  st7701WriteData(0xFF);
//  st7701WriteData(0xFF);
//  st7701WriteData(0xFF);
//  st7701WriteData(0xFF);
//  st7701WriteData(0xFF);
//  st7701WriteData(0x20);
//  st7701WriteData(0x45);
//  st7701WriteData(0x67);
//  st7701WriteData(0x98);
//  st7701WriteData(0xBA);
//
//  st7701WriteCmd(0x36);
//  st7701WriteData(0x00);
//
//  //-----------VAP & VAN---------------
//  st7701WriteCmd(0xFF);
//  st7701WriteData(0x77);
//  st7701WriteData(0x01);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x13);
//
//  st7701WriteCmd(0xE5);
//  st7701WriteData(0xE4);
//
//  st7701WriteCmd(0xFF);
//  st7701WriteData(0x77);
//  st7701WriteData(0x01);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//  st7701WriteData(0x00);
//
//
//	SPI_WriteComm(0x3a);
//	SPI_WriteData(0x66);
//	SPI_WriteComm(0x21);
//	HAL_Delay(1);
//	SPI_WriteComm(0x11);
//	HAL_Delay(120);
//	SPI_WriteComm(0x29);
//
//  st7701WriteCmd(0x3A);   //0x70 RGB888, 0x60 RGB666, 0x50 RGB565
//  st7701WriteData(0x60);
//
//  st7701WriteCmd(0x21);   //Display Inversion On
//
//  st7701WriteCmd(0x11);   //Sleep Out
//  HAL_Delay(100);
//
//  bool ret;
//
//  ret = st7701WriteCmd(0x29);   //Display On
//  HAL_Delay(50);
//
//  return ret;
}

bool SPI_WriteComm(uint8_t data)
{
  bool ret = true;
  uint16_t tx_data;

  HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_RESET);

  tx_data = (0<<8) | data;
  HAL_SPI_Transmit(&hspi5, (const uint8_t *)&tx_data, 1, 10);

  HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_SET);
  return ret;
}

bool SPI_WriteData(uint8_t data)
{
  bool ret = true;
  uint16_t tx_data;

  HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_RESET);

  tx_data = (1<<8) | data;
  HAL_SPI_Transmit(&hspi5, (const uint8_t *)&tx_data, 1, 10);

  HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_SET);
  return ret;
}

