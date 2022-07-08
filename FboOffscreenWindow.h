#ifndef FBOOFFSCREENWINDOW_H
#define FBOOFFSCREENWINDOW_H

#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <vtkExternalOpenGLRenderWindow.h>

class myFboRenderer;
class FboOffscreenWindow: public vtkExternalOpenGLRenderWindow, protected QOpenGLFunctions {
public:
    FboOffscreenWindow();
    ~FboOffscreenWindow();
    virtual auto OpenGLInitState() -> void override;
    myFboRenderer* QtParentRenderer = nullptr;
    static auto New() -> FboOffscreenWindow*;
    auto Render() -> void override;
    auto InternalRender() -> void;
    auto SetFramebufferObject(QOpenGLFramebufferObject* fbo) -> void;

};

#endif // FBOOFFSCREENWINDOW_H
