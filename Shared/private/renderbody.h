#ifndef RENDERBODY_H
#define RENDERBODY_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QImage>
#include <QDebug>


#include "body.h"
#include "shared_global.h"

/**
 * @brief The RenderBody class Body class that will be rendered on screen, client-side
 */
class SHAREDSHARED_EXPORT RenderBody : public Body
{
public:
    /**
     * @brief RenderBody Initialize a RenderBody without an asset. This can be dangerous.
     */
    RenderBody();

    /**
     * @brief RenderBody Initialize a RenderBody with the given asset
     */
    RenderBody(QString assetPath);

    /**
     * @brief createGraphic Create the QGraphicsPixmapItem with the mask applied
     * @return True if the graphic was created successfully, false otherwise
     */
    bool createGraphic();

    /**
     * @brief tick Update RenderBody specific things
     */
    void tick(double);

    /**
     * @brief getGraphicsItem Get the Body's QGraphicsItem for adding to the QGraphicsScene
     * @return
     */
    QGraphicsPixmapItem* getGraphicsItem();

    /**
     * @brief setAssetPath Set the asset path
     * @param path
     */
    void setAssetPath(QString assetPath);

    /**
     * @brief getAssetPath
     * @return
     */
    QString getAssetPath();

    /**
     * @brief read Read in from the given JSON object
     * @param json
     */
    void read(const QJsonObject &json);

    /**
     * @brief write Write to the given JSON object
     * @param json
     */
    void write(QJsonObject &json) const;

private:
    /**
     * @brief applyMask Randomly generate the colors from the mask
     * @param image
     * @param mask
     */
    void applyMask(QImage* image, QImage* mask);

    // QResource path
    QString assetPath;

    // GraphicsItem to be loaded into the QGraphicsScene
    QGraphicsPixmapItem *spriteGraphicsItem;

    // Asset Resource File Paths
    const static QString imagePath;
    const static QString maskPath;
};

#endif // RENDERBODY_H
