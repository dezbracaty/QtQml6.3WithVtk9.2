#include "myFboRenderer.h"
#include <QOpenGLFramebufferObject>
#include <iostream>
#include <FboOffscreenWindow.h>
myFboRenderer::myFboRenderer(FboOffscreenWindow *offscreenWindow)
: m_fboOffscreenWindow(offscreenWindow), m_fbo(0)
{
    m_fboOffscreenWindow->Register(NULL);
    m_fboOffscreenWindow->QtParentRenderer = this;

#ifdef __APPLE__
    m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
#endif

#ifdef __linux__
    m_interactor = vtkSmartPointer<quick::Vtk::GenericInteractor>::New();
#endif

#ifdef _MSC_VER
    m_interactor = vtkSmartPointer<quick::Vtk::Win32Interactor>::New();
#endif

    m_interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    m_interactor->SetRenderWindow(offscreenWindow);
    m_interactor->Initialize();
    m_interactor->SetInteractorStyle(m_interactorStyle);
}

myFboRenderer::~myFboRenderer()
{
    m_fboOffscreenWindow->QtParentRenderer = 0;
    m_fboOffscreenWindow->Delete();
}

void myFboRenderer::render()
{
    m_interactor->Disable();
    m_fboOffscreenWindow->PushState();
    m_fboOffscreenWindow->OpenGLInitState();
    m_fboOffscreenWindow->InternalRender();
    m_fboOffscreenWindow->PopState();
    m_interactor->Enable();
}

QOpenGLFramebufferObject *myFboRenderer::createFramebufferObject(const QSize &size)
{
    std::cout<<__FUNCTION__<<std::endl;
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    m_fbo =  new QOpenGLFramebufferObject(size, format);

    return m_fbo;
}
