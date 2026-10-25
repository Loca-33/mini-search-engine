#include "searchengine.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QElapsedTimer>
#include <algorithm>

SearchEngine::SearchEngine(QObject *parent) : QObject(parent) {}

void SearchEngine::buildIndex(const QDir &directory) {
    QElapsedTimer timer;
    timer.start();

    invertedIndex.clear();
    files.clear();
    queryCache.clear();

    // 预分配内存
    QStringList fileNames = directory.entryList(QDir::Files | QDir::Readable, QDir::Name);
    invertedIndex.resize(10000);
    files.reserve(fileNames.size());

    for (int i = 0; i < fileNames.size(); ++i) {
        processFile(directory.filePath(fileNames[i]), i);
        if (i % 10 == 0) {
            emit progressUpdated(i + 1, fileNames.size());
        }
    }

    qDebug() << "索引构建完成，耗时" << timer.elapsed() << "毫秒";
}

void SearchEngine::processFile(const QString &filePath, int fileIndex) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << filePath;
        return;
    }

    FileInfo fileInfo;
    fileInfo.fileName = QFileInfo(file).fileName();
    fileInfo.lines.reserve(100); // 假设平均每个文件100行

    QTextStream in(&file);
    int lineNumber = 0;
    static QRegularExpression wordRegex(R"(\b\w+\b)");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue; // 跳过空行

        fileInfo.lines.append(line);

        auto matchIter = wordRegex.globalMatch(line);
        while (matchIter.hasNext()) {
            QString word = matchIter.next().captured().toLower();
            uint hash = qHash(word) % invertedIndex.size();
            invertedIndex[hash].append({static_cast<short>(fileIndex),
                                        static_cast<short>(lineNumber)});
        }
        lineNumber++;
    }

    files.append(fileInfo);
    file.close();
}

QString SearchEngine::search(const QString &query) {
    // 快速处理短查询
    if (query.size() < 2) return "0\n查询过短";

    // 缓存检查
    if (QString* cached = queryCache[query]) {
        return *cached;
    }

    QStringList queryWords;
    static QRegularExpression wordRegex(R"(\b\w+\b)");
    auto matchIter = wordRegex.globalMatch(query);
    while (matchIter.hasNext()) {
        queryWords.append(matchIter.next().captured().toLower());
    }

    if (queryWords.isEmpty()) {
        return "0\n无有效查询词";
    }

    // 第一遍筛选
    QVector<int> candidateFiles;
    const quint64 targetMask = (1ULL << queryWords.size()) - 1;
    for (int fileIndex = 0; fileIndex < files.size(); ++fileIndex) {
        if (computeBitmask(queryWords, fileIndex) == targetMask) {
            candidateFiles.append(fileIndex);
        }
    }

    // 第二遍统计
    QHash<int, int> fileHitCounts;
    QHash<int, QSet<short>> fileMatches;
    for (int fileIndex : candidateFiles) {
        QSet<short> matchedLines;
        int hits = 0;

        for (const QString &word : queryWords) {
            uint hash = qHash(word) % invertedIndex.size();
            for (const auto &pos : invertedIndex[hash]) {
                if (pos.fileIndex == fileIndex) {
                    matchedLines.insert(pos.lineNumber);
                    hits++;
                }
            }
        }

        if (!matchedLines.isEmpty()) {
            fileHitCounts[fileIndex] = hits;
            fileMatches[fileIndex] = matchedLines;
        }
    }

    // 生成结果
    QString result;
    result.reserve(4096); // 预分配内存
    result += QString::number(fileHitCounts.size()) + "\n";

    if (!fileHitCounts.isEmpty()) {
        // 排序
        QList<int> sortedFiles = fileHitCounts.keys();
        std::sort(sortedFiles.begin(), sortedFiles.end(),
                  [&](int a, int b) {
                      return fileHitCounts[a] != fileHitCounts[b] ?
                                 fileHitCounts[a] > fileHitCounts[b] :
                                 files[a].fileName < files[b].fileName;
                  });

        // 构建结果
        for (int fileIndex : sortedFiles) {
            result += getFileNameWithoutExtension(files[fileIndex].fileName) + "\n";
            QList<short> sortedLines = fileMatches[fileIndex].values();
            std::sort(sortedLines.begin(), sortedLines.end());
            for (short lineNum : sortedLines) {
                result += files[fileIndex].lines[lineNum] + "\n";
            }
        }
    } else {
        result += "Not Found";
    }

    queryCache.insert(query, new QString(result));
    return result;
}

quint64 SearchEngine::computeBitmask(const QStringList &words, int fileIndex) const {
    quint64 mask = 0;
    for (int i = 0; i < words.size(); ++i) {
        uint hash = qHash(words[i]) % invertedIndex.size();
        for (const auto &pos : invertedIndex[hash]) {
            if (pos.fileIndex == fileIndex) {
                mask |= (1ULL << i);
                break;
            }
        }
    }
    return mask;
}

QString SearchEngine::getFileNameWithoutExtension(const QString &fileName) const {
    int dotIndex = fileName.lastIndexOf('.');
    return dotIndex >= 0 ? fileName.left(dotIndex) : fileName;
}
