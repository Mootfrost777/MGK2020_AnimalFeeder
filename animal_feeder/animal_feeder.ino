
// Подключаем библиотеки для работы
// библиотека для работы с RFID/NFC
#include <Adafruit_PN532.h>
#include <Wire.h>
#include <TroykaRTC.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
//#include <SoftwareSerial.h>
//
//
// ПЕРВЫЙ ВАРИАНТ НАБОРА ПЕРЕМЕННЫХ
//
//1 ЛОТОК "котенок": 3-х разовое питание, время открывания 0,5 сек (500 мсек)
// Время первого кормления 1 лотка
#define FEED_HOUR1_1_1     9
#define FEED_HOUR1_1_11    24
// Время второго кормления 1 лотка
#define FEED_HOUR1_1_2     12
#define FEED_HOUR1_1_21    13
// Время третьего кормления 1 лотка
#define FEED_HOUR1_1_3     19
#define FEED_HOUR1_1_31    20
//
// Время открывания
#define I_OPEN1_1 500

//2 ЛОТОК "кошка": 3-х разовое питание, время открывания 1 сек (1000 мсек)
// Время первого кормления 2 лотка
#define FEED_HOUR1_2_1     9
#define FEED_HOUR1_2_11    24
// Время второго кормления 2 лотка
#define FEED_HOUR1_2_2     11
#define FEED_HOUR1_2_21    12
// Время третьего кормления 2 лотка
#define FEED_HOUR1_2_3     18
#define FEED_HOUR1_2_31    19
//
// Время открывания
#define I_OPEN1_2 1000
//
//

// ВТОРОЙ ВАРИАНТ НАБОРА ПЕРЕМЕННЫХ
//
//1 ЛОТОК "кошка": 3-х разовое питание, время открывания 1 сек (1000 мсек)
// Время первого кормления 1 лотка
#define FEED_HOUR2_1_1     1
#define FEED_HOUR2_1_11    24
// Время второго кормления 1 лотка
#define FEED_HOUR2_1_2     11
#define FEED_HOUR2_1_21    12
// Время третьего кормления 1 лотка
#define FEED_HOUR2_1_3     19
#define FEED_HOUR2_1_31    20
//
// Время открывания
#define I_OPEN2_1 1000
//
// Время первого кормления 2 лотка
//2 ЛОТОК "маленькая собака": 2-х разовое питание, время открывания 1 сек (1000 мсек)
#define FEED_HOUR2_2_1     9
#define FEED_HOUR2_2_11    24
// Время второго кормления 2 лотка
#define FEED_HOUR2_2_2     11
#define FEED_HOUR2_2_21    11
// Время третьего кормления 2 лотка
#define FEED_HOUR2_2_3     18
#define FEED_HOUR2_2_31    19
//
// Время открывания
#define I_OPEN2_2 1000
//
//
// ТРЕТИЙ ВАРИАНТ НАБОРА ПЕРЕМЕННЫХ
//
//1 ЛОТОК "котенок": 3-х разовое питание, время открывания 0,5 сек (500 мсек)
#define FEED_HOUR3_1_1     
#define FEED_HOUR3_1_11    
// Время первого кормления 1 лотка
// Время второго кормления 1 лотка
#define FEED_HOUR3_1_2     12
#define FEED_HOUR3_1_21    12
// Время третьего кормления 1 лотка
#define FEED_HOUR3_1_3     19
#define FEED_HOUR3_1_31    20
//
// Время открывания
#define I_OPEN3_1 500

//2 ЛОТОК "маленькая собака": 2-х разовое питание, время открывания 1 сек (1000 мсек)
// Время первого кормления 2 лотка
#define FEED_HOUR3_2_1     9
#define FEED_HOUR3_2_11    24
// Время второго кормления 2 лотка
#define FEED_HOUR3_2_2     11
#define FEED_HOUR3_2_21    11
// Время третьего кормления 2 лотка
#define FEED_HOUR3_2_3     18
#define FEED_HOUR3_2_31    19
//
// Время открывания
#define I_OPEN3_2 1000
//
//

// Пины к которому подключаются сервоприводы.A0 и A1 не определены, вероятно это пин 1 и 2
#define SERVO_PIN  A0
#define SERVO_PIN1 A1
//
// Пин, к которому подключен сканер
#define PN532_IRQ  9
//
//


// Создает объект для работы со сканером и передаем ему два параметра
//первый номер пина прерывания
//второй - число 100
//от Adafruit был програмный сброс шилда
//в сканере FRIF/FNC 13,56 МГц этот пин не используется
//поэтом передает цифру большую,чем любой пин Arduino
Adafruit_PN532 nfc(PN532_IRQ, 100);


//Массивы, в корорые надо передать ID карт
uint8_t uidFirstCard[] = {0x04, 0x10, 0x7B, 0xB2, 0xF3, 0x59, 0x80};
uint8_t uidSecondCard[] = {0x04, 0x0F, 0x77, 0xB2, 0xF3, 0x59, 0x80};
uint8_t uidThirdCard[] = {0x04, 0x71, 0xC1, 0xDA, 0xA3, 0x40, 0x81};


//Функция, которая сравнивает два передних ID
//при совпадении возвращает значение TRUE
//и значение Falsу,если значение разные

boolean comparisonOfUid(uint8_t uidRead[8], uint8_t uidComp[8], uint8_t uidLen)
{
  for (uint8_t i = 0; i < uidLen; i++)
  {
    if (uidRead[i] != uidComp[i])
    {
      return false;
    }
    if (i == (uidLen) - 0x01) {
      return true;
    }
  }
}


// int val;
int x;
int buff = 1;
int buff_1 = 1;
int cl_1 = 1;
int cl_2 = 1;
int cl_12 = 1;
int cl_22 = 1;
int cl_13 = 1;
int cl_23 = 1;


// Флаг "Уже покормили"
boolean flag = true;

RTC clock;

Servo servo1;
Servo servo2;

void setup()
{
  Serial.begin(9600);

  // Инициализируем часы
  clock.begin();
  servo1.attach(SERVO_PIN);
  servo1.write(90);
  servo2.attach(SERVO_PIN1);
  servo2.write(90);
  // Устанавливаем время
  clock.set(__TIMESTAMP__);
  //
  //
  //
  //


  // инициализация RFID/NFC сканера
  nfc.begin();
  int versiondata = nfc.getFirmwareVersion();
  if (!versiondata)
  {
    while (1)
    {
      Serial.print("Didn't find RFID/NFC reader");
      delay(1000);
    }
  }
  Serial.println("Found RFID/NFC reader");
  // настраиваем модуль
  nfc.SAMConfig();
  Serial.println("Waiting for a card ...");
}

void serialEvent()
{
  //  if (Serial.available())
  //  {
  buff = Serial.parseInt();
  if (buff == 0)
  {
    buff = buff_1;
  }
  buff_1 = buff;
  Serial.println("event buff=");
  Serial.print(buff);

  //  }
}


//
//
void loop()
{
  // if (Serial.available())
  // {

  //   buff = Serial.parseInt();
  //   Serial.println("внутри serial buff=");
  //   Serial.print(buff);

  //      buff = Serial.peek();
  //    val = Serial.read();
  // }
  // Serial.println("VAL после SERIAL  VAL=");
  //  Serial.print(val);
  //Serial.println("buff после SERIAL  buff=");
  //Serial.print(buff);

  //    Serial.println("FEED_HOUR1_1_11=");
  //    Serial.print(FEED_HOUR1_1_11);

  //
  // СКАНИРОВАНИЕ КАРТЫ
  //
  // Сканируем карту и определяем принадлежность объекта, присваеваем переменной x значение 1 или 2
  uint8_t success;
  // буфер для хранения ID карты
  uint8_t uid[8];
  // размер буфера карты
  uint8_t uidLength;
  // слушаем новые метки
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  // если найдена карта

  if ((success) || (buff >= 0))
  {
    // выводим в консоль полученные данные
    Serial.println("Found a card");
    Serial.print("ID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("ID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");
    delay(1000);
    // присваеваем 1 переменной x если функция сравнения
    // ID вернёт true иначе оставляем всё как есть
    if (comparisonOfUid(uid, uidFirstCard, uidLength))
    {

      x = 1;

      //     Serial.println("после определения карты 1  val=");
      //      Serial.print(val);
      Serial.println("стоим после определения карты 1  buff=");
      Serial.print(buff);
      Serial.println("X=");
      Serial.print(x);
      Serial.println("FirstTAG");
      Serial.println("!!!!!!!!!");
    }
    else
    {
      // присваеваем 2 переменной x если функция сравнения
      // ID вернёт true иначе оставляем всё как есть
      if (comparisonOfUid(uid, uidSecondCard, uidLength))
      {

        x = 2;

        // Serial.println("после определения карты 2  VAL=");
        //       Serial.print(val);
        Serial.println("стоим после определения карты 2  buff=");
        Serial.print(buff);
        Serial.println("X=");
        Serial.print(x);

        Serial.println("SecondTAG");
      }
      else
      {
        x = 0;
        Serial.println("NoTAG");
      }
    }

    delay(100);
  }
  //
  //   ОКОНЧАНИЕ СКАНИРОВАНИЯ КАРТЫ !!!!
  //



  //
  //ПЕРВЫЙ НАБОР ПЕРЕМЕННЫХ КОРМУШЕК при buff=1
  //

  //  Serial.println("перед IF (VAL== '1')  VAL=");
  //  Serial.print(val);
  Serial.println("стоим перед IF (buff == 1)  buff=");
  Serial.print(buff);
  Serial.println("!!!!!!!!!");

  if (buff == 1)
  {
    //    Serial.println("после IF  VAL=1  VAL=");
    //    Serial.print(val);
    Serial.println("стоим после (IF buff=1)  buff=");
    Serial.print(buff);
    Serial.println("FEED_HOUR1_1_11=");
    Serial.print(FEED_HOUR1_1_11);
    Serial.println("!!!!!!!!!");

    if (x == 1)
    {
      clock.read();
      //    Serial.print(val);
      Serial.println("стоим после (if x=1) X=");
      Serial.print(x);
      Serial.println("buff=");
      Serial.print(buff);
      Serial.println("cl_1=");
      Serial.print(cl_1);
      Serial.println("!!!!!!!!!");


      // servo1.write(0);
      // delay(I_OPEN1);
      // servo1.write(90);
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR1_1_1) && (clock.getHour() < FEED_HOUR1_1_11) && cl_1 == 1)
          || ((clock.getHour() > FEED_HOUR1_1_2) && (clock.getHour() < FEED_HOUR1_1_21))
          || ((clock.getHour() > FEED_HOUR1_1_3) && (clock.getHour() < FEED_HOUR1_1_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        flag == false;
        cl_1 = 0;
        // Открываем заслонку
        //        Serial.print(val);
        Serial.println("стоим после первого кормления X=");
        Serial.print(x);
        Serial.println("KORM 1");
        Serial.println("cl_1=");
        Serial.print(cl_1);

        servo1.write(180);
        // Время открытия заслонки
        delay(I_OPEN1_1);

        servo1.write(90);
      } else
      {

        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo1.write(90);
        Serial.println("после else  cl_1=");
        Serial.print(cl_1);

      }
    }
    //
    //
    Serial.println("стоим перед (IF =2) x=");
    Serial.print(x);
    Serial.println("buff=");
    Serial.print(buff);

    //      Serial.println("PERED IF HA CERV 2");

    if (x == 2)
    {
      Serial.println("стоим после (IF = 2) x=");
      Serial.print(x);

      clock.read();
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR1_2_1) && (clock.getHour() < FEED_HOUR1_2_11) &&  cl_2 == 1)
          || ((clock.getHour() > FEED_HOUR1_2_2) && (clock.getHour() < FEED_HOUR1_2_21))
          || ((clock.getHour() > FEED_HOUR1_2_3) && (clock.getHour() < FEED_HOUR1_2_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        cl_2 = 0;
        flag == false;
        // Открываем заслонку
        Serial.println("KORM 2 x=");
        Serial.print(x);

        servo2.write(0);
        // Время открытия заслонки
        delay(I_OPEN1_2);
        servo2.write(90);
      } else
      {
        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo2.write(90);
      }
    }
    //
    //
    buff = 1;
    Serial.println("последняя скобка  buff=");
    Serial.print(buff);

  }

  // ОКОНЧАНИЕ ПЕРВОГО НАБОРА ПЕРЕМЕННЫХ


  //
  //ВТОРОЙ НАБОР ПЕРЕМЕННЫХ при ПРИЗНАКЕ = 2
  //
  if (buff == 2)
  {
    Serial.println("стоим после (IF  buff=2) перед (IF x=1) buff=");
    Serial.print(buff);
    Serial.println("FEED_HOUR2_1_11=");
    Serial.print(FEED_HOUR2_1_11);

    //
    Serial.println("х=");
    Serial.print(x);
    //Serial.println("PERED IF HA CERV 1");
    if (x == 1)
      //  Serial.print(val);
    {
      clock.read();
      //    Serial.print(val);
      Serial.print(x);
      // servo1.write(0);
      // delay(I_OPEN1);
      // servo1.write(90);
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR2_1_1) && (clock.getHour() < FEED_HOUR2_1_11)  &&  cl_12 == 1)
          || ((clock.getHour() > FEED_HOUR2_1_2) && (clock.getHour() < FEED_HOUR2_1_21))
          || ((clock.getHour() > FEED_HOUR2_1_3) && (clock.getHour() < FEED_HOUR2_1_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        cl_12 = 0;
        flag == false;
        // Открываем заслонку
        //        Serial.print(val);
        Serial.print(x);
        Serial.println("KORM 1");
        servo1.write(180);
        // Время открытия заслонки
        delay(I_OPEN2_1);

        servo1.write(90);
      } else
      {
        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo1.write(90);
      }
    }
    //
    //
    Serial.println("стоим перед (IF x=2) х=");
    Serial.print(x);
    Serial.println("buff=");
    Serial.print(buff);

    if (x == 2)
    {
      Serial.println("стоим после (IF x=2) х=");
      Serial.print(x);
      Serial.println("buff=");
      Serial.print(buff);


      clock.read();
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR2_2_1) && (clock.getHour() < FEED_HOUR2_2_11) &&  cl_22 == 1)
          || ((clock.getHour() > FEED_HOUR2_2_2) && (clock.getHour() < FEED_HOUR2_2_21))
          || ((clock.getHour() > FEED_HOUR2_2_3) && (clock.getHour() < FEED_HOUR2_2_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        cl_22 = 0;
        flag == false;
        // Открываем заслонку
        Serial.print(x);
        Serial.println("KORM 2");
        servo2.write(0);
        // Время открытия заслонки
        delay(I_OPEN2_2);
        servo2.write(90);
      } else
      {
        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo2.write(90);
      }
    }
    //
    //
  }


  if (buff == 3)
  {
    Serial.println("стоим после IF  buff=3  buff=");
    Serial.print(buff);
    Serial.println("FEED_HOUR3_1_11=");
    Serial.print(FEED_HOUR1_1_11);

    //
    //
    Serial.println("перед  if x=1   x=");
    Serial.print(x);

    if (x == 1)
      //  Serial.print(val);
    {
      clock.read();
      //    Serial.print(val);
      Serial.print(x);
      // servo1.write(0);
      // delay(I_OPEN1);
      // servo1.write(90);
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR1_1_1) && (clock.getHour() < FEED_HOUR1_1_11)  &&  cl_13 == 1)
          || ((clock.getHour() > FEED_HOUR1_1_2) && (clock.getHour() < FEED_HOUR1_1_21))
          || ((clock.getHour() > FEED_HOUR1_1_3) && (clock.getHour() < FEED_HOUR1_1_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        cl_13 = 0;
        flag == false;
        // Открываем заслонку
        //        Serial.print(val);
        Serial.print(x);
        Serial.println("KORM 1");
        servo1.write(180);
        // Время открытия заслонки
        delay(I_OPEN3_1);

        servo1.write(90);
      } else
      {
        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo1.write(90);
      }
    }
    //
    //
    Serial.print(x);
    Serial.println("PERED IF HA CERV 2");

    if (x == 2)
    {
      Serial.print(x);
      Serial.println("Posle IF HA CERV 2");
      clock.read();
      //Проверяем не пришло ли время покормить животное
      if (((clock.getHour() > FEED_HOUR1_2_1) && (clock.getHour() < FEED_HOUR1_2_11) &&  cl_23 == 1)
          || ((clock.getHour() > FEED_HOUR1_2_2) && (clock.getHour() < FEED_HOUR1_2_21))
          || ((clock.getHour() > FEED_HOUR1_2_3) && (clock.getHour() < FEED_HOUR1_2_31)))
      {
        // Если время пришло устанавливаем флаг "Уже покормили"
        cl_23 = 0;
        flag == false;
        // Открываем заслонку
        Serial.print(x);
        Serial.println("KORM 2");
        servo2.write(0);
        // Время открытия заслонки
        delay(I_OPEN3_2);
        servo2.write(90);
      } else
      {
        flag == true;
        long timeMs = millis();
        while (millis() - timeMs < 10) {}
        servo2.write(90);
      }
    }
    //
    //
  }
  if (buff == 4)
  {

    cl_1 = 1;
    cl_2 = 1;
    cl_12 = 1;
    cl_22 = 1;
    cl_13 = 1;
    cl_23 = 1;

  }
  // }
}
