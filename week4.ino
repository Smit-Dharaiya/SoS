void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial3.println("AT+RST");
  Serial3.println("AT+CWMODE=1");
  Serial3.println("AT+CWJAP=\"Hi\",\"ahol6956\"");
  delay(5000);
  Serial.print("ready");
  httppost();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}




void httppost () {

  String data = "var=111";  //data to be sent
  Serial3.println("AT+CIPSTART=\"TCP\",\"vishalahuja.tk\",80");//start a TCP connection.

  if( Serial3.find("OK")) {

    Serial.println("TCP connection ready");

  }
  delay(1000);

  String postRequest = "POST /SoS/ HTTP/1.0\r\n";

  postRequest = postRequest +"Host: vishalahuja.tk \r\n";

  postRequest = postRequest +"Accept: */*\r\n";

  postRequest = postRequest +"Content-Length: " + data.length() + "\r\n";

  postRequest = postRequest +"Content-Type: application/x-www-form-urlencoded\r\n";

  postRequest = postRequest +"\r\n" +data;

  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

  Serial3.print(sendCmd);

  Serial3.println(postRequest.length() );

  delay(500);

  if(Serial3.find(">")) {
    Serial.println("Sending..");
    Serial3.print(postRequest);
    
    if( Serial3.find("SEND OK")) {
      Serial.println("Packet sent");
      
      while (Serial3.available()) {
        String tmpResp = Serial3.readString();
        Serial.println(tmpResp);
      }
        // close the connection
      Serial3.println("AT+CIPCLOSE");
    }
  }
}
