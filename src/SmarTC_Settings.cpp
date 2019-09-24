#include <FS.h>
#include <SmarTC_Settings.h>

/************************ Public Functions ************************/
SmarTC_Settings::SmarTC_Settings()
{
}
SmarTC_Settings::~SmarTC_Settings()
{
}

bool SmarTC_Settings::init()
{
    return SPIFFS.begin();
}

void SmarTC_Settings::printFilesList()
{
    Dir dir = SPIFFS.openDir("");
    while (dir.next())
    {
        Serial.print(F("File "));
        Serial.print(dir.fileName());
        Serial.print(F(" | Size "));
        File f = dir.openFile("r");
        Serial.println(f.size());
    }
}

char *SmarTC_Settings::wifiSsid()
{
    return getParam("/wifi_ssid.txt");
}

char *SmarTC_Settings::wifiPwd()
{
    return getParam("/wifi_pwd.txt");
}

char *SmarTC_Settings::mqttSrv()
{
    return getParam("/mqtt_server.txt");
}

int SmarTC_Settings::mqttPort()
{
    char *number = getParam("/mqtt_port.txt");
    int port = (int)strtol(number, NULL, 10);
    free(number);
    return port;
}

char *SmarTC_Settings::mqttUser()
{
    return getParam("/mqtt_user.txt");
}

char *SmarTC_Settings::mqttPwd()
{
    return getParam("/mqtt_pwd.txt");
}

int SmarTC_Settings::otaPort()
{
    char *number = getParam("/ota_port.txt");
    int port = (int)strtol(number, NULL, 10);
    free(number);
    return port;
}

char *SmarTC_Settings::otaPwd()
{
    return getParam("/ota_pwd.txt");
}

char *SmarTC_Settings::boardName()
{
    return getParam("/mqtt_name.txt");
}

/************************ Private Functions ************************/

//TODO: Comment warning to dealocate memory if return value not used
char *SmarTC_Settings::getParam(const char *type)
{
    File f = SPIFFS.open(type, "r");
    if (!f)
    {
        Serial.print(type);
        Serial.println(" file open failed");
        return NULL;
    }

    String data = f.readString();
    Serial.print(type);
    Serial.print(" : ");
    Serial.println(data);

    int size = data.length() + 1;
    if (1 > size)
    {
        Serial.print(type);
        Serial.println(" name is zero size");
        return NULL;
    }

    char *ret_value = (char *)calloc(1, size);
    data.toCharArray(ret_value, size);

    f.close();

    return ret_value;
}