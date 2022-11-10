#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define LDR A0
#define buzzer 9

int button[4] = {3, 4, 5, 6};
bool buttonState[4] = {0, 0, 0, 0};
bool lastButtonState[4] = {0, 0, 0, 0};
long currentTime[4] = {0, 0, 0, 0};
int debounceDelay = 30;
int timer1_counter;
int t1 = 0;
int startArduino = 0;

int light = 0;

int state = 0;                                                                                                // normal, timer, setting, alarm
int Ssec = 0, Ssecsec = 0, Sdsec = 0, Smin = 0, Sdmin = 0, Shour = 0, Sdhour = 0, Si = 0;                   // Setting
int Asec = 0, Asecsec = 0, Adsec = 0, Amin = 0, Admin = 0, Ahour = 0, Adhour = 0, Ai = 0;                   // Alarm
int Tsec = 0, Tsecsec = 0, Tdsec = 0, Tmin = 0, Tdmin = 0, Thour = 0, Tdhour = 0, timerCounter = 0, Ti = 0 ; // Timer
int Nsec = 0, Nsecsec = 0, Ndsec = 0, Nmin = 0, Ndmin = 0, Nhour = 0, Ndhour = 0;                           // Normal
int sec = 0, secsec = 0, dsec = 0, minute = 0, dmin = 0, hour = 0, dhour = 0;
float time1secf = 0;
bool enableTimer = false;
int timerCheck = 0;
float t2 = 0;

Adafruit_SSD1306 OLED(OLED_RESET);

void setup() //
{
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  for (size_t i = 0; i < 4; i++)
  {
    pinMode(button[i], INPUT);
  }
  Nsec = EEPROM.read(0);
  Ndsec = EEPROM.read(1);
  Nmin = EEPROM.read(2);
  Ndmin = EEPROM.read(3);
  Nhour = EEPROM.read(4);
  Ndhour = EEPROM.read(5);
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;     // Set Mode of Timer : Normal Mode
  TCCR1B = 0;
  timer1_counter = 3036 + 31250; // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter; // preload timer
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect) // interrupt service routine
{
  TCNT1 = timer1_counter; // preload timer
  t1 += (timerCheck++) % 2;
  //t2 += 0.5;
}

bool debounce(int i) //
{
  bool reading = digitalRead(button[i]);
  bool updates = 0;
  if (lastButtonState[i] != reading)
  {
    currentTime[i] = millis();
  }
  if (millis() - currentTime[i] > debounceDelay)
  {
    if (buttonState[i] != reading)
    {
      buttonState[i] = reading;
      if (buttonState[i] == 1)
      {
        updates = 1;
      }
    }
  }
  lastButtonState[i] = reading;
  // Serial.println(updates);
  return updates;
}

void clockDisplay(int Rhour2, int Rhour, int Rminute2, int Rminute, int Rsecond2, int Rsecond) {
  dhour = Rhour2;
  hour = Rhour;
  dmin = Rminute2;
  minute = Rminute;
  dsec = Rsecond2;
  sec = Rsecond;
}

void stateDisplay() {
  if ( state == 0 ) {
    OLED.print("Normal");
  }
  else if ( state == 1 ) {
    OLED.print("Setting");
  }
  else if ( state == 2 ) {
    OLED.print("Alarm");
  }
  else if ( state == 3 ) {
    OLED.print("Counter");
  }
}

void pointerDisplay(int pointer) {
  int pos = 97 - (pointer * 13) - (pointer / 2 * 10);
  OLED.setCursor(pos, 25);
  OLED.setTextSize(1);
  OLED.print("^");
}

void NclockSysytem() {
  if (Nsecsec >= 1)
  {
    Nsec++;
    Nsecsec -= 1;
  }
  if (Nsec >= 10)
  {
    Ndsec++;
    Nsec -= 10;
  }
  if (Ndsec >= 6)
  {
    Nmin++;
    Ndsec -= 6;
  }
  if (Nmin >= 10)
  {
    Nmin -= 10;
    Ndmin++;
  }
  if (Ndmin >= 6)
  {
    Nhour++;
    Ndmin -= 6;
  }
  if (Nhour >= 10)
  {
    Ndhour++;
    Nhour -= 10;
  }
  if (Ndhour == 2 && Nhour == 4)
  {
    Ndhour = 0;
    Nhour = 0;
  }
}

void TclockSystem() {
  if (Tsecsec >= 1)
  {
    Tsec++;
    Tsecsec -= 1;
  }
  if (Tsec >= 10)
  {
    Tdsec++;
    Tsec -= 10;
  }
  if (Tdsec >= 6)
  {
    Tmin++;
    Tdsec -= 6;
  }
  if (Tmin >= 10)
  {
    Tmin -= 10;
    Tdmin++;
  }
  if (Tdmin >= 6)
  {
    Thour++;
    Tdmin -= 6;
  }
  if (Thour >= 10)
  {
    Tdhour++;
    Thour -= 10;
  }
  if (Tdhour == 2 && Thour == 4)
  {
    Tdhour = 0;
    Thour = 0;
  }
}

void eepRom() {
  EEPROM.update(0, (char)Nsec);
  EEPROM.update(1, (char)Ndsec);
  EEPROM.update(2, (char)Nmin);
  EEPROM.update(3, (char)Ndmin);
  EEPROM.update(4, (char)Nhour);
  EEPROM.update(5, (char)Ndhour);
  //  EEPROM.write(0, (char)Nsec);
  //  EEPROM.write(1, (char)Ndsec);
  //  EEPROM.write(2, (char)Nmin);
  //  EEPROM.write(3, (char)Ndmin);
  //  EEPROM.write(4, (char)Nhour);
  //  EEPROM.write(5, (char)Ndhour);
}

void clockDisplayOut() {
  OLED.print((int)dhour);
  OLED.print((int)hour);
  OLED.print(".");
  OLED.print((int)dmin);
  OLED.print((int)minute);
  OLED.print(".");
  OLED.print((int)dsec);
  OLED.println((int)sec);
}

void loop() //
{
  light = analogRead(LDR);
  if (light >= 450) {
    OLED.dim(1);
  }
  else {
    OLED.dim(0);
  }

  OLED.clearDisplay();

  OLED.setTextColor(WHITE);

  OLED.setCursor(10, 0);
  OLED.setTextSize(1);
  stateDisplay();

  OLED.setCursor(10, 10);
  OLED.setTextSize(2);
  clockDisplayOut();

  if (debounce(0) == 1)
  {
    state++;
    state %= 4;
  }

  //นับเวลา
  if (state != 1)
  {
    t2 = t1;
    time1secf = t1;
    Nsecsec = time1secf;
    NclockSysytem();
    t1 = 0;
    //eepRom();
  }
  //นาฬิกาปรกติ normal
  if (state == 0)
  {
    clockDisplay(Ndhour, Nhour, Ndmin, Nmin, Ndsec, Nsec);
  }
  //ตั้งเวลา setting
  if (state == 1)
  {
    clockDisplay(Ndhour, Nhour, Ndmin, Nmin, Ndsec, Nsec);
    pointerDisplay(Si);
    if (debounce(1) == 1)
    {
      Si = (Si + 1) % 6;
    }
    if (debounce(2) == 1)
    {
      if (Si == 0)
      {
        Nsec = (Nsec + 1) % 10;
      }
      else if (Si == 1)
      {
        Ndsec = (Ndsec + 1) % 6;
      }
      if (Si == 2)
      {
        Nmin = (Nmin + 1) % 10;
      }
      if (Si == 3)
      {
        Ndmin = (Ndmin + 1 ) % 6;
      }
      if (Si == 4)
      {
        Nhour = (Nhour + 1) % 10;
        if (Ndhour == 2 && Nhour >= 4)
          Nhour = 0;
      }
      if (Si == 5)
      {
        Ndhour = (Ndhour + 1 ) % 3;
        if (Ndhour == 2 && Nhour >= 4)
          Ndhour = 0;
      }
    }
    if (debounce(3) == 1)
    {
      if (Si == 0)
      {
        Nsec--;
        if (Nsec <= -1)
          Nsec = 9;
      }
      else if (Si == 1)
      {
        Ndsec--;
        if (Ndsec <= -1)
          Ndsec = 5;
      }
      if (Si == 2)
      {
        Nmin--;
        if (Nmin <= -1)
          Nmin = 9;
      }
      if (Si == 3)
      {
        Ndmin--;
        if (Ndmin <= -1)
          Ndmin = 5;
      }
      if (Si == 4)
      {
        Nhour--;
        if (Nhour <= -1)
          Nhour = 9;
      }
      if (Si == 5)
      {
        Ndhour--;
        if (Ndhour <= -1)
          Ndhour = 2;
      }
    }
  }
  //ตั้งนาฬิกาปลุก Alarm
  if (state == 2)
  {
    clockDisplay(Adhour, Ahour, Admin, Amin, Adsec, Asec);
    pointerDisplay(Ai);
    if (debounce(1) == 1)
    {
      Ai = ( Ai + 1 ) % 6;
    }
    if (debounce(2) == 1)
    {
      if (Ai == 0)
      {
        Asec = (Asec + 1) % 10;
      }
      else if (Ai == 1)
      {
        Adsec = (Adsec + 1 ) % 6;
      }
      if (Ai == 2)
      {
        Amin = (Amin + 1 ) % 10;
      }
      if (Ai == 3)
      {
        Admin = (Admin + 1) % 6;
      }
      if (Ai == 4)
      {
        Ahour = (Ahour + 1) % 10;
        if (Adhour == 2 && Ahour >= 4) {
          Ahour = 0;
        }

      }
      if (Ai == 5)
      {
        Adhour = (Adhour + 1) % 3;
        if (Adhour == 2 && Ahour >= 4)
          Adhour = 0;
      }
    }
    if (debounce(3) == 1)
    {
      if (Ai == 0)
      {
        Asec--;
        if (Asec <= -1)
          Asec = 9;
      }
      else if (Ai == 1)
      {
        Adsec--;
        if (Adsec <= -1)
          Adsec = 5;
      }
      if (Ai == 2)
      {
        Amin--;
        if (
          Amin <= -1)
          Amin = 9;
      }
      if (Ai == 3)
      {
        Admin--;
        if (Admin <= -1)
          Admin = 5;
      }
      if (Ai == 4)
      {
        Ahour--;
        if (Ahour <= -1)
          Ahour = 9;
      }
      if (Ai == 5)
      {
        Adhour--;
        if (Adhour <= -1)
          Adhour = 2;
      }
    }
  }
  //จับเวลา Timer
  if (state == 3)
  {
    clockDisplay(Tdhour, Thour, Tdmin, Tmin, Tdsec, Tsec);
    if (debounce(1) == 1)
    {
      enableTimer = !enableTimer;
      timerCounter = t2;
    }
    if (debounce(2) == 1)
    {
      Tdhour = 0, Thour = 0, Tdmin = 0, Tmin = 0, Tdsec = 0, Tsec = 0;
    }
    if (enableTimer == true)
    {
      Tsecsec = t2 - timerCounter;
      TclockSystem();
    }
  }
  //บูมมมมมมมมมมมมมมมมมมมมมม
  if (Nsec == Asec && Ndsec == Adsec && Nmin == Amin && Ndmin == Admin && Nhour == Ahour && Ndhour == Adhour)
  {
    tone(buzzer, 3000, 1000);
    tone(buzzer, 400, 1000);
    tone(buzzer, 3000, 1000);
    tone(buzzer, 400, 1000);
    tone(buzzer, 3000, 1000);
    tone(buzzer, 400, 1000);
  }
  OLED.display();
}
