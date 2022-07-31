void ble_to_oralb(uint8_t cManufacturerData[100]) {
  oralb_state = cManufacturerData[5];
  //oralb_pressure = round((cManufacturerData[6] - 50) / 192 * 100);
  oralb_pressure = round(cManufacturerData[6] );
  oralb_time_min = cManufacturerData[7];
  oralb_time_sec = cManufacturerData[8];
  oralb_time = cManufacturerData[7] * 60 + cManufacturerData[8];
  oralb_mode = cManufacturerData[9];
  oralb_quadrant = cManufacturerData[10] & 0b00000111;
  oralb_smiley = ( cManufacturerData[10] & 0b00111000 ) >> 3;
  oralb_quadrant_percentage = cManufacturerData[11];

  Serial.printf("Quadrant: %d Sekunden: %d Prozent: %d Smiley %d\n", oralb_quadrant, oralb_time, oralb_quadrant_percentage, oralb_smiley);
//  for (int i = 7; i >= 0; i--) {
//    Serial.print(bitRead(cManufacturerData[10], i));
//    Serial.print(" ");
//  }
//  Serial.println(" ");
  Serial.printf("Mode: %d Druck: %d Status: %d\n", oralb_mode, oralb_pressure, oralb_state);


}
