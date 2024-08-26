#pragma once

#define GLFW_INCLUDE_VULKAN

#include <string>
#include <vulkan/vulkan.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace lve {

struct ANativeWindowDeleter {
    void operator()(ANativeWindow *window) { ANativeWindow_release(window); }
};

class LveWindow {
 public:
  LveWindow(int w, int h, std::string name);
  ~LveWindow();

  LveWindow(const LveWindow &) = delete;
  LveWindow &operator=(const LveWindow &) = delete;

  bool shouldClose() { return false; }//glfwWindowShouldClose(window); }
  VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
  bool wasWindowResized() { return framebufferResized; }
  void resetWindowResizedFlag() { framebufferResized = false; }

  void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
  void reset(ANativeWindow* nativeWindow) {
      window.reset(nativeWindow);
  }

 private:
  //static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
  void initWindow();

  int width;
  int height;
  bool framebufferResized = false;

  std::string windowName;
  std::unique_ptr<ANativeWindow, ANativeWindowDeleter> window;
};
}  // namespace lve
