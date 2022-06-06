#include "SimulationViewC3D.h"

#ifdef C3D_USAGE

static inline Image ConvertToImage(QImage image)
{
	/// convert to vision image
	Image::Format format = Image::Format::UINT32;
	image = image.convertToFormat(QImage::Format_RGBA8888);
	image = image.mirrored();
	image = image.rgbSwapped();

	Image result;
	result.Init(image.width(), image.height(), format, (const unsigned char*)image.bits());

	return result;
}

static NodeKey createShapeSegment(GeometryRep* pShapeRep, const MbVector3D& vecMove, const Color& color, SceneSegment* pParent)
{
	SceneSegment* pSegment = new SceneSegment(pShapeRep, pParent);
	pSegment->SetColorPresentationMaterial(color);
	pSegment->GetTransform().Move(vecMove);
	return pSegment->GetUniqueKey();
}

SimulationViewC3D::SimulationViewC3D(QWidget* parent)
	: SimulationView(parent)
{
	QtVision::setSurfaceFormat();
	glWidget = new QtVision::QtOpenGLSceneWidget(this);
	setCentralWidget(glWidget);
	QtVision::createProcessesCameraControls(glWidget);
	prepareScene();
	checkLicense();
}

SimulationViewC3D::~SimulationViewC3D()
{
	delete glWidget;
}

void SimulationViewC3D::addDrawItem(int x, int y, int size, QColor color)
{
	frame.push_back(DrawItem{ x,y,float(0.5 * size),Color(color.red(), color.green(), color.blue()) });
}

void SimulationViewC3D::clear()
{
	frame.clear();
}

void SimulationViewC3D::resize3DScene()
{
	glWidget->sceneContent()->GetContainer()->SetUseVertexBufferObjects(true);
	glWidget->ZoomToFit();
}

void SimulationViewC3D::frameComplete()
{
	if (!processStartCheck())return;
	glWidget->sceneContent()->Clear();
	SceneSegment* pTopSegment = glWidget->sceneContent()->GetRootSegment();
	Q_ASSERT(pTopSegment != nullptr);
	std::vector<DrawItem> temp = frame;

	for (auto item : temp) {
		::createShapeSegment(
			SceneGenerator::Instance()->CreateSphere(item.size),
			MbVector3D(item.x, item.y, 0.0),
			item.color,
			pTopSegment
		);
	}
	frame.clear();
	glWidget->update();
	processEndCheck();
}

bool SimulationViewC3D::processStartCheck()
{
	if (process <= 0) {
		process++;
		return true;
	}
	return false;
}

void SimulationViewC3D::processEndCheck()
{
	if (process > 0) {
		process--;
	}
}

void SimulationViewC3D::prepareScene()
{
	glWidget->mainLight()->SetDoubleSided(true);
	glWidget->viewport()->SetBackgroundColour(Color(250, 250, 250, 50));

	QImage img(":/backgrounds/resources/bg.png");
	glWidget->viewport()->LoadBackgroundImage(ConvertToImage(img));

	SceneSegment* pTopSegment = glWidget->sceneContent()->GetRootSegment();
	Q_ASSERT(pTopSegment != nullptr);

	// 1 Cone
	::createShapeSegment(SceneGenerator::Instance()->CreateCone(1.5, 1.5), MbVector3D(0.0, 4.0, -1.5), Color(255, 0, 0), pTopSegment);
	// 2 Cylinder
	::createShapeSegment(SceneGenerator::Instance()->CreateCylinder(1.5, 1.5), MbVector3D(-5.0, 4.0, -1.5), Color(0, 190, 0), pTopSegment);
	// 3 Box
	::createShapeSegment(SceneGenerator::Instance()->CreateBox(2.5, 2.5, 2.5), MbVector3D(5.0, -4.0, 0.0), Color(0, 0, 180), pTopSegment);

	glWidget->sceneContent()->GetContainer()->SetUseVertexBufferObjects(true);
	glWidget->viewport()->ZoomToFit(glWidget->sceneContent()->GetBoundingBox());

	glWidget->move(QPoint(200, 200));
}

void SimulationViewC3D::checkLicense()
{
	QtVision::activateLicense();
}

#endif