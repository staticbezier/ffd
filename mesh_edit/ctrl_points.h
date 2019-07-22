#pragma once

#include <glm/glm.hpp>
#include <array>
#include <map>

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DLogic>
#include <Qt3DExtras>
#include <Qt3DAnimation>
#include <QVector3D>


class ctrl_points : public Qt3DCore::QEntity {
    Q_OBJECT
    Q_PROPERTY(int x_points READ xPoints WRITE setXPoints NOTIFY xPointsChanged)
    Q_PROPERTY(int y_points READ yPoints WRITE setYPoints NOTIFY yPointsChanged)
    Q_PROPERTY(int z_points READ zPoints WRITE setZPoints NOTIFY zPointsChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

    float _radius = 0.025f;
    int _pts_x = 3;
    int _pts_y = 3;
    int _pts_z = 3;

    std::map<Qt3DCore::QEntity *, std::array<int, 3>> _CtrlPtIDs;
    std::map<Qt3DCore::QEntity *, glm::vec3> _CtrlPtPos;

public:
    ctrl_points(Qt3DCore::QEntity* parent = nullptr);
    virtual ~ctrl_points();

    std::map<Qt3DCore::QEntity *, std::array<int, 3>> getCtrlIDs() { return _CtrlPtIDs; }

    float radius() const { return _radius; }
    int xPoints() const { return _pts_x; }
    int yPoints() const { return _pts_y; }
    int zPoints() const { return _pts_z; }

    void setRadius(float val) { if(val > 0) _radius = val; emit radiusChanged(); }
    void setXPoints(int x) { _pts_x = x; emit xPointsChanged(); }
    void setYPoints(int y) { _pts_y = y; emit yPointsChanged(); }
    void setZPoints(int z) { _pts_z = z; emit zPointsChanged(); }

public slots:
    void sl_resetCtrlPoints();
    void sl_entityPressed(Qt3DRender::QPickEvent *, Qt3DCore::QEntity *entity);
    void sl_changePosition(Qt3DCore::QEntity *ctrl_point, QVector3D position);

signals:
    void entityPressed(Qt3DCore::QEntity *ctrl_point, QVector3D entity_position, QPointF mouse_position);
    void positionChanged();

    void radiusChanged();
    void xPointsChanged();
    void yPointsChanged();
    void zPointsChanged();
};

