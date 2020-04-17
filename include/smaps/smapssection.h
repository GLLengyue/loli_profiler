#ifndef SMAPSSECTION_H
#define SMAPSSECTION_H

#include <QVector>

struct SMapsSectionAddr {
    quint64 start_ = 0, end_ = 0, offset_ = 0;
    SMapsSectionAddr() = default;
    SMapsSectionAddr(quint64 start, quint64 end, quint64 offset) :
        start_(start), end_(end), offset_(offset) {}
};

struct SMapsSection {
    QVector<SMapsSectionAddr> addrs_;
    quint32 virtual_ = 0;
    quint32 rss_ = 0;
    quint32 pss_ = 0;
    quint32 sharedClean_ = 0;
    quint32 sharedDirty_ = 0;
    quint32 privateClean_ = 0;
    quint32 privateDirty_ = 0;
    bool Contains(quint64 addr, qint32 size, quint64& baseAddr) const  {
        for (auto& sectionAddr : addrs_) {
            auto start = sectionAddr.start_ - sectionAddr.offset_;
            auto end = sectionAddr.end_ - sectionAddr.offset_;
            if (addr >= start &&
                addr + static_cast<quint64>(size) <= end) {
                baseAddr = start;
                return true;
            }
        }
        return false;
    }
};

#endif // SMAPSSECTION_H
