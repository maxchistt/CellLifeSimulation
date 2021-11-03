#pragma once

#include <QWidget>
#include "ui_GenerationSettingsWidget.h"

class GenerationSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	GenerationSettingsWidget(QWidget *parent = Q_NULLPTR);
	~GenerationSettingsWidget();

private:
	Ui::GenerationSettingsWidget ui;
};
