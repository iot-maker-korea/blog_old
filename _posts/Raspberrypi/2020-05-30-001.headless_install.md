---
layout: post
title: 001.headless_install
comments: true
category: [Raspberrypi]
tags: [raspberrypi,라즈베리파이,raspbian]
---

# 라즈베리 1주차 학습

## [headless install][1]
라즈베리는 OS로 raspbian을 사용하기때문에   
첫번째인 만큼 micro sd카드(4g이상 권장)에 raspbian을 설치했습니다

보통 라즈베리만 사용하려면   
모니터와 키보드, 마우스가 필요한데요
* [준비물 참고][0]

ssh(원격접속 터미널) 를 바로 사용할 수 있는   
headless 방식으로 설치를 진행합니다

---

## headless

headless의 장점의 모니터가 필요없는건데, 그래도 원격접속을 하기위해선 
ip를 확인해야하는 문제가 있습니다

* [headless install 참고][1]

> 그래서 [UART][2]를 사용하는게 더 편합니다
> * [uart 참고][2]

---

## [UART][2]

UART 모듈(?)의 장점은   
아두이노, nodemcu, 라즈베리 등에서도   
사용할 수 있으니 한두개정도 구비하시면 좋습니다

### UART 사용준비(pi3 이상, pi4는 확인 못함)

라즈베리3 부터는 RX/TX를 블루투스와 공유하기때문에 이전 모델과는 다르게 별도의 설정을 해줘야합니다

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FCNywm%2FbtqBDXgMgHA%2FTjOlv8bM2B6L32KPIqBkyK%2Fimg.png">

boot/config.txt 파일 하단에 enable_uart=1 을 추가해주면 준비가 끝납니다

### UART pinMap

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2F3xmWK%2FbtqACGz6geq%2F5veUsn0vZZoNq133vk9Qh0%2Fimg.png">

출처: http://elinux.org/RPi_Low-level_peripherals

가지고 있는 모듈의 TX/RX 핀을 파이에 연결해줍니다

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2F7OE6Q%2FbtqAB3PPlH7%2FRJa25rZPcUBMInE5YUst5k%2Fimg.jpg">

참고로 USB-TO-SERIAL와 라즈베리파이 RX/TX 핀은 __교차__ 해서 연결해줍니다 

---

### [Uart 통신][2]

PC와 연결을 위해 COM 포트를 확인해야합니다

<img src="https://t1.daumcdn.net/cfile/tistory/2131804057248E6B24">

정상적으로 드라이버를 잡았다면 위와같이 COM포트를 표시해 줍니다  
COM5번으로 확인되네요

[<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FtQGK0%2FbtqA2ceKvRJ%2Fk4xEtcYLSMKOt3KfJoVxYk%2Fimg.png" width="500">][3]

하지만 [PL2303HXA-PHASED-OUT-SINCE-2012-PLEASE-CONTACT-YOUR-SUPPLIER][3] 메시지가 뜬다면  
드라이버를 다시 잡아야 합니다  
참고: https://zelkun.tistory.com/entry/PL2303HXA-PHASED-OUT-SINCE-2012-PLEASE-CONTACT-YOUR-SUPPLIER

<img src="https://t1.daumcdn.net/cfile/tistory/264CF44657248E6B2F"/>

COM포트 확인이 끝나면  
윈도우는 Putty를 이용해서 Pi와 연결하면 됩니다  
주의 할점은 SSH와 달리 우측의 Serial 로 변경하고  
확인된 COM포트, 통신속도 115200 으로 해줘야 합니다

<img src="https://t1.daumcdn.net/cfile/tistory/271B533557248E6C06">

통신속도의 경우 /boot/cmdline.txt 를 따르니 혹시 변경했다면 맞춰주면 됩니다

<img src="https://t1.daumcdn.net/cfile/tistory/24363D3A57248E6C25">

정상적으로 연결되면 Putty 화면(검은색) 이나오고 엔터를 눌러주면  
로그인 메시지를 볼수 있게 됩니다


## Ref

- https://zelkun.tistory.com

[0]: https://zelkun.tistory.com/entry/000-Raspberry-Pi-라즈베리-파이-시작하기
[1]: https://zelkun.tistory.com/entry/050-Raspberry-Pi-라즈베리-파이-Raspbian-headless-setup-for-WiFi-connection-and-UART-use-windows-macOS-linux-ubuntu
[2]: https://zelkun.tistory.com/entry/017-Raspberry-Pi-라즈베리-파이-UART-시리얼-통신-윈도우window-RS232-TTL-PL2303HX-usb-to-serial
[3]: https://zelkun.tistory.com/entry/PL2303HXA-PHASED-OUT-SINCE-2012-PLEASE-CONTACT-YOUR-SUPPLIER
