#include "time.h"

DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
char* timeZone = "EET-2EEST,M3.5.0/3,M10.5.0/4";

void setupDateTime() {
  DateTime.setServer("ua.pool.ntp.org");
  bool tzOk = DateTime.setTimeZone(timeZone);
  if (tzOk) {
    Serial.println(String("Timezone is correct: ") + DateTime.getTimeZone());
  } else {
    Serial.println(String("Timezone is NOT correct: ") + timeZone);
  }
  DateTime.begin();
  if (!DateTime.isTimeValid()) {
    Serial.println("Failed to get time from server.");
  } else {
    Serial.printf("Date Now is %s\n", DateTime.toISOString().c_str());
    Serial.printf("Timestamp is %ld\n", DateTime.now());
  }
}
