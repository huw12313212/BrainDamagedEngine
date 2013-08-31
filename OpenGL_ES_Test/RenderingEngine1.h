#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.hpp"

class RenderingEngine1 : public IRenderingEngine {
public:
    RenderingEngine1();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep) {}
    void OnRotate(DeviceOrientation newOrientation) {}
private:
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
};

IRenderingEngine* CreateRenderer1()
{
    return new RenderingEngine1();
}