#include "WKBConverter.h"

#include <QPointF>
#include <QPolygonF>
#include <QRectF>
#include <QDebug>

WKBConverter::WKBConverter(const QString &bin) {
    m_bytes = QByteArray::fromHex(bin.toUtf8());

    m_littleEdian = m_bytes[0];

    QDataStream m_ds(m_bytes);
    m_ds.skipRawData(1);
    m_ds.setByteOrder(m_littleEdian ? QDataStream::ByteOrder::LittleEndian : QDataStream::ByteOrder::BigEndian);

    quint32 type;
    m_ds >> type;
    m_type = WKBGeometryType(type);
}

Coordinate WKBConverter::toCoord(){
    double log;
    double lat;

    // X, then Y AKA long, then lat
    m_ds >> log;
    m_ds >> lat;

    return {lat, log};
}

QPointF WKBConverter::toQPointF() {
    Coordinate coord = toCoord();
    // TODO: point in QML may work in lat/long? If shit breaks, it's probably this
    return QPointF(coord.longitude, coord.latitude);
}

QPolygonF WKBConverter::toQPolygonF() {
    QPolygonF poly;
    quint32 numRings;
    m_ds >> numRings;

    while(--numRings) {
        quint32 numPoints;
        m_ds >> numPoints;

        while(--numPoints) poly.append(toQPointF());
    }

    return poly;
}
