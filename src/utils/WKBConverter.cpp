#include "WKBConverter.h"

#include <QPointF>
#include <QPolygonF>
#include <QRectF>
#include <QDebug>

WKBConverter::WKBConverter(const QByteArray &bin) : m_ds(bin) {
    qDebug() << "Converting WKB:" << bin.toHex();

    m_littleEdian = bin[0];

    m_ds.skipRawData(1);
    m_ds.setByteOrder(m_littleEdian ? QDataStream::ByteOrder::LittleEndian : QDataStream::ByteOrder::BigEndian);

    quint32 type;
    m_ds >> type;
    m_type = WKBGeometryType(type);
}

QGeoCoordinate WKBConverter::toCoord(){
    qreal log;
    qreal lat;

    // X, then Y AKA long, then lat
    m_ds >> log;
    m_ds >> lat;

    return QGeoCoordinate(lat, log);
}

QPointF WKBConverter::toQPointF() {
    QGeoCoordinate coord = this->toCoord();
    // TODO: point in QML may work in lat/long? If shit breaks, it's probably this
    return QPointF(coord.longitude(), coord.latitude());
}

QPolygonF WKBConverter::toQPolygonF() {
    QPolygonF poly;
    quint32 numRings;
    m_ds >> numRings;

    while(--numRings) {
        quint32 numPoints;
        m_ds >> numPoints;

        while(--numPoints) poly.append(this->toQPointF());
    }

    return poly;
}
