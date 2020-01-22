#include <MyGE.h>

class Sandbox : public MyGE::Application
{
    // Methods
    public:
        Sandbox()
        {

        }

        ~Sandbox()
        {

        }

};

MyGE::Application* MyGE::CreateApplication()
{
    return new Sandbox();
}