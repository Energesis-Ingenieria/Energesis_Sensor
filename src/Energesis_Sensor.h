/**
 * @file Energesis_Sensor.h
 * @author Jose Guerra Carmenate (joseguerracarmenate@gmail.com)
 * @brief Definición de clases genéricas para la implementación de 
 * controladores de sensores.
 * @version 0.1
 * @date 2022-05-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ENERGESIS_SENSOR_H_
#define ENERGESIS_SENSOR_H_

#include <Arduino.h>
#include <stdint.h>

#define ENERGESIS_MAJOR_VERSION 0
#define ENERGESIS_MINOR_VERSION 1
#define ENERGESIS_PATCH_VERSION 3

namespace Energesis{

/**
 * @brief Definiciones de los distintos tipos de sensores disponibles
 * 
 */
typedef enum{
  SENSOR_TYPE_TEMPERATURE,        //!< Sensor de Temperatura
  SENSOR_TYPE_RELATIVE_HUMIDITY,  //!< Sensor de Humedad relativa
  SENSOR_TYPE_CURRENT,            //!< Sensor de corriente
  SENSOR_TYPE_VOLTAGE,            //!< Sensor de voltaje
  SENSOR_TYPE_MAX,                //!< Cantidad de tipos de sensores
} sensor_type_t;


/**
 * @brief Estructura para obtener una muestra con toda la 
 * información referente a esta 
 * 
 */
struct sensor_sample_t{
  uint64_t sensor_id;     //!< Identificador único del sensor
  sensor_type_t type;     //!< Magnitud sensada
  uint64_t timestamp;     //!< Timestamp del momento en que fue tomada la muestra

  union{
    float temperature;    //!< Valor de la temperatura en ºC.
    float humidity;       //!< Valor de la humedad relativa en %.
    float current;        //!< Valor de la corriente en mA.
    float voltage;        //!< Valor del voltaje en mV.
    float valueFloat;     //!< Genérico para variables de tipo float 
  };

} ;

/**
 * @brief Permite almacenar información detallada de un sensor.
 *  
 *  Inspirado por la estructura sensor_t implementada en 
 * https://github.com/android/platform_hardware_libhardware/blob/master/include/hardware/sensors.h 
 * 
 */
struct sensor_details_t{
  char name[16];          //!< Nombre del sensor 

  uint32_t version;       //!< Combinación de la version del hardware y del driver 
  uint64_t sensor_id;     //!< Identificador único del sensor
  sensor_type_t type;     //!< Magnitud sensada
  
  float max_value; /**< Maximum value of this sensor's value in SI units. <br>
                        Máximo valor que el sensor puede medir, en unidades del SI*/
  float min_value; /**< Minimum value of this sensor's value in SI units. <br>
                        Mínimo valor que el sensor puede medir, en unidades del SI*/
  float resolution; /*!< Smallest difference between two values reported by this sensor. <br> 
                         Menor diferencia entre dos valores obtenidos por el sensor */

  float power; /**< Rough estimate of this sensor's power consumption in mA. <br> 
                    Estimación aproximada del consumo de energía de este sensor en mA*/

  uint32_t min_delay;

} ;


/**
 * @brief Interfaz común para simplificar el uso de varios sensores de 
 * distintas magnitudes y características.
 * 
 */
class Energesis_Sensor{
public:
  
  Energesis_Sensor(){};
  virtual ~Energesis_Sensor(){};

  /**
   * @brief Permite obtener la muestra más reciente de la magnitud sensada.
   * 
   * @param[out] sample puntero a la struct \a sensor_sample_t donde se almacenará la
   * muestra.
   * @return true La muestra se ha obtenido y almacenado correctamente
   * @return false Error al obtener la muestra.
   */
  virtual bool getSample( sensor_sample_t *sample ) = 0;

  /**
   * @brief Almacena en una struct \a sensor_details_t información relativa al sensor.  
   * 
   * @param details puntero a \a sensor_details_t donde se pondrá la información.
   */
  virtual void getSensorDetails( sensor_details_t *details ) = 0;

  /**
   * @brief Envía información relativa al sensor a un Stream.
   * 
   * @param output 
   */
  void printSensorDetails( Stream *output = &Serial );

private:
  /**
   * @brief Retorna un arreglo de caracteres con la descripción 
   * de un tipo de sensor
   * 
   * @param type tipo de sensor
   * 
   * @return const char* descripcion del tipo de sensor
   */
  static const char* sensorTypeToString( sensor_type_t type );



};


/**
 * @brief Clase base para sensores analógicos
 * 
 */
class Energesis_AnalogSensor{
  public:
    Energesis_AnalogSensor():m_v_ref(5000), m_resolution(12){};
    virtual ~Energesis_AnalogSensor(){};

    float setVref( float v_ref ){
      if( v_ref < 0.0 ){ // auto select
        #if defined(ESP32)
        v_ref = 3300;
        #elif defined(ARDUINO_UNO) || defined(ARDUINO_MEGA)
        v_ref = 5000;
        #else
        v_ref = 5000;
        #endif
      }
      else{
        m_v_ref = v_ref; 
      }
      return m_v_ref;
    }

    float getVref(){ return m_v_ref; };

    /**
     * @brief Indica la resolución del ADC.
     * 
     * @param bits resolución del ADC en bits
     * 
     * @note La resolución es solo para realizar la conversion
     * y obtener el valor de temperatura. El controlador no realiza 
     * ninguna acción de configuración sobre el ADC.
     */
    void setAnalogResolution( uint8_t bits ){ m_resolution = bits; }

    uint8_t getAnalogResolution(){ return m_resolution; }

    /**
     * @brief Retorna el valor bruto obtenido por el ADC
     * 
     * @return uint16_t valor obtenido por el ADC
     */
    virtual uint16_t getRaw() = 0;

  private:
    float m_v_ref;        //!< voltaje de referencia [mV]
    uint8_t m_resolution;   //!< resolución [bits]
};


/**
 * @brief Interfaz para sensores de temperatura.
 * 
 */
class Energesis_TemperatureSensor{
  public:
    Energesis_TemperatureSensor(){}
    ~Energesis_TemperatureSensor(){
      if( m_temperature_sensor )
        delete m_temperature_sensor;
    }
  
    /**
     * @brief Retorna la temperatura en grados Celsius (ºC).
     *
     */
    virtual float getTemperature() = 0;

    /**
     * @brief Retorna la temperatura en grados Fahrenheit (ºF)
     * 
     * @return float Temperatura en grados Fahrenheit (ºF).
     */
    float getTemperatureFahrenheit(){
      return (getTemperature()*9/5) + 32.0; 
    }
  
    /**
     * @brief Retorna la temperatura en grados Kelvin (K).
     * 
     * @return float temperatura en grados Kelvin (K).
     */
    float getTemperatureKelvin(){
      return getTemperature() + 273.15;
    }

    virtual Energesis_Sensor *getTemperatureSensor() = 0;


    static float CelsiusToFahrenheit( float c ){
      return (c*9/5) + 32.0; 
    }

    static float CelsiusToKelvin( float c ){
      return c + 273.15;
    }

  protected:
    Energesis_Sensor *m_temperature_sensor = NULL;

};


/**
 * @brief Interfaz para sensores de humedad relativa.
 * 
 */
class Energesis_RelativeHumiditySensor{
  public:
    Energesis_RelativeHumiditySensor(){};
    virtual ~Energesis_RelativeHumiditySensor(){
      if( m_humidity_sensor )
        delete m_humidity_sensor;
    };

    virtual float getRelativeHumidity() = 0;

    virtual Energesis_Sensor* getRelativeHumiditySensor() = 0;

  protected:
    Energesis_Sensor *m_humidity_sensor = NULL;

};

};

#endif
