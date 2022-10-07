#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 OLED(OLED_RESET);
int table[6][6] = {{0, 0, 0, 0, 0, 0},
  {0, 1024, 1024, 0, 0, 0},
  {0, 16, 64, 0, 0, 0},
  {0, 8, 16, 32, 16, 0},
  {0, 2, 2, 4, 8, 0},
  {0, 0, 0, 0, 0, 0}
};
int tube[6][6] {0};
int buzz = 11;
int button[4] = {4, 5, 6, 7}; //Up, Down ,Left, Right
int buttonState[4] = {0, 0, 0, 0};
int lastState[4] = {0, 0, 0, 0};
long lastTime[4] = {0, 0, 0, 0};
int movable = 1;
int win = 0;
int x = 0;
int y = 0;
int ran = 0;
int same = 1;
void setup() {
  Serial.begin(115200);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  //pinMode(buzz,OUTPUT);
  pinMode(button[0], INPUT);
  pinMode(button[1], INPUT);
  pinMode(button[2], INPUT);
  pinMode(button[3], INPUT);
  randomSeed(analogRead(A0));
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(10, 1);
  OLED.setTextSize(1);
  OLED.println("2048 GAME");
}
void loop() {
  if (win == 0 && movable == 1) {
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    ran = 0;
    for (int i = 1; i < 5; i++) // OLED.print
    {
      for (int j = 1; j < 5; j++)
      {
        int bottle = table[i][j];
        for (int k = 0; k < 4; k++) {
          if (bottle / 10 == 0)
            OLED.print(" ");
          bottle /= 10;
        }
        OLED.print(table[i][j]);
        tube[i][j] = table[i][j];
      }
      OLED.print("\n");
    }
    movable = 0;
    for (int i = 1; i < 5; i++) // check movable
    {
      for (int j = 1; j < 5; j++)
      {
        if (table[i][j] == 0 ||
            (table[i + 1][j] == table[i][j]) ||
            (table[i - 1][j] == table[i][j]) ||
            (table[i][j + 1] == table[i][j]) ||
            (table[i][j - 1] == table[i][j]))
        {
          movable = 1;
          break;
        }
      }
    }
    for (int p = 0; p < 4; p++)
    {
      int reading = digitalRead(button[p]);
      if (reading != lastState[p]) {
        lastTime[p] = millis();
      }
      if (millis() - lastTime[p] > 50) {
        if (reading != buttonState[p]) {
          buttonState[p] = reading;
          if (buttonState[0] == 1)
          {
            tone(buzz, 2000, 100);
            Serial.println("dog");
            for (int col = 1; col < 5; col++)
            {
              for (int cur = 1; cur < 5; cur++)
              {
                if (table[cur][col] == 0)
                {
                  for (int i = cur + 1; i < 5; i++)
                  {
                    if (table[i][col] != 0)
                    {
                      table[cur][col] = table[i][col];
                      table[i][col] = 0;
                      break;
                    }
                  }
                }
                if (table[cur][col] != 0)
                {
                  for (int i = cur + 1; i < 5; i++)
                  {
                    if (table[i][col] == table[cur][col])
                    {
                      table[cur][col] *= 2;
                      if (table[cur][col] == 2048)
                        win = 1;
                      table[i][col] = 0;
                      break;
                    }
                    else if (table[i][col] != table[cur][col] && table[i][col] != 0)
                      break;
                  }
                }
              }
            }
          }
          if (buttonState[1] == 1)
          {
            tone(buzz, 2000, 100);
            for (int col = 1; col < 5; col++)
            {
              for (int cur = 4; cur >= 1; cur--)
              {
                if (table[cur][col] == 0)
                {
                  for (int i = cur - 1; i >= 1; i--)
                  {
                    if (table[i][col] != 0)
                    {
                      table[cur][col] = table[i][col];
                      table[i][col] = 0;
                      break;
                    }
                  }
                }
                if (table[cur][col] != 0)
                {
                  for (int i = cur - 1; i >= 1; i--)
                  {
                    if (table[i][col] == table[cur][col])
                    {
                      table[cur][col] *= 2;
                      if (table[cur][col] == 2048)
                        win = 1;
                      table[i][col] = 0;
                      break;
                    }
                    else if (table[i][col] != table[cur][col] && table[i][col] != 0)
                      break;
                  }
                }
              }
            }
          }
          if (buttonState[2] == 1)
          {
            tone(buzz, 2000, 100);
            for (int col = 1; col < 5; col++)
            {
              for (int cur = 1; cur < 5; cur++)
              {
                if (table[col][cur] == 0)
                {
                  for (int i = cur + 1; i < 5; i++)
                  {
                    if (table[col][i] != 0)
                    {
                      table[col][cur] = table[col][i];
                      table[col][i] = 0;
                      break;
                    }
                  }
                }
                if (table[col][cur] != 0)
                {
                  for (int i = cur + 1; i < 5; i++)
                  {
                    if (table[col][i] == table[col][cur])
                    {
                      table[col][cur] *= 2;
                      if (table[col][cur] == 2048)
                        win = 1;
                      table[col][i] = 0;
                      break;
                    }
                    else if (table[col][i] != table[col][cur] && table[col][i] != 0)
                      break;
                  }
                }
              }
            }
          }
          if (buttonState[3] == 1)
          {
            tone(buzz, 2000, 100);
            for (int col = 1; col < 5; col++)
            {
              for (int cur = 4; cur >= 1; cur--)
              {
                if (table[col][cur] == 0)
                {
                  for (int i = cur - 1; i >= 1; i--)
                  {
                    if (table[col][i] != 0)
                    {
                      table[col][cur] = table[col][i];
                      table[col][i] = 0;
                      break;
                    }
                  }
                }
                if (table[col][cur] != 0)
                {
                  for (int i = cur - 1; i >= 1; i--)
                  {
                    if (table[col][i] == table[col][cur])
                    {
                      table[col][cur] *= 2;
                      if (table[col][cur] == 2048)
                        win = 1;
                      table[col][i] = 0;
                      break;
                    }
                    else if (table[col][i] != table[col][cur] && table[col][i] != 0)
                      break;
                  }
                }
              }
            }
          }
        }
      }
      lastState[p] = reading;
    }
    same = 1;
    for (int i = 1; i < 5; i++)
    {
      for (int j = 1; j < 5; j++)
      {
        if (table[i][j] != tube[i][j])
        { same = 0;
          break;
        }
      }
    }
    x = rand() % 4 + 1;
    y = rand() % 4 + 1;
    if (same == 0)
    {
      while (table[x][y] != 0) // rand2
      {
        x = rand() % 4 + 1;
        y = rand() % 4 + 1;
        if (table[x][y] == 0)
          break;
      }
      table[x][y] = 2;
    }

  }
  else if (win == 1)
  {
    OLED.clearDisplay();
    OLED.setCursor(8, 10);
    OLED.println(" YOU WIN");
    OLED.print(" 2048 GAME.");
    OLED.display();
    win = 0;
    movable = 1;
    delay(5000);
    for (int i = 1; i < 5 ; i++)
    {
      for (int j = 1 ; j < 5; j++)
        table[i][j] = 0;
    }
    table[x][y] = 2;
    x = rand() % 4 + 1;
    y = rand() % 4 + 1;
    table[x][y] = 2;
  }
  else if (movable == 0)
  {
    OLED.clearDisplay();
    OLED.setCursor(8, 10);
    OLED.println("NICE TRY");
    OLED.display();
    win = 0;
    movable = 1;
    delay(5000);
    for (int i = 1; i < 5 ; i++)
    {
      for (int j = 1 ; j < 5; j++)
        table[i][j] = 0;
    }
    table[x][y] = 2;
    x = rand() % 4 + 1;
    y = rand() % 4 + 1;
    table[x][y] = 2;
  }
  OLED.display();
}
