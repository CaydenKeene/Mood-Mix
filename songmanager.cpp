#include "songmanager.h"

SongManager::SongManager(QObject *parent)
    : QObject{parent}
{
    _data.LoadData("Data/dataset.csv");
    addSongs();
}

void SongManager::addSongs()
{
    for(auto _song : _data.GetAllSongs())
    {
        m_trie.insert(_song->_trackName.toLower().toStdString(), _song);
    }
}


QVariantList SongManager::searchSongs(const QString &query)
{
    QVariantList results;
    int count = 0;

    if (query.length() == 0) {
        return results;
    }

    std::string queryStd = query.toLower().toStdString();
    auto range = m_trie.equal_prefix_range(queryStd);
    for (auto it = range.first; it != range.second && count < 10; ++it) {
        QVariantMap songMap;
        songMap["name"] = it.value()->_trackName;
        songMap["artist"] = it.value()->_artist;
        songMap["trackID"] = it.value()->_trackID;
        results.append(songMap);
        count++;
    }

    return results;
}

QVariantList SongManager::mergeSort(QString name, QString songAttribute) {
    return _data.sortByMergeSort(name, songAttribute);
};

QString SongManager::_getMergeTime() {
    return _data.getMergeTime();
}

QString SongManager::_getShellTime() {
    return _data.getShellTime();
}

void SongManager::shellSort(QString name, QString songAttribute) {
    _data.sortByShellSort(name, songAttribute);
}

void SongManager::spotify(QString trackID) {
    _data.openInSpotify(trackID);
}
