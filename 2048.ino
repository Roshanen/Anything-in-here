#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 OLED(OLED_RESET);
int table[4][4] = {{0, 0, 0, 0},
  {0, 0, 0, 0},
  {8, 16, 0, 0},
  {2, 2, 4, 0}
};
int tube[4][4] {0};
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

  if (win == 0) {
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    ran = 0;
    for (int i = 0; i < 4; i++) // OLED.print
    {
      for (int j = 0; j < 4; j++)
      {
        int bottle = table[i][j];
        for (int k = 0; k < 4; k++) {
          if (bottle / 10 == 0)
            OLED.print(" ");
          bottle /= 10;
        }
        OLED.print(table[i][j]);
        if (table[i][j] == 0)
          ran = 1;
        tube[i][j] = table[i][j];
      }
      OLED.print("\n");
    }
    movable = 0;
    for (int i = 0; i < 4; i++) // check movable
    {
      for (int j = 0; j < 4; j++)
      {
        if (table[i][j] == 0 ||
            (table[i + 1][j] == table[i][j] && (i + 1) < 4) ||
            (table[i - 1][j] == table[i][j] && (i - 1) >= 0) ||
            (table[i][j + 1] == table[i][j] && (j + 1) < 4) ||
            (table[i][j - 1] == table[i][j] && (j - 1) >= 0))
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
            for (int col = 0; col < 4; col++)
            {
              for (int cur = 0; cur < 4; cur++)
              {
                if (table[cur][col] == 0)
                {
                  for (int i = cur + 1; i < 4; i++)
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
                  for (int i = cur + 1; i < 4; i++)
                  {
                    if (table[i][col] == table[cur][col])
                    {
                      table[cur][col] *= 2;
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
            for (int col = 0; col < 4; col++)
            {
              for (int cur = 3; cur >= 0; cur--)
              {
                if (table[cur][col] == 0)
                {
                  for (int i = cur - 1; i >= 0; i--)
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
                  for (int i = cur - 1; i >= 0; i--)
                  {
                    if (table[i][col] == table[cur][col])
                    {
                      table[cur][col] *= 2;
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
            for (int col = 0; col < 4; col++)
            {
              for (int cur = 0; cur < 4; cur++)
              {
                if (table[col][cur] == 0)
                {
                  for (int i = cur + 1; i < 4; i++)
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
                  for (int i = cur + 1; i < 4; i++)
                  {
                    if (table[col][i] == table[col][cur])
                    {
                      table[col][cur] *= 2;
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
            for (int col = 0; col < 4; col++)
            {
              for (int cur = 3; cur >= 0; cur--)
              {
                if (table[col][cur] == 0)
                {
                  for (int i = cur - 1; i >= 0; i--)
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
                  for (int i = cur - 1; i >= 0; i--)
                  {
                    if (table[col][i] == table[col][cur])
                    {
                      table[col][cur] *= 2;
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
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (table[i][j] != tube[i][j])
          same = 0;
        break;
      }
    }
    while (table[x][y] != 0 && ran == 1 && same == 0)
    {
      x = random(4);
      y = random(4);
    }
    table[x][y] = 2;

  }
  else if (win == 1)
  {
    OLED.clearDisplay();
    OLED.setCursor(8, 10);
    OLED.println(" YOU WIN");
    OLED.print(" 2048 GAME.");
    OLED.display();
  }
  OLED.display();
}
