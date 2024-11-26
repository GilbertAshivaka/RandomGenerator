#ifndef COUNTERCLASS_H
#define MYCOUNTER_H

#include <QObject>

class CounterClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
    explicit CounterClass(QObject *parent = nullptr) : QObject(parent), m_count(0) {}
    int count() const { return m_count; }

public slots:
    void increment() {
        setCount(m_count + 1);
    }

    void decrement() {
        setCount(m_count - 1);
    }

    void setCount(int count) {
        if (m_count == count) return;
        m_count = count;
        emit countChanged();
    }

signals:
    void countChanged();

private:
    int m_count;
};

#endif // MYCOUNTER_H
