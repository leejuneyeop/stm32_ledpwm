/*
 * app.c
 *
 *  Created on: Jan 17, 2025
 *      Author: com
 */

#include "app.h"
#include "math.h"

// 장치 선언
extern TIM_HandleTypeDef htim1;



// tim1의 Duty 변경
void setDuty (uint8_t r, uint8_t g, uint8_t b){
	//instance 실제 객체의 위치 (포인터 구조체)/ CCR1: 채널1의 Counter Compare Register /CNT: 카운터 그 자체
	htim1.Instance->CCR1 = (r)*10;
	htim1.Instance->CCR2 = (g)*10;
	htim1.Instance->CCR3 = (b)*10;

}

void app(){
	// 타이머 장치 시작
	// xxx: 장치 종류 (HAL_TIM_XXX_Start)
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);


	while(1){
		static int angleR =0;
		static int angleG =120;
		static int angleB =240;
		angleR ++;
		angleG ++;
		angleB ++;
		angleR %=360; //angle이 360되면 0으로 바꾸라는 일종의 조건문
		angleG %=360; //angle이 360되면 0으로 바꾸라는 일종의 조건문
		angleB %=360; //angle이 360되면 0으로 바꾸라는 일종의 조건문
		uint8_t valueR = sin(angleR * M_PI/180)*50 +49;
		uint8_t valueG = sin(angleG * M_PI/180)*50 +49;
		uint8_t valueB = sin(angleB * M_PI/180)*50 +49;
		setDuty(valueR, valueG, valueB);
		HAL_Delay(10);
	}


}
