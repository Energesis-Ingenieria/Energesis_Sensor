# Energesis Generic Sensor Driver

![Hex.pm](https://img.shields.io/hexpm/l/plug)  [![PlatformIO Registry](https://badges.registry.platformio.org/packages/energesis-ingenieria/library/Energesis_Sensor.svg)](https://registry.platformio.org/libraries/energesis-ingenieria/Energesis_Sensor) [![GitHub Release](https://img.shields.io/github/release/energesis-ingenieria/Energesis_Sensor.svg?style=flat)]() 
![GitHub all releases](https://img.shields.io/github/downloads/energesis-ingenieria/Energesis_Sensor/total) ![GitHub watchers](https://img.shields.io/github/watchers/Energesis-Ingenieria/Energesis_Sensor)

_[See in english](README.md)_

Uno de los muchos desafíos del diseño de sistemas electrónicos es el hecho de que los componentes que hoy se utilizan pueden estar obsoletos y descontinuados mañana, o los requisitos del sistema pueden cambiar y es posible que se deba elegir un sensor diferente.

Crear nuevos controladores es una tarea relativamente fácil, pero integrarlos en los sistemas existentes es propenso a errores y requiere horas de esfuerzo, ya que los sensores rara vez usan exactamente las mismas unidades de medida o los mismos protocolos.

Al reducir todos los datos a un solo tipo (**sensor_sample\_t**) y establecer unidades estandarizadas para cada familia de sensores, los datos de un sensor son comparables con cualquier otro sensor similar. Esto permite cambiar de modelo de sensor con muy poco impacto en el resto del sistema, lo que puede ayudar a mitigar algunos de los riesgos y problemas de la disponibilidad del sensor y la reutilización del código.

Además, se cuenta con un conjunto de interfaces (clases abstractas) para cada tipo de sensor que garantiza una implementación homogénea para sensores de un mismo tipo. Esto significa, por ejemplo, que el controlador de cualquier sensor de temperatura implementará el método `getTemperature()`.

_**Nota:** Esta biblioteca está basada en [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)._


## License
Licencia Apache 2.0 license, ver [LICENSE](LICENSE) para más detalles.
