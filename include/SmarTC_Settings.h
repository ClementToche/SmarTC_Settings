#ifndef SMARTC_SETTINGS_H
#define SMARTC_SETTINGS_H

class SmarTC_Settings
{
public:
    SmarTC_Settings();
    ~SmarTC_Settings();

    bool init();
    void printFilesList();

    char *wifiSsid();
    char *wifiPwd();
    char *mqttSrv();
    int mqttPort();
    char *mqttUser();
    char *mqttPwd();
    int otaPort();
    char* otaPwd();
    char *boardName();

private:
    char *getParam(const char *type);
};

#endif //SMARTC_SETTINGS_H
