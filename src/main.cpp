
#include "ApplicationComposer.h"

ApplicationComposer * app = ApplicationComposer::getInstance();

void setup() {
  ESP_ERROR_CHECK(app->init());
}

void loop() {
  app->loop();
}

