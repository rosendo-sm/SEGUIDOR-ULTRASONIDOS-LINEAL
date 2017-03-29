/* Sencillo programa que controla un motor en función de la distancia medida por un sensor de ultrasonidos 
 * manteniendo una distancia fija de 6cm hasta el obstáculo detectado. El motor desplaza al sensor que está
 * montado sobre una protoboard atornillada a una guía de cajón. El conjunto actúa como un sistema de enfoque
 * automático o como un servo lineal que mantiene una distancia fija de un mecanismo a un objeto detectado
*/
// Patas en las que se conecta el HC04
const int EchoPin = 3;
const int TriggerPin = 4;
const int LedPin = 13; // Pata del indicador luminoso Builtin LED
const int Buzzer = 2; // Pata de salida del zumbador
// ************************************* Inicialización de variables y pines *******************************************
void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);// Control motor giro derecha
  pinMode(12, OUTPUT);// Control motor giro izquierda
  pinMode(2, OUTPUT);// Salida zumbador
  pinMode(LedPin, OUTPUT); // Salida piloto de estado funcionando
  pinMode(TriggerPin, OUTPUT); // Salida pata trigger del HC04
  pinMode(EchoPin, INPUT); // // Salida pata trigger del HC04
}
 
//************************************** Bucle del programa principal **************************************************
void loop() {
 int cm = ping(TriggerPin, EchoPin);//Llama a la función para medir distancia y lo almacena en la variable cm
 Serial.print("Distancia: "); // Imprime por puerto serie "Distancia:"
 Serial.println(cm); // Imprime por puerto serie el valor de distancia medido en cm
 if (cm ==6) {
  digitalWrite (11, LOW); // Para el motor si la distancia es 6cm
  digitalWrite(12, LOW);
  digitalWrite(2, LOW); //Hace un pitido corto avisando que está ajustado
  delay(100);
  digitalWrite(2, LOW);                
  }
  else {
  if (cm>=7) {
  digitalWrite(11, HIGH);// Si está más separado de 7cm mueve el motor para acercar
  digitalWrite(12, LOW); 
  }
  if (cm <5) {
  digitalWrite (11, LOW);// Si está más cerca de 5cm mueve el motor para alejar
  digitalWrite(12, HIGH);
  }     
  }
 delay(100);      // Retardo para una medida cada segundo
}

//********************************* Función de medida de distancia ******************************************************
// Función de medida por tiempo de rebote de sonido en us -> cm

int ping(int TriggerPin, int EchoPin) {
 long duration, distanceCm;
 
 digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
 delayMicroseconds(4);
 digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
 delayMicroseconds(10);
 digitalWrite(TriggerPin, LOW);
 
 duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
 
 distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
 return distanceCm; // Elegir devolver us o cm
 //return duration; // Elegir devolver us o cm
}

