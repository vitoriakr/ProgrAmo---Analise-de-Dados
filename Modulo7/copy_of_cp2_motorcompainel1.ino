/*
* Checkpoint 2:
* Aluno: Vitória Kereski Da Rosa
*/
#include <LiquidCrystal.h>

#define H1 10 
#define H2 9  
#define RS 2 
#define EN 3 
#define BTN 8 
#define UPDATE_TIME 500 //ms
#define SPEED A5
/*------------------------------------------------------------------------*/
typedef enum{
  DRIVE_POSITION_FORWARD,
  DRIVE_POSITION_BACKWARD,
  DRIVE_POSITION_UNKNOWN
} drive_position_t;

/*------------------------------------------------------------------------*/
/**
 * @brief Exibe no display uma mensagem de boas vindas ao usuário com duração 
 * minima de 2segundos
 * 
 */
static void welcome(void);

static void updateDisplayDrivePosition(drive_position_t pos);

static void updateDisplayMotorSpeed(uint8_t speed);
/*------------------------------------------------------------------------*/
/**
 * @brief Atualiza o acionamento do motor de acordo com a posição
 * e a velocidade selecionado pelo usuário
 * 
 * @param speed valor de velocidade de 0 a 100 selecionado (o mesmo que é exibido)
 * @param pos posição selecionada pela chave seletora do câmbio
 * @param f_pin pino da ponte H com direção "para frente"
 * @param b_pin pino da ponte H com direção "para trás"
 */
static void controlMotor(uint8_t speed, drive_position_t pos, uint8_t f_pin, uint8_t b_pin);
/*------------------------------------------------------------------------*/
/**
 * @brief Lê o valor do câmbio no pino indicado
 * 
 * @param digitalPin pino para leitura
 * @return drive_position_t Valor lido
 */
static drive_position_t readSelectedPosition(uint8_t digitalPin);
/*------------------------------------------------------------------------*/
/**
 * @brief Lê o valor de velocidade do potênciometo
 * 
 * @param analogPin pino para leitura do canal AD
 * @return uint8_t valor convertido na faixa de 0-100
 */
static uint8_t readSpeed(uint8_t analogPin);
/*-----------------------------------------------------------------------*/

// Inicializa o objeto lcd (isso é código C++)
LiquidCrystal lcd(RS, EN, 4, 5, 6, 7);

void setup()
{
  Serial.begin(9600);

  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(BTN, INPUT);

  // Começa com o motor desligado
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  
  // Inicializa o display informando as dimensões
  lcd.begin(16,2);
  
  welcome();
}

void loop()
{
  
  drive_position_t selectedPosition;
  uint8_t selectedSpeed;
  while(true){
    selectedPosition = readSelectedPosition(BTN);
    selectedSpeed = readSpeed(SPEED);

  controlMotor(selectedSpeed, selectedPosition, H1, H2);
    updateDisplayDrivePosition(selectedPosition);
    updateDisplayMotorSpeed(selectedSpeed);

    Serial.print("Pos : ");
    Serial.print(selectedPosition);
    Serial.print("| Speed: ");
    Serial.println(selectedSpeed);

    delay(UPDATE_TIME);
  }
}

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
static drive_position_t readSelectedPosition(uint8_t digitalPin)
{
  uint8_t btnValue;
  btnValue = digitalRead(digitalPin);
  if(btnValue)
    return DRIVE_POSITION_FORWARD;
  else
    return DRIVE_POSITION_BACKWARD;
}
/*------------------------------------------------------------------------*/
static uint8_t readSpeed(uint8_t analogPin)
{
  uint16_t potValue;

  potValue = analogRead(analogPin);
  return map (potValue, 0, 1023, 0, 100);
}

/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
static void welcome(void){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Checkpoint02");
  delay(1000);
  lcd.clear();
  lcd.print("EDGE");
  delay(1000);
  lcd.clear();
}


static void updateDisplayDrivePosition(drive_position_t pos){
   lcd.setCursor(16, 0);
  if(pos == DRIVE_POSITION_FORWARD)
    lcd.print("R");
  else
    lcd.print("D");
} 
}

static void updateDisplayMotorSpeed(uint8_t speed){
  lcd.setCursor(0, 0);
  lcd.print(speed);
} 

static void controlMotor(uint8_t speed, drive_position_t pos, uint8_t f_pin, uint8_t b_pin){
  
}