#pragma once

#include "../stl/stl_import.h"

#include <QGeometryRenderer>
#include <QVector3D>
#include <glm/glm.hpp>

class QNode;
class QUrl;
class ctrl_points;

class stl_mesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT

private:
    std::vector<stl::face> _ffd_mesh;

public:
    stl_mesh(QNode *parent = nullptr);

public slots:
    void sl_load(const QUrl &filename);
    void sl_performFFD(ctrl_points *);
};
