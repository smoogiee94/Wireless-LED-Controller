#include <ESP8266WiFi.h>
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1
const char* ssid = "MarquezGuest";
const char* password = "Ilovelila94";


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  setupPins();
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  //-------------------------------------------
  // LEDs On and Off Logic Begin
  //-------------------------------------------
  if (request.indexOf("LED=ON") != -1)  {
    digitalWrite(D0, HIGH);
  }
  if (request.indexOf("LED=OFF") != -1)  {
    digitalWrite(D0, LOW);
  }
  //--------------------------------------------
  // LEDs On and Off Logic End
  //--------------------------------------------




  //--------------------------------------------
  // Basic RGBW Logic Begin
  //--------------------------------------------
  if (request.indexOf("LED=RED") != -1)  {
    resetPins();
    digitalWrite(D7, HIGH);
  }
  if (request.indexOf("LED=GREEN") != -1)  {
    resetPins();
    digitalWrite(D8, HIGH);
  }
  if (request.indexOf("LED=BLUE") != -1)  {
    resetPins();
    digitalWrite(D9, HIGH);
  }
  if (request.indexOf("LED=WHITE") != -1)  {
    resetPins();
    digitalWrite(D10, HIGH);
  }
  //--------------------------------------------
  // Basic RGBW Logic End
  //--------------------------------------------

  //--------------------------------------------
  // Flash logic begin
  //--------------------------------------------
  if (request.indexOf("LED=FLASH") != -1){
    resetPins();
    digitalWrite(D4, HIGH);
  }
  //--------------------------------------------
  // Flash logic end
  //--------------------------------------------

  //--------------------------------------------
  // Fade Logic Begin
  //--------------------------------------------
  if (request.indexOf("LED=FADE") != -1){
    resetPins();
    digitalWrite(D3, HIGH);
  }
  //--------------------------------------------
  // Fade Logic End
  //--------------------------------------------

  //--------------------------------------------
  // Increase / Decrease Brightness Logic Begin
  //--------------------------------------------
  if (request.indexOf("LED=INCRBRIGHT") != -1){
    digitalWrite(D1, HIGH);
    delay(10);
    digitalWrite(D1, LOW);
  }

  if (request.indexOf("LED=DECRBRIGHT") != -1){
    digitalWrite(D2, HIGH);
    delay(10);
    digitalWrite(D2, LOW);
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  //Beginning of website declarations
  client.println("<!DOCTYPE html><html lang=\"en\"> <head> <meta charset=\"utf-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags --> <meta name=\"description\" content=\"\"> <meta name=\"author\" content=\"\"> <title>Smoogiee's LED Dashboard</title><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\">");
  client.println("<style type=\"text/css\">a,a:focus,a:hover {color: #fff;}.btn-default,.btn-default:hover,.btn-default:focus {color: #333;text-shadow: none; /* Prevent inheritance from `body` */background-color: #fff;border: 1px solid #fff;}html,body {height: 100%;background-color: #333;}body {color: #fff; background: url(http://i.imgur.com/djLF3Dj.jpg); background-size: 100% 100%; background-repeat: no-repeat; text-align: center;text-shadow: 0 1px 3px rgba(0,0,0,.5);}.site-wrapper {display: table;width: 100%;height: 100%; /* For at least Firefox */min-height: 100%;-webkit-box-shadow: inset 0 0 100px rgba(0,0,0,.5);box-shadow: inset 0 0 100px rgba(0,0,0,.5);}.site-wrapper-inner {display: table-cell;vertical-align: top;}.cover-container {margin-right: auto;margin-left: auto;}.inner {padding: 30px;}.masthead-brand {margin-top: 10px;margin-bottom: 10px;}.masthead-nav > li {display: inline-block;}.masthead-nav > li + li {margin-left: 20px;}.masthead-nav > li > a {padding-right: 0;padding-left: 0;font-size: 16px;font-weight: bold;color: #fff; /* IE8 proofing */color: rgba(255,255,255,.75);border-bottom: 2px solid transparent;}");
  client.println(".masthead-nav > li > a:hover,.masthead-nav > li > a:focus {background-color: transparent;border-bottom-color: #a9a9a9;border-bottom-color: rgba(255,255,255,.25);}.masthead-nav > .active > a,.masthead-nav > .active > a:hover,.masthead-nav > .active > a:focus {color: #fff;border-bottom-color: #fff;}@media (min-width: 768px) {.masthead-brand {float: left;}.masthead-nav {float: right;}}.cover {padding: 0 20px;}.cover .btn-lg {padding: 10px 20px;font-weight: bold;}.mastfoot {color: #999; /* IE8 proofing */color: rgba(255,255,255,.5);}@media (min-width: 768px) {.masthead {position: fixed;top: 0;}.mastfoot {position: fixed;bottom: 0;}.site-wrapper-inner {vertical-align: middle;}/* Handle the widths */.masthead,.mastfoot,.cover-container {width: 100%; /* Must be percentage or pixels for horizontal alignment */}}@media (min-width: 992px) {.masthead,.mastfoot,.cover-container {width: 700px;}}</style></head>");
  //End of website declarations
  //Beginning of website body
  client.println("<body> <div class=\"site-wrapper\"> <div class=\"site-wrapper-inner\"> <div class=\"cover-container\"> <div class=\"masthead clearfix\"> <div class=\"inner\"> <h3 class=\"masthead-brand\">LED Controller Dashboard</h3> <nav> <ul class=\"nav masthead-nav\"> <li class=\"active\"><a href=\"#\">Home</a></li> <li><a href=\"#\">Features</a></li> <li><a href=\"#\">Contact</a></li> </ul> </nav> </div> </div> <div class=\"inner cover\"> <h1 class=\"cover-heading\">LED Dashboard.</h1> <p class=\"lead\">Proof of concept for NodeMCU Amica Bootstrapped controller.</p> <p class=\"lead\"> <a href=\"/LED=RED\" class=\"btn btn-lg btn-default\">&nbsp;Red&nbsp;</a> <a href=\"/LED=GREEN\" class=\"btn btn-lg btn-default\">Green</a> <a href=\"/LED=BLUE\" class=\"btn btn-lg btn-default\">Blue</a> <a href=\"/LED=WHITE\" class=\"btn btn-lg btn-default\">White</a> <a href=\"/LED=FLASH\" class=\"btn btn-lg btn-default\">Flash</a> <a href=\"/LED=FADE\" class=\"btn btn-lg btn-default\">Fade</a></p>");
  client.println("<p class=\"lead\"> &nbsp;<a href=\"/LED=INCRBRIGHT\" class=\"btn btn-lg btn-default\">Increase Brightness</a> <a href=\"/LED=DECRBRIGHT\" class=\"btn btn-lg btn-default\">Decrease Brightness</a> </p> <p class=\"lead\"> <a href=\"/LED=ON\" class=\"btn btn-lg btn-default\">Turn On</a> <a href=\"/LED=OFF\" class=\"btn btn-lg btn-default\">Turn Off</a> </p> </div> <div class=\"mastfoot\"> <div class=\"inner\"> <p>Cover template by <a href=\"https://twitter.com/mdo\">@mdo</a>. Ported to NodeMCU Amica by <a href=\"https://github.com/smoogiee94\">Smoogiee</a>.</p> </div> </div> </div> </div> </div></html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}

void setupPins(){
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  pinMode(D8, OUTPUT);
  digitalWrite(D8, LOW);
  pinMode(D9, OUTPUT);
  digitalWrite(D9, LOW);
  pinMode(D10, OUTPUT);
  digitalWrite(D10, LOW);
  return;
}

void resetPins(){
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
}

