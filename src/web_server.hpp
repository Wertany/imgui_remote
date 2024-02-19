#ifndef SRC_WEB_SERVER_HPP
#define SRC_WEB_SERVER_HPP
#ifndef MAIN_INCLUDE_WEB_SERVER_HPP
#define MAIN_INCLUDE_WEB_SERVER_HPP

#include <imgui-ws/imgui-ws.h>

#include <chrono>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "imgui/imgui.h"

namespace dc::web_server {

struct VSync {
  explicit VSync(double rate_fps = 60.0) : tStep_us(1000000.0 / rate_fps) {}

  uint64_t tStep_us;
  uint64_t tLast_us = t_us();
  uint64_t tNext_us = tLast_us + tStep_us;

  [[nodiscard]] static inline uint64_t t_us() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::high_resolution_clock::now().time_since_epoch())
        .count();// duh ..
  }

  inline void wait() {
    uint64_t t_now_us = t_us();
    while (t_now_us < tNext_us - 100) {
      std::this_thread::sleep_for(
          std::chrono::microseconds(static_cast<uint64_t>(0.9 * (tNext_us - t_now_us))));
      t_now_us = t_us();
    }

    tNext_us += tStep_us;
  }

  inline float delta_s() {
    uint64_t t_now_us = t_us();
    uint64_t res = t_now_us - tLast_us;
    tLast_us = t_now_us;
    return static_cast<float>(res) / 1e6F;
  }
};

struct State {
  State() = default;

  struct ClientData {
    bool hasControl = false;

    std::string ip = "---";
  };

  // client control
  float tControl_s{10.0F};
  float tControlNext_s{0.0F};

  int controlIteration = 0;
  int curIdControl = -1;
  std::map<int, ClientData> clients;

  struct InputEvent {
    enum Type {
      kEKey,
      kEMousePos,
      kEMouseButton,
      kEMouseWheel,
    };

    Type type;

    bool isDown = false;

    ImGuiKey key = ImGuiKey_COUNT;
    ImGuiMouseButton mouseButton{-1};
    ImVec2 mousePos;
    float mouseWheelX{0.0F};
    float mouseWheelY{0.0F};
  };

  // client input
  std::vector<InputEvent> input_events;
  std::string last_add_text;

  void handle(ImGuiWS::Event &&event);
  void update();
};

class WebServer final {
public:
  WebServer() = default;
  
  static WebServer &GetWebServer() {
    static WebServer server;
    return server;
  }

  void Initialize();
  void Tick();
private:
  ImGuiWS imgui_ws_;
  State state_;
  VSync vsync_;
};

}// namespace web_server

#endif /* MAIN_INCLUDE_WEB_SERVER_HPP */


#endif /* SRC_WEB_SERVER_HPP */
