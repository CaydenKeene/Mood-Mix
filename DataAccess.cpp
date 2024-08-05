#include "DataAccess.h"

DataAccess::DataAccess(QObject *parent)
    : QObject{parent}
{

}

DataAccess::DataAccess(std::string fileName)
{
    LoadData(fileName);
}

DataAccess::~DataAccess()
{
    for (auto &tempSong : _allSongs)
    {
        delete tempSong;
    }

}

void DataAccess::LoadData(std::string fileName)
{
    fileName = "/" + fileName;
    fileName = QCoreApplication::applicationDirPath().toUtf8().constData() + fileName;

    if(!std::filesystem::exists(fileName))
    {
        throw std::runtime_error("Could not find file" + fileName);
    }

    std::ifstream dataSet(fileName);

    if(!dataSet.is_open())
    {
        throw std::runtime_error("Could not open " + fileName);
    }
    else
    {
        std::string line;
        std::getline(dataSet, line); //Skipping the csv header

        while (std::getline(dataSet, line))
        {
            Song* tempSong = new Song();
            std::string tempData;
            std::istringstream inStream(line);

            getline(inStream, tempData, ','); //index (int)

            tempData = GetColumnData(inStream); //track_id (string)
            tempSong->_trackID = QString::fromStdString(tempData);

            tempData = GetColumnData(inStream); // artists (string)
            tempSong->_artist = QString::fromStdString(tempData);

            tempData = GetColumnData(inStream); // album_name (string)

            tempData = GetColumnData(inStream); // track_name (string)
            tempSong->_trackName = QString::fromStdString(tempData);

            getline(inStream, tempData, ','); // popularity (int)
            tempSong->_popularity = std::stoi(tempData);

            getline(inStream, tempData, ','); // duration_ms (float)

            getline(inStream, tempData, ','); // explicit (bool)
            tempSong->_explicit = (tempData == "True") ? true : false;
            if(tempSong->_explicit)
            {
                continue;   // Skip if explicit is true
            }

            getline(inStream, tempData, ','); // danceability (float)
            tempSong->_danceability = std::stof(tempData);

            getline(inStream, tempData, ','); // energy (float)
            tempSong->_energy = std::stof(tempData);

            getline(inStream, tempData, ','); // key (int)

            getline(inStream, tempData, ','); // loudness (float)
            tempSong->_loudness = std::stof(tempData);

            getline(inStream, tempData, ','); // discovery mode (bool)

            getline(inStream, tempData, ','); // speechiness (float)

            getline(inStream, tempData, ','); // acousticness (float)

            getline(inStream, tempData, ','); // instrumentalness (float)

            getline(inStream, tempData, ','); // liveness (float)

            getline(inStream, tempData, ','); // valence (float)
            tempSong->_valence = std::stof(tempData);

            getline(inStream, tempData, ','); // tempo (float)
            tempSong->_tempo = std::stof(tempData);

            getline(inStream, tempData, ','); // time_signature (int)

            tempData = GetColumnData(inStream); // track_genre (string)
            tempSong->_genre = QString::fromStdString(tempData);

            _genreCollection[tempSong->_genre].append(tempSong);    // Add the the genre vectors
            _allSongs.append(tempSong);     // Add to the total list
        }
        dataSet.close();
    }
}

std::string DataAccess::GetColumnData(std::istringstream& dataStream)
{
    std::string data;
    std::string tempdata;
    int doubleQuoteCount = 0;
    getline(dataStream, data, ',');

    if(data[0] == '"')
    {
        for (char c : data) {
            if (c == '"') {
                doubleQuoteCount++;
            }
        }
        while((data.back() != '"') || (doubleQuoteCount % 2 != 0))
        {
            getline(dataStream, tempdata, ',');
            data += tempdata;
            for (char c : tempdata) {
                if (c == '"') {
                    doubleQuoteCount++;
                }
            }
        }
    }
    return data;
}

QVector<Song*>& DataAccess::GetSongsByGenre(QString& genreName)
{
    return _genreCollection[genreName];
}

QVector<Song*>& DataAccess::GetAllSongs()
{
    return _allSongs;
}

void DataAccess::merge(QVector<Song*>& songList, SongAttributes& songAttribute, int left, int mid, int right, const float& attributeVal)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Song** X = new Song*[n1];
    Song** Y = new Song*[n2];

    for (int i = 0; i < n1; i++)
        X[i] = songList[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = songList[mid + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    bool lessThanEqual = false;
    while (i < n1 && j < n2)
    {

        switch(songAttribute) {
        case danceability:
            lessThanEqual = abs(attributeVal - X[i]->_danceability) <= abs(attributeVal - Y[j]->_danceability);
            break;
        case energy:
            lessThanEqual = abs(attributeVal - X[i]->_energy) <= abs(attributeVal - Y[j]->_energy);
            break;
        case loudness:
            lessThanEqual = abs(attributeVal - X[i]->_loudness) <= abs(attributeVal - Y[j]->_loudness);
            break;
        case valence:
            lessThanEqual = abs(attributeVal - X[i]->_valence) <= abs(attributeVal - Y[j]->_valence);
            break;
        case tempo:
            lessThanEqual = abs(attributeVal - X[i]->_tempo) <= abs(attributeVal - Y[j]->_tempo);
            break;
        }

        if (lessThanEqual)
        {
            songList[k] = X[i];
            i++;
        }
        else
        {
            songList[k] = Y[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        songList[k] = X[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        songList[k] = Y[j];
        j++;
        k++;
    }

    delete[] X;
    delete[] Y;
}

void DataAccess::mergeSort(QVector<Song*>& songList, SongAttributes& songAttribute, int left, int right, const float& attributeVal)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(songList, songAttribute, left, mid, attributeVal);
        mergeSort(songList, songAttribute, mid + 1, right, attributeVal);

        merge(songList, songAttribute, left, mid, right, attributeVal);
    }
}

/*
QVector<Song*> DataAccess::SortByMergeSort(Song* song, SongAttributes songAttribute)
{
    _mergeSorted.clear();
    for(Song* tempSong : GetSongsByGenre(song->_genre))
    {   if(tempSong != song && tempSong->_popularity >= 30)
            _mergeSorted.push_back(tempSong);
    }

    float attributeVal;
    switch(songAttribute) {
    case danceability:
        attributeVal = song->_danceability;
        break;
    case energy:
        attributeVal = song->_energy;
        break;
    case loudness:
        attributeVal = song->_loudness;
        break;
    case valence:
        attributeVal = song->_valence;
        break;
    case tempo:
        attributeVal = song->_tempo;
        break;
    }

    mergeSort(_mergeSorted, songAttribute, 0, _mergeSorted.size()-1, attributeVal);

    return _mergeSorted;
}
*/


QVariantList DataAccess::sortByMergeSort(QString &name, QString &attribute)
{
    //finds the song pointer for the given song name
    Song* song;
    for (int i=0; i<_allSongs.size(); i++) {
        if (_allSongs[i]->_trackName == name) {
            song = _allSongs[i];
        }
    }

    //adds all the songs from the given songs genre to the _mergeSorted vector
    _mergeSorted.clear();
    /*
    for(Song* tempSong : GetSongsByGenre(song->_genre))
    {   if(tempSong != song)
            _mergeSorted.push_back(tempSong);
    }
    */
    //adds all the songs to be sorted instead of just one genre
    for(Song* tempSong : _allSongs)
    {   if(tempSong != song)
            _mergeSorted.push_back(tempSong);
    }

    enum SongAttributes songAttribute;
    float attributeVal;
    if (attribute == "danceability") {
        attributeVal = song->_danceability;
        songAttribute = danceability;
    } else if (attribute == "energy") {
        attributeVal = song->_energy;
        songAttribute = energy;
    } else if (attribute == "loudness") {
        attributeVal = song->_loudness;
        songAttribute = loudness;
    } else if (attribute == "valence") {
        attributeVal = song->_valence;
        songAttribute = valence;
    } else if (attribute == "tempo") {
        attributeVal = song->_tempo;
        songAttribute = tempo;
    }

    //start timer
    auto start = std::chrono::high_resolution_clock::now();

    //run mergeSort function
    mergeSort(_mergeSorted, songAttribute, 0, _mergeSorted.size()-1, attributeVal);

    //end timer and find duration
    auto end = std::chrono::high_resolution_clock::now();
    long long mergeTimeMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    mergeTime = mergeTimeMS/1000.0;

    QVariantList results;
    for (int i=0; i<_mergeSorted.size(); i++) {
        //changed to only display songs of the same genre
        if (_mergeSorted[i]->_popularity >= 50 && _mergeSorted[i]->_genre == song->_genre) {
            QVariantMap songMap;
            songMap["name"] = _mergeSorted[i]->_trackName;
            songMap["artist"] = _mergeSorted[i]->_artist;
            results.append(songMap);
        }
    }

    qDebug() << "songs sorted using merge: " << _mergeSorted.size();

    return results;
}

QString DataAccess::getMergeTime() {
    return QString::number(mergeTime);
}

QString DataAccess::getShellTime() {
    return QString::number(shellTime);
}

//possible fix to shellSort being faster than the mergeSort is to sort all of the
//songs and then only add the songs of the same genre do the vector that is displayed

//void bc we only use the sorted QVariantList from the mergeSort function
void DataAccess::sortByShellSort(QString &name, QString &attribute) {
    //finds the song pointer for the given song name
    Song* song;
    for (int i=0; i<_allSongs.size(); i++) {
        if (_allSongs[i]->_trackName == name) {
            song = _allSongs[i];
        }
    }

    //adds all the songs from the given songs genre to the _shellSorted vector
    _shellSorted.clear();
    //changed to use all songs
    for(Song* tempSong : _allSongs) {
        if(tempSong != song) {
            float  val;
            if (attribute == "danceability") {
                val = abs(song->_danceability - tempSong->_danceability);
            } else if (attribute == "energy") {
                val = abs(song->_energy - tempSong->_energy);
            } else if (attribute == "loudness") {
                val = abs(song->_loudness - tempSong->_loudness);
            } else if (attribute == "valence") {
                val = abs(song->_valence - tempSong->_valence);
            } else if (attribute == "tempo") {
                val = abs(song->_tempo - tempSong->_tempo);
            }
            _shellSorted.push_back({tempSong, val});
        }
    }

    //start timer
    auto start = std::chrono::high_resolution_clock::now();

    //run shellSort function
    int n = _shellSorted.size();
    int gap = n/2;
    while (gap > 0) {
        for (int i=gap; i<n; i++) {
            QPair<Song*, float> temp;
            temp = _shellSorted[i];
            int j;
            for (j=i; j>=gap && _shellSorted[j-gap].second > temp.second; j-=gap) {
                _shellSorted[j] =  _shellSorted[j-gap];
            }
            _shellSorted[j] = temp;
        }
        if (gap == 2) {
            gap = 1;
        } else {
            gap /= 2.2;
        }
    }

    //end timer and find duration
    auto end = std::chrono::high_resolution_clock::now();
    long long shellTimeMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    shellTime = shellTimeMS/1000.0;

    qDebug() << "songs sorted using shell: " << _shellSorted.size();

    int count = 0;
    for (int i=0; i<_shellSorted.size(); i++) {
        if (_shellSorted[i].first->_popularity >= 50 && _shellSorted[i].first->_genre == song->_genre) {
            qDebug() << _shellSorted[i].first->_trackName << _shellSorted[i].second;
            count++;
        }
    }
    qDebug() << "Songs shown: " << count;
}
