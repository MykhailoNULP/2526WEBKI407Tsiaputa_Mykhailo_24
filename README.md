Лабораторна робота №5: HTTPS & Security
Hardware (Апаратна частина):


Microcontroller: ESP32 Dev Module (30-pin version).


Security: Integrated RSA/AES Hardware Accelerator для апаратного шифрування.


Interface: USB-to-UART (CP2102 або CH340) для програмування.


Network: Wi-Fi 2.4GHz для захищеної передачі даних.

Libraries (Програмні бібліотеки):


Arduino.h — базовий фреймворк для розробки.


WiFi.h — підключення до мережі.


HTTPSServer.hpp — сервер із підтримкою протоколу захищеної передачі даних SSL/TLS.


SSLCert.hpp — бібліотека для генерації та роботи з RSA-сертифікатами безпеки.


mbedTLS — вбудована криптографічна бібліотека для безпосереднього шифрування трафіку.
