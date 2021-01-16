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

data currentData;
data settingMin;
data settingMax;

void data_settingInit(){
	settingMin.humid = 50.00;
	settingMin.temp = 18.00;
	settingMax.humid = 70.00;
	settingMax.temp = 30.00;
}

void data_settingSave(){
	EE_WriteVariable(MIN_HUM_ADDR,  100*settingMin.humid);
	EE_WriteVariable(MAX_HUM_ADDR, 100*settingMax.humid);
	EE_WriteVariable(MIN_TEMP_ADDR, 100*settingMin.temp);
	EE_WriteVariable(MAX_TEMP_ADDR, 100*settingMax.temp);
}

void data_settingLoad(){
	uint16_t buf;
	EE_ReadVariable(MIN_HUM_ADDR, &buf);
	settingMin.humid = (float) buf/100.0;

	EE_ReadVariable(MAX_HUM_ADDR, &buf);
	settingMax.humid = (float) buf/100.0;

	EE_ReadVariable(MIN_TEMP_ADDR, &buf);
	settingMin.temp = (float) buf/100.0;

	EE_ReadVariable(MAX_TEMP_ADDR, &buf);
	settingMax.temp = (float) buf/100.0;
}

void data_settingEnter(){
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
	settingMin.humid = s;
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
	settingMax.humid = s;
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
	settingMin.temp = s;
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
	settingMax.temp = s;
	usart_send_string("Settings saved.");
}

void data_settingPrint(){
	lcd_clear(&disp);
	char buf[3];

	sprintf(buf,"%f",settingMin.humid);
	sprintf((char *)disp.f_line,"Min. hum:");
	strncat((char *)disp.f_line,buf,5);

	sprintf(buf,"%f",settingMax.humid);
	sprintf((char *)disp.s_line,"Max. hum:");
	strncat((char *)disp.s_line,buf,5);

	lcd_display(&disp);
	HAL_Delay(5000);
	lcd_clear(&disp);

	sprintf(buf,"%f",settingMin.temp);
	sprintf((char *)disp.f_line,"Min. temp:");
	strncat((char *)disp.f_line,buf,5);

	sprintf(buf,"%f",settingMax.temp);
	sprintf((char *)disp.s_line,"Max. temp:");
	strncat((char *)disp.s_line,buf,5);

	lcd_display(&disp);
	HAL_Delay(5000);
	lcd_clear(&disp);
}

void data_get(){
	hts221_readHumid(&(currentData.humid));
	hts221_readTemp(&(currentData.temp));
	currentData.soil = convertMoisture(s);
}

char* convertMoisture(uint32_t adc_data){
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

void data_print(struct lcd_disp *disp){
	char arr1[5];
	char arr2[5];
	char zeros[8] = "        ";
	gcvt(currentData.humid,4,arr1);
	gcvt(currentData.temp,4,arr2);

	sprintf((char *)disp->f_line, "H:");
	strncat(disp->f_line, arr1,5);
	strncat(disp->f_line,"  T:",4);
	strncat(disp->f_line,arr2,5);
	sprintf((char *)disp->s_line, "Soil: ");
	strncat(disp->s_line,currentData.soil,strlen(currentData.soil));
	strncat(disp->s_line,zeros,16-6-strlen(currentData.soil));
	usart_send_string("Hum: ");
	usart_send_string(arr1);
	usart_send_string("    Temp: ");
	usart_send_string(arr2);
	usart_send_string("    Soil: ");
	usart_send_string(currentData.soil);
	usart_send_string("\n\r");
}

void data_printAlert(int e, struct lcd_disp *disp){
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

uint8_t data_check(){
	if(currentData.temp > settingMax.temp)
		return S_HIGHTEMP;
	if(currentData.temp < settingMin.temp)
		return S_LOWTEMP;
	if(currentData.humid > settingMax.humid)
		return S_HIGHHUM;
	if(currentData.humid < settingMin.humid)
		return S_LOWHUM;
	return S_OK;
}
