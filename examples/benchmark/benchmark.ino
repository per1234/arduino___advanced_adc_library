#include "AdvancedADC.h"
const uint16_t n_samples = 255;
uint8_t buffer8[n_samples];
uint16_t buffer16[n_samples];
uint8_t channels[] = {0, 1};

void setup() {
  Serial.begin(115200);
  Serial.println("A0=" + String(analogRead(0)));
  Serial.println("A1=" + String(analogRead(1)));
  Serial.println();

  unsigned long t_start, t_end;

  AdvancedADC.enableDigitalInputs(false);
  AdvancedADC.setPrescaler(ADC_PRESCALER_8);

  Serial.println("prescaler=8\n");

  Serial.print("single channel, 8-bit, free running mode: ");
  AdvancedADC.setAutoTrigger(true);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 16-bit, free running mode: ");
  AdvancedADC.setAutoTrigger(true);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 8-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 16-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("dual channel, 8-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannels(channels);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();
  
  Serial.print("dual channel, 16-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannels(channels);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  AdvancedADC.setPrescaler(ADC_PRESCALER_16);

  Serial.println("prescaler=16\n");

  Serial.print("single channel, 8-bit, free running mode: ");
  AdvancedADC.setAutoTrigger(true);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 16-bit, free running mode: ");
  AdvancedADC.setAutoTrigger(true);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 8-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("single channel, 16-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannel(0);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();

  Serial.print("dual channel, 8-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer8);
  AdvancedADC.setChannels(channels);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer8[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();
  
  Serial.print("dual channel, 16-bit, normal mode: ");
  AdvancedADC.setAutoTrigger(false);
  AdvancedADC.setBuffer(buffer16);
  AdvancedADC.setChannels(channels);
  t_start = micros();
  AdvancedADC.begin();
  while(!AdvancedADC.finished());
  t_end = micros();
  Serial.print(1e3*n_samples/(float)(t_end-t_start));
  Serial.println(" kHz");
  for (uint8_t i = 0; i < 10; i++) {
    Serial.print(String(buffer16[i]) + ", ");
  }
  Serial.println("...");
  Serial.println();
}

void loop() {
}
