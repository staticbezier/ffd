#pragma once

#include <Qt3DRender/QGeometry>
#include <vector>
#include <memory>
#include "../stl/stl_import.h"


class QNode;
namespace Qt3DRender {
class QBuffer;
};

class stl_mesh_geom : public Qt3DRender::QGeometry
{
    Q_OBJECT
    Q_PROPERTY(Qt3DRender::QAttribute *positionAttribute READ positionAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *normalAttribute READ normalAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *indexAttribute READ indexAttribute CONSTANT)

private:
    void init(const std::vector<stl::face> &);

    std::vector<stl::face> _stl_data;
    glm::vec3 _dim;

    std::shared_ptr<Qt3DRender::QAttribute> m_positionAttribute = nullptr;
    std::shared_ptr<Qt3DRender::QAttribute> m_normalAttribute = nullptr;
    std::shared_ptr<Qt3DRender::QAttribute> m_indexAttribute = nullptr;

    std::shared_ptr<Qt3DRender::QBuffer> m_vertexBuffer = nullptr;
    std::shared_ptr<Qt3DRender::QBuffer> m_indexBuffer = nullptr;

public:
    stl_mesh_geom(QNode *parent = nullptr);

    void load(const QUrl &filename);
    void refresh(const std::vector<stl::face> &);

    glm::vec3 getDim() const {return _dim;}
    const std::vector<stl::face> &faces() const { return _stl_data; }

    Qt3DRender::QAttribute *positionAttribute() const;
    Qt3DRender::QAttribute *normalAttribute() const;
    Qt3DRender::QAttribute *indexAttribute() const;
};

