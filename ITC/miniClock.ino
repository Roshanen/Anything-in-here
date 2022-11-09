#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
int button[4] = { 3, 4, 5, 6 };
bool buttonState[4] = { 0, 0, 0, 0 };
bool lastButtonState[4] = { 0, 0, 0, 0 };
long currentTime[4] = { 0, 0, 0, 0 };
int debounceDelay = 50;
int timer1_counter;
int t1 = 0;

float time1secf = 0;
char state = 'n';  // normal, timer, setting, alarm
//char timestr[50];
float Ssec = 0, Ssecsec = 0, Sdsec = 0, Smin = 0, Sdmin = 0, Shour = 0, Sdhour = 0, Si = 0;
float Asec = 0, Asecsec = 0, Adsec = 0, Amin = 0, Admin = 0, Ahour = 0, Adhour = 0, Ai = 0;
float Tsec = 0, Tsecsec = 0, Tdsec = 0, Tmin = 0, Tdmin = 0, Thour = 0, Tdhour = 0, Ti = 0, Ttime1secf = 0;
bool Ttimming = false;
float sec = 0, secsec = 0, dsec = 0, min = rand() % 10, dmin = rand() % 6, hour = rand() % 10, dhour = rand() % 2;

Adafruit_SSD1306 OLED(OLED_RESET);

void setup()  //
{
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  for (size_t i = 0; i < 4; i++) {
    pinMode(button[i], INPUT);
  }
  noInterrupts();  // disable all interrupts
  TCCR1A = 0;      // Set Mode of Timer : Normal Mode
  TCCR1B = 0;
  timer1_counter = 3036;   // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter;  // preload timer
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << TOIE1);  // enable timer overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect)  // interrupt service routine
{
  TCNT1 = timer1_counter;  // preload timer
  //Serial.println(t1++);
}

int debounce(int i)  //
{
  bool reading = digitalRead(button[i]);
  bool update = 0;
  if (lastButtonState[i] != reading) {
    currentTime[i] = millis();
  }
  if (millis() - currentTime[i] > debounceDelay) {
    if (buttonState[i] != reading) {
      buttonState[i] = reading;
      Serial.println(reading);
      update = 1;
    }
  }
  lastButtonState[i] = reading;
  return update;
}


void loop()  //
{
  for ( size_t i = 0 ; i < 4 ; i++ ){
    debounce(i);
  }
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(10,0);
  OLED.setTextSize(2);
  if (buttonState[0] == 1 ) {
    if (state == 'n') {
      state = 's';
      Sdhour = dhour;
      Shour = hour;
      Smin = min;
      Sdmin = dmin;
      Ssec = sec;
      Sdsec = dsec;
      Si = 0;
    } else if (state == 's') {

      state = 'n';
      dhour = Sdhour;
      hour = Shour;
      min = Smin;
      dmin = Sdmin;
      sec = Ssec;
      dsec = Sdsec;
    }
  }
  if (buttonState[1] == 1 ) {
    if (state == 'n') {
      state = 'a';
      Adhour = dhour;
      Ahour = hour;
      Amin = min;
      Admin = dmin;
      Asec = sec;
      Adsec = dsec;
      Ai = 0;
    }
    if (state == 'a') {
      state = 'n';
    }
  }
  if (buttonState[2] == 1 ) {
    if (state == 'n')
      state = 't';
    else if (state == 't')
      state = 'n';
    Tsec = 0, Tsecsec = 0, Tdsec = 0, Tmin = 0, Tdmin = 0, Thour = 0, Tdhour = 0, Ti = 0, Ttimming = false;
  }

  //นับเวลา
  if (state != 's') {
    time1secf = t1;
    secsec += time1secf;
    if (secsec >= 1) {
      sec++;
      secsec -= 1;
    }
    if (sec >= 10) {
      dsec++;
      sec -= 10;
    }
    if (dsec >= 6) {
      min++;
      dsec -= 6;
    }
    if (min >= 10) {
      min -= 10;
      dmin++;
    }
    if (dmin >= 6) {
      hour++;
      dmin -= 6;
    }
    if (hour >= 10) {
      dhour++;
      hour -= 10;
    }
    if (dhour == 2 && hour == 4) {
      dhour = 0;
      hour = 0;
    }
    t1 = 0;
  }
  //นาฬิกาปรกติ
  if (state == 'n') {
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", dhour, hour, dmin, min, dsec, sec);
    OLED.print((int)dhour);
    OLED.print((int)hour);
    OLED.print(".");
    OLED.print((int)dmin);
    OLED.print((int)min);
    OLED.print(".");
    OLED.print((int)dsec);
    OLED.print((int)sec);
  }
  //ตั้งเวลา
  if (state == 's') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      Si++;
    }
    if (buttonState[1] == 1 && debounce(1) == 1) {
      Si--;
    }
    if (Si >= 6)
      Si = 0;
    if (Si <= -1)
      Si = 5;
    if (buttonState[2] == 1 && debounce(2) == 1) {
      if (Si == 0) {
        Ssec++;
        if (Ssec >= 10)
          Ssec = 0;
      } else if (Si == 1) {
        Sdsec++;
        if (Sdsec >= 6)
          Sdsec = 0;
      }
      if (Si == 2) {
        Smin++;
        if (Smin >= 10)
          Smin = 0;
      }
      if (Si == 3) {
        Sdmin++;
        if (Sdmin >= 6)
          Sdmin = 0;
      }
      if (Si == 4) {
        Shour++;
        if (Shour >= 10)
          Shour = 0;
        if (Sdhour == 2 && Shour >= 4)
          Shour = 0;
      }
      if (Si == 5) {
        Sdhour++;
        if (Sdhour == 2 && Shour >= 4)
          Sdhour = 0;
        if (Sdhour >= 3)
          Sdhour = 0;
      }
    }
    if (buttonState[3] == 1 && debounce(3) == 1) {
      if (Si == 0) {
        Ssec--;
        if (Ssec <= -1)
          Ssec = 9;
      } else if (Si == 1) {
        Sdsec--;
        if (Sdsec <= -1)
          Sdsec = 5;
      }
      if (Si == 2) {
        Smin--;
        if (Smin <= -1)
          Smin = 9;
      }
      if (Si == 3) {
        Sdmin--;
        if (Sdmin <= -1)
          Sdmin = 5;
      }
      if (Si == 4) {
        Shour--;
        if (Shour <= -1)
          Shour = 9;
      }
      if (Si == 5) {
        Sdhour--;
        if (Sdhour <= -1)
          Sdhour = 2;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Sdhour, Shour, Sdmin, Smin, Sdsec, Ssec);
    OLED.print(Sdhour);
    OLED.print(Shour);
    OLED.print(".");
    OLED.print(Sdmin);
    OLED.print(Smin);
    OLED.print(".");
    OLED.print(Sdsec);
    OLED.print(Ssec);
  }
  //ตั้งนาฬิกาปลุก
  if (state == 'a') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      Ai++;
    }
    if (buttonState[1] == 1 && debounce(1) == 1) {
      Ai--;
    }
    if (Ai >= 6)
      Ai = 0;
    if (Ai <= -1)
      Ai = 5;
    if (buttonState[2] == 1 && debounce(2) == 1) {
      if (Ai == 0) {
        Asec++;
        if (Asec >= 10)
          Asec = 0;
      } else if (Ai == 1) {
        Adsec++;
        if (Adsec >= 6)
          Adsec = 0;
      }
      if (Ai == 2) {
        Amin++;
        if (Amin >= 10)
          Amin = 0;
      }
      if (Ai == 3) {
        Admin++;
        if (Admin >= 6)
          Admin = 0;
      }
      if (Ai == 4) {
        Ahour++;
        if (Ahour >= 10)
          Ahour = 0;
        if (Adhour == 2 && Ahour >= 4)
          Ahour = 0;
      }
      if (Ai == 5) {
        Adhour++;
        if (Adhour == 2 && Ahour >= 4)
          Adhour = 0;
        if (Adhour >= 3)
          Adhour = 0;
      }
    }
    if (buttonState[3] == 1 && debounce(3) == 1) {
      if (Ai == 0) {
        Asec--;
        if (Asec <= -1)
          Asec = 9;
      } else if (Ai == 1) {
        Adsec--;
        if (Adsec <= -1)
          Adsec = 5;
      }
      if (Ai == 2) {
        Amin--;
        if (
          Amin <= -1)
          Amin = 9;
      }
      if (Ai == 3) {
        Admin--;
        if (Admin <= -1)
          Admin = 5;
      }
      if (Ai == 4) {
        Ahour--;
        if (Ahour <= -1)
          Ahour = 9;
      }
      if (Ai == 5) {
        Adhour--;
        if (Adhour <= -1)
          Adhour = 2;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Adhour, Ahour, Admin, Amin, Adsec, Asec);
    OLED.print(Adhour);
    OLED.print(Ahour);
    OLED.print(".");
    OLED.print(Admin);
    OLED.print(Amin);
    OLED.print(".");
    OLED.print(Adsec);
    OLED.print(Asec);
  }
  //จับเวลา
  if (state == 't') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      if (Ttimming == false)
        Ttimming = true;
      else if (Ttimming == true)
        Ttimming = false;
    }
    if (Ttimming == true) {
      Ttime1secf = millis();
      Tsecsec += Ttime1secf;
      if (Tsecsec >= 1) {
        Tsec++;
        Tsecsec -= 1;
      }
      if (Tsec >= 10) {
        Tdsec++;
        Tsec -= 10;
      }
      if (Tdsec >= 6) {
        Tmin++;
        Tdsec -= 6;
      }
      if (Tmin >= 10) {
        Tmin -= 10;
        Tdmin++;
      }
      if (Tdmin >= 6) {
        Thour++;
        Tdmin -= 6;
      }
      if (Thour >= 10) {
        Tdhour++;
        Thour -= 10;
      }
      if (Tdhour == 2 && Thour == 4) {
        Tdhour = 0;
        Thour = 0;
      }
      if (buttonState[1] == 1 && debounce(1) == 1) {
        Tdhour = 0, Thour = 0, Tdmin = 0, Tmin = 0, Tdsec = 0, Tsec = 0;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Tdhour, Thour, Tdmin, Tmin, Tdsec, Tsec);
    OLED.print(Tdhour);
    OLED.print(Thour);
    OLED.print(".");
    OLED.print(Tdmin);
    OLED.print(Tmin);
    OLED.print(".");
    OLED.print(Tdsec);
    OLED.print(Tsec);
  }
  //บูมมมมมมมมมมมมมมมมมมมมมม
  if (sec == Asec && dsec == Adsec && min == Amin && dmin == Admin && hour == Ahour && dhour == Adhour) {
    //std::cout << "Wake up";
    tone(9, 800, 3000);
    tone(9, 600, 1000);
    tone(9, 800, 3000);
  }
  OLED.display();
}#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
int button[4] = { 3, 4, 5, 6 };
bool buttonState[4] = { 0, 0, 0, 0 };
bool lastButtonState[4] = { 0, 0, 0, 0 };
long currentTime[4] = { 0, 0, 0, 0 };
int debounceDelay = 50;
int timer1_counter;
int t1 = 0;

float time1secf = 0;
char state = 'n';  // normal, timer, setting, alarm
//char timestr[50];
float Ssec = 0, Ssecsec = 0, Sdsec = 0, Smin = 0, Sdmin = 0, Shour = 0, Sdhour = 0, Si = 0;
float Asec = 0, Asecsec = 0, Adsec = 0, Amin = 0, Admin = 0, Ahour = 0, Adhour = 0, Ai = 0;
float Tsec = 0, Tsecsec = 0, Tdsec = 0, Tmin = 0, Tdmin = 0, Thour = 0, Tdhour = 0, Ti = 0, Ttime1secf = 0;
bool Ttimming = false;
float sec = 0, secsec = 0, dsec = 0, min = rand() % 10, dmin = rand() % 6, hour = rand() % 10, dhour = rand() % 2;

Adafruit_SSD1306 OLED(OLED_RESET);

void setup()  //
{
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  for (size_t i = 0; i < 4; i++) {
    pinMode(button[i], INPUT);
  }
  noInterrupts();  // disable all interrupts
  TCCR1A = 0;      // Set Mode of Timer : Normal Mode
  TCCR1B = 0;
  timer1_counter = 3036;   // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter;  // preload timer
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << TOIE1);  // enable timer overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect)  // interrupt service routine
{
  TCNT1 = timer1_counter;  // preload timer
  //Serial.println(t1++);
}

int debounce(int i)  //
{
  bool reading = digitalRead(button[i]);
  bool update = 0;
  if (lastButtonState[i] != reading) {
    currentTime[i] = millis();
  }
  if (millis() - currentTime[i] > debounceDelay) {
    if (buttonState[i] != reading) {
      buttonState[i] = reading;
      Serial.println(reading);
      update = 1;
    }
  }
  lastButtonState[i] = reading;
  return update;
}


void loop()  //
{
  for ( size_t i = 0 ; i < 4 ; i++ ){
    debounce(i);
  }
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(10,0);
  OLED.setTextSize(2);
  if (buttonState[0] == 1 ) {
    if (state == 'n') {
      state = 's';
      Sdhour = dhour;
      Shour = hour;
      Smin = min;
      Sdmin = dmin;
      Ssec = sec;
      Sdsec = dsec;
      Si = 0;
    } else if (state == 's') {

      state = 'n';
      dhour = Sdhour;
      hour = Shour;
      min = Smin;
      dmin = Sdmin;
      sec = Ssec;
      dsec = Sdsec;
    }
  }
  if (buttonState[1] == 1 ) {
    if (state == 'n') {
      state = 'a';
      Adhour = dhour;
      Ahour = hour;
      Amin = min;
      Admin = dmin;
      Asec = sec;
      Adsec = dsec;
      Ai = 0;
    }
    if (state == 'a') {
      state = 'n';
    }
  }
  if (buttonState[2] == 1 ) {
    if (state == 'n')
      state = 't';
    else if (state == 't')
      state = 'n';
    Tsec = 0, Tsecsec = 0, Tdsec = 0, Tmin = 0, Tdmin = 0, Thour = 0, Tdhour = 0, Ti = 0, Ttimming = false;
  }

  //นับเวลา
  if (state != 's') {
    time1secf = t1;
    secsec += time1secf;
    if (secsec >= 1) {
      sec++;
      secsec -= 1;
    }
    if (sec >= 10) {
      dsec++;
      sec -= 10;
    }
    if (dsec >= 6) {
      min++;
      dsec -= 6;
    }
    if (min >= 10) {
      min -= 10;
      dmin++;
    }
    if (dmin >= 6) {
      hour++;
      dmin -= 6;
    }
    if (hour >= 10) {
      dhour++;
      hour -= 10;
    }
    if (dhour == 2 && hour == 4) {
      dhour = 0;
      hour = 0;
    }
    t1 = 0;
  }
  //นาฬิกาปรกติ
  if (state == 'n') {
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", dhour, hour, dmin, min, dsec, sec);
    OLED.print((int)dhour);
    OLED.print((int)hour);
    OLED.print(".");
    OLED.print((int)dmin);
    OLED.print((int)min);
    OLED.print(".");
    OLED.print((int)dsec);
    OLED.print((int)sec);
  }
  //ตั้งเวลา
  if (state == 's') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      Si++;
    }
    if (buttonState[1] == 1 && debounce(1) == 1) {
      Si--;
    }
    if (Si >= 6)
      Si = 0;
    if (Si <= -1)
      Si = 5;
    if (buttonState[2] == 1 && debounce(2) == 1) {
      if (Si == 0) {
        Ssec++;
        if (Ssec >= 10)
          Ssec = 0;
      } else if (Si == 1) {
        Sdsec++;
        if (Sdsec >= 6)
          Sdsec = 0;
      }
      if (Si == 2) {
        Smin++;
        if (Smin >= 10)
          Smin = 0;
      }
      if (Si == 3) {
        Sdmin++;
        if (Sdmin >= 6)
          Sdmin = 0;
      }
      if (Si == 4) {
        Shour++;
        if (Shour >= 10)
          Shour = 0;
        if (Sdhour == 2 && Shour >= 4)
          Shour = 0;
      }
      if (Si == 5) {
        Sdhour++;
        if (Sdhour == 2 && Shour >= 4)
          Sdhour = 0;
        if (Sdhour >= 3)
          Sdhour = 0;
      }
    }
    if (buttonState[3] == 1 && debounce(3) == 1) {
      if (Si == 0) {
        Ssec--;
        if (Ssec <= -1)
          Ssec = 9;
      } else if (Si == 1) {
        Sdsec--;
        if (Sdsec <= -1)
          Sdsec = 5;
      }
      if (Si == 2) {
        Smin--;
        if (Smin <= -1)
          Smin = 9;
      }
      if (Si == 3) {
        Sdmin--;
        if (Sdmin <= -1)
          Sdmin = 5;
      }
      if (Si == 4) {
        Shour--;
        if (Shour <= -1)
          Shour = 9;
      }
      if (Si == 5) {
        Sdhour--;
        if (Sdhour <= -1)
          Sdhour = 2;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Sdhour, Shour, Sdmin, Smin, Sdsec, Ssec);
    OLED.print(Sdhour);
    OLED.print(Shour);
    OLED.print(".");
    OLED.print(Sdmin);
    OLED.print(Smin);
    OLED.print(".");
    OLED.print(Sdsec);
    OLED.print(Ssec);
  }
  //ตั้งนาฬิกาปลุก
  if (state == 'a') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      Ai++;
    }
    if (buttonState[1] == 1 && debounce(1) == 1) {
      Ai--;
    }
    if (Ai >= 6)
      Ai = 0;
    if (Ai <= -1)
      Ai = 5;
    if (buttonState[2] == 1 && debounce(2) == 1) {
      if (Ai == 0) {
        Asec++;
        if (Asec >= 10)
          Asec = 0;
      } else if (Ai == 1) {
        Adsec++;
        if (Adsec >= 6)
          Adsec = 0;
      }
      if (Ai == 2) {
        Amin++;
        if (Amin >= 10)
          Amin = 0;
      }
      if (Ai == 3) {
        Admin++;
        if (Admin >= 6)
          Admin = 0;
      }
      if (Ai == 4) {
        Ahour++;
        if (Ahour >= 10)
          Ahour = 0;
        if (Adhour == 2 && Ahour >= 4)
          Ahour = 0;
      }
      if (Ai == 5) {
        Adhour++;
        if (Adhour == 2 && Ahour >= 4)
          Adhour = 0;
        if (Adhour >= 3)
          Adhour = 0;
      }
    }
    if (buttonState[3] == 1 && debounce(3) == 1) {
      if (Ai == 0) {
        Asec--;
        if (Asec <= -1)
          Asec = 9;
      } else if (Ai == 1) {
        Adsec--;
        if (Adsec <= -1)
          Adsec = 5;
      }
      if (Ai == 2) {
        Amin--;
        if (
          Amin <= -1)
          Amin = 9;
      }
      if (Ai == 3) {
        Admin--;
        if (Admin <= -1)
          Admin = 5;
      }
      if (Ai == 4) {
        Ahour--;
        if (Ahour <= -1)
          Ahour = 9;
      }
      if (Ai == 5) {
        Adhour--;
        if (Adhour <= -1)
          Adhour = 2;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Adhour, Ahour, Admin, Amin, Adsec, Asec);
    OLED.print(Adhour);
    OLED.print(Ahour);
    OLED.print(".");
    OLED.print(Admin);
    OLED.print(Amin);
    OLED.print(".");
    OLED.print(Adsec);
    OLED.print(Asec);
  }
  //จับเวลา
  if (state == 't') {
    if (buttonState[0] == 1 && debounce(0) == 1) {
      if (Ttimming == false)
        Ttimming = true;
      else if (Ttimming == true)
        Ttimming = false;
    }
    if (Ttimming == true) {
      Ttime1secf = millis();
      Tsecsec += Ttime1secf;
      if (Tsecsec >= 1) {
        Tsec++;
        Tsecsec -= 1;
      }
      if (Tsec >= 10) {
        Tdsec++;
        Tsec -= 10;
      }
      if (Tdsec >= 6) {
        Tmin++;
        Tdsec -= 6;
      }
      if (Tmin >= 10) {
        Tmin -= 10;
        Tdmin++;
      }
      if (Tdmin >= 6) {
        Thour++;
        Tdmin -= 6;
      }
      if (Thour >= 10) {
        Tdhour++;
        Thour -= 10;
      }
      if (Tdhour == 2 && Thour == 4) {
        Tdhour = 0;
        Thour = 0;
      }
      if (buttonState[1] == 1 && debounce(1) == 1) {
        Tdhour = 0, Thour = 0, Tdmin = 0, Tmin = 0, Tdsec = 0, Tsec = 0;
      }
    }
    //sprintf_s(timestr, "%.0f%.0f : %.0f%.0f : %.0f%.0f", Tdhour, Thour, Tdmin, Tmin, Tdsec, Tsec);
    OLED.print(Tdhour);
    OLED.print(Thour);
    OLED.print(".");
    OLED.print(Tdmin);
    OLED.print(Tmin);
    OLED.print(".");
    OLED.print(Tdsec);
    OLED.print(Tsec);
  }
  //บูมมมมมมมมมมมมมมมมมมมมมม
  if (sec == Asec && dsec == Adsec && min == Amin && dmin == Admin && hour == Ahour && dhour == Adhour) {
    //std::cout << "Wake up";
    tone(9, 800, 3000);
    tone(9, 600, 1000);
    tone(9, 800, 3000);
  }
  OLED.display();
}
