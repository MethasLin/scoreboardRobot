#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <Arduino_JSON.h>

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";
typedef struct struct_message {
  int id;
  float temp;
  float hum;
  unsigned int readingId;
} struct_message;

JSONVar board;
struct_message incomingReadings;
AsyncWebServer server(80);
AsyncEventSource events("/events");
const int ledPin = 2; // Built-in LED pin
const int buttonPin = 4; // GPIO 4 used as the button input
bool ledState = false; // LED state (OFF by default)

// Variables to implement hold button functionality
bool buttonState = false;
bool ledHoldState = false;
unsigned long buttonPressStartTime = 0;
const unsigned long HOLD_DURATION_MS = 1000;
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  // ... (existing callback code)
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <link href='https://fonts.googleapis.com/css?family=Zen Tokyo Zoo' rel='stylesheet'>
<title>TouchUIIYEDMAE</title>
<style>
    body{
        background-color: #ADFCE9;    
    }
    #btnupL{
        cursor: pointer;
        position: absolute;
        top : 300px;
        left: 50px;
    }
    #btnupL path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    #btnupL:active g {
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    #btnupL:active path {
      fill: rgb(45, 108, 67);
    }
    #btndownL{
        cursor: pointer;
        position: absolute;
        top: 500px;
        left:50px;
    }
    #btndownL path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    #btndownL:active g {
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    #btndownL:active path {
      fill: rgb(45, 108, 67);
    }
    #btnupR{
        cursor: pointer;
        position: absolute;
        top : 300px;
        right:50px;
    }#btnupR path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    #btnupR:active g {
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    #btnupR:active path {
      fill: rgb(45, 108, 67);
    }
    #btndownR{
        cursor: pointer;
        position: absolute;
        top : 500px;
        right:50px;
    }
    #btndownR path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    #btndownR:active g {
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    #btndownR:active path {
      fill: rgb(45, 108, 67);
    }
    .half-circleL{
      cursor: pointer;
      width : 252px;
      height: 420px;
      background-color: #6BE3B7;
      border: 5px solid #04916E;
      box-shadow: 0px 10px 5px 0px rgba(82, 173, 140, 0.80);
      border-top-left-radius: 420px;
      border-bottom-left-radius: 420px;
      position: absolute;
      top : 250px;
      left: 275px; 
    }
    .half-circleL path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    .half-circleL:active {
      box-shadow: none;
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    .half-circleL:active {
      background-color: rgb(45, 108, 67);
    }
    .half-circleL img {
      width : auto;
      height: auto;
      position: absolute;
      top : 75px;
      display: block;
    }
    .half-circleR{
      cursor: pointer;
      width : 252px;
      height: 420px;
      background-color: #6BE3B7;
      border: 5px solid #04916E;
      box-shadow: 0px 10px 5px 0px rgba(82, 173, 140, 0.80);
      border-top-right-radius: 420px;
      border-bottom-right-radius: 420px;
      position: absolute;
      top : 250px;
      right:275px; 
    }
    .half-circleR path{
      fill: #6BE3B7;
      transition: fill 0.05s;
    }
    .half-circleR:active {
      box-shadow: none;
      filter: none;
      filter: url(#filter1_i_3_4);
    }
    .half-circleR:active {
      background-color: rgb(45, 108, 67);
    }
    .half-circleR img {
      width : auto;
      height: auto;
      position: absolute;
      top : 75px;
      right:0px;
      display: block;
    }
    .bordermonitor {
      background-color: #04916E;
      box-shadow: 0px 20px 10px 10px rgba(82, 173, 140, 0.80);
      height: 650px;
      width: 850px;
      border-radius: 5%;
      position: absolute;
      top: 75px;
      left: 42px;
      display: none;
    }
    .monitor {
      background-color: #6BE3B7;
      box-shadow: 0px 20px 10px 10px rgba(82, 173, 140, 0.80) inset;
      height: 550px;
      width: 750px;
      border-radius: 5%;
      position: absolute;
      top: 75px;
      left: 42px;
      display: none;
    }
    .moniter p{
      width: 535px;
      height: 106px;
      flex-shrink: 0;
      color: #2209BA;
      font-family: 'Zen Tokyo Zoo';font-size: 22px;
      font-size: 100px;
      font-style: normal;
      font-weight: 400;
      line-height: normal;
      display: none;
    }
    @media screen and (max-width: 834px) {
      .bordermonitor{
        display: block;
        position: absolute;
        top: 150px;
        left:40px;
      }
      .monitor{
        display: block;
        position: absolute;
        top: 200px;
        left:90px;
      }  
    .monitor .p1{
      width: 535px;
      height: 106px;
      flex-shrink: 0;
      color: #2209BA;
      text-shadow:5px 5px 0 #fff,
      -5px -5px 0 #fff,
      5px -5px 0 #fff,
      -5px 5px 0 #fff;
      font-family: 'Zen Tokyo Zoo';font-size: 30px;
      font-size: 110px;
      font-style: normal;
      font-weight: bold;
      line-height: normal;
      margin-top: 125px;
      margin-left: 80px;
      display:inline-block;
    }
    .monitor .p2{
      width: 535px;
      height: 106px;
      flex-shrink: 0;
      color: #2209BA;
      text-shadow:5px 5px 0 #fff,
      -5px -5px 0 #fff,
      5px -5px 0 #fff,
      -5px 5px 0 #fff;
      font-family: 'Zen Tokyo Zoo';font-size: 30px;
      font-size: 150px;
      font-style: normal;
      font-weight: bold;
      line-height: normal;
      margin-top: -80px;
      margin-left: 80px;
      display:inline-block;
    }
    .monitor .p3{
      border-top: 14px solid #fff;
      margin-top: -265px;
      margin-left: 80px;
      margin-right: 58px;
      display: block;
    }
    .monitor .p4{
      border-top: 7px solid #2209BA;
      margin-top: -26px;
      margin-left: 80px;
      margin-right: 61px;
      display: block;
    }
      .half-circleL{
        width : 180px;
        height: 180px;
        box-shadow: 0px 10px 5px 0px rgba(82, 173, 140, 0.80);
        border-radius: 180px;
        top : 1100px;
        left: 10px; 
      }
      .half-circleL img {
      width : 250px;
      height: 175px;
      position: absolute;
      top : 0px;
      left: 0px;
      display: block;
    }
    .half-circleR{
        width : 180px;
        height: 180px;
        box-shadow: 0px 10px 5px 0px rgba(82, 173, 140, 0.80);
        border-radius: 180px;
        top : 1100px;
right:-100px;
        
      }
      .half-circleR img {
      width : 250px;
      height: 175px;
      position: absolute;
      top : 0px;
      right: -15px;
      display: block;
    }
    #btnupL{
        top : 954px;
        left: 250px;
    }
    #btndownL{
        top: 1154px;
        left: 250px;
    }
    #btnupR{
        top : 954px;
        right:150px;
    }
    #btndownR{
        top: 1154px;
        right:150px;
    }



    }
    
    

    </style>
    
</head>
<body>
  <svg id="btnupL" xmlns="http://www.w3.org/2000/svg" width="166" height="167" viewBox="0 0 166 167" fill="none">
    <g filter="url(#filter0_d_101_68)">
      <path d="M69.6548 9.00391C75.2324 -1.86441 90.7676 -1.86443 96.3452 9.00389L158.39 129.901C163.512 139.883 156.264 151.75 145.045 151.75H20.9555C9.73578 151.75 2.48752 139.883 7.61025 129.901L69.6548 9.00391Z" fill="#6BE3B7"/>
      <path d="M94.121 10.1454L156.166 131.043C160.434 139.361 154.394 149.25 145.045 149.25H20.9555C11.6057 149.25 5.56551 139.361 9.83445 131.043L71.879 10.1454C76.527 1.08843 89.473 1.08843 94.121 10.1454Z" stroke="#04916E" stroke-width="5"/>
    </g>
    <defs>
      <filter id="filter0_d_101_68" x="0.935547" y="0.852661" width="164.129" height="165.897" filterUnits="userSpaceOnUse" color-interpolation-filters="sRGB">
        <feFlood flood-opacity="0" result="BackgroundImageFix"/>
        <feColorMatrix in="SourceAlpha" type="matrix" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0" result="hardAlpha"/>
        <feOffset dy="10"/>
        <feGaussianBlur stdDeviation="2.5"/>
        <feComposite in2="hardAlpha" operator="out"/>
        <feColorMatrix type="matrix" values="0 0 0 0 0.320733 0 0 0 0 0.68 0 0 0 0 0.550664 0 0 0 0.8 0"/>
        <feBlend mode="normal" in2="BackgroundImageFix" result="effect1_dropShadow_101_68"/>
        <feBlend mode="normal" in="SourceGraphic" in2="effect1_dropShadow_101_68" result="shape"/>
      </filter>
    </defs>
  </svg>
  

  <svg id="btndownL" xmlns="http://www.w3.org/2000/svg" width="166" height="167" viewBox="0 0 166 167" fill="none">
    <g filter="url(#filter0_d_101_69)">
      <path d="M96.3452 142.996C90.7676 153.864 75.2324 153.864 69.6548 142.996L7.61026 22.0988C2.48753 12.1168 9.73577 0.25 20.9555 0.25L145.045 0.25C156.264 0.25 163.512 12.1168 158.39 22.0988L96.3452 142.996Z" fill="#6BE3B7"/>
      <path d="M71.879 141.855L9.83446 20.9573C5.56552 12.639 11.6057 2.75 20.9555 2.75L145.045 2.75C154.394 2.75 160.434 12.639 156.166 20.9573L94.121 141.855C89.473 150.912 76.527 150.912 71.879 141.855Z" stroke="#04916E" stroke-width="5"/>
    </g>
    <defs>
      <filter id="filter0_d_101_69" x="0.935562" y="0.25" width="164.129" height="165.897" filterUnits="userSpaceOnUse" color-interpolation-filters="sRGB">
        <feFlood flood-opacity="0" result="BackgroundImageFix"/>
        <feColorMatrix in="SourceAlpha" type="matrix" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0" result="hardAlpha"/>
        <feOffset dy="10"/>
        <feGaussianBlur stdDeviation="2.5"/>
        <feComposite in2="hardAlpha" operator="out"/>
        <feColorMatrix type="matrix" values="0 0 0 0 0.320733 0 0 0 0 0.68 0 0 0 0 0.550664 0 0 0 0.8 0"/>
        <feBlend mode="normal" in2="BackgroundImageFix" result="effect1_dropShadow_101_69"/>
        <feBlend mode="normal" in="SourceGraphic" in2="effect1_dropShadow_101_69" result="shape"/>
      </filter>
    </defs>
  </svg>
  
  
  <svg id="btnupR" xmlns="http://www.w3.org/2000/svg" width="166" height="167" viewBox="0 0 166 167" fill="none">
    <g filter="url(#filter0_d_101_68)">
      <path d="M69.6548 9.00391C75.2324 -1.86441 90.7676 -1.86443 96.3452 9.00389L158.39 129.901C163.512 139.883 156.264 151.75 145.045 151.75H20.9555C9.73578 151.75 2.48752 139.883 7.61025 129.901L69.6548 9.00391Z" fill="#6BE3B7"/>
      <path d="M94.121 10.1454L156.166 131.043C160.434 139.361 154.394 149.25 145.045 149.25H20.9555C11.6057 149.25 5.56551 139.361 9.83445 131.043L71.879 10.1454C76.527 1.08843 89.473 1.08843 94.121 10.1454Z" stroke="#04916E" stroke-width="5"/>
    </g>
    <defs>
      <filter id="filter0_d_101_68" x="0.935547" y="0.852661" width="164.129" height="165.897" filterUnits="userSpaceOnUse" color-interpolation-filters="sRGB">
        <feFlood flood-opacity="0" result="BackgroundImageFix"/>
        <feColorMatrix in="SourceAlpha" type="matrix" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0" result="hardAlpha"/>
        <feOffset dy="10"/>
        <feGaussianBlur stdDeviation="2.5"/>
        <feComposite in2="hardAlpha" operator="out"/>
        <feColorMatrix type="matrix" values="0 0 0 0 0.320733 0 0 0 0 0.68 0 0 0 0 0.550664 0 0 0 0.8 0"/>
        <feBlend mode="normal" in2="BackgroundImageFix" result="effect1_dropShadow_101_68"/>
        <feBlend mode="normal" in="SourceGraphic" in2="effect1_dropShadow_101_68" result="shape"/>
      </filter>
    </defs>
  </svg>
  

  <svg id="btndownR" xmlns="http://www.w3.org/2000/svg" width="166" height="167" viewBox="0 0 166 167" fill="none">
    <g filter="url(#filter0_d_101_69)">
      <path d="M96.3452 142.996C90.7676 153.864 75.2324 153.864 69.6548 142.996L7.61026 22.0988C2.48753 12.1168 9.73577 0.25 20.9555 0.25L145.045 0.25C156.264 0.25 163.512 12.1168 158.39 22.0988L96.3452 142.996Z" fill="#6BE3B7"/>
      <path d="M71.879 141.855L9.83446 20.9573C5.56552 12.639 11.6057 2.75 20.9555 2.75L145.045 2.75C154.394 2.75 160.434 12.639 156.166 20.9573L94.121 141.855C89.473 150.912 76.527 150.912 71.879 141.855Z" stroke="#04916E" stroke-width="5"/>
    </g>
    <defs>
      <filter id="filter0_d_101_69" x="0.935562" y="0.25" width="164.129" height="165.897" filterUnits="userSpaceOnUse" color-interpolation-filters="sRGB">
        <feFlood flood-opacity="0" result="BackgroundImageFix"/>
        <feColorMatrix in="SourceAlpha" type="matrix" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0" result="hardAlpha"/>
        <feOffset dy="10"/>
        <feGaussianBlur stdDeviation="2.5"/>
        <feComposite in2="hardAlpha" operator="out"/>
        <feColorMatrix type="matrix" values="0 0 0 0 0.320733 0 0 0 0 0.68 0 0 0 0 0.550664 0 0 0 0.8 0"/>
        <feBlend mode="normal" in2="BackgroundImageFix" result="effect1_dropShadow_101_69"/>
        <feBlend mode="normal" in="SourceGraphic" in2="effect1_dropShadow_101_69" result="shape"/>
      </filter>
    </defs>
  </svg>


<div class="half-circleL"><img src="https://pic.in.th/image/ksfRx" alt="Image inside Half Circle"></div>

<div class="half-circleR"><img src="https://pic.in.th/image/k3Twh" alt="Image inside Half Circle"></div>

<div class="bordermonitor"></div>

<div class="monitor"><p class="p1">TOUCHY</p><p class="p2">ROBOT</p><p class="p3"></p><p class="p4"></p></div>




  <script>
    // Function to update LED status when an event is received
    function updateLEDStatus(status) {
      document.getElementById("ledStatus").innerHTML = status;
    }

    // Function to handle LED state change event
    function handleLEDState(state) {
      updateLEDStatus(state);
    }

    // Function to start holding the button (turning on the LED)
    function startHoldLED() {
      fetch('/holdled/start')
        .then(response => response.text())
        .then(data => {
          console.log(data);
          updateLEDStatus(data);
        });
    }

    // Function to stop holding the button (turning off the LED)
    function stopHoldLED() {
      fetch('/holdled/stop')
        .then(response => response.text())
        .then(data => {
          console.log(data);
          updateLEDStatus(data);
        });
    }

    // Establish a server-sent events (SSE) connection with the server
    const eventSource = new EventSource('/events');
    eventSource.onmessage = function(event) {
      const eventData = JSON.parse(event.data);
      if (eventData.event === "led_state") {
        handleLEDState(eventData.data);
      }
    };
  </script>
</body>
</html>)rawliteral";

void setup() {
  Serial.begin(115200);
  Serial.print("Setting AP (Access Point)…");
  // Connect to Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/toggleled", HTTP_GET, [](AsyncWebServerRequest *request){
    // Toggle the LED state when the button is released after a hold
    if (buttonState && ledHoldState) {
//      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      events.send(String(ledState ? "ON" : "OFF").c_str(), "led_state", millis());
      ledHoldState = false;
      request->send(200, "text/plain", ledState ? "ON" : "OFF");
//      digitalWrite(2,LOW);
    } else {
      // If the button is not being held, respond with the current LED state
      request->send(200, "text/plain", ledState ? "ON" : "OFF");
//      digitalWrite(2,LOW);
    }
  });

  // New route to handle starting the hold (turning on the LED)
  server.on("/holdled/start", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!buttonState) {
      // Start the button press timing
      buttonState = true;
      buttonPressStartTime = millis();
      ledHoldState = false;
    }
    request->send(200, "text/plain", "Holding LED...");
    digitalWrite(2,HIGH);
  });

  // New route to handle stopping the hold (turning off the LED)
  server.on("/holdled/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    if (buttonState) {
      // Check the button press duration to determine if it's a hold
      unsigned long buttonPressDuration = millis() - buttonPressStartTime;
      if (buttonPressDuration >= HOLD_DURATION_MS) {
        // Hold duration detected, set the LED hold state
        ledHoldState = true;
      }
      buttonState = false;
    }
    request->send(200, "text/plain", ledHoldState ? "ON" : "OFF");
    digitalWrite(2,LOW);
  });

  events.onConnect([](AsyncEventSourceClient *client){
    // Send the initial LED state when a client connects
    events.send(String(ledState ? "ON" : "OFF").c_str(), "led_state", millis());
  });
  server.addHandler(&events);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
