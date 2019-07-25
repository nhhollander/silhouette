/*!
 *  @file include/se/graphics/shader.hpp
 * 
 *  Copyright 2019 Nicholas Hollander <nhhollander@wpi.edu>
 * 
 *  Licensed under the MIT license (see LICENSE for the complete text)
 */

#ifndef _SE_GRAPHICS_SHADER_H_
#define _SE_GRAPHICS_SHADER_H_

#include "se/fwd.hpp"

#include <map>

namespace se::graphics {

    /*!
     *  Shader State.
     */
    enum class ShaderState {
        LOADING,
        READY,
        ERROR
    };

    /*!
     *  Shader Class.
     * 
     *  This class represents a single stage of the rendering process, as
     *  described on the
     *  [Khronos Wiki](https://www.khronos.org/opengl/wiki/Shader).
     */
    class Shader {

        private:

            /*!
             *  Create a new shader object.
             * 
             *  Where possible, it is preferred to retrieve shaders from the
             *  cache instead of creating multiple instances.
             * 
             *  @param parent   The parent `se::Engine` instance.
             *  @param name     Name of the shader (including source files).
             *  @param type     OpenGL type of the shader.
             */
            Shader(se::Engine* engine, const char* name, unsigned int type);

            /*!
             *  Destroy this shader.
             */
            ~Shader();

            /// Parent Engine
            se::Engine* engine;
            /// Shader Name
            std::string name;
            /// OpenGL shader type
            unsigned int type;

            /// OpenGL shader ID
            unsigned int gl_shader = -1;

            /// Shader Object State
            volatile ShaderState state = ShaderState::LOADING;

            /*!
             *  Source Code.
             * 
             *  Uncompiled source code for uncompiled shaders only.
             */
            char* source_code = nullptr;

            /*!
             *  Compilation Method.
             * 
             *  **Warning:** This method must only be called from the graphics
             *  thread.
             */
            void compile();

            /*!
             *  Static Shader Cache.
             * 
             *  Compiled shaders live here.
             */
            static std::map<uint32_t, Shader*> cache;

        public:

            /*!
             *  Get a shader.
             * 
             *  This method attempts to retrieve a shader by performing the
             *  following steps.
             * 
             *  1. Check the shader cache
             *  2. Construct a new shader
             * 
             *  @param enigne   Parent engine.
             *  @param name Name of the shader.  Extension will automatically be
             *              applied based on the value of `type`.
             *  @param type Type of the shader.
             */
            static Shader* get_shader(se::Engine* engine, const char* name, unsigned int type);

            /*!
             *  Get the shader name.
             */
            std::string get_name();

            /*!
             *  Get the shader type.
             */
            unsigned int get_type();

            /*!
             *  Get the State.
             * 
             *  Returns the state of the shader object.
             */
            ShaderState get_state();

            /*!
             *  Wait for Loading to complete.
             * 
             *  **Warning:** Make sure to check the state after loading is
             *  complete, as it may have resulted in `ShaderState::ERROR`.
             * 
             *  This method will block until this shader is no longer in the
             *  `ShaderState::LOADING` state, at which point it will return the
             *  new state.
             * 
             *  This method checks for load completion every 10ms.
             * 
             *  @return The state the shader is in after loading.
             */
            ShaderState wait_for_loading();

            /*!
             *  Get the OpenGL ID.
             */
            unsigned int get_gl_id();
            

    };

}

#endif