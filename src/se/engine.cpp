/*!
 *  @file src/se/engine.cpp
 * 
 *  Copyright 2019 Nicholas Hollander <nhhollander@wpi.edu>
 * 
 *  Licensed under the MIT license (see LICENSE for the complete text)
 */

#include "se/engine.hpp"

#include "se/graphics/graphicsController.hpp"

#include "util/log.hpp"
#include "util/config.hpp"
#include "util/dirs.hpp"

se::Engine::Engine() {
    // Load the base configuration
    DEBUG("Loading base configuration");
    this->config = new util::Configuration("base_config");
    std::string cfgfile = util::dirs::app_data();
    cfgfile += "/config.cfg";
    this->config->load(cfgfile.c_str());

    // Initialize graphics
    this->graphics_controller = new se::graphics::GraphicsController(this);

    INFO("Engine construction complete");

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

se::Engine::~Engine() {

    this->threads_run = false;

    delete this->graphics_controller;
    INFO("Engine destruction complete");
}