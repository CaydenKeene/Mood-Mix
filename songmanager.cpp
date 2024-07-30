#include "songmanager.h"

SongManager::SongManager(QObject *parent)
    : QObject{parent}
{
    _data.LoadData("dataset.csv");
    addSongs();

    // TODO: Remove these two lines
    // This is how I tested the merge sort
    //SongAttributes testSong = danceability;
    //_data.SortByMergeSort(_data.GetAllSongs().front(), testSong);
}

void SongManager::addSongs()
{
    for(auto _song : _data.GetAllSongs())
    {
        m_trie.insert(_song->_trackName.toLower().toStdString(), _song);
    }
}

void SongManager::addSong(const QString &name, const QString &artist)
{
    //creates and instance of the song struct and sets the name and the artist
    //auto song = std::make_shared<Song>(Song{name, artist});
    //m_songs.append(song);

    //std::string nameStd = name.toLower().toStdString();
    //qDebug() << "Inserting song:" << QString::fromStdString(nameStd) << "by" << artist;
   // m_trie.insert(nameStd.c_str(), song);
}

QVariantList SongManager::searchSongs(const QString &query)
{
    QVariantList results;
    int count = 0;

    std::string queryStd = query.toLower().toStdString();

    auto range = m_trie.equal_prefix_range(queryStd);
    for (auto it = range.first; it != range.second && count < 5; ++it) {
        QVariantMap songMap;
        songMap["name"] = it.value()->_trackName;
        songMap["artist"] = it.value()->_artist;
        results.append(songMap);
        count++;
    }

    return results;
}
