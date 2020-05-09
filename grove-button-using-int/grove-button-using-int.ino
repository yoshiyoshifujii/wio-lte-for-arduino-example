#include <WioLTEforArduino.h>

// You can use WIOLTE_(D20|A4|A6) with `Wio.PowerSupplyGrove(true);`
#define BUTTON_PIN  (WIOLTE_D20)

#define COLOR_ON	127, 127, 127
#define COLOR_OFF	  0,   0,   0

#define BUZZER_PIN      (WIOLTE_D38)
#define BUZZER_ON_TIME  (100)

WioLTE Wio;

volatile bool StateChanged = false;
volatile bool State = false;

void change_state()
{
  State = !State;
  StateChanged = true;
}

void setup()
{
  Wio.Init();
  Wio.PowerSupplyGrove(true);

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, change_state, RISING);
  
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  if (StateChanged) {
    SerialUSB.print(State ? '*' : '.');

    if (State) {
      Wio.LedSetRGB(COLOR_ON);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(BUZZER_ON_TIME);
      digitalWrite(BUZZER_PIN, LOW);
    }
    else {
      Wio.LedSetRGB(COLOR_OFF);
    }

	StateChanged = false;
  }
}
