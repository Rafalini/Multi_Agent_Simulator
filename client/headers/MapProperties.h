#ifndef MAPPROPERTIES_H
#define MAPPROPERTIES_H

#include <QObject>
#include "City.h"
#include "Path.h"
#include "Point.h"

class MapProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<Path*> paths READ getPaths NOTIFY pathsChanged);
    Q_PROPERTY(QVector<City*> cities READ getCities NOTIFY citiesChanged);
    Q_PROPERTY(QVector<Point*> points READ getPoints NOTIFY pointsChanged);
public:
    MapProperties();
    QJsonObject toJson() const;
    virtual ~MapProperties();
    QVector<Path*> getPaths() const;
    QVector<Point*> getPoints() const;
    QVector<City*> getCities() const;
    void fill(const QJsonDocument& doc);
    void clear();
    Q_INVOKABLE void addCity(const QString& name, const double& x, const double& y, int id = -1);
    Q_INVOKABLE void addPoint(const double& x, const double& y, int id = -1);
    Q_INVOKABLE void addPath(Point* begining, Point* end, Path::RoadType type = Path::STANDARD, int id = -1);
    Q_INVOKABLE void removePoint(Point* point);
    Q_INVOKABLE void removeCity(City* city);
    Q_INVOKABLE void removePath(Path* path);
    Q_INVOKABLE void splitPath(Path* old_path, double x, double y);
    Q_INVOKABLE void promotePointToCity(Point*, QString name);
    Q_INVOKABLE Point* getPointById(int id);
    Q_INVOKABLE City* getCityByName(QString name);
    Q_INVOKABLE Path* getPathById(int id);
    Q_INVOKABLE void readFromJsonFile();
    Q_INVOKABLE void saveToJson();

signals:
    void duplicateCityName(QString);
    void pathsChanged();
    void citiesChanged();
    void pointsChanged();
    void pathAlreadyExist();
    void pathEndOnBegining();
    void aboutToClear();
    void fileFormatException();
    void readFromFileFinished();

private:
    QVector<City*> cities;
    QVector<Point*> points;
    QVector<Path*> paths;
    QString mapJson = "{\"cities\":[{\"id\":0,\"name\":\"Kraków\",\"x\":0.5663186661948019,\"y\":0.8255102040816326},{\"id\":1,\"name\":\"Warszawa\",\"x\":0.6719653179190753,\"y\":0.39884393063583834},{\"id\":2,\"name\":\"Szczecin\",\"x\":0.1,\"y\":0.12},{\"id\":3,\"name\":\"Białystok\",\"x\":0.8455284552845529,\"y\":0.2764227642276423},{\"id\":4,\"name\":\"Gdańsk\",\"x\":0.4476761125992762,\"y\":0.11035293011889657},{\"id\":5,\"name\":\"Bydgoszcz\",\"x\":0.4288617886178863,\"y\":0.22357723577235777},{\"id\":6,\"name\":\"Poznań\",\"x\":0.26016260162601634,\"y\":0.3556910569105693},{\"id\":7,\"name\":\"Wrocław\",\"x\":0.22201231260867552,\"y\":0.6401687109356643},{\"id\":8,\"name\":\"Zielona Góra\",\"x\":0.10772357723577239,\"y\":0.4268292682926829},{\"id\":9,\"name\":\"Gorzów Wielkopolski\",\"x\":0.12398373983739838,\"y\":0.2621951219512197},{\"id\":10,\"name\":\"Rzeszów\",\"x\":0.7624277456647398,\"y\":0.8653179190751445},{\"id\":11,\"name\":\"Katowice\",\"x\":0.4815028901734106,\"y\":0.769364161849711},{\"id\":12,\"name\":\"Łódź\",\"x\":0.5219653179190756,\"y\":0.44450867052023163},{\"id\":13,\"name\":\"Lublin\",\"x\":0.8213872832369947,\"y\":0.6514450867052026},{\"id\":14,\"name\":\"Opole\",\"x\":0.38786127167630075,\"y\":0.6919075144508671},{\"id\":15,\"name\":\"Kielce\",\"x\":0.648661082930282,\"y\":0.6851283866147615},{\"id\":16,\"name\":\"Olsztyn\",\"x\":0.6271676300578036,\"y\":0.17283236994219653}],\"paths\":[{\"begining\":4,\"end\":5,\"id\":0,\"type\":1},{\"begining\":1,\"end\":12,\"id\":1,\"type\":2},{\"begining\":9,\"end\":2,\"id\":3,\"type\":1},{\"begining\":6,\"end\":18,\"id\":4,\"type\":0},{\"begining\":17,\"end\":2,\"id\":6,\"type\":2},{\"begining\":17,\"end\":18,\"id\":7,\"type\":0},{\"begining\":18,\"end\":5,\"id\":8,\"type\":0},{\"begining\":18,\"end\":2,\"id\":9,\"type\":0},{\"begining\":16,\"end\":19,\"id\":10,\"type\":0},{\"begining\":19,\"end\":3,\"id\":11,\"type\":0},{\"begining\":16,\"end\":4,\"id\":12,\"type\":1},{\"begining\":3,\"end\":20,\"id\":14,\"type\":0},{\"begining\":20,\"end\":13,\"id\":15,\"type\":0},{\"begining\":20,\"end\":1,\"id\":16,\"type\":0},{\"begining\":13,\"end\":10,\"id\":17,\"type\":1},{\"begining\":12,\"end\":11,\"id\":18,\"type\":0},{\"begining\":1,\"end\":21,\"id\":19,\"type\":2},{\"begining\":21,\"end\":15,\"id\":20,\"type\":2},{\"begining\":15,\"end\":0,\"id\":22,\"type\":2},{\"begining\":0,\"end\":11,\"id\":23,\"type\":2},{\"begining\":0,\"end\":10,\"id\":24,\"type\":0},{\"begining\":11,\"end\":14,\"id\":25,\"type\":2},{\"begining\":14,\"end\":7,\"id\":26,\"type\":2},{\"begining\":22,\"end\":6,\"id\":29,\"type\":1},{\"begining\":22,\"end\":9,\"id\":30,\"type\":1},{\"begining\":22,\"end\":8,\"id\":31,\"type\":0},{\"begining\":16,\"end\":23,\"id\":32,\"type\":0},{\"begining\":23,\"end\":1,\"id\":33,\"type\":0},{\"begining\":23,\"end\":24,\"id\":34,\"type\":0},{\"begining\":24,\"end\":5,\"id\":35,\"type\":0},{\"begining\":24,\"end\":12,\"id\":36,\"type\":2},{\"begining\":25,\"end\":7,\"id\":38,\"type\":0},{\"begining\":25,\"end\":11,\"id\":39,\"type\":0},{\"begining\":21,\"end\":13,\"id\":40,\"type\":0},{\"begining\":1,\"end\":13,\"id\":41,\"type\":1},{\"begining\":26,\"end\":15,\"id\":42,\"type\":0},{\"begining\":26,\"end\":12,\"id\":43,\"type\":0},{\"begining\":27,\"end\":15,\"id\":44,\"type\":0},{\"begining\":28,\"end\":27,\"id\":45,\"type\":0},{\"begining\":11,\"end\":28,\"id\":46,\"type\":0},{\"begining\":29,\"end\":27,\"id\":47,\"type\":0},{\"begining\":29,\"end\":11,\"id\":48,\"type\":0},{\"begining\":7,\"end\":30,\"id\":49,\"type\":0},{\"begining\":31,\"end\":30,\"id\":51,\"type\":0},{\"begining\":31,\"end\":32,\"id\":52,\"type\":0},{\"begining\":32,\"end\":7,\"id\":53,\"type\":0},{\"begining\":22,\"end\":33,\"id\":54,\"type\":0},{\"begining\":30,\"end\":34,\"id\":55,\"type\":0},{\"begining\":34,\"end\":8,\"id\":56,\"type\":0},{\"begining\":7,\"end\":35,\"id\":57,\"type\":2},{\"begining\":35,\"end\":6,\"id\":58,\"type\":2},{\"begining\":6,\"end\":36,\"id\":59,\"type\":0},{\"begining\":36,\"end\":25,\"id\":60,\"type\":1},{\"begining\":25,\"end\":37,\"id\":61,\"type\":1},{\"begining\":37,\"end\":12,\"id\":62,\"type\":1},{\"begining\":38,\"end\":23,\"id\":63,\"type\":0},{\"begining\":38,\"end\":3,\"id\":64,\"type\":0},{\"begining\":39,\"end\":1,\"id\":66,\"type\":1},{\"begining\":39,\"end\":38,\"id\":67,\"type\":0},{\"begining\":3,\"end\":40,\"id\":68,\"type\":1},{\"begining\":40,\"end\":39,\"id\":69,\"type\":1},{\"begining\":16,\"end\":5,\"id\":70,\"type\":0},{\"begining\":12,\"end\":41,\"id\":71,\"type\":2},{\"begining\":41,\"end\":6,\"id\":72,\"type\":2},{\"begining\":41,\"end\":5,\"id\":73,\"type\":1},{\"begining\":4,\"end\":42,\"id\":74,\"type\":2},{\"begining\":42,\"end\":17,\"id\":75,\"type\":2},{\"begining\":17,\"end\":43,\"id\":76,\"type\":0},{\"begining\":43,\"end\":4,\"id\":77,\"type\":0},{\"begining\":21,\"end\":44,\"id\":78,\"type\":0},{\"begining\":44,\"end\":10,\"id\":79,\"type\":0},{\"begining\":44,\"end\":15,\"id\":80,\"type\":0},{\"begining\":27,\"end\":12,\"id\":81,\"type\":0}],\"points\":[{\"id\":17,\"x\":0.25028901734104053,\"y\":0.09884393063583821},{\"id\":18,\"x\":0.26878612716763006,\"y\":0.20751445086705206},{\"id\":19,\"x\":0.7947976878612719,\"y\":0.18901734104046244},{\"id\":20,\"x\":0.8456647398843933,\"y\":0.4364161849710984},{\"id\":21,\"x\":0.7070595478406392,\"y\":0.545292876125849},{\"id\":22,\"x\":0.13005780346820808,\"y\":0.35317919075144505},{\"id\":23,\"x\":0.6520605450074927,\"y\":0.3308768804446},{\"id\":24,\"x\":0.5068613642481179,\"y\":0.2909729084569247},{\"id\":25,\"x\":0.3719888155,\"y\":0.54233869072},{\"id\":26,\"x\":0.6300309597523222,\"y\":0.4989680082559337},{\"id\":27,\"x\":0.5670794633642932,\"y\":0.609391124871001},{\"id\":28,\"x\":0.5764137233840906,\"y\":0.7118868600071612},{\"id\":29,\"x\":0.5278637770897833,\"y\":0.7063983488132098},{\"id\":30,\"x\":0.14028865199689747,\"y\":0.5791974253998805},{\"id\":31,\"x\":0.06326530612244895,\"y\":0.5965986394557823},{\"id\":32,\"x\":0.15578231292517003,\"y\":0.6551020408163265},{\"id\":33,\"x\":0.0619047619047619,\"y\":0.36122448979591837},{\"id\":34,\"x\":0.16172724996499083,\"y\":0.507299224788493},{\"id\":35,\"x\":0.19675371144141898,\"y\":0.48877504354163115},{\"id\":36,\"x\":0.3176870748299319,\"y\":0.44557823129251695},{\"id\":37,\"x\":0.42035263962429487,\"y\":0.48256601416774264},{\"id\":38,\"x\":0.7013605442176868,\"y\":0.2591836734693877},{\"id\":39,\"x\":0.7398830518789984,\"y\":0.34959651886065113},{\"id\":40,\"x\":0.7925827472713735,\"y\":0.31166652752327445},{\"id\":41,\"x\":0.33334556744070504,\"y\":0.3793407964471879},{\"id\":42,\"x\":0.32843795066016945,\"y\":0.040911763057118716},{\"id\":43,\"x\":0.32312925170068024,\"y\":0.11904761904761904},{\"id\":44,\"x\":0.7647674831161191,\"y\":0.7295557537971874}]}";
};

#endif // MAPPROPERTIES_H
