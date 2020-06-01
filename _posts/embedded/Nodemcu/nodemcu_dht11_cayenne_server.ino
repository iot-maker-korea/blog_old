/*
 * ref: https://raw.githubusercontent.com/RuiSantosdotme/Random-Nerd-Tutorials/master/Projects/ESP8266/ESP8266_WiFi_DHT_Web_Server.ino
 */

#include <Arduino.h>
#include <Hash.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 2

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

void router_setting(void);
DHT dht(DHTPIN, DHTTYPE);

// WiFi network info.
const char ssid[] = "your wifi ssid";
const char wifiPassword[] = "your wifi passwd";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "cayennes mqtt username";
char password[] = "cayennes mqtt passwd";
char clientID[] = "cayennes mqtt client id";

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;
float hic = 0.0;

bool CayenneSent = false;
bool ReadError = true;

//Time to sleep - 5 minutes
unsigned long sleepTime = 5 * 6 * 10000000;
unsigned long startTime = 0;

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
	<style>
		html {
			font-family: Arial;
			display: inline-block;
			margin: 0px auto;
			text-align: center;
		}
		h2 { font-size: 3.0rem; }
		p { font-size: 3.0rem; }
		.units { font-size: 1.2rem; }
		.dht-labels{
			font-size: 1.5rem;
			vertical-align:middle;
			padding-bottom: 15px;
		}
	</style>
</head>
<body>
	<h2>ESP8266 DHT Server</h2>
	<p>
		<i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
		<span class="dht-labels">Temperature</span> 
		<span id="temperature">%TEMPERATURE%</span>
		<sup class="units">&deg;C</sup>
	</p>
	<p>
		<i class="fas fa-tint" style="color:#00add6;"></i> 
		<span class="dht-labels">Humidity</span>
		<span id="humidity">%HUMIDITY%</span>
		<sup class="units">%</sup>
	</p>
</body>
<script>
setInterval(function ( ) {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById("temperature").innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", "/temperature", true);
	xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById("humidity").innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", "/humidity", true);
	xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
	//Serial.println(var);
	if(var == "TEMPERATURE"){
		return String(t);
	}
	else if(var == "HUMIDITY"){
		return String(h);
	}
	return String();
}

void router_setting(){
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });

  // Start server
  server.begin();
}

void setup() {
	Serial.begin(115200);
	dht.begin();

	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
	CayenneSent = false; //init setting
	ReadError = true; //init setting

	// Connect to Wi-Fi
	//WiFi.begin(ssid, wifiPassword);
	Serial.println("Connecting to WiFi");
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println(".");
	}

	// Print ESP8266 Local IP Address
	Serial.println(WiFi.localIP());

	router_setting(); //init route setting
}

void loop() {
	Cayenne.loop();

	float newT = dht.readTemperature();
	float newH = dht.readHumidity();
	float newHic = dht.computeHeatIndex(newT, newH, false);
	
	if(isnan(newT) || isnan(newH) || isnan(newHic)){
		ReadError = true;
		Serial.println("dht11 Sensor Error");
	} else {
		ReadError = false;
		t = newT;
		h = newH;
		hic = newHic;
	}

	//Sent Data and Delay
	if (CayenneSent){
		Serial.println("Sent all values - delay");
	  	startTime = millis();
	  	CayenneSent = false;
		//ESP.deepSleep(sleepTime); //ESP DeepSleep, D0 <-> rst pin connect
	}

	delay(1000); //1 second delay
}

CAYENNE_OUT_DEFAULT() {
	if(!ReadError && (startTime == 0 || millis() - startTime > sleepTime)){
		Serial.println("cayenne send");
		Serial.print("temperature: ");
		Serial.println(t);
		Serial.print("humidity: ");
		Serial.println(h);
		Serial.print("heatIndex: ");
		Serial.println(hic);

		Cayenne.virtualWrite(0, t, "temperature", "c");
		Cayenne.virtualWrite(1, h, "humidity", "p");
		Cayenne.virtualWrite(2, hic, "heat_index", "c");
		CayenneSent = true;
	}
}
