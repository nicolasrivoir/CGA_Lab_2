// Settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

enum ShadingType {
    INTERPOLATED,  // 0
    FACETED,      // 1
};

class Settings {
public:
    Settings();
    void setGameSpeed(float speed);
    bool wireframeActivated;
    bool texturesActivated;
    ShadingType shadingType;

//  void chageLight(Vec3 color, Vec3 direction);
    void chageLight(double color, double direction);

};

#endif // SETTINGS_H
#pragma once
