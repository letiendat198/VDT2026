#ifndef WKBCONVERTER_H
#define WKBCONVERTER_H

#include <QString>
#include <QByteArray>
#include <QGeoCoordinate>

// https://libgeos.org/specifications/wkb/#standard-wkb
enum WKBGeometryType {
    wkbInvalid = 0,
    wkbPoint = 1,
    wkbLineString = 2,
    wkbPolygon = 3,
    wkbMultiPoint = 4,
    wkbMultiLineString = 5,
    wkbMultiPolygon = 6,
    wkbGeometryCollection = 7
};

// We only handle point and polygon since they're the only things we care
class WKBConverter
{
public:
    WKBConverter(const QByteArray &bin);

    QGeoCoordinate toCoord();
    // For POLYGON geometry type
    QList<QGeoCoordinate> toListCoord();
private:
    bool m_littleEdian{};
    WKBGeometryType m_type{};
    QDataStream m_ds{};
};

#endif // WKBCONVERTER_H
