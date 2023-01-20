#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include <SocketIOclient.h>
#include <WebSocketsClient.h>
#include <WiFi.h>
#include <esp_task_wdt.h>

#include <ClockScene.h>
#include <Globals.h>
#include <GoLScene.h>
#include <MIDIScene.h>
#include <MarioScene.h>
#include <MetaballsScene.h>
#include <MonaLisaScene.h>
#include <OTAStatusScene.h>
#include <PWMTestScene.h>
#include <Scene.h>
#include <SceneSwitcher.h>
#include <TextTestScene.h>
#include <WasmTestScene.h>
#include <WiFiStatusScene.h>

const int PIN_ENABLE = 47;

const int PIN_SWITCH = 45;

const int PIN_LATCH = 21;
const int PIN_CLOCK = 20;
const int PIN_DATA = 19;

const int PWM_CHANNEL = 0;
const int PWM_FREQUENCY = 1000;
const int PWM_RESOLUTION = 10;
const int PWM_DUTY_CYCLE_MAX = 1 << PWM_RESOLUTION;

// clang-format off
const int POSITIONS[PIXELS] = {
  0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
  0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
  0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
  0x4f, 0x4e, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x48, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
  0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
  0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
  0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
  0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
  0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0xa7, 0xa6, 0xa5, 0xa4, 0xa3, 0xa2, 0xa1, 0xa0, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
  0xaf, 0xae, 0xad, 0xac, 0xab, 0xaa, 0xa9, 0xa8, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
  0xcf, 0xce, 0xcd, 0xcc, 0xcb, 0xca, 0xc9, 0xc8, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
  0xc7, 0xc6, 0xc5, 0xc4, 0xc3, 0xc2, 0xc1, 0xc0, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xe7, 0xe6, 0xe5, 0xe4, 0xe3, 0xe2, 0xe1, 0xe0, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
  0xef, 0xee, 0xed, 0xec, 0xeb, 0xea, 0xe9, 0xe8, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
};
// clang-format on

typedef struct RenderingContext {
  char pixels1[PIXELS] = {};
  char pixels2[PIXELS] = {};
  char *pixels = pixels1;
  char *buffer = pixels2;
  int dc_max = 0x1e;
  int dcs[4] = {0, 0x05, 0x1a, 0x7f};
} RenderingContext;

RenderingContext rendering_context;

int frame = 0;

Scene *current_scene = NULL;

void set_scene(Scene *scene) {
  current_scene = scene;

  if (current_scene) {
    current_scene->init();
  }
}

SocketIOclient socketIO;

bool on = true;

void socketIOEvent(socketIOmessageType_t type, uint8_t *payload,
                   size_t length) {
  switch (type) {
  case sIOtype_DISCONNECT:
    Serial.printf("[IOc] Disconnected!\n");
    break;
  case sIOtype_CONNECT:
    Serial.printf("[IOc] Connected to url: %s\n", payload);

    // join default namespace (no auto join in Socket.IO V3)
    socketIO.send(sIOtype_CONNECT, "/");
    break;
  case sIOtype_EVENT: {
    char *sptr = NULL;
    int id = strtol((char *)payload, &sptr, 10);
    Serial.printf("[IOc] get event: %d id: %d\n", length, id);
    // Serial.printf("[IOc] get event: %s id: %d\n", payload, id);
    if (id) {
      payload = (uint8_t *)sptr;
    }
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, payload, length);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    String eventName = doc[0];
    Serial.printf("[IOc] event name: %s\n", eventName.c_str());

    // Message Includes a ID for a ACK (callback)
    if (id) {
      // creat JSON message for Socket.IO (ack)
      DynamicJsonDocument docOut(1024);
      JsonArray array = docOut.to<JsonArray>();

      // add payload (parameters) for the ack (callback function)
      JsonObject param1 = array.createNestedObject();
      param1["now"] = millis();

      // JSON to String (serializion)
      String output;
      output += id;
      serializeJson(docOut, output);

      // Send event
      socketIO.send(sIOtype_ACK, output);
    } else {
      if (eventName == "activate") {
        Serial.println("IFTTT activation");

        String scene = doc[1];

        Serial.println("Scene: " + scene);

        if (scene == "pixels") {
          Serial.println("Toggling Pixels");
          on = !on;
          ledcWrite(PWM_CHANNEL, on ? 0 : PWM_DUTY_CYCLE_MAX);
          // TODO save last state in EPROM
        }
      } else if (eventName == "midi") {
        if (current_scene) {
          auto payload = doc[1];
          int status = payload["status"];
          int channel = payload["data1"];
          int value = payload["data2"];

          current_scene->handle_midi(status, channel, value);

          // if (channel < 4) {
          //   rendering_context.dcs[channel] = value;
          // } else if (channel == 4) {
          //   rendering_context.dc_max = value ? value : 1;
          // }
        }
      } else if (eventName == "binary") {
        if (current_scene) {
          current_scene->load_wasm(payload, length);
        }
      }
    }
  } break;
  case sIOtype_ACK:
    Serial.printf("[IOc] get ack: %u\n", length);
    break;
  case sIOtype_ERROR:
    Serial.printf("[IOc] get error: %u\n", length);
    break;
  case sIOtype_BINARY_EVENT:
    Serial.printf("[IOc] get binary: %u\n", length);
    break;
  case sIOtype_BINARY_ACK:
    Serial.printf("[IOc] get binary ack: %u\n", length);
    break;
  }
}

int prevSwitchState;

void reset_settings(Preferences &preferences) {
  Serial.println("Resetting settings");

  preferences.clear();

  preferences.putString("wifi_ssid", "<your WiFi SSID>");
  preferences.putString("wifi_password", "<your WiFi password>");
  preferences.putString("hostname", "obegransad");
}

WiFiStatusScene wifi_status_scene;
OTAStatusScene ota_status_scene;
SceneSwitcher scene_switcher;

void render() {
  memset(rendering_context.pixels, 0, sizeof(rendering_context.pixels1));

  if (current_scene) {
    current_scene->render(rendering_context.pixels, frame);
  }

  frame++;

  char *swap = rendering_context.buffer;
  rendering_context.buffer = rendering_context.pixels;
  rendering_context.pixels = swap;
}

void draw_loop(void *pRenderingContext) {
  RenderingContext &ctx = *static_cast<RenderingContext *>(pRenderingContext);

  int cycle = 0;
  int dc;
  int scaled_dcs[4];
  int pos;
  bool on;

  for (;;) {
    dc = cycle % ctx.dc_max;

    for (int i = 0; i < 4; i++) {
      scaled_dcs[i] = ctx.dcs[i] * ctx.dc_max / 0x7f;
    }

    for (int idx = 0; idx < PIXELS; idx++) {
      pos = POSITIONS[idx];
      on = scaled_dcs[ctx.buffer[pos] & 3] > dc;

      digitalWrite(PIN_DATA, on ? HIGH : LOW);
      digitalWrite(PIN_CLOCK, HIGH);
      digitalWrite(PIN_CLOCK, LOW);
    }

    digitalWrite(PIN_LATCH, HIGH);
    digitalWrite(PIN_LATCH, LOW);

    cycle++;
  }
}

void setup() {
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PIN_ENABLE, PWM_CHANNEL);

  pinMode(PIN_SWITCH, INPUT_PULLUP);
  pinMode(BUILTIN_LED, OUTPUT);

  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  digitalWrite(PIN_DATA, LOW);
  digitalWrite(PIN_LATCH, LOW);
  digitalWrite(PIN_CLOCK, LOW);

  prevSwitchState = !digitalRead(PIN_SWITCH);

  Serial.begin(115200);

  delay(1000);

  Serial.println("Booting");

  Preferences preferences;

  preferences.begin("obegransad");

  // reset_settings(preferences);

  String wifi_ssid = preferences.getString("wifi_ssid");
  String wifi_password = preferences.getString("wifi_password");
  String hostname = preferences.getString("hostname");

  preferences.end();

  set_scene(&wifi_status_scene);

  Serial.printf("Connecting to %s", wifi_ssid.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000 / FPS);
    render();
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");

  ArduinoOTA.setHostname(hostname.c_str());

  ArduinoOTA
      .onStart([]() {
        String type;

        if (ArduinoOTA.getCommand() == U_FLASH) {
          type = "sketch";
        } else { // U_SPIFFS
          type = "filesystem";
        }
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS
        // using SPIFFS.end()
        Serial.println("Start updating " + type);

        set_scene(&ota_status_scene);

        if (ota_status_scene.set_progress(0)) {
          render();
        }
      })
      .onEnd([]() {
        Serial.println("\nEnd");
        if (ota_status_scene.set_progress(100)) {
          render();
        }
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        int pct = progress * 100 / total;
        Serial.printf("Progress: %u%%\r", pct);

        if (ota_status_scene.set_progress(pct)) {
          render();
        }
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
          Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
          Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
          Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
          Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
          Serial.println("End Failed");
      });

  ArduinoOTA.begin();

  socketIO.beginSSL("frekvens-fjarrkontroll.glitch.me", 443,
                    "/socket.io/?EIO=4");

  socketIO.onEvent(socketIOEvent);

  scene_switcher.append_scene(new ClockScene(), 10);
  scene_switcher.append_scene(new MonaLisaScene(), 5);
  scene_switcher.append_scene(new GoLScene(), 20);
  scene_switcher.append_scene(new MarioScene(), 5);
  // scene_switcher.append_scene(new MetaballsScene(), 20);

  set_scene(&scene_switcher);
  // set_scene(new MIDIScene());
  // set_scene(new PWMTestScene());
  // set_scene(new TextTestScene());
  set_scene(new WasmTestScene());

  esp_task_wdt_init(5000, false);

  TaskHandle_t task_handle = NULL;
  // UBaseType_t priority = 2 | portPRIVILEGE_BIT;
  UBaseType_t task_priority = tskIDLE_PRIORITY + 1;
  // vTaskPrioritySet

  auto result = xTaskCreatePinnedToCore(
      &draw_loop, "draw_loop", configMINIMAL_STACK_SIZE, &rendering_context,
      task_priority, &task_handle, 0);
  if (result == pdPASS) {
    Serial.println("Render loop task created");
  } else {
    Serial.println("Failed to create render loop task");
  }
}

void loop() {
  ArduinoOTA.handle();
  socketIO.loop();

  int switchState = !digitalRead(PIN_SWITCH);

  if (switchState != prevSwitchState) {
    prevSwitchState = switchState;
    // digitalWrite(BUILTIN_LED, switchState);
    // Serial.println(switchState ? "ON" : "OFF");

    if (switchState == LOW) {
      on = !on;
      ledcWrite(PWM_CHANNEL, on ? 0 : PWM_DUTY_CYCLE_MAX);
    }
  }

  render();

  // TODO make this based on elapsed time
  delay(1000 / FPS);
}