#ifndef MYFBORENDERER_H
#define MYFBORENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
class FboOffscreenWindow;
class myFboRenderer: public QQuickFramebufferObject::Renderer
{
public:
    myFboRenderer(FboOffscreenWindow *offscreenWindow);
    ~myFboRenderer();
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override ;

    FboOffscreenWindow* m_fboOffscreenWindow = nullptr;
    QOpenGLFramebufferObject* m_fbo = nullptr;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor = nullptr;
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
};

#endif // MYFBORENDERER_H
