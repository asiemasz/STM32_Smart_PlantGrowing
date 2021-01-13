/*
 * sensors.c
 *
 *  Created on: 5 lis 2020
 *      Author: pajcz
 */
#include "sensors.h"

const uint8_t dry_val = 20;
const uint8_t wet_val = 160;
uint8_t intervals;

data current_data;
data setting_min;
data setting_max;

void data_setting_init(){
	setting_min.humid = 50.00;
	setting_min.temp = 18.00;
	setting_max.humid = 70.00;
	setting_max.temp = 30.00;
}

void data_setting_save(){
	EE_WriteVariable(MIN_HUM_ADDR, (uint16_t) setting_min.humid);
	EE_WriteVariable(MAX_HUM_ADDR, (uint16_t) setting_max.humid);
	EE_WriteVariable(MIN_TEMP_ADDR, (uint16_t) setting_min.temp);
	EE_WriteVariable(MAX_TEMP_ADDR, (uint16_t) setting_max.temp);
}

void data_setting_load(){
	uint16_t buf;
	EE_ReadVariable(MIN_HUM_ADDR, &buf);
	setting_min.humid = (float) buf;

	EE_ReadVariable(MAX_HUM_ADDR, &buf);
	setting_max.humid = (float) buf;

	EE_ReadVariable(MIN_TEMP_ADDR, &buf);
	setting_min.temp = (float) buf;

	EE_ReadVariable(MAX_TEMP_ADDR, &buf);
	setting_max.temp = (float) buf;
}

void data_setting_enter(){
	float s=0;
	char buf[2];
	uint8_t key;
	sprintf((char *)disp.f_line,"Enter settings! ");
	sprintf((char *)disp.s_line,"                ");
	usart_send_string("Setting mode...");
	lcd_display(&disp);
	HAL_Delay(2000);
	lcd_clear(&disp);

	int i;

	sprintf((char *)disp.f_line,"Min. humid.: ");
	sprintf((char *)disp.s_line,"");
	lcd_display(&disp);
	for(i=0 ; i<4 ; i++){
		key = kb_service();
		sprintf(buf,"%d",key);
		strncat(disp.s_line,buf,1);
		if(i==1)
			strncat(disp.s_line,".",1);
		lcd_display(&disp);
		s += 10.0/powf(10.0,(float)i) * (float)key;
		HAL_Delay(100);
	}
	lcd_clear(&disp);
	setting_min.humid = s;
	s=0;

	sprintf((char *)disp.f_line,"Max. humid.: ");
	sprintf((char *)disp.s_line,"");
	lcd_display(&disp);
	for(i=0 ; i<4 ; i++){
		key = kb_service();
		sprintf(buf,"%d",key);
		strncat(disp.s_line,buf,1);
		if(i==1)
			strncat(disp.s_line,".",1);
		lcd_display(&disp);
		s += 10.0/powf(10.0,(float)i) * (float)key;
		HAL_Delay(100);
	}
	lcd_clear(&disp);
	setting_max.humid = s;
	s=0;

	sprintf((char *)disp.f_line,"Min. temp.: ");
	sprintf((char *)disp.s_line,"");
	lcd_display(&disp);
	for(i=0 ; i<4 ; i++){
		key = kb_service();
		sprintf(buf,"%d",key);
		strncat(disp.s_line,buf,1);
		if(i==1)
			strncat(disp.s_line,".",1);
		lcd_display(&disp);
		s += 10.0/powf(10.0,(float)i) * (float)key;
		HAL_Delay(100);
	}
	lcd_clear(&disp);
	setting_min.temp = s;
	s=0;

	sprintf((char *)disp.f_line,"Max. temp.: ");
	sprintf((char *)disp.s_line,"");
	lcd_display(&disp);
	for(i=0 ; i<4 ; i++){
		key = kb_service();
		sprintf(buf,"%d",key);
		strncat(disp.s_line,buf,1);
		if(i==1)
			strncat(disp.s_line,".",1);
		lcd_display(&disp);
		s += 10.0/powf(10.0,(float)i) * (float)key;
		HAL_Delay(100);
	}
	lcd_clear(&disp);
	setting_max.temp = s;
	usart_send_string("Settings saved.");
}

void data_setting_print(){
	lcd_clear(&disp);
	char buf[3];

	sprintf(buf,"%f",setting_min.humid);
	sprintf((char *)disp.f_line,"Min. hum:");
	strncat((char *)disp.f_line,buf,5);

	sprintf(buf,"%f",setting_max.humid);
	sprintf((char *)disp.s_line,"Max. hum:");
	strncat((char *)disp.s_line,buf,5);

	lcd_display(&disp);
	HAL_Delay(5000);
	lcd_clear(&disp);

	sprintf(buf,"%f",setting_min.temp);
	sprintf((char *)disp.f_line,"Min. temp:");
	strncat((char *)disp.f_line,buf,5);

	sprintf(buf,"%f",setting_max.temp);
	sprintf((char *)disp.s_line,"Max. temp:");
	strncat((char *)disp.s_line,buf,5);

	lcd_display(&disp);
	HAL_Delay(5000);
	lcd_clear(&disp);
}

void get_data(){
	hts221_read_humid(&(current_data.humid));
	hts221_read_temp(&(current_data.temp));
	current_data.soil = convert_moisture(s);
}

char* convert_moisture(uint32_t adc_data){
	intervals = (wet_val-dry_val)/4;
	if(adc_data < intervals)
		return "dry";
	else if(adc_data >= intervals && adc_data < 2*intervals)
		return "little wet";
	else if(adc_data>= 2*intervals && adc_data < 3*intervals)
		return "wet";
	else
		return "very wet";
}

void print_data(struct lcd_disp *disp){
	char arr1[5];
	char arr2[5];
	char zeros[8] = "        ";
	gcvt(current_data.humid,4,arr1);
	gcvt(current_data.temp,4,arr2);

	sprintf((char *)disp->f_line, "H:");
	strncat(disp->f_line, arr1,5);
	strncat(disp->f_line,"  T:",4);
	strncat(disp->f_line,arr2,5);
	sprintf((char *)disp->s_line, "Soil: ");
	strncat(disp->s_line,current_data.soil,strlen(current_data.soil));
	strncat(disp->s_line,zeros,16-6-strlen(current_data.soil));
	usart_send_string("Hum: ");
	usart_send_string(arr1);
	usart_send_string("    Temp: ");
	usart_send_string(arr2);
	usart_send_string("    Soil: ");
	usart_send_string(current_data.soil);
	usart_send_string("\n\r");
}

void print_alert(int e, struct lcd_disp *disp){
	sprintf((char *)disp->f_line, "ALERT!          ");
	switch(e){
	case S_HIGHTEMP:
		sprintf((char *)disp->s_line,"Temp too high!  "); break;
	case S_LOWTEMP:
		sprintf((char *)disp->s_line,"Temp too low!  "); break;
	case S_HIGHHUM:
		sprintf((char *)disp->s_line, "Hum too high!   "); break;
	case S_LOWHUM:
		sprintf((char *)disp->s_line, "Hum too low!   "); break;
	}
	usart_send_string(disp->f_line);
	usart_send_string(disp->s_line);
	usart_send_string("\n\r");
}

uint8_t check_data(){
	if(current_data.temp > setting_max.temp)
		return S_HIGHTEMP;
	if(current_data.temp < setting_min.temp)
		return S_LOWTEMP;
	if(current_data.humid > setting_max.humid)
		return S_HIGHHUM;
	if(current_data.humid < setting_min.humid)
		return S_LOWHUM;
	return S_OK;
}
