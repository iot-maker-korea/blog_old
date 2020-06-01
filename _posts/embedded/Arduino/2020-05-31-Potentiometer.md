---
layout: post
title: 가변저항(Potentiometer)
comments: true
category: [Arduino]
tags: [arduino,아두이노]
---

# [Potentiometer][1]

<img src="https://ae01.alicdn.com/kf/H285524d6e48f43f7b10693f09741d7d69/5pcs-WH148-B1K-B2K-B5K-B10K-B20K-B50K-B100K-B500K-3Pin-15mm-Shaft-Amplifier-Dual-Stereo.jpg" width="250">

출처: https://www.aliexpress.com/item/32846573934.html

 가변저항으로 5v연결시 0~1023 의 값을 얻을 수 있다 ([analogRead][5])  
 과거 라디오 볼륨조절에 많이 사용되었으나, 현재는 전자식이 많아 보기힘듦

## pinMap

<img src="https://www.arduino.cc/en/uploads/Tutorial/potentiometer.jpg" width="250">

VCC, GND, A0 ~ A5 에 연결해서 사용


### Sample Code

<pre><code>#define readPin A0
void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int nRead = analogRead(readPin);
	//map
	int convert = map(nRead, 0, 1023, 0, 180);

	Serial.print("A0: ");
	Serial.println(nRead);
	Serial.print("Convert: ");
	Serial.println(convert);
	delay(100);
}</code></pre>

읽어들인 아날로그 값을 Serial로 출력하는 예제  
[map][3] 을 사용해서 0~1023 값을 180도로 변경한 값도 볼 수 있다  

---

## [PWM][2]

<img src="https://www.theengineeringprojects.com/wp-content/uploads/2018/10/how-to-use-analogWrite-in-Arduino.png" width="500">

출처: https://www.theengineeringprojects.com/2018/12/how-to-use-analogwrite-in-arduino.html

디지털핀(우노보드) ~3,~5,~6,~9,~10,~11 에 해당하며  

[analogWrite][6]를 이용해서 0~255 값을 사용할 수 있다

### Sample Code

<pre><code>#define ledPin 11
void setup()
{
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
}
void loop()
{
	/* PWM Test */
	int i=0;
	unsigned long wait = 100L;

	for(i = 0; i< 255; i++){
		analogWrite(ledPin, i);
		delay(wait);
	}
	for(i = 255; i > 0; i--){
		analogWrite(ledPin, i);
		delay(wait);
	}
}</code></pre>

[PWM][2]핀을 사용해서 Led의 밝기조절하는 예제  
사용하는 보드가 ~10 핀이 고장났나 [PWM][2]이 안되서 ~11을 사용

---

## [Servo motor][4]

<img src="https://ae01.alicdn.com/kf/Hcf41b536b1c248009da9508a2667f086Y/HIINST-1pcs-100-NEW-SG90-9G-Micro-Servo-Motor-For-Robot-6CH-RC-Helicopter-Airplane-Controls.jpg" width="250">

출처: https://www.aliexpress.com/item/4000595327297.html

0~180도를 회전하는 모터

### pinMap

<img src="https://www.allaboutcircuits.com/uploads/articles/servo-arduino_.jpg" width="500">

출처: https://www.allaboutcircuits.com/projects/servo-motor-control-with-an-arduino/

VCC, GND, [PWM][2] 핀에 연결하면 된다

### Sample Code

<pre><code>#include &lt;Servo.h&gt;
#define servoPin 9
Servo servo;

void setup()
{
	Serial.begin(9600);
	servo.attach(servoPin);
}

void loop()
{
	int i=0;
	unsigned long wait = 100L;

	/* Servo Test */
	for (i = 0; i < 180; i++){
		servo.write(i);
		delay(wait);
	}

	for (i = 180; i > 0; i--){
		servo.write(i);
		delay(wait);
	}
}</code></pre>

0~180도를 일정간격으로 회전하고 복귀하는 예제

---

## [Potentiometer][1] + [Servo motor][4] Combination

### Test Video(Youtube)

[![testing](https://img.youtube.com/vi/n0QHb3xcWf0/0.jpg)](https://www.youtube.com/watch?v=n0QHb3xcWf0)

### Sample Code

<pre><code>#include &lt;Servo.h&gt;
#define servoPin 9
#define ledPin 11
#define readPin A0

Servo servo;

void setup()
{
	Serial.begin(9600);
	servo.attach(servoPin);
	pinMode(ledPin, OUTPUT);
}

void loop()
{
	int nRead = analogRead(readPin);
	//map
	int servoDegree = map(nRead, 0, 1023, 0, 180);
	int ledDegree = map(nRead, 0, 1023, 0, 255);

	analogWrite(ledPin, ledDegree);
	servo.write(servoDegree);
}</code></pre>

가변저항값을 map으로 0~180로 변환해서  
[Servo motor][4]를 제어하는 예제
덤으로 PWM Led도 같이 있다

---

## Ref

[potentiometer][1]  
[PWM][2]  
[map][3]  
[servo motor][4]  

[1]: https://www.arduino.cc/en/tutorial/potentiometer
[2]: https://www.arduino.cc/en/tutorial/PWM
[3]: https://www.arduino.cc/reference/en/language/functions/math/map/
[4]: https://www.arduino.cc/en/Reference/Servo
[5]: https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
[6]: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
