



Microcontroller: ESP32 Dev Module (30-pin version).


Sensor: HMC5883L (3-axis Digital Compass/Magnetometer) для вимірювання параметрів магнітного поля та орієнтації.


Interface: USB-to-UART (CP2102 або CH340) для програмування та моніторингу.


Network: Wi-Fi 2.4GHz (для передачі даних телеметрії в режимі реального часу).

Libraries (Програмні бібліотеки):

Arduino.h — базовий фреймворк для розробки.


WiFi.h — забезпечення мережевого підключення ESP32 до точки доступу.


ESPAsyncWebServer.h — асинхронний сервер для швидкої та стабільної передачі даних через WebSockets.


AsyncTCP.h — фундаментальна бібліотека для асинхронної роботи протоколу TCP на ESP32.


ArduinoJson.h — використовується для пакування даних з магнітометра (осі X, Y, Z) у формат JSON перед відправкою на клієнт.

Wire.h — стандартна бібліотека для роботи з інтерфейсом I2C, за яким підключається датчик HMC5883L.
=======
=======

Peripheral: Built-in Blue LED (підключений до GPIO 2).


Interface: USB-to-UART (CP2102 або CH340) для програмування.


Network: Wi-Fi 2.4GHz (підтримка режимів Station та Access Point).

Libraries (Програмні бібліотеки):


Arduino.h — базовий фреймворк для розробки.


WiFi.h — бібліотека для забезпечення роботи з мережею Wi-Fi.


WebServer.h — стандартний HTTP-сервер для обробки запитів.


LittleFS.h — файлова система для зберігання файлів сайту в пам'яті контролера.


ArduinoJson.h — спеціальна бібліотека для парсингу та формування команд керування світлодіодом у форматі JSON.
=======
Лабораторна робота №1 (HTTP Server)
Hardware:

Microcontroller: ESP32 Dev Module (30-pin version).

Interface: USB-to-UART (CP2102 or CH340).

Network: Wi-Fi 2.4GHz (Station and Access Point modes).

Libraries:


Arduino.h — базовий фреймворк.


WiFi.h — робота з мережею.


WebServer.h — стандартний HTTP-сервер.


LittleFS.h — файлова система для зберігання сайту.

Студент: Цяпута Михайло Петрович
Група: КІ-407
Дисципліна: Веб-технології та проєктування систем на мікроконтролерах

Загальна апаратна частина (Hardware):


Мікроконтролер: ESP32 Dev Module (30-pin version) використовується в усіх лабораторних роботах.


Інтерфейс програмування: USB-to-UART (на базі чіпів CP2102 або CH340).


Мережеві можливості: Підтримка Wi-Fi 2.4GHz у режимах Station (клієнт) та Access Point (точка доступу).

Структура проєкту:

Lab 1: Базовий HTTP-сервер на LittleFS.

Lab 2: Керування вбудованим світлодіодом (GPIO 2) через REST API та JSON.

Lab 3: Передача телеметрії з датчика HMC5883L через WebSockets.

Lab 4: Створення Captive Portal для конфігурації Wi-Fi.


