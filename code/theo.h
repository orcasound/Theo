#ifndef THEO_H
#define THEO_H

#include <QMainWindow>         //  version 0.9 dated Sept. 8, 2020
#include <QPixmap>
#include <QKeyEvent>
#include "mygraphicsscene.h"
#include <QGraphicsScene>
#include <QPoint>
#include <QList>
#include <QKeyEvent>
#include <QSettings>
#include <QCloseEvent>
#include <QImage>

#include "nr3.h"

namespace Ui {
class Theo;
}

class Theo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Theo(QWidget *parent = 0);
    ~Theo();

private:
    Ui::Theo *ui;
    QPixmap g_pixmap;
    myGraphicsScene * theoScene;
    QPixmap g_pixmap_thm;
    myGraphicsScene * thmScene;
    int m_keyPressed;
    void processClick(int key, double x, double y);
    VecDoub PIXxFiducial;
    VecDoub PIXyFiducial;
    int m_targetCnt;

    void lookupInSpace(double x, double y);
    double getBearingFromLatLong(int i);

    void lookupUTMs(int i, int j);
    void extrap(MatDoub utms, int idx1, int idy1, int idx2, int idy2, int &i1, int &j1, int &i2, int &j2);

    void calculateRadPerPixel();
    void calculateUTMsFlat(double x, double y);
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent * event);
    QStringList m_imageFileList;
    int m_thisImageIdx;
    void openImageFile(bool rescaleToView);
    QImage m_img;
    void loadTheImage(QString theFile, bool rescaleToView, bool drawContours);
    MatInt m_utmXline_px_x;
    MatInt m_utmXline_px_y;
    MatInt m_utmYline_px_x;
    MatInt m_utmYline_px_y;
    int m_graphicsViewWidth;
    void compressTargetItems(int idx);

    void getRangeAndBearingDeltaXY(double x, double y, double &range, double &bearing, double &xTarget, double &yTarget);
    double calcEpsilon(VecDoub R0, double FOVy, double CCDy);
    double calcCameraAz(double FOVx, double CCDx);

    bool m_firstImage;
    MatDoub m_LatLongH;
    MatDoub m_xyH;
    MatDoub m_xyScene;
    MatDoub m_LatLonScene;

    MatDoub m_R;
    MatDoub m_Phi;
    MatDoub m_UTMx;
    MatDoub m_UTMy;

    MatDoub m_UTMx_Img;   // indices here are m_UTMx_Img[pixel_x][pixel_y] is the UTMx of this point in the image
    MatDoub m_UTMy_Img;
    MatInt  m_UTMx_ContourIdx;
    MatInt  m_UTMy_ContourIdx;

    VecDoub m_fidRange;   // range from camera to each of the four fiducials
    VecDoub m_fidElevation;  // elevation from fiducial to camera
    double m_radPerPixel;
    VecDoub m_fidBearing;
    double m_CCDyMidFrac;

    double m_tilt_cam;
    double m_azimuth_cam;
    double m_ccd_x;
    double m_ccd_y;
    double m_fov_x;
    double m_fov_y;

    void initializeGlobals();
    void calculateCameraBearingAz();
    double calcCameraAzLatLon();

    QString m_photoFilename[7];
    QString m_photoDate[7];
    QString m_locFilename[7];
    bool m_needPrecompute;
    bool m_needDigitizeFids;
    bool m_calibrated;
    bool m_displayUTM;

    int getExifData(QString filename);

private slots:
    void loadPhoto();
    void gotMouseSelection(QList<double> coords);
    void advanceOneImage();
    void retreatOneImage();
    void clear_1();void clear_2();void clear_3();void clear_4();void clear_5();void clear_6();void clear_7();
    void saveData();
    void setSaveDir();
    void changeCoord_UTM();
    void changeCoord_LatLong();
    void calculateLatLonFromUTMs();
    void showHelp();
    void readLocations();
    void precomputeSpace();


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);

};

#endif // THEO_H
