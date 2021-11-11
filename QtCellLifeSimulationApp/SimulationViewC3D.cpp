#include "SimulationViewC3D.h"

#ifdef C3D_USAGE

static void createShapeSegment(GeometryRep* pShapeRep, const MbVector3D& vecMove, const Color& color, SceneSegment* pParent)
{
	SceneSegment* pSegment = new SceneSegment(pShapeRep, pParent);
	pSegment->SetColorPresentationMaterial(color);
	MbMatrix3D relativeMatrix; relativeMatrix.Move(vecMove);
	pSegment->CreateRelativeMatrix(relativeMatrix);
}

SimulationViewC3D::SimulationViewC3D(QWidget* parent)
	: SimulationView(parent)
{
	QtVision::setSurfaceFormat();
	glWidget = new QtVision::QtOpenGLSceneWidget(this);
	glWidget->setStyleSheet("background-image:url(\":/backgrounds/resources/bg.png\");background-position: center;");
	setCentralWidget(glWidget);
	testScene();
	checkLicense();
}

SimulationViewC3D::~SimulationViewC3D()
{
	delete glWidget;
}

void SimulationViewC3D::drawItem(int x, int y, int size, QColor color)
{
	//view->scene()->addEllipse(x, y, size, size, Qt::NoPen, color);
}

void SimulationViewC3D::clear()
{
	//view->scene()->clear();
}

void SimulationViewC3D::testScene()
{

	glWidget->mainLight()->SetDoubleSided(true);
	glWidget->viewport()->SetBackgroundColour(Color(74, 74, 74));

	SceneSegment* pTopSegment = glWidget->sceneContent()->GetRootSegment();
	Q_ASSERT(pTopSegment != nullptr);

	// 1 Cone
	::createShapeSegment(SceneGenerator::Instance()->CreateCone(1.5, 1.5), MbVector3D(0.0, 4.0, -1.5), Color(255, 0, 0), pTopSegment);
	// 2 Cylinder
	::createShapeSegment(SceneGenerator::Instance()->CreateCylinder(1.5, 1.5), MbVector3D(-5.0, 4.0, -1.5), Color(0, 190, 0), pTopSegment);
	// 3 Box
	::createShapeSegment(SceneGenerator::Instance()->CreateBox(2.5, 2.5, 2.5), MbVector3D(5.0, -4.0, 0.0), Color(0, 0, 180), pTopSegment);
	// 4 Rectangle
	::createShapeSegment(SceneGenerator::Instance()->CreateRectangle(2.5, 2.5), MbVector3D(0.0, -4.0, 0.0), Color(0, 100, 180), pTopSegment);
	// 5 Sphere
	::createShapeSegment(SceneGenerator::Instance()->CreateSphere(1.5), MbVector3D(-5.0, -4.0, 0.0), Color(100, 100, 180), pTopSegment);
	// 5 Rectangle
	::createShapeSegment(SceneGenerator::Instance()->CreateRectangle(2.5, 2.5), MbVector3D(5.0, 4.0, 0.0), Color(200, 100, 180), pTopSegment);

	auto pLabel = new LabelGeometry();
	pLabel->Init(WString("text"), MbPlacement3D(MbVector3D::xAxis, MbVector3D::yAxis, {}));
	pLabel->SetFontSize(22);
	new SceneSegment(new GeometryRep(pLabel), pTopSegment);

	glWidget->sceneContent()->GetContainer()->SetUseVertexBufferObjects(true);
	QtVision::createProcessesCameraControls(glWidget->graphicsEngine()->GetTopEssence());
	glWidget->viewport()->ZoomToFit(glWidget->sceneContent()->GetBoundingBox());

	glWidget->move(QPoint(200, 200));
	QRect geom = QApplication::desktop()->availableGeometry();
}

void SimulationViewC3D::checkLicense()
{
	QtVision::setLicense(LKEY, LSIGN);
	QtVision::activateLicense();
}

#endif