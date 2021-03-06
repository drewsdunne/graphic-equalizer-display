#ifndef GPIO_H
#define GPIO_H

#include <fsl_device_registers.h>

typedef uint8_t pin_count_t;
typedef uint16_t pin_id_t;

// Configures a pin as a digital out
#define DIGITAL_OUT(LETTER, PIN) DIGITAL_OUT_IMPL(LETTER, PIN)
#define DIGITAL_OUT_IMPL(LETTER, PIN)                                          \
  SIM->SCGC5 |= SIM_SCGC5_PORT##LETTER##_MASK;                                 \
  PORT##LETTER->PCR[PIN] = PORT_PCR_MUX(0x01);                                 \
  PT##LETTER->PDDR |= (1 << PIN);

// Writes to a pin
#define DIGITAL_WRITE_HIGH(LETTER, PIN) DIGITAL_WRITE_HIGH_IMPL(LETTER, PIN)
#define DIGITAL_WRITE_LOW(LETTER, PIN) DIGITAL_WRITE_LOW_IMPL(LETTER, PIN)
#define DIGITAL_WRITE_HIGH_IMPL(LETTER, PIN) PT##LETTER->PTOR |= (1 << PIN)
#define DIGITAL_WRITE_LOW_IMPL(LETTER, PIN) PT##LETTER->PCOR |= (1 << PIN)
#define DIGITAL_WRITE(LETTER, PIN, STATE)                                      \
  ((STATE) ? (DIGITAL_WRITE_HIGH(LETTER, PIN))                                 \
           : (DIGITAL_WRITE_LOW(LETTER, PIN)));

#endif
