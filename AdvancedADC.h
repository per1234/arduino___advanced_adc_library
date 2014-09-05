#ifndef ADVANCED_ADC_H
#define ADVANCED_ADC_H

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

// Macros for reading the ADC result register(s)
#define ADC_RESULT (ADCL | (ADCH<<8))
#define ADC_8BIT_RESULT ADCH

// Prescaler source definitions
#define ADC_PRESCALER_2 0
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7

// Auto trigger source definitions
#define ADC_ATS_FREE_RUNNING_MODE 0
#define ADC_ATS_ANALOG_COMPARATOR 1
#define ADC_ATS_EXTERNAL_INTERRUPT_REQUEST 2
#define ADC_ATS_TIMER0_CMA 3
#define ADC_ATS_TIMER0_OVERFLOW 4
#define ADC_ATS_TIMER1_CMB 5
#define ADC_ATS_TIMER1_OVERFLOW 6
#define ADC_ATS_TIMER1_CAPTURE_EVENT 7

class ADCClass {
public:
  static bool finished() __attribute__((always_inline)) {
    if (current_index_ == buffer_len_) {
      stop();
      return true;
    }
    return false;
  }
  static void (*update)();
  static void setAnalogReference(uint8_t ref);
  static void setChannel(uint8_t channel) __attribute__((always_inline));
  static void setPrescaler(uint8_t prescaler) __attribute__((always_inline));
  static void setSamplingRate(float sampling_rate);
  static float samplingRate() { return sampling_rate_; }
  static uint16_t prescaler();
  static void setLeftAlignResult(bool on) __attribute__((always_inline));
  static void setAutoTrigger(bool on) __attribute__((always_inline));
  static void setTriggerSource(uint8_t trigger_source) __attribute__((always_inline));
  static uint8_t triggerSource() __attribute__((always_inline));
  static void registerCallback(void (*callback)(uint8_t, uint16_t)) {
    update = &updateCallback;
    callback_ = callback;
  }

  static void setBuffer(uint8_t* buffer, uint16_t len) {
    buffer_len_ = len;
    buffer8_ = buffer;
    setLeftAlignResult(true);
  }

  static void setBuffer(uint16_t* buffer, uint16_t len) {
    buffer_len_ = len;
    buffer16_ = buffer;
    setLeftAlignResult(false);
  }

  template<typename T, size_t N>
  static void setBuffer(T (&buffer)[N]) {
    if (sizeof(T)==1) {
      setBuffer((uint8_t*)buffer, N);
    } else {
      setBuffer((uint16_t*)buffer, N);
    }
  }

  static void setChannels(uint8_t* channels, uint8_t N) {
    if (N == 1) {
      setChannel(channels[0]);
    } else {
      channels_ = channels;
      n_channels_ = N;
      channel_index_ = 0;
      update = &updateMultiChannel;
      _setChannel(channels_[channel_index_]); // set_current_channel
    }
  }

  template<typename uint8_t, size_t N>
  static void setChannels(uint8_t (&channels)[N]) {
    setChannels(channels, N);
  }
  
  static void begin() __attribute__((always_inline));
  static void stop() __attribute__((always_inline));
  static void next() __attribute__((always_inline));
  static void updateSingleChannel() __attribute__((always_inline));
  static void updateMultiChannel() __attribute__((always_inline));
  static void updateCallback() __attribute__((always_inline));
  static void enableDigitalInputs(bool enabled);
  static uint16_t currentIndex() { return current_index_; }
  static float readVcc();
  ADCClass();

private:
  static void _setChannel(uint8_t channel) __attribute__((always_inline));
  static void _startTimer() __attribute__((always_inline));
  static void _stopTimer() __attribute__((always_inline));

  static bool auto_trigger_on_;
  static uint8_t* channels_;
  static uint8_t channel_index_;
  static uint8_t n_channels_;
  static uint8_t channel_;
  static uint8_t* buffer8_;
  static uint16_t* buffer16_;
  static uint16_t buffer_len_;
  volatile static uint16_t current_index_;
  static void (*callback_)(uint8_t, uint16_t);
  static unsigned long t_start_;
  static float sampling_rate_;
  static uint8_t clock_select_bits_;
};

extern ADCClass AdvancedADC;

#endif // ADVANCED_ADC_H
