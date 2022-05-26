# Energesis Generic Sensor Driver

![Hex.pm](https://img.shields.io/hexpm/l/plug)  [![PlatformIO Registry](https://badges.registry.platformio.org/packages/energesis-ingenieria/library/Energesis_Sensor.svg)](https://registry.platformio.org/libraries/energesis-ingenieria/Energesis_Sensor) [![GitHub Release](https://img.shields.io/github/release/energesis-ingenieria/Energesis_Sensor.svg?style=flat)]() 
![GitHub all releases](https://img.shields.io/github/downloads/energesis-ingenieria/Energesis_Sensor/total) ![GitHub watchers](https://img.shields.io/github/watchers/Energesis-Ingenieria/Energesis_Sensor)


_[Ver en español](README-es.md)_

One of the many challenges of electronic system design is the fact that components used today may be obsolete and discontinued tomorrow, or system requirements may change and a different sensor may need to be chosen.

Creating new controllers is a relatively easy task, but integrating them into existing systems is error-prone and requires hours of effort, since sensors rarely use exactly the same units of measurement or the same protocols.

By reducing all data to a single type (**sensor_sample\_t**) and establishing standardized units for each sensor family, data from one sensor is comparable to any other similar sensor. This allows switching between sensor models with very little impact on the rest of the system, which can help mitigate some of the risks and issues of sensor availability and code reuse.

In addition, there is a set of interfaces (abstract classes) for each type of sensor that guarantees a homogeneous implementation for sensors of the same type. This means, for example, that the controller of any temperature sensor will implement the `getTemperature()` method.

_**Note:** This library has been inspired by [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)._

## License

This project is under Apache 2.0 license. See [LICENSE](LICENSE) for more details.
