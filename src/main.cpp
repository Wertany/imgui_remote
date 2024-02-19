#include <cmath>

#include "imgui/imgui.h"
#include "implot.h"
#include "web_server.hpp"

ImGuiKey toImGuiKey(int32_t keyCode) {
  switch (keyCode) {
    case 8: return ImGuiKey_Backspace;
    case 9: return ImGuiKey_Tab;
    case 13: return ImGuiKey_Enter;
    case 16: return ImGuiKey_ModShift;
    case 17: return ImGuiKey_ModCtrl;
    case 18: return ImGuiKey_ModAlt;
    case 19: return ImGuiKey_Pause;
    case 20: return ImGuiKey_CapsLock;
    case 27: return ImGuiKey_Escape;
    case 32: return ImGuiKey_Space;
    case 33: return ImGuiKey_PageUp;
    case 34: return ImGuiKey_PageDown;
    case 35: return ImGuiKey_End;
    case 36: return ImGuiKey_Home;
    case 37: return ImGuiKey_LeftArrow;
    case 38: return ImGuiKey_UpArrow;
    case 39: return ImGuiKey_RightArrow;
    case 40: return ImGuiKey_DownArrow;
    case 45: return ImGuiKey_Insert;
    case 46: return ImGuiKey_Delete;
    case 48: return ImGuiKey_0;
    case 49: return ImGuiKey_1;
    case 50: return ImGuiKey_2;
    case 51: return ImGuiKey_3;
    case 52: return ImGuiKey_4;
    case 53: return ImGuiKey_5;
    case 54: return ImGuiKey_6;
    case 55: return ImGuiKey_7;
    case 56: return ImGuiKey_8;
    case 57: return ImGuiKey_9;
    case 65: return ImGuiKey_A;
    case 66: return ImGuiKey_B;
    case 67: return ImGuiKey_C;
    case 68: return ImGuiKey_D;
    case 69: return ImGuiKey_E;
    case 70: return ImGuiKey_F;
    case 71: return ImGuiKey_G;
    case 72: return ImGuiKey_H;
    case 73: return ImGuiKey_I;
    case 74: return ImGuiKey_J;
    case 75: return ImGuiKey_K;
    case 76: return ImGuiKey_L;
    case 77: return ImGuiKey_M;
    case 78: return ImGuiKey_N;
    case 79: return ImGuiKey_O;
    case 80: return ImGuiKey_P;
    case 81: return ImGuiKey_Q;
    case 82: return ImGuiKey_R;
    case 83: return ImGuiKey_S;
    case 84: return ImGuiKey_T;
    case 85: return ImGuiKey_U;
    case 86: return ImGuiKey_V;
    case 87: return ImGuiKey_W;
    case 88: return ImGuiKey_X;
    case 89: return ImGuiKey_Y;
    case 90: return ImGuiKey_Z;

    // case 91: return ImGuiKey_LWin;
    // case 92: return ImGuiKey_RWin;
    // case 93: return ImGuiKey_Apps;
    case 91: 
    case 92:
    case 93: return ImGuiKey_ModSuper;

    case 96: return ImGuiKey_Keypad0;
    case 97: return ImGuiKey_Keypad1;
    case 98: return ImGuiKey_Keypad2;
    case 99: return ImGuiKey_Keypad3;
    case 100: return ImGuiKey_Keypad4;
    case 101: return ImGuiKey_Keypad5;
    case 102: return ImGuiKey_Keypad6;
    case 103: return ImGuiKey_Keypad7;
    case 104: return ImGuiKey_Keypad8;
    case 105: return ImGuiKey_Keypad9;
    case 106: return ImGuiKey_KeypadMultiply;
    case 107: return ImGuiKey_KeypadAdd;
    case 108: return ImGuiKey_KeypadEnter;
    case 109: return ImGuiKey_KeypadSubtract;
    case 110: return ImGuiKey_KeypadDecimal;
    case 111: return ImGuiKey_KeypadDivide;
    case 112: return ImGuiKey_F1;
    case 113: return ImGuiKey_F2;
    case 114: return ImGuiKey_F3;
    case 115: return ImGuiKey_F4;
    case 116: return ImGuiKey_F5;
    case 117: return ImGuiKey_F6;
    case 118: return ImGuiKey_F7;
    case 119: return ImGuiKey_F8;
    case 120: return ImGuiKey_F9;
    case 121: return ImGuiKey_F10;
    case 122: return ImGuiKey_F11;
    case 123: return ImGuiKey_F12;
    case 144: return ImGuiKey_NumLock;
    case 145: return ImGuiKey_ScrollLock;
    case 186: return ImGuiKey_Semicolon;
    case 187: return ImGuiKey_Equal;
    case 188: return ImGuiKey_Comma;
    case 189: return ImGuiKey_Minus;
    case 190: return ImGuiKey_Period;
    case 191: return ImGuiKey_Slash;
    case 219: return ImGuiKey_LeftBracket;
    case 220: return ImGuiKey_Backslash;
    case 221: return ImGuiKey_RightBracket;
    case 222: return ImGuiKey_Apostrophe;
    default: return ImGuiKey_COUNT;
  }

  return ImGuiKey_COUNT;
}

int main() {
  int port = 5000;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  ImGui::GetIO().MouseDrawCursor = true;

  ImGui::StyleColorsDark();
  ImGui::GetStyle().AntiAliasedFill = false;
  ImGui::GetStyle().AntiAliasedLines = false;
  ImGui::GetStyle().WindowRounding = 0.0F;
  ImGui::GetStyle().ScrollbarRounding = 0.0F;

  auto &server = dc::web_server::WebServer::GetWebServer();

  server.Initialize();

  while (true) {
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(nullptr);

    ImGui::Begin("ImPlot", nullptr);
    static float xs1[1001];
    static float ys1[1001];
    for (int i = 0; i < 1001; ++i) {
      xs1[i] = i * 0.001F;
      ys1[i] = 0.5F + 0.5F * sinf(50 * (xs1[i] + static_cast<float>(ImGui::GetTime()) / 10));
    }
    static double xs2[20];
    static double ys2[20];
    for (int i = 0; i < 20; ++i) {
      xs2[i] = i * 1 / 19.0F;
      ys2[i] = xs2[i] * xs2[i];
    }
    if (ImPlot::BeginPlot("Line Plots")) {
      ImPlot::SetupAxes("x", "y");
      ImPlot::PlotLine("f(x)", xs1, ys1, 1001);
      ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
      ImPlot::PlotLine("g(x)", xs2, ys2, 20, ImPlotLineFlags_Segments);
      ImPlot::EndPlot();
    }
    ImGui::End();

    ImGui::EndFrame();
    ImGui::Render();

    server.Tick();
  }

  ImPlot::DestroyContext();
  ImGui::DestroyContext();

  return 0;
}