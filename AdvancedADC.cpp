#include "AdvancedADC.h"

uint8_t* ADCClass::buffer8_;
uint16_t* ADCClass::buffer16_;
volatile uint16_t ADCClass::current_index_;
uint16_t ADCClass::buffer_len_ = 0;
bool ADCClass::auto_trigger_on_;
uint8_t* ADCClass::channels_;
uint8_t ADCClass::n_channels_ = 0;
uint8_t ADCClass::channel_index_ = 0;
void (*ADCClass::update)();

void ADCClass::setPrescaler(uint8_t prescaler) {
  // ADCSRA: ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
  ADCSRA &= ~0x07;  // clear the ADPS2:0 bits
  ADCSRA |= prescaler; // set the ADPS2:0 bits
}

// option to left align the ADC values so we can read highest 8 bits from ADCH register only
void ADCClass::setLeftAlignResult(bool on) {
  // ADMUX: REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
  if (on) {
    ADMUX |= (1 << ADLAR); // turn on left alignment
  } else {
    ADMUX &= ~(1 << ADLAR); // turn off left alignment
  }
}

void ADCClass::setTriggerSource(uint8_t trigger_source) {
  // ADCSRB:  -  ACME  -   -  MUX5 ADTS2 ADTS1 ADTS0
  ADCSRB &= ~0x07; // clear the ADTS2:0 bits
  ADCSRB |= trigger_source; // set the ADTS2:0 bits
}

void ADCClass::setAutoTrigger(bool on) {
  auto_trigger_on_ = on;
  // ADCSRA: ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
  if (on) {
    ADCSRA |= (1 << ADATE); // enable auto trigger mode
  } else {
    ADCSRA &= ~(1 << ADATE); // clear auto trigger
  }
}

void ADCClass::next() {
  ADCSRA |= (1 << ADSC); // start next conversion
}

void ADCClass::begin() {
  current_index_ = 0;

  // re/enable auto trigger; it gets cleared on stop()
  setAutoTrigger(auto_trigger_on_);

  // enable ADC, enable interrupts when measurement completes,
  // and start first conversion.
  //
  // ADCSRA: ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
  //
  // ADATE bit enabbles auto trigger
  // ADIE bit enable interrupts when measurement complete
  // ADEN bit enables the ADC
  // ADSC bit starts a conversion
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE);
}

void ADCClass::stop() {
  // disable auto trigger (ADATE) and disable interrupts when
  // measurement completes (ADIE)
  //
  // ADCSRA: ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
  ADCSRA &= ~( (1 << ADATE) | (1 << ADIE) );
}

// publicly available method
// This clears any existing channel array
void ADCClass::setChannel(uint8_t channel) {
  // clear the channel array
  n_channels_ = 0;
  channels_ = 0;
  channel_index_ = 0;
  update = &updateSingleChannel;
  // set the ADC registers for this channel
  _setChannel(channel);
}

// private method for setting up ADC registers to read a channel
void ADCClass::_setChannel(uint8_t channel) {
  // set ADMUX register
  // ADMUX: REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
  ADMUX &= 0xF0; // clear MUX4:0
  ADMUX |= (channel & 0x07); // set MUX2:0

  // update MUX5 bit on ADCSRB register
  // ADCSRB:  -  ACME  -   -  MUX5 ADTS2 ADTS1 ADTS0
  if (channel > 7) {
    ADCSRB |= (1 << MUX5);
  } else {
    ADCSRB &= ~(1 << MUX5);
  }
}

void ADCClass::enableDigitalInputs(bool enabled) {
  //---------------------------------------------------------------------
  // DIDR0 and DIDR2 settings
  //---------------------------------------------------------------------
  // When this bit is written logic one, the digital input buffer on the
  // corresponding ADC pin is disabled. The corresponding PIN Register
  // bit will always read as zero when this bit is set. When an analog
  // signal is applied to the AD7:0 pin (DIDR0) or AD15:8 pin (DIDR2)
  // and the digital input from this pin is not needed, this bit should
  // be written logic one to reduce power consumption in the digital
  // input buffer.
  if (enabled) {
    DIDR0 = 0;
    DIDR2 = 0;
  } else {
    DIDR0 = 0xFF;
    DIDR2 = 0xFF;
  }
}

// update buffer with new reading and increment to next channel
void ADCClass::updateMultiChannel() {
  // increment the channel index
  if (++channel_index_ == n_channels_) {
    channel_index_ = 0; // wrap around to zero
  }
  // set registers for next read
  _setChannel(channels_[channel_index_]);
  updateSingleChannel();
}

// update buffer with new reading (single channel)
void ADCClass::updateSingleChannel() {
  uint16_t value = ADC_RESULT;
  
  // check that we're not writing past the end of the buffer (possible if
  // main loop doesn't check finished() fast enough)
  if (current_index_ < buffer_len_) {
    next(); // start next conversion
    if (ADMUX & (1 << ADLAR)) {
      buffer8_[current_index_++] = value >> 8;
    } else {
      buffer16_[current_index_++] = value;
    }    
  }
}

// interrupt service routine triggered when an ADC conversion completes
ISR(ADC_vect) {
  (*AdvancedADC.update)();
}

// Preinstantiate object
ADCClass AdvancedADC = ADCClass();
