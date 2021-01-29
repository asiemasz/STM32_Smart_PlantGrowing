/**
 * @file src/hts221_add.c
 * @brief This file provides functions to use HTS221 sensors
 */
/** @addtogroup COMPONENTS
  * @{
 */
/**
 * @addtogroup HTS221_ADD
 * @{
 */

#include "hts221_add.h"


/**
 * @brief Initialize hts221 sensors using library from ST X-CUBE-MEMS1 pack
 * @param None.
 * @retval Success or error status:
 * 		   - 0: BSP_ERROR_NONE - no error occured
 * 		   - -1: BSP_ERROR_NO_INIT - initialization failed
 * 		   - -2: BSP_ERROR_WRONG_PARAM - wrong parameter
 * 		   - -5: BSP_ERROR_COMPONENT_FAILURE - error during sensor work
 * 		   - -7: BSP_ERROR_UNKNOWN_COMPONENT - no component detected
 */
int32_t hts221_init(){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_Init(IKS01A2_HTS221_0, ENV_TEMPERATURE | ENV_HUMIDITY);
	return status;
}

/**
 * @brief Read temperature value from hts221 sensor.
 * @param temp: pointer to variable to store the temperature value
 * @retval Success or error status:
 * 		   - 0: BSP_ERROR_NONE - no error occured
 * 		   - -2: BSP_ERROR_WRONG_PARAM - wrong parameter
 * 		   - -5: BSP_ERROR_COMPONENT_FAILURE - error during sensor work
 */

int32_t hts221_readTemp(float *temp){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_GetValue(IKS01A2_HTS221_0, ENV_TEMPERATURE, temp);
	return status;
}

/**
 * @brief Read relative air humidity value from hts221 sensor.
 * @param temp: pointer to variable to store the humidity value
 * @retval Success or error status:
 * 		   - 0: BSP_ERROR_NONE - no error occured
 * 		   - -2: BSP_ERROR_WRONG_PARAM - wrong parameter
 * 		   - -5: BSP_ERROR_COMPONENT_FAILURE - error during sensor work
 */

int32_t hts221_readHumid(float *hum){
	int32_t status;
	status = IKS01A2_ENV_SENSOR_GetValue(IKS01A2_HTS221_0, ENV_HUMIDITY, hum);
	return status;
}
