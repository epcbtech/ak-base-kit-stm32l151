#include <stm32l1xx_rcc.h>
#include <stm32l1xx_gpio.h>
#include <misc.h>
#include <buzzer.h>

GPIO_InitTypeDef PORT;
volatile       uint32_t          _beep_duration;
volatile       bool              _tones_playing;
volatile const Tone_TypeDef     *_tones;

void buzzer_irq( void ) {
	if (BUZZER_TIM->SR & TIM_SR_UIF) {
		BUZZER_TIM->SR &= ~TIM_SR_UIF; // Clear the TIMx's interrupt pending bit

		_beep_duration--;
		if (_beep_duration == 0) {
			if (_tones_playing) {
				// Currently playing tones, take next tone
				_tones++;
				if (_tones->frequency == 0 && _tones->duration == 0) {
					// Last tone in sequence
					BUZZER_Disable();
					_tones_playing = false;
					_tones = NULL;
				} else {
					if (_tones->frequency == 0) {
						// Silence period
						BUZZER_TIM->ARR = SystemCoreClock / (100 * BUZZER_TIM->PSC) - 1;
						BUZZER_TIM->CCR3 = 0; // 0% duty cycle
						_beep_duration = _tones->duration + 1;
					} else {
						// Play next tone in sequence
						BUZZER_Enable(_tones->frequency,_tones->duration);
					}
				}
			} else {
				BUZZER_Disable();
			}
		}
	}
}

// Initialize buzzer output
void BUZZER_Init(void) {
	buzzer_io_init();
}

// Turn on buzzer with specified frequency
// input:
//   freq - PWM frequency for buzzer (Hz)
//   duration - duration of buzzer work (tens ms: 1 -> 10ms sound duration)
void BUZZER_Enable(uint16_t freq, uint32_t duration) {
	if (freq < 100 || freq > 8000 || duration == 0) {
		BUZZER_Disable();
	} else {
		_beep_duration = (freq / 100) * duration + 1;

		// Configure and enable PWM timer
		RCC->APB1ENR |= BUZZER_TIM_PERIPH; // Enable TIMx peripheral
		BUZZER_TIM->ARR = SystemCoreClock / (freq * BUZZER_TIM->PSC) - 1;
		BUZZER_TIM->CCR3 = BUZZER_TIM->ARR >> 1; // 50% duty cycle
		BUZZER_TIM->CR1 |= TIM_CR1_CEN; // Counter enable
	}
}

// Turn off buzzer
void BUZZER_Disable(void) {
	// Counter disable
	BUZZER_TIM->CR1 &= ~TIM_CR1_CEN;
	// Disable TIMx peripheral to conserve power
	RCC->APB1ENR &= ~BUZZER_TIM_PERIPH;
	// Configure buzzer pin as analog input without pullup to conserve power
	GPIO_ResetBits(BUZZER_IO_PORT, BUZZER_IO_PIN);
}

// Start playing tones sequence
// input:
//   tones - pointer to tones array
void BUZZER_PlayTones(const Tone_TypeDef * tones) {
	_tones = tones;
	_tones_playing = true;
	BUZZER_Enable(_tones->frequency,_tones->duration);
}
