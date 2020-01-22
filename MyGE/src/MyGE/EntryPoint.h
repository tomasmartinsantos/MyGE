#pragma once

#ifdef MG_PLATFORM_WINDOWS

extern MyGE::Application* MyGE::CreateApplication();

int main(int argc, char** argv)
{
    MyGE::Log::Init();
    MG_CORE_WARN("Initialized Log");
    int a = 5;
    MG_INFO("Hello Var={0}", a);

    auto App = MyGE::CreateApplication();
    App->Run();
    delete App;
}

#endif