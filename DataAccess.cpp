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

    QVector<Song*> X;
    QVector<Song*> Y;

    for (int i = 0; i < n1; i++)
        X.push_back(songList[left + i]);
    for (int j = 0; j < n2; j++)
        Y.push_back(songList[mid + 1 + j]);

    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        bool lessThanEqual = false;
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
