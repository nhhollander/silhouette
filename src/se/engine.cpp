/*!
 *  @file src/se/engine.cpp
 * 
 *  Copyright 2019 Nicholas Hollander <nhhollander@wpi.edu>
 * 
 *  Licensed under the MIT license (see LICENSE for the complete text)
 */

#include "se/engine.hpp"

#include "util/log.hpp"
#include "util/config.hpp"
#include "util/dirs.hpp"

se::Engine::Engine() {
    // Load the base configuration
    DEBUG("Loading base configuration");
    DEBUG("Hello");
    this->config = new util::Configuration("base_config");
    std::string cfgfile = util::dirs::app_data();
    cfgfile += "/config.cfg";
    this->config->load(cfgfile.c_str());

    INFO("Engine construction complete");
}

se::Engine::~Engine() {
    INFO("Engine destruction complete");
}