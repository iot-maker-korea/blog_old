---
layout: post
title: 001.NODEMCU + DHT11 + Cayenne
comments: true
category: [Nodemcu]
tags: [nodemcu,embedded,dht11,온습도,센서]
---

# NODEMCU + DHT11 + Cayenne

> NODEMCU Temperature(DHT11) Server + Cayenne   
> Using arduino sketch   
> * https://zelkun.tistory.com/entry/00-Arduino-아두이노-시작하기-스케치-설치-및-포트-확인

## NODEMCU + DHT11 + Cayenne

<img src="https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/06/esp8266-dht.png" />
<br/>
> This sensor is DHT22 but same using pin for DHT11

## IDE Setting

### How to Esp3266 Board add

* https://www.youtube.com/watch?v=RVSCjCpZ_nQ
* https://zelkun.tistory.com/entry/031-Arduino-아두이노-보드-추가하기Adding-Arduino-Boards

### ESPAsyncTCP & WebServer library

* https://github.com/me-no-dev/ESPAsyncTCP
* https://github.com/me-no-dev/ESPAsyncWebServer

### Cayenne Library
* https://github.com/myDevicesIoT/Cayenne-MQTT-ESP

### How to Library Add
* https://zelkun.tistory.com/entry/023-Arduino-아두이노-DH11-Sensor-Module-온습도-센서-모듈   
* https://zelkun.tistory.com/entry/012-Arduino-아두이노-library-라이브러리-추가하기

### DHT11 Lib Add
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FyfD2W%2FbtqwEwHxWYu%2FbXKje74ZPrelgKM79ga6hk%2Fimg.png" />
<img src="https://i1.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/04/adafruit_dht_library.png" />

#### Library manager search & install   
> Adafruit DHT sensor library   
> Adafruit Unified Sensor   

## Cayenne Web & App
#### steps
* https://cayenne.mydevices.com   
> 1. sign up   
> 2. Add new Device/Widget   
> 3. Generic ESP8266 (All Device)   
> 4. Check Info   
> > MQTT USERNAME   
> > MQTT PASSWORD   
> > CLIENT ID   

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FEUVoC%2FbtqA2ag0a9Y%2FkcWB57Se0jCKiPOzaYKT5k%2Fimg.png" />

## Modify Your Source
> WiFi SSID, PASSWD   
> Cayenne Authentication info

<pre><code>
// WiFi network info.
const char ssid[] = "your wifi ssid";
const char wifiPassword[] = "your wifi passwd";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "cayenees mqtt username";
char password[] = "cayenees mqtt passwd";
char clientID[] = "cayenees mqtt client id";
</code></pre>

## Upload Source
### Arduino sketch
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FkVl6P%2FbtqA9CEt2YX%2FMFDKrSueBLMtFatkYRnrp0%2Fimg.png" />

board select > esp8266   
source upload

## Run
### Connect NODEMCU
* https://zelkun.tistory.com/entry/008-Arduino-아두이노-스케치-시리얼-모니터Seial-Monitor-사용방법
<img src="https://t1.daumcdn.net/cfile/tistory/2458EB4556B2E32510" />
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FZxDRg%2FbtqBcLOae1u%2FBhnwwIz7bQ0W5tE82MOhuk%2Fimg.png" />
Using arduino sketch Serial Monitor and cheking your Nodemcu ip (192.168.0.x)

#### using browser and connecting ip address (192.168.0.x)
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FLx8gc%2FbtqBaAfmImy%2Fsvtr7FqxStzyl0hJw6BWlk%2Fimg.png" />

#### Caynees Dashboard
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FcmNTdq%2FbtqA4AeMnCG%2FLB1lKRWEuppGIkxaEqp4i0%2Fimg.png" />
this is raspberry pi Dashboard but same.

#### Add Widget
if you want different widget, use to button "Add Device/Widget"



## ref
* https://raw.githubusercontent.com/RuiSantosdotme/Random-Nerd-Tutorials/master/Projects/ESP8266/ESP8266_WiFi_DHT_Web_Server.ino
* https://zelkun.tistory.com
* https://cayenne.mydevices.com
