#include <MyGE.h>


class ExampleLayer : public MyGE::Layer
{
    // Methods
    public:
        ExampleLayer()
            : Layer("Example")
        {
        }

        virtual void OnUpdate() override
        {
            MG_INFO("ExampleLayer::OnUpdate");
        }

        virtual void OnEvent(MyGE::Event& Event) override
        {
            MG_TRACE("{0}", Event);
        }
};

class Sandbox : public MyGE::Application
{
    // Methods
    public:
        Sandbox()
        {
            PushLayer(new ExampleLayer());
            PushOverlay(new MyGE::ImGuiLayer());
        }

        ~Sandbox()
        {

        }

};

MyGE::Application* MyGE::CreateApplication()
{
    return new Sandbox();
}