#include "lve_window.hpp"

// std
#include <stdexcept>

namespace lve {

LveWindow::LveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
  initWindow();
}

LveWindow::~LveWindow() {
  //glfwDestroyWindow(window);
  //glfwTerminate();
}

void LveWindow::initWindow() {
//  glfwInit();
//  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
//
//  window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
  //FIXME: glfwSetWindowUserPointer(window, this);
  //FIXME: glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
//  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
//    throw std::runtime_error("failed to craete window surface");
//  }
    //assert(window != nullptr);  // window not initialized
    const VkAndroidSurfaceCreateInfoKHR create_info{
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .pNext = nullptr,
            .flags = 0,
            .window = window.get()};

    auto retval = vkCreateAndroidSurfaceKHR(instance, &create_info,
                                       nullptr /* pAllocator */, surface);
    if (retval != VK_SUCCESS)
        exit(1);
}

//void LveWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
//  auto lveWindow = reinterpret_cast<LveWindow *>(glfwGetWindowUserPointer(window));
//  lveWindow->framebufferResized = true;
//  lveWindow->width = width;
//  lveWindow->height = height;
//}

}  // namespace lve
