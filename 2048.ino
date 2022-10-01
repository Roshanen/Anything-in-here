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
int up = 4;
int down = 5;
int left = 6;
int right = 7;
int movable = 1;
int win = 0;
int x = 0;
int y = 0;
int ran = 0;
int same = 1;
void setup() {
  Serial.begin(115200);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
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
        OLED.print(table[i][j]);
        OLED.print("   ");
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
    int Up = digitalRead(up);
    if (Up) // Up
    {
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
    int Down = digitalRead(down);
    if (Down) // Down
    {
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
    int Left = digitalRead(left);
    if (Left) // Left
    {
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
    int Right = digitalRead(right);
    if (Right) // Right
    {
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
    OLED.setCursor(8,10);
    OLED.println(" YOU WIN");
    OLED.print(" 2048 GAME.");
    OLED.display();
  }
  OLED.display();
  delay(50);
}
