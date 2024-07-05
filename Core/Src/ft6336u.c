/*
 * ft6336u.c
 *
 *  Created on: Jul 4, 2024
 *      Author: user
 */

#include "ft6336u.h"

//private:
//static int8_t sda = -1;
//static int8_t scl = -1;
//static uint8_t rst_n = -1;
//static uint8_t int_n = -1;

static bool readByte(uint8_t addr, uint8_t *p_data, uint32_t length);
static bool writeByte(uint8_t addr, uint8_t data);

static FT6336U_TouchPointType touchPoint;

void ft6336u_init(void) {
	/* Power on sequence FT6336U 3.5 */
	HAL_Delay(3);	// Power On rise time

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = LCD_TP_INT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(LCD_TP_INT_GPIO_Port, &GPIO_InitStruct);

//	HAL_GPIO_WritePin(LCD_TP_INT_GPIO_Port, LCD_TP_INT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_TP_RESET_GPIO_Port, LCD_TP_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);	// Min 1ms
	HAL_GPIO_WritePin(LCD_TP_RESET_GPIO_Port, LCD_TP_RESET_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LCD_TP_INT_GPIO_Port, LCD_TP_INT_Pin, GPIO_PIN_SET);

	HAL_Delay(500);
}

uint8_t ft6336u_read_device_mode(void) {
	uint8_t retVal;
	readByte(FT6336U_ADDR_DEVICE_MODE, &retVal, 1);
//	retVal = ((retVal & 0x70) >> 4);
//    return retVal;
    return ((retVal & 0x70) >> 4);
}

void ft6336u_write_device_mode(DEVICE_MODE_Enum mode) {
    writeByte(FT6336U_ADDR_DEVICE_MODE, ((mode & 0x07) << 4));
}

uint8_t ft6336u_read_gesture_id(void) {
	uint8_t retVal;
	readByte(FT6336U_ADDR_GESTURE_ID, &retVal, 1);
    return retVal;
}

uint8_t ft6336u_read_td_status(void) {
	uint8_t retVal;
	readByte(FT6336U_ADDR_TD_STATUS, &retVal, 1);
    return retVal;
}

uint8_t ft6336u_read_touch_number(void) {
	uint8_t retVal;
	readByte(FT6336U_ADDR_TD_STATUS, &retVal, 1);
	retVal = (retVal & 0x0F);
    return retVal;
}

// Touch 1 functions
uint16_t ft6336u_read_touch1_x(void) {
    uint8_t read_buf[2];

    readByte(FT6336U_ADDR_TOUCH1_X, read_buf, 2);

    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}

uint16_t ft6336u_read_touch1_y(void) {
    uint8_t read_buf[2];

    readByte(FT6336U_ADDR_TOUCH1_Y, read_buf, 2);

    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}

uint8_t ft6336u_read_touch1_event(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH1_EVENT, &retVal, 1);

    return (retVal >> 6);
}

uint8_t ft6336u_read_touch1_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH1_ID, &retVal, 1);

	return (retVal >> 4);
}

uint8_t ft6336u_read_touch1_weight(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH1_WEIGHT, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_touch1_misc(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH1_MISC, &retVal, 1);

	return (retVal >> 4);
}

// Touch 2 functions
uint16_t ft6336u_read_touch2_x(void) {
    uint8_t read_buf[2];

    readByte(FT6336U_ADDR_TOUCH2_X, read_buf, 2);

    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}

uint16_t ft6336u_read_touch2_y(void) {
    uint8_t read_buf[2];

    readByte(FT6336U_ADDR_TOUCH2_Y, read_buf, 2);

    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}

uint8_t ft6336u_read_touch2_event(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH2_EVENT, &retVal, 1);

	return (retVal >> 6);
}

uint8_t ft6336u_read_touch2_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH2_ID, &retVal, 1);

	return (retVal >> 4);
}

uint8_t ft6336u_read_touch2_weight(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH2_WEIGHT, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_touch2_misc(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TOUCH2_MISC, &retVal, 1);

	return (retVal >> 4);
}

// Mode Parameter Register
uint8_t ft6336u_read_touch_threshold(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_THRESHOLD, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_filter_coefficient(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_FILTER_COE, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_ctrl_mode(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_CTRL, &retVal, 1);

	return retVal;
}

void ft6336u_write_ctrl_mode(CTRL_MODE_Enum mode) {
    writeByte(FT6336U_ADDR_CTRL, mode);
}

uint8_t ft6336u_read_time_period_enter_monitor(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_TIME_ENTER_MONITOR, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_active_rate(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_ACTIVE_MODE_RATE, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_monitor_rate(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_MONITOR_MODE_RATE, &retVal, 1);

	return retVal;
}

// Gesture Parameters
uint8_t ft6336u_read_radian_value(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_RADIAN_VALUE, &retVal, 1);

	return retVal;
}

void ft6336u_write_radian_value(uint8_t val) {
    writeByte(FT6336U_ADDR_RADIAN_VALUE, val);
}

uint8_t ft6336u_read_offset_left_right(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_OFFSET_LEFT_RIGHT, &retVal, 1);

	return retVal;
}

void ft6336u_write_offset_left_right(uint8_t val) {
    writeByte(FT6336U_ADDR_OFFSET_LEFT_RIGHT, val);
}

uint8_t ft6336u_read_offset_up_down(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_OFFSET_UP_DOWN, &retVal, 1);

	return retVal;
}

void ft6336u_write_offset_up_down(uint8_t val) {
    writeByte(FT6336U_ADDR_OFFSET_UP_DOWN, val);
}

uint8_t ft6336u_read_distance_left_right(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_DISTANCE_LEFT_RIGHT, &retVal, 1);

	return retVal;
}

void ft6336u_write_distance_left_right(uint8_t val) {
    writeByte(FT6336U_ADDR_DISTANCE_LEFT_RIGHT, val);
}

uint8_t ft6336u_read_distance_up_down(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_DISTANCE_UP_DOWN, &retVal, 1);

	return retVal;
}

void ft6336u_write_distance_up_down(uint8_t val) {
    writeByte(FT6336U_ADDR_DISTANCE_UP_DOWN, val);
}

uint8_t ft6336u_read_distance_zoom(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_DISTANCE_ZOOM, &retVal, 1);

	return retVal;
}

void ft6336u_write_distance_zoom(uint8_t val) {
    writeByte(FT6336U_ADDR_DISTANCE_ZOOM, val);
}

// System Information
uint16_t ft6336u_read_library_version(void) {
    uint8_t read_buf[2];

    readByte(FT6336U_ADDR_LIBRARY_VERSION_H, read_buf, 2);

    return ((read_buf[0] & 0x0f) << 8) | read_buf[1];
}

uint8_t ft6336u_read_chip_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_CHIP_ID, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_g_mode(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_G_MODE, &retVal, 1);

	return retVal;
}

void ft6336u_write_g_mode(G_MODE_Enum mode){
    writeByte(FT6336U_ADDR_G_MODE, mode);
}

uint8_t ft6336u_read_pwrmode(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_POWER_MODE, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_firmware_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_FIRMARE_ID, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_focaltech_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_FOCALTECH_ID, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_release_code_id(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_RELEASE_CODE_ID, &retVal, 1);

	return retVal;
}

uint8_t ft6336u_read_state(void) {
	uint8_t retVal;

	readByte(FT6336U_ADDR_STATE, &retVal, 1);

	return retVal;
}

//coordinate diagram（FPC downwards）
////y ////////////////////264x176
                        //
                        //
                        //x
                        //
                        //
FT6336U_TouchPointType ft6336u_scan(void){
    touchPoint.touch_count = ft6336u_read_td_status();

    if(touchPoint.touch_count == 0) {
        touchPoint.tp[0].status = release;
        touchPoint.tp[1].status = release;
    }
    else if(touchPoint.touch_count == 1) {
        uint8_t id1 = ft6336u_read_touch1_id(); // id1 = 0 or 1
        touchPoint.tp[id1].status = (touchPoint.tp[id1].status == release) ? touch : stream;
        touchPoint.tp[id1].x = ft6336u_read_touch1_x();
        touchPoint.tp[id1].y = ft6336u_read_touch1_y();
        touchPoint.tp[~id1 & 0x01].status = release;
    }
    else {
        uint8_t id1 = ft6336u_read_touch1_id(); // id1 = 0 or 1
        touchPoint.tp[id1].status = (touchPoint.tp[id1].status == release) ? touch : stream;
        touchPoint.tp[id1].x = ft6336u_read_touch1_x();
        touchPoint.tp[id1].y = ft6336u_read_touch1_y();
        uint8_t id2 = ft6336u_read_touch2_id(); // id2 = 0 or 1(~id1 & 0x01)
        touchPoint.tp[id2].status = (touchPoint.tp[id2].status == release) ? touch : stream;
        touchPoint.tp[id2].x = ft6336u_read_touch2_x();
        touchPoint.tp[id2].y = ft6336u_read_touch2_y();
    }

    return touchPoint;

}

// Private Function
bool readByte(uint8_t addr, uint8_t *p_data, uint32_t length) {

	bool ret;
    HAL_StatusTypeDef i2c_ret;
    do {
    	i2c_ret = HAL_I2C_Mem_Read(&hi2c1, (I2C_ADDR_FT6336U << 1), addr, I2C_MEMADD_SIZE_8BIT, p_data, length, 1000);
    	if(i2c_ret == HAL_OK)
    		ret = true;
    	else
    		ret = false;
    } while(!ret);

    return ret;
}

bool writeByte(uint8_t addr, uint8_t data) {
    DEBUG_PRINT("\r\n")
    DEBUG_PRINT("writeI2C reg 0x%2x -> 0x%2x\r\n", addr, data)

	bool ret;
    HAL_StatusTypeDef i2c_ret;

    i2c_ret = HAL_I2C_Mem_Write(&hi2c1, (I2C_ADDR_FT6336U << 1), addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&data, 1, 100);

    if(i2c_ret == HAL_OK)
      ret = true;
    else
      ret = false;

    return ret;
}
