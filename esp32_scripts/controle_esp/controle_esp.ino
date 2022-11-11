#include <WiFi.h>

#define PIN_BUTTON_1 19
#define PIN_BUTTON_2 21

const char *ssid = "redinha";
const char *pw = "12345678";

WiFiServer server(80);

int flag_btn1 = 0;
int flag_btn2 = 0;

void setup() {
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

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
  if (client) {
    while (client.connected()) {
      // Serial.println("Alguem esta conectado");
      if(deBounce(flag_btn1, PIN_BUTTON_1) == LOW){
        if(flag_btn1 == 0){
          
        }
        // Serial.write("apertando\n");
        client.println("esq botao_pressionado");

        flag_btn1 = 1;
        
      }

      if(deBounce(flag_btn2, PIN_BUTTON_2) == LOW){
        if(flag_btn2 == 0){
          
        }
        // Serial.write("apertando\n");
        client.println("dir botao_pressionado");

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

      while (client.available()) {
        String s = client.readStringUntil('\n');
        // Recebe dados da godot

      }

    }

  }

}


int deBounce(int state, int pin){
  int current_state = digitalRead(pin);

  if(state != current_state){
    delay(10);
    current_state = digitalRead(pin);

  }
  
  return current_state;
}
