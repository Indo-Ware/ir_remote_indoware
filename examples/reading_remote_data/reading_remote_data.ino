#include <idwr_ir.h>
#include <IRLibAll.h>

IRrecvPCI receiver(3);
IRdecode remot;

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();
}

void loop() {
  char data_baca;
  if (receiver.getResults()) {
    remot.decode();
    data_baca=baca_data_remot();
    Serial.println(data_baca,DEC);
    receiver.enableIRIn();
  }
}


