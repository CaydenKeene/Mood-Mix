#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>
#include "DataAccess.h"
#include "tsl/htrie_map.h"



class SongManager : public QObject
{
    Q_OBJECT
public:
    explicit SongManager(QObject *parent = nullptr);

    Q_INVOKABLE void addSong(const QString &name, const QString &artist);
    Q_INVOKABLE void addSongs();
    Q_INVOKABLE QVariantList searchSongs(const QString &query);
    Q_INVOKABLE QVariantList mergeSort(QString name, QString songAttribute);
    Q_INVOKABLE void shellSort(QString name, QString songAttribute);
    Q_INVOKABLE QString _getMergeTime();
    Q_INVOKABLE QString _getShellTime();
    Q_INVOKABLE void spotify(QString trackID);

private:
    tsl::htrie_map<char, Song*> m_trie;
    QVector<std::shared_ptr<Song>> m_songs;
    DataAccess _data;
};

#endif // SONGMANAGER_H
