/**
 * @file Energesis_Sensor.cpp
 * @author José Guerra Carmenate (joseguerracarmenate@gmail.com)
 * @brief Implementación de la clase Base Energesis_Sensor.
 * @version 0.3
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Arduino.h>
#include "Energesis_Sensor.h"

#define ENERGESIS_LANGUAGE_ES (1<<0)
#define ENERGESIS_LANGUAGE_EN (1<<1)

#ifndef ENERGESIS_LANGUAGE_SET
#define ENERGESIS_LANGUAGE_SET ENERGESIS_LANGUAGE_EN 
#endif


namespace Energesis{

inline const char* language_auto_select( const char *es, const char *en = NULL ){
#if ENERGESIS_LANGUAGE_SET == ENERGESIS_LANGUAGE_ES
  return es;
#elif ENERGESIS_LANGUAGE_SET == ENERGESIS_LANGUAGE_EN
  return en;
#endif
}


#if ENERGESIS_LANGUAGE_SET == ENERGESIS_LANGUAGE_ES
static const char *sensor_type_temperature  = "Temperatura",
                  *sensor_type_humidity     = "Humedad relativa",
                  *sensor_type_current      = "Corriente",
                  *sensor_type_voltaje      = "Voltaje",
                  *sensor_type_invalid      = "Tipo inválido";
#elif ENERGESIS_LANGUAGE_SET == ENERGESIS_LANGUAGE_EN

const char sensor_type_temperature[] PROGMEM = "Temperature";
const char sensor_type_humidity[] PROGMEM = "Relative Humidity";
const char sensor_type_current[] PROGMEM = "Current";
const char sensor_type_voltage[] PROGMEM = "Voltage";
const char sensor_type_on_off[] PROGMEM = "On/Off";
const char sensor_type_noise[] PROGMEM = "Noise";
const char sensor_type_acceleration[] PROGMEM = "Acceleration";
const char sensor_type_gyroscope[] PROGMEM = "Gyroscope";
const char sensor_type_gas[] PROGMEM = "Gas";
const char sensor_type_invalid[] PROGMEM = "Invalid Type";

// Array of strings in program memory
const char* const sensorTypeStrings[] PROGMEM = {
    sensor_type_temperature,
    sensor_type_humidity,
    sensor_type_current,
    sensor_type_voltage,
    sensor_type_on_off,
    sensor_type_noise,
    sensor_type_acceleration,
    sensor_type_gyroscope,
    sensor_type_gas,
};
#endif

void Energesis_Sensor::printSensorDetails( Stream *output ){
  if( output == NULL )
    return;
  
  sensor_details_t sensor;
  getSensorDetails( &sensor );

  output->print( "Sensor: " );
  output->println(sensor.name);

  output->print( language_auto_select( "Tipo: ", "Type: " ) );
  output->println( sensorTypeToString(sensor.type) );

  output->print( language_auto_select( "Versión del controlador: ", "Driver version: " ) );
  output->println( sensor.version );

  output->print( language_auto_select( "ID único: ", "Unique ID: " ) );
  output->println( (unsigned long)(sensor.sensor_id), HEX );

  output->print( language_auto_select( "Valor Min.: ", "Min value: " ) );
  output->println( sensor.min_value );

  output->print( language_auto_select( "Valor Max.: ", "Max value: " ) );
  output->println( sensor.max_value );

  output->print( language_auto_select( "Resolución: ", "Resolution: " ) );
  output->println( sensor.resolution );

}


const char* Energesis_Sensor::sensorTypeToString( sensor_type_t type ){
    if (type >= 0 && type < SENSOR_TYPE_MAX) {
        return sensorTypeStrings[type];
    } else {
        return sensor_type_invalid;
    }  
}



}
