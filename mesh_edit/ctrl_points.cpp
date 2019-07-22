#include "ctrl_points.h"
#include <QColor>

ctrl_points::ctrl_points( Qt3DCore::QEntity* parent) : Qt3DCore::QEntity(parent)
{
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial;
    material->setDiffuse(QColor(255,0,0));
    material->setShininess(0);
    material->setSpecular(QColor(255,0,0));
    Qt3DExtras::QSphereMesh *ctrl_pt = new Qt3DExtras::QSphereMesh;
    ctrl_pt->setRadius(_radius);

    Qt3DRender::QPickingSettings *settings = new Qt3DRender::QPickingSettings(this);
    //settings->setFaceOrientationPickingMode(Qt3DRender::QPickingSettings::FrontFace);
    settings->setPickMethod(Qt3DRender::QPickingSettings::TrianglePicking);
    //settings->setPickResultMode(Qt3DRender::QPickingSettings::NearestPick);

    for(int x = 0; x < _pts_x; x++)
    for(int y = 0; y < _pts_y; y++)
    for(int z = 0; z < _pts_z; z++) {
        Qt3DCore::QTransform *pos = new Qt3DCore::QTransform;
        glm::vec3 t = glm::vec3(static_cast<float>(x) / (_pts_x-1),
                                static_cast<float>(y) / (_pts_y-1),
                                static_cast<float>(z) / (_pts_z-1)
                                );
        pos->setTranslation({ t.x, t.y, t.z });

        auto entity = new Qt3DCore::QEntity(this);

        Qt3DRender::QObjectPicker *picker = new Qt3DRender::QObjectPicker(entity);
        QObject::connect(picker, &Qt3DRender::QObjectPicker::clicked, this, [=](Qt3DRender::QPickEvent *event){sl_entityPressed(event, entity);} );

        entity->addComponent(picker);
        entity->addComponent(material);
        entity->addComponent(ctrl_pt);
        entity->addComponent(pos);

        _CtrlPtIDs[entity] = {x,y,z};
        _CtrlPtPos[entity] = t;
    }
}

ctrl_points::~ctrl_points() {}

void ctrl_points::sl_resetCtrlPoints() {
    for(auto &p : _CtrlPtPos) {
        auto point = p.first;
        auto pos = p.second;

        for (auto *component : point->components()) {
            Qt3DCore::QTransform *trafo = dynamic_cast<Qt3DCore::QTransform *>(component);
            if(trafo) {
                trafo->setTranslation(QVector3D(pos[0], pos[1], pos[2]));
            }
        }
    }
}

void ctrl_points::sl_entityPressed(Qt3DRender::QPickEvent *event, Qt3DCore::QEntity *entity) {
    for (auto *component : entity->components()) {
        Qt3DCore::QTransform *trafo = dynamic_cast<Qt3DCore::QTransform *>(component);
        if(trafo) {
            auto transl = trafo->translation();
            emit entityPressed(entity, QVector3D(transl.x(), transl.y(), transl.z()), event->position());
        }
    }
}

void ctrl_points::sl_changePosition(Qt3DCore::QEntity *ctrl_point, QVector3D position) {
    for (auto *component : ctrl_point->components()) {
        Qt3DCore::QTransform *trafo = dynamic_cast<Qt3DCore::QTransform *>(component);
        if(trafo) {
            trafo->setTranslation(position);
            emit positionChanged();
        }
    }
}
