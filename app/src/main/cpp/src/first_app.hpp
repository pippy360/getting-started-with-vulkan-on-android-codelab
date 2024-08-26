#pragma once

#include "lve_descriptors.hpp"
#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"
#include "lve_window.hpp"

#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>

// std
#include <memory>
#include <vector>

namespace lve {
class FirstApp {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();

    FirstApp(const FirstApp &) = delete;
    FirstApp &operator=(const FirstApp &) = delete;

    void init();
    bool isInitialized() { return initialized; };

    void run();

    void reset(ANativeWindow *newWindow, AAssetManager *newManager) {
        lveWindow.reset(newWindow);
        assetManager = newManager;
    };

private:
    bool initialized = false;
    void loadGameObjects();

    LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan Tutorial"};
    LveDevice lveDevice{lveWindow};
    LveRenderer lveRenderer{lveWindow, lveDevice};

    // note: order of declarations matters
    std::unique_ptr<LveDescriptorPool> globalPool{};
    LveGameObject::Map gameObjects;
    AAssetManager *assetManager;
};
}  // namespace lve