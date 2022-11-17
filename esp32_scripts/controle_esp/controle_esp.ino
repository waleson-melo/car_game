#include <WiFi.h>
#include <WiFiUdp.h>//Biblioteca do UDP.

#define LED 4
#define trigger_pin 5
#define Echo_pin 18

WiFiUDP udp;//Cria um objeto da classe UDP.

long duration;
int distance;

void connect();
void send();
void listen();


void setup() {
  pinMode(LED, OUTPUT);//Habilita o LED onboard como saida.
  digitalWrite(LED, LOW);

  pinMode(trigger_pin, OUTPUT);
  pinMode(Echo_pin, INPUT);

  WiFi.mode(WIFI_STA);//Define o ESP8266 como Station.

  Serial.begin(9600);

  connect();
}

void loop() {
  //connect(); // Sub-rotina para conectar-se ao host.

  send(); // Sub-rotina para enviar os dados ao host.

  //listen();

  delay(500); // Aguarda meio segundo.
}

void connect() { // Sub-rotina para verificar a conexao com o host. 
  if (WiFi.status() != WL_CONNECTED) { //Caso nao esteja conectado ao host, ira se conectar.
    WiFi.begin("redinha", "12345678"); // Conecta à rede do host.
    delay(1000); // Espera ate que a conexao seja feita.
    Serial.println("Conectado");
    Serial.println(WiFi.localIP());
  }
}

void send() { //Sub-rotina para enviar dados ao host.
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(Echo_pin, HIGH);
  distance = duration * 0.034/2;
  delay(5);
  Serial.println(distance);
  
  if(WiFi.status() == WL_CONNECTED) { //Só ira enviar dados se estiver conectado.

    udp.beginPacket("192.168.137.1", 555);//Inicializa o pacote de transmissao ao IP e PORTA.
    udp.print(distance);//Adiciona-se o valor ao pacote.
    udp.endPacket();//Finaliza o pacote e envia.

    // digitalWrite(LED, HIGH);
  }
}

void listen()//Sub-rotina que verifica se há pacotes UDP's para serem lidos.
{
  if(udp.parsePacket() > 0)//Se houver pacotes para serem lidos
  {
    int req = 0;//Reseta a string para receber uma nova informaçao
    while (udp.available() > 0)//Enquanto houver dados para serem lidos
    {
      char z = udp.read();//Adiciona o byte lido em uma char
      req += z;//Adiciona o char à string
    }

    //Após todos os dados serem lidos, a String estara pronta.
    
    Serial.println(req);//Printa a string recebida no Serial monitor.
  }
  //Enviar Resposta
  //delay(500);
}
