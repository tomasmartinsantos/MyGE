#pragma once

#ifdef MG_PLATFORM_WINDOWS

extern MyGE::Application* MyGE::CreateApplication();

int main(int argc, char** argv)
{
    auto App = MyGE::CreateApplication();

    App->Run();

    delete App;
}

#endif