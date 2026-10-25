#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QDir>
#include <QVector>
#include <QSet>
#include <QCache>
#include <QHash>
#include <QStringConverter> // Qt6 需要这个头文件

class SearchEngine : public QObject
{
    Q_OBJECT

public:
    explicit SearchEngine(QObject *parent = nullptr);
    void buildIndex(const QDir &directory);
    QString search(const QString &query);

signals:
    void progressUpdated(int current, int total);

private:
    struct WordPosition {
        short fileIndex;
        short lineNumber;
    };

    struct FileInfo {
        QString fileName;
        QVector<QString> lines;
    };

    QVector<QList<WordPosition>> invertedIndex;
    QVector<FileInfo> files;
    QCache<QString, QString> queryCache{10000}; // 增大缓存容量

    void processFile(const QString &filePath, int fileIndex);
    QString getFileNameWithoutExtension(const QString &fileName) const;
    quint64 computeBitmask(const QStringList &words, int fileIndex) const;
    bool validatePosition(const WordPosition &pos) const;
};

#endif // SEARCHENGINE_H
