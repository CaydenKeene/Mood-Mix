#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QCoreApplication>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <QObject>


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


class DataAccess : public QObject
{
private:
    std::unordered_map<QString, QVector<Song*>> _genreCollection;
    QVector<Song*> _allSongs;

    std::string GetColumnData(std::istringstream& dataStream);
    Q_OBJECT
public:
    explicit DataAccess(QObject *parent = nullptr);
    DataAccess(std::string fileName);
    ~DataAccess();

    Q_INVOKABLE void LoadData(std::string fileName);

    Q_INVOKABLE QVector<Song*>& GetSongsByGenre(QString& genreName);
    Q_INVOKABLE QVector<Song*>& GetAllSongs();
};

#endif // DATAACCESS_H
