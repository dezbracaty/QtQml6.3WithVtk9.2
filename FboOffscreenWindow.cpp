#include "FboOffscreenWindow.h"
#include <vtkOpenGLState.h>

FboOffscreenWindow::FboOffscreenWindow()
{
    this->OffScreenRenderingOn();
}

FboOffscreenWindow::~FboOffscreenWindow()
{
    OffScreenRenderingOff();
}

void FboOffscreenWindow::OpenGLInitState()
{
    this->MakeCurrent();
    initializeOpenGLFunctions();

    // Get OpenGL viewport size as configured by QtQuick
    int glViewport[4];
    glGetIntegerv(GL_VIEWPORT, glViewport);
    //std::cout << "FboOffscreenWindow::OpenGLInitState - glViewport: " << glViewport[0] << "," << glViewport[1] << "," << glViewport[2] << "," << glViewport[3] << "\n";

    // Do not know why exactly we need this, but it seems to help with syncing the Qt-VTK OpenGL states
    this->GetState()->Initialize(this);

    // We now check the viewport size in vtkOpenGLState
    int vtkGLViewport[4];
    this->GetState()->vtkglGetIntegerv(GL_VIEWPORT, vtkGLViewport);
    //std::cout << "FboOffscreenWindow::OpenGLInitState - vtkGLViewport: " << vtkGLViewport[0] << "," << vtkGLViewport[1] << "," << vtkGLViewport[2] << "," << vtkGLViewport[3] << "\n";

    // We adjust if they went out of sync
    if (vtkGLViewport[2] != glViewport[2] || vtkGLViewport[3] != glViewport[3])
    {
        //std::cout << "Need to adjust viewport..\n";
        if (glViewport[2] > 1 && glViewport[3] > 1)
            this->GetState()->vtkglViewport(0, 0, glViewport[2], glViewport[3]);
    }

    // We can now reset the GL state based on the VTK state
    Superclass::OpenGLInitState();
    glUseProgram(0);

    glEnable(GL_BLEND);
    // This one throws an invalid enum
    //glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT, GL_FASTEST);

    //NOTE:
    // disabling the call to glDepthMask fixed an exception on windows
    // occured only if opacity (vtkProperty) is < 1.0.
    // this works fine on macOS & windows, not sure about Linux...

    //glDepthMask(GL_TRUE);

}

FboOffscreenWindow* FboOffscreenWindow::New()
{
    return new FboOffscreenWindow();
}

void FboOffscreenWindow::Render()
{
    if (this->QtParentRenderer) {
//        this->QtParentRenderer->update();
    }
}

void FboOffscreenWindow::InternalRender()
{
    Superclass::Render();
}

void FboOffscreenWindow::SetFramebufferObject(QOpenGLFramebufferObject *fbo)
{
    //            this->BackLeftBuffer = this->FrontLeftBuffer = this->BackBuffer = this->FrontBuffer = static_cast<unsigned int>(GL_COLOR_ATTACHMENT0);
    SetFrontLeftBuffer(GL_COLOR_ATTACHMENT0);
    SetFrontRightBuffer(GL_COLOR_ATTACHMENT0);
    SetBackLeftBuffer(GL_COLOR_ATTACHMENT0);
    SetBackRightBuffer(GL_COLOR_ATTACHMENT0);
    auto size                    = fbo->size();
    OffScreenRenderingOn();
    UseOffScreenBuffersOn();
    this->Size[0]                   = size.width();
    this->Size[1]                   = size.height();
//            this->NumberOfFrameBuffers      = 1;
//            this->FrameBufferObject         = static_cast<unsigned int>(fbo->handle());
//            this->DepthRenderBufferObject   = 0;
//            this->TextureObjects[0]         = static_cast<unsigned int>(fbo->texture());
//            this->OffScreenRendering        = 1;
//            this->OffScreenUseFrameBuffer   = 1;
    this->Modified();
}
