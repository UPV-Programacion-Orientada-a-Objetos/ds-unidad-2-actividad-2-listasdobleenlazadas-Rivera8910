
// Mensaje de ejemplo del documento
const char* tramas[] = {
  "L,H",
  "L,O",
  "L,L",
  "M,2",
  "L,A",
  "L, ",    // Espacio
  "L,W",
  "M,-2",
  "L,O",
  "L,R",
  "L,L",
  "L,D",
  nullptr   // Marca el final
};

int tramaActual = 0;
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 1000; // 1 segundo entre tramas

void setup() {
  // Inicializar comunicación serial a 9600 baudios
  Serial.begin(9600);
  
  // Esperar a que se establezca la conexión
  delay(2000);
  
  Serial.println("========================================");
  Serial.println("  Emisor PRT-7 - Arduino");
  Serial.println("  Sistema de Telemetria Industrial");
  Serial.println("========================================");
  Serial.println();
  Serial.println("Iniciando transmision de tramas...");
  Serial.println();
  
  tiempoAnterior = millis();
}

void loop() {
  unsigned long tiempoActual = millis();
  
  // Verificar si ha pasado el intervalo
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    
    // Verificar si hay más tramas por enviar
    if (tramas[tramaActual] != nullptr) {
      // Enviar la trama
      Serial.println(tramas[tramaActual]);
      
      // Mostrar en el monitor serial del Arduino (opcional)
      // Serial.print("Enviando: ");
      // Serial.println(tramas[tramaActual]);
      
      tramaActual++;
    } else {
      // Reiniciar para enviar el mensaje nuevamente
      tramaActual = 0;
      
      Serial.println();
      Serial.println("--- Fin de transmision ---");
      Serial.println("Reiniciando en 3 segundos...");
      Serial.println();
      
      delay(3000);
    }
  }
}

/**
 * Función auxiliar para crear tramas personalizadas
 * Descomenta y modifica según necesites
 */
/*
void enviarMensajePersonalizado() {
  // Ejemplo: enviar "HOLA"
  Serial.println("L,H");
  delay(1000);
  Serial.println("L,O");
  delay(1000);
  Serial.println("L,L");
  delay(1000);
  Serial.println("L,A");
  delay(1000);
}
*/
