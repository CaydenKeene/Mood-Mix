#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QCoreApplication>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <QObject>
#include <cmath>
#include <QVariant>
#include <QVector>
#include <chrono>
#include <QDesktopServices>
#include <QUrl>


struct Song
{
    QString _trackName;
    QString _trackID;
    QString _artist;
    float _danceability;
    float _energy;
    float _loudness;
    float _valence;
    float _tempo;
    int _popularity;
    QString _genre;
    bool _explicit;
};

enum SongAttributes
{
    danceability, energy, loudness, valence, tempo
};

class DataAccess : public QObject
{
private:
    std::unordered_map<QString, QVector<Song*>> _genreCollection;
    QVector<Song*> _allSongs;
    QVector<Song*> _mergeSorted;
    QVector<QPair<Song*, float>> _shellSorted;

    //measuring time
    double mergeTime;
    double shellTime;

    // For getting data from csv
    std::string GetColumnData(std::istringstream& dataStream);

    // For merge sort
    void merge(QVector<Song*>& songList, SongAttributes& songAttribute, int left, int mid, int right, const float &attributeVal);
    void mergeSort(QVector<Song*>& songList, SongAttributes& songAttribute, int left, int right, const float& attributeVal);

    Q_OBJECT
public:
    explicit DataAccess(QObject *parent = nullptr);
    DataAccess(std::string fileName);
    ~DataAccess();

    // For getting data from csv
    Q_INVOKABLE void LoadData(std::string fileName);

    Q_INVOKABLE QVector<Song*>& GetSongsByGenre(QString& genreName);
    Q_INVOKABLE QVector<Song*>& GetAllSongs();

    // For merge sort
    //QVector<Song*> SortByMergeSort(Song* song, SongAttributes songAttribute);
    QVariantList sortByMergeSort(QString &name, QString &attribute);

    // shell sort
    void sortByShellSort(QString &name, QString &attribute);

    //getting time
    QString getMergeTime();
    QString getShellTime();

    void openInSpotify(QString& trackID);
};

#endif // DATAACCESS_H
