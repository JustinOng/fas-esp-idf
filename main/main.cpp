#include <stdio.h>

#include "FastAccelStepper.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

constexpr int PIN_STEPPER0_EN = 27;
constexpr int PIN_STEPPER0_DIR = 23;
constexpr int PIN_STEPPER0_STEP = 18;

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

static const char *TAG = "main";

extern "C" {
void app_main(void) {
  engine.init();
  ESP_LOGI(TAG, "engine.init");
  stepper = engine.stepperConnectToPin(PIN_STEPPER0_STEP);
  ESP_LOGI(TAG, "engine.stepperConnectToPin");

  assert(stepper);

  stepper->setDirectionPin(PIN_STEPPER0_DIR);
  stepper->setEnablePin(PIN_STEPPER0_EN);
  stepper->setAutoEnable(true);
  ESP_LOGI(TAG, "pins");

  stepper->setSpeedInUs(1000);  // the parameter is us/step !!!
  stepper->setAcceleration(100);
  stepper->runForward();

  ESP_LOGI(TAG, "done");

  while (1) {
    vTaskDelay(1000);
  }
}
}
