#pragma once

#include <QObject>

class BuildIndex : public QObject {
protected:
    Q_OBJECT
    Q_DISABLE_COPY(BuildIndex)
public:
    BuildIndex (QObject * parent = nullptr);
    virtual ~BuildIndex() = default;
};
