
void setup()
{
  Serial.begin(115200);
  init_tft( ) ;
  init_ble();

}

void loop()
{
  // put your main code here, to run repeatedly:


  display_data();
  delay(200);
}
