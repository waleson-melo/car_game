#include <Arduino.h>
#include <WiFi.h>

#include <utils.h>

#define PIN_BUTTON_1 19
#define PIN_BUTTON_2 21

#define trigger_pin 5
#define Echo_pin 18
#define LED 4

const char *ssid = "redinha";
const char *pw = "12345678";

WiFiServer server(80);

long duration;
int distance;

int flag_btn1 = 0;
int flag_btn2 = 0;


void sensor_distance(WiFiClient client);


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

  pinMode(trigger_pin, OUTPUT);
  pinMode(Echo_pin, INPUT);

  Serial.begin(9600);

  delay(1000);

  WiFi.begin(ssid, pw);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  Serial.println("Conectado");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if(client) {
      Serial.println("entrou no if");
    while (client.connected()) {
      if(deBounce(flag_btn1, PIN_BUTTON_1) == LOW){
        if(flag_btn1 == 0){
          client.println("esq botao_pressionado");
          Serial.write("esq apertando\n");
        }

        flag_btn1 = 1;
      }

      if(deBounce(flag_btn2, PIN_BUTTON_2) == LOW){
        if(flag_btn2 == 0){
          client.println("dir botao_pressionado");
          Serial.write("dir apertando\n");
        }

        flag_btn2 = 1;

      }

      if(flag_btn1 == 1 && deBounce(flag_btn1, PIN_BUTTON_1) == HIGH){
        //Serial.write("soltando\n");
        client.println("esq botao_liberado");
        flag_btn1 = 0;
      }

      if(flag_btn2 == 1 && deBounce(flag_btn2, PIN_BUTTON_2) == HIGH){
        //Serial.write("soltando\n");
        client.println("dir botao_liberado");
        flag_btn2 = 0;
      }

      //sensor_distance(client);

      while (client.available()) {
        String s = client.readStringUntil('\n');
        
        if(s == "alerta") {
          tone(33, 200);
        }else {
          noTone(33);
        }
      }
    }
  }
}


void sensor_distance(WiFiClient client) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(Echo_pin, HIGH);
  distance= duration*0.034/2;

  client.println("dis " + String(distance));
  
  if(distance < 15) {
    client.println("perto");
  }else {
    client.println("longe");
  }
}
