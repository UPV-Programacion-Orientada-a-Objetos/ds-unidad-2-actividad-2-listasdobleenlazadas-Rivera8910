
// ============================================
// Configuración
// ============================================
const unsigned long INTERVALO = 1000; // Milisegundos entre tramas
const int BAUD_RATE = 9600;

// ============================================
// Mensajes de Prueba Predefinidos
// ============================================

/**
 * @brief Envia el mensaje "HOLA MUNDO"
 */
void enviarHolaMundo() {
  Serial.println("L,H");
  delay(INTERVALO);
  Serial.println("L,O");
  delay(INTERVALO);
  Serial.println("L,L");
  delay(INTERVALO);
  Serial.println("L,A");
  delay(INTERVALO);
  Serial.println("L, ");
  delay(INTERVALO);
  Serial.println("L,M");
  delay(INTERVALO);
  Serial.println("L,U");
  delay(INTERVALO);
  Serial.println("L,N");
  delay(INTERVALO);
  Serial.println("L,D");
  delay(INTERVALO);
  Serial.println("L,O");
  delay(INTERVALO);
}

/**
 * @brief Envia "ABCD" con rotación
 */
void enviarConRotacion() {
  Serial.println("L,A");
  delay(INTERVALO);
  Serial.println("M,1"); // Rotar +1
  delay(INTERVALO);
  Serial.println("L,A"); // A con rotación = B
  delay(INTERVALO);
  Serial.println("M,1"); // Rotar +1 más
  delay(INTERVALO);
  Serial.println("L,A"); // A con rotación = C
  delay(INTERVALO);
  Serial.println("M,1"); // Rotar +1 más
  delay(INTERVALO);
  Serial.println("L,A"); // A con rotación = D
  delay(INTERVALO);
}

/**
 * @brief Envia el mensaje del documento (HOLCY YORLD)
 */
void enviarMensajeDocumento() {
  Serial.println("L,H");
  delay(INTERVALO);
  Serial.println("L,O");
  delay(INTERVALO);
  Serial.println("L,L");
  delay(INTERVALO);
  Serial.println("M,2");
  delay(INTERVALO);
  Serial.println("L,A");
  delay(INTERVALO);
  Serial.println("L, ");
  delay(INTERVALO);
  Serial.println("L,W");
  delay(INTERVALO);
  Serial.println("M,-2");
  delay(INTERVALO);
  Serial.println("L,O");
  delay(INTERVALO);
  Serial.println("L,R");
  delay(INTERVALO);
  Serial.println("L,L");
  delay(INTERVALO);
  Serial.println("L,D");
  delay(INTERVALO);
}

/**
 * @brief Prueba de rotaciones extremas
 */
void pruebaRotacionesExtremas() {
  Serial.println("L,T");
  delay(INTERVALO);
  Serial.println("L,E");
  delay(INTERVALO);
  Serial.println("L,S");
  delay(INTERVALO);
  Serial.println("L,T");
  delay(INTERVALO);
  Serial.println("M,26"); // Rotación completa
  delay(INTERVALO);
  Serial.println("L,A");
  delay(INTERVALO);
}

/**
 * @brief Crea un mensaje personalizado
 * INSTRUCCIONES:
 * 1. Para enviar un carácter: Serial.println("L,X"); donde X es tu carácter
 * 2. Para rotar: Serial.println("M,N"); donde N es el número de rotaciones
 * 3. No olvides delay(INTERVALO); entre cada línea
 */
void enviarMensajePersonalizado() {
  // Ejemplo: Enviar "HOLA" con cifrado César
  Serial.println("L,H");
  delay(INTERVALO);
  Serial.println("L,O");
  delay(INTERVALO);
  Serial.println("L,L");
  delay(INTERVALO);
  Serial.println("M,3"); // Rotación +3 (cifrado César clásico)
  delay(INTERVALO);
  Serial.println("L,A"); // Se decodificará como 'D'
  delay(INTERVALO);
  
  // Agrega más líneas aquí para tu mensaje personalizado
}

// ============================================
// Configuración del Arduino
// ============================================
void setup() {
  Serial.begin(BAUD_RATE);
  delay(2000); // Esperar a que se establezca la conexión
  
  Serial.println("========================================");
  Serial.println("  Emisor PRT-7 Personalizado - Arduino");
  Serial.println("========================================");
  Serial.println();
}

// ============================================
// Bucle Principal
// ============================================
void loop() {
  Serial.println("--- INICIANDO TRANSMISION ---");
  Serial.println();
  
  // DESCOMENTAR LA FUNCIÓN QUE QUIERAS PROBAR:
  
  // enviarHolaMundo();
  // enviarConRotacion();
  enviarMensajeDocumento();  // <- ACTIVA POR DEFECTO
  // pruebaRotacionesExtremas();
  // enviarMensajePersonalizado();
  
  Serial.println();
  Serial.println("--- FIN DE TRANSMISION ---");
  Serial.println("Esperando 5 segundos para reiniciar...");
  Serial.println();
  
  delay(5000); // Esperar antes de repetir
}

// ============================================
// Funciones Auxiliares
// ============================================

/**
 * @brief Envia una cadena de caracteres sin rotación
 * @param mensaje Cadena a enviar (solo mayúsculas y espacios)
 */
void enviarCadenaSinRotacion(const char* mensaje) {
  int i = 0;
  while (mensaje[i] != '\0') {
    Serial.print("L,");
    Serial.println(mensaje[i]);
    delay(INTERVALO);
    i++;
  }
}

/**
 * @brief Envia una cadena con cifrado César simple
 * @param mensaje Cadena a enviar
 * @param rotacion Valor de rotación César (ej. 3 para ROT3)
 */
void enviarCadenaConCifrado(const char* mensaje, int rotacion) {
  // Primero rotar
  Serial.print("M,");
  Serial.println(rotacion);
  delay(INTERVALO);
  
  // Luego enviar el mensaje
  int i = 0;
  while (mensaje[i] != '\0') {
    Serial.print("L,");
    Serial.println(mensaje[i]);
    delay(INTERVALO);
    i++;
  }
  
  // Restaurar rotación
  Serial.print("M,");
  Serial.println(-rotacion);
  delay(INTERVALO);
}