Лабораторна робота №4: Captive Portal & Config
Hardware (Апаратна частина):


Microcontroller: ESP32 Dev Module (30-pin version).


Interface: USB-to-UART (CP2102 або CH340) для програмування.


Network: Wi-Fi 2.4GHz (використовується режим Access Point для створення точки доступу).

Libraries (Програмні бібліотеки):


Arduino.h — базовий фреймворк для розробки.


WiFi.h — робота з мережею та створення точки доступу.


DNSServer.h — перехоплення DNS-запитів для автоматичного відкриття сторінки авторизації (Captive Portal).


Preferences.h — бібліотека для запису та зберігання логіна/пароля Wi-Fi в енергонезалежну пам'ять (NVS).


WebServer.h — сервер для відображення сторінки конфігурації.
