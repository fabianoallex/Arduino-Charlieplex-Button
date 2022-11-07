#define NUM_PINS 4

const int pins[] = {2,3,4,5};

void init_pins(){
  for (int i = 0; i< NUM_PINS; i++) { 
    pinMode(pins[i], INPUT_PULLUP); 
    digitalWrite(pins[i], HIGH);
  }
}

byte readCharlieplexButons(int pin1, int pin2){
  init_pins();
  pinMode(pin1, OUTPUT);
  digitalWrite(pin1, LOW);
  return !digitalRead(pin2);
}

int getButton(){
  byte index_button = 0;
  for (int i=0; i<NUM_PINS; i++) { 
    for (int j=i+1; j<NUM_PINS; j++) { 
      if (i!=j) { 
        if (readCharlieplexButons(pins[j], pins[i])) {
          return index_button;
        }
        index_button++;
        if (readCharlieplexButons(pins[i], pins[j])) {
          return index_button;
        }
        index_button++;
      }
    }
  }
  return -1;  //-1 --> nenhum botão pressionado
}
  
int getButtonOnce(){
  static int lastVal = -1;
  static unsigned long m = 0;
  int val = getButton();
  if (lastVal != val && millis() > (m+100) ) { //M+100 -->DEBOUNCING 100ms
    lastVal = val;
    m = millis();
    return lastVal;
  } 
  return -1;
}

void setup() { 
  init_pins(); 
  Serial.begin(9600);
}

void loop() { 
  int button = getButtonOnce();
  if ( button >=0){
    Serial.println(button);
  }
  delay(10);   //necessário apenas no simulador.
}