void Theo::precomputeSpace(){
    this->setCursor(Qt::WaitCursor);
    // calculate the range and bearing from each pixel in image to location of camera.
    //     OR  calculate the UTMx and UTMy of each pont i image -- then calculate range and bearing later
    int Ny = ui->CCD_y->value();
    int Nx = ui->CCD_x->value();
    initializeGlobals();
    calculateCameraBearingAz();

    VecDoub Y(Ny);
    MatDoub X(Nx, Ny);
    bool gotOne = false;
    qDebug()<<ui->tiltCam->value();
    for (int j=0; j<Ny; j++){
        double theta_Target = ui->tiltCam->value()*DEG2RAD + ((float)j-0.5*ui->CCD_y->value())*m_radPerPixel;
        double range = m_xyH[2][0]/tan(theta_Target);
//        if (range > 15000){
//            qDebug()<<" j= "<<j<<"theta_Target_"<<theta_Target*RAD2DEG<<"range="<<range;
//            gotOne = true;
//        }
        Y[j] = range;
        if ((range < 0) || (range > 18000)) Y[j] = -9999;   // Note Bene Do we need this max range limit?????
    }
    gotOne = false;
    for (int j=0;j<Ny;j++){
        for (int i=0;i<(int)(Nx/2);i++){
            double f = ((float)Nx/2.0 - (float)i)*2.0/(float)Nx;
            X[i][j] = -f*Y[j]*sin(ui->fov_X->value()*DEG2RAD/2.0);
            X[Nx-i-1][j] = - X[i][j];  // camera axis splits the ccd and hence level camera is symmetric in locations relative to the center of the ccd
//            if ((i==0) && (j>1140))
//                qDebug()<<i<<j<<X[i][j]<<Y[j]<<  sin(ui->fov_X->value()/2.0);
//            if (!gotOne && (j>Ny/2) && i % 100 == 0){
//                qDebug()<<"ui->fov_X->value()/2.0"<<ui->fov_X->value()/2.0<<"f"<<f<<"j"<<j<<"range"<<Y[j]<<i<<"dist off axis"<<X[i][j]<<"Nx-i-1"<<Nx-i-1<<X[Nx-i-1][j];
//                gotOne = true;
//            }
        }
    }

// now transform into utm coordinates
    // X and Y are relative to camera with Y pointing away and X to the right
    // Rotate about vertical axis at the point where lens axis strikes the sea
    double azCam = ui->AzCam->value()*DEG2RAD;
    m_UTMx_Img.resize(Nx,Ny);
    m_UTMy_Img.resize(Nx,Ny);
    m_UTMx_ContourIdx.resize(Nx,Ny);
    m_UTMy_ContourIdx.resize(Nx,Ny);
    double UTMxAxis; double UTMyAxis;
    double RtoAxis = m_xyH[2][0]/tan(ui->tiltCam->value()*DEG2RAD);  // ht of camera / tan elevation

    UTMxAxis = ui->xCamera->value()+RtoAxis*sin(azCam);
    UTMyAxis = ui->yCamera->value()+RtoAxis*cos(azCam);
    qDebug()<<"RtoAxis"<<RtoAxis<<"UTMxAxis"<<UTMxAxis<<"UTMyAxis"<<UTMyAxis<<"sin(azCam)"<<sin(azCam)<<"cos(azCam)"<<cos(azCam);
    int cnt = 0;
    double maxUTMx = 0; double minUTMx = 9e9;
    double maxUTMy = 0; double minUTMy = 9e9;
    int axisIdx_x; int axisIdx_y;
    double minDist = 9e9;
    for (int j=0; j<Ny; j++){
        for (int i=0; i<Nx; i++){
            if (Y[j]==-9999 || X[i][j]==-9999){
                m_UTMx_Img[i][j] = m_UTMy_Img[i][j] = -9999;  // no UTM coordinates at this image location
            } else {
                double utmx = UTMxAxis + (X[i][j]*cos(azCam) + (Y[j]-RtoAxis)*sin(azCam));
                double utmy = UTMyAxis + (-X[i][j]*sin(azCam) + (Y[j]-RtoAxis)*cos(azCam));
                double dist = SQR(utmx - UTMxAxis) + SQR(utmy - UTMyAxis);
                if (dist < minDist){
                    minDist = dist;
                    axisIdx_x = i;
                    axisIdx_y = j;
                }
                m_UTMx_Img[i][j] = utmx;
                m_UTMy_Img[i][j] = utmy;
                maxUTMx = max(maxUTMx,utmx);
                maxUTMy = max(maxUTMy,utmy);
                minUTMx = min(minUTMx,utmx);
                minUTMy = min(minUTMy,utmy);
            }
        }
    }


    int Ncontours = 5;
    m_utmXline_px_x.resize(2,Ncontours);
    m_utmXline_px_y.resize(2,Ncontours);
    m_utmYline_px_x.resize(2,Ncontours);
    m_utmYline_px_y.resize(2,Ncontours);

    VecDoub xLineUTMs(Ncontours);
    VecDoub yLineUTMs(Ncontours);

    // axisIdx_y is y axis pixel value of point where camera axis penetrates z=0 plane

    // chose Ncontours points in image's vertical direction for utmx and utmy isolines
    int yHorizon = 0;
    while (((m_UTMx_Img[axisIdx_x][yHorizon] == -9999) && (m_UTMy_Img[axisIdx_y][yHorizon] == -9999)) && (yHorizon < ui->CCD_y->value())){
        yHorizon++;
    }
    int deltay = (axisIdx_y - yHorizon)/(Ncontours-1);
    int deltaX = 100;  // step this much  to the side to find other point on UTM isoline
    int i1; int j1;int i2;int j2;
    for (int k=0; k<Ncontours;k++){
        int x = axisIdx_x;
        int y = yHorizon + deltay*0.25 + deltay*(k);
        // step sideways and find points that match the current location's utms
        int IdxY;
        int thisStep;
        IdxY = getIdxMatchingUTM(m_UTMx_Img, yHorizon, axisIdx_x,  deltaX, thisStep, m_UTMx_Img[x][y]);
        extrap(m_UTMx_Img,x,y,x+thisStep,IdxY,i1,j1,i2,j2);
        m_utmXline_px_x[0][k] = i1;
        m_utmXline_px_y[0][k] = j1;
        m_utmXline_px_x[1][k] = i2;
        m_utmXline_px_y[1][k] = j2;

        IdxY = getIdxMatchingUTM(m_UTMy_Img, yHorizon, axisIdx_x, deltaX, thisStep, m_UTMy_Img[x][y]);
        extrap(m_UTMy_Img,x,y,x+thisStep,IdxY,i1,j1,i2,j2);
        m_utmYline_px_x[0][k] = i1;
        m_utmYline_px_y[0][k] = j1;
        m_utmYline_px_x[1][k] = i2;
        m_utmYline_px_y[1][k] = j2;

    }


    QString fullPathFile = ui->photoFolder->text()+ui->photoFilename->text();
    bool drawLines = false;
    if (ui->parm->value() == 10) drawLines = true;
    loadTheImage(fullPathFile,true,drawLines);  // true here says rescaleToView
    this->setCursor(Qt::ArrowCursor);
    m_needPrecompute = false;
}
