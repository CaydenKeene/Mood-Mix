#include "songmanager.h"

SongManager::SongManager(QObject *parent)
    : QObject{parent}
{
    addSong("Song 1", "Artist 1");
    addSong("Song 2", "Artist 2");
    addSong("Song 3", "Artist 3");
    addSong("Song 4", "Artist 4");
    addSong("Song 5", "Artist 5");
    addSong("Song 6", "Artist 6");
    addSong("Song 7", "Artist 7");
    addSong("Song 8", "Artist 8");

}

void SongManager::addSong(const QString &name, const QString &artist) {
    //creates and instance of the song struct and sets the name and the artist
    auto song = std::make_shared<Song>(Song{name, artist});
    //m_songs.append(song);

    std::string nameStd = name.toLower().toStdString();
    //qDebug() << "Inserting song:" << QString::fromStdString(nameStd) << "by" << artist;
    m_trie.insert(nameStd.c_str(), song);
}

QVariantList SongManager::searchSongs(const QString &query) {
    QVariantList results;
    int count = 0;

    std::string queryStd = query.toLower().toStdString();

    auto range = m_trie.equal_prefix_range(queryStd);
    for (auto it = range.first; it != range.second && count < 5; ++it) {
        QVariantMap songMap;
        songMap["name"] = it.value()->name;
        songMap["artist"] = it.value()->artist;
        results.append(songMap);
        count++;
    }

    return results;
}
