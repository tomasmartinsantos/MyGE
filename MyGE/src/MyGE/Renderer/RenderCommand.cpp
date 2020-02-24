#include "mgpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace MyGE {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}