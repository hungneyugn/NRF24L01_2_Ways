
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN
const byte diachi[][6] = {"12345", "10000"};

void setup() 
{
  Serial.begin(9600);

  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }   
  radio.openWritingPipe(diachi[0]);
  //Chỉ có thể mở 1 đường ghi
  //Lệnh openWritingPipe có số đường truyền mặc định là 0
  //Mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  //kênh này chỉ ghi data trên địa chỉ 12345   
  radio.openReadingPipe(1, diachi[1]);
  //Có thể mở 6 đường đọc cùng lúc
  //Nhưng đường 0 mặc định dùng cho ghi  
  //Lệnh openReadingPipe có số đường truyền từ 1-5
  //Đọc data của địa chỉ 10000 trên đường truyền 1  
  
  radio.setPALevel(RF24_PA_MIN); //Cài bộ khuyết địa công suất ở mức MIN
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);    
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
}

void loop() 
{  
  const char text[] = "handsome"; //Mảng chứa chuỗi kí tự
  radio.stopListening(); //Ngưng nhận
  radio.write(&text, sizeof(text));
  Serial.print("Truyen: ");
  Serial.print(text);
  Serial.print(".   ");
  delay(10); 
  radio.startListening(); //Bắt đầu nhận
  while(!radio.available());
  char nhan[30] = ""; //30 là số kí tự trong mảng
  radio.read(&nhan, sizeof(nhan));
  Serial.print("Nhan: ");
  Serial.println(nhan);
  delay(10); 
}
