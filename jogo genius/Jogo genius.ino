// Elias Felipe 
// Jogo Genius 

//*****Codigo*****//
int LED[4] = {A1, A2, A3, A4};
const int botao[4] = {2, 3, 4, 5};
int armazena_Sequencia[9] = {};// Array para armazenar a sequência gerada

//*****Portas do display de 7 segmentos*****//
const int a = 6;
const int b = 7;
const int c = 8;
const int d = 9;
const int e = 10;
const int f = 11;
const int g = 12;

//*****Variáveis*****//
int numero_aleatorio;
int nivel;
int botao_Apertado;
int comparaSequencia = 0;
bool status_de_partida = true;

//*****Funções*****//
void sequencia(int nivel);
void mostrarSequencia();
void inicializa();
bool confere_Jogada();
void mostrarNivel(int nivel);

void setup() {
  randomSeed(analogRead(0));

  // Configura LEDs como saída
  for (int i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
    pinMode(botao[i], INPUT);
  }

  // Configura pinos do display como saída
  const int segmentosPortas[7] = {a, b, c, d, e, f, g};
  for (int i = 0; i < 7; i++) {
    pinMode(segmentosPortas[i], OUTPUT);
  }

  Serial.begin(9600);

  inicializa();
  nivel = 0;
}

void loop() {
 //Gera uma sequência de acordo com o nível atual
  sequencia(nivel);
 // Mostra a sequência gerada ao jogador
  mostrarSequencia();
  // Verifica se o jogador acertou a sequência
  if (confere_Jogada()) {
    nivel++;
    Serial.print("Nivel atual: ");
    Serial.println(nivel);
    if (nivel == 9) {
      nivel = 0;
    } else {
      mostrarNivel(nivel);
    }
  } else {
    // Indicação de erro
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED[i], HIGH);
    }
    delay(1000);
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED[i], LOW);
    }
    delay(1000);

    // Reinicia o jogo
    memset(armazena_Sequencia, 0, sizeof(armazena_Sequencia));
    nivel = 0; 
    comparaSequencia = 0;
    status_de_partida = true; 
    mostrarNivel(nivel);
    Serial.println("voce perdeu!!");

    // Recomeça o jogo
    inicializa();
  }
}

// Inicializa a sequência inicial 
void inicializa() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], HIGH);
    delay(500);
    digitalWrite(LED[i], LOW);
    delay(500);
  }
  delay(500);
}

/* Gera uma sequência aleatória */
void sequencia(int nivel) {
  for (int i = 0; i < nivel; i++) {
    armazena_Sequencia[i] = random(4);
  }
}

/* Mostra a sequência de LEDs */
void mostrarSequencia() {
  for (int i = 0; i < nivel; i++) {
    digitalWrite(LED[armazena_Sequencia[i]], HIGH);
    delay(500);
    digitalWrite(LED[armazena_Sequencia[i]], LOW);
    delay(500);
  }
  delay(500);
}

/* Confere a jogada do usuário */
bool confere_Jogada() {
  for (int i = 0; i < nivel; i++) {
    bool jogou = false;
    while (!jogou) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(botao[j]) == HIGH) {
          botao_Apertado = j;
          digitalWrite(LED[j], HIGH);
          delay(500);
          digitalWrite(LED[j], LOW);
          delay(500);
          jogou = true;
        }
      }
    }
    if (armazena_Sequencia[comparaSequencia] != botao_Apertado) {
      status_de_partida = false;
      break;
    }
    comparaSequencia++;
  }
  comparaSequencia = 0;
  return status_de_partida;
}

/* Mostra o nível atual no display de 7 segmentos */
void mostrarNivel(int nivel) {
  const bool segmentos[10][7] = {
      {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},  // 0
      {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 1
      {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW}, // 2
      {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW}, // 3
      {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW}, // 4
      {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW}, // 5
      {LOW, HIGH, LOW, LOW, LOW, LOW, LOW}, // 6
      {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 7
      {LOW, LOW, LOW, LOW, LOW, LOW, LOW}, // 8
      {LOW, LOW, LOW, LOW, HIGH, LOW, LOW} // 9
  };

  const int segmentosPortas[7] = {a, b, c, d, e, f, g};

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentosPortas[i], segmentos[nivel][i]);
  }
  delay(2000);
}
