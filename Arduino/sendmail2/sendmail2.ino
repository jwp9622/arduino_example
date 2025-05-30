#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

const char *WIFI_SSID = "AI_academy_302";
const char *WIFI_PASSWORD = "0532161010";

//#define SMTP_HOST "smtp.gmail.com"
#define SMTP_HOST "smtp.naver.com"

#define SMTP_PORT esp_mail_smtp_port_587

//#define AUTHOR_EMAIL "jwp9622@gmail.com" //구글 이메일주소
//#define AUTHOR_PASSWORD "xovo iknt lyqh mqcb" //구글 앱 비밀번호 16자리
#define AUTHOR_EMAIL "jwp9622@naver.com" //네이버 이메일주소
#define AUTHOR_PASSWORD "!5086qkrwjddnjs" //네이버 비밀번호 16자리


SMTPSession smtp;

String strSender = "jwp9622"; //보내는사람 (영어만)
String strRecipientName = "Park Dahee"; //받는사람 (영어만)
//String strRecipientMail = "jwp9622@naver.com"; //받는사람 이메일
//String strSubject = "WemosR1D1 mail Test(google->naver)"; //메일제목 (영어만)
String strRecipientMail = "jwp9622@gmail.com"; //받는사람 이메일
String strSubject = "WemosR1D1 mail Test(naver->google)"; //메일제목 (영어만)
String strMsg = "ESP8266에서 움직임이 감지되었습니다."; //메일내용



#define TRIG_PIN D7
#define ECHO_PIN D6

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

void loop()
{
  //static float distanceCM;
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration=pulseIn(ECHO_PIN, HIGH);

  float distanceCM = ((3400.0*(float)duration)/1000000.0)/2.0;
  Serial.println(distanceCM);
  if(distanceCM > 10 && distanceCM < 30){
    Serial.print("움직임 감지!! ");
    Serial.println("메일 보냈습니다.");
    sendEmail(distanceCM);
    delay(20000);
  }
}


void sendEmail(float timeStr)
{
  smtp.debug(1);
  smtp.callback(smtpCallback);
  ESP_Mail_Session session;
  
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = F("mydomain.net");

  session.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  session.time.gmt_offset = 3;
  session.time.day_light_offset = 0;

  SMTP_Message message;

  message.sender.name = strSender;
  message.sender.email = AUTHOR_EMAIL;
  message.subject = strSubject+" "+timeStr;
  message.addRecipient(strRecipientName, strRecipientMail);

  String textMsg = strMsg+" "+timeStr;
  message.text.content = textMsg ;
  
  message.text.charSet = F("utf-8");
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.addHeader(F("Message-ID: <abcde.fghij@gmail.com>"));

  if (!smtp.connect(&session))
    return;

  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

  ESP_MAIL_PRINTF("Free Heap: %d\n", MailClient.getFreeHeap());
}


void smtpCallback(SMTP_Status status)
{
  Serial.println(status.info());
  
  if (status.success())
  {
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");
    
    smtp.sendingResult.clear();
  }
}
