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
            tempSong->_explicit = (tempData == "TRUE") ? true : false;

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
