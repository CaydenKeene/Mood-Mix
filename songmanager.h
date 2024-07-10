#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QVariant>
#include <tsl/htrie_map.h>

struct Song {
    QString name;
    QString artist;
};

class SongManager : public QObject
{
    Q_OBJECT
public:
    explicit SongManager(QObject *parent = nullptr);

    Q_INVOKABLE void addSong(const QString &name, const QString &artist);
    Q_INVOKABLE QVariantList searchSongs(const QString &query);

private:
    QVector<std::shared_ptr<Song>> m_songs;
    tsl::htrie_map<char, std::shared_ptr<Song>> m_trie;
};

#endif // SONGMANAGER_H
